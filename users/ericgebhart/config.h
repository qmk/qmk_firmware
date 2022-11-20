/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

// pro-micro v3's don't always detect otherwise.
/* #define SPLIT_USB_DETECT */

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// Sets good default for the speed of the mouse.
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          100
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7

#undef MOUSEKEY_WHEEL_MAX_SPEED
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#undef MOUSEKEY_WHEEL_DELAY

#define MOUSEKEY_WHEEL_MAX_SPEED    5
#define MOUSEKEY_WHEEL_TIME_TO_MAX  60
#define MOUSEKEY_WHEEL_DELAY        100

#undef TAPPING_TOGGLE
#undef TAPPING_TERM
#undef IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TOGGLE  2
#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT


#define TAP_HOLD_TERM    200
#define COMBO_MUST_HOLD_MODS
#define COMBO_HOLD_TERM 150
#define TAP_CODE_DELAY 5  // for send string with delay

// change the behavior of Mod taps for HRMs.
// #define GLOBAL_QUICK_TAP

 /* Control switches for my keymaps. */
 /* if needed, this goes in the keyboard's config.h */
 /* Alternately, fix the number row in the layout template. */
/* #define BASE_NUMBER_ROW    // turn on 4 row base templates. */

// Extensions, turn them on and off.
#define USERSPACE_H "ericgebhart.h"

// Layout definitions, which language, thumb cluster, mod layer.
// Columns in and out.

// the default. set it, use it, set it back.
// US_INT // EN, BEPO, US_INT
#define LANG_IS US_INT
#define DEFAULT_LANG US_INT
#define DEFAULT_LANG_NAME " us"

// Enable a second locale, for another set of layers.
// This will add bepo versions of all layers chosen.
/* #define SECOND_LOCALE BEPO */
/* #define SECOND_LOCALE_NAME " bepo" */

// Choose a mod layer. Can be changed per layer.
// TRNS, ALT, HRS_NAV HRM_GACS, HRM_SCAG, HRM_GASC, MIRYOKU_HRM_GASC
#define MODS_ARE HRS_NAV
#define DEFAULT_MODS MODS_ARE

// Choose a thumb cluster.
// WI, WIa, DEFAULT, TEST, TRNS, MODS, LAYERS, MODS_LAYERS,
// MIRYOKU, MIRYOKU_TR, MODS_LAYERS_NAV,
// The following use THUMB_LETTER to place a letter on the Thumbs.
// for use with the hands down metals, maltron, and rsthd.
// HD, HDA, HD_SIMPLE, TH_LTR, HD_DASH,
// MIRYOKU_TR_LTR, MIRYOKU_LTR
#define THUMBS_ARE DEFAULT
#define DEFAULT_THUMBS DEFAULT

// pick the edge key set. normie, no kc, smart locks or test.
// NORM, NOKC, SML, TEST
#define EDGE_KEY_SET_IS SML
#define DEFAULT_EDGE_SET SML

// for the base layers which need a thumb cluster which takes a letter.
#define HANDS_DOWN_LTR_THUMBS_ARE TH_LTR
#define MALTRON_LTR_THUMBS_ARE TH_LTR
#define RSTHD_LTR_THUMBS_ARE TH_LTR

// layout io, matrix size.
// a reasonable default for most keyboards.
// give a 3x10 and get a 3x12, managed in keyboards/keyboards.h
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6

// OLED STUFF.
#define OLED_CUSTOM_ENABLE // custom oled here.
//#define OLED_LOGO_ENABLE // turn on/off the logo.
#define KEYLOGGER_ENABLE // 1500 bytes, track and print keypress info to oled.
//#define SPLIT_LAYER_STATE_ENABLE  // to sync state between sides.

// EXTENSIONS

// Combos
#define COMBO_REF_LAYER_ENABLE
// #define COMBO_REF_LAYER_TWO_ENABLE
// works if you know the number of your layer.
// otherwise set and use them later.
// #define COMBO_ONLY_FROM_LAYER 2
// #define COMBO_REF_DEFAULT 2


