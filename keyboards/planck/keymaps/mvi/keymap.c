/* Copyright 2015-2017 Jack Humbert
 * Copyright 2017-2021 Emmanuel Villéger
 *
 * Use Jeebak layout for layer TOUCHCURSOR
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
#include "keymap_bepo.h"
#include "sendstring_bepo.h"

// super alt/tab macro
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// timer for Mod-Tap
uint16_t mu_cced_timer = 0;

// record states of modifiers before using unicode
uint8_t mod_state;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _BEPO,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _PLOVER,
  _TOUCHCURSOR,
  _ADJUST
};

enum custom_keycodes {
  BEPO = SAFE_RANGE,
  NUMPAD,
  PLOVER,
  EXT_PLV,
  ALT_TAB, // super alt/tab macro
  // custom keycodes for shortcuts
  MVI_CLK, // clear keyboard
  MVI_CXU, // C-x u
  MVI_CCC, // C-c ;
  // custom keycode for personal mod_tap
  MU_CCED  // Mute when hold, ç when tapped
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Custom macros
#define TC_SPC   LT(_TOUCHCURSOR, KC_SPC)  // L-ayer T-ap T-ouch C-ursor on Space
#define TC_ENT   LT(_TOUCHCURSOR, KC_ENT)  // L-ayer T-ap T-ouch C-ursor on Enter
#define TC_PENT  LT(_TOUCHCURSOR, KC_PENT) // L-ayer T-ap T-ouch C-ursor on Enter
#define MVI_CUT  S(KC_DEL)  // cut
#define MVI_CPY  C(KC_INS)  // copy
#define MVI_PST  S(KC_INS)  // paste
#define XCV_CUT  C(BP_X)    // cut
#define XCV_CPY  C(BP_C)    // copy
#define XCV_PST  C(BP_V)    // paste
#define CTL_TAB  C(KC_TAB)    // C-Tab
#define CS_TAB   C(S(KC_TAB)) // C-Shift-Tab
#define MVI_MEN  LSFT(KC_F10) // Menu

// Left-hand home row mods
#define GUI_A  LGUI_T(BP_A)
#define ALT_U  LALT_T(BP_U)
#define SFT_I  LSFT_T(BP_I)
#define CTR_E  LCTL_T(BP_E)

#define GUI_F5 LGUI_T(KC_F5)
#define ALT_F6 LALT_T(KC_F6)
#define SFT_F7 LSFT_T(KC_F7)
#define CTR_F8 LCTL_T(KC_F8)

#define GUI_WHD LGUI_T(KC_WH_D)
#define ALT_MSL LALT_T(KC_MS_L)
#define SFT_MSD LSFT_T(KC_MS_D)
#define CTR_MSR LCTL_T(KC_MS_R)
  
// Right-hand home row mods
#define CTR_T  LCTL_T(BP_T)
#define SFT_S  RSFT_T(BP_S)
#define ALT_R  LALT_T(BP_R)
#define GUI_N  RGUI_T(BP_N)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BEPO] = LAYOUT_planck_grid(
  //,-----------------------------------------------------------------------------------------------------------.
     BP_W,    BP_B,    BP_EACU, BP_P,    BP_O,    BP_EGRV, BP_DCIR, BP_V,    BP_D,    BP_L,    BP_J,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     BP_Z,    GUI_A,   ALT_U,   SFT_I,   CTR_E,   BP_COMM, BP_C,    CTR_T,   SFT_S,   ALT_R,   GUI_N,   BP_M,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     BP_ECIR, BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,    BP_QUOT, BP_Q,    BP_G,    BP_H,    BP_F,    MU_CCED,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_LEFT, KC_DOWN, KC_ALGR, LOWER,   TC_ENT,  TC_SPC,  RAISE,   KC_ALGR, KC_UP,   KC_RGHT, KC_ENT
  //`-----------------------------------------------------------------------------------------------------------'
),

[_NUMPAD] = LAYOUT_planck_grid(
  //,-----------------------------------------------------------------------------------------------------------.
     KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PMNS, KC_UP,   KC_NLCK, KC_P7,   KC_P8,   KC_P9,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_ESC,  GUI_F5,  ALT_F6,  SFT_F7,  CTR_F8,  KC_PPLS, KC_LEFT, KC_RGHT, KC_P4,   KC_P5,   KC_P6,   KC_PSLS,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_CAPS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PEQL, KC_DOWN, KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, MVI_CUT, MVI_CPY, MVI_PST, LOWER,   TC_PENT, TC_SPC,  RAISE,   KC_P0,   KC_PDOT, KC_PAST, KC_PENT
  //`-----------------------------------------------------------------------------------------------------------'
),

[_LOWER] = LAYOUT_planck_grid(
  //,-----------------------------------------------------------------------------------------------------------.
     BP_DLR,  BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN, BP_AT,   BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_ESC,  MVI_CXU, BP_LABK, BP_RABK, BP_LBRC, BP_RBRC, KC_PSCR, BP_EQL,  _______, _______, KC_TAB,  MVI_MEN,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_CAPS, ALT_TAB, BP_LEQL, BP_GEQL, CTL_TAB, _______, MVI_CCC, BP_PERC, MVI_CUT, MVI_CPY, MVI_PST, KC_VOLD,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_HOME, KC_PGDN, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_END,  _______
  //`-----------------------------------------------------------------------------------------------------------'
),

[_RAISE] = LAYOUT_planck_grid(
  //,-----------------------------------------------------------------------------------------------------------.
     BP_HASH, BP_1,    BP_2,    BP_3,    BP_4,    BP_5,    BP_6,    BP_7,    BP_8,    BP_9,    BP_0,    _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   BP_DEG,  CTL_TAB, ALT_TAB, KC_TAB,  MVI_MEN,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  BP_GRV,  XCV_CUT, XCV_CPY, XCV_PST, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_MUTE, KC_INS,  _______, _______, _______, _______, _______, _______, KC_PSCR, KC_DEL,  _______
  //`-----------------------------------------------------------------------------------------------------------'
),

/* Plover layer (http://opensteno.org)
   *,-----------------------------------------------------------------------------------------------------------.
   *|   #    |   #    |   #    |   #    |   #    |   #    |   #    |   #    |   #    |   #    |   #    |   #    |
   *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   *|        |   S    |   T    |   P    |   H    |   *    |   *    |   F    |   P    |   L    |   T    |   D    |
   *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   *|        |   S    |   K    |   W    |   R    |   *    |   *    |   R    |   B    |   G    |   S    |   Z    |
   *|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
   *| Exit   |        |        |   A    |   O    |        |        |   E    |   U    |        |        |        |
   *`-----------------------------------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
  //,-----------------------------------------------------------------------------------------------------------.
     KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
  //`-----------------------------------------------------------------------------------------------------------'
),

[_TOUCHCURSOR] = LAYOUT_planck_grid(
  //,-----------------------------------------------------------------------------------------------------------.
     KC_TAB,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN1, KC_INS,  KC_HOME, KC_UP,   KC_PGUP, KC_BTN1, KC_ACL2,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_ESC,  GUI_WHD, ALT_MSL, SFT_MSD, CTR_MSR, KC_BTN2, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BTN2, KC_ACL1,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_CAPS, _______, _______, _______, KC_BTN4, KC_BTN3, KC_BTN5, KC_END,  KC_DOWN, KC_PGDN, KC_BTN3, KC_ACL0,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, KC_ACL2, KC_ACL1, KC_ACL0, KC_SPC,  _______, _______, _______, _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
),

[_ADJUST] = LAYOUT_planck_grid(
  //,-----------------------------------------------------------------------------------------------------------.
     RESET,   MVI_CLK, _______, _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_ESC,  _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, BEPO,    NUMPAD,  _______, PLOVER,  DEBUG,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
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
    case BEPO:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_BEPO);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_NUMPAD);
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
  case ALT_TAB:
    if (record->event.pressed) {
      if (!is_alt_tab_active) {
	is_alt_tab_active = true;
	register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }
    break;
  case MU_CCED:
    if (record->event.pressed) {
      mu_cced_timer = timer_read();
    } else {
      if (timer_elapsed(mu_cced_timer) < TAPPING_TERM) {
	tap_code16(BP_CCED);
      }
      else {
	tap_code(KC_MUTE);
      }
    }
    break;
  case MVI_CLK:
    if (record->event.pressed) { // clear all mods and keys currently pressed
      clear_keyboard();
    }
    return false;
    break;
  case MVI_CXU:
    if (record->event.pressed) { // C-x u, undo in Emacs
      register_code(KC_LCTL);
      tap_code16(BP_X);
      unregister_code(KC_LCTL);
      tap_code16(BP_U);
    }
    return false;
    break;
  case MVI_CCC:
    if (record->event.pressed) { // C-c ;, comment/uncomment region in Emacs/AucTeX
      register_code(KC_LCTL);
      tap_code16(BP_C);
      unregister_code(KC_LCTL);
      tap_code16(S(BP_COMM));
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
  return false;
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
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > ALT_TAB_TERM) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
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
