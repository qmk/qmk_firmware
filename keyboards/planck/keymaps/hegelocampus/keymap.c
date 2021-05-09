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
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _DVORAK,
  _GAME,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  GAME,
  BACKLIT,
  FN
};


#define LEADER_TIMEOUT 400

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FN    MO(_FN)
#define GAME  MO(_GAME)

#define LSPA  LT(_RAISE, KC_SPC)
#define RSPA  LT(_FN, KC_SPC)
#define RLEFT LT(_RAISE, KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Lead | GUI  |  Alt |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,     KC_L,     KC_QUOT, KC_ENT ,
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH, KC_RSPC,
    KC_LCTL, KC_LGUI, KC_LALT, LOWER,   LSPA,    LSPA,    RSPA,    RSPA,   RLEFT,    KC_DOWN,  KC_UP,   KC_RIGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_GESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT ,
    KC_LSPO, KC_SLSH, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC,
    KC_LCTL, KC_LALT, KC_LGUI, LOWER,   LSPA,    LSPA,    RSPA,    RSPA,    RAISE,   KC_LCTL, KC_LEAD, KC_RALT
),



/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   !  |  @   |  #   |  $   |   %  |   ^  |   &  |   *  |  [   |   ]  |  _   |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |   |  |   ~  |  {   |   }  |  :   |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = LAYOUT_planck_grid(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_PIPE, KC_COLON, _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC,  _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TILD, _______, KC_LCBR, KC_RCBR,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RALT, KC_RGUI,  KC_RCTL
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift| Next | Vol- | Vol+ | Play |      |      |   \  |   [  |   ]  |   ;  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |Pg Dn |Pg Up |      |
 * `-----------------------------------------------------------------------------------'
 */

[_RAISE] = LAYOUT_planck_grid(
  _______, _______, _______, _______, _______, _______, _______, KC_MINS,  KC_EQL , KC_BSLS, KC_SCLN, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    _______,
  _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, KC_GRAVE, _______, KC_LBRC, KC_RBRC, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_RALT, KC_RGUI,  KC_RCTL
),

[_FN] = LAYOUT_planck_grid(
  _______, _______, _______, _______, _______, _______, _______, KC_TILD, KC_SLSH, KC_BSLS,  _______, KC_DEL,
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_SCLN, _______,
  _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, KC_LBRC,  KC_LBRC, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RALT,  KC_RGUI,  KC_RCTL
),

[_GAME] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_1,    KC_2,   KC_3,     KC_4,     KC_5,    KC_ESC,
  KC_1,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,     KC_L,     KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM,  KC_DOT,   KC_SLSH, KC_RSPC,
  KC_LCTL, KC_LGUI, KC_LALT, RAISE,   KC_SPC,  KC_SPC,  RSPA,    RSPA,   LOWER,    KC_DOWN,  KC_UP,   DVORAK
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QWERTY,  DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD,  _______,
    _______, _______, _______,  DVORAK,  _______, GAME,    AG_NORM, AG_SWAP, _______,  CK_TOGG, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MU_MOD,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF,  _______, _______,
    AU_ON,   AU_OFF,  _______, _______, _______, _______, _______, _______, _______,  _______, _______,  RESET
)


};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode switched to qwerty");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
      }
        return false;
        break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_ONE_KEY(KC_SLSH) {
      SEND_STRING(SS_LCTRL("Z"));
    }
    SEQ_ONE_KEY(KC_Q) {
      SEND_STRING(SS_LCTRL("x"));
    }
    SEQ_ONE_KEY(KC_J) {
      SEND_STRING(SS_LCTRL("c"));
    }
    SEQ_ONE_KEY(KC_K) {
      SEND_STRING(SS_LCTRL("v"));
    }
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING(SS_LCTRL("a"));
    }
    SEQ_ONE_KEY(KC_U) {
      SEND_STRING(SS_LCTRL(SS_LALT("F")));
    }
    SEQ_ONE_KEY(KC_P) {
      SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_PSCREEN))));
    }
    SEQ_ONE_KEY(KC_L) {
      SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_PSCREEN))));
    }
    SEQ_ONE_KEY(KC_L) {
      SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_PSCREEN))));
    }
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_RALT("sf"));
    }
    SEQ_ONE_KEY(KC_TAB) {
      SEND_STRING(SS_LGUI(SS_TAP(X_TAB)));
    }
}
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
