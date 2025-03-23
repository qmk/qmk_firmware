// Copyright 2024 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum custom_keycodes_kb {
    MY_BTN1 = SAFE_RANGE,
    MY_BTN2,
    MY_BTN3,
    MY_SCRL,	// Scroll
    MY_CLKI,	// Click time increase
    MY_CLKD,	// Click time decrease
    MY_SCDV,	// Scroll vertical
    MY_SCDH,	// Scroll horizontal
    MY_JSDI,	// Joy stick movement divisor increase
    MY_JSDD,	// Joy stick movement divisor decrease
    MY_STGE,    // Setting End
    MY_JSKD,    // Joy stick key default
    MY_JSKE,    // Joy stick key enable
};