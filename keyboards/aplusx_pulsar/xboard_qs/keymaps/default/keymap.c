/* Copyright 2024 Aplusx Inc.
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

enum _layer { WIN_BASE = 0, WIN_FN, MAC_BASE, MAC_FN };

enum pulsar_keycodes {
KC_TGUI = SAFE_RANGE,   // Toggle between GUI Lock or Unlock
NEW_SAFE_RANGE
};

#define KC_TASK LGUI(KC_TAB)
#define KC_DIC  LGUI(KC_H)      // WIN ; 받아쓰기
#define KC_LOCK2 LGUI(KC_L)     // WIN ; pc잠금

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     [WIN_BASE] = LAYOUT( /* Layer 0 ; WIN Base Layer */
                                                                                                                        KC_VOLD, KC_VOLU, KC_MUTE,
        KC_ESC,    KC_F1, KC_F2, KC_F3, KC_F4,      KC_F5,  KC_F6,  KC_F7,  KC_F8,    KC_F9, KC_F10, KC_F11, KC_F12,  KC_F13, KC_PSCR, KC_SCRL,KC_PAUS,
        KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,   KC_0,   KC_MINS,   KC_EQL,  KC_BSPC,           KC_INS, KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,   KC_P,   KC_LBRC,   KC_RBRC, KC_BSLS,           KC_DEL, KC_END,  KC_PGDN,
        KC_CAPS, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,   KC_SCLN, KC_QUOT,            KC_ENT,
        KC_LSFT,        KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,           KC_RSFT,                    KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                 KC_SPC,        KC_RALT,  MO(WIN_FN),  KC_APP,  KC_RCTL,                     KC_LEFT, KC_DOWN, KC_RGHT),

     [WIN_FN] = LAYOUT( /* Layer 1 ; WIN Function Layer */
                                                                                                                                        _______, _______, _______,
        _______,    KC_BRID, KC_BRIU, KC_TASK, KC_WSCH, KC_DIC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,       _______, KC_CALC, KC_WHOM,KC_LOCK2,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  NK_OFF,  NK_ON,  RGB_TOG,          RGB_SAI, RGB_HUI, RGB_MOD,
        _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_SAD, RGB_HUD, RGB_RMOD,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______,      KC_BTN4, KC_BTN3, KC_BTN5, _______, _______, _______, _______,  _______, _______, _______,            _______,                   RGB_VAI,
        _______, KC_TGUI, _______,                             _______,                            _______,_______, _______, _______,          RGB_SPD, RGB_VAD, RGB_SPI),

    [MAC_BASE] = LAYOUT( /* Layer 2 ; MAC Base Layer */
                                                                                                                                KC_VOLD, KC_VOLU, KC_MUTE,
        KC_ESC,  KC_BRID, KC_BRIU, KC_TASK,  KC_WSCH, KC_DIC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,KC_VOLD,KC_VOLU, _______, _______,_______,_______,
        KC_GRV,  KC_1,  KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,           KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSLS,           KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,  KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,          KC_RSFT,                     KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                       KC_RGUI,  MO(MAC_FN), KC_RALT, KC_RCTL,           KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN]   = LAYOUT(/* Layer 3 ; MAC Function Layer */
                                                                                                                                _______, _______, _______,
        _______,      KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_F13, KC_F14, KC_F15,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, NK_OFF,   NK_ON,  RGB_TOG,          RGB_SAI, RGB_HUI, RGB_MOD,
        _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_SAD, RGB_HUD, RGB_RMOD,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,         KC_BTN4, KC_BTN3, KC_BTN5, _______, _______, _______, _______, _______, _______, _______,          _______,                   RGB_VAI,
        _______, _______, _______,                         _______,                               _______, _______, _______, _______,          RGB_SPD, RGB_VAD, RGB_SPI)
        };
//-----------------------------------------------------------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif // ENCODER_MAP_ENABLE

static bool win_key_locked = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case KC_TGUI:
            if (record->event.pressed) {                // Toggle GUI lock on key press
                win_key_locked = !win_key_locked;
            }
            break;

        case KC_LGUI:
            if (win_key_locked) { return false; }
            else{ return true;}

        default:
            return true;   // Process all other keycodes normally
    }
    return true;
}

//-----------------------------------------------------------------------------

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void)  {

    led_t host_leds = host_keyboard_led_state();

    if (host_leds.caps_lock) {
        rgb_matrix_set_color(72, 50, 50, 50);
    }
    if (host_leds.scroll_lock) {
        rgb_matrix_set_color(22, 50, 50, 50);
    }

    if (win_key_locked){                // WIN key Lock
                rgb_matrix_set_color(99, 50, 50, 50);
    }
    return TRUE;
}
#endif
