/* Copyright 2024 Pablo Jiménez Mateo (@pablojimenezmateo)
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

/* These are some Spanish specific keys */
#define ES_ACUT KC_QUOT
#define ES_NTIL KC_SCLN
#define ES_SLSH S(KC_7)
#define ES_PIPE ALGR(KC_1)
#define ES_AT ALGR(KC_2)
#define ES_LCBR ALGR(KC_QUOT)
#define ES_RCBR ALGR(KC_NUHS)
#define ES_CIRC S(KC_LBRC)
#define ES_IEXL KC_EQL
#define ES_LPRN S(KC_8)
#define ES_RPRN S(KC_9)
#define ES_HASH ALGR(KC_3)
#define ES_LBRC ALGR(KC_LBRC)
#define ES_RBRC ALGR(KC_RBRC)
#define ES_TILD ALGR(KC_4)
#define ES_APOS KC_MINS
#define ES_DQUO S(KC_2)
#define ES_EQL S(KC_0)
#define ES_AMPR S(KC_6)
#define ES_ASTR S(KC_RBRC)
#define ES_GRV KC_LBRC
#define ES_IQUE S(KC_EQL)
#define ES_QUES S(KC_MINS)
#define ES_COLN S(KC_DOT)
#define ES_SCLN S(KC_COMM)
#define ES_PLUS KC_RBRC
#define ES_LESS KC_NUBS
#define ES_GRTR S(KC_NUBS)
#define ES_MINS KC_SLSH
#define ES_UNDS S(KC_SLSH)
#define ES_BSLS ALGR(KC_GRV)

#define LED_ROWS_PER_HALF 4
#define LED_COLS_PER_HALF 6
#define LED_COLS  (LED_COLS_PER_HALF * 2)
#define LED_TOTAL 48

enum layer_names {
    _MAIN = 0,
    _NUMBERS,
    _SYMBOLS,
    _NAVIGATION,
    _GAMING
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_NO,      KC_Q,       KC_W,                KC_E,               KC_R,               KC_T,                KC_Y,            KC_U,               KC_I,               KC_O,               KC_P,    KC_NO,
        KC_TAB,     KC_A,       MT(MOD_LSFT,  KC_S), MT(MOD_LALT, KC_D), MT(MOD_LCTL, KC_F), KC_G,                KC_H,            MT(MOD_RCTL, KC_J), MT(MOD_LALT, KC_K), MT(MOD_RSFT, KC_L), ES_NTIL, ES_ACUT,
        KC_ESCAPE,  KC_Z,       KC_X,                KC_C,               KC_V,               KC_B,                KC_N,            KC_M,               KC_COMMA,           KC_DOT,             ES_SLSH, KC_NO,
        LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),          KC_NO,              MO(1),              LT(3, KC_SPC),       LT(2, KC_ENTER), KC_LSFT,            KC_NO,              KC_LEFT_GUI,        KC_NO,   LCTL(KC_F)
    ),
    [_NUMBERS] = LAYOUT(
        KC_NO, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_NO,       KC_NO, KC_7,  KC_8,  KC_9,  KC_NO, KC_NO,
        KC_NO, KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_NO,       KC_NO, KC_4,  KC_5,  KC_6,  KC_NO, KC_NO,
        KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,       KC_NO, KC_1,  KC_2,  KC_3,  KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_0,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [_SYMBOLS] = LAYOUT(
        KC_NO, ES_PIPE, ES_AT,   ES_LCBR, ES_RCBR, ES_CIRC,       ES_APOS, ES_DQUO, ES_EQL,  ES_AMPR, ES_ASTR, ES_GRV,
        KC_NO, ES_IEXL, KC_EXLM, ES_LPRN, ES_RPRN, KC_DLR,        ES_IQUE, ES_QUES, ES_SLSH, ES_COLN, ES_SCLN, ES_PLUS,
        KC_NO, ES_HASH, KC_PERC, ES_LBRC, ES_RBRC, ES_TILD,       ES_LESS, ES_GRTR, ES_MINS, ES_UNDS, ES_BSLS, KC_PSCR,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BSPC,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT
    ),
    [_NAVIGATION] = LAYOUT(
        TG(_GAMING), KC_NO,      MS_BTN4,    MS_UP,   MS_BTN5, KC_NO,             LSFT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP),   LSFT(KC_RGHT), KC_NO,  KC_VOLU,
        KC_NO,       QK_LLCK,    MS_LEFT,    MS_DOWN, MS_RGHT, KC_LEFT_CTRL,      KC_HOME,       MS_BTN1,       MS_BTN3,       MS_BTN2,       KC_END, KC_VOLD,
        KC_NO,       KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,             KC_LEFT,       KC_DOWN,       KC_UP,         KC_RGHT,       KC_NO,  KC_BRIU,
        LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), KC_NO,   KC_NO,   KC_NO,             MS_WHLD,       MS_WHLU,       KC_NO,         KC_NO,         KC_NO,  KC_BRID
    ),
    [_GAMING] = LAYOUT(
        KC_TAB,       KC_Q,  KC_W,  KC_E,          KC_R,   KC_T,                   KC_Y,  KC_U, KC_I,     KC_O,   KC_P,    ES_ACUT,
        KC_LEFT_CTRL, KC_A,  KC_S,  KC_D,          KC_F,   KC_G,                   KC_H,  KC_J, KC_K,     KC_L,   ES_NTIL, KC_NO,
        KC_ESCAPE,    KC_Z,  KC_X,  KC_C,          KC_V,   KC_B,                   KC_N,  KC_M, KC_COMMA, KC_DOT, ES_SLSH, KC_NO,
        TG(_GAMING),  KC_NO, KC_NO, KC_LEFT_SHIFT, KC_SPC, MO(_GAMING_NUM),        KC_NO, KC_1, KC_2,     KC_3,   KC_4,    KC_5
    )
};

