/* Copyright 2018-2019 eswai <@eswai>
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

void nicola_type(void);
void nicola_clear(void);

void nicola_mode(uint16_t, keyrecord_t *);

void nicola_on(void);
void nicola_off(void);
bool nicola_state(void);

bool process_nicola(uint16_t, keyrecord_t *);
void set_nicola(uint8_t);

typedef enum nicola_keycodes {
  NG_Q = SAFE_RANGE,
  NG_W,
  NG_E,
  NG_R,
  NG_T,
  NG_Y,
  NG_U,
  NG_I,
  NG_O,
  NG_P,

  NG_A,
  NG_S,
  NG_D,
  NG_F,
  NG_G,
  NG_H,
  NG_J,
  NG_K,
  NG_L,
  NG_SCLN,

  NG_Z,
  NG_X,
  NG_C,
  NG_V,
  NG_B,
  NG_N,
  NG_M,
  NG_COMM,
  NG_DOT,
  NG_SLSH,

  NG_SHFTL,
  NG_SHFTR,
} NGKEYS;

#define NG_SAFE_RANGE SAFE_RANGE+32

enum keymap_layers {
  _QWERTY = 0,
// NICOLA親指シフト
  _NICOLA, // NICOLA親指シフト入力レイヤー
// NICOLA親指シフト
  _FUNC,
// for left control
  _LCTL,
  _MOUSE
};

enum custom_keycodes {
// NICOLA親指シフト
  KC_QWERTY = NG_SAFE_RANGE, // SAFE_RANGE を NG_SAFE_RANGE に変更してください
// NICOLA親指シフト
  KC_EISU,
  KC_KANA2
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define _____ KC_TRNS
#define XXXXX KC_NO

#define KC_MOUSE TG(_MOUSE)
#define KC_NICOLA TG(_NICOLA)

#define LC_A LCTL(KC_A)
#define LC_B LCTL(KC_B)
#define LC_C LCTL(KC_C)
#define LC_D LCTL(KC_D)
#define LC_E LCTL(KC_E)
#define LC_F LCTL(KC_F)
#define LC_G LCTL(KC_G)
#define LC_H LCTL(KC_H)
#define LC_I LCTL(KC_I)
#define LC_J LCTL(KC_J)
#define LC_K LCTL(KC_K)
#define LC_L LCTL(KC_L)
#define LC_M LCTL(KC_M)
#define LC_N LCTL(KC_N)
#define LC_O LCTL(KC_O)
#define LC_P LCTL(KC_P)
#define LC_Q LCTL(KC_Q)
#define LC_R LCTL(KC_R)
#define LC_S LCTL(KC_S)
#define LC_T LCTL(KC_T)
#define LC_U LCTL(KC_U)
#define LC_V LCTL(KC_V)
#define LC_W LCTL(KC_W)
#define LC_X LCTL(KC_X)
#define LC_Y LCTL(KC_Y)
#define LC_Z LCTL(KC_Z)
#define LCOP LCTL(KC_LALT)
#define LCFN LCTL(KC_LGUI)
