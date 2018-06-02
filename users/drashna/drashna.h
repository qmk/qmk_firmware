/*
Copyright 2017 Christopher Courtney <drashna@live.com> @drashna

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

#ifndef USERSPACE
#define USERSPACE
#include "quantum.h"

// Define layer names
enum userspace_layers {
  _QWERTY = 0,
  _NUMLOCK = 0,
  _COLEMAK,
  _DVORAK,
  _WORKMAN,
  _MODS,
  _GAMEPAD,
  _DIABLO,
  _MACROS,
  _MEDIA,
  _LOWER,
  _RAISE,
  _ADJUST,
};

//define modifiers
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK  (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))


// RGB color codes are no longer located here anymore.  Instead, you will want to
// head to https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h

extern bool clicky_enable;

#ifdef RGBLIGHT_ENABLE
void rgblight_sethsv_default_helper(uint8_t index);
#endif // RGBLIGHT_ENABLE

void tap(uint16_t keycode);
bool process_record_secrets(uint16_t keycode, keyrecord_t *record);


#define EECONFIG_USERSPACE (uint8_t *)19

typedef union {
  uint8_t raw;
  struct {
    bool     clicky_enable    :1;
    bool     rgb_layer_change :1;
    bool     is_overwatch     :1;
    bool     nuke_switch      :1;
  };
} userspace_config_t;

enum userspace_custom_keycodes {
  EPRM = SAFE_RANGE, // can always be here
  VRSN,
  KC_QWERTY,
  KC_COLEMAK,
  KC_DVORAK,
  KC_WORKMAN,
  KC_DIABLO_CLEAR,
  KC_OVERWATCH,
  KC_SALT,
  KC_MORESALT,
  KC_SALTHARD,
  KC_GOODGAME,
  KC_SYMM,
  KC_JUSTGAME,
  KC_GLHF,
  KC_TORB,
  KC_AIM,
  KC_C9,
  KC_GGEZ,
  KC_MAKE,
  KC_RESET,
  KC_RGB_T,
  KC_SECRET_1,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
  KC_CCCV,
  KC_NUKE,

#ifdef UNICODE_ENABLE
  UC_FLIP,
#endif //UNICODE_ENABLE
  NEW_SAFE_RANGE //use "NEWPLACEHOLDER for keymap specific codes
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)


#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3
#define KC_SEC4 KC_SECRET_4
#define KC_SEC5 KC_SECRET_5

#define QWERTY KC_QWERTY
#define DVORAK KC_DVORAK
#define COLEMAK KC_COLEMAK
#define WORKMAN KC_WORKMAN

#define KC_RST KC_RESET

#ifdef SWAP_HANDS_ENABLE
#define KC_C1R3 SH_TT
#else // SWAP_HANDS_ENABLE
#define KC_C1R3 KC_BSPC
#endif // SWAP_HANDS_ENABLE

// OSM keycodes, to keep things clean and easy to change
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
#define ALT_APP ALT_T(KC_APP)

#define MG_NKRO MAGIC_TOGGLE_NKRO


#ifdef TAP_DANCE_ENABLE
enum {
  TD_D3_1 = 0,
  TD_D3_2,
  TD_D3_3,
  TD_D3_4
};
#endif // TAP_DANCE_ENABLE


// Custom Keycodes for Diablo 3 layer
// But since TD() doesn't work when tap dance is disabled
// We use custom codes here, so we can substitute the right stuff
#ifdef TAP_DANCE_ENABLE
#define KC_D3_1 TD(TD_D3_1)
#define KC_D3_2 TD(TD_D3_2)
#define KC_D3_3 TD(TD_D3_3)
#define KC_D3_4 TD(TD_D3_4)
#else // TAP_DANCE_ENABLE
#define KC_D3_1 KC_1
#define KC_D3_2 KC_2
#define KC_D3_3 KC_3
#define KC_D3_4 KC_4
#endif // TAP_DANCE_ENABLE



// Since our quirky block definitions are basically a list of comma separated
// arguments, we need a wrapper in order for these definitions to be
// expanded before being used as arguments to the LAYOUT_xxx macro.
#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)


// Blocks for each of the four major keyboard layouts
// Organized so we can quickly adapt and modify all of them
// at once, rather than for each keyboard, one at a time.
// And this allows for much cleaner blocks in the keymaps.
// For instance Tap/Hold for Control on all of the layouts

// NOTE: These are all the same length.  If you do a search/replace
//       then you need to add/remove underscores to keep the
//       lengths consistent.

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________  CTL_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLASH)


#define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________       KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ CTL_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLASH)

#define ______________COLEMAK_MOD_DH_L1____________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________       KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________ CTL_T(KC_Z),   KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________       KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________       KC_K,    KC_H,    KC_COMM, KC_DOT,  CTL_T(KC_SLASH)


#define _________________DVORAK_L1_________________        KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________        KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________  CTL_T(KC_SCLN),KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________        KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________        KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________        KC_B,    KC_M,    KC_W,    KC_V,    CTL_T(KC_Z)


#define _________________WORKMAN_L1________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________       KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________ CTL_T(KC_Z),   KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________       KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________       KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _________________WORKMAN_R3________________       KC_K,    KC_L,    KC_COMM, KC_DOT,    CTL_T(KC_SLASH)


#define _________________NORMAN_L1_________________       KC_Q,    KC_W,    KC_D,    KC_F,    KC_K
#define _________________NORMAN_L2_________________       KC_A,    KC_S,    KC_E,    KC_T,    KC_G
#define _________________NORMAN_L3_________________ CTL_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B

#define _________________NORMAN_R1_________________       KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN
#define _________________NORMAN_R2_________________       KC_Y,    KC_N,    KC_I,    KC_O,    KC_U
#define _________________NORMAN_R3_________________       KC_P,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLASH)

#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

// Since we have 4 default layouts (QWERTY, DVORAK, COLEMAK and WORKMAN),
// this allows us to quickly modify the bottom row for all of the layouts
// so we don't have to alter it 4 times and hope that we haven't missed
// anything
#define ___________ERGODOX_BOTTOM_LEFT_____________       OSM(MOD_MEH), OSM(MOD_LGUI), KC_LBRC, KC_RBRC
#define ___________ERGODOX_BOTTOM_RIGHT____________       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT


#define __________________ERGODOX_THUMB_CLUSTER_____________________           ALT_T(KC_APP), OSM(MOD_LGUI),                 OSM(MOD_RGUI), CTL_T(KC_ESCAPE), \
                                                                                              KC_HOME,                 KC_PGUP, \
                                                                LT(_LOWER, KC_SPACE),KC_BSPC, KC_END,                  KC_PGDN, KC_DEL,  LT(_RAISE, KC_ENTER)


#endif // !USERSPACE
