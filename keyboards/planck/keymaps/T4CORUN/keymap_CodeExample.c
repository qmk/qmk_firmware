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


#include "T4CORUN.h"
#include "muse.h"
#include "version.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *                    ,-----------------------------------------------------------------------------------.
 *                    | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |ADJUST| -- Tap for '
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Ent  |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 * Tap for (, [, { -- | Dance|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Dance| -- Tap for ), ], }
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Alt  | GUI  | Esc  |LOWER | Bksp | Shft | Spc  |RAISE |  FN  | Vol- | Vol+ | Mute |
 *                    `-----------------------------------------------------------------------------------'
 *
 */  
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    AD_QUOT,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    TD_LBKT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD_RBKT,
    KC_LALT, KC_LGUI, KC_ESC,  LOWER,   KC_BSPC, KC_LSFT, KC_SPC,  RAISE,   FN,      KC_VOLD, KC_VOLU, KC_MUTE
),

/* Colemak
 *                    ,-----------------------------------------------------------------------------------.
 *                    | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |ADJUST| -- Tap for '
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Ctrl |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  | Ent  |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------| 
 * Tap for (, [, { -- | Dance|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | Dance| -- Tap for ), ], }
 *                    |------+------+------+------+------+------+------+------+------+------+------+------| 
 *                    | Alt  | GUI  | Esc  |LOWER | Bksp | Shft | Spc  |RAISE |  FN  | Vol- | Vol+ | Mute |
 *                    `-----------------------------------------------------------------------------------'
 * 
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, AD_QUOT,
    KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    TD_LBKT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD_RBKT, 
    KC_LALT, KC_LGUI, KC_ESC,  LOWER,   KC_BSPC, KC_LSFT, KC_SPC,  RAISE,  FN,      KC_VOLD, KC_VOLU, KC_MUTE
),

/* Gaming, QWERTY
 *                    ,-----------------------------------------------------------------------------------.
 *                    | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |ADJUST| -- Tap for '
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Alt  | GUI  | Esc  |LOWER | Bksp | Spc  | Spc  |RAISE |  FN  | Vol- | Vol+ | Mute |
 *                    `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    AD_QUOT,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LALT, KC_LGUI, KC_ESC,  LOWER,   KC_BSPC, KC_SPC,  KC_SPC,  RAISE,   FN,      KC_VOLD, KC_VOLU, KC_MUTE
),

/* Lower
 *                    ,-----------------------------------------------------------------------------------.
 *                    |   ~  |      | Home | Up   | End  | Snip |      | PgDn | PgUp |      |      |   |  |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      | Left | Down | Right|      |      | Shft | Ctrl | Alt  | GUI  |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      | Undo | Cut  | Copy | Paste|      |      |      |      |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      | App  |      |      | Del  |      |      |      |      | Prev | Next | Play |
 *                    `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, ___x___, KC_HOME, KC_UP,   KC_END,  W_SNIP,  ___x___, KC_PGDN, KC_PGUP, ___x___, ___x___, KC_PIPE,
    _______, ___x___, KC_LEFT, KC_DOWN, KC_RGHT, ___x___, ___x___, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
    _______, SC_UNDO, SC_CUT,  SC_COPY, SC_PAST, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, _______,
    _______, KC_APP,  _______, _______, KC_DEL,  _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY
),

/* Raise
 *                    ,-----------------------------------------------------------------------------------.
 *                    |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  \   |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Calc |      |      |      |      |   _  |   +  |   -  |  =   |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      | App  |      |      | Del  |      |      |      |      |      |      |      |
 *                    `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_CALC, ___x___, ___x___, ___x___, ___x___, KC_UNDS, KC_PLUS, KC_MINS, KC_EQL,  _______, _______, _______,
    _______, KC_APP,  _______, _______, KC_DEL,  _______, _______, _______, _______, _______, _______, _______
),

/* Function
 *                    ,-----------------------------------------------------------------------------------.
 *                    |      |      |      |      |      |PrtScr|PauBrk|      |  F9  | F10  | F11  | F12  |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |CapLck|      | Lead |  F5  |  F6  |  F7  |  F8  |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |DanceL|DanceR|      |  F1  |  F2  |  F3  |  F4  |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    `-----------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_planck_grid(
    ___x___, ___x___, ___x___, ___x___, ___x___, KC_PSCR, KC_PAUS, ___x___, KC_F9,   KC_F10,  KC_F11,  KC_F12, 
    _______, ___x___, ___x___, ___x___, ___x___, KC_CAPS, ___x___, KC_LEAD, KC_F5,   KC_F6,   KC_F7,   KC_F8,  
    ___x___, ___x___, ___x___, ___x___, ___x___, TD_LBKT, TD_RBKT, ___x___, KC_F1,   KC_F2,   KC_F3,   KC_F4,   
    _______, _______, _______, ___x___, ___x___, ___x___, ___x___, ___x___, _______, ___x___, ___x___, ___x___ 
),

/* Mouse
 *                        Mouse -----/`````````````````````````\ 
 *                    ,-----------------------------------------------------------------------------------.
 *                    |      |      |Ms B1 |Ms Up |Ms B2 |Ms WU |      |      |      |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      | Ms L |Ms Dn |Ms R  |Ms WD |      |      |      |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
    _______, ___x___, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, ___x___, ___x___, ___x___, ___x___, ___x___, _______, 
    _______, ___x___, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, ___x___, ___x___, ___x___, ___x___, ___x___, _______, 
    _______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
),

/* Adjust
 *                    ,-----------------------------------------------------------------------------------.
 *                    | Reset| Hue+ | Hue- |RGBTog|Qwerty|RecStp|      |      |      |Aud on|Audoff|      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      | Sat+ | Sat- |      |Colemk|DMRec1|DMPly1|      |MUSmod|Mus on|Musoff|      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    | Debug| Vib+ | Vib- |      |Gaming|DMRec2|DMPly2|      |      |MIDIon|MIDIof|      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   RGB_HUI, RGB_HUD, RGB_TOG, QWERTY,  DM_RSTP, ___x___, ___x___, ___x___, AU_ON,   AU_OFF,  _______,
    ___x___, RGB_SAI, RGB_SAD, ___x___, COLMAK, DM_REC1, DM_PLY1, ___x___, MU_MOD,  MU_ON,   MU_OFF,  ___x___,
    DEBUG,   RGB_VAI, RGB_VAD, ___x___, GAMING,  DM_REC2, DM_PLY2, ___x___, ___x___, MI_ON,   MI_OFF,  ___x___,
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, MUV_DE,  MUV_IN,  ___x___
)

/*                    Template ()
 *                    ,-----------------------------------------------------------------------------------.
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    |------+------+------+------+------+------+------+------+------+------+------+------|
 *                    |      |      |      |      |      |      |      |      |      |      |      |      |
 *                    `-----------------------------------------------------------------------------------'
 *
[_TEMPLATE] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
)
*/

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float lower_song[][2]  = SONG(CAPS_LOCK_ON_SOUND);
  float raise_song[][2]  = SONG(NUM_LOCK_ON_SOUND);
  float fn_song[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
  float adjust_song[][2]  = SONG(UNICODE_WINDOWS);
  float default_sound[][2]  = SONG(AG_NORM_SOUND);  
#endif


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AD_QUOT:
            //print("NAV_BSP\n");
            return TAPPING_TERM + 100;
            break;
        default:
            return TAPPING_TERM;
            break;
    }
}

