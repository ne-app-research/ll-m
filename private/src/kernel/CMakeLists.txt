# SPDX-License-Identifier: Apache-2.0
# Copyright 2026, Amlal El Mahrouss and Ne.app.

cmake_minimum_required(VERSION 3.20)

project(LL_M
  VERSION 1.0.5
  LANGUAGES CXX
  DESCRIPTION "LL-M formal reasoning ML model"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ll-1.m STATIC
  src/tactics/construction_solver.cpp
  src/tactics/contradiction_solver.cpp
  src/solvers/dtt_solver_validate.cpp
  src/tactics/induction_solver.cpp
  src/training/riemannian_trainer+impl.cpp
  src/training/std_trainer+impl.cpp
  src/solvers/zfc_solver_validate.cpp
)

target_include_directories(ll-1.m PUBLIC
  include
)

target_compile_definitions(ll-1.m PUBLIC _LL_TRAINER_STD)

if (DEFINED _COMMONCORE_USE_OCL)
  target_compile_definitions(ll-1.m _LL_OCL)
endif()

target_compile_options(ll-1.m PRIVATE
  $<$<CXX_COMPILER_ID:Clang,GNU>:-Wall -Wextra -Wpedantic>
)

## EOF
