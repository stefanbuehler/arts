#pragma once

#include "matpack_concepts.h"
#include "nonstd.h"

#include <complex>
#include <type_traits>

template <typename T> struct ComplexLayout {
  T real, imag;
};

template <matpack::complex_type T>
constexpr matpack::complex_subtype<T> &real_val(T &c) noexcept {
  return reinterpret_cast<ComplexLayout<matpack::complex_subtype<T>>(&)>(c)
      .real;
}

template <matpack::complex_type T>
constexpr matpack::complex_subtype<T> &imag_val(T &c) noexcept {
  return reinterpret_cast<ComplexLayout<matpack::complex_subtype<T>>(&)>(c)
      .imag;
}

template <matpack::complex_type T>
constexpr matpack::complex_subtype<T> real_val(const T &c) noexcept {
  return reinterpret_cast<const ComplexLayout<matpack::complex_subtype<T>>(&)>(
             c)
      .real;
}

template <matpack::complex_type T>
constexpr matpack::complex_subtype<T> imag_val(const T &c) noexcept {
  return reinterpret_cast<const ComplexLayout<matpack::complex_subtype<T>>(&)>(
             c)
      .imag;
}

template <matpack::complex_type T>
constexpr T operator+(matpack::complex_subtype<T> x, T c) noexcept {
  return x + c;
}

template <matpack::complex_type T>
constexpr T operator-(matpack::complex_subtype<T> x, T c) noexcept {
  return x - c;
}

template <matpack::complex_type T>
constexpr T operator*(matpack::complex_subtype<T> x, T c) noexcept {
  return x * c;
}

template <matpack::complex_type T>
constexpr T operator/(matpack::complex_subtype<T> x, T c) noexcept {
  return x / c;
}
template <matpack::complex_type T>
constexpr T operator+(T x, matpack::complex_subtype<T> c) noexcept {
  return x + c;
}

template <matpack::complex_type T>
constexpr T operator-(T x, matpack::complex_subtype<T> c) noexcept {
  return x - c;
}

template <matpack::complex_type T>
constexpr T operator*(T x, matpack::complex_subtype<T> c) noexcept {
  return x * c;
}
template <matpack::complex_type T>
constexpr T operator/(T x, matpack::complex_subtype<T> c) noexcept {
  return x / c;
}

template <matpack::complex_type T> constexpr T operator+(T x, T c) {
  return x + c;
}

template <matpack::complex_type T> constexpr T operator-(T x, T c) {
  return x - c;
}

template <matpack::complex_type T> constexpr T operator*(T x, T c) {
  return x * c;
}

template <matpack::complex_type T> constexpr T operator/(T x, T c) {
  return x / c;
}

template <matpack::complex_type T> constexpr T operator-(T c) { return -c; }

template <matpack::complex_type T> constexpr T operator+(T c) { return c; }

template <matpack::complex_type T, matpack::complex_type U>
constexpr auto operator+(T x, U c) noexcept
  requires(not std::same_as<T, U>)
{
  using K = std::common_type_t<matpack::complex_subtype<T>,
                               matpack::complex_subtype<U>>;
  return std::complex<K>{static_cast<K>(x.real()), static_cast<K>(x.imag())} +
         std::complex<K>{static_cast<K>(c.real()), static_cast<K>(c.imag())};
}

template <matpack::complex_type T, matpack::complex_type U>
constexpr auto operator-(T x, U c) noexcept
  requires(not std::same_as<T, U>)
{
  using K = std::common_type_t<matpack::complex_subtype<T>,
                               matpack::complex_subtype<U>>;
  return std::complex<K>{static_cast<K>(x.real()), static_cast<K>(x.imag())} -
         std::complex<K>{static_cast<K>(c.real()), static_cast<K>(c.imag())};
}

template <matpack::complex_type T, matpack::complex_type U>
constexpr auto operator*(T x, U c) noexcept
  requires(not std::same_as<T, U>)
{
  using K = std::common_type_t<matpack::complex_subtype<T>,
                               matpack::complex_subtype<U>>;
  return std::complex<K>{static_cast<K>(x.real()), static_cast<K>(x.imag())} *
         std::complex<K>{static_cast<K>(c.real()), static_cast<K>(c.imag())};
}

template <matpack::complex_type T, matpack::complex_type U>
constexpr auto operator/(T x, U c) noexcept
  requires(not std::same_as<T, U>)
{
  using K = std::common_type_t<matpack::complex_subtype<T>,
                               matpack::complex_subtype<U>>;
  return std::complex<K>{static_cast<K>(x.real()), static_cast<K>(x.imag())} /
         std::complex<K>{static_cast<K>(c.real()), static_cast<K>(c.imag())};
}

template <matpack::complex_type T>
constexpr matpack::complex_subtype<T> abs2(T c) {
  return c.real() * c.real() + c.imag() * c.imag();
}

template <matpack::complex_type T> constexpr T conj(T c) {
  return {c.real(), -c.imag()};
}

