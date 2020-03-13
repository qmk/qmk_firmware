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

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
bool isGame = false;
bool isMusic = false;


enum planck_layers {
  _COLEMAK,
  _GAME,
  _MUSIC,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  GCTOGG,
  MCTOGG,
  LOWER,
  RAISE,
  LENNY,
  COMMENTHEAD,
  RICKANDMORT,
  MARIO,
  MARIOE,
  OVERWATCH,
  DOOM,
  DISNEY,
  NUMBERONE,
  CABBAGE,
  OLDSPICE,
};

enum {
  TD_SPC_ENT = 0,
  TD_ESC_CAPS
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |lenny |Lower | shift|space |Raise | macro|macro2|macro3|QWERTY|
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_EQL,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
  KC_LCTL, KC_LGUI, KC_LALT, LENNY, LOWER,   RSFT_T(KC_BSPC),  TD(TD_SPC_ENT),  RAISE,   COMMENTHEAD, RICKANDMORT, KC_LEFT, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |   [  |   ]  |      |  (   |   )  |   {  |   }  |      |  +   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | left | down |  up  | right|  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |  _   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_LPRN, KC_RPRN,  KC_LCBR,    KC_RCBR, _______, S(KC_EQL),
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LEFT,    KC_DOWN,    KC_UP, KC_RGHT,   KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    _______,    _______, _______, KC_UNDS,
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | DEL  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  ~   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |  bl- |  bl+ | GCTG |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_DEC,  MCTOGG,  GCTOGG
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  _______, RESET,   DEBUG,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______,  COLEMAK, _______,  _______,  _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  _______, _______,  TERM_ON, TERM_OFF, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_GAME] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_EQL,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
  KC_LCTL, RAISE, KC_LALT, LOWER, KC_SPC, RSFT_T(KC_BSPC), TD(TD_SPC_ENT), RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
),

[_MUSIC] = LAYOUT_planck_grid(
  MARIO,  MARIOE, OVERWATCH,  DOOM, DISNEY, NUMBERONE, CABBAGE, OLDSPICE, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float guitar[][2] = SONG(GUITAR_SOUND);
  float mario[][2] = SONG(MARIO_THEME);
  float marioe[][2] = SONG(MARIO_GAMEOVER);
  float overwatch[][2] = SONG(OVERWATCH_THEME);
  float doom[][2] = SONG(E1M1_DOOM);
  float disney[][2] = SONG(DISNEY_SONG);
  float numberone[][2] = SONG(NUMBER_ONE);
  float cabbage[][2] = SONG(CABBAGE_SONG);
  float oldspice[][2] = SONG(OLD_SPICE);
#endif

void setLayer(int layer) {
    if (layer == _COLEMAK) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(marioe);
        #endif
        set_single_persistent_default_layer(_COLEMAK);
        #ifdef BACKLIGHT_ENABLE
            backlight_set(0);
        #endif
    } else if (layer == _GAME) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(mario);
        #endif
        set_single_persistent_default_layer(_GAME);
        #ifdef BACKLIGHT_ENABLE
            backlight_set(15);
        #endif
    } else if (layer == _MUSIC) {
        #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(guitar);
        #endif
        set_single_persistent_default_layer(_MUSIC);
        #ifdef BACKLIGHT_ENABLE
            backlight_set(1);
        #endif
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
        #ifdef BACKLIGHT_ENABLE
		  backlight_set(0);
        #endif
      }
      return false;
      break;
	case GCTOGG:
      if (record->event.pressed) {
		  if (isGame) {
              if (isMusic)
                  setLayer(_MUSIC);
              else
                  setLayer(_COLEMAK);
              isGame = false;
          } else {
              setLayer(_GAME);
              isGame = true;
          }
      }
      return false;
      break;
    case MCTOGG:
        if (record->event.pressed) {
            if (isMusic) {
                if (isGame)
                    setLayer(_GAME);
                else
                    setLayer(_COLEMAK);
                isMusic = false;
            } else {
                setLayer(_MUSIC);
                isMusic = true;
            }
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
    case LENNY:
    	if (record->event.pressed) {
    		SEND_STRING("()");
    	}
    	return false; break;
    case COMMENTHEAD:
    	if (record->event.pressed) {
    		SEND_STRING("// ---------------------------------------------------------------");
    	}
    	return false; break;
    case RICKANDMORT:
    	if (record->event.pressed) {
    		SEND_STRING("// ***************************************************************");
    	}
    	return false; break;
    case MARIO:
        if(record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_SONG(mario);
          #endif
        }
        return false; break;
      case MARIOE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(marioe);
            #endif
          }
          return false; break;
      case OVERWATCH:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(overwatch);
            #endif
          }
          return false; break;
      case DOOM:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(doom);
            #endif
          }
          return false; break;
      case DISNEY:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(disney);
            #endif
          }
          return false; break;
      case NUMBERONE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(numberone);
            #endif
          }
          return false; break;
      case CABBAGE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(cabbage);
            #endif
          }
          return false; break;
      case OLDSPICE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(oldspice);
            #endif
          }
          return false; break;
  }
  return true;
}

void matrix_init_user(void) {
	set_single_persistent_default_layer(_COLEMAK);
	isGame = false;
  #ifdef BACKLIGHT_ENABLE
        backlight_level(0);
  #endif
}
