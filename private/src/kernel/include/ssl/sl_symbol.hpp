// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app.

/// (C) Amlal El Mahrouss

#pragma once

#ifdef _LL_OCL
#include <ocl/scientific_fwd.hpp>
#include <ocl/math_fwd.hpp>
#endif

#ifndef _SSL
#define _SSL (0x091026)
#endif

#define _SSL_ZFC_NOT "¬"
#define _SSL_ZFC_NULL "∅"
#define _SSL_SET_INTEGER "ℤ"
#define _SSL_BELONGS_TO "∈"
#define _SSL_NE "≠"
#define _SSL_EQ "="
#define _SSL_SQR "√"
#define _SSL_SQRT "√"

#define _SSL_HIGH_CONF 1.0
#define _SSL_LOW_CONF .0
#define _SSL_X_CONF(X) 0.##X