template <matpack::complex_type T>
constexpr matpack::complex_subtype<T> real(T c) {
  return c.real();
}

template <matpack::complex_type T>
constexpr matpack::complex_subtype<T> imag(T c) {
  return c.imag();
}

inline std::complex<float> operator+(const double& d,
                                     const std::complex<float>& c) {
  return (float(d) + c);
}
inline std::complex<float> operator*(const double& d,
                                     const std::complex<float>& c) {
  return (float(d) * c);
}

inline std::complex<float> operator+(const std::complex<float>& c,
                                     const double& d) {
  return (c + float(d));
}
inline std::complex<float> operator*(const std::complex<float>& c,
                                     const double& d) {
  return (c * float(d));
}

// Constexpr versions of common Complex operations

// Helpers to keep equations readable
#define a1 c.real()
#define b1 c.imag()
#define a2 z.real()
#define b2 z.imag()

/** squared magnitude of c */
constexpr Numeric abs2(Complex c) noexcept { return a1 * a1 + b1 * b1; }

/** the conjugate of c */
constexpr Complex conj(Complex c) noexcept { return {a1, -b1}; }

/** real */
constexpr Numeric real(Complex c) noexcept { return a1; }

/** imag */
constexpr Numeric imag(Complex c) noexcept { return b1; }

// Basic constexpr operations for Complex that don't exist in the standard yet (C++11)
// NOTE: Remove these if there is ever an overload warning updating the C++ compiler version

constexpr Complex operator+(Complex c, Numeric n) noexcept {
  return {a1 + n, b1};
}
constexpr Complex operator-(Complex c, Numeric n) noexcept {
  return {a1 - n, b1};
}
constexpr Complex operator*(Complex c, Numeric n) noexcept {
  return {a1 * n, b1 * n};
}
constexpr Complex operator/(Complex c, Numeric n) noexcept {
  return {a1 / n, b1 / n};
}

constexpr Complex operator+(Numeric n, Complex c) noexcept {
  return {n + a1, b1};
}
constexpr Complex operator-(Numeric n, Complex c) noexcept {
  return {n - a1, -b1};
}
constexpr Complex operator*(Numeric n, Complex c) noexcept {
  return {n * a1, n * b1};
}
constexpr Complex operator/(Numeric n, Complex c) noexcept {
  return Complex(n * a1, -n * b1) / abs2(c);
}

constexpr Complex operator+(Complex c, Complex z) noexcept {
  return {a1 + a2, b1 + b2};
}
constexpr Complex operator-(Complex c, Complex z) noexcept {
  return {a1 - a2, b1 - b2};
}
constexpr Complex operator*(Complex c, Complex z) noexcept {
  return {a1 * a2 - b1 * b2, a1 * b2 + b1 * a2};
}
constexpr Complex operator/(Complex c, Complex z) noexcept {
  return Complex(a1 * a2 + b1 * b2, -a1 * b2 + b1 * a2) / abs2(z);
}
constexpr Complex operator-(Complex c) noexcept { return {-a1, -b1}; }

// Remove helpers to keep global namespace usable
#undef a1
#undef b1
#undef a2
#undef b2

// Basic constexpr operations for different types since C++11 std::complex is
// lacking conversions
// FIXME: Cannot be template because Eigen interferes, so explicit copies are
// required for operations NOTE: Remove these if there is ever an overload
// warning updating the C++ compiler version
#define _complex_operations_(T)                                                \
  constexpr Complex operator+(Complex c, T x) noexcept {                       \
    return operator+(c, static_cast<Numeric>(x));                              \
  }                                                                            \
  constexpr Complex operator-(Complex c, T x) noexcept {                       \
    return operator-(c, static_cast<Numeric>(x));                              \
  }                                                                            \
  constexpr Complex operator*(Complex c, T x) noexcept {                       \
    return operator*(c, static_cast<Numeric>(x));                              \
  }                                                                            \
  constexpr Complex operator/(Complex c, T x) noexcept {                       \
    return operator/(c, static_cast<Numeric>(x));                              \
  }                                                                            \
                                                                               \
  constexpr Complex operator+(T x, Complex c) noexcept {                       \
    return operator+(static_cast<Numeric>(x), c);                              \
  }                                                                            \
  constexpr Complex operator-(T x, Complex c) noexcept {                       \
    return operator-(static_cast<Numeric>(x), c);                              \
  }                                                                            \
  constexpr Complex operator*(T x, Complex c) noexcept {                       \
    return operator*(static_cast<Numeric>(x), c);                              \
  }                                                                            \
  constexpr Complex operator/(T x, Complex c) noexcept {                       \
    return operator/(static_cast<Numeric>(x), c);                              \
  }

_complex_operations_(int)
_complex_operations_(float)
_complex_operations_(Index)

#undef _complex_operations_

constexpr bool isnan(Complex c) noexcept {
  return nonstd::isnan(c.real()) or nonstd::isnan(c.imag());
}
