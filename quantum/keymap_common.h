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
#include "keymap.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
// #include "print.h"
#include "debug.h"

#ifdef BOOTMAGIC_ENABLE
/* NOTE: Not portable. Bit field order depends on implementation */
typedef union {
    uint16_t raw;
    struct {
        bool swap_control_capslock:1;
        bool capslock_to_control:1;
        bool swap_lalt_lgui:1;
        bool swap_ralt_rgui:1;
        bool no_gui:1;
        bool swap_grave_esc:1;
        bool swap_backslash_backspace:1;
        bool nkro:1;
    };
} keymap_config_t;
keymap_config_t keymap_config;
#endif


/* translates key to keycode */
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint16_t keycode);

/* translates Fn keycode to action */
action_t keymap_func_to_action(uint16_t keycode);

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];

// Ability to use mods in layouts
#define LCTL(kc) kc | 0x0100
#define LSFT(kc) kc | 0x0200
#define LALT(kc) kc | 0x0400
#define LGUI(kc) kc | 0x0800
#define RCTL(kc) kc | 0x1100
#define RSFT(kc) kc | 0x1200
#define RALT(kc) kc | 0x1400
#define RGUI(kc) kc | 0x1800

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

#define KC_PIPE LSFT(KC_SLSH)   // |

// Alias for function layers than expand past FN31
#define FUNC(kc) kc | 0x2000

// Aliases
#define S(kc) LSFT(kc)
#define F(kc) FUNC(kc)

#define M(kc) kc | 0x3000

#define MACRODOWN(...) (record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)

// These affect the backlight (if your keyboard has one).
// We don't need to comment them out if your keyboard doesn't have a backlight,
// since they don't take up any space.
#define BL_ON 0x4009
#define BL_OFF 0x4000
#define BL_0 0x4000
#define BL_1 0x4001
#define BL_2 0x4002
#define BL_3 0x4003
#define BL_4 0x4004
#define BL_5 0x4005
#define BL_6 0x4006
#define BL_7 0x4007
#define BL_8 0x4008
#define BL_9 0x4009
#define BL_10 0x400A
#define BL_11 0x400B
#define BL_12 0x400C
#define BL_13 0x400D
#define BL_14 0x400E
#define BL_15 0x400F
#define BL_DEC 0x4010
#define BL_INC 0x4011
#define BL_TOGG 0x4012
#define BL_STEP 0x4013

#define RESET 0x5000
#define DEBUG 0x5001

// GOTO layer - 16 layers max
// when:
// ON_PRESS    = 1
// ON_RELEASE  = 2
// Unless you have a good reason not to do so, prefer  ON_PRESS (1) as your default.
#define TO(layer, when) (layer | 0x5100 | (when << 0x4))

// Momentary switch layer - 256 layer max
#define MO(layer) (layer | 0x5200)

// Set default layer - 256 layer max
#define DF(layer) (layer | 0x5300)

#define MIDI(n) (n | 0x6000)

// For sending unicode codes.
// You may not send codes over 1FFF -- this supports most of UTF8.
// To have a key that sends out Œ, go UC(0x0152)
#define UNICODE(n) (n | 0x8000)
#define UC(n) UNICODE(n)


#endif
