// Copyright 2024 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum custom_keycodes_kb {
    MY_BTN1 = SAFE_RANGE,   // User 0
    MY_BTN2,                // User 1
    MY_BTN3,                // User 2
    MY_SCRL,                // User 3 : Scroll
    MY_CLKI,                // User 4 : Click time increase
    MY_CLKD,                // User 5 : Click time decrease
    MY_SCDV,                // User 6 : Scroll vertical
    MY_SCDH,                // User 7 : Scroll horizontal
    MY_JSDI,                // User 8 : Joy stick movement divisor increase
    MY_JSDD,                // User 9 : Joy stick movement divisor decrease
    MY_STGE,                // User 10 : Setting End
    MY_JSKD,                // User 11 : Joy stick key default
    MY_JSKE,                // User 12 : Joy stick key enable
};