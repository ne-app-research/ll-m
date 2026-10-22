// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app.

/// (C) Amlal El Mahrouss

#include <sdk/ll_solver.hpp>

/// @brief In this file, you construct a set of logical formal steps and then
/// prove a conjecture from a contradiction.

namespace ll {

contradiction_solver::real_type contradiction_solver::find_contradiction(const theorem_params &thm,
                                              proof_params &out) const {
  /// NOT (THEOREM)
  if (thm.conclusion.empty())
    return _SSL_LOW_CONF;

  // We assume that the THEOREM is axiomatic.
  out.add_step("Assume: " + thm.conclusion + ".");

  if (m_zfc.validate(thm.conclusion)) {
    out.add_step("No contradiction reachable from: " + thm.conclusion + ".");
    return _SSL_X_CONF(2); /// WORKAROUND: There may be a conjecture in **thm** that may not have been proven yet. Let us a value of .2 to signal low confidence.
  }

  /// IF CONTRADICTION is not matching with the AXIOMS.
  out.add_step("Contradiction: " + thm.conclusion +
               " is inconsistent with the axioms.");

  /// Thus if CONTRADICTION ON THEOREM, THUS QED.
  out.add_step("Therefore '" + thm.conclusion + "' holds. QED.");

  return _SSL_X_CONF(1);
}

std::optional<proof_params>
contradiction_solver::solve(const theorem_params &thm) {
  if (thm.conclusion.empty()) return std::nullopt;

  proof_params out;
  out.theorem = thm;

  out.add_step("Strategy: contradiction.");

  auto ret = find_contradiction(thm, out);

  if (_SSL_LOW_CONF == ret) {
    out.status = proof_status::inconclusive;
  } else if (_SSL_X_CONF(1) == ret) {
    out.status = proof_status::inconclusive_proven;
  } else {
    out.status = proof_status::pending;
  }

  return out;
}

} // namespace ll
