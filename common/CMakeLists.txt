# SPDX-License-Identifier: Apache-2.0
# Copyright 2026, Ne.app.

cmake_minimum_required(VERSION 3.30)

project(nebld-cc VERSION 0.1 LANGUAGES CXX)

option(_LLM_COMMONCORE_BUILD "=> Produces a CommonCore build of LL-M")

message(STATUS "=> CommonCore? ${_LLM_COMMONCORE_BUILD}")

if (_LLM_COMMONCORE_BUILD STREQUAL "ON")
    include(commoncore_build.cmake)
endif()
