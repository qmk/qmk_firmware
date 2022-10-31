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

enum layers {
    _ALPHA,
    _LEFTFN,
    _RIGHTFN,
    _NUMPAD,
    _LEAGUE,
    _PUBG,
    _OVERWATCH,
    _STARCRAFT,
    _TETRIS,
    _CLEAN,
    _RGB
};

#define ALPHA TO(_ALPHA)
#define LEFTFN MO(_LEFTFN)
#define RIGHTFN MO(_RIGHTFN)
#define NUMPAD MO(_NUMPAD)
#define LEAGUE TG(_LEAGUE)
#define PUBG TG(_PUBG)
#define OVERWATCH TG(_OVERWATCH)
#define STARCRAFT TG(_STARCRAFT)
#define TETRIS TG(_TETRIS)
#define CLEAN TG(_CLEAN)
#define RGB MO(_RGB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ALPHA
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ESC/NP|  KOR | Win  | Alt  |LEFTFN|    Space    |RFN/- |   =  |Delete|  \   | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_ALPHA] = LAYOUT_planck_mit(
    KC_TAB,             KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,                 KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL,            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,                 KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,                 KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    LT(NUMPAD, KC_ESC), KC_LNG1, KC_LGUI, KC_LALT, LEFTFN,     KC_SPC,      LT(RIGHTFN, KC_MINS), KC_EQL,  KC_DEL,  KC_BSLS, KC_PENT
),

/* LEFTFN
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Left | Down | Up   |Right |CTRL+/|HANJA |   [  |   ]  |   )  |   :  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| PGUP | PGDN | Home | End  | CAPS |PRNTSR|   (  |   ,  |   .  |   /  |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RGB  |   [  |   ]  | Alt  | Trns |    Space    |   _  |   +  | INS  |   |  | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_LEFTFN] = LAYOUT_planck_mit(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, LCTL(KC_SLSH),  KC_LNG2, KC_LBRC, KC_RBRC, KC_RPRN, KC_COLN, KC_DQUO,
    KC_LSFT, KC_PGUP, KC_PGDN, KC_HOME, KC_END,   KC_CAPS,        KC_PSCR, KC_LPRN, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    RGB,     KC_LBRC, KC_RBRC, KC_LALT, KC_TRNS,           KC_SPC,         KC_UNDS, KC_PLUS, KC_INS,  KC_PIPE, KC_PENT
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

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |   *  |   7  |   8  |   9  | NumLk|      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Alt |   4  |   5  |   6  |Return|      |      |      |      |      | Shift|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   -  |   1  |   2  |   3  | Bksp |      |      |      |      |      | Ctrl |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Trns |   ,  |   +  |   .  |   0  |    Space    |LEAGUE| PUBG | OVWCh|  SC  |TETRIS|
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_mit(
    KC_ASTR, KC_P7,   KC_P8,   KC_P9,   KC_NLCK, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,     KC_NO,     KC_BSPC,
    KC_LALT, KC_P4,   KC_P5,   KC_P6,   KC_ENT,  KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,     KC_LSFT,   KC_NO,
    KC_PMNS, KC_P1,   KC_P2,   KC_P3,   KC_BSPC, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,     KC_LCTL,   KC_ENT,
    KC_TRNS, KC_COMM, KC_PPLS, KC_PDOT, KC_0,       KC_SPC,    LEAGUE, PUBG,  OVERWATCH, STARCRAFT, TETRIS
),


/* LEAGUE
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
[_LEAGUE] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R, KC_5,  KC_Y,  KC_NO, KC_NO, KC_O,  KC_P,  KC_ESC,
    KC_LCTL, KC_A, KC_S, KC_D,    KC_F, KC_NO, KC_NO, KC_NO, KC_NO, KC_L,  KC_NO, KC_NO,
    KC_LSFT, KC_Z, KC_6, KC_4,    KC_1, KC_B,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ENT,
    KC_3,    KC_X, KC_C, KC_LALT, KC_2,    KC_SPC,    KC_NO, KC_NO, KC_NO, KC_NO, ALPHA
),

/* PUBG
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
[_PUBG] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,  KC_ESC,
    KC_1,    KC_A, KC_S, KC_D,    KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_NO, KC_F7,
    KC_LSFT, KC_Z, KC_3, KC_X,    KC_C, KC_V, KC_B, KC_M, KC_COMM, KC_DOT, KC_NO, KC_F9,
    KC_LCTL, KC_5, KC_4, KC_LALT, KC_2,   KC_SPC,   KC_6, KC_8,    KC_7,   KC_9,  ALPHA
),

/* OVERWATCH
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
[_OVERWATCH] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,  KC_W,  KC_E,    KC_R, KC_T, KC_Y, KC_U,    KC_I,    KC_O,   KC_P,    KC_ESC,
    KC_1,    KC_A,  KC_S,  KC_D,    KC_F, KC_G, KC_H, KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,  KC_X,  KC_C,    KC_V, KC_B, KC_N, KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
    KC_LCTL, KC_NO, KC_NO, KC_LALT, KC_2,   KC_SPC,   KC_BSPC, KC_NO,   KC_NO,  KC_NO,   ALPHA
),

/* STARCRAFT
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
[_STARCRAFT] = LAYOUT_planck_mit(

    KC_TAB,  KC_Q,   KC_W,  KC_E,    KC_R,  KC_T, KC_Y, KC_U,   KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_LCTL, KC_A,   KC_S,  KC_D,    KC_F,  KC_G, KC_H, KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,   KC_X,  KC_C,    KC_V,  KC_B, KC_N, KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
    KC_ESC,  KC_NO,  KC_NO, KC_LALT, KC_F1,   KC_SPC,   KC_F10, KC_PAUS, KC_DEL, KC_NO,   ALPHA
),

/* TETRIS
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
[_TETRIS] = LAYOUT_planck_mit(

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
 * |      | Reset|      |      |      |      |      |      |      |      |      | CLEAN|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |RGBTGL| MOD+ | BRT+ | SAT+ |      |      |      | FX+  | HUE+ |      | MOD R| MODES|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | MOD- | BRT- | SAT- | Trns |             | FX-  | HUE- |      | MOD B| MOD P|
 * `-----------------------------------------------------------------------------------'
 */
