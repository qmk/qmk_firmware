// Copyright 2023 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _DEFAULT,
    _LAYER_LOWER,
    _LAYER_UPPER
};

enum keycodes {
    KC_TOGGLE_LOWER_LAYER = SAFE_RANGE,
    KC_TOGGLE_UPPER_LAYER,
    KC_USER_MACRO_1,
    KC_USER_MACRO_2,
    KC_USER_MACRO_3,
    KC_USER_MACRO_4,
    KC_USER_MACRO_5,
    KC_USER_MACRO_6,
    KC_USER_MACRO_7
};

enum rgb_led {
    RGB_CAPSLOCK_LED,
    RGB_LOWER_LAYER_LED,
    RGB_UPPER_LAYER_LED,
    RGB_EXTRA_LED
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_ESC,	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,	KC_BACKSPACE,
        KC_TAB,	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_H,	KC_J,	KC_K,	KC_L,	KC_SEMICOLON,	KC_QUOTE,
        KC_LEFT_SHIFT,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC_N,	KC_M,	KC_COMMA,	KC_DOT,	KC_SLASH,	KC_RIGHT_SHIFT,
        KC_LEFT_CTRL,	KC_LEFT_GUI,	KC_LEFT_ALT,	KC_DELETE,	KC_TOGGLE_LOWER_LAYER,	KC_SPACE,	KC_SPACE,	KC_TOGGLE_UPPER_LAYER,	KC_ENTER,	KC_RIGHT_CTRL,	KC_RIGHT_GUI,	KC_RIGHT_ALT
    ),	
    [_LAYER_LOWER] = LAYOUT(
        KC_USER_MACRO_1,	KC_USER_MACRO_2,	KC_USER_MACRO_3,	KC_USER_MACRO_4,	KC_USER_MACRO_5,	KC_USER_MACRO_6,	KC_USER_MACRO_7,	KC_AUDIO_MUTE,	KC_AUDIO_VOL_DOWN,	KC_AUDIO_VOL_UP,	KC_MEDIA_PLAY_PAUSE,	KC_MEDIA_STOP,
        KC_GRAVE,	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_BACKSLASH,
        KC_TRANSPARENT,	KC_HOME,	KC_PAGE_UP,	KC_PAGE_DOWN,	KC_END,	KC_NO,	KC_NO,	KC_NO,	KC_LEFT_BRACKET,	KC_RIGHT_BRACKET,	KC_UP,	KC_TRANSPARENT,
        KC_TRANSPARENT,	KC_TRANSPARENT,	KC_TRANSPARENT,	KC_CAPS_LOCK,	KC_TRANSPARENT,	KC_MINUS,	KC_EQUAL,	KC_TRANSPARENT,	KC_PRINT_SCREEN,	KC_LEFT,	KC_DOWN,	KC_RIGHT
    ),
    [_LAYER_UPPER] = LAYOUT(
        KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_F5,	KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,	KC_F11,	KC_F12,
        KC_TILDE,	KC_EXCLAIM,	KC_AT,	KC_HASH,	KC_DOLLAR,	KC_PERCENT,	KC_CIRCUMFLEX,	KC_AMPERSAND,	KC_ASTERISK,	KC_LEFT_PAREN,	KC_RIGHT_PAREN,	KC_PIPE,
        KC_TRANSPARENT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_LEFT_CURLY_BRACE,	KC_RIGHT_CURLY_BRACE,	KC_NO,	KC_TRANSPARENT,
        KC_TRANSPARENT,	KC_TRANSPARENT,	KC_TRANSPARENT,	KC_TRANSPARENT,	KC_TRANSPARENT,	KC_UNDERSCORE,	KC_PLUS,	KC_TRANSPARENT,	KC_TRANSPARENT,	KC_TRANSPARENT,	KC_TRANSPARENT,	KC_TRANSPARENT
    )
};

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLACK);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

bool led_update_user(led_t led_state) {
    led_state.caps_lock ? rgblight_setrgb_at(1, 0, 0, RGB_CAPSLOCK_LED) : rgblight_setrgb_at(0, 0, 0, RGB_CAPSLOCK_LED);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _LAYER_LOWER:
            rgblight_setrgb_at(1, 0, 0, RGB_LOWER_LAYER_LED);
            rgblight_setrgb_at(0, 0, 0, RGB_UPPER_LAYER_LED);
            break;
        case _LAYER_UPPER:
            rgblight_setrgb_at(0, 0, 0, RGB_LOWER_LAYER_LED);
            rgblight_setrgb_at(1, 0, 0, RGB_UPPER_LAYER_LED);
            break;
        default: //  for any other layers, or the default layer
            rgblight_setrgb_range(0, 0, 0, RGB_LOWER_LAYER_LED, RGB_EXTRA_LED);
            break;
    }
    return state;
}

void keyboard_pre_init_kb(void) {
    setPinInputHigh(GP3);
    setPinInputHigh(GP2);
    keyboard_pre_init_user();
}

void matrix_scan_kb(void) {
    if (!readPin(GP3)) {
        register_code(KC_MS_BTN1);
    } else {
        unregister_code(KC_MS_BTN1);
    }
    if (!readPin(GP2)) {
        register_code(KC_MS_BTN2);
    } else {
        unregister_code(KC_MS_BTN2);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_layer;

    switch (keycode) {
        // Custom keyboard layer handling
        case KC_TOGGLE_LOWER_LAYER:
            if (record->event.pressed) {
                current_layer = get_highest_layer(layer_state);
                if (current_layer != _LAYER_LOWER) {
                    layer_move(_LAYER_LOWER);
                } else {
                    layer_move(_DEFAULT);
                }
            }
            return false;
        // Custom keyboard layer handling
        case KC_TOGGLE_UPPER_LAYER:
            if (record->event.pressed) {
                current_layer = get_highest_layer(layer_state);
                if (current_layer != _LAYER_UPPER) {
                    layer_move(_LAYER_UPPER);
                } else {
                    layer_move(_DEFAULT);
                }
            }
            return false;
        case KC_USER_MACRO_1:
            // insert code here
            return false;
        case KC_USER_MACRO_2:
            // insert code here
            return false;
        case KC_USER_MACRO_3:
            // insert code here
            return false;
        case KC_USER_MACRO_4:
            // insert code here
            return false;
        case KC_USER_MACRO_5:
            // insert code here
            return false;
        case KC_USER_MACRO_6:
            // insert code here
            return false;
        case KC_USER_MACRO_7:
            // insert code here
            return false;
        // Process other keycodes normally
        default:
            return true;
    }
}
