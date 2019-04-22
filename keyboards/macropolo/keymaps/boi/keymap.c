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
//keycode defs
enum custom_keycodes {
  LOGIN = SAFE_RANGE,
  MACRO,
  OOF,
  PHAT,
  COPY,
  PASTE,
  BANTER1,
  BANTER2,
  BANTER3,
  BANTER4
};
#define L1 TG(_L1)
#define L2 TG(_L2)
#define L3 TG(_L3)
#define L4 TG(_L4)
#define L5 TG(_L5)
#define L6 TG(_L6)
#define L7 TG(_L7)
#define L8 TG(_L8)

#define ___ KC_TRNS
#define XXX KC_NO
#define KC_ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*                          .-------.   .-------.
  .-----------.-----------./>NO      \./>NO      \.
  |           |           ||<NO      |||<NO      ||
  |           |           |\         /|\ Select  /|
  |-----------+-----------+-----------+-----------|
  | L5        | Minecraft | Osu!      | Music     |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  | Premiere  | Photoshop | KiCad     | None      |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_PICK] = LAYOUT( /* Layer Select */
    XXX,XXX,XXX,XXX, \
    TO(_L5),XXX,XXX,XXX, \
    TO(_L1),TO(_L2),TO(_L3),TO(_L4) \
  ),
  /*                          .-------.   .-------.
    .-----------.-----------./>        \./>        \.
    |           |           ||<        |||<        ||
    |           |           |\         /|\         /|
    |-----------+-----------+-----------+-----------|
    |           |           |           |           |
    |           |           |           |           |
    |-----------+-----------+-----------+-----------|
    |           |           |           |           |
    |           |           |           |           |
    `-----------'-----------'-----------'-----------'*/
    [_L1] = LAYOUT( /* 1 */
      KC_SPC,KC_E,KC_S,L1,  \
      KC_B,KC_DEL,OOF,PHAT, \
      KC_MINUS,KC_PLUS,KC_L,KC_F7 \
    ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\         /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_L2] = LAYOUT( /* 2 */
    COPY,PASTE,KC_MUTE,L2,  \
    KC_PSCR,KC_LCTL,BANTER1,BANTER2, \
    KC_LWIN,KC_LALT,BANTER3,BANTER4 \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>        \./>        \.
  |           |           ||<        |||<        ||
  |           |           |\         /|\         /|
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
  |           |           |\         /|\         /|
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
  .-----------.-----------./>VolUp   \./>MNXT    \.
  | Play      | Stop      ||<VolDown |||<MPRV    ||
  | Pause     |           |\ Player  /|\ Layers  /|
  |-----------+-----------+-----------+-----------|
  | Mute      |           | RGB       | RGB       |
  |           |           | On        | Off       |
  |-----------+-----------+-----------+-----------|
  | Login     |           |           | RGB Value |
  | Macro     |           |           | Decrease  |
  `-----------'-----------'-----------'-----------'*/
  [_L5] = LAYOUT( /* Media Control */
    KC_MPLY,KC_MSTP,KC_MSEL,L5,  \
    KC_AUDIO_MUTE,RGB_TOG, XXX, XXX, \
    XXX, XXX, XXX, XXX \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOGIN:
      if (record->event.pressed) {
        SEND_STRING("password" SS_TAP(X_ENTER));
      } else {
      }
      break;
    case MACRO:
      if (record->event.pressed) {
        SEND_STRING("thisisamacro" SS_TAP(X_ENTER));
      } else {
      }
      break;
    case OOF:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("o"));
      } else {
      }
      break;
    case PHAT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("s"));
      } else {
      }
      break;
    case COPY:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c"));
      } else {
      }
      break;
    case PASTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("v"));
      } else {
      }
      break;
    case BANTER1:
      if (record->event.pressed) {
        SEND_STRING("I'm so nuts, you can suck my fresh");
      } else {
      }
      break;
    case BANTER2:
      if (record->event.pressed) {
        SEND_STRING("MAKE AMERICA GREAT AGAIN!");
      } else {
      }
      break;
    case BANTER3:
      if (record->event.pressed) {
        SEND_STRING("#BUILDit!!");
      } else {
      }
      break;
    case BANTER4:
      if (record->event.pressed) {
        SEND_STRING("AMEN BROTHER!");
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
        clockwise ? tap_code(KC_A) : tap_code(KC_B);
        break;
      case _L2:
        clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
        break;
      case _L5:
        clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
        break;
      default:
        clockwise ? tap_code(KC_UP) : tap_code(KC_DOWN);
        break;
      }
  }
else if (index == 1) {
    switch(biton32(layer_state)) {
      case _PICK:
        clockwise ? tap_code(KC_NO) : tap_code(KC_NO);
        break;
      case _L1:
        clockwise ? tap_code(KC_C) : tap_code(KC_D);
        break;
      case _L2:
        clockwise ? tap_code(KC_BRIU) : tap_code(KC_BRID);
        break;
      case _L5:
        clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
        break;
      default:
        clockwise ? tap_code(KC_RIGHT) : tap_code(KC_LEFT);
        break;
      }
    }
}
#endif // ENCODER_ENABLE


//RGB Code
#ifdef RGBLIGHT_ENABLE
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
      case _PICK:
          rgblight_sethsv (0,30,70);
          break;
      case _L1:
          rgblight_sethsv (0,255,255);
          break;
      case _L2:
          rgblight_sethsv (60,255,255);
          break;
      case _L3:
          rgblight_sethsv (120,255,255);
          break;
      case _L4:
          rgblight_sethsv (180,255,255);
          break;
      case _L5:
          rgblight_sethsv (240,255,255);
          break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv (130,255,255);
        break;
    }
  return state;
}
#endif //RGBLIGHT_ENABLE
