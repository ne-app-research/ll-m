// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app.

/// (C) Amlal El Mahrouss

#pragma once

#include <sdk/ll_model.hpp>
#include <ssl/sl_symbol.hpp>
#include <optional>

namespace ll {

// Base interface every proof solver implements.
class _LL_API solver_base {
public:
  virtual ~solver_base() = default;

  // Attempt to prove `thm`. Returns a completed proof_params on success,
  // or nullopt when the strategy cannot close the goal.
  virtual std::optional<proof_params> solve(const theorem_params &thm) = 0;
};

// Proof by induction.
class _LL_API induction_solver final : public solver_base {
public:
  std::optional<proof_params> solve(const theorem_params &thm) override;

private:
  bool check_base(const theorem_params &thm, proof_params &out) const;
  bool check_step(const theorem_params &thm, proof_params &out) const;

  dtt_solver m_dtt{};
};

// Proof by construction — finds a witness satisfying the conclusion.
class _LL_API construction_solver final : public solver_base {
public:
  std::optional<proof_params> solve(const theorem_params &thm) override;
  using real_type = double;

private:
  construction_solver::real_type build_witness(const theorem_params &thm, proof_params &out) const;

  dtt_solver     m_dtt{};
  zfc_set_solver m_zfc{};
};

// Proof by contradiction — assumes ¬conclusion and derives a contradiction.
class _LL_API contradiction_solver final : public solver_base {
public:
  std::optional<proof_params> solve(const theorem_params &thm) override;
  using real_type = double;

private:
  contradiction_solver::real_type find_contradiction(const theorem_params &thm, proof_params &out) const;

  zfc_set_solver m_zfc{};
};

} // namespace ll
