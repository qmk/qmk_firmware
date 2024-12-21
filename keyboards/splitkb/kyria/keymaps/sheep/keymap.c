/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include <stdlib.h>
#include "sheep.h"

enum custom_keycodes {
    LENC = SAFE_RANGE,
    RENC,
};

enum layers {
    _BASE = 0,
    _MOVE = 1,
    _NUM = 2,
    _SETTINGS = 3,
};

uint32_t encoder_pressed_timer = 0;

// Aliases for readability
#define CTL_ESC  LCTL_T(KC_ESC)
#define MOVE_TAB LT(_MOVE, KC_TAB)
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: BASE
 *
 * ,-------------------------------------------.                              ,-----------------------------------------.
 * |MOVE/Tab|   B  |   É  |   P  |   O  |   È  |  start/stop recording macro  |   ^  |   V  |   D  |   L  |   J  |   Z  |
 * |--------+------+------+------+------+------|        |                     |------+------+------+------+------+------|
 * |Ctrl/Esc|   A  |   U  |   I  |   E  |   ;  |        v                     |   C  |   T  |   S  |   R  |   N  |   M  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |    Ç   |   À  |   Y  |   X  |   :  |   K  | rec1 | rec2 |  | play2| play1|   ?  |   Q  |   G  |   H  |   F  |   W  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                        | MUTE | SUPER| ALT  | Space| NUM  |  | MOVE | Enter| SHIFT|  ALT |SETTNG|
 *                        |      |      |      |      |(NUM) |  |(MOVE)|      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
     MOVE_TAB, KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                           KC_Y,   KC_U,    KC_I,   KC_O,   KC_P, KC_LBRC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                           KC_H,   KC_J,    KC_K,   KC_L,KC_SCLN, KC_QUOT,
     KC_BSLS , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B ,DM_REC1, DM_REC2,     DM_PLY2  , DM_PLY1,  KC_N,   KC_M, KC_COMM, KC_DOT,KC_SLSH, KC_RBRC,
                                LENC, KC_LGUI, KC_LALT, KC_SPC,TT(_NUM),     TT(_MOVE), KC_ENT,KC_RSFT,KC_RALT, RENC
    ),

