// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app.

/// (C) Amlal El Mahrouss

#include <sdk/ll_solver.hpp>

/// @brief This file you'd construct a set of logical proofs or axioms towards a proof or disproof.

namespace ll {

construction_solver::real_type construction_solver::build_witness(const theorem_params &thm,
                                        proof_params         &out) const {
  for (const auto &h : thm.hypotheses) {
    if (!m_zfc.validate(h)) {
      out.add_step("Set validation failed for: '" + h + "'.");
      return _SSL_LOW_CONF;
    }

    out.add_step("Witness factor verified: '" + h + "'.");
  }

  if (!m_dtt.check(thm.hypotheses, thm.conclusion)) {
    out.add_step("Type check failed: '" + thm.conclusion +
                 "' not derivable from the verified factors.");
    
    return _SSL_LOW_CONF;
  }

  out.add_step("Witness constructed: '" + thm.conclusion + "'. QED.");
  return _SSL_X_CONF(5);
}

std::optional<proof_params>
construction_solver::solve(const theorem_params &thm) {
  if (thm.conclusion.empty()) return std::nullopt;

  proof_params out{};
  
  out.theorem = thm;
  out.add_step("Strategy: construction.");
  auto ret = build_witness(thm, out);

  if (ret == _SSL_LOW_CONF) {
    out.status = proof_status::inconclusive;
  } else if (ret == _SSL_X_CONF(5)) {
    out.status = proof_status::inconclusive_proven;
  } else {
    out.status = proof_status::proven;
  }

  return out;
}

} // namespace ll
