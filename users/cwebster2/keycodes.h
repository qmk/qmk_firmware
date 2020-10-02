#pragma once

#include QMK_KEYBOARD_H

enum userspace_custom_keycodes {
    KC_LCCL = SAFE_RANGE,
    NEW_SAFE_RANGE
};

#define KC_CTLBS CTL_T(KC_BSPC)
#define KC_ALTCL LALT_T(KC_CAPS)
