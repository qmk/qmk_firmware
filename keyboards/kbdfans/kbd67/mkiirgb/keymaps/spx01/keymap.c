/* Copyright 2022 spx01 (@spx01)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "print.h"

enum CustomKeycodes {
    CK_HEXRGB = SAFE_RANGE,
    /* esc when shift is held, grave otherwise; particularly useful for windows' task manager shortcut */
    CK_ESCG,
};

enum Layers {
    _LAYER1,
    _LAYER2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_LAYER1] = LAYOUT_65_ansi_blocker( 
        QK_GESC,              KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_HOME,
        KC_TAB,               KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,
        LT(_LAYER2, KC_CAPS), KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDN,
        KC_LSFT,              KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,           KC_UP,     KC_END,
        KC_LCTL,              KC_LGUI,  KC_LALT,                KC_SPC,                KC_RALT,           MO(1),    KC_LEFT,           KC_DOWN,   KC_RIGHT),
    [_LAYER2] = LAYOUT_65_ansi_blocker( 
        CK_ESCG,  KC_F1,    KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,  KC_F12,  KC_DEL,   KC_INS,
        KC_TRNS,  KC_TRNS,  KC_TRNS, EE_CLR,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR,   KC_TRNS, KC_TRNS, RESET,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,          KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, CK_HEXRGB, KC_MPLY,          KC_VOLU,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                    RGB_TOG,                   KC_TRNS,          KC_TRNS,   KC_MPRV,          KC_VOLD,  KC_MNXT),
    /* [] = LAYOUT_65_ansi_blocker(
        KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                   KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS), */
    // clang-format on
};

/* exported by the rgb_static effect */
void           RGB_STATIC_save_eeprom(void);
void           RGB_STATIC_reset(void);
extern uint8_t g_rgb_static_color[3];

/* returns number corresponding to hex digit represented by keycode or -1 if keycode isn't a valid hex digit */
static int8_t key_hexdigit(uint16_t keycode) {
    if (keycode >= KC_A && keycode <= KC_F) {
        return keycode - KC_A + 10;
    }
    if (keycode >= KC_1 && keycode <= KC_0) {
        int8_t res = keycode - KC_1 + 1;
        /* mod 10 considering res is between 1 and 10 */
        res *= res != 10;
        return res;
    }
    return -1;
}

typedef struct {
    bool    active;
    uint8_t color[3];
    uint8_t count;
} RGBHexState;
static RGBHexState hexrgb;

/* handles input mode for an rgb value */
static void hexrgb_input(uint16_t keycode) {
    /* only check for special keys when input mode has just been triggered */
    if (hexrgb.count == 0) {
        switch (keycode) {
            case HEXRGB_SAVE_KC:
                RGB_STATIC_save_eeprom();
                hexrgb.active = false;
                return;
            case HEXRGB_RESET_KC:
                RGB_STATIC_reset();
                hexrgb.active = false;
                return;
            default:
        }
    }

    int8_t digit = key_hexdigit(keycode);
    /* exit input mode if an invalid key has been pressed */
    if (digit == -1) {
        hexrgb.count = 0;
        hexrgb.active = false;
        return;
    }

    /* append digit to current color */
    uint8_t idx = hexrgb.count / 2;
    hexrgb.color[idx] <<= 4;
    hexrgb.color[idx] |= digit;

    ++hexrgb.count;
    /* done with input */
    if (hexrgb.count == 6) {
        hexrgb.active = false;
        hexrgb.count  = 0;
        /* copy color to rgb_static's buffer */
        for (int8_t i = 0; i < 3; ++i) {
            g_rgb_static_color[i] = hexrgb.color[i];
            hexrgb.color[i]       = 0;
        }
    }
}

void keyboard_post_init_user(void) {
#if CUSTOM_DEBUG
    debug_enable = true;
    debug_matrix = true;
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* shift status last time ck_escg was pressed so that the correct key can be released */
    static bool ck_escg_last_shifted;

    if (hexrgb.active && record->event.pressed) {
        hexrgb_input(keycode);
        /* while in input mode nothing passes through */
        return false;
    }

    switch (keycode) {
        case CK_HEXRGB:
            hexrgb.active = record->event.pressed;
            return false;
        case CK_ESCG:
            /* if pressed, inject key, otherwise delete it */
            if (record->event.pressed) {
                bool shifted = get_mods() & MOD_BIT(KC_LSHIFT);
                add_key(shifted ? KC_ESC : KC_GRV);
                ck_escg_last_shifted = shifted;
            } else {
                del_key(ck_escg_last_shifted ? KC_ESC : KC_GRV);
            }
            send_keyboard_report();
            return false;
        default:
    }
    return true;
}
