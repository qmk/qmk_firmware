/* Copyright 2021 Christoph Jabs (BifbofII)
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

/* ====== Unicode ====== */
/* Character names */
enum unicode_names { SAE, BAE, SUE, BUE, SOE, BOE, SS, EUR, CPR };

/* Unicode map */
const uint32_t PROGMEM unicode_map[] = {
    [SAE] = 0x00E4,  // ä
    [BAE] = 0x00C4,  // Ä
    [SUE] = 0x00FC,  // ü
    [BUE] = 0x00DC,  // Ü
    [SOE] = 0x00F6,  // ü
    [BOE] = 0x00D6,  // Ü
    [SS]  = 0x00DF,  // ß
    [EUR] = 0x20AC,  // €
    [CPR] = 0x00A9   // ©
};

/* ====== Layers ====== */
enum layer_names {
    QWERTY = 0,
    GAMING,
    FUNCTIONS_1,
    FUNCTIONS_2,
    UNICODE,
    SPECIALS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------------.
     * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
     * |-----------------------------------------------------------------------------------------+
     * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Enter |
     * |-----------------------------------------------------------------------------------+     +
     * | Esc/Unic|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    \  |     |
     * |-----------------------------------------------------------------------------------------+
     * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |      RShift     |
     * |-----------------------------------------------------------------------------------------+
     * | Ctrl | Super |  Alt  |              Space/Fnc            |  Alt  | Super |  Ctrl | Spec |
     * `-----------------------------------------------------------------------------------------'
     */
    [QWERTY] = LAYOUT_60_iso(
        KC_GRV,               KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,               KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        LT(UNICODE, KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT,              KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL,              KC_LGUI, KC_LALT,          LT(FUNCTIONS_1, KC_SPC),                              KC_RALT, KC_RGUI, KC_RCTL, MO(SPECIALS)
    ),

    /* Arrows and media keys
     * ,-----------------------------------------------------------------------------------------.
     * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |    Del    |
     * |-----------------------------------------------------------------------------------------+
     * |        |     |     |     |     |Mute | Prev| V-  | V+  | Next| Play|     |     |  Enter |
     * |-----------------------------------------------------------------------------------+     +
     * | Caps    |     |  <  |     |     |  >  |Left |Down | Up  |Right|     |     |       |     |
     * |-----------------------------------------------------------------------------------------+
     * | Shift     |     |     |     |     |     |Home |Page-|Page+| End |     |         Fnc2    |
     * |-----------------------------------------------------------------------------------------+
     * | Ctrl | Super |  Alt  |             Trans                 |  Alt  | Super |  Ctrl |      |
     * `-----------------------------------------------------------------------------------------'
     */
    [FUNCTIONS_1] = LAYOUT_60_iso(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,              KC_F11,  KC_F12,          KC_DEL,
        _______, _______, _______, _______, _______, KC_MUTE, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MEDIA_PLAY_PAUSE, _______, _______,
        KC_CAPS, _______, KC_WBAK, _______, _______, KC_WFWD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,             _______, _______,         KC_ENT,
        KC_LSFT, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,              _______, MO(FUNCTIONS_2),
        KC_LCTL, KC_LGUI, KC_LALT,                            _______,                            KC_RALT,             KC_RGUI, KC_RCTL,         _______
    ),

    /* More Function keys
     * ,-----------------------------------------------------------------------------------------.
     * |     | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 | F21 | F22 | F23 | F24 |    Del    |
     * |-----------------------------------------------------------------------------------------+
     * |        |     |     |     |     |     |     |     |     |     |     |     |     |  Enter |
     * |-----------------------------------------------------------------------------------+     +
     * | Caps    |     |     |     |     |     |     |     |     |     |     |     |       |     |
     * |-----------------------------------------------------------------------------------------+
     * | Shift     |     |     |     |     |     |     |     |     |     |     |      Trans      |
     * |-----------------------------------------------------------------------------------------+
     * | Ctrl | Super |  Alt  |              Trans                |  Alt  | Super |  Ctrl |      |
     * `-----------------------------------------------------------------------------------------'
     */
    [FUNCTIONS_2] = LAYOUT_60_iso(
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT,
        KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            _______,                            KC_RALT, KC_RGUI, KC_RCTL, _______
    ),

