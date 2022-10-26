// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#ifdef FADER_ENABLE
#    include "fader.h"
#endif
#include "debug_list.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

enum keycodes { 
    DEVICE_INFO = SAFE_RANGE,
    RGB_MATRIX_INDICATOR_ONLY,
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
#define D_INFO   DEVICE_INFO
#define IND_ONLY RGB_MATRIX_INDICATOR_ONLY
#define FAD_REV  FADER_REVERSE
#define FAD_CHI  FADER_CHANNEL_INCREASE
#define FAD_CCI  FADER_CC_INCREASE
#define FAD_TOG  FADER_ENABLE_TOGGLE
#define M_EXP    MACOS_EXPOSE_VIEW
#define M_LPAD   MACOS_LAUNCHPAD
#define M_SEAR   MACOS_SEARCH
#define M_DICT   MACOS_DICTATION
#define M_DND    MACOS_DO_NOT_DISTURB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     __  __  __  __  __  __  __  __  __  __  __  __  __  ______
    |Es||! ||@ ||# ||$ ||% ||^ ||& ||* ||( ||) ||_ ||+ ||Bksp  |
    |__||__||__||__||__||__||__||__||__||__||__||__||__||______|
     ____  __  __  __  __  __  __  __  __  __  __  __  __  ____
    |Tab ||Q ||W ||E ||R ||T ||Y ||U ||I ||O ||P ||{ ||} |||   |
    |____||__||__||__||__||__||__||__||__||__||__||__||__||____|
     _____  __  __  __  __  __  __  __  __  __  __  __  _______
    |Caps ||A ||S ||D ||F ||G ||H ||J ||K ||L ||: ||" ||Enter  |
    |_____||__||__||__||__||__||__||__||__||__||__||__||_______|
     _______  __  __  __  __  __  __  __  __  __  __  _____  __
    |Shift  ||Z ||X ||C ||V ||B ||N ||M ||< ||> ||? ||Shift||↑ |
    |_______||__||__||__||__||__||__||__||__||__||__||_____||__|
     ___  ___  ___  _______________________  ___  ___    __  __  __
    |Ctr||Alt||Win||Space                  ||Win||Fn |  |← ||↓ ||→ |
    |___||___||___||_______________________||___||___|  |__||__||__|
    */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,   KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                KC_RGUI, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
        ),
    [_FN] = LAYOUT(
        _______, KC_BRID, KC_BRIU, M_EXP,   M_SEAR,  M_DICT,  M_DND,   KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______,
        _______, RGB_TOG, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, IND_ONLY, D_INFO,  _______, _______, _______, _______, _______,
        _______, FAD_TOG, FAD_REV, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, NK_TOGG, _______,  _______, _______, _______, _______, KC_PGUP,
        CL_TOGG, GUI_TOG, AG_TOGG,                            _______,                    _______, _______, _______, KC_PGDN, _______
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
        case RGB_MATRIX_INDICATOR_ONLY:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_indicator_only);
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