[_RGB] = LAYOUT_planck_mit(
    KC_NO,   QK_BOOT,  KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   CLEAN,
    KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,
    RGB_TOG, RGB_MOD,  RGB_VAI, RGB_SAI, KC_NO, KC_NO, KC_NO, RGB_SPI, RGB_HUI, KC_NO, RGB_M_R, RGB_M_SW,
    KC_NO,   RGB_RMOD, RGB_VAD, RGB_SAD, KC_TRNS,   KC_NO,    RGB_SPD, RGB_HUD, KC_NO, RGB_M_B, RGB_M_P
)

};

/*

// Key Matrix to LED Index
{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11},
{12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
{24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
{36, 37, 38, 39, 40,   41,   42, 43, 44, 45, 46}

*/

void rgb_matrix_indicators_user(void) {
    uint8_t red[3] = {50, 5, 0};
    uint8_t yellow[3] = {50, 50, 0};
    uint8_t blue[3] = {0, 15, 50};
    uint8_t green[3] = {15, 33, 1};
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
        case _LEAGUE:
            rgb_matrix_set_color(15, yellow[0], yellow[1], yellow[2]);
            rgb_matrix_set_color(16, red[0], red[1], red[2]);
            rgb_matrix_set_color(29, blue[0], blue[1], blue[2]);
            rgb_matrix_set_color(42, green[0], green[1], green[2]);

            break;

        case _PUBG:
            rgb_matrix_set_color(43, green[0], green[1], green[2]);

            break;

        case _OVERWATCH:
            rgb_matrix_set_color(44, green[0], green[1], green[2]);
            break;

        case _STARCRAFT:
            rgb_matrix_set_color(45, green[0], green[1], green[2]);
            break;

        case _TETRIS:
            rgb_matrix_set_color(46, green[0], green[1], green[2]);
            break;

        case _CLEAN:
            rgb_matrix_set_color_all(white[0], white[1], white[2]);
            break;

        case _RGB:
            break;
    }

    led_t led_state = host_keyboard_led_state();

    //Capslock led
    if (led_state.caps_lock) {
        rgb_matrix_set_color(12, green[0], green[1], green[2]);
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

}
