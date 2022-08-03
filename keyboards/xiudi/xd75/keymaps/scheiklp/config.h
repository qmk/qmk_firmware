// Copyright 2021 Paul Maria Scheikl (@ScheiklP)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// place overrides here
#define AUTO_SHIFT_TIMEOUT 175
#define NO_AUTO_SHIFT_SPECIAL

// Mouse control
// constant mode (velocity)
#define MK_3_SPEED
// KC_ACL0 < KC_ACL1 < unmodified < KC_ACL2
// Cursor offset per movement (unmodified)
#define MK_C_OFFSET_UNMOD 16
// Time between cursor movements (unmodified)
#define MK_C_INTERVAL_UNMOD 16
// Cursor offset per movement (KC_ACL0)
#define MK_C_OFFSET_0 1
// Time between cursor movements (KC_ACL0)
#define MK_C_INTERVAL_0 32
// Cursor offset per movement (KC_ACL1)
#define MK_C_OFFSET_1 4
// Time between cursor movements (KC_ACL1)
#define MK_C_INTERVAL_1 16
// Cursor offset per movement (KC_ACL2)
#define MK_C_OFFSET_2 32
// Time between cursor movements (KC_ACL2)
#define MK_C_INTERVAL_2 16
