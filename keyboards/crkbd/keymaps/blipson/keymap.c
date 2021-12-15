/*
Copyright 2019 @foostan
Copyright 2020 Ben Lipson <ben.j.lipson@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,  KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           MO(1),  KC_LGUI, KC_SPC,     KC_SPC,  KC_RALT, MO(2)
                                       //`--------------------------'  `--------------------------'

   ),

   [1] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,  KC_EXLM, KC_AT,  KC_HASH,  KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_UP,   KC_LPRN, KC_RPRN, KC_BSLS,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, KC_ENT,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_INS,  KC_END,  KC_HOME, KC_PGDN,  KC_PGUP, KC_RSFT,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _______, KC_LGUI, KC_SPC,    KC_SPC,  KC_RALT,  MO(3)
                                       //`--------------------------'  `--------------------------'
   ),

   [2] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, KC_ASTR, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_BSLS, KC_PIPE, KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           MO(3),  KC_LGUI,  KC_SPC,    KC_SPC, KC_RALT, _______
                                       //`--------------------------'  `--------------------------'
   ),

   [3] = LAYOUT_split_3x6_3(
   //,-------------------------------------------------------------------------------.                    ,------------------------------------------------------------------.
       KC_ESC,    KC_F1,       KC_F2,         KC_F3,          KC_F4,     KC_F5,                            KC_F6,       KC_F7,       KC_F8,       KC_F9,   KC_F10,  RESET,
   //|----------+------------+--------------+---------------+-----------+------------|                    |------------+------------+------------+--------+--------+---------|
       KC_LCTL,   A(KC_F12),   A(G(KC_LEFT)), A(G(KC_RIGHT)), S(KC_F6),  C(S(KC_D)),                       C(S(KC_R)),  G(KC_LBRC),  G(KC_RBRC),  KC_F11,  KC_F12, KC_MPLY,
   //|----------+------------+--------------+---------------+-----------+------------|                    |------------+------------+------------+--------+--------+---------|
       G(KC_F2), A(G(KC_F)),  KC_MUTE,       KC__VOLDOWN,     KC__VOLUP, G(KC_GRV),                        C(G(KC_G)),  KC_TAB,      S(KC_TAB),   KC_BRID, KC_BRIU, KC_CAPS,
   //|----------+------------+--------------+---------------+-----------+------------+--------|  |--------+------------+------------+------------+--------+--------+---------|
                                                             _______,    KC_LGUI,     KC_SPC,     KC_SPC,   KC_RALT,     _______
                                                         //`----------------------------------'  `-------------------------------'
   )
 };

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_left()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
    oled_write_P(PSTR("I love Marce"), false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
