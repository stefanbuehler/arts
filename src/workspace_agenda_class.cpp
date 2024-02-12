#include "workspace_agenda_class.h"

#include <auto_wsa.h>
#include <auto_wsm.h>

#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "compare.h"
#include "debug.h"
#include "workspace_class.h"
#include "workspace_method_class.h"

void Agenda::add(const Method& method) {
  checked = false;
  method.add_defaults_to_agenda(*this);
  methods.push_back(method);
}

auto is_in(const std::vector<std::string>& seq) {
  return [&seq](auto& str) {
    return std::find(seq.begin(), seq.end(), str) != seq.end();
  };
}

auto is_not_in(const std::vector<std::string>& seq) {
  return [&seq](auto& str) {
    return std::find(seq.begin(), seq.end(), str) == seq.end();
  };
}

void Agenda::finalize(bool fix) try {
  static const auto& wsa = workspace_agendas();

  auto ag_ptr = wsa.find(name);
  if (ag_ptr == wsa.end()) {
    return;
  }

  std::vector<std::string> ins_first;
  std::vector<std::string> outs_first;
  std::vector<std::string> in_then_out;

  for (const Method& method : methods) {
    const auto& ins = method.get_ins();
    const auto& outs = method.get_outs();

    std::ranges::copy_if(
        ins,
        std::back_inserter(ins_first),
        [&outs_first, &ins_first, &in_then_out, &outs](const std::string& i) {
          const auto cmp = Cmp::eq(i);
          return not std::ranges::any_of(ins_first, cmp) and
                 not std::ranges::any_of(outs_first, cmp) and
                 not std::ranges::any_of(in_then_out, cmp) and
                 not std::ranges::any_of(outs, cmp);
        });

    std::ranges::copy_if(
        ins,
        std::back_inserter(in_then_out),
        [&outs_first, &in_then_out, &outs](const std::string& i) {
          const auto cmp = Cmp::eq(i);
          return not std::ranges::any_of(outs_first, cmp) and
                 not std::ranges::any_of(in_then_out, cmp) and
                 std::ranges::any_of(outs, cmp);
        });

    std::ranges::copy_if(
        outs,
        std::back_inserter(outs_first),
        [&outs_first, &ins_first, &in_then_out, &ins](const std::string& i) {
          const auto cmp = Cmp::eq(i);
          return not std::ranges::any_of(ins_first, cmp) and
                 not std::ranges::any_of(outs_first, cmp) and
                 not std::ranges::any_of(in_then_out, cmp) and
                 not std::ranges::any_of(ins, cmp);
        });
  }

  auto sort_and_erase_copies = [](std::vector<std::string>& vec) {
    std::ranges::sort(vec);
    auto [s, e] = std::ranges::unique(vec);
    vec.erase(s, e);
  };
  sort_and_erase_copies(ins_first);
  sort_and_erase_copies(outs_first);
  sort_and_erase_copies(in_then_out);

  const std::vector<std::string>& must_out = ag_ptr->second.output;
  const std::vector<std::string>& must_in = ag_ptr->second.input;

  for (const std::string& i : must_in) {
    if (std::ranges::binary_search(outs_first, i)) {
      throw std::runtime_error(
          var_string("Agenda ",
                     std::quoted(name),
                     " first uses ",
                     std::quoted(i),
                     " as an output but it is agenda input"));
    }

    if (not std::ranges::binary_search(ins_first, i)) {
      if (fix) {
        methods.emplace_back("Ignore",
                             std::vector<std::string>{i},
                             std::unordered_map<std::string, std::string>{});
      } else {
        throw std::runtime_error(var_string(
            "Agenda ", std::quoted(name), " does not use ", std::quoted(i)));
      }
    }
  }

  for (const std::string& o : must_out) {
    if (std::ranges::binary_search(ins_first, o) or
        std::ranges::binary_search(in_then_out, o)) {
      throw std::runtime_error(
          var_string("Agenda ",
                     std::quoted(name),
                     " first uses ",
                     std::quoted(o),
                     " as an input but it is agenda output"));
    }

    if (not std::ranges::binary_search(outs_first, o)) {
      if (fix) {
        methods.emplace_back("Touch",
                             std::vector<std::string>{o},
                             std::unordered_map<std::string, std::string>{});
      } else {
        throw std::runtime_error(var_string(
            "Agenda ", std::quoted(name), " does not set ", std::quoted(o)));
      }
    }
  }

  std::erase_if(ins_first, [&must_in](const auto& str) {
    return std::ranges::any_of(must_in, Cmp::eq(str));
  });

  std::erase_if(ins_first, [&in_then_out](const auto& str) {
    return std::ranges::binary_search(in_then_out, str);
  });

  copy = in_then_out;
  share = ins_first;

  checked = true;
} catch (std::exception& e) {
  throw std::runtime_error(var_string(
      "Error finalizing agenda ", std::quoted(name), '\n', e.what()));
}