// Console key logging for creation of heatmaps, etc.
// CONSOLE must be enabled for this to work.
// To create Precondition's heat maps, from console key logging
// with hid_listen or qmk console
//#define CONSOLE_KEY_LOGGER_ENABLE  // turn on keylogging for heat maps.

#define ALT_LOCAL_ENABLE // alternate key combinations, with mods as needed.
#define ACCENTED_KEYS_ENABLE // direct access to altgr keys.

#define SMART_LOCK_ENABLE // smart lock layers and mods.
//#define MOD_LOCK_ENABLE  // smart lock mods, similar/overlapping with Smart lock.
#define NSHOT_ENABLE // smart n-shot for count.
//#define ONESHOT_MOD_ENABLE  // oneshot mods, similar/overlapping with nshots

#define TAP_HOLD_ENABLE // tap for one thing, hold for tapping term to get another.
//#define SWAPPER_ENABLE // enable swapper keys.
#define NOT_DEAD_ENABLE // make undead versions (US_DQUO_ND) of dead keys.
//#define ALT_SHIFT_ENABLE // alternate shift behaviors for existing keys.
//#define SEND_STRING_ENABLE // Turn on send string keys
//#define SEND_UNICODE_ENABLE // Unicode must be enabled for this to work.


// Turn on the base layers do not exceed 4 if doing two locales.
// That will likely push a layer past 15 and then it will
// no longer work with the LT macro.

// dvorak and relatives
#define DVORAK_LAYER_ENABLE
//#define DVORAK_RLC_IU_LAYER_ENABLE
//#define CAPEWELL_DVORAK_LAYER_ENABLE
//#define AHEI_LAYER_ENABLE
//#define BOO_LAYER_ENABLE

// qwerty and derivitives
//#define QWERTY_LAYER_ENABLE
//#define AZERTY_LAYER_ENABLE
//#define WORKMAN_LAYER_ENABLE
//#define NORMAN_LAYER_ENABLE

// COLEMAK and relatives
//#define COLEMAK_LAYER_ENABLE
//#define COLEMAK_DH_LAYER_ENABLE
//#define HALMAK_LAYER_ENABLE
//#define MINIMAK_LAYER_ENABLE
//#define MINIMAK_8_LAYER_ENABLE
//#define MINIMAK_12_LAYER_ENABLE

// BEAKL
// #define BEAKL15_LAYER_ENABLE
//#define BEAKL19_LAYER_ENABLE
//#define BEAKL27_LAYER_ENABLE
//#define BEAKLWI_LAYER_ENABLE

// carpalx layouts
//#define CARPALX_QFMLWY_LAYER_ENABLE
//#define CARPALX_QGMLWB_LAYER_ENABLE
//#define CARPALX_QGMLWY_LAYER_ENABLE

// alternate layouts
//#define MALTRON_LAYER_ENABLE
//#define EUCALYN_LAYER_ENABLE
//#define HANDS_UP_LAYER_ENABLE
//#define RSTHD_LAYER_ENABLE
//#define HANDS_UP_LAYER_ENABLE
//#define WHITE_LAYER_ENABLE
//#define ISRT_LAYER_ENABLE
//#define SOUL_LAYER_ENABLE
//#define NIRO_LAYER_ENABLE
//#define ASSET_LAYER_ENABLE
//#define WHORF_LAYER_ENABLE
//#define WHORF6_LAYER_ENABLE

// mtgap and relatives
//#define MTGAP_LAYER_ENABLE
//#define CTGAP_LAYER_ENABLE
//#define APT_LAYER_ENABLE
//#define CANARY_LAYER_ENABLE

// Hands down
#define HD_NEU_NARROW_LAYER_ENABLE
//#define HD_REF_LAYER_ENABLE
//#define HD_DASH_LAYER_ENABLE
//#define HD_ELAN_LAYER_ENABLE
//#define HD_BRONZE_LAYER_ENABLE
//#define HD_SILVER_LAYER_ENABLE
//#define HD_PLATINUM_LAYER_ENABLE
//#define HD_GOLD_LAYER_ENABLE
//#define HD_TITANIUM_LAYER_ENABLE

// A compact optimot for 3x10.
// requires accent characters.
//#define OPTIMOT_COMPACT_LAYER_ENABLE

