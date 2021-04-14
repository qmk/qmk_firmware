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
/* #include "muse.h" */
#include "unicodes.h"
#include "customkey.h"

/* #include "keymap_danish.h" */
#include "keymap_spanish.h"

enum preonic_layers {
  _QWERTY,
  _QWERTY_ESP,
  _QWERTY_GRK,
  _MATH,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTY_ESP,
  QWERTY_GRK,
  MATH,
  LOWER,
  RAISE,
  MORE,
  PSSW,
  TO,
  FROM,
  OCPRN,
  OCBRC,
  OCCBR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |`/ESC |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |LGUI/:|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Ctrl/'|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Sf/{ |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sft/\ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RGUI | MORE |Ctl/[ |Alt/( |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
 KC_GESC, KC_1, KC_2,    KC_3,    KC_4,  KC_5,    KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC,
 KC_TAB,  KC_Q, KC_W,    KC_E,    KC_R,  KC_T,    KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_ENT,
 KC_LSPO, KC_A, KC_S,    KC_D,    KC_F,  KC_G,    KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, SFT_QUOT,
 KC_RSPC, KC_Z, KC_X,    KC_C,    KC_V,  KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, CTL_BSLS,
 KC_RGUI, MORE, CTL_LBR, KC_LAPO, LOWER, CTL_SPC, CTL_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
 _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_PSCR,
 _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_DQT,
 OCCBR,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_LT,   KC_GT,   KC_QUES, KC_PIPE,
 _______, _______, OCBRC,   OCPRN,   _______, KC_MPLY, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
 KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, OCPRN,   OCBRC,   OCCBR,
 KC_TILD, KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, _______, _______, _______, _______, _______, _______, _______,
 KC_RCBR, KC_UNDS, KC_PLUS, _______, _______, _______, _______, _______, FROM,    TO,      _______, _______,
 _______, _______, KC_RBRC, KC_RPRN, _______, KC_SPC,  KC_SPC,  _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
 RESET,   _______,  _______, _______, _______, _______, _______, _______, _______,    _______,    _______, KC_PWR,
 PSSW,    _______,  _______, _______, _______, _______, _______, _______, _______,    _______,    _______, KC_SLEP,
 _______, RGB_SAD,  RGB_SAI, _______, _______, _______, _______, QWERTY,  QWERTY_ESP, QWERTY_GRK, MATH,    _______,
 RGB_TOG, RGB_RMOD, RGB_MOD, _______, _______, _______, _______, _______, _______,    _______,    _______, _______,
 RGB_SPD, RGB_VAD,  RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______,    _______,    _______, _______
),

/* QWERTY_ESP
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY_ESP] = LAYOUT_preonic_grid(
 ES_MORD, ES_1,    ES_2,    ES_3,    ES_4,  ES_5,    ES_6,    ES_7,  ES_8,    ES_9,    ES_0,    KC_BSPC,
 KC_TAB,  ES_Q,    ES_W,    ES_E,    ES_R,  ES_T,    ES_Y,    ES_U,  ES_I,    ES_O,    ES_P,    KC_ENT,
 KC_LSPO, ES_A,    ES_S,    ES_D,    ES_F,  ES_G,    ES_H,    ES_J,  ES_K,    ES_L,    ES_NTIL, SFT_CCED,
 SFT_GRV, ES_Z,    ES_X,    ES_C,    ES_V,  ES_B,    ES_N,    ES_M,  ES_COMM, ES_DOT,  ES_QUOT, CTL_ACUT,
 KC_RGUI, KC_ALGR, CTL_LBR, KC_LAPO, LOWER, CTL_SPC, CTL_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Qwerty Greek
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY_GRK] = LAYOUT_preonic_grid(
 KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
 KC_TAB,  GK_XI,   GK_THTA, GK_EPS,  GK_RHO,  GK_TAU,  GK_PSI,  KC_U,    GK_IOTA, GK_OMGA, GK_PI,   KC_ENT,
 KC_LSPO, GK_ALPH, GK_SGMA, GK_DLTA, GK_PHI,  GK_GMMA, GK_ETA,  KC_J,    GK_KPPA, GK_LMBD, KC_SCLN, SFT_QUOT,
 KC_RSPC, GK_ZETA, GK_CHI,  GK_OMI,  GK_UPS,  GK_BETA, GK_NU,   GK_MU,   KC_COMM, KC_DOT,  KC_SLSH, CTL_BSLS,
 KC_RGUI, MORE,    CTL_LBR, KC_LAPO, _______, CTL_SPC, CTL_SPC, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Qwerty Math
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_MATH] = LAYOUT_preonic_grid(
 KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC,
 KC_TAB,  GK_XI,   GK_THTA, GK_EPS,  GK_RHO, GK_TAU,  GK_PSI,  KC_U,  MTH_IN,  GK_OMGA, GK_PI,   KC_ENT,
 KC_LSPO, GK_ALPH, GK_SGMA, GK_DLTA, GK_PHI, GK_GMMA, GK_ETA,  KC_J,  GK_KPPA, GK_LMBD, KC_SCLN, SFT_QUOT,
 KC_RSPC, GK_ZETA, GK_CHI,  GK_OMI,  GK_UPS, GK_BETA, GK_NU,   GK_MU, KC_COMM, KC_DOT,  KC_SLSH, CTL_BSLS,
 KC_RGUI, MORE,    CTL_LBR, KC_LAPO, LOWER,  CTL_SPC, CTL_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
  case PSSW:
    if (record->event.pressed) {
      SEND_STRING("");
    }
    return false;
    break;
  case TO:
    if (record->event.pressed) {
      SEND_STRING("->");
    }
    return false;
    break;
  case FROM:
    if (record->event.pressed) {
      SEND_STRING("<-");
    }
    return false;
    break;
  case OCPRN:
    if (record->event.pressed) {
      SEND_STRING("()");
    }
    return false;
    break;
  case OCBRC:
    if (record->event.pressed) {
      SEND_STRING("[]");
    }
    return false;
    break;
  case OCCBR:
    if (record->event.pressed) {
      SEND_STRING("{}");
    }
    return false;
    break;
  case QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
      SEND_STRING(SS_RGUI("z"));
    }
    return false;
    break;
  case QWERTY_ESP:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY_ESP);
      SEND_STRING(SS_RGUI("z"));
    }
    return false;
    break;
  case MATH:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_MATH);
    }
    return false;
    break;
  case QWERTY_GRK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY_GRK);
    }
    return false;
    break;
  case MORE:
    if (record->event.pressed) {
      layer_on(_MATH);
      update_tri_layer(_RAISE, _MATH, _QWERTY_GRK);
    } else {
      layer_off(_MATH);
      update_tri_layer(_RAISE, _MATH, _QWERTY_GRK);
    }
    return false;
    break;
  }
  return true;
};

/* Local Variables: */
/* before-save-hook: nil */
/* eval: (setq-local before-save-hook nil) */
/* End: */
