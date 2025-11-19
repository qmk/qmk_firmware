// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Older code tried to rename the helper using __LINE__ which is brittle
// and can lead to implicit-declaration errors when line numbers change.
// Provide a stable alias instead.
#undef raw_hid_send
#define raw_hid_send(a, b) replaced_hid_send(a, b)

// Historical mappings (left as comments for reference):
// _temp_rhs_29 replaced_hid_send  // raw_hid.h
// _temp_rhs_461 replaced_hid_send // via.c
// _temp_rhs_465 replaced_hid_send // via.c (current location)
// _temp_rhs_472 replaced_hid_send // via.c (new line number after PR #25255)
// _temp_rhs_609 replaced_hid_send // via.c (updated location)
// _temp_rhs_610 replaced_hid_send // via.c (new location)
// _temp_rhs_618 replaced_hid_send // via.c (newest location)
