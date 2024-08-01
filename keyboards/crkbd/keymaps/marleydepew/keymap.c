/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "../../macro.h"

enum layer_names {
    _COLEMAK_DH,
    _NUMBER,
    _SYMBOL,
    _FUNCTION,
    _NAVIGATION,
    _MACRO,
    _RGB
};

enum custom_keycodes {
    MACRO_0 = SAFE_RANGE,
    MACRO_1,
    MACRO_2,
    MACRO_TM,
    MACRO_TH,
    MACRO_WM,
    MACRO_WL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK_DH] = LAYOUT_split_3x6_3(                                                        // Colemak DH Layer
    // |---------------+---------------+---------------+---------------+---------------+---------------|   |---------------+---------------+---------------+---------------+---------------+---------------|
        XXXXXXX,        KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,               KC_J,           KC_L,           KC_U,           KC_Y,           XXXXXXX,        XXXXXXX,
    // |---------------+---------------+---------------+---------------+---------------+---------------|   |---------------+---------------+---------------+---------------+---------------+---------------|
        KC_CAPS,        LGUI_T(KC_A),   LALT_T(KC_R),   LSFT_T(KC_S),   LCTL_T(KC_T),   KC_G,               KC_M,           LCTL_T(KC_N),   LSFT_T(KC_E),   LALT_T(KC_I),   LGUI_T(KC_O),   KC_QUOT,
    // |---------------+---------------+---------------+---------------+---------------+---------------|   |---------------+---------------+---------------+---------------+---------------+---------------|
        KC_ESC,         KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,               KC_K,           KC_H,           KC_COMM,        KC_DOT,         KC_SLSH,        QK_LEAD,
    // |---------------+---------------+---------------+---------------+---------------+---------------|   |---------------+---------------+---------------+---------------+---------------+---------------|
                                                        LT(3,KC_TAB),   LT(1,KC_BSPC),  LT(2,KC_DEL),       LT(5,KC_ENT),   LT(4,KC_SPC),   LT(6,KC_PSCR) 
    //                                                 |---------------+---------------+---------------|   |---------------+---------------+---------------|
    ),

    [_NUMBER] = LAYOUT_split_3x6_3(                                      // Number Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_1,       KC_2,       KC_3,       XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        KC_MINS,    KC_4,       KC_5,       KC_6,       KC_COLN,    KC_GRV,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_UNDS,    KC_7,       KC_8,       KC_9,       KC_SLSH,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_LPRN,    KC_0,       KC_RPRN
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
    ),

    [_SYMBOL] = LAYOUT_split_3x6_3(                                      // Symbols Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_EXLM,    KC_AT,      KC_HASH,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        KC_PLUS,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_SCLN,    KC_TILD,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_EQL,     KC_AMPR,    KC_ASTR,    KC_DOT,     KC_BSLS,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_LBRC,    XXXXXXX,    KC_RBRC
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_FUNCTION] = LAYOUT_split_3x6_3(                                   // Function Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_F1,      KC_F2,      KC_F3,      XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        XXXXXXX,    KC_F4,      KC_F5,      KC_F6,      KC_APP,     KC_PIPE,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_F7,      KC_F8,      KC_F9,      KC_PAUS,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_F11,     KC_F10,     KC_F12
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_NAVIGATION] = LAYOUT_split_3x6_3(                                // Navigation Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_WH_L,    KC_WH_U,    KC_WH_D,    KC_WH_R,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LEFT,    KC_UP,      KC_DOWN,    KC_RGHT,    XXXXXXX,          XXXXXXX,    KC_RCTL,    KC_RSFT,    KC_RALT,    KC_RGUI,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_HOME,    KC_PGUP,    KC_PGDN,    KC_END,     XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            KC_ACL0,    KC_ACL1,    KC_ACL2,        XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_MACRO] = LAYOUT_split_3x6_3(                                        // Macro Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_1,    DM_REC2,    DM_REC1,    MACRO_TH,   MACRO_WL,   XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_2,    DM_PLY2,    DM_PLY1,    MACRO_TM,   MACRO_WM,   LSFT(KC_F3),    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Y),     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_RGB] = LAYOUT_split_3x6_3(                                           // RGB Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    DT_PRNT,    DT_UP,      DT_DOWN,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        RGB_TOG,    RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        RGB_M_P,    RGB_RMOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  )
};

// The next section is only applicable if OLEDs are enabled.
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {

    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_0;
    }
}

