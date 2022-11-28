/* Copyright 2019 George Koenig
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "ridingqwerty.h"

/*                                                         MinOrca
        ┏━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┯━━━━━━━━┓
        ┃   ⎋    │   Q    │   W    │   E    │   R    │   T    │   Y    │   U    │   I    │   O    │   P    │  ❦ ⌫   ┃
        ┠────────┴─┬──────┴─┬──────┴─┬──────┴─┬──────┴─┬──────┴─┬──────┴─┬──────┴─┬──────┴─┬──────┴─┬──────┴────────┨
        ┃   ¶ ⇥    │   A    │   S    │   D    │   F    │   G    │   H    │   J    │   K    │   L    │     🔢 ↵      ┃
        ┠──────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬───────────┨
        ┃    " ⇧       │   Z    │   X    │   C    │   V    │   B    │   N    │   M    │   ,    │  𝔽 .   │    ⇧ /    ┃
        ┠──────────┬───┴──────┬─┴────────┼────────┴────────┴──┬─────┴────────┴─────┬──┴───────┬┴───────┬┴───────────┨
        ┃   { ⎈    │   [ ⌘    │  (  ⌥    │       🔢 ␣         │       ★ ␣          │   ) ⌥    │  ] ⌘   │    } ⎈     ┃
        ┗━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━┷━━━━━━━━┷━━━━━━━━━━━━┛
*/

#define LAYOUT_minorca( \
    KA00, KA01, KA02, KA03, KA04, KA05, KA06, KA07, KA08, KA09, KA10, KA11, \
    KB00,  KB01, KB02, KB03, KB04, KB05, KB06, KB07, KB08, KB09,    KB11,   \
    KC00,    KC02, KC03, KC04, KC05, KC06, KC07, KC08, KC09, KC10,   KC11,  \
    KD00,  KD02,  KD03,          KD04, KD07,           KD09,  KD10,  KD11   \
) { \
  {  KA00,  KA01,   KA02,  KA03,  KA04,  KA05,   KA06,   KA07,  KA08,   KA09,  KA10,   KA11  }, \
  {  KB00,  KB01,   KB02,  KB03,  KB04,  KB05,   KB06,   KB07,  KB08,   KB09,  KC_NO,  KB11  }, \
  {  KC00,  KC_NO,  KC02,  KC03,  KC04,  KC05,   KC06,   KC07,  KC08,   KC09,  KC10,   KC11  }, \
  {  KD00,  KC_NO,  KD02,  KD03,  KD04,  KC_NO,  KC_NO,  KD07,  KC_NO,  KD09,  KD10,   KD11  } \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = {
        {QK_GESC,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     SC(BSPC) },
        {ED(TAB),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     XXXXXXX,  NM(SCLN) },
        {LS(QUOT), XXXXXXX,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  FK(DOT),  RS(SLSH) },
        {LC(ESC),  XXXXXXX,  LG(LBRC), LA(RBRC), NM(BSPC), XXXXXXX,  XXXXXXX,  SM(SPC),  XXXXXXX,  RA(MINS), RG(EQL),  RC(ENT)  }
/*
      //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┤
      //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
      //├─────────────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┴────────┼────────┼────────┤
      //└─────────────────┴────────┴────────┴─────────────────┴─────────────────┴─────────────────┴────────┴────────┘
*/


    },
#ifdef UNICODE_H
    [_RUNE] = {
        {KC_ESC,  X(INGWZ), X(WUNJO),  X(EHWAZ), X(RAIDO), X(TIWAZ), X(IWAZ),  X(UR),    X(ISAZ),  X(ETHEL), X(PERTH), SC(BSPC) },
        {ED(TAB), X(ANSUZ), X(SOWIL),  X(DAGAZ), X(FE),    X(GEBO),  X(HAGLZ), X(JERAN), X(KAUNA), X(LAUKZ), XXXXXXX,  NM(SCLN) },
        {MT_QUOT, XXXXXXX,  X(ALGIZ),  X(THURS), X(KAUNA), X(WUNJO), X(BEORC), X(NAUDZ), X(MANNZ), KC_COMM,  FK(DOT),  RS(SLSH) },
        {LC(ESC), XXXXXXX,  LG(LBRC),  LA(RBRC), NM(BSPC), XXXXXXX,  XXXXXXX,  SM(SPC),  XXXXXXX,  RA(MINS), RG(EQL),  RC(ENT)  }
    },
#endif
    [_EDITOR] = {
      //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
        {KC_GRV,  _______, _______, KC_END,  _______, KC_F5,   _______, _______, KC_INS,  _______, KC_PGUP, KC_DEL  },
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┤
        {_______, KC_HOME, _______, KC_DEL,  _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_SCLN },
      //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
        {_______, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_PGDN, _______, KC_SCLN, KC_QUOT, KC_BSLS },
      //├─────────────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┴────────┼────────┼────────┤
        {_______, XXXXXXX, _______, _______, KC_EQL,  XXXXXXX, XXXXXXX, KC_MINS, XXXXXXX, KC_COLN, KC_DQUO, KC_PIPE }
      //└─────────────────┴────────┴────────┴─────────────────┴─────────────────┴─────────────────┴────────┴────────┘
    },
    [_NUMBER] = {
      //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
        {KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┤
        {_______, KC_4,    KC_5,    KC_6,    KC_PAST, _______, KC_PPLS, KC_4,    KC_5,    KC_6,    XXXXXXX, _______ },
      //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
        {_______, KC_7,    KC_8,    KC_9,    KC_SLSH, _______, _______, KC_MINS, KC_1,    KC_2,    KC_3,    _______ },
      //├─────────────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┴────────┼────────┼────────┤
        {_______, XXXXXXX, KC_0,    _______, _______, XXXXXXX, XXXXXXX, KC_0,    XXXXXXX, KC_DOT,  _______, _______ }
      //└─────────────────┴────────┴────────┴─────────────────┴─────────────────┴─────────────────┴────────┴────────┘
    },
    [_SYMBOL] = {
      //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
        {KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL  },
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┤
        {_______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, XXXXXXX, _______ },
      //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
        {_______, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, KC_SCLN, KC_QUOT, KC_BSLS },
      //├─────────────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┴────────┼────────┼────────┤
        {_______, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, KC_COLN, KC_DQUO, KC_PIPE }
      //└─────────────────┴────────┴────────┴─────────────────┴─────────────────┴─────────────────┴────────┴────────┘
    },
    [_SECRET] = {
      //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
        {QK_BOOT, _______, _______, _______, SECRET0, SECRET1, _______, _______, _______, _______, VERSION, _______ },
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┤
        {_______, SECRET4, SECRET8, DB_TOGG, _______, _______, _______, _______, _______, SECRET7, XXXXXXX, MAKE    },
      //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
        {_______, XXXXXXX, SECRET6, _______, SECRET2, SECRET5, _______, _______, SECRET3, _______, _______, _______ },
      //├─────────────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┴────────┼────────┼────────┤
        {_______, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, _______ }
      //└─────────────────┴────────┴────────┴─────────────────┴─────────────────┴─────────────────┴────────┴────────┘
    },
    [_F_KEYS] = {
      //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
        {KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11  },
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┤
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______ },
      //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┤
        {_______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
      //├─────────────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┴────────┼────────┼────────┤
        {_______, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, _______ }
      //└─────────────────┴────────┴────────┴─────────────────┴─────────────────┴─────────────────┴────────┴────────┘
    },
};
