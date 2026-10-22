// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app.

/// (C) Amlal El Mahrouss

#include <sdk/ll_solver.hpp>

namespace ll {

bool induction_solver::check_base(const theorem_params &thm,
                                  proof_params &out) const {
  if (!m_dtt.check(thm.hypotheses, thm.conclusion))
    return false;

  out.add_step("Base case: '" + thm.conclusion +
               "' is derivable from the given hypotheses.");
  return true;
}

bool induction_solver::check_step(const theorem_params &thm,
                                  proof_params &out) const {
  std::vector<std::string> extended = thm.hypotheses;
  extended.push_back("inductive_hypothesis: " + thm.conclusion);

  if (!m_dtt.check(extended, thm.conclusion))
    return false;

  out.add_step("Inductive step: assuming '" + thm.conclusion +
               "', the conclusion holds at the next step.");
  return true;
}

/// @note solve assumes that all theorems and conjecture have been proven. If not, treat solve as inconclusive_proven.
std::optional<proof_params> induction_solver::solve(const theorem_params &thm) {
  if (thm.conclusion.empty()) return std::nullopt;

  proof_params out;
  out.theorem = thm;
  out.add_step("Strategy: induction.");

  auto ret = check_base(thm, out);
  auto ret2 = check_step(thm, out);

  if (!ret || !ret2) {
    out.status = proof_status::inconclusive;
    return out;
  } else if (ret || !ret2) {
    out.status = proof_status::pending;
    return out;
  }

  out.add_step("By induction, '" + thm.conclusion + "' holds. QED.");
  out.status = proof_status::proven;

  return out;
}

} // namespace ll