void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM marley_katakana[] = {
        // https://javl.github.io/image2cpp/
        // Code Output: Plain Bytes; Draw Mode: Vertical; Rotate Image: 0 degrees
        // 'marley katakana_rotated.jpg'; 128x32px 
        // (source image was rotated 90 degrees to lay horizontally
        // with the bottom of the image on the left and the top of the image on the right)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
        0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0e, 0x0f, 0x0f, 0x1f, 
        0x1f, 0x1f, 0x3f, 0x3f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x03, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0x80, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 
        0x38, 0x00, 0x00, 0x01, 0x0f, 0x3f, 0xff, 0xff, 0xf1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0e, 0x1c, 0x3c, 0x78, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf4, 0xfc, 0x78, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 
        0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x7c, 0x7e, 0x3f, 0x3f, 0x1f, 0x07, 0x0f, 
        0x3e, 0x7c, 0xf8, 0xf0, 0xe0, 0xe0, 0xc1, 0xcf, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // clang-format on
    oled_write_raw_P(marley_katakana, sizeof(marley_katakana));
}

void oled_render_status(void) {

    /* layer */
    oled_set_cursor(0, 0);
    oled_write("LAYER", false);

    oled_set_cursor(0, 2);
    switch (get_highest_layer(layer_state)) {

        case _COLEMAK_DH:
            oled_write("COLMK", false);
            break;

        case _NUMBER:
            oled_write("NUMBR", false);
            break;

        case _SYMBOL:
            oled_write("SYMBL ", false);
            break;

        case _FUNCTION:
            oled_write("FNCTN", false);
            break;

        case _NAVIGATION:
            oled_write("NVGTN", false);
            break;

        case _MACRO:
            oled_write("MACRO", false);
            break;

        case _RGB:
            oled_write("RGBLT", false);
            break;

    default:
            oled_write("UNDEF", false);

    }

    led_t led_usb_state = host_keyboard_led_state();

    //print num lock status
    oled_set_cursor(0, 8);
    if(led_usb_state.num_lock) {
        oled_write("NUMLK", true);
    } else {
        oled_write("     ", false);
    }
    
    //print scroll lock status
    oled_set_cursor(0, 10);
    if (led_usb_state.scroll_lock) {
        oled_write("SCRLK", true);
    } else {
        oled_write("     ", false);
    }

    //print caps lock status
    oled_set_cursor(0, 12);
    if (led_usb_state.caps_lock) {
        oled_write("CPSLK", true);
    } else {
        oled_write("     ", false);
    }

}

bool oled_task_user(void) {
    
    if (is_keyboard_master()) {
        oled_render_status();
    } else {
        oled_render_logo();
    }

    return false;
}

#endif // End OLED Section

// These are my custom overrides for the shift keys
#ifdef KEY_OVERRIDE_ENABLE

// Shift + ( = < on the number layer
const key_override_t left_parenth_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LPRN, KC_LABK, 1 << _NUMBER);
// Shift + ) = > on the number layer
const key_override_t right_parenth_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RPRN, KC_RABK, 1 << _NUMBER);
// Shift + 9 = . on the number layer
const key_override_t nine_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_9, KC_DOT, 1 << _NUMBER);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &left_parenth_override,
    &right_parenth_override,
    &nine_override,
    NULL // Null terminate the array of overrides!
};

#endif // End Key Override Section

// This gets called for each key.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // This is for the macro
    switch (keycode) {
        
        case MACRO_0:
            if (record->event.pressed) {
                // when keycode MACRO_0 is pressed
                SEND_STRING(M0_STRING);
            } else {
                // when keycode MACRO_0 is released
            }
            break;

        case MACRO_1:
            if (record->event.pressed) {
                // when keycode MACRO_1 is pressed
                SEND_STRING(M1_STRING);
            } else {
                // when keycode MACRO_1 is released
            }
            break;

        case MACRO_2:
            if (record->event.pressed) {
                // when keycode MACRO_2 is pressed
                SEND_STRING(M2_STRING);
            } else {
                // when keycode MACRO_2 is released
            }
            break;

        case MACRO_TM:
            if (record->event.pressed) {
                // when keycode MS Teams Mute is pressed
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) "m" SS_UP(X_LSFT) SS_UP(X_LCTL));
            } else {
                // when keycode MACRO_1 is released
            }
            break;

        case MACRO_TH:
            if (record->event.pressed) {
                // when keycode MS Teams Hangup is pressed
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) "h" SS_UP(X_LSFT) SS_UP(X_LCTL));
            } else {
                // when keycode MACRO_2 is released
            }
            break;

        case MACRO_WM:
            if (record->event.pressed) {
                // when keycode WebEx Mute is pressed
                SEND_STRING(SS_LCTL("m"));
            } else {
                // when keycode MACRO_1 is released
            }
            break;

        case MACRO_WL:
            if (record->event.pressed) {
                // when keycode WebEx Leave is pressed
                SEND_STRING(SS_LCTL("l"));
            } else {
                // when keycode MACRO_2 is released
            }
            break;

    }

    return true;
}
