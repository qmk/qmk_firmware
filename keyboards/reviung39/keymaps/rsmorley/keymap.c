/* Copyright 2019 gtips
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

//Tap Dance Declarations
enum {
  TD_COPY_PASTE = 0
};

enum layer_names {
    _BASE,
    _NAV_MEDIA,
    _NUM_SCHAR,
    _ADJUST
};

#define KC_COPY LCMD(KC_C)
#define KC_PASTE LCMD(KC_V)
#define NAV_MEDIA  MO(_NAV_MEDIA)
#define NUM_SCHAR  MO(_NUM_SCHAR)
#define ADJUST MO(_ADJUST)

#define RETRO_WAVE_PURPLE 0xc0, 0x4d, 0xf9
#define RETRO_WAVE_RED 0xff, 0x3f, 0x3f
#define RETRO_WAVE_PINK 0xff, 0x48, 0xc4
#define RETRO_WAVE_YELLOW 0xf3, 0xea, 0x5f
#define RETRO_WAVE_BLUE 0x2b, 0xd1, 0xfc

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung39(
    KC_GESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    LSFT_T(KC_TAB),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_RSPC,
    KC_LCPO,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   TD(TD_COPY_PASTE),  ALT_T(KC_F6),
                                                       LT(_NUM_SCHAR, KC_ENT),    RCMD_T(KC_F3),   LT(_NAV_MEDIA, KC_SPC)
  ),
  
  [_NAV_MEDIA] = LAYOUT_reviung39(
    _______,  _______,  KC_UP,    _______,  _______,    _______,            _______,  _______,  KC__MUTE,  KC__VOLDOWN,  KC__VOLUP,  _______,
    _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,   _______,            _______,  KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,  _______,   _______,
    _______,  _______,   _______,  _______,  _______,   _______,            _______,  _______,   _______,  _______,  _______,  KC_CAPSLOCK,
                                                       _______,  _______,   _______
  ),
  
  [_NUM_SCHAR] = LAYOUT_reviung39(
    KC_GRV,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
    _______,  _______,  _______,   KC_QUOT,  KC_LBRC,   KC_RBRC,            KC_BSLS,    KC_MINS,    KC_EQL,    KC_SLSH,    _______,    _______,
    _______,  _______,   _______,  _______,  _______,   _______,            _______,    _______,    _______,    _______,   _______,   ALT_T(KC_F5),
                                                       _______,  _______,  _______
  ),
  
  [_ADJUST] = LAYOUT_reviung39(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                                       _______,  XXXXXXX,  _______
  ),
};

void keyboard_post_init_user(void) {
  //only show animations across bottom LEDs so top LED can
  //be used as an indicator light
  rgblight_set_effect_range(0, 10);
  //rainbow_swirl supports additional numbers 0-5
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);
  setrgb(RETRO_WAVE_PURPLE, (LED_TYPE *)&led[10]); //purple
  rgblight_set();
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Copy, twice for Paste
  [TD_COPY_PASTE]  = ACTION_TAP_DANCE_DOUBLE(KC_COPY, KC_PASTE)
};

//Tri state allows momentary toggle of _ADJUST layer when 
//buttons are held to toggle _NAV_MEDIA and _NUM_SCHAR
//Top facing led changes color based on layer
layer_state_t layer_state_set_user(layer_state_t state) {
  //update state first so we can correctly set color for _ADJUST layer
  state = update_tri_layer_state(state, _NAV_MEDIA, _NUM_SCHAR, _ADJUST);
  
  switch (get_highest_layer(state)) {
  case _BASE:
    setrgb(RETRO_WAVE_PURPLE, (LED_TYPE *)&led[10]);
    break;
  case _NUM_SCHAR:
    setrgb(RETRO_WAVE_BLUE, (LED_TYPE *)&led[10]);
    break;
  case _NAV_MEDIA:
    setrgb(RETRO_WAVE_YELLOW, (LED_TYPE *)&led[10]);
    break;
  case _ADJUST:
    setrgb(RETRO_WAVE_RED, (LED_TYPE *)&led[10]);
    break;
  default:
    setrgb(RGB_WHITE, (LED_TYPE *)&led[10]);
    break;
  }
  rgblight_set();

  return state;
}

//set LED11 to specified r,g,b on keydown 
//and back to layer specific on keyup
void update_indicator(keyrecord_t *record, uint8_t r, uint8_t g, uint8_t b) {
  if (record->event.pressed) {
    setrgb(r, g, b, (LED_TYPE *)&led[10]); //white
    rgblight_set();
    //
  } else {
    layer_state_set_user(layer_state);
  }
}

//used to set LED11 as indicator for Shift, Ctrl, Option and Command
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCPO:
    case ALT_T(KC_F6):
    case RCMD_T(KC_F3):
    case LSFT_T(KC_TAB):
    case KC_RSPC:
      update_indicator(record, RGB_WHITE);
      return true;
      break;
  }
  return true;
}