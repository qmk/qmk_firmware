// Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>,
// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "vitoni.h"

enum layer_names {
    _BASE,
    _MOV,
    _RGB
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]                          PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "        #        Enter             PgDn
//      Sh_L     /        Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press CAPS+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        MO(_MOV), KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, TG(_RGB),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_MOV] = LAYOUT(
        RESET,   KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, KC_PGUP, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [_RGB] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   RGB_RMOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,          RGB_SPI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_SAI, RGB_SPD,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_HUD, RGB_SAD, RGB_HUI
    ),

};
// clang-format on

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _MOV:
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
            break;
#if defined(RGB_MATRIX_ENABLE)
        case _RGB:
            if (clockwise) {
                rgb_matrix_increase_val_noeeprom();
            } else {
                rgb_matrix_decrease_val_noeeprom();
            }
            break;
#endif // RGB_MATRIX_ENABLE
        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
    return true;
}
#endif // ENCODER_ENABLE

#if defined(RGB_MATRIX_ENABLE)
/*
* Set up default RGB color.
*/
void rgb_matrix_set_default_color(void) {
    rgb_matrix_sethsv_noeeprom_user(HSV_CHARTREUSE);
}

/*
* Set up RGB defaults.
*/
void rgb_matrix_configure_default_settings(void) {
    rgb_matrix_set_default_color();
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_configure_default_settings();
}

/*
* Use RGB underglow to indicate specific layers.
*/
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _MOV:
            rgb_matrix_sethsv_noeeprom_user(HSV_SPRINGGREEN);
            break;
        case _RGB:
            rgb_matrix_sethsv_noeeprom_user(HSV_GREEN);
            break;
        default: // for any other layer
            rgb_matrix_set_default_color();
            break;
    }
    return state;
}

void matrix_scan_user(void) {
    matrix_scan_user_rgb();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user_rgb(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case RESET:  // when activating RESET mode for flashing
            if (record->event.pressed) {
                rgb_matrix_set_color_all(63, 0, 0);
                rgb_matrix_driver.flush();
            }
            return true;
    }
    return true; // Process all other keycodes normally
}
#endif // RGB_MATRIX_ENABLE
