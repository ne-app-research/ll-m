# SPDX-License-Identifier: Apache-2.0
# Copyright 2026, Ne.app.

message(STATUS "=> CommonCore: Building LL-M...")

execute_process(
    COMMAND cmake -B build-cc
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../private/src/kernel"
)

execute_process(
    COMMAND cmake --build build-cc
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../private/src/kernel"
)

execute_process(
    COMMAND cmake -B build-cc
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../private/src/tests"
)

execute_process(
    COMMAND cmake --build build-cc
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../private/src/tests"
)
