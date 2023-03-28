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
#include "keymap_canadian_multilingual.h"


enum planck_layers {
  _MACQWERTY,
  _MACRAISE,
  _MACLOWER,
  _QWERTY,
  _LOWER,
  _RAISE,
  _KEYSHORTCUT,
  _MACKEYSHORTCUT,
  _ADJUST,
  _ADJUST2
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  MACQWERTY,
  MACQWERTYENG,
  QWERTYENG,
  BACKLIT
};

#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define KEYSHC TT(_KEYSHORTCUT)
#define MACKEYSHC TT(_MACKEYSHORTCUT)
#define MACRAISE TT(_MACRAISE)
#define MACLOWER TT(_MACLOWER)

/* ---------- Variables for shortcut ---------- */
//----------     Shortcut on MAC     ----------
#define MACOS_LCK LCTL(LSFT(KC_SYSTEM_POWER))
// LONG ASS SHORTCUT



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,----------------------------------------------------------------------------------------------.
 * |       Tab       |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  |
 * |-----------------+------+------+------+------+------+------+------+------+------+------+------|
 * |       Esc       |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  `   |
 * |-----------------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift(caps lock)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   é  |Enter |
 * |-----------------+------+------+------+------+------+------+------+------+------+------+------|
 * |       Ctrl      | GUI  |  Alt |   ?  |Space |Lower |Raise | Bksp | Left | Down |  Up  |Right |
 * `----------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LSFT_T(KC_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LSFT_T(KC_ENT),
    KC_LCTL,         KC_LGUI, KC_LALT, BACKLIT, LOWER,  KC_SPC,   KEYSHC,   RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),

    /* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  Del |   !  |   "  |   @  |   $  |   %  |   ?  |   &  |  Up  |   «  |   »  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  |   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | Left | Down |Right |  ¸   |   ^  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Home |  End |Pg up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_DEL,  KC_EXLM, KC_AT,   RALT(KC_2), KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_UP,    KC_NUBS, S(KC_NUBS), KC_BSPC,
    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LEFT,    KC_DOWN,    KC_RGHT, KC_RBRC, KC_LCBR,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  Del |   1  |   2  |   3  |   =  |   &  |   *  |  (   |   )  |  {   |  }   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   #  |   4  |   5  |   6  |   +  |   -  |   _  |  <   |   >  |  [   |  ]   |  ¨   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   7  |   8  |   9  |  0   |   /  |   \  |  ~   |      |      | Ins  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_DEL,  KC_1,    KC_2,    KC_3,    KC_EQL, KC_AMPR, KC_PAST, KC_LPRN, KC_RPRN, RALT(KC_QUOT), RALT(KC_NUHS), KC_BSPC,
    KC_GRV,  KC_4,    KC_5,    KC_6,    KC_PPLS, KC_MINS, KC_UNDS, KC_NUHS,   S(KC_NUHS),   RALT(KC_LBRC), RALT(KC_RBRC), KC_RCBR,
    _______, KC_7,    KC_8,    KC_9,    KC_0,    KC_PSLS,  RALT(KC_GRV), RALT(KC_SCLN), _______, _______, KC_INS, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY
),
    /* Keyshortcut
 * ,---------------------------------------------------------------------------------------------.
 * |  Del |ctrl+alt+del|          |   @  |   $  |   %  |   ?  |   &  |  Up  |   «  |   »  |      |
 * |------+------------+----------+------+------+------+------+------+------+------+------+------|
 * |  |   |     F1     |     F2   |  F3  |  F4  |  F5  |  F6  | Left | Down |Right |  ¸   |   ^  |
 * |------+------------+----------+------+------+------+------+------+------+------+------+------|
 * |      |  alt+enter |alt+insert|  F9  |  F10 |  F11 |  F12 | Home |  End |Pg up |Pg Dn |      |
 * |------+------------+----------+------+------+------+------+------+------+------+------+------|
 * |      |            |          |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `---------------------------------------------------------------------------------------------'
 */
[_KEYSHORTCUT] = LAYOUT_planck_grid(
    KC_DEL,  KC_CAD,           KC_AT,          RALT(KC_2), KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_INS,   KC_NUBS, S(KC_NUBS), KC_BSPC,
    KC_TILD, KC_F1,            KC_F2,          KC_F3,      KC_F4,   KC_F5,   KC_F6,   KC_LEFT, KC_DOWN, KC_RGHT, KC_RBRC,    KC_LCBR,
    _______, LALT(KC_ENTER),   LALT(KC_INS),   KC_F9,      KC_F10,  KC_F11,  KC_F12,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN,    _______,
    _______, _______,          _______,        _______,    _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU,    KC_MPLY
),


