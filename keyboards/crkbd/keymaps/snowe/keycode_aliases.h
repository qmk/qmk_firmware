/*
 * Copyright 2020 Drashna Jaelre <@drashna>
 * Copyright 2021 Tyler Thrailkill <@snowe/@snowe2010>
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

#define GUI_ESC GUI_T(KC_ESC)
#define CTL_ESC CTL_T(KC_ESC)
#define SH_BKSP SFT_T(KC_BSPC)
#define SP_RAIS LT(_UPPER, KC_SPC)

#define LOWER MO(_LOWER)
#define RAISE MO(_UPPER)
#define ADJUST MO(_ADJUST)
#define TG_MODS TG(_MODS)
//#define TG_GAME TG(_GAMEPAD)
//#define OS_LWR OSL(_LOWER)
//#define OS_RSE OSL(_UPPER)

//#define KC_SEC1 KC_SECRET_1
//#define KC_SEC2 KC_SECRET_2
//#define KC_SEC3 KC_SECRET_3
//#define KC_SEC4 KC_SECRET_4
//#define KC_SEC5 KC_SECRET_5

#define QWERTY KC_QWERTY
#define DVORAK KC_DVORAK
#define COLEMAK KC_COLEMAK
#define WORKMAN KC_WORKMAN

#define KC_RESET RESET
#define KC_RST KC_RESET

#ifdef SWAP_HANDS_ENABLE
#    define KC_C1R3 SH_TT
#else  // SWAP_HANDS_ENABLE
#    define KC_C1R3 KC_BSPC
#endif  // SWAP_HANDS_ENABLE

#define BK_LWER LT(_LOWER, KC_BSPC)
#define SP_LWER LT(_LOWER, KC_SPC)
#define DL_RAIS LT(_UPPER, KC_DEL)
#define ET_RAIS LT(_UPPER, KC_ENTER)
#define SFT_ENT SFT_T(KC_ENTER)
#define SP_RAIS LT(_UPPER, KC_SPC)

/* OSM keycodes, to keep things clean and easy to change */
#define KC_MLSF OSM(MOD_LSFT)
#define KC_MRSF OSM(MOD_RSFT)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_MEH OSM(MOD_MEH)
#define OS_HYPR OSM(MOD_HYPR)

#define ALT_APP ALT_T(KC_APP)

#define MG_NKRO MAGIC_TOGGLE_NKRO

#define UC_IRNY UC(0x2E2E)
#define UC_CLUE UC(0x203D)
