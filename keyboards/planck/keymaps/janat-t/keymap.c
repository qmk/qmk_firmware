/* Copyright 2023 Taerakul Janat
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

#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _NOMOD,
  _LOWER,
  _RAISE,
  _NAV,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  NOMOD
};

#define MOU_Z LT(_MOUSE, KC_Z)
#define MOU_SCLN LT(_MOUSE, KC_SCLN)
#define NAV_SLSH LT(_NAV, KC_SLSH)
#define NAV_Z LT(_NAV, KC_Z)

// Left-hand home row mods QWERTY
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods QWERTY
#define SFT_J RSFT_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)

// Left-hand home row mods COLEMAK
#define CTL_A LCTL_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define GUI_S LGUI_T(KC_S)
#define SHFT_T LSFT_T(KC_T)

// Right-hand home row mods COLEMAK
#define SFT_N RSFT_T(KC_N)
#define GUI_E RGUI_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define CTL_O RCTL_T(KC_O)

#define HYPER MEH(KC_LGUI)

#define CT_ESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  BS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  |Ctl-A |Alt-S |GUI-D |Shft-F|   G  |   H  |Shft-J|GUI-K |Alt-L |Ctl-; |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  CW  |MOU-Z |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |NAV-/ |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | HYPER| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CT_ESC,  CTL_A,   ALT_S,   GUI_D,   SFT_F,   KC_G,    KC_H,    SFT_J,   GUI_K,   ALT_L,   CTL_SCLN,KC_QUOT,
    CW_TOGG, MOU_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  NAV_SLSH,KC_ENT,
    HYPER,   KC_LCTL, KC_LALT, KC_LGUI, TL_LOWR,   KC_SPC,  KC_SPC,  TL_UPPR,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  |  BS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  |Ctl-A |Alt-R |GUI-S |Shft-T|   G  |   M  |Shft-N|GUI-E |Alt-I |Ctl-O |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  CW  |MOU-Z |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |NAV-/ |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | HYPER| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    CT_ESC,  CTL_A,   ALT_R,   GUI_S,   SHFT_T,   KC_G,    KC_M,    SFT_N,   GUI_E,   ALT_I,   CTL_O,   KC_QUOT,
    CW_TOGG, MOU_Z,   KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  NAV_SLSH,KC_ENT,
    HYPER,   KC_LCTL, KC_LALT, KC_LGUI, TL_LOWR,   KC_SPC,  KC_SPC,  TL_UPPR,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
/* Qwerty without home row mod
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  BS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | HYPER| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_NOMOD] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CT_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    HYPER,   KC_LCTL, KC_LALT, KC_LGUI, TL_LOWR,   KC_SPC,  KC_SPC,  TL_UPPR,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  BS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  | F13  | F14  | F15  | F16  | F17  | F18  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | F19  | F20  | F21  | F22  | F23  | F24  |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |Adjust| Prev | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MPRV,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  BS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  | F10  | F11  | F12  |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Adjust|             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Nav
 * /-----------------------------------------------------------------------------------\
 * |      | Home | PgUp | PgDn | End  |      |  T1  |  T←  |  T→  |  T9  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Shift |      |  ←   |  ↓   |  ↑   |  →   | Del  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |[Nav] |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |    Shift    |      |      |      |      |      |
 * \-----------------------------------------------------------------------------------/
 */
[_NAV] = LAYOUT_planck_grid(
    _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______, G(KC_1), SCMD(KC_LBRC), SCMD(KC_RBRC), G(KC_9), _______, _______,
    _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_LSFT, KC_LSFT, _______, _______, _______, _______, _______
),

/* Mouse
 * /-----------------------------------------------------------------------------------\
 * |      |      |  S↓  |  M↑  |  S↑  |      |  S←  |  S↓  |  S↑  |  S→  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  M←  |  M↓  |  M→  |      |  M←  |  M↓  |  M↑  |  M→  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |[Mou] |      |      |      |  M3  |  M3  |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |  M2  |  LeftClick  |  M2  |      |      |      |      |
 * \-----------------------------------------------------------------------------------/
 */
[_MOUSE] = LAYOUT_planck_grid(
    _______, _______, KC_WH_D, KC_MS_U, KC_WH_U, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
    _______, _______, _______, _______, _______, KC_BTN3, KC_BTN3, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * | PWR  | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|NoMod |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    KC_PWR,  QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, NOMOD,   _______,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case NOMOD:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_NOMOD);
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
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
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
