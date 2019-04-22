/* Copyright 2019 mythosmann
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
//layer defs
#define _PICK 0
#define _L1 1
#define _L2 2
#define _L3 3
#define _L4 4
#define _L5 5
#define _L6 6
#define _L7 7
#define _L8 8
#define _L9 9
#define _L10 10

//keycode defs
enum custom_keycodes {
  LOGIN = SAFE_RANGE,
  MACRO
};
#define L1 TG(_L1)
#define L2 TG(_L2)
#define L3 TG(_L3)
#define L4 TG(_L4)
#define L5 TG(_L5)
#define L6 TG(_L6)
#define L7 TG(_L7)
#define L8 TG(_L8)
#define L9 TG(_L9)
#define L10 TG(_L10)

#define ___ KC_TRNS
#define XXX KC_NO
#define KC_ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*                          .-------.   .-------.
  .-----------.-----------./>NO      \./>NO      \.
  |           |           ||<NO      |||<NO      ||
  |           |           |\         /|\ Select  /|
  |-----------+-----------+-----------+-----------|
  | 5         | 6         | 7         | 8         |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  | 1         | 2         | 3         | 4         |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_PICK] = LAYOUT( /* Layer Select */
    TO(_L9),TO(_L10),KC_,KC_, \
    TO(_L5),TO(_L6),TO(_L7),TO(_L8), \
    TO(_L1),TO(_L2),TO(_L3),TO(_L4) \
  ),
  /*                          .-------.   .-------.
    .-----------.-----------./>        \./>        \.
    |           |           ||<        |||<        ||
    |           |           |\         /|\ Pick    /|
    |-----------+-----------+-----------+-----------|
    |           |           |           |           |
    |           |           |           |           |
    |-----------+-----------+-----------+-----------|
    |           |           |           |           |
    |           |           |           |           |
    `-----------'-----------'-----------'-----------'*/
    [_L1] = LAYOUT( /* 1 */
      KC_MSEL,KC_,KC_MUTE,L1,  \
      KC_MPRV,KC_MPLY,KC_MNXT,KC_MSTP, \
      KC_SLEP,KC_WAKE,LOGIN,KC_ \
    ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L2] = LAYOUT( /* 2 */
    C(A(KC_S)),C(S(KC_S)),KC_,L2,  \
    KC_R,KC_C,KC_L,KC_D, \
    KC_Q,KC_F,C(S(KC_C)),LCTL(KC_M) \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L3] = LAYOUT( /* 3 */
    KC_,KC_,KC_,L3,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L4] = LAYOUT( /* 4 */
    KC_,KC_,KC_,L4,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L5] = LAYOUT( /* 4 */
    KC_,KC_,KC_,L5,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L6] = LAYOUT( /* 4 */
    KC_,KC_,KC_,L6,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L7] = LAYOUT( /* 4 */
    KC_,KC_,KC_,L7,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L8] = LAYOUT( /* 4 */
    KC_,KC_,KC_,L8,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L9] = LAYOUT( /* 1 */
    KC_,KC_,KC_,L9,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\ Pick    /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L10] = LAYOUT( /* 1 */
    KC_,KC_,KC_,L10,  \
    KC_,KC_,KC_,KC_, \
    KC_,KC_,KC_,KC_ \
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOGIN:
      if (record->event.pressed) {
        SEND_STRING("15328" SS_TAP(X_ENTER));
      } else {
      }
      break;
    case MACRO:
      if (record->event.pressed) {
        SEND_STRING("thisisamacro" SS_TAP(X_ENTER));
      } else {
      }
      break;
    }
  return true;
}

//Encoder Code
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
if (index == 0) {
    switch(biton32(layer_state)) {
      case _PICK:
        clockwise ? tap_code(KC_NO) : tap_code(KC_NO);
        break;
      case _L1:
        clockwise ? tap_code(KC_VOLD) : tap_code(KC_VOLU);
        break;
      case _L2:
        clockwise ? tap_code(KC_WH_U) : tap_code(KC_WH_D);
        break;
      default:
        clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
        break;
      }
  }
else if (index == 1) {
    switch(biton32(layer_state)) {
      case _PICK:
        clockwise ? tap_code(KC_NO) : tap_code(KC_NO);
        break;
      case _L1:
        clockwise ? tap_code(KC_BRID) : tap_code(KC_BRIU);
        break;
      case _L2:
        clockwise ? tap_code(KC_PGUP) : tap_code(KC_PGDN);
        break;
      default:
        clockwise ? tap_code(KC_LEFT) : tap_code(KC_RGHT);
        break;
      }
    }
}
#endif // ENCODER_ENABLE

//RGB Light Code
#ifdef RGBLIGHT_ENABLE
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _PICK:
        rgblight_sethsv_range (0,30,40,0,7);
        break;
    case _L1:
        rgblight_sethsv_at (130,255,40,0);
        rgblight_sethsv_at (50,255,40,4);
        break;
    case _L2:
        rgblight_sethsv_at (150,255,40,1);
        rgblight_sethsv_at (50,255,40,4);
        break;
    case _L3:
        rgblight_sethsv_at (170,255,40,2);
        rgblight_sethsv_at (50,255,40,4);
        break;
    case _L4:
        rgblight_sethsv_at (190,255,40,3);
        rgblight_sethsv_at (50,255,40,4);
        break;
    case _L5:
        rgblight_sethsv_at (230,255,40,0);
        rgblight_sethsv_at (30,255,40,5);
        break;
    case _L6:
        rgblight_sethsv_at (250,255,40,1);
        rgblight_sethsv_at (30,255,40,5);
        break;
    case _L7:
        rgblight_sethsv_at (270,255,40,2);
        rgblight_sethsv_at (30,255,40,5);
        break;
    case _L8:
        rgblight_sethsv_at (290,255,40,3);
        rgblight_sethsv_at (30,255,40,5);
        break;
    case _L9:
        rgblight_sethsv_at (320,255,40,0);
        rgblight_sethsv_at (10,255,40,6);
        break;
    case _L10:
        rgblight_sethsv_at (340,255,40,1);
        rgblight_sethsv_at (10,255,40,6);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv (0,0,100);
        break;
    }
  return state;
}
#endif //RGBLIGHT_ENABLE
