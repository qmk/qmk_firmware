/* Copyright 2020 tominabox1
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
#include "features/custom_shift_keys.h"

enum layers {
    _ALPHA,
    _LEFTFN,
    _NUMPAD,
    _RIGHTFN,
    _MOBA,
    _FPS1,
    _FPS2,
    _STRAT,
    _ARROWS,
    _CLEAN,
    _RGB
};

#define ALPHA TO(_ALPHA)
#define LEFTFN MO(_LEFTFN)
#define NUMPAD MO(_NUMPAD)
#define RIGHTFN MO(_RIGHTFN)
#define MOBA TG(_MOBA)
#define FPS1 TG(_FPS1)
#define FPS2 TG(_FPS2)
#define STRAT TG(_STRAT)
#define ARROWS TG(_ARROWS)
#define CLEAN TG(_CLEAN)
#define RGB MO(_RGB)

// Tap dance declarations
enum {
    TD_PAST_PSLS,
    TD_PASTE_COPY
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_PAST_PSLS]  = ACTION_TAP_DANCE_DOUBLE(KC_PAST,    KC_PSLS),
    [TD_PASTE_COPY] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_V), LCTL(KC_C))
};

// Custom shift implementation
const custom_shift_key_t custom_shift_keys[] = {
    {KC_LNG1, KC_LNG2},
    {KC_LT, KC_COMM},
    {KC_GT, KC_DOT},
    {KC_LCBR, KC_LBRC},
    {KC_RCBR, KC_RBRC}
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    if ( !process_custom_shift_keys(keycode, record)) { return false; }

    return true;
}

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ALPHA
 * ,-----------------------------------------------------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Esc |KOR/HN|  Win |  Alt |LEFTFN|    Space    |RFN/- |   =  |Delete|   \  | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_ALPHA] = LAYOUT_planck_mit(
    KC_TAB,              KC_Q,    KC_W,    KC_E,    KC_R,   KC_T, KC_Y, KC_U,                 KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL,             KC_A,    KC_S,    KC_D,    KC_F,   KC_G, KC_H, KC_J,                 KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,   KC_B, KC_N, KC_M,                 KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    LT(NUMPAD, KC_ESC),  KC_LNG1, KC_LGUI, KC_LALT, LEFTFN,   KC_SPC,   LT(RIGHTFN, KC_MINS), KC_EQL,  KC_DEL,  KC_BSLS, KC_PENT
),

/* LEFTFN
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Left | Down | Up   |Right |Ctrl+/|PrntSc|   {  |   }  |   )  |   :  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   [  |  ]   | Home | End  | PGUP | PGDN |   (  |   <  |   >  |   /  |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  RGB | Caps | Ins  | Alt  | Trns |    Space    |   _  |   +  |Delete|   |  | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_LEFTFN] = LAYOUT_planck_mit(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, LCTL(KC_SLSH), KC_PSCR, KC_LCBR, KC_RCBR, KC_RPRN, KC_COLN, KC_DQUO,
    KC_LSFT, KC_LBRC, KC_RBRC, KC_HOME, KC_END,   KC_PGUP,       KC_PGDN, KC_LPRN, KC_LT,   KC_GT,   KC_SLSH, KC_ENT,
    RGB,     KC_CAPS, KC_INS,  KC_LALT, KC_TRNS,        KC_SPC,           KC_UNDS, KC_PLUS, KC_DEL,  KC_PIPE, KC_PENT
),

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * | *or/ |   7  |   8  |   9  | NumLk|      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Alt |   4  |   5  |   6  |Return|      |      |      |      |      | Shift|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   -  |   1  |   2  |   3  | Bksp |      |      |      |   ,  |   .  | Ctrl |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Trns |   ,  |   +  |   .  |   0  |    Space    | MOBA | FPS1 | FPS2 | STRAT|ARROWS|
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_mit(
    TD(TD_PAST_PSLS), KC_P7,   KC_P8,   KC_P9,   KC_NUM,  KC_NO,     KC_NO, KC_NO,  KC_NO,   KC_NO,     KC_NO,     KC_BSPC,
    KC_LALT,          KC_P4,   KC_P5,   KC_P6,   KC_ENT,  KC_NO,     KC_NO, KC_NO,  KC_NO,   KC_NO,     KC_LSFT,   KC_NO,
    KC_PMNS,          KC_P1,   KC_P2,   KC_P3,   KC_BSPC, KC_NO,     KC_NO, KC_NO,  KC_COMM, KC_DOT,    KC_LCTL,   KC_ENT,
    KC_TRNS,          KC_COMM, KC_PPLS, KC_PDOT, KC_P0,       KC_SPC,       MOBA, FPS1,    FPS2, STRAT, ARROWS
),

/* RIGHTFN
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |  F12 |  F11 |  F10 |  F9  | Pause|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |      |      |      |      |      |  F8  |  F7  |  F6  |  F5  |Scllck|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |  F4  |  F3  |  F2  |  F1  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  Alt |      |    Space    | Trns |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RIGHTFN] = LAYOUT_planck_mit(
    KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_F12,  KC_F11, KC_F10, KC_F9, KC_PAUS,
    KC_LCTL, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_F8,   KC_F7,  KC_F6,  KC_F5, KC_SCRL,
    KC_LSFT, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_F4,   KC_F3,  KC_F2,  KC_F1, KC_NO,
    KC_NO,   KC_NO, KC_NO, KC_LALT, KC_NO,    KC_SPC,    KC_TRNS, KC_NO,  KC_NO,  KC_NO, KC_NO
),

/* MOBA
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   5  |   Y  |      |      |   O  |   P  | ESC  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |      |      |      |      |   L  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   6  |   4  |   1  |   B  |      |      |      |      |      |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   3  |   X  |   C  |  Alt |   2  |    Space    |      |      |      |      | ALPHA|
 * `-----------------------------------------------------------------------------------'
 */
