/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_SYMB,
    WIN_FN
};


// Macros
enum custom_keycodes{
    MS_JGL = SAFE_RANGE,  // Jiggle the mouse
};

// Tap Dance configuration
enum {
    TD_STC_END,
};

void td_sentence_end(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        SEND_STRING("> ");
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    } else {
        SEND_STRING(".");
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_STC_END] = ACTION_TAP_DANCE_FN(td_sentence_end),
};

bool mouse_jiggle_mode = false;

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Layers 0 and 1 are left unchanged in case I need to connect this keyboard to a Mac
     */
    [MAC_BASE] = LAYOUT_ansi_89(
        KC_MUTE,  KC_ESC,   KC_BRID,  KC_BRIU,  KC_NO,    KC_NO,    RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,          KC_VOLU,  KC_INS,             KC_DEL,
        _______,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,          KC_EQL,   KC_BSPC,            KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,          KC_RBRC,  KC_BSLS,            KC_PGDN,
        _______,  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                    KC_ENT,             KC_HOME,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  TD(TD_STC_END),   KC_SLSH,  KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  KC_LOPT,            KC_LCMD,  KC_SPC,  MO(MAC_FN),                     KC_SPC,             KC_RCMD,                              KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_89(
        RGB_TOG,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    /*
     * Left space as backspace
     * Caps lock as esc when tapped, ctrl when held
     * Esc as key lock
     * Right B as delete
     * Home row mods!
     */
    [WIN_BASE] = LAYOUT_ansi_89(
        KC_MUTE,  KC_LOCK,               KC_F1,                  KC_F2,                  KC_F3,                  KC_F4,                  KC_F5,     KC_F6,    KC_F7,                  KC_F8,                    KC_F9,                  KC_F10,                 KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        _______,  KC_GRV,                KC_1,                   KC_2,                   KC_3,                   KC_4,                   KC_5,      KC_6,     KC_7,                   KC_8,                     KC_9,                   KC_0,                   KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        _______,  KC_TAB,                KC_Q,                   KC_W,                   KC_E,                   KC_R,                   KC_T,      KC_Y,     KC_U,                   KC_I,                     KC_O,                   KC_P,                   KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        _______,  MT(MOD_LCTL, KC_ESC),  MT(MOD_LGUI, KC_A),     MT(MOD_LALT, KC_S),     MT(MOD_LCTL, KC_D),     MT(MOD_LSFT, KC_F),     KC_G,      KC_H,     MT(MOD_RSFT, KC_J),     MT(MOD_LCTL, KC_K),       MT(MOD_LALT, KC_L),     MT(MOD_LGUI, KC_SCLN),  KC_QUOT,            KC_ENT,             KC_HOME,
        _______,  KC_LSFT,               KC_Z,                   KC_X,                   KC_C,                   KC_V,                   KC_B,      KC_DEL,   KC_N,                   KC_M,                     KC_COMM,                KC_DOT,                 KC_SLSH,  KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  KC_LWIN,                             KC_LALT,                KC_BSPC,                MO(WIN_FN),                        KC_SPC,   MO(WIN_SYMB),                             KC_LEFT,  KC_DOWN,  KC_RGHT),

    /*
     * Symbol layer w/ numpad
     */
    [WIN_SYMB] = LAYOUT_ansi_89(
        _______,  _______,  _______,                _______,                _______,                _______,                _______,  _______,  _______,                _______,                _______,                _______,                _______,   _______,  _______,            _______,
        _______,  _______,  _______,                _______,                _______,                _______,                _______,  _______,  _______,                _______,                _______,                _______,                _______,   _______,  _______,            _______,
        _______,  _______,  _______,                _______,                KC_LBRC,                KC_RBRC,                KC_PIPE,  _______,  KC_7,                   KC_8,                   KC_9,                   _______,                _______,   _______,  _______,            _______,
        _______,  _______,  MT(MOD_LGUI, KC_LT),    MT(MOD_LALT, KC_GT),    MT(MOD_LCTL, KC_LPRN),  MT(MOD_LSFT, KC_RPRN),  KC_GRV,   _______,  MT(MOD_RSFT, KC_4),     MT(MOD_LCTL, KC_5),     MT(MOD_LALT, KC_6),     MT(MOD_LGUI, _______),  _______,             _______,            _______,
        _______,  _______,                          _______,                _______,                KC_LCBR,                KC_RCBR,  KC_TILD,  _______,                KC_0,                   KC_1,                   KC_2,                   KC_3,      _______,  _______,  _______,
        _______,  _______,  _______,                                        _______,                _______,                MO(WIN_FN),                                 _______,                                        _______,                       _______,  _______,  _______),

    /*
     * WASD as pgup/pgdn/home/end
     * HJKL as arrow keys
     * FCVB move mouse
     * G/T as mouse left/right click
     * YUIO scrolls mouse (like HJKL)
     * 4 as Alt+F4
     * Esc to put keyboard in bootloader mode
     * F1/F2 change RGB hue
     * F3/F4 change RGB saturation
     * F5/F6 cycle through RGB modes
     */
    [WIN_FN] = LAYOUT_ansi_89(
        RGB_TOG,  RESET,    RGB_HUD,                RGB_HUI,                RGB_SAD,               RGB_SAI,                   RGB_RMOD,  RGB_MOD,  KC_MPRV,                KC_MPLY,                KC_MNXT,                KC_MUTE,                KC_VOLD,   KC_VOLU,  _______,            _______,
        _______,  _______,  _______,                _______,                _______,               LALT(KC_F4),               _______,   _______,  _______,                _______,                _______,                _______,                _______,   _______,  _______,            _______,
        _______,  _______,  _______,                KC_PGUP,                _______,               _______,                   KC_BTN2,   KC_WH_L,  KC_WH_D,                KC_WH_U,                KC_WH_R,                _______,                _______,   _______,  _______,            _______,
        _______,  _______,  MT(MOD_LGUI, KC_HOME),  MT(MOD_LALT, KC_PGDN),  MT(MOD_LCTL, KC_END),  MT(MOD_LSFT, KC_MS_U),     KC_BTN1,   KC_LEFT,  MT(MOD_RSFT, KC_DOWN),  MT(MOD_LCTL, KC_UP),    MT(MOD_LALT, KC_RGHT),  MT(MOD_LGUI, _______),  _______,             _______,            _______,
        _______,  _______,                          MS_JGL,                 _______,               KC_MS_L,                   KC_MS_D,   KC_MS_R,  _______,                _______,                _______,                _______,                _______,   _______,  _______,  _______,
        _______,  _______,  _______,                                        _______,               _______,                   _______,                                     _______,                _______,                                        _______,   _______,  _______),

};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_SYMB] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif // ENCODER_MAP_ENABLE

void matrix_scan_user(void) {
    if (mouse_jiggle_mode) {
        tap_code(KC_MS_LEFT);
        tap_code(KC_MS_RIGHT);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case MS_JGL:
        if (record->event.pressed) {
            mouse_jiggle_mode = !mouse_jiggle_mode;
        }
        return false;

    default:
        break;
    }

    return true;
}