/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|  ENG |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      | PROG |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______,  RGB_M_B, RGB_M_G, RGB_TOG,
    _______, _______, _______, _______, _______, _______, _______, QWERTY, MACQWERTY,  _______, _______, MU_OFF,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),
[_ADJUST2] = LAYOUT_planck_grid(
    _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______,  BL_BRTG, BL_STEP, BL_TOGG,
    _______, _______, _______, _______, _______, _______, _______, QWERTY, MACQWERTY,  _______, _______, MU_OFF,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

/* ----- For Mac -----*/
    /* Qwerty CSA
     * ,----------------------------------------------------------------------------------------------.
     * |       Esc       |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  |
     * |-----------------+------+------+------+------+------+------+------+------+------+------+------|
     * |       Tab      |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  `   |
     * |-----------------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift(caps lock)|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   é  |Enter |
     * |-----------------+------+------+------+------+------+------+------+------+------+------+------|
     * |       Ctrl      | GUI  |  Alt |Lower |Space |KeySHC|Raise | Bksp | Left | Down |  Up  |Right |
     * `----------------------------------------------------------------------------------------------'
     */
[_MACQWERTY] = LAYOUT_planck_grid(
    KC_ESC,          KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,          KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, CA_GRV,
    LSFT_T(KC_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,  CA_EACU, LSFT_T(KC_ENT),
    KC_LCTL,         MACKEYSHC,  KC_LALT, KC_LGUI, MACLOWER, KC_SPC, MACKEYSHC,  MACRAISE, KC_RGUI, KC_RALT, KC_LCTL,   KC_RGHT
),

  /* Raise on Mac
 * ,-----------------------------------------------------------------------------------.
 * |  Del |   !  |   "  |   @  |   $  |   %  |   ?  |   &  |  Up  |   «  |   »  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  |   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | Left | Down |Right |  ¸   |   ^  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Home |  End |Pg up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_MACRAISE] = LAYOUT_planck_grid(
    KC_DEL,  CA_EXLM, CA_DQUO, CA_AT,   CA_DLR,  CA_PERC, CA_QUES, CA_AMPR,    KC_UP,   CA_LDAQ, CA_RDAQ, KC_BSPC,
    CA_PIPE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LEFT,    KC_DOWN, KC_RGHT, KC_RBRC, CA_CIRC,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME,    KC_END,  KC_PGUP, KC_PGDN,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Lower on Mac
 * ,-----------------------------------------------------------------------------------.
 * |  Del |   1  |   2  |   3  |   =  |   &  |   *  |  (   |   )  |  {   |  }   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   #  |   4  |   5  |   6  |   +  |   -  |   _  |  <   |   >  |  [   |  ]   |  ¨   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   7  |   8  |   9  |  0   |   /  |   \  |  ~   |      |      | Ins  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_MACLOWER] = LAYOUT_planck_grid(
    KC_DEL,  KC_1,    KC_2,    KC_3,    CA_EQL, CA_AMPR, CA_ASTR, CA_LPRN, CA_RPRN, CA_LCBR, CA_RCBR, KC_BSPC,
    KC_GRV,  KC_4,    KC_5,    KC_6,    CA_PLUS, CA_MINS, CA_UNDS, CA_LABK,   CA_RABK,   CA_LBRC, CA_RBRC, CA_DIAE,
    _______, KC_7,    KC_8,    KC_9,    KC_0,    CA_SLSH,  CA_BSLS, CA_DTIL, _______, _______, KC_INS, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY
),

    /* Keyshortcut
 * ,-----------------------------------------------------------------------------------------.
 * |cmd+ctrl+esc|      |      |      |      |      |      |      |      |      |      |      |
 * |------------+------+------+------+------+------+------+------+------+------+------+------|
 * |            |      |      |      |      |      |      |      |      | Lock |      |      |
 * |------------+------+------+------+------+------+------+------+------+------+------+------|
 * |            |      |      |      |      |      |      |      |      |      |      |      |
 * |------------+------+------+------+------+------+------+------+------+------+------+------|
 * |            |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------------'
 */
[_MACKEYSHORTCUT] = LAYOUT_planck_grid(
    KC_COE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, MACOS_LCK, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
      state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
      state = update_tri_layer_state(state, _MACLOWER, _MACRAISE, _ADJUST2);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("QWERTY\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case MACQWERTY:
      if (record->event.pressed) {
        print("MACQWERTY\n");
        set_single_persistent_default_layer(_MACQWERTY);
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
  }
  return true;
}

bool muse_mode = false;



bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
