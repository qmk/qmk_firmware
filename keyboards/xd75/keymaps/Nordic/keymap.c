/* Copyright 2017 Benjamin Kesselring
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
#include "xd75.h"

#ifndef KEYMAP_NORDIC_H
#define KEYMAP_NORDIC_H

#include "keymap.h"

// Alt gr
#define ALGR(kc) RALT(kc)
#define NO_ALGR KC_RALT

// Normal characters
#define NO_HALF	KC_GRV
#define NO_PLUS	KC_MINS
#define NO_ACUT	KC_EQL

#define NO_AM	KC_LBRC
#define NO_QUOT	KC_RBRC // this is the "umlaut" char on Nordic keyboards, Apple layout
#define NO_AE	KC_SCLN
#define NO_OSLH	KC_QUOT
#define	NO_APOS	KC_NUHS

#define NO_LESS	KC_NUBS
#define NO_MINS KC_SLSH

// Shifted characters
#define NO_SECT LSFT(NO_HALF)
#define NO_QUO2	LSFT(KC_2)
#define NO_BULT LSFT(KC_4)
#define NO_AMPR	LSFT(KC_6)
#define NO_SLSH LSFT(KC_7)
#define NO_LPRN	LSFT(KC_8)
#define NO_RPRN	LSFT(KC_9)
#define NO_EQL	LSFT(KC_0)
#define NO_QUES	LSFT(NO_PLUS)
#define NO_GRV	LSFT(NO_ACUT)

#define NO_CIRC LSFT(NO_QUOT)

#define NO_GRTR	LSFT(NO_LESS)
#define NO_SCLN LSFT(KC_COMM)
#define NO_COLN LSFT(KC_DOT)
#define NO_UNDS LSFT(NO_MINS)

// Alt Gr-ed characters
#define NO_AT	ALGR(KC_2)
#define NO_PND	ALGR(KC_3)
#define NO_DLR	ALGR(KC_4)
#define NO_LCBR ALGR(KC_7)
#define NO_LBRC ALGR(KC_8)
#define NO_RBRC ALGR(KC_9)
#define NO_RCBR	ALGR(KC_0)
#define NO_PIPE ALGR(KC_NUBS)

#define NO_EURO ALGR(KC_E)
#define NO_TILD ALGR(NO_QUOT)

#define NO_BSLS ALGR(KC_MINS)
#define NO_MU 	ALGR(KC_M)

#endif

#ifndef KEYMAP_NORWEGIAN_H
#define KEYMAP_NORWEGIAN_H

#include "keymap_nordic.h"

// There are slight differrences in the keyboards in the nordic contries

// Norwegian redifinitions from the nordic keyset
#undef NO_ACUT
#define NO_ACUT	ALGR(NO_BSLS)  // ´
#undef NO_AE
#define NO_AE	KC_QUOT  // æ
#undef NO_BSLS
#define NO_BSLS KC_EQL  // '\'
#undef NO_CIRC
#define NO_CIRC LSFT(KC_RBRC)  // ^
#undef NO_GRV
#define NO_GRV	LSFT(NO_BSLS)  //
#undef NO_OSLH
#define NO_OSLH	KC_SCLN  // ø
#undef NO_PIPE
#define NO_PIPE KC_GRV  // |

// Additional norwegian keys not defined in the nordic keyset
#define NO_AA	KC_LBRC  // å
#define NO_ASTR LSFT(KC_BSLS)  // *

// Norwegian unique MAC characters
#define NO_ACUT_MAC KC_EQL  // =
#define NO_APOS_MAC KC_NUBS  // '
#define NO_AT_MAC   KC_BSLS  // @
#define NO_BSLS_MAC ALGR(LSFT(KC_7)) // '\'
#define NO_DLR_MAC  LSFT(KC_4) // $
#define NO_GRV_MAC ALGR(NO_BSLS) // `
#define NO_GRTR_MAC LSFT(KC_GRV)  // >
#define NO_LCBR_MAC ALGR(LSFT(KC_8))  // }
#define NO_LESS_MAC KC_GRV  // >
#define NO_PIPE_MAC ALGR(KC_7)  // |
#define NO_RCBR_MAC ALGR(LSFT(KC_9))  // }

#endif


// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

// Layer shorthand
#define _QW 0
#define _FN 1
#define _NP 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY - MIT ENHANCED / GRID COMPATIBLE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | +      | \      | PRINT  | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | Å      | ¨      | BACKSP | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAPS   | A      | S      | D      | F      | G      | H      | J      | K      | L      | Ø      | Æ      | '      | ENTER  | PG DN  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | -      | RSHIFT | HOME   | UP     | END    |
 * |--------+--------+--------+--------+--------+- 3u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | <      | FN     | LALT   | XXXXX  . SPACE  . XXXXX  | RALT   | FN     | WIN    | VOL DN | VOL UP | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
	
 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,    KC_0,    NO_PLUS, NO_BSLS, KC_PSCR, KC_DEL  },
  { KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,    NO_AA,   NO_QUOT, KC_BSPC, KC_PGUP },
  { KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,    NO_OSLH, NO_AE,   NO_APOS, KC_ENT,  KC_PGDN },
  { KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,  NO_MINS, KC_RSFT, KC_HOME, KC_UP,   KC_END  },
  { KC_LCTL, NO_LESS , MO(_FN), KC_LALT, _______,  KC_SPC,  _______,  NO_ALGR, MO(_NP), KC_LGUI, KC_VOLU, KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT  },
 },


/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |   |    | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | INS    | SCRLCK |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        | PAUSE  |
 * |--------+--------+--------+--------+--------+- 3u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        | XXXXXX .        . XXXXXX |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FN] = { /* FUNCTION */
  { NO_PIPE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_SLCK  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
 
/* NUMPAD
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |   7    |   8    |   9    |  /     | BKSP   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |   4    |   4    |   5    |  *     | ENTER  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |   1    |   1    |   2    |        |        |        |
 * |--------+--------+--------+--------+--------+- 3u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        | XXXXXX .        . XXXXXX |        |        |        |   0    |   -    |  +     |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_NP] = { /* NUMPAD FUNCTION */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_7   , KC_8   , KC_9   , NO_SLSH, KC_BSPC, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_4   , KC_5   , KC_6   , NO_CIRC, KC_ENT , _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1   , KC_2   , KC_3   , _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0   , NO_MINS, NO_PLUS, _______, _______ },
 },

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};