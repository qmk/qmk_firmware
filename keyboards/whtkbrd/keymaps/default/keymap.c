/* Copyright 2022 Alexander Metz
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

/* A keyboard layout with only 5 columns, 3-4 rows, and 3 thumb keys. */

/* Keybindings for MacOS. */
#define KC_PREV_WORD LALT(KC_LEFT)
#define KC_NEXT_WORD LALT(KC_RGHT)
#define KC_PREV_TAB LCTL(LSFT(KC_TAB))
#define KC_NEXT_TAB LCTL(KC_TAB)
#define KC_LINE_BEGIN LGUI(KC_LEFT)
#define KC_LINE_END LGUI(KC_RGHT)

/* Keybindings for Linux. */
/*
 * #define KC_PREV_WORD LCTL(KC_LEFT)
 * #define KC_NEXT_WORD LCTL(KC_RGHT)
 * #define KC_PREV_TAB LCTL(KC_PGUP)
 * #define KC_NEXT_TAB LCTL(KC_PGDN)
 * #define KC_LINE_BEGIN KC_HOME
 * #define KC_LINE_END KC_END
 */

/* Thumbs keys with mod tap / layer tap. */
#define KC_THUMB_L0 LT(LAYER_SYM_NAV, KC_SPC)
#define KC_THUMB_L1 LCTL_T(KC_TAB)
#define KC_THUMB_R0 LT(LAYER_BRA_SYM, KC_ENT)
#define KC_THUMB_R1 RSFT_T(KC_BSPC)

typedef enum _layer_t {
    LAYER_ALPHA = 0,
    /* Layer for thumb keys without mod tap / layer tap for hold-repeat. */
    LAYER_THUMB,
    LAYER_SYM_NAV,
    LAYER_BRA_SYM,
    LAYER_FUN_NUM,
} layer_t;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_ALPHA] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          XXXXXXX,
        XXXXXXX,       KC_A,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_ESC,        XXXXXXX,
        XXXXXXX,       KC_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,      MO(LAYER_THUMB), XXXXXXX,
                                      XXXXXXX,       KC_THUMB_L1,   KC_THUMB_L0,   KC_LGUI,                      KC_LALT,       KC_THUMB_R0,   KC_THUMB_R1,   XXXXXXX
    ),
    [LAYER_THUMB] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       XXXXXXX,
        XXXXXXX,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       XXXXXXX,
        XXXXXXX,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       XXXXXXX,
                                      XXXXXXX,       KC_TAB,        KC_SPC,        KC_RGUI,                      KC_RALT,       KC_ENT,        KC_BSPC,       XXXXXXX
    ),
    [LAYER_SYM_NAV] = LAYOUT(
        XXXXXXX,       XXXXXXX,       KC_LPRN,       KC_RPRN,       KC_LCBR,       KC_RCBR,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_TILD,       KC_PLUS,       KC_UNDS,       KC_BSLS,                      KC_PGUP,       KC_PREV_WORD,  KC_UP,         KC_NEXT_WORD,  KC_PSCR,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH,                      KC_HOME,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_END,        XXXXXXX,
        XXXXXXX,       _______,       KC_PIPE,       KC_AMPR,       KC_ASTR,       KC_CIRC,                      KC_PGDN,       KC_PREV_TAB,   KC_NEXT_TAB,   KC_INS,        XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       _______,       _______,       _______,                      _______,       _______,       _______,       XXXXXXX
    ),
    [LAYER_BRA_SYM] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,       KC_LCBR,       KC_RCBR,       XXXXXXX,                      KC_DQUO,       KC_COMM,       KC_QUES,       KC_COLN,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_LT,         KC_LPRN,       KC_RPRN,       KC_GT,                        KC_QUOT,       KC_DOT,        KC_EXLM,       KC_SCLN,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       _______,       XXXXXXX,       KC_LBRC,       KC_RBRC,       XXXXXXX,                      KC_AT,         KC_HASH,       KC_DLR,        KC_PERC,       XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       _______,       _______,       _______,                      _______,       _______,       _______,       XXXXXXX
    ),
    [LAYER_FUN_NUM] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_F1,         KC_F2,         KC_F3,         KC_F4,                        KC_0,          KC_1,          KC_2,          KC_3,          RESET,         XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_F5,         KC_F6,         KC_F7,         KC_F8,                        KC_DOT,        KC_4,          KC_5,          KC_6,          XXXXXXX,       XXXXXXX,
        XXXXXXX,       _______,       KC_F9,         KC_F10,        KC_F11,        KC_F12,                       KC_COMM,       KC_7,          KC_8,          KC_9,          XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       _______,       _______,       _______,                      _______,       _______,       _______,       XXXXXXX
    ),
};

void update_leds(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case LAYER_ALPHA:
            pwr_led_off();
            stat_led_off();
            break;
        case LAYER_SYM_NAV:
            pwr_led_off();
            stat_led_on();
            break;
        case LAYER_BRA_SYM:
            pwr_led_on();
            stat_led_off();
            break;
        case LAYER_FUN_NUM:
            pwr_led_on();
            stat_led_on();
            break;
        case LAYER_THUMB:
            break;
        default:
            break;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, LAYER_SYM_NAV, LAYER_BRA_SYM, LAYER_FUN_NUM);
  update_leds(state);
  return state;
}
