// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app.

/// (C) Amlal El Mahrouss

#include <sdk/ll_trainer.hpp>
#include <ssl/sl_symbol.hpp>

using namespace ll;

int main(int, char **) {
  machine_model_priv model;
  induction_solver solver;

  basic_trainer t(model, solver);

  theorem_params thm;
  
  thm.name = "sqrt2_irrational";
  thm.hypotheses = {"n" _SSL_BELONGS_TO " " _SSL_SET_INTEGER,
                    "m" _SSL_BELONGS_TO " " _SSL_SET_INTEGER, "gcd(n,m) = 1"};
  thm.conclusion = "√2 ≠ n/m";

  thm.strategy = proof_strategy::contradiction;

  t.add_theorem(thm);
  t.train(1000);
}

// EOF
