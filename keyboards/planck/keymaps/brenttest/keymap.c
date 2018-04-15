/* to do
 * 1) how to move to default layer? TO(0)?
 * 2) transfer keycodes over from pc, mac and ios layouts
 * 3) pick numlock sounds
 * 4) make meh key the menu key
 */
/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _DVORAK,
  _MDVORAK,
  _MUSICL,
  _LOWER,
  _RAISE,
  _MRAISE,
  _ADJUST,
  _MADJUST
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  MDVORAK,
  MUSICL,
  LOWER,
  RAISE,
  BACKLIT,
  NUMLOCK
};

//Tap Dance Declarations

enum {

  TD_SFT_CAPS //Capslock tap, shift hold
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* PC Dvorak
   *      ,-----------------------------------------------------------------------------------.
   *      | Esc  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
   *      |------+------+------+------+------+-------------+------+------+------+------+------|
   *      | Tab  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  -   |
   *      |------+------+------+------+------+------|------+------+------+------+------+------|
   *Dvorak|alpha |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Up   |
   *      |------+------+------+------+------+------+------+------+------+------+------+------|
   *      | GUI  |Adjust|Raise |Lower |Caps  |Space | Enter| Bksp | Del  | Left | Down |Right |
   *      `-----------------------------------------------------------------------------------'
   *               Meh    Ctrl   Alt   Shift
   */
  [_DVORAK] = {
    {KC_ESC,             KC_QUOT,     KC_COMM, KC_DOT, KC_P,            KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH},
    {LT(_RAISE, KC_TAB), KC_A,        KC_O,    KC_E,   KC_U,            KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    LT(_LOWER, KC_MINS)},
    {LT(_LOWER, KC_GRV), KC_SCLN,     KC_Q,    KC_J,   KC_K,            KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_UP},
    {KC_LGUI,            TO(_ADJUST), CTL_T(TO(_RAISE)),   ALT_T(TO(_LOWER)),  TD(TD_SFT_CAPS), KC_SPC,  KC_ENT,  KC_BSPC, KC_DEL,  KC_LEFT, KC_RGHT, KC_DOWN}
  },

/* Lower, minus hold, alpha hold
 * ,-----------------------------------------------------------------------------------.
 * |NUMLK |   -  |   7  |   8  |   9  |   /  |   @  |   [  |   ]  |   &  |   ~  |   %  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   +  |   4  |   5  |   6  |   *  |   \  |   (  |   )  |   !  |   ^  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   0  |   1  |   2  |   3  |   =  |   $  |   {  |   }  |   |  |   #  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {NUMLOCK, KC_MINS, KC_KP_7, KC_KP_8, KC_KP_9, KC_SLSH, KC_AT,   KC_LBRC, KC_RBRC, KC_AMPR, KC_TILD, KC_PERC},
  {KC_GRV,  KC_PLUS, KC_KP_4, KC_KP_5, KC_KP_6, KC_ASTR, KC_BSLS, KC_LPRN, KC_RPRN, KC_EXLM, KC_CIRC, _______},
  {TO(0), KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_EQL,  KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE, KC_HASH, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise, tab hold
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | Home | Up   | End  |Pg Up |VolUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |SelAll| Cut  | Copy |Paste |      |      | Left | Down |Right |Pg Dn |VolDn |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Undo | Redo | Find |PrtScr|Mute  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, KC_HOME,    KC_UP,      KC_END,     KC_PGUP, KC_VOLU},
  {_______, LCTL(KC_A), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX, XXXXXXX, KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN, KC_VOLD},
  {TO(0), XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX, LCTL(KC_Z), LCTL(KC_Y), LCTL(KC_F), KC_PSCR, KC_MUTE},
  {_______, _______,    _______,    _______,    _______,    _______, _______, _______,    _______,    _______,    _______, _______}
},

[_MRAISE] = {
  {_______, MUTESONG,   VOLTLD,     VOLTCO,     IMPERIAL,   ODE,     XXXXXXX, LGUI(KC_LEFT), KC_UP,            LGUI(KC_RGHT), KC_PGUP,          KC__VOLUP},
  {_______, LGUI(KC_A), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), XXXXXXX, XXXXXXX, KC_LEFT,       KC_DOWN,          KC_RGHT,       KC_PGDN,          KC__VOLDOWN},
  {_______, COIN,       SONIC,      ONEUP,      ZELDAP,     ZELDAT,  XXXXXXX, LGUI(KC_Z),    LGUI(LSFT(KC_Z)), LGUI(KC_F),    LGUI(LSFT(KC_3)), KC__MUTE},
  {_______, _______,    XXXXXXX,    _______,    _______,    _______, _______, _______,       _______,          _______,       _______,          _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Sleep | Reset|Qwerty|Colemk|Dvorak|      |      |  F1  |  F2  |  F3  |  F4  |VolUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|      |      |  F5  |  F6  |  F7  |  F8  |VolDn |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|  F9  |  F10 |  F11 |  F12 |Mute  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {KC_SLEP, RESET,   XXXXXXX, XXXXXXX, DVORAK,  XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_VOLU},
  {_______, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_VOLD},
  {TO(0), MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[_MADJUST] = {
  {KC_SLEP, RESET,   QWERTY,  COLEMAK, DVORAK,  XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC__VOLUP},
  {_______, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC__VOLDOWN},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC__MUTE},
  {_______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float tone_caps_off[][2]   = SONG(NUM_LOCK_OFF_SOUND);
  float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
  float tone_nums_off[][2]   = SONG(SCROLL_LOCK_OFF_SOUND);
  float tone_nums_on[][2]    = SONG(CAPS_LOCK_OFF_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
    case NUMLOCK:
      if (record->event.pressed) {
        register_code (KC_NLCK);
    	  if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)){
    		    #ifdef AUDIO_ENABLE
    			     PLAY_SONG(tone_nums_off);
    		    #endif
        } else {
          #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_nums_on);
          #endif
        }
      } else {
          unregister_code(KC_NLCK);
      }
      return false;
      break;
  }
  return true;
}


//layer changes backlight level
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _RAISE:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(1);
        #endif
        break;
    case _LOWER:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(2);
        #endif
        break;
    case _ADJUST:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(0);
        #endif
        break;
    default: //  for any other layers, or the default layer
        #ifdef BACKLIGHT_ENABLE
        backlight_set(3);
        #endif
        break;
    }
  return state;
}
/*
bool has_layer_changed = true;

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  static uint8_t old_layer = 0;

  if (old_layer != layer) {
    has_layer_changed = true;
    old_layer = layer;
  }

  if (has_layer_changed) {
    has_layer_changed = false;

    switch (layer) {
      case _LOWER:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(1);
        #endif
      break;
      case _QWERTY:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(2);
        #endif
      break;
      case _RAISE:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(3);
        #endif
      break;
      case _ADJUST:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(0);
        #endif
      break;
    }
  }
};
*/

//Tap Dance Definitions
typedef struct {
  bool alt;
  bool finished_once;
} td_sftcaps_state_t;

//TD shift on hold, capslock on tap
void _td_sftcaps_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_sftcaps_state_t *s = (td_sftcaps_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    register_code (KC_LSFT);
  } else {
    s->alt = false;
    register_code (KC_CAPS);
	if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)){
		#ifdef AUDIO_ENABLE
			PLAY_SONG(tone_caps_off);
		#endif
	} else {
		#ifdef AUDIO_ENABLE
			PLAY_SONG(tone_caps_on);
		#endif
	}
  }
}

void _td_sftcaps_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_sftcaps_state_t *s = (td_sftcaps_state_t *)user_data;

  if (s->alt) {
    unregister_code (KC_LSFT);
  } else {
    unregister_code (KC_CAPS);
  }

  s->finished_once = false;
}

//TD Actions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SFT_CAPS] = {
    .fn = { NULL, _td_sftcaps_finished, _td_sftcaps_reset },
    .user_data = (void *)&((td_sftcaps_state_t) { false, false })
  }
};