void agenda_add_inner_logic(Workspace& out,
                            const Workspace& in,
                            WorkspaceAgendaBoolHandler handle) {
startover:
  for (auto& var : out) {
    if (var.second->holds<Agenda>()) {
      if (not handle.has(var.first)) {
        auto& ag = var.second->get<Agenda>();
        handle.set(var.first);
        ag.copy_workspace(out, in, true);
        goto startover;
      }
    } else if (var.second->holds<ArrayOfAgenda>()) {
      if (not handle.has(var.first)) {
        auto& aag = var.second->get<ArrayOfAgenda>();
        handle.set(var.first);
        for (auto& ag : aag) {
          ag.copy_workspace(out, in, true);
        }
        goto startover;
      }
    }
  }
}

void Agenda::copy_workspace(Workspace& out,
                            const Workspace& in,
                            bool share_only) const try {
  if (share_only) {
    for (auto& str : share) {
      if (not out.contains(str)) out.set(str, in.share(str));
    }
    for (auto& str : copy) {
      if (not out.contains(str)) out.set(str, in.share(str));
    }
  } else {
    for (auto& str : share) {
      out.set(str, in.share(str));
    }

    for (auto& str : copy) {
      if (out.contains(str)) {
        //! If copy and share are the same, copy will overwrite share (keep them unique!)
        //! Also if named-agenda call has set output variable, copy will take a copy of variable
        out.overwrite(str, out.copy(str));
      } else {
        out.set(str, in.copy(str));
      }
    }

    WorkspaceAgendaBoolHandler handle;
    handle.set(name);
    agenda_add_inner_logic(out, in, handle);
  }
} catch (std::exception& e) {
  throw std::runtime_error(var_string(
      "Cannot get value from\n\n", in, "\ninto\n\n", out, '\n', e.what()));
}

Workspace Agenda::copy_workspace(const Workspace& in) const {
  Workspace out{WorkspaceInitialization::Empty};
  copy_workspace(out, in);
  return out;
}

void Agenda::execute(Workspace& ws) const try {
  for (auto& method : methods) {
    method(ws);
  }
} catch (std::exception& e) {
  throw std::runtime_error(
      var_string("Error executing agenda ", std::quoted(name), '\n', e.what()));
}

bool Agenda::has_method(const std::string& method) const {
  for (auto& m : methods) {
    if (m.get_name() == method) {
      return true;
    }
  }
  return false;
}

Agenda::Agenda(std::string n,
               const std::vector<Method>& m,
               const std::vector<std::string>& s,
               const std::vector<std::string>& c,
               bool check)
    : name(std::move(n)), methods(m), share(s), copy(c), checked(check) {}

std::vector<std::string> split(const std::string& s, char c) {
  std::vector<std::string> out;
  std::string tmp;
  for (auto& ch : s) {
    if (ch == c) {
      out.push_back(tmp);
      tmp.clear();
    } else {
      tmp.push_back(ch);
    }
  }
  out.push_back(tmp);
  return out;
}

std::ostream& operator<<(std::ostream& os, const Agenda& a) {
  static const auto& wsa = workspace_agendas();

  auto ptr = wsa.find(a.name);
  const bool named = ptr != wsa.end();
  const bool checked = a.checked;

  os << "Agenda " << a.name;

  if (a.is_checked())
    os << " (checked)";
  else
    os << " (unchecked)";

  if (checked or named) {
    os << ":\n";

    if (named) {
      os << "  Output : ";
      for (auto& o : ptr->second.output) {
        os << o << ", ";
      }
      os << '\n';

      os << "  Input  : ";
      for (auto& i : ptr->second.input) {
        os << i << ", ";
      }
    }

    if (checked) {
      if (named) {
        os << '\n';
      }

      os << "  Share  : ";
      for (auto& s : a.share) {
        os << s << ", ";
      }
      os << '\n';

      os << "  Copy   : ";
      for (auto& c : a.copy) {
        os << c << ", ";
      }
    }
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const ArrayOfAgenda& a) {
  for (auto& ag : a) os << ag << '\n';
  return os;
}