[_MOBA] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R, KC_5,  KC_Y,  KC_NO, KC_NO, KC_O,  KC_P,  KC_ESC,
    KC_LCTL, KC_A, KC_S, KC_D,    KC_F, KC_NO, KC_NO, KC_NO, KC_NO, KC_L,  KC_NO, KC_NO,
    KC_LSFT, KC_Z, KC_6, KC_4,    KC_1, KC_B,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ENT,
    KC_3,    KC_X, KC_C, KC_LALT, KC_2,    KC_SPC,    KC_NO, KC_NO, KC_NO, KC_NO, ALPHA
),

/* FPS1
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | ESC  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   1  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |      |  F7  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   3  |   X  |   C  |   V  |   B  |   M  |   ,  |   .  |      |  F9  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   5  |   4  |  Alt |   2  |    Space    |   6  |   8  |  7   |  9   | ALPHA|
 * `-----------------------------------------------------------------------------------'
 */
[_FPS1] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,  KC_ESC,
    KC_1,    KC_A, KC_S, KC_D,    KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_NO, KC_F7,
    KC_LSFT, KC_Z, KC_3, KC_X,    KC_C, KC_V, KC_B, KC_M, KC_COMM, KC_DOT, KC_NO, KC_F9,
    KC_LCTL, KC_5, KC_4, KC_LALT, KC_2,   KC_SPC,   KC_6, KC_8,    KC_7,   KC_9,  ALPHA
),

/* FPS2
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | ESC  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   1  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |      | Alt  |   2  |    Space    | Bksp |      |      |      | ALPHA|
 * `-----------------------------------------------------------------------------------'
 */
[_FPS2] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,  KC_W,  KC_E,    KC_R, KC_T, KC_Y, KC_U,    KC_I,    KC_O,   KC_P,    KC_ESC,
    KC_1,    KC_A,  KC_S,  KC_D,    KC_F, KC_G, KC_H, KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,  KC_X,  KC_C,    KC_V, KC_B, KC_N, KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
    KC_LCTL, KC_NO, KC_NO, KC_LALT, KC_2,   KC_SPC,   KC_BSPC, KC_NO,   KC_NO,  KC_NO,   ALPHA
),

/* STRAT
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |      |      | Alt  |   F1 |    Space    |  F10 | Pause|Delete|      | ALPHA|
 * `-----------------------------------------------------------------------------------'
 */
[_STRAT] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,   KC_W,  KC_E,    KC_R,  KC_T, KC_Y, KC_U,   KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_LCTL, KC_A,   KC_S,  KC_D,    KC_F,  KC_G, KC_H, KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,   KC_X,  KC_C,    KC_V,  KC_B, KC_N, KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
    KC_ESC,  KC_NO,  KC_NO, KC_LALT, KC_F1,   KC_SPC,   KC_F10, KC_PAUS, KC_DEL, KC_NO,   ALPHA
),

/* ARROWS
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |  Up  |   E  |   R  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   A  | Left | Down | Right|   F  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |      |  Alt |   S  |    Space    |      |      |      |      | ALPHA|
 * `-----------------------------------------------------------------------------------'
 */
