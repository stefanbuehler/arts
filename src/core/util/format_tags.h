#pragma once

#include <configtypes.h>

#include <concepts>
#include <format>
#include <map>
#include <print>
#include <ranges>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>

using namespace std::literals;

struct format_tags;
template <typename T>
concept arts_inner_fmt =
    requires(std::formatter<T> x) { x.inner_fmt().tags; } and
    std::same_as<
        format_tags,
        std::remove_cvref_t<decltype(std::formatter<T>{}.inner_fmt().tags)>>;

template <typename T>
concept arts_formattable =
    std::formattable<T, char> and arts_inner_fmt<T> and requires(T x) {
      std::format("{}", x);
      std::format("{:sqNB,}", x);
    };

template <typename T>
concept arts_formattable_or_value_type =
    arts_formattable<T> or std::integral<T> or std::floating_point<T> or
    std::same_as<T, std::string>;

struct format_tags {
  bool names     = false;
  bool comma     = false;
  bool bracket   = false;
  bool quoted    = false;
  bool short_str = false;

  [[nodiscard]] constexpr std::string get_format_args() const {
    std::string out{'{'};
    if (names or comma or bracket or quoted or short_str) {
      out += ':';
    }
    if (names) out += 'N';
    if (comma) out += ',';
    if (quoted) out += 'q';
    if (short_str) out += 's';
    if (bracket) out += 'B';
    out += '}';

    out.shrink_to_fit();

    return out;
  }

  template <typename T>
  constexpr void compat(std::formatter<T>& x) const {
    if constexpr (requires { x.inner_fmt().tags = *this; }) {
      x.inner_fmt().tags = *this;
    } else if constexpr (requires { x = *this; }) {
      x = *this;
    } else if constexpr (requires { x.tags = *this; }) {
      x.tags = *this;
    }
  }

  template <typename... Ts>
  constexpr void compat(std::formatter<Ts>&... x) const
    requires(sizeof...(Ts) > 1)
  {
    (compat(x), ...);
  }

  [[nodiscard]] constexpr std::string_view sep(bool newline = false) const {
    if (newline) {
      if (comma) return ",\n"sv;
      return "\n"sv;
    }
    if (comma) return ", "sv;
    return " "sv;
  }

  [[nodiscard]] constexpr std::string_view quote() const {
    if (quoted) return R"(")"sv;
    return ""sv;
  }

  template <class FmtContext>
  void add_if_bracket(FmtContext& ctx, char x) const {
    if (bracket) std::format_to(ctx.out(), "{}", x);
  }

  template <class FmtContext>
  constexpr auto format(FmtContext& ctx) const {
    return ctx.out();
  }

  template <class FmtContext, std::formattable<char> T, typename... Rest>
  constexpr auto format(FmtContext& ctx, const T& x, const Rest&... r) const {
    std::formatter<T> fmt;
    compat(fmt);
    fmt.format(x, ctx);
    return format(ctx, r...);
  }
};

constexpr std::format_parse_context::iterator parse_format_tags(
    format_tags& fmt, std::format_parse_context& ctx) {
  auto&& it = ctx.begin();

  while (it != ctx.end() and *it != '}') {
    if (*it == ',') {
      fmt.comma = true;
      ++it;
      continue;
    }

    if (*it == 'B') {
      fmt.bracket = true;
      ++it;
      continue;
    }

    if (*it == 's') {
      fmt.short_str = true;
      ++it;
      continue;
    }

    if (*it == 'N') {
      fmt.names = true;
      ++it;
      continue;
    }

    if (*it == 'q') {
      fmt.quoted = true;
      ++it;
      continue;
    }

    throw std::format_error("Invalid format args for arts-type");
  }

  return it;
}

struct arts_formattable_compat_format_tags {
  format_tags tags;

  [[nodiscard]] constexpr auto& inner_fmt() { return *this; }
  [[nodiscard]] constexpr const auto& inner_fmt() const { return *this; }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return parse_format_tags(tags, ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const auto& v, FmtContext& ctx) const {
    return std::format_to(ctx.out(), "{}", v);
  }
};

