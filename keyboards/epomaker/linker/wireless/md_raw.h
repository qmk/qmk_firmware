// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RENAME_WITH_LINE(A, B) COMBINE(A, B)
#define COMBINE(A, B) A##B
#define raw_hid_send(a, b) RENAME_WITH_LINE(_temp_rhs_, __LINE__)(a, b)
#define _temp_rhs_29 replaced_hid_send  // raw_hid.h
#define _temp_rhs_461 replaced_hid_send // via.c
#define _temp_rhs_465 replaced_hid_send // via.c (current location)
#define _temp_rhs_472 replaced_hid_send // via.c (new line number after PR #25255)
#define _temp_rhs_609 replaced_hid_send // via.c (updated location)
#define _temp_rhs_610 replaced_hid_send // via.c (new location)
#define _temp_rhs_618 replaced_hid_send // via.c (newest location)
