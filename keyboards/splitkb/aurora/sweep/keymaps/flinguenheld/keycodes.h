// Copyright 2023 Florent Linguenheld (@FLinguenheld)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum layers {
    _BASE,
    _NUMERIC,
    _ARROWS,
    _MOUSE,
    _ADJUST,
    _FN,
    _LEFT_HAND,
};

enum custom_keys {
    UNICODE = SAFE_RANGE, // Shortcut to write unicodes, see numeric layer

    /* See auto-shift */
    CS_E_ACUTE,

    CS_A_GRAVE,
    CS_E_GRAVE,
    CS_I_GRAVE,
    CS_O_GRAVE,
    CS_U_GRAVE,

    CS_C_CEDILLA,
    CS_AE,
    CS_OE,

    CS_A_CIRCUMFLEX,
    CS_E_CIRCUMFLEX,
    CS_I_CIRCUMFLEX,
    CS_O_CIRCUMFLEX,
    CS_U_CIRCUMFLEX,

    CS_A_DIAERESIS,
    CS_E_DIAERESIS,
    CS_I_DIAERESIS,
    CS_O_DIAERESIS,
    CS_U_DIAERESIS,
    CS_Y_DIAERESIS,
};