template <class FmtContext, class iterable>
void format_value_iterable(FmtContext& ctx,
                           const format_tags& tags,
                           const iterable& v) {
  const std::size_t n = std::size(v);
  if (tags.short_str and n > 8) {
    const auto sep = tags.sep();
    for (auto&& s : v | std::views::take(3)) {
      tags.format(ctx, s, sep);
    }
    tags.format(ctx, "..."sv);
    for (auto&& s : v | std::views::drop(n - 3)) {
      tags.format(ctx, sep, s);
    }
  } else {
    std::string_view next = tags.sep();
    std::string_view sep  = ""sv;
    for (auto&& a : v) {
      tags.format(ctx, std::exchange(sep, next), a);
    }
  }
}

template <class FmtContext, class iterable>
void format_map_iterable(FmtContext& ctx,
                         const format_tags& tags,
                         const iterable& m) {
  const std::size_t n = std::size(m);
  if (tags.short_str and n > 8) {
    const auto sep = tags.sep();
    for (auto&& [k, v] : m | std::views::take(3)) {
      tags.format(ctx, k, ": "sv, v, sep);
    }
    tags.format(ctx, "..."sv);
    for (auto&& [k, v] : m | std::views::drop(n - 3)) {
      tags.format(ctx, sep, k, ": "sv, v);
    }
  } else {
    std::string_view next = tags.sep();
    std::string_view sep  = ""sv;
    for (auto&& [k, v] : m) {
      tags.format(ctx, std::exchange(sep, next), k, ": "sv, v);
    }
  }
}

template <arts_formattable_or_value_type... WTs>
struct std::formatter<std::variant<WTs...>> {
  format_tags tags;

  [[nodiscard]] constexpr auto& inner_fmt() { return *this; }

  [[nodiscard]] constexpr const auto& inner_fmt() const { return *this; }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return parse_format_tags(tags, ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::variant<WTs...>& v,
                              FmtContext& ctx) const {
    std::visit([*this, &ctx]<typename T>(const T& x) { tags.format(ctx, x); },
               v);
    return ctx.out();
  }
};

template <arts_formattable_or_value_type Key,
          arts_formattable_or_value_type Value>
struct std::formatter<std::unordered_map<Key, Value>> {
  format_tags tags;

  [[nodiscard]] constexpr auto& inner_fmt() { return *this; }

