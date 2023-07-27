 /* Copyright 2023 Garavito
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
#include <stdio.h>

//extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _DVORAK,
  _D_LOWER,
  _D_RAISE,
  _D_ADJUST,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LGUI  | LOWER| LAlt | /Space  /       \Enter \  |BackSP| RAISE | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LGUI, MO(_LOWER), KC_LALT, KC_SPC, KC_ENT, KC_BSPC, MO(_RAISE), KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Br- |  Br+ |      |      |     |       |                    | Vol- |  Vol+ | Prev | Play | Next |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LGUI  | LOWER| LAlt | /Space  /       \Enter \  |BackSP| ADJUST | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_BRID,   KC_BRIU,_______,_______,_______,_______,                     KC_VOLD, KC_VOLU ,KC_MPRV,KC_MPLY, KC_MNXT, _______,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, TO(_ADJUST), _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |LCTRL|LShift| LAlt |      |       |                    |      |      |      |      | Prnt |  Ins |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |  Up  |   8  |   9  |  0   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Home | Left | Down | Right|     |  End |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LGUI  | ADJUST| LAlt | /Space  /       \Enter \  |BackSP| RAISE | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______,KC_LCTL, KC_LSFT, KC_LALT, _______, _______,                     _______, _______, _______, _______, KC_PSCR , KC_INS,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_UP,    KC_8,    KC_9,   KC_0 ,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_HOME, KC_LEFT , KC_DOWN, KC_RGHT,_______, KC_END,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, TO(_ADJUST), _______,  _______, _______,  KC_DEL, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Reset |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|QWERTY|    | DVORAK |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LGUI  | LOWER| LAlt | /Space  /       \Enter \  |BackSP| RAISE | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  QK_BOOT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_QWERTY), TO(_DVORAK), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),
  /* DVORAK
 *      ,-----------------------------------------.                    ,-----------------------------------------.
 *      | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 *      |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCTRL(Tab)|  '   |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   K  |  R   |  -   |
 *      |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *      |  [   |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |   ]  |/\
 *      |------+------+------+------+------+------|   \   |    |   /   |------+------+------+------+------+------|
 *      |LShift|   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   N  |   M  |  W  |   V  |   Z  |RShift|
 *      `-----------------------------------------/       /     \      \-----------------------------------------'
 *                        |LGUI  |D_LOWER| LAlt | /Space  /       \Enter \  |BackSP|D_RAISE| RGUI|
 *                        |      |      |      |/       /         \      \ |      |      |      |
 *                        `----------------------------'           '------''--------------------'
 */

 [_DVORAK] = LAYOUT(
       KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
LCTL_T(KC_TAB), KC_QUOT, KC_COMM, KC_DOT,    KC_P,  KC_Y,                       KC_F,   KC_G  ,  KC_C ,  KC_K  ,  KC_R  ,    KC_MINS,
       KC_LBRC,  KC_A,   KC_O,    KC_E,    KC_U,    KC_I,                       KC_D,   KC_H,    KC_T,    KC_N,   KC_S ,     KC_RBRC,
       KC_LSFT, KC_SCLN,   KC_Q,    KC_J,    KC_K,  KC_X,  KC_BSLS , KC_SLSH ,  KC_B,    KC_M,    KC_W,     KC_V ,  KC_Z,  KC_RSFT,
                             KC_LGUI, MO(_D_LOWER), KC_LALT, KC_SPC, KC_ENT, KC_BSPC, MO(_D_RAISE), KC_RGUI
),
/* _D_LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Br- |  Br+ |      |      |     |       |                    | Vol- |  Vol+ | Prev | Play | Next |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LGUI  |D_LOWER| LAlt | /Space  /       \Enter \  |BackSP|ADJUST| RGUI|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_D_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_BRID,   KC_BRIU,_______,_______,_______,_______,                     KC_VOLD, KC_VOLU ,KC_MPRV,KC_MPLY, KC_MNXT, _______,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, TO(_ADJUST), _______
),
/* _D_RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |LCTRL|LShift| LAlt |      |       |                    |      |      |      |      | Prnt |  Ins |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |  Up  |   8  |   9  |  0   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Home | Left | Down | Right|     |  End |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LGUI  |ADJUST| LAlt | /Space  /       \Enter \  |BackSP|D_RAISE| RGUI|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_D_RAISE] = LAYOUT(
  _______,KC_LCTL, KC_LSFT, KC_LALT, _______, _______,                     _______, _______, _______, _______, KC_PSCR , KC_INS,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_UP,    KC_8,    KC_9,   KC_0 ,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_HOME, KC_LEFT , KC_DOWN, KC_RGHT,_______, KC_END,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, TO(_ADJUST), _______,  _______, _______,  KC_DEL, _______, _______
)
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
//     return state;
// }

static void render_logo(void) {

    static const char dragon [] PROGMEM = {
  // 'egm dragon', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc,
0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
0xfc, 0xf8, 0x18, 0x18, 0x08, 0x08, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
0xf0, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x60,
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x1c, 0x14, 0x24, 0xa4, 0xc4, 0x44, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x98, 0x90, 0x90, 0xb0, 0x30, 0x70, 0xf4, 0xc7, 0xc3, 0x83,
0xc3, 0xe3, 0xe1, 0x81, 0x81, 0x83, 0xc3, 0xe3, 0xe3, 0xe3, 0xe3, 0xf3, 0xf3, 0xf3, 0xf3, 0xe7,
0xe7, 0xe7, 0xe7, 0xcf, 0xcf, 0xdf, 0xdf, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xdf, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xc0, 0x80, 0x00, 0x06, 0x06, 0x0e, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f, 0x1f, 0xff, 0xff, 0xff,
0xfe, 0xfc, 0x78, 0x70, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x1e, 0x3e, 0xff, 0xe3, 0xe1, 0xc1, 0xc1,
0xc3, 0xc2, 0x82, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x86, 0x06, 0x06, 0x05, 0x85, 0x84, 0x84, 0x84, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x67, 0x7f, 0x7f, 0xff, 0xff, 0xff,
0xbf, 0xbf, 0xbf, 0xff, 0xff, 0xf3, 0xf7, 0xa7, 0x29, 0x21, 0x21, 0x21, 0x31, 0x31, 0x31, 0x31,
0x61, 0x63, 0x23, 0x07, 0x0f, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xf9, 0xf9, 0xe3,
0xe3, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x9c, 0x9c, 0x1c, 0x0e, 0x0e, 0x0f, 0x8f, 0x8f, 0xdf, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f,
0xff, 0xff, 0xf0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x23,
0x73, 0x7b, 0x5f, 0x5f, 0x1f, 0x1f, 0x1f, 0x1f, 0xbf, 0xfe, 0xfc, 0xfc, 0xfc, 0xf6, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x20, 0x20, 0x23, 0x20, 0x10, 0x99, 0x06, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x0f,
0x1f, 0x1f, 0x1f, 0x0f, 0x07, 0x27, 0x27, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x07, 0x07, 0x07, 0x03, 0x02, 0x06,
0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3e, 0x20, 0x20, 0x30, 0x30, 0x20, 0x20, 0x3c, 0x00, 0x00, 0x00, 0x00
};

    oled_write_raw_P(dragon, sizeof(dragon));
}
char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}
//new

bool oled_task_user(void) {

  if (is_keyboard_master()) {
    // Host Keyboard Layer Status

    switch (get_highest_layer(layer_state)) {
  case _QWERTY:
    oled_write_P(PSTR("Layer: Default\n"), false);
    break;
  case _RAISE:
    oled_write_P(PSTR("Layer: Raise\n"), false);
    break;
  case _LOWER:
    oled_write_P(PSTR("Layer: Lower\n"), false);
    break;
  case _DVORAK:
    oled_write_P(PSTR("Layer: Dvorak\n"), false);
    break;
  case _D_RAISE:
    oled_write_P(PSTR("Layer: D_Raise\n"), false);
    break;
  case _D_LOWER:
    oled_write_P(PSTR("Layer: D_Lower\n"), false);
    break;
  case _ADJUST:
    oled_write_P(PSTR("Layer: Adjust\n"), false);
    break;
  case _D_ADJUST:
    oled_write_P(PSTR("Layer: D_Adjust\n"), false);
    break;
  default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);

  } else {
      render_logo();
  }
    return false;
}
#endif // OLED_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