/* These values are in RGB */
const uint8_t PROGMEM ledmap[][LED_TOTAL][3] = {
    [_MAIN] = { 
        {255,255,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,0},
        {255,255,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,0},
        {255,255,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,0},
        {255,255,0}, {255,255,0},   {255,255,0},   {255,255,0},   {255,255,0},   {255,255,0},        {255,255,0}, {255,255,0}, {255,255,0}, {255,255,0}, {255,255,0}, {255,255,0}, 
    },
    [_NUMBERS] = { 
        {0,0,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {0,0,255},
        {0,0,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {0,0,255},
        {0,0,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {0,0,255},
        {0,0,255}, {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},          {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255}, 
    },
    [_SYMBOLS] = { 
        {255,0,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,0,255},
        {255,0,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,0,255},
        {255,0,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,0,255},
        {255,0,255}, {255,0,255},   {255,0,255},   {255,0,255},   {255,0,255},   {255,0,255},        {255,0,255},   {255,0,255},   {255,0,255},   {255,0,255},   {255,0,255},   {255,0,255}, 
    },
    [_NAVIGATION] = { 
        {0,255,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {0,255,0},
        {0,255,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {0,255,0},
        {0,255,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {0,255,0},
        {0,255,0}, {0,255,0},     {0,255,0},     {0,255,0},     {0,255,0},     {0,255,0},          {0,255,0},     {0,255,0},     {0,255,0},     {0,255,0},     {0,255,0},     {0,255,0},
    },
    [_GAMING] = { 
        {255,0,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,0,0},
        {255,0,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,0,0},
        {255,0,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255},      {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,0,0},
        {255,0,0}, {255,0,0},     {255,0,0},     {255,0,0},     {255,0,0},     {255,0,0},          {255,0,0},     {255,0,0},     {255,0,0},     {255,0,0},     {255,0,0},     {255,0,0},
    },
};

/* We use this to get the correct values from the ledmap depending on the half we are on */
uint8_t index_offset;

void keyboard_post_init_user(void) {
    bool is_left = eeconfig_read_handedness();

    if (is_left) {
        index_offset = 0;
    } else {
        index_offset = LED_COLS_PER_HALF;
    }
}

/* We use this so we can keep the ledmap with a "visual"
representation (each half uses indexes from 0-23, we cannot use 0-47)
*/
const uint8_t PROGMEM physical_index[LED_TOTAL] = {
    0,  1,  2,  3,  4,  5,       5,  4,  3,  2,  1,  0, 
    11, 10, 9,  8,  7,  6,       6,  7,  8,  9,  10, 11, 
    12, 13, 14, 15, 16, 17,      17, 16, 15, 14, 13, 12, 
    23, 22, 21, 20, 19, 18,      18, 19, 20, 21, 22, 23,
};


/* This is run in each half per cycle */
bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    for (uint8_t row = 0; row < LED_ROWS_PER_HALF; row++) {
        for (uint8_t col = 0; col < LED_COLS_PER_HALF; col++) {

            uint8_t linear_index = row * LED_COLS + col + index_offset;
            uint8_t index = pgm_read_byte(&physical_index[linear_index]);

            uint8_t r = pgm_read_byte(&ledmap[layer][linear_index][0]);
            uint8_t g = pgm_read_byte(&ledmap[layer][linear_index][1]);
            uint8_t b = pgm_read_byte(&ledmap[layer][linear_index][2]);

            rgb_matrix_set_color(index, r, g, b);
        }
    }

    return true;
}