  [[nodiscard]] constexpr const auto& inner_fmt() const { return *this; }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return parse_format_tags(tags, ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::unordered_map<Key, Value>& v,
                              FmtContext& ctx) const {
    tags.add_if_bracket(ctx, '{');
    format_map_iterable(ctx, inner_fmt().tags, v);
    tags.add_if_bracket(ctx, '}');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type Key,
          arts_formattable_or_value_type Value>
struct std::formatter<std::map<Key, Value>> {
  format_tags tags;

  [[nodiscard]] constexpr auto& inner_fmt() { return *this; }

  [[nodiscard]] constexpr const auto& inner_fmt() const { return *this; }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return parse_format_tags(tags, ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::unordered_map<Key, Value>& v,
                              FmtContext& ctx) const {
    tags.add_if_bracket(ctx, '{');
    format_map_iterable(ctx, inner_fmt().tags, v);
    tags.add_if_bracket(ctx, '}');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type T>
struct std::formatter<std::span<T>> {
  std::conditional_t<arts_formattable<T>,
                     std::formatter<T>,
                     arts_formattable_compat_format_tags>
      fmt;

  [[nodiscard]] constexpr auto& inner_fmt() { return fmt.inner_fmt(); }
  [[nodiscard]] constexpr auto& inner_fmt() const { return fmt.inner_fmt(); }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return fmt.parse(ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::span<T>& v, FmtContext& ctx) const {
    inner_fmt().tags.add_if_bracket(ctx, '[');
    format_value_iterable(ctx, inner_fmt().tags, v);
    inner_fmt().tags.add_if_bracket(ctx, ']');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type T>
struct std::formatter<std::set<T>> {
  std::conditional_t<arts_formattable<T>,
                     std::formatter<T>,
                     arts_formattable_compat_format_tags>
      fmt;

  [[nodiscard]] constexpr auto& inner_fmt() { return fmt.inner_fmt(); }
  [[nodiscard]] constexpr auto& inner_fmt() const { return fmt.inner_fmt(); }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return fmt.parse(ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::set<T>& v, FmtContext& ctx) const {
    inner_fmt().tags.add_if_bracket(ctx, '[');
    format_value_iterable(ctx, inner_fmt().tags, v);
    inner_fmt().tags.add_if_bracket(ctx, ']');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type T>
struct std::formatter<std::unordered_set<T>> {
  std::conditional_t<arts_formattable<T>,
                     std::formatter<T>,
                     arts_formattable_compat_format_tags>
      fmt;

  [[nodiscard]] constexpr auto& inner_fmt() { return fmt.inner_fmt(); }
  [[nodiscard]] constexpr auto& inner_fmt() const { return fmt.inner_fmt(); }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return fmt.parse(ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::unordered_set<T>& v,
                              FmtContext& ctx) const {
    inner_fmt().tags.add_if_bracket(ctx, '[');
    format_value_iterable(ctx, inner_fmt().tags, v);
    inner_fmt().tags.add_if_bracket(ctx, ']');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type T, class Allocator>
struct std::formatter<std::vector<T, Allocator>> {
  std::conditional_t<arts_formattable<T>,
                     std::formatter<T>,
                     arts_formattable_compat_format_tags>
      fmt;

  [[nodiscard]] constexpr auto& inner_fmt() { return fmt.inner_fmt(); }
  [[nodiscard]] constexpr auto& inner_fmt() const { return fmt.inner_fmt(); }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return fmt.parse(ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::vector<T, Allocator>& v,
                              FmtContext& ctx) const {
    inner_fmt().tags.add_if_bracket(ctx, '[');
    format_value_iterable(ctx, inner_fmt().tags, v);
    inner_fmt().tags.add_if_bracket(ctx, ']');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type T, std::size_t N>
struct std::formatter<std::array<T, N>> {
  std::conditional_t<arts_formattable<T>,
                     std::formatter<T>,
                     arts_formattable_compat_format_tags>
      fmt;

  [[nodiscard]] constexpr auto& inner_fmt() { return fmt.inner_fmt(); }
  [[nodiscard]] constexpr auto& inner_fmt() const { return fmt.inner_fmt(); }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return fmt.parse(ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::array<T, N>& v,
                              FmtContext& ctx) const {
    inner_fmt().tags.add_if_bracket(ctx, '[');
    format_value_iterable(ctx, inner_fmt().tags, v);
    inner_fmt().tags.add_if_bracket(ctx, ']');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type A, arts_formattable_or_value_type B>
struct std::formatter<std::pair<A, B>> {
  format_tags tags;

  [[nodiscard]] constexpr auto& inner_fmt() { return *this; }
  [[nodiscard]] constexpr auto& inner_fmt() const { return *this; }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return parse_format_tags(tags, ctx);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::pair<A, B>& v, FmtContext& ctx) const {
    using std::ranges::views::take, std::ranges::views::drop;

    tags.add_if_bracket(ctx, '(');
    tags.format(ctx, v.first, tags.sep(), v.second);
    tags.add_if_bracket(ctx, ')');
    return ctx.out();
  }
};

template <arts_formattable_or_value_type... WT>
struct std::formatter<std::tuple<WT...>> {
  format_tags tags;

  [[nodiscard]] constexpr auto& inner_fmt() { return *this; }
  [[nodiscard]] constexpr auto& inner_fmt() const { return *this; }

  constexpr std::format_parse_context::iterator parse(
      std::format_parse_context& ctx) {
    return parse_format_tags(tags, ctx);
  }

  template <class FmtContext, std::size_t... Ints>
  void format(FmtContext& ctx,
              std::index_sequence<Ints...>,
              const tuple<WT...>& v) const {
    (tags.format(ctx, std::get<Ints>(v), tags.sep()), ...);
  }

  template <class FmtContext>
  FmtContext::iterator format(const std::tuple<WT...>& v,
                              FmtContext& ctx) const {
    using std::ranges::views::take, std::ranges::views::drop;

    tags.add_if_bracket(ctx, '(');
    format(ctx, std::index_sequence_for<WT...>{}, v);
    tags.add_if_bracket(ctx, ')');
    return ctx.out();
  }
};
