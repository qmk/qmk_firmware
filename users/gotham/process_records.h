/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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

#pragma once

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,  // Prints QMK Firmware and board info
    KC_MAKE,            // Run keyboard's customized make command
    KC_CCCV,            // Hold to copy, tap to paste
    KC_LAYOUT,          // Cycle through keyboard layouts
    NEW_SAFE_RANGE      // use this instead of SAFE_RANGE for keymap specific codes
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define TG_GAME TG(_GAME)
#define TG_GNAV TG(_GAMENAV)
#define MO_GNUM MO(_GAMENUM)
#define GN_ESC LT(_GAMENUM, KC_ESC)
#define GN_TAB LT(_GAMENUM, KC_TAB)

#define ALT_ESC MT(MOD_LALT, KC_ESC)
#define CTL_EQL MT(MOD_LCTL, KC_EQL)
#define SF_QUOT MT(MOD_RSFT, KC_QUOT)
#define CT_MINS MT(MOD_RCTL, KC_MINS)
#define TAB_CTL MT(MOD_LCTL, KC_TAB)
#define TAB_SFT MT(MOD_LSFT, KC_TAB)
#define ENT_CTL MT(MOD_LCTL, KC_ENT)
#define ENT_SFT MT(MOD_LSFT, KC_ENT)

#define SP_LOWR LT(_LOWER, KC_SPC)
#define TB_LOWR LT(_LOWER, KC_TAB)
#define BK_LOWR LT(_LOWER, KC_BSPC)
#define EN_LOWR LT(_LOWER, KC_ENTER)

#define SP_RAIS LT(_RAISE, KC_SPC)
#define TB_RAIS LT(_RAISE, KC_TAB)
#define BK_RAIS LT(_RAISE, KC_BSPC)
#define EN_RAIS LT(_RAISE, KC_ENTER)

#define MS_DEL LT(_MOUSE, KC_DEL)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