//This is what allows LOWER + RAISE to call ADJUST
layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef AUDIO_ENABLE
    switch (get_highest_layer(state)) {
      case _RAISE:
        stop_all_notes();
        PLAY_SONG(raise_song);
        break;
      case _LOWER:
        stop_all_notes();
        PLAY_SONG(lower_song);
        break;
      case _ADJUST:
        stop_all_notes();
        PLAY_SONG(adjust_song);
        break;
      case _FUNCTION:
        stop_all_notes();
        PLAY_SONG(fn_song);
        break;
      default:
        stop_all_notes();
        PLAY_SONG(default_sound);
        break;
    }
  #endif
  return update_tri_layer_state(state, _LOWER, _RAISE, _MOUSE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("Mode Switch to QWERTY\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLMAK:
      if (record->event.pressed) {
        print("Mode Switch to COLEMAK\n");
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        print("Mode Switch to GAMING\n");
        set_single_persistent_default_layer(_GAMING);
      }
      return false;
      break;
    /*
    case KC_ENT:
      if (record->event.pressed) {
        print("Pressed Enter\n");
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(caps_sound);
        #endif
      }
      return true;
      break;
      */
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

LEADER_EXTERNS();

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

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }
    SEQ_ONE_KEY(KC_E) {
      //Open File Explorer
      SEND_STRING(SS_LGUI("e"));
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      //Ctrl A Ctrl C
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_TWO_KEYS(KC_F, KC_Q) {
      //Chrome Previous Tab
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))));
    }
    SEQ_TWO_KEYS(KC_F, KC_W) {
      //Chrome Close Tab
      SEND_STRING(SS_LCTL("w"));
    }
    SEQ_TWO_KEYS(KC_F, KC_E) {
      //Chrome Next Tab
      SEND_STRING(SS_LCTL(SS_TAP(X_TAB)));
    }
    SEQ_TWO_KEYS(KC_F, KC_R) {
      //Chrome Reopen Tab
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_T))));
    }
    SEQ_TWO_KEYS(KC_C, KC_COMM) {
      //XML < code
      SEND_STRING("&lt;");
    }
    SEQ_TWO_KEYS(KC_C, KC_DOT) {
      //XML > code
      SEND_STRING("&gt;");
    }
    SEQ_THREE_KEYS(KC_Q, KC_M, KC_K) {
      //shows QMK version
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " Built on: " QMK_BUILDDATE);
    }
    SEQ_THREE_KEYS(KC_E, KC_M, KC_L) {
      //types out my email
      SEND_STRING("VictorN076@gmail.com");
    }
  }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    //add all the keys that would be on your base layer that are not defaults. If we don't do this then the sounds do not play
    //Layer Taps do add delays to sounds. Probably the mod Taps too
    case RAISE:
    case LOWER:
    case ADJUST:
    case FN:
    case AD_QUOT:
      return false;
    default:
      return true;
  }
}
