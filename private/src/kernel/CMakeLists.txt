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

# Set OCL_INCLUDE_DIR to point at the OCL headers if they are not on the
# default system include path (e.g. -DOCL_INCLUDE_DIR=/path/to/ocl/include).
set(OCL_INCLUDE_DIR "" CACHE PATH "Path to OCL include directory")

add_library(ll-1.m STATIC
  src/tactics/construction_solver.cpp
  src/tactics/contradiction_solver.cpp
  src/solvers/dtt_solver.cpp
  src/tactics/induction_solver.cpp
  src/training/riemannian_trainer+impl.cpp
  src/training/basic_trainer+impl.cpp
  src/solvers/zfc_solver.cpp
)

# ll_model.hpp includes <ocl/...> in its public interface, so OCL_INCLUDE_DIR
# must propagate to consumers of ll_kernel as well.
target_include_directories(ll-1.m PUBLIC
  include
  $<$<BOOL:${OCL_INCLUDE_DIR}>:${OCL_INCLUDE_DIR}>
)

target_compile_definitions(ll-1.m _LL_TRAINER_BASIC)

if (DEFINED _COMMONCORE_USE_OCL)
  target_compile_definitions(ll-1.m _LL_OCL)
endif()

target_compile_options(ll-1.m PRIVATE
  $<$<CXX_COMPILER_ID:Clang,GNU>:-Wall -Wextra -Wpedantic>
)
