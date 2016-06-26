/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
// #include "print.h"
#include "debug.h"
#include "keycode_config.h"

/* translates key to keycode */
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint16_t keycode);

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];

enum quantum_keycodes {
    // Ranges used in shortucuts - not to be used directly
    QK_TMK                = 0x0000,
    QK_TMK_MAX            = 0x00FF,
    QK_MODS               = 0x0100,
    QK_LCTL               = 0x0100,
    QK_LSFT               = 0x0200,
    QK_LALT               = 0x0400,
    QK_LGUI               = 0x0800,
    QK_RCTL               = 0x1100,
    QK_RSFT               = 0x1200,
    QK_RALT               = 0x1400,
    QK_RGUI               = 0x1800,
    QK_MODS_MAX           = 0x1FFF,
    QK_FUNCTION           = 0x2000,
    QK_FUNCTION_MAX       = 0x2FFF,
    QK_MACRO              = 0x3000,
    QK_MACRO_MAX          = 0x3FFF,
    QK_LAYER_TAP          = 0x4000,
    QK_LAYER_TAP_MAX      = 0x4FFF,
    QK_TO                 = 0x5000,
    QK_TO_MAX             = 0x50FF,
    QK_MOMENTARY          = 0x5100,
    QK_MOMENTARY_MAX      = 0x51FF,
    QK_DEF_LAYER          = 0x5200,
    QK_DEF_LAYER_MAX      = 0x52FF,
    QK_TOGGLE_LAYER       = 0x5300,
    QK_TOGGLE_LAYER_MAX   = 0x53FF,
    QK_ONE_SHOT_LAYER     = 0x5400,
    QK_ONE_SHOT_LAYER_MAX = 0x54FF,
    QK_ONE_SHOT_MOD       = 0x5500,
    QK_ONE_SHOT_MOD_MAX   = 0x55FF,
#ifndef DISABLE_CHORDING
    QK_CHORDING           = 0x5600,
    QK_CHORDING_MAX       = 0x56FF,
#endif
    QK_MOD_TAP            = 0x6000,
    QK_MOD_TAP_MAX        = 0x6FFF,
#ifdef UNICODE_ENABLE
    QK_UNICODE            = 0x8000,
    QK_UNICODE_MAX        = 0xFFFF,
#endif

    // Loose keycodes - to be used directly

    RESET = 0x7000,
    DEBUG,
    MAGIC_SWAP_CONTROL_CAPSLOCK,
    MAGIC_CAPSLOCK_TO_CONTROL,
    MAGIC_SWAP_LALT_LGUI,
    MAGIC_SWAP_RALT_RGUI,
    MAGIC_NO_GUI,
    MAGIC_SWAP_GRAVE_ESC,
    MAGIC_SWAP_BACKSLASH_BACKSPACE,
    MAGIC_HOST_NKRO,
    MAGIC_SWAP_ALT_GUI,
    MAGIC_UNSWAP_CONTROL_CAPSLOCK,
    MAGIC_UNCAPSLOCK_TO_CONTROL,
    MAGIC_UNSWAP_LALT_LGUI,
    MAGIC_UNSWAP_RALT_RGUI,
    MAGIC_UNNO_GUI,
    MAGIC_UNSWAP_GRAVE_ESC,
    MAGIC_UNSWAP_BACKSLASH_BACKSPACE,
    MAGIC_UNHOST_NKRO,
    MAGIC_UNSWAP_ALT_GUI,

    // Leader key
#ifndef DISABLE_LEADER
    KC_LEAD,
#endif

    // Audio on/off/toggle
    AU_ON,
    AU_OFF,
    AU_TOG,

    // Music mode on/off/toggle
    MU_ON,
    MU_OFF,
    MU_TOG,

    // Music voice iterate
    MUV_IN,
    MUV_DE,

    // Midi mode on/off
    MIDI_ON,
    MIDI_OFF,

    // Backlight functionality
    BL_0,
    BL_1,
    BL_2,
    BL_3,
    BL_4,
    BL_5,
    BL_6,
    BL_7,
    BL_8,
    BL_9,
    BL_10,
    BL_11,
    BL_12,
    BL_13,
    BL_14,
    BL_15,
    BL_DEC,
    BL_INC,
    BL_TOGG,
    BL_STEP,

    // Left shift, open paren
    KC_LSPO,

    // Right shift, close paren
    KC_RSPC,

    // always leave at the end
    SAFE_RANGE
};

// Ability to use mods in layouts
#define LCTL(kc) (kc | QK_LCTL)
#define LSFT(kc) (kc | QK_LSFT)
#define LALT(kc) (kc | QK_LALT)
#define LGUI(kc) (kc | QK_LGUI)
#define RCTL(kc) (kc | QK_RCTL)
#define RSFT(kc) (kc | QK_RSFT)
#define RALT(kc) (kc | QK_RALT)
#define RGUI(kc) (kc | QK_RGUI)

#define HYPR(kc) (kc | QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI)
#define MEH(kc)  (kc | QK_LCTL | QK_LSFT | QK_LALT)
#define LCAG(kc) (kc | QK_LCTL | QK_LALT | QK_LGUI)

#define MOD_HYPR 0xf
#define MOD_MEH 0x7


// Aliases for shifted symbols
// Each key has a 4-letter code, and some have longer aliases too.
// While the long aliases are descriptive, the 4-letter codes
// make for nicer grid layouts (everything lines up), and are
// the preferred style for Quantum.
#define KC_TILD LSFT(KC_GRV)    // ~
#define KC_TILDE    KC_TILD

