#pragma once

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    RGBRST,
    MACRO1,
    MACRO2,
    MACRO3,
    MACRO4,
    MACRO5
};

enum {
    TD_CTRENCADA,
    TD_ACCENT
};

#define PERMISSIVE_HOLD
#define HOLD_SFT_CAPS MT(MOD_LSFT, KC_CAPS)