[_ARROWS] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,    KC_UP,   KC_E,     KC_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_A,    KC_LEFT, KC_DOWN, KC_RIGHT, KC_F, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_LCTL, KC_NO,   KC_NO,   KC_LALT,  KC_S,    KC_SPC,    KC_NO, KC_NO, KC_NO, KC_NO, ALPHA
),

/* CLEAN
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | ALPHA|
 * `-----------------------------------------------------------------------------------'
 */
[_CLEAN] = LAYOUT_planck_mit(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, ALPHA
),

/* RGB (LEFTFN + RGB)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * | Mute | Reset| MS_U | BR B | BR F |      |      | MOD R| MOD B| FX+  |      |CLEAN |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | MS_L | MS_D | MS_R |Return|PST/CO|      | MOD P| MOD S| FX-  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| MCK  | RCK  | LCK  | Bksp |      |      | BRT+ | MOD+ | SAT+ | HUE+ | MS 0 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Trns | VOL- | VOL+ | WL U | WL D |    Space    | BRT- | MOD- | SAT- | HUE- |RGBTGL|
 * `-----------------------------------------------------------------------------------'
 */
[_RGB] = LAYOUT_planck_mit(
    KC_MUTE, QK_BOOT, KC_MS_U, KC_WBAK, KC_WFWD, KC_NO,             KC_NO, RGB_M_R, RGB_M_B,  RGB_SPI, KC_NO,   CLEAN,
    KC_LCTL, KC_MS_L, KC_MS_D, KC_MS_R, KC_ENT,  TD(TD_PASTE_COPY), KC_NO, RGB_M_P, RGB_M_SW, RGB_SPD, KC_NO,   KC_NO,
    KC_LSFT, KC_BTN3, KC_BTN2, KC_BTN1, KC_BSPC, KC_NO,             KC_NO, RGB_VAI, RGB_MOD,  RGB_SAI, RGB_HUI, KC_ACL0,
    KC_TRNS, KC_VOLD, KC_VOLU, KC_WH_U, KC_WH_D,           KC_SPC,         RGB_VAD, RGB_RMOD, RGB_SAD, RGB_HUD, RGB_TOG
)

};

/*
// Key Matrix to LED Index
{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11},
{12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
{24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
{36, 37, 38, 39, 40,   41,   42, 43, 44, 45, 46}
*/
bool rgb_matrix_indicators_user(void) {
    uint8_t red[3] = {22, 2, 0};
    uint8_t yellow[3] = {20, 22, 0};
    uint8_t blue[3] = {0, 6, 20};
    uint8_t green[3] = {14, 22, 0};
    uint8_t purple[3] = {6, 0, 22};
    uint8_t white[3] = {255, 255, 255};

    switch (get_highest_layer(layer_state)) {
        case _ALPHA:
            break;
        case _LEFTFN:
            break;
        case _RIGHTFN:
            break;
        case _NUMPAD:
            break;
        case _MOBA:
            rgb_matrix_set_color(16, red[0],    red[1],    red[2]);
            rgb_matrix_set_color(15, yellow[0], yellow[1], yellow[2]);
            rgb_matrix_set_color(29, blue[0],   blue[1],   blue[2]);
            rgb_matrix_set_color(10, purple[0], purple[1], purple[2]);
            break;
        case _FPS1:
            rgb_matrix_set_color(43, green[0],  green[1],  green[2]);
            break;
        case _FPS2:
            rgb_matrix_set_color(44, green[0],  green[1],  green[2]);
            break;
        case _STRAT:
            rgb_matrix_set_color(45, green[0],  green[1],  green[2]);
            break;
        case _ARROWS:
            rgb_matrix_set_color(46, green[0],  green[1],  green[2]);
            break;
        case _CLEAN:
            rgb_matrix_set_color_all(white[0],  white[1],  white[2]);
            break;
        case _RGB:
            rgb_matrix_set_color(1, blue[0], blue[1], blue[2]);
            break;
    }

    led_t led_state = host_keyboard_led_state();
    //Capslock led
    if (led_state.caps_lock) {
        rgb_matrix_set_color(0,  green[0], green[1], green[2]);
    }
    //Numlock led
    if (led_state.num_lock) {
    } else {
        rgb_matrix_set_color(11, green[0], green[1], green[2]);
    }
    //Scroll lock led
    if (led_state.scroll_lock) {
        rgb_matrix_set_color(23, green[0], green[1], green[2]);
    }
    return false;
}

// Turn of RGB Matrix Effect
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}
