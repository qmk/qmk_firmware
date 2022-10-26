// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#ifdef FADER_ENABLE
#    include "fader.h"
#endif
#ifdef RGB_INDICATOR_ENABLE
#    include "rgb_indicator.h"
#endif
#include "debug_list.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

enum keycodes {
    DEVICE_INFO = SAFE_RANGE,
    RGB_INDICATOR_HUE_INCREASE,
    RGB_INDICATOR_SATURATION_INCREASE,
    RGB_INDICATOR_VAL_INCREASE,
    RGB_INDICATOR_MODE,
    RGB_INDICATOR_SELECT,
    RGB_INDICATOR_ENABLE_TOGGLE,
    FADER_REVERSE,
    FADER_CHANNEL_INCREASE,
    FADER_CC_INCREASE,
    FADER_ENABLE_TOGGLE,
    MACOS_EXPOSE_VIEW,
    MACOS_LAUNCHPAD,
    MACOS_SEARCH,
    MACOS_DICTATION,
    MACOS_DO_NOT_DISTURB,
};

// Keycodes aliases
#define D_INFO  DEVICE_INFO
#define IND_HUI RGB_INDICATOR_HUE_INCREASE
#define IND_SAI RGB_INDICATOR_SATURATION_INCREASE
#define IND_VAI RGB_INDICATOR_VAL_INCREASE
#define IND_MOD RGB_INDICATOR_MODE
#define IND_SEL RGB_INDICATOR_SELECT
#define IND_TOG RGB_INDICATOR_ENABLE_TOGGLE
#define FAD_REV FADER_REVERSE
#define FAD_CHI FADER_CHANNEL_INCREASE
#define FAD_CCI FADER_CC_INCREASE
#define FAD_TOG FADER_ENABLE_TOGGLE
#define M_EXP   MACOS_EXPOSE_VIEW
#define M_LPAD  MACOS_LAUNCHPAD
#define M_SEAR  MACOS_SEARCH
#define M_DICT  MACOS_DICTATION
#define M_DND   MACOS_DO_NOT_DISTURB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     __  __  __  __  __  __  __  __  __  __  __  __  __  __  __
    |Es||! ||@ ||# ||$ ||% ||^ ||& ||* ||( ||) ||_ ||+ ||~ ||Bk|
    |__||__||__||__||__||__||__||__||__||__||__||__||__||__||__|
     ____  __  __  __  __  __  __  __  __  __  __  __  __  ____
    |Tab ||Q ||W ||E ||R ||T ||Y ||U ||I ||O ||P ||{ ||} |||   |
    |____||__||__||__||__||__||__||__||__||__||__||__||__||____|
     _____  __  __  __  __  __  __  __  __  __  __  __  __  ___
    |Caps ||A ||S ||D ||F ||G ||H ||J ||K ||L ||: ||" ||~ ||Ent|
    |_____||__||__||__||__||__||__||__||__||__||__||__||__||___|
     ___  __  __  __  __  __  __  __  __  __  __  __  _____  __
    |Shi||| ||Z ||X ||C ||V ||B ||N ||M ||< ||> ||? ||Shift||↑ |
    |___||__||__||__||__||__||__||__||__||__||__||__||_____||__|
     ___  ___  ___  _______________________  ___  ___    __  __  __
    |Ctr||Alt||Win||Space                  ||Win||Fn |  |← ||↓ ||→ |
    |___||___||___||_______________________||___||___|  |__||__||__|
    */
    [_BASE] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X, KC_C, KC_V,   KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                     KC_SPC,                    KC_LGUI, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
        ),
    [_FN] = LAYOUT_all(
        _______, KC_BRID, KC_BRIU, M_EXP,   M_SEAR,  M_DICT,  M_DND,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        _______, IND_TOG, IND_MOD, IND_SEL, IND_HUI, IND_SAI, IND_VAI, _______, D_INFO,  _______, _______, _______, _______, _______,
        _______, FAD_TOG, FAD_REV, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______, KC_PGUP,
        CL_TOGG, GUI_TOG, AG_TOGG,                            _______,                            _______, _______, _______, KC_PGDN, _______
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEVICE_INFO:
            if (record->event.pressed) {
                debug_custom();
            } else {
            }
            return false;
        case RGB_INDICATOR_HUE_INCREASE:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    rgb_indicator_decrease_hue();
                } else {
                    rgb_indicator_increase_hue();
                }
            } else {
            }
            return false;
        case RGB_INDICATOR_SATURATION_INCREASE:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    rgb_indicator_decrease_sat();
                } else {
                    rgb_indicator_increase_sat();
                }
            } else {
            }
            return false;
        case RGB_INDICATOR_VAL_INCREASE:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    rgb_indicator_decrease_val();
                } else {
                    rgb_indicator_increase_val();
                }
            } else {
            }
            return false;
        case RGB_INDICATOR_MODE:
            if (record->event.pressed) {
                rgb_indicator_step();
            } else {
            }
            return false;
        case RGB_INDICATOR_SELECT:
            if (record->event.pressed) {
                rgb_indicator_select_toggle();
            } else {
            }
            return false;
        case RGB_INDICATOR_ENABLE_TOGGLE:
            if (record->event.pressed) {
                rgb_indicator_enable_toggle();
            } else {
            }
            return false;
        case FADER_REVERSE:
            if (record->event.pressed) {
                fader_reverse();
            } else {
            }
            return false;
        case FADER_CHANNEL_INCREASE:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    fader_decrease_channel();
                } else {
                    fader_increase_channel();
                }
            } else {
            }
            return false;
        case FADER_CC_INCREASE:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    fader_decrease_cc();
                } else {
                    fader_increase_cc();
                }
            } else {
            }
            return false;
        case FADER_ENABLE_TOGGLE:
            if (record->event.pressed) {
                fader_enable_toggle();
            } else {
            }
            return false;
        case MACOS_EXPOSE_VIEW:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MACOS_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MACOS_SEARCH:
            if (record->event.pressed) {
                host_consumer_send(0x221);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MACOS_DICTATION:
            if (record->event.pressed) {
                host_consumer_send(0xCF);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MACOS_DO_NOT_DISTURB:
            if (record->event.pressed) {
                host_system_send(0x9B);
            } else {
                host_system_send(0);
            }
        default:
            return true; // Process all other keycodes normally
    }
}