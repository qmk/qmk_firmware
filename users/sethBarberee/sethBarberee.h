#pragma once

#include QMK_KEYBOARD_H

#include "wrappers.h"

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum userspace_keycodes {
    KC_VRSN = SAFE_RANGE,
    NEW_SAFE_RANGE
};

#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)

#ifdef TAP_DANCE_ENABLE
#   include "tap_dance.h"
#endif

#ifdef RGBLIGHT_ENABLE
#   include "rgb_light.h"
#endif

void keyboard_pre_init_keymap(void);
void keyboard_post_init_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
layer_state_t layer_state_set_keymap (layer_state_t state);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