// 3x12 sized base layers
//--------------------------
//#define HD_NEU_LAYER_ENABLE

// Optimized for french
// All these have accent characters on base layer.
// so these dont work for En, but do for US-international and Bepo.

//#define BEPO_LAYER_ENABLE
//#define OPTIMOT_LAYER_ENABLE
//#define BEAKL19bis_LAYER_ENABLE


// enable transient function layers.
#define SYMBOL_LAYER_ENABLE
#define NAV_LAYER_ENABLE
// #define MOUSE_LAYER_ENABLE
#define TOPROWS_LAYER_ENABLE
// #define LAYERS_LAYER_ENABLE - defunct. always on.
#define KEYPAD_LAYER_ENABLE
//#define ADJUST_LAYER_ENABLE
//#define RGB_LAYER_ENABLE
//#define MEDIA_LAYER_ENABLE
//#define FUNC_LAYER_ENABLE


// define alternate thumb definitions for the transient layers.
#define MEDIA_LAYER_THUMBS MEDIA_THUMBS
#define MOUSE_LAYER_THUMBS MOUSE_THUMBS
#define NAV_LAYER_THUMBS TRNS_THUMBS
#define KEYPAD_LAYER_THUMBS KEYPAD_THUMBS
#define SYMB_LAYER_THUMBS SYMB_THUMBS
#define TOPROWS_LAYER_THUMBS DEFAULT

// Extra character layers.
// Bepo has dead keys (altgr) and accented keycodes
// A layer of accented keys
// #define ACCENTS_LAYER_ENABLE
// A layer of dead keys
// #define MORTE_LAYER_ENABLE
// A layer of the most popular accented keys and dead keys
#define ACCENTS_MORTE_LAYER_ENABLE

// Functional layer choices.
/* configure the function layers. */
/* They have to be turned on above. */
/* Choose one of each as desired. */
/* There are reasonable defaults */
/* for each if nothing is defined. */

/* nav */
//#define NAV_FULL  // monolithic, two sided nav with mouse and arrows.
#define NAV_FULL_LOCK_MODS // Replace left mouse buttons with lockmods.

// Just the non mouse bits, with lock mods, n-shot mods on the left.
// if mousekeys enabled, adds a mouse layer accessible via smart lock.
// #define NAV_NO_MOUSE
// #define NAV_MIRYOKU
// #define NAV_MOUSE_MIRYOKU


/* keypads */
// beakl keypads are usual, if not chosen, regular keypads will be used.
// left side is the default.
// Beakl, except for WI, is only on the left side.
// Miryoku is on the left also.

//#define KEYPAD_RIGHT
#define KEYPAD_BEAKL        // beakl doesn't have a rightside, swap hands?
//#define KEYPAD_MODS      //  give mods on the other side instead of funcs.
//#define KEYPAD_BEAKL_WI  //  right side with hexpad on left.
//#define KEYPAD_MIRYOKU   //  use the miryoku keypad
// the default if nothing chosen,
// is a functionpad on the left and normal keypad on the right.

// funcpad from miryoku
// #define FUNCPAD_MIRYOKU


/* symbols */
// pick one of these or get the default.
//#define SYMBOL_BEAKL         // original - the default if nothing else.
//#define SYMBOL_BEAKL_EXT     // extended for non beakl base layers.
//#define SYMBOL_BEAKL_EXT_VI  // extended with vi keybinding in mind.
#define SYMBOL_BEAKL_C         // more alterations by frequency
// #define SYMBOL_NEO             // The symbol layer from the Neo layout.
// #define SYMBOL_MIRYOKU      // minimalist symbols after miryoku
//#define SYMBOL_BEAKL_WI      // original wi


/* toprows. */
// The default, if not defined, is a standard qwerty set of rows.
// symbols, numbers, function keys. Numbers on the home row.

// #define TOPROWS_BKL_15_NUMS  // center row with Beakl15 order. 40123 76598.
// #define TOPROWS_BKL_19_NUMS // Beakl 19 order: 32104  76598
#define TOPROWS_MOD  // beakl 15 nums, oneshot and smart lock mods. no Fkeys.


#endif
