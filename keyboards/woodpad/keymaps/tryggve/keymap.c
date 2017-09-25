/*
 * Copyright 2017 Michael Atkinson
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
#include "woodpad.h"

/* Layers */
#define _PD1 0
#define _PD2 1
#define _MIDI 2
#define _NUMLCK 3

/* Macros */
#define M_DSP0 M(0)
#define M_DSP1 M(1)
//#define M_MODE M(2)
#define M_BANG M(3)
#define M_MBNG M(4)
#define M_TOGG M(5)
#define M_LPLS M(6)
#define M_LMNS M(7)
#define M_LAST M(8)
#define M_SEND M(9)
#define M_RECV M(10)
#define M_HSLD M(11)
#define M_VSLD M(12)
#define M_HRDO M(13)
#define M_VRDO M(14)
#define M_INLT M(15)
#define M_OULT M(16)
#define M_TRGR M(17)
#define M_FLOT M(18)
#define M_COSC M(19)
#define M_PHAS M(20)
#define M_LLNE M(21)
#define M_LINE M(22)
#define M_METR M(23)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_PD1] = KEYMAP(
  KC_NLCK, M_DSP0,  M_DSP1,  LCTL(KC_E),  \
  M_BANG,  M_TOGG,  M_RECV,  M_LAST,  \
  LCTL(4), LCTL(5), M_SEND,  M_LMNS,  \
  LCTL(1), LCTL(2), LCTL(3), M_LPLS,  \
  _______, _______, _______, M_MBNG   \
),
[_PD2] = KEYMAP(
  _______, M_LINE,  M_LLNE,  _______, \
  M_COSC,  M_PHAS,  M_METR,  _______, \
  M_INLT,  M_OULT,  M_TRGR,  M_FLOT,  \
  M_HSLD,  M_VSLD,  M_HRDO,  M_VRDO,  \
  _______, _______, _______, _______  \
),
[_MIDI] = KEYMAP(
  _______, _______, _______, MI_ALLOFF, \
  MI_C_1,  MI_Cs_1, MI_D_1,  MI_Ds_1, \
  MI_Gs,   MI_A,    MI_As,   MI_B,    \
  MI_E,    MI_F,    MI_Fs,   MI_G,    \
  MI_C,    MI_Cs,   MI_D,    MI_Ds    \
),
[_NUMLCK] = KEYMAP(
  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
  KC_P4,   KC_P5,   KC_P6,   KC_BSPC, \
  KC_P1,   KC_P2,   KC_P3,   KC_TAB,  \
  KC_LALT, KC_P0,   KC_PDOT, KC_PENT  \
)
};

void numlock_led_on(void) {
  PORTF |= (1<<7);
}

void numlock_led_off(void) {
  PORTF &= ~(1<<7);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
    switch(id) {
      case 0:
        return MACRO(D(LCTL), T(SLSH), U(LCTL));
      case 1:
        return MACRO(D(LCTL), T(DOT), U(LCTL));
      case 2:
        // NOT USED
        return MACRO_NONE;
      case 3:
        return MACRO(D(LCTL), D(LSFT), T(B), U(LSFT), U(LCTL)) ;
      case 4:
        return MACRO(D(LCTL), T(2), U(LCTL), T(B), T(A), T(N), T(G));
      case 5:
        return MACRO(D(LCTL), D(LSFT), T(T), U(LSFT), U(LCTL)) ;
      case 6:
        return MACRO(D(LCTL), T(2), U(LCTL), D(LSFT), T(EQL), T(GRV), U(LSFT));
      case 7:
        return MACRO(D(LCTL), T(2), U(LCTL), T(MINS), D(LSFT), T(GRV), U(LSFT));
      case 8:
        return MACRO(D(LCTL), T(2), U(LCTL), D(LSFT), T(8), T(GRV), U(LSFT));
      case 9:
        return MACRO(D(LCTL), T(2), U(LCTL), T(S), T(SPC));
      case 10:
        return MACRO(D(LCTL), T(2), U(LCTL), T(R), T(SPC));
      case 11:
        return MACRO(D(LCTL), D(LSFT), T(H), U(LSFT), U(LCTL)) ;
      case 12:
        return MACRO(D(LCTL), D(LSFT), T(V), U(LSFT), U(LCTL)) ;
      case 13:
        return MACRO(D(LCTL), D(LSFT), T(I), U(LSFT), U(LCTL)) ;
      case 14:
        return MACRO(D(LCTL), D(LSFT), T(D), U(LSFT), U(LCTL)) ;
      case 15:
        return MACRO(D(LCTL), T(2), U(LCTL), T(I), T(N), T(L), T(E), T(T));
      case 16:
        return MACRO(D(LCTL), T(2), U(LCTL), T(O), T(U), T(T), T(L), T(E), T(T));
      case 17:
        return MACRO(D(LCTL), T(2), U(LCTL), T(T), T(SPC));
      case 18:
        return MACRO(D(LCTL), T(2), U(LCTL), T(F), T(SPC));
      case 19:
        return MACRO(D(LCTL), T(2), U(LCTL), T(O), T(S), T(C), D(LSFT), T(GRV), U(LSFT));
      case 20:
        return MACRO(D(LCTL), T(2), U(LCTL), T(P), T(H), T(A), T(S), T(O), T(R), D(LSFT), T(GRV), U(LSFT));
      case 21:
        return MACRO(D(LCTL), T(2), U(LCTL), T(L), T(I), T(N), T(E), D(LSFT), T(GRV), U(LSFT));
      case 22:
        return MACRO(D(LCTL), T(2), U(LCTL), T(L), T(I), T(N), T(E));
      case 23:
        return MACRO(D(LCTL), T(2), U(LCTL), T(M), T(E), T(T), T(R), T(O));
    }
  }
  return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // TODO implement some stuff here, like numlock and LEDs and such
  return true;
}

void matrix_init_user(void) {
  // set Numlock LED to output and low
  DDRF  |=  (1<<7);
  PORTF &= ~(1<<7);
}