#define KC_EXLM LSFT(KC_1)      // !
#define KC_EXCLAIM  KC_EXLM

#define KC_AT   LSFT(KC_2)      // @

#define KC_HASH LSFT(KC_3)      // #

#define KC_DLR  LSFT(KC_4)      // $
#define KC_DOLLAR   KC_DLR

#define KC_PERC LSFT(KC_5)      // %
#define KC_PERCENT  KC_PERC

#define KC_CIRC LSFT(KC_6)      // ^
#define KC_CIRCUMFLEX   KC_CIRC

#define KC_AMPR LSFT(KC_7)      // &
#define KC_AMPERSAND    KC_AMPR

#define KC_ASTR LSFT(KC_8)      // *
#define KC_ASTERISK KC_ASTR

#define KC_LPRN LSFT(KC_9)      // (
#define KC_LEFT_PAREN   KC_LPRN

#define KC_RPRN LSFT(KC_0)      // )
#define KC_RIGHT_PAREN  KC_RPRN

#define KC_UNDS LSFT(KC_MINS)   // _
#define KC_UNDERSCORE   KC_UNDS

#define KC_PLUS LSFT(KC_EQL)    // +

#define KC_LCBR LSFT(KC_LBRC)   // {
#define KC_LEFT_CURLY_BRACE KC_LCBR

#define KC_RCBR LSFT(KC_RBRC)   // }
#define KC_RIGHT_CURLY_BRACE    KC_RCBR

#define KC_LABK LSFT(KC_COMM)   // <
#define KC_LEFT_ANGLE_BRACKET   KC_LABK

#define KC_RABK LSFT(KC_DOT)    // >
#define KC_RIGHT_ANGLE_BRACKET  KC_RABK

#define KC_COLN LSFT(KC_SCLN)   // :
#define KC_COLON    KC_COLN

#define KC_PIPE LSFT(KC_BSLS)   // |

#define KC_LT LSFT(KC_COMM)     // <

#define KC_GT LSFT(KC_DOT)      // >

#define KC_QUES LSFT(KC_SLSH)   // ?
#define KC_QUESTION KC_QUES

#define KC_DQT LSFT(KC_QUOT)   // "
#define KC_DOUBLE_QUOTE KC_DQT
#define KC_DQUO KC_DQT

#define KC_DELT KC_DELETE // Del key (four letter code)

// Alias for function layers than expand past FN31
#define FUNC(kc) (kc | QK_FUNCTION)

// Aliases
#define S(kc) LSFT(kc)
#define F(kc) FUNC(kc)

#define M(kc) (kc | QK_MACRO)

#define MACRODOWN(...) (record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (kc | QK_LAYER_TAP | ((layer & 0xF) << 8))

#define AG_SWAP MAGIC_SWAP_ALT_GUI
#define AG_NORM MAGIC_UNSWAP_ALT_GUI

#define BL_ON  BL_9
#define BL_OFF BL_0

#define MI_ON MIDI_ON
#define MI_OFF MIDI_OFF

// GOTO layer - 16 layers max
// when:
// ON_PRESS    = 1
// ON_RELEASE  = 2
// Unless you have a good reason not to do so, prefer  ON_PRESS (1) as your default.
#define TO(layer, when) (layer | QK_TO | (when << 0x4))

// Momentary switch layer - 256 layer max
#define MO(layer) (layer | QK_MOMENTARY)

// Set default layer - 256 layer max
#define DF(layer) (layer | QK_DEF_LAYER)

// Toggle to layer - 256 layer max
#define TG(layer) (layer | QK_TOGGLE_LAYER)

// One-shot layer - 256 layer max
#define OSL(layer) (layer | QK_ONE_SHOT_LAYER)

// One-shot mod
#define OSM(layer) (layer | QK_ONE_SHOT_MOD)

// M-od, T-ap - 256 keycode max
#define MT(mod, kc) (kc | QK_MOD_TAP | ((mod & 0xF) << 8))
#define CTL_T(kc) MT(MOD_LCTL, kc)
#define SFT_T(kc) MT(MOD_LSFT, kc)
#define ALT_T(kc) MT(MOD_LALT, kc)
#define GUI_T(kc) MT(MOD_LGUI, kc)
#define C_S_T(kc) MT((MOD_LCTL | MOD_LSFT), kc) // Control + Shift e.g. for gnome-terminal
#define MEH_T(kc) MT((MOD_LCTL | MOD_LSFT | MOD_LALT), kc) // Meh is a less hyper version of the Hyper key -- doesn't include Win or Cmd, so just alt+shift+ctrl
#define LCAG_T(kc) MT((MOD_LCTL | MOD_LALT | MOD_LGUI), kc) // Left control alt and gui
#define ALL_T(kc) MT((MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI), kc) // see http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/

// Dedicated keycode versions for Hyper and Meh, if you want to use them as standalone keys rather than mod-tap
#define KC_HYPR HYPR(KC_NO)
#define KC_MEH  MEH(KC_NO)

#ifdef UNICODE_ENABLE
    // For sending unicode codes.
    // You may not send codes over 7FFF -- this supports most of UTF8.
    // To have a key that sends out Œ, go UC(0x0152)
    #define UNICODE(n) (n | QK_UNICODE)
    #define UC(n) UNICODE(n)
#endif


#endif