    /* German Umlaute
     * ,-----------------------------------------------------------------------------------------.
     * |     |     |     |     |     |     |     |     |     |     |     |     |     |   Bkspc   |
     * |-----------------------------------------------------------------------------------------+
     * |        |     |     |  €  |     |     |     |  Ü  |     |  Ö  |     |     |     |  Enter |
     * |-----------------------------------------------------------------------------------+     +
     * | Trans   |  Ä  |  ß  |     |     |     |     |     |     |     |     |     |       |     |
     * |-----------------------------------------------------------------------------------------+
     * | Trans     |     |     |  ©  |     |     |     |     |     |     |     |      Trans      |
     * |-----------------------------------------------------------------------------------------+
     * | Ctrl | Super |  Alt  |              Space                |  Alt  | Super |  Ctrl |      |
     * `-----------------------------------------------------------------------------------------'
     */
    [UNICODE] = LAYOUT_60_iso(
        _______, _______,      _______, _______, _______, _______, _______, _______,      _______, _______,      _______, _______, _______, KC_BSPC,
        _______, _______,      _______, X(EUR),  _______, _______, _______, XP(SUE, BUE), _______, XP(SOE, BOE), _______, _______, _______,
        KC_TRNS, XP(SAE, BAE), X(SS),   _______, _______, _______, _______, _______,      _______, _______,      _______, _______, _______, KC_ENT,
        KC_LSFT, _______,      _______, _______, X(CPR),  _______, _______, _______,      _______, _______,      _______, _______, KC_RSFT,
        KC_LCTL, KC_LGUI,      KC_LALT,                            KC_SPC,                                       KC_RALT, KC_RGUI, KC_RCTL, _______
    ),

    /* Specials (Reset, etc)
     * ,-----------------------------------------------------------------------------------------.
     * |     |     |     |     |     |     |     |     |     |     |     | RGB-|RGB+ |           |
     * |-----------------------------------------------------------------------------------------+
     * |        |     | Win |     |     |     |     |     |     | OSX |     |     |     |  RGB   |
     * |-----------------------------------------------------------------------------------+ tog +
     * |         |     |     |     |     |Gamin|     |     |     | Lnx |     |     |       |     |
     * |-----------------------------------------------------------------------------------------+
     * |           |     |     |     |     |QK_BOOT|     |     |     |     |     |                 |
     * |-----------------------------------------------------------------------------------------+
     * |      |       |       |                                   |       |       |       | Trans|
     * `-----------------------------------------------------------------------------------------'
     */
    [SPECIALS] = LAYOUT_60_iso(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_VAI, XXXXXXX,
        XXXXXXX, XXXXXXX, UC_WINC, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, UC_MAC,  XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(GAMING), XXXXXXX, XXXXXXX, XXXXXXX, UC_LINX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                               XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS
    ),

    /* Gaming
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
     * |-----------------------------------------------------------------------------------------+
     * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Enter |
     * |-----------------------------------------------------------------------------------+     +
     * | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    \  |     |
     * |-----------------------------------------------------------------------------------------+
     * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |      RShift     |
     * |-----------------------------------------------------------------------------------------+
     * | Ctrl | Super |  Alt  |              Space                |  Alt  | Super |  Ctrl | Spec |
     * `-----------------------------------------------------------------------------------------'
     */
    [GAMING] = LAYOUT_60_iso(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_RCTL, MO(SPECIALS)
    ),
};

/* ====== LED Underglow ====== */
#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_mode_noeeprom(1);
    rgblight_sethsv_noeeprom(HSV_WHITE);
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_mode_noeeprom(1);
        rgblight_sethsv_noeeprom(HSV_RED);
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_mode_noeeprom(1);
    if (layer_state_cmp(state, GAMING)) {
        rgblight_sethsv_noeeprom(HSV_BLUE);
    } else if (layer_state_cmp(state, SPECIALS)) {
        rgblight_sethsv_noeeprom(HSV_PURPLE);
    } else {
        rgblight_sethsv_noeeprom(HSV_WHITE);
    }
    return state;
}
#endif
