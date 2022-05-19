/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include <stdio.h>
#include "ocean_dream.h"

// Ocean Dream
//#    ifdef OCEAN_DREAM_ENABLE
        //render_stars();
//        is_calm = (record->event.pressed) ? true : false;
//#    endif

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LSFT_T(KC_D)
#define HOME_F LCTL_T(KC_F)

// Right-hand home row mods
#define HOME_J RCTL_T(KC_J)
#define HOME_K RSFT_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        TO(0),  HOME_A,  HOME_S,  HOME_D,  HOME_F,    KC_G,                         KC_H,  HOME_J,  HOME_K,  HOME_L, HOME_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_DEL, LT(1, KC_SPC), OSL(1), OSL(2),  LT(2, KC_SPC), KC_ENT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_CIRC, KC_HASH, KC_LPRN, KC_RPRN,  KC_DLR,                      KC_BSLS,   KC_P7,   KC_P8,   KC_P9, KC_PPLS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        TO(0), KC_EXLM,   KC_AT, KC_LCBR, KC_RCBR,  KC_EQL,                      KC_SLSH,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_GRV, KC_PERC, KC_LBRC, KC_RBRC, KC_AMPR,                      KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PDOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,   TO(1),    KC_LCTL, KC_TRNS,   KC_P0
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,   TO(3),  KC_INS,   KC_UP, KC_HOME, KC_PGUP,                      KC_VOLU,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        TO(0), C(KC_A), KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                      KC_VOLD,   KC_F4,   KC_F5,   KC_F6,  KC_F11,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, C(KC_Z), C(KC_X), C(KC_C), C(KC_V),  KC_ESC,                      KC_MUTE,   KC_F1,   KC_F2,   KC_F3,  KC_F12,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS, S(KC_TAB),    TO(2), KC_LCTL, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_F1,   KC_F2,   KC_F4,  KC_F11,  RESET,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_X,    KC_Z,    KC_L,    KC_C, KC_BRIU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_B,                         KC_5,    KC_6,    KC_7,    KC_8,    KC_9, KC_BRID,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_F3,  KC_SPC,   KC_F5,      TO(0),   TO(4),  KC_ENT
                                      //`--------------------------'  `--------------------------'

  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       MI_D_2,  MI_E_2, MI_Fs_2, MI_Gs_2, MI_Bb_2,  MI_C_3,                        MI_D_3, MI_E_3, MI_Fs_3, MI_Gs_3, MI_Bb_3,  MI_C_4,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MI_Cs_2, MI_Eb_2,  MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,                      MI_Cs_3, MI_Eb_3,  MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       MI_C_2,  MI_D_2,  MI_E_2, MI_Fs_2, MI_Gs_2, MI_Bb_2,                       MI_C_3,  MI_D_3,  MI_E_3, MI_Fs_3, MI_Gs_3, MI_Bb_3,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MI_TRNSD, MI_TRNSU, MI_TOG,     TO(0), MI_OCTD, MI_OCTU
                                      //`--------------------------'  `--------------------------'

  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8
#define L_MIDI 10

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Numpad"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case L_ADJUST:
            oled_write_ln_P(PSTR("Minecraft"), false);
            break;
        case L_MIDI:
            oled_write_ln_P(PSTR("MIDI"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Default"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
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

//void oled_render_logo(void) {
//    static const char PROGMEM crkbd_logo[] = {
//        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
//        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
//        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
//        0};
//    oled_write_P(crkbd_logo, false);
//}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        //oled_render_logo();
        if (is_oled_on()) render_stars();
    }
    return false;
}

//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//  if (record->event.pressed) {
//    set_keylog(keycode, record);
//  }
//  return true;
//}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
#ifdef OCEAN_DREAM_ENABLE
            is_calm = (record->event.pressed) ? true : false;
#endif
            break;
    }
    return true;
}
#endif // OLED_ENABLE
