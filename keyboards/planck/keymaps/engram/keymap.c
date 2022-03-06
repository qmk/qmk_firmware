/* Copyright 2015-2021 Jack Humbert
 * Copyright 2022 Callum Andrew
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
#include "muse.h"


enum planck_layers {
  _ENGRAM,
  _SHIFT,
  _LOWER,
  _RAISE,
  _SLOWER,
  _SRAISE,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  ENGRAM = SAFE_RANGE,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

#define SHIFT MO(_SHIFT)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Engram
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   B  |   Y  |   O  |   U  |   '  |   "  |   L  |   D  |   W  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   C  |   I  |   E  |   A  |   ,  |   .  |   H  |   T  |   S  |   N  |   Q  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   G  |   X  |   J  |   K  |   -  |   ?  |   R  |   M  |   F  |   P  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | GUI  | Alt  | Ctrl |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_ENGRAM] = LAYOUT_planck_grid(
    KC_TAB,  KC_B,    KC_Y,    KC_O,    KC_U,    KC_QUOT,  KC_DQT,  KC_L,   KC_D,    KC_W,    KC_V,    KC_Z,
    KC_ESC,  KC_C,    KC_I,    KC_E,    KC_A,    KC_COMM,  KC_DOT,  KC_H,   KC_T,    KC_S,    KC_N,    KC_Q,
    SHIFT,   KC_G,    KC_X,    KC_J,    KC_K,    KC_MINS,  KC_QUES, KC_R,   KC_M,    KC_F,    KC_P,    SHIFT,
    KC_BSPC, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,   KC_SPC,  RAISE,  KC_RGUI, KC_RALT, KC_RCTL, KC_ENT
),

/* Shift
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   B  |   Y  |   O  |   U  |   (  |   )  |   L  |   D  |   W  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   C  |   I  |   E  |   A  |   ;  |   :  |   H  |   T  |   S  |   N  |   Q  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   G  |   X  |   J  |   K  |   _  |   !  |   R  |   M  |   F  |   P  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp | Ctrl | Alt  | GUI  |Lower |    Space    |Raise |  GUI |  Alt | Ctrl |Enter |
 * `-----------------------------------------------------------------------------------
 */
[_SHIFT] = LAYOUT_planck_grid(
    S(KC_TAB),  S(KC_B),    S(KC_Y),    S(KC_O),    S(KC_U),     KC_LPRN, KC_RPRN, S(KC_L),     S(KC_D),    S(KC_W),    S(KC_V),    S(KC_Z),
    S(KC_ESC),  S(KC_C),    S(KC_I),    S(KC_E),    S(KC_A),     KC_SCLN, KC_COLN, S(KC_H),     S(KC_T),    S(KC_S),    S(KC_N),    S(KC_Q),
    _______,    S(KC_G),    S(KC_X),    S(KC_J),    S(KC_K),     KC_UNDS, KC_EXLM, S(KC_R),     S(KC_M),    S(KC_F),    S(KC_P),    _______,
    S(KC_BSPC), S(KC_LCTL), S(KC_LALT), S(KC_LGUI), MO(_SLOWER), _______, _______, MO(_SRAISE), S(KC_RGUI), S(KC_RALT), S(KC_RCTL), S(KC_ENT)
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   {  |   |  |   =  |   ~  |   +  |   <  |   >  |   ^  |   &  |   %  |   *  |  }   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   $  |   `  |   \  |Brght+| Num  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |Brght-|Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Prev | Play | Stop | Next |      |             |      | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_LCBR,     KC_PIPE, KC_EQL,  KC_TILD, KC_PLUS, KC_LT,   KC_GT,   KC_CIRC, KC_AMPR, KC_PERC, KC_ASTR, KC_RCBR,
    KC_CAPS,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_DLR,  KC_GRV,  KC_BSLS, KC_BRIU, KC_NUM,
    MO(_SLOWER), KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_BRID, MO(_SLOWER),
    KC_MPRV,     KC_MPLY, KC_MSTP, KC_MNXT, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   [  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  ]   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Scroll|  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |   #  |   @  |   /  |PrtSc | Ins  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |      |      |      |      |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Del | Mute | Vol- | Vol+ |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_LBRC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_RBRC,
    KC_SCRL,     KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_HASH, KC_AT,   KC_SLSH, KC_PSCR, KC_INS,
    MO(_SRAISE), KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______, _______, _______, _______, MO(_SRAISE),
    KC_DEL,      KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Shift + Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |   +  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |      |   ~  |   |  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_SLOWER] = LAYOUT_planck_grid(
    _______, _______,  KC_PLUS,  _______,  _______,   _______,   _______,   _______, _______,    _______,    _______,  _______,
    _______, S(KC_F1), S(KC_F2), S(KC_F3), S(KC_F4),  S(KC_F5),  S(KC_F6),  _______, KC_TILD,    KC_PIPE,    _______,  _______,
    _______, S(KC_F7), S(KC_F8), S(KC_F9), S(KC_F10), S(KC_F11), S(KC_F12), _______, _______,    _______,    _______,  _______,
    _______, _______,  _______,  _______,  _______,   _______,   _______,   _______, S(KC_LEFT), S(KC_DOWN), S(KC_UP), S(KC_RIGHT)
),

/* Shift + Raise
 * ,-----------------------------------------------------------------------------------.
 * |   {  |   ?  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  }   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |   ?  |PrtSc | Ins  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Del |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_SRAISE] = LAYOUT_planck_grid(
    KC_LCBR,   KC_QUES, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_RCBR,
    _______,   _______, _______, _______, _______, _______, _______, _______, _______,    KC_QUES,    S(KC_PSCR), S(KC_INS),
    _______,   _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______,    _______,
    S(KC_DEL), _______, _______, _______, _______, _______, _______, _______, S(KC_HOME), S(KC_PGDN), S(KC_PGUP), S(KC_END)
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 * v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|   7  |   8  |   9  |   +  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Reset|Debug |MUSmod|Aud on|Audoff|AGnorm|AGswap|Engram|   7  |   8  |   9  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|Plover|   1  |   2  |   3  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite|      |      |      |      |             |      |   *  |   0  |   .  |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_P7,   KC_P8,  KC_P9,   KC_PPLS,
    RESET,   DEBUG,   MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, ENGRAM,  KC_P4,   KC_P5,  KC_P6,   KC_PMNS,
    MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, PLOVER,  KC_P1,   KC_P2,  KC_P3,   KC_PSLS,
    BACKLIT, _______, _______, _______, _______, _______, _______, _______, KC_PAST, KC_P0,  KC_PDOT, KC_PENT
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ENGRAM:
      if (record->event.pressed) {
        print("mode just switched to engram and this is a huge string\n");
        set_single_persistent_default_layer(_ENGRAM);
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
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
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

bool encoder_update_user(uint8_t index, bool clockwise) {
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
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
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
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
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
