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
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ECDR | Ctrl | Alt  | GUI  |Space |Lower |Raise |Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    RSFT_T(KC_MPLY),  KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  LOWER,   RAISE,   KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
),

/* Lower
 *                                           v-------NUM PAD------v
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   *  |   /  |   7  |   8  |   9  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |   $  |   %  |   ^  |   +  |   -  |   4  |   5  |   6  |   [  |   ]  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |   &  |   ?  |   :  |   ~  |   .  |   1  |   2  |   3  |   <  |   >  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ECDR | Ctrl | Alt  | GUI  |Space |Lower |Raise |   0  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_GRV,  KC_EXLM, KC_AT,    KC_HASH,  KC_ASTR,  KC_PSLS, KC_7,   KC_8,  KC_9,  KC_LPRN,  KC_RPRN,  KC_BSPC,
    KC_ESC,  KC_DLR,  KC_PERC,  KC_CIRC,  KC_PLUS,  KC_MINS, KC_4,   KC_5,  KC_6,  KC_LBRC,  KC_RBRC,  KC_PEQL,
    KC_LSFT, KC_AMPR, KC_QUES,  KC_COLN,  KC_TILD,  KC_DOT,  KC_1,   KC_2,  KC_3,  KC_LABK,  KC_RABK,  KC_ENT,
    RSFT_T(KC_MPLY),  KC_LCTL,  KC_LALT,  KC_LGUI,  KC_SPC,  LOWER,  RAISE, KC_0,  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RGHT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |SLEEP |  BR- |  BR+ |  <<  | PLAY |  >>  | MUTE | VOL- | VOL+ |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   "  |   \  |   [  |   ]  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   ?  |   :  |   <  |   >  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ECDR | Ctrl | Alt  | GUI  |Space |Lower |Raise |Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_SLEP, KC_BRID, KC_BRIU, KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE, KC__VOLDOWN, KC__VOLUP, KC_LPRN, KC_RPRN,  KC_BSPC,
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_DQT,      KC_BSLS,   KC_LBRC, KC_RBRC,  KC_PEQL,
    KC_LSFT, KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_QUES,     KC_COLN,   KC_LABK, KC_RABK,  KC_ENT,
    RSFT_T(KC_MPLY),  KC_LCTL, KC_LALT,  KC_LGUI, KC_SPC,  LOWER,   RAISE,       KC_SPC,    KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT
),

/* Adjust (Lower + Raise)
 *                                                  v--------MOUSE CONTROL------v
 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      |MSE-1 |MSE-2 |MSE-S0|MSE-S1| Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | CALC | MAIL | MDIA |Debug |      |      |MSE-L |MSE-D |MSE-U |MSE-R |RGB-TG|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ECDR | Ctrl | Alt  | GUI  |Space |Lower |Raise |Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    QK_BOOT, _______,  _______,  _______,  _______, _______, _______, KC_BTN1, KC_MS_BTN2, KC_ACL1, KC_ACL2,  KC_BSPC ,
    _______, KC_CALC,  KC_MAIL,  KC_MSEL,  DEBUG,   _______, _______, KC_MS_L, KC_MS_D,    KC_MS_U, KC_MS_R,  RGB_TOG,
    KC_LSFT, _______,  _______,  _______,  _______, _______, _______, _______, _______,    _______, _______,  KC_ENT,
    RSFT_T(KC_MPLY),   KC_LCTL,  KC_LALT,  KC_LGUI, KC_SPC,  LOWER,   RAISE,   KC_SPC,     KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(_RAISE)) {
        if (get_mods() & MOD_BIT(KC_RSFT)) {
            // ZOOM
            // Store which mods are held
            uint8_t mod_state = get_mods();
            // Ignore all shift keys
            del_mods(MOD_MASK_SHIFT);
            if (clockwise) {
                tap_code16(LGUI(KC_PPLS));
            } else {
                tap_code16(LGUI(KC_PMNS));
            }
            // Add back shift keys
            set_mods(mod_state);
        } else if (get_mods() & MOD_BIT(KC_LSFT)) {
            // SCROLL X
            uint8_t mod_state = get_mods();
            del_mods(MOD_MASK_SHIFT);
            if (clockwise) {
                tap_code16(KC_WH_L);
            } else {
                tap_code16(KC_WH_R);
            }
            set_mods(mod_state);
        } else {
            // SCROLL Y
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
            }
        }
    } else {
        if (get_mods() & MOD_BIT(KC_RSFT)) {
            // ZOOM
            uint8_t mod_state = get_mods();
            del_mods(MOD_MASK_SHIFT);
            if (clockwise) {
                tap_code16(LGUI(KC_PPLS));
            } else {
                tap_code16(LGUI(KC_PMNS));
            }
            set_mods(mod_state);
        } else if (get_mods() & MOD_BIT(KC_LSFT)) {
          // BRIGHTNESS
          uint8_t mod_state = get_mods();
          del_mods(MOD_MASK_SHIFT);
          if (clockwise) {
            tap_code16(KC_PAUSE);
          } else {
            tap_code16(KC_SCROLLLOCK);
          }
          set_mods(mod_state);
      } else {
          // VOLUME
          if (clockwise) {
            tap_code(KC__VOLUP);
          } else {
            tap_code(KC__VOLDOWN);
          }
      }
  }
  return true;
}