/*
 * Navigation Layer: MOVE
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | PrtSc|      |      |                              | PgUp | Home |   ↑  | End  | BkSpc| Insert |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | SUPER|  ALT | SHIFT| CTRL |CAPSLK|                              | PgDn |  ←   |   ↓  |   →  |  Del |  KC_NO | // évite de taper M 
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------| // par erreur
 * |        |      |      |      |      |      |      |      |  |      |      |      | prev | play | next |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MOVE] = LAYOUT(
      _______, _______, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX,                                     KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_BSPC, KC_INS,
      _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_CAPS,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL ,XXXXXXX,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_MRWD, KC_MPLY, KC_MNXT, XXXXXXX,_______,
                                 _______, _______, _______, _______, _______, _______, _______, _______,  KC_APP, _______
    ),

/*
 * Numbers Layer: NUM
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    $   |   "  |  «   |  »   |  (   |  )   |                              |   @  |   +  |  -   |  /   |  *   |   =    |  <--.
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|     |  test inversion
 * |        |      |      |      |      |      |                              |   %  |      |      |      |      |        |  <--'
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  F12   |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  |      |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                        KC_6,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_F12 ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 , _______, _______, _______, _______,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 ,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Settings Layer: SETTINGS
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SETTINGS] = LAYOUT(
      _______, RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN,                                     _______, _______, _______, _______, _______, _______,
      _______, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T,RGB_M_TW,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};


#ifdef RGBLIGHT_ENABLE

//uint8_t base_hue = RGBLIGHT_DEFAULT_HUE;
//uint8_t base_sat = RGBLIGHT_DEFAULT_SAT;
//uint8_t base_val = RGBLIGHT_DEFAULT_VAL; défini dans sheep.c
static uint8_t current_mode = 1; // gradient 7

void rgblight_sethsv_master_slave(uint8_t hue, uint8_t sat, uint8_t val) {
    rgblight_sethsv_noeeprom(hue, sat, val);
    //rgblight_sethsv_range(hue, sat, val, 0, 9);
    //rgblight_sethsv_range(hue + RGBLIGHT_SLAVE_HUE_OFFSET, sat, val, 10, 19);
}

void keyboard_post_init_user(void) {
    //rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_mode_noeeprom(current_mode);
    rgblight_sethsv_master_slave(base_hue, base_sat, base_val);
    //rgblight_sethsv_range(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL, 0, 9);
    //rgblight_sethsv_range(RGBLIGHT_DEFAULT_HUE + RGBLIGHT_SLAVE_HUE_OFFSET, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL, 10, 19);
}

uint32_t layer_state_set_user(uint32_t state) {
    // TODO : use #define RGBLIGHT_LAYERS
    uint8_t hue;
    uint8_t sat;

	switch(get_highest_layer(state)) {
        case _MOVE:
            hue = 232;
            sat = base_sat;
            break;
        case _NUM:
            hue = 96;
            sat = base_sat;
            //sat = base_sat;
            break;
        default:
            hue = base_hue;
            sat = base_sat;
            //sat = base_sat;
            break;
    };

    rgblight_sethsv_master_slave(hue, sat, base_val);

	return state;
};
#endif //RGBLIGHT_ENABLE

#ifdef ENCODER_ENABLE
void left_encoder_cw(void) {
    switch (encoder_mode) {
        case _RGB:
            base_hue -= RGBLIGHT_HUE_STEP;
            rgblight_sethsv_master_slave(base_hue, base_sat, base_val);
            break;
        case _MOUSE:
            tap_code(KC_MS_WH_RIGHT);
            break;
        case _MUSIC:
            tap_code(KC_VOLD);
            break;
        //case _PAGE:
        //    tap_code16(RCTL(KC_TAB));
        //    break;
        default:
            tap_code(KC_VOLD);
    }
}

void left_encoder_acw(void) {
    switch (encoder_mode) {
        case _RGB:
            base_hue += RGBLIGHT_HUE_STEP;
            rgblight_sethsv_master_slave(base_hue, base_sat, base_val);
            break;
        case _MOUSE:
            tap_code(KC_MS_WH_LEFT);
            break;
        case _MUSIC:
            tap_code(KC_VOLU);
            break;
        //case _PAGE:
        //    tap_code16(RCS(KC_TAB));
        //    break;
        default:
            tap_code(KC_VOLU);
    }
}

void right_encoder_cw(void) {
    switch (encoder_mode) {
        case _RGB:
            base_val -= RGBLIGHT_VAL_STEP;
            if (base_val > RGBLIGHT_LIMIT_VAL) { //underflow
                base_val = 0;
            }
            rgblight_sethsv_master_slave(base_hue, base_sat, base_val);
            break;
        case _MOUSE:
            tap_code(KC_MS_WH_UP);
            break;
        case _PAGE:
            tap_code(KC_PGUP);
            //tap_code16(LSA(KC_TAB));
            break;
        case _MUSIC:
            tap_code(KC_MEDIA_PREV_TRACK);
            break;
        default:
            tap_code(KC_PGUP);
    }
}

void right_encoder_acw(void) {
    switch (encoder_mode) {
        case _RGB:
            base_val += RGBLIGHT_VAL_STEP;
            if (base_val > RGBLIGHT_LIMIT_VAL) { //overflow
                base_val = RGBLIGHT_LIMIT_VAL;
            } 
            rgblight_sethsv_master_slave(base_hue, base_sat, base_val);
            break;
        case _MOUSE:
            tap_code(KC_MS_WH_DOWN);
            break;
        case _PAGE:
            tap_code(KC_PGDN);
            //tap_code16(LALT(KC_TAB));
            break;
        case _MUSIC:
            tap_code(KC_MEDIA_NEXT_TRACK);
            break;
        default:
            tap_code(KC_PGDN);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume or hue control
        if (clockwise) {
            left_encoder_cw();
        } else {
            left_encoder_acw();
        }
    } else if (index == 1) {
        // Page up/Page down or RGB Brightness
        if (clockwise) {
            right_encoder_cw();
        } else {
            right_encoder_acw();
        }
    }
    return false;
}

void left_encoder_pressed(bool pressed) {
    switch (encoder_mode) {
        case _MUSIC:
            if (pressed) {
                tap_code(KC_MEDIA_PLAY_PAUSE);
            }
            break;
        case _RGB:
            if (pressed) {
                rgblight_toggle_noeeprom();
            }
            break;
        default:
            if (pressed) {
                tap_code(KC_MUTE);
            }
    }
}

void right_encoder_pressed(bool pressed) {
    if (pressed) {
        encoder_pressed_timer = sync_timer_read32();
    } else {
        if (sync_timer_elapsed32(encoder_pressed_timer) > (200 + TAPPING_TERM)) {
            layer_invert(_SETTINGS);
            if (encoder_mode == _RGB) {
                encoder_mode = _PAGE; 
            } else {
                encoder_mode = _RGB;
            }
        } else {
            if (IS_LAYER_ON(_SETTINGS)) {
                layer_off(_SETTINGS);
            }
            encoder_mode = (encoder_mode + 1) % 3; 
        }
        encoder_pressed_timer = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RENC:
            right_encoder_pressed(record->event.pressed);
            break;
        case LENC:
            left_encoder_pressed(record->event.pressed);
            break;
    }
    return true;
}
#endif // ENCODER_ENABLE