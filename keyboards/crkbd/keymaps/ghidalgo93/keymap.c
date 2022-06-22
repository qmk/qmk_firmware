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

enum layers {
    _QWERTY = 0,
    _NAV,
    _RSYM,
    _LSYM,
    _FUN,
    _NUM,
    _MED, 
    _ALWAYS
};

// Left-hand mods
#define GUI_A LGUI_T(KC_A)
#define CTL_S LCTL_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define RSYM_F LT(_RSYM, KC_F)
#define ALT_Z LALT_T(KC_Z)
#define MED MO(_MED)
#define NAV MO(_NAV)

// Right-hand mods
#define LSYM_J LT(_LSYM, KC_J)
#define SFT_K RSFT_T(KC_K)
#define CTL_L LCTL_T(KC_L)
#define GUI_SCLN LGUI_T(KC_SCLN)
#define ALT_SLSH LALT_T(KC_SLSH)
#define ALW_SPC LT(_ALWAYS, KC_SPC)
#define NUM MO(_NUM)
#define FUN MO(_FUN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
      _______, KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     _______, 
      _______, GUI_A,    CTL_S,   SFT_D,   RSYM_F,  KC_G,                                        KC_H,    LSYM_J,  SFT_K,   CTL_L,  GUI_SCLN, _______, 
      _______, ALT_Z,    KC_X,    KC_C,    KC_V,    KC_B,    																		 KC_N,    KC_M,    KC_COMM, KC_DOT, ALT_SLSH, _______, 
      				                             				  MED,     NAV,     KC_BSPC, ALW_SPC, NUM,     FUN
    ),
     [_NAV] = LAYOUT_split_3x6_3(
       _______, _______, _______, _______, _______, _______,                                     _______, KC_PGDN, KC_PGUP, _______, KC_DEL,  _______, 
       _______, _______, _______, _______, _______, _______,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
       _______, _______, _______, _______, _______, _______, 																	   _______, KC_END,  KC_HOME, _______, _______, _______, 
                                  									_______, XXXXXXX, _______, _______, _______, _______
     ),
     [_RSYM] = LAYOUT_split_3x6_3(
       _______, _______, _______, _______, _______, _______,                                     _______, KC_TILD, KC_SLSH, KC_QUOT, _______, _______,
       _______, KC_CIRC, KC_ASTR, KC_AMPR, XXXXXXX, _______,                                     KC_HASH, KC_MINS, KC_PIPE, KC_DQUO, KC_DLR,  _______,
       _______, _______, _______, _______, _______, _______, 																		 _______, KC_UNDS, KC_BSLS, KC_GRV,  _______, _______,
                              											_______, _______, _______, _______, _______, _______ 
     ),
     [_LSYM] = LAYOUT_split_3x6_3(
       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, 
       _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,                                       _______, XXXXXXX, KC_EQL,  KC_PPLS, KC_PERC, _______, 
       _______, _______, KC_EXLM, KC_LBRC, KC_RBRC, _______,  																	 _______, _______, _______, _______, _______, _______,  
                                  				 					_______, _______, _______, _______, _______, _______
     ),
     [_FUN] = LAYOUT_split_3x6_3(
       _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F12,                                      _______, _______, _______, _______, _______, _______,
       _______, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,                                      _______, _______, _______, _______, _______, _______,
       _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F10,   																	 _______, _______, _______, _______, _______, _______,
                                   				 					_______, _______, _______, _______, _______, XXXXXXX
     ),
     [_NUM] = LAYOUT_split_3x6_3(
       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_1, 		KC_2, 	 KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8, 	  KC_9,    KC_0,    _______, 
       _______, _______, _______, _______, _______, _______, 																		 _______, _______, _______, _______, _______, _______,
                                  									_______, _______, _______, _______, XXXXXXX, _______
     ),
     [_MED] = LAYOUT_split_3x6_3(
       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, RESET,
       _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                     _______, KC_VOLD, KC_VOLU, _______, _______, _______,
       _______, _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, 																		 _______, _______, _______, _______, _______, _______,
                                  				 					XXXXXXX, _______, _______, _______, _______, _______
     ),
     [_ALWAYS] = LAYOUT_split_3x6_3(
       _______, _______, _______, KC_COLN, KC_ESC,  _______,                                     _______, _______, _______, _______, _______, _______,
       _______, _______, KC_PERC, KC_SLSH, KC_ENT,  _______,                                     _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, KC_EXLM, _______, 																		 _______, _______, _______, _______, _______, _______,
                                  				 					_______, _______, KC_TAB,  XXXXXXX, _______, _______
     ),
};

/* #ifdef OLED_DRIVER_ENABLE */
/* oled_rotation_t oled_init_user(oled_rotation_t rotation) { */
/*   if (!is_master) { */
/*     return OLED_ROTATION_180;  // flips the display 180 degrees if offhand */
/*   } */
/*   return rotation; */
/* } */

/* static void render_fifi_logo(void) { */
/*     static const char PROGMEM fifi_logo[] = { */
/* 			// put fifi logo here */
/*     }; */
/*     oled_write_raw_P(fifi_logo, sizeof(fifi_logo)); */
/* } */

/* static void render_qmk_logo(void) { */
/*   static const char PROGMEM qmk_logo[] = { */
/*     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94, */
/*     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4, */
/*     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0}; */

/*   oled_write_P(qmk_logo, false); */
/* } */

/* static void render_status(void) { */
/*     // QMK Logo and version information */
/*     render_qmk_logo(); */
/*     oled_write_P(PSTR("Fifi\n\n"), false); */

/*     // Host Keyboard Layer Status */
/*     oled_write_P(PSTR("Layer: "), false); */
/*     switch (get_highest_layer(layer_state)) { */
/*         case _QWERTY: */
/*             oled_write_P(PSTR("Default\n"), false); */
/*             break; */
/*         case _NAV: */
/*             oled_write_P(PSTR("Nav\n"), false); */
/*             break; */
/*         case _RSYM: */
/*             oled_write_P(PSTR("Right Sym\n"), false); */
/*             break; */
/*         case _LSYM: */
/*             oled_write_P(PSTR("Left Sym\n"), false); */
/*             break; */
/*         case _FUN: */
/*             oled_write_P(PSTR("Functions\n"), false); */
/*             break; */
/*         case _NUM: */
/*             oled_write_P(PSTR("Numbers\n"), false); */
/*             break; */
/*         case _MED: */
/*             oled_write_P(PSTR("Media\n"), false); */
/*             break; */
/*         case _GAME: */
/*             oled_write_P(PSTR("Game!\n"), false); */
/*             break; */
/*         case _ALWAYS: */
/*             oled_write_P(PSTR("Always\n"), false); */
/*             break; */
/*         default: */
/*             oled_write_P(PSTR("Undefined\n"), false); */
/*     } */
/* } */

/* void oled_task_user(void) { */
/*     if (is_keyboard_master()) { */
/*         render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc) */
/*     } else { */
/*         render_fifi_logo(); */
/*     } */
/* } */

/* #endif // OLED_DRIVER_ENABLE */
