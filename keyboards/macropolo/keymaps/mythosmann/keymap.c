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
#define _PREM 1
#define _PS 2
#define _KICAD 3
#define _CODE 4
#define _MED 5
#define _MINE 6
#define _OSU 7
#define _MU 8
//macro defs
enum custom_keycodes {
  LOGIN = SAFE_RANGE,
  MACRO
};
//custom keycodes
#define ___ KC_TRNS
#define XXX KC_NO
#define KC_ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*                          .-------.   .-------.
  .-----------.-----------./>NO      \./>NO      \.
  |           |           ||<NO      |||<NO      ||
  |           |           |\         /|\ Select  /|
  |-----------+-----------+-----------+-----------|
  | Media     | Minecraft | Osu!      | Music     |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  | Premiere  | Photoshop | KiCad     | None      |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_PICK] = LAYOUT( /* Layer Select */
    KC_NO, KC_NO, KC_NO, KC_TRNS, \
    TO(_MED), TO(_MINE), TO(_OSU), TO(_MU), \
    TO(_PREM), TO(_PS), TO(_KICAD), TO(_CODE) \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>Right   \./>Up      \.
  | Timeline  | Timeline  ||<Left    |||<Down    ||
  | Select    | Cut       |\ Ctrl+S  /|\ Select  /|
  |-----------+-----------+-----------+-----------|
  | Insert    | Overwrite | Delete    | Enter     |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  | Shift     | Control   | Alt       | Space      |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_PREM] = LAYOUT( /* Premiere */
    KC_V, KC_C, LCTL(KC_S), TG(_PREM),  \
    KC_COMMA,  KC_DOT,  KC_DELETE, KC_ENTER, \
    KC_LSFT,  KC_LCTL,  KC_LALT, KC_SPACE \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>Right   \./>Up      \.
  | Selection | Wire      ||<Left    |||<Down    ||
  | Tool      | Tool      |\         /|\ Layers  /|
  |-----------+-----------+-----------+-----------|
  | Shift     | New       | Move      | Delete    |
  |           | Track     |           |           |
  |-----------+-----------+-----------+-----------|
  | Control   |           |           |           |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_KICAD] = LAYOUT( /* KiCad */
    KC_ESC, KC_W,  KC_C,  TG(_KICAD), \
    KC_LSFT,  KC_X,  KC_M, KC_DEL, \
    KC_LCTL,  KC_I,  KC_J, KC_ENT \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>Right   \./>Wh Up   \.
  | S         | R         ||<Left    |||<Wh Down ||
  |           |           |\         /|\ Layers  /|
  |-----------+-----------+-----------+-----------|
  | Shift     | E         | F         | G         |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  | Control   | Alt       | Space     | K         |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_PS] = LAYOUT( /* Photoshop */
    KC_S, KC_R,  KC_C, TG(_PS), \
    KC_RSFT,  KC_E,  KC_F, KC_G, \
    KC_RCTL,  KC_LALT,  KC_SPC, KC_K \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>PageUp  \./>Up      \.
  | Escape    | Tab       ||<PageDown||/<Down    ||
  |           |           |\ Save    /|\ Layers  /|
  |-----------+-----------+-'-------'-+-----------|
  | Left      | Left      | Asterisk  | Slash     |
  | Shift     | Alt       |           |           |
  |-----------+-----------+-----------+-----------|
  | RGB       | Left      | Right     | Enter     |
  | Hue-      | Bracket   | Bracket   |           |
  `-----------'-----------'-----------'-----------'*/
  [_CODE] = LAYOUT( /* Coding hotkeys */
    KC_ESC, KC_TAB, LCTL(KC_S), TG(_CODE),  \
    KC_LSFT, KC_LALT, KC_ASTERISK, KC_SLSH, \
    KC_LCTL, KC_LBRACKET, KC_RBRACKET, KC_ENT \
  ),
  /*                          .-------.   .-------.
    .-----------.-----------./>VolUp   \./>MNXT    \.
    | Play      | Stop      ||<VolDown |||<MPRV    ||
    | Pause     |           |\ Player  /|\ Layers  /|
    |-----------+-----------+-----------+-----------|
    | Mute      |           | RGB       | RGB Value |
    |           |           | Toggle    | Increase  |
    |-----------+-----------+-----------+-----------|
    | Login     |           |           | RGB Value |
    | Macro     |           |           | Decrease  |
    `-----------'-----------'-----------'-----------'*/
    [_MED] = LAYOUT( /* Media Control */
      KC_MPLY, KC_MSTP,  KC_MEDIA_SELECT, TG(_MED),  \
      KC_AUDIO_MUTE,  KC_NO, RGB_TOG, RGB_VAI, \
      LOGIN, KC_NO, KC_NO, RGB_VAD \
    ),
  /*                          .-------.   .-------.
    .-----------.-----------./>PageUp  \./>Wh Up   \.
    | E         | Tab       ||<PageDown|||<Wh Down ||
    |           |           |\ F3      /|\         /|
    |-----------+-----------+-----------+-----------|
    |           |           |           |           |
    |           |           |           |           |
    |-----------+-----------+-----------+-----------|
    |           |           |           |           |
    |           |           |           |           |
    `-----------'-----------'-----------'-----------'*/
    [_MINE] = LAYOUT( /* Minecraft */
      KC_E, KC_TAB,  KC_F3, TG(_MINE),  \
      KC_NO, KC_NO, KC_NO, KC_NO, \
      KC_NO, KC_NO, KC_NO, KC_NO \
    ),
/*                          .-------.   .-------.
  .-----------.-----------./>PageUp  \./>Wh Up   \.
  | Esc       |           ||<PageDown|||<Wh Down ||
  |           |           |\ F3      /|\         /|
  |-----------+-----------+-----------+-----------|
  |           |           |           |           |
  |           |           |           |           |
  |-----------+-----------+-----------+-----------|
  | G         | H         | J         | K         |
  |           |           |           |           |
  `-----------'-----------'-----------'-----------'*/
  [_OSU] = LAYOUT( /* Osu! */
    KC_ESC, KC_MSTP,  KC_F3, TG(_OSU),  \
    KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_G, KC_H, KC_J, KC_K \
  ),
/*                          .-------.   .-------.
  .-----------.-----------./>PageUp  \./>Wh Up   \.
  | Clicky    | Music     ||<PageDown|||<Wh Down ||
  | Toggle    | On        |\ AU_TOG  /|\         /|
  |-----------+-----------+-----------+-----------|
  | Clicky    | Music     | Audio     |           |
  | Up        | Off       | On        |           |
  |-----------+-----------+-----------+-----------|
  | Clicky    | Clicky    | Audio     |           |
  | Down      | Reset     | Off       |           |
  `-----------'-----------'-----------'-----------'*/
    [_MU] = LAYOUT( /* Audio */
    CK_TOGG, MU_ON, AU_TOG, TG(_MU),  \
    CK_UP, MU_OFF, AU_ON, KC_NO, \
    CK_DOWN, CK_RST, AU_OFF, KC_NO \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOGIN:
      if (record->event.pressed) {
        SEND_STRING("43110" SS_TAP(X_ENTER));
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

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
if (index == 0) {
    switch(biton32(layer_state)) {
      case _PICK:
        clockwise ? tap_code(KC_NO) : tap_code(KC_NO);
        break;
      case _CODE:
        clockwise ? tap_code(KC_PGUP) : tap_code(KC_PGDN);
        break;
      case _MED:
        clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
        break;
      case _MU:
        clockwise ? tap_code(KC_NO) : tap_code(KC_NO);
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
      case _CODE:
        clockwise ? tap_code(KC_UP) : tap_code(KC_DOWN);
        break;
      case _MED:
        clockwise ? tap_code(KC_MEDIA_NEXT_TRACK) : tap_code(KC_MEDIA_PREV_TRACK);
        break;
      case _PS:
        clockwise ? tap_code(KC_MS_WH_UP) : tap_code(KC_MS_WH_DOWN);
        break;
      case _MU:
        clockwise ? tap_code(KC_NO) : tap_code(KC_NO);
        break;
      default:
        clockwise ? tap_code(KC_RIGHT) : tap_code(KC_LEFT);
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
    case _PREM:
        rgblight_sethsv_at (130,255,160,0);
        rgblight_sethsv_at (50,255,160,4);
        break;
    case _PS:
        rgblight_sethsv_at (150,255,160,1);
        rgblight_sethsv_at (50,255,160,4);
        break;
    case _KICAD:
        rgblight_sethsv_at (170,255,160,2);
        rgblight_sethsv_at (50,255,160,4);
        break;
    case _CODE:
        rgblight_sethsv_at (190,255,160,3);
        rgblight_sethsv_at (50,255,160,4);
        break;
    case _MED:
        rgblight_sethsv_at (230,255,160,0);
        rgblight_sethsv_at (30,255,160,5);
        break;
    case _MINE:
        rgblight_sethsv_at (250,255,160,1);
        rgblight_sethsv_at (30,255,160,5);
        break;
    case _OSU:
        rgblight_sethsv_at (270,255,160,2);
        rgblight_sethsv_at (30,255,160,5);
        break;
    case _MU:
        rgblight_sethsv_at (290,255,160,3);
        rgblight_sethsv_at (30,255,160,5);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv (0,0,100);
        break;
    }
  return state;
}
#endif //RGBLIGHT_ENABLE
