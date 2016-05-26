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
#define HYPR(kc) kc | 0x0F00
#define MEH(kc) kc  | 0x0700
#define LCAG(kc) kc  | 0x0D00 // Modifier Ctrl Alt and GUI

#define MOD_HYPR 0xf
#define MOD_MEH 0x7

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
#define FUNC(kc) kc | 0x2000

// Aliases
#define S(kc) LSFT(kc)
#define F(kc) FUNC(kc)

#define M(kc) (kc | 0x3000)

#define MACRODOWN(...) (record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)

// 0x3100+ is free

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (kc | 0x4000 | ((layer & 0xF) << 8))

#define RESET 0x5000
#define DEBUG 0x5001

// MAGIC keycodes
#define MAGIC_SWAP_CONTROL_CAPSLOCK      0x5002
#define MAGIC_UNSWAP_CONTROL_CAPSLOCK    0x5003
#define MAGIC_CAPSLOCK_TO_CONTROL        0x5004
#define MAGIC_UNCAPSLOCK_TO_CONTROL      0x5005
#define MAGIC_SWAP_LALT_LGUI             0x5006
#define MAGIC_UNSWAP_LALT_LGUI           0x5007
#define MAGIC_SWAP_RALT_RGUI             0x5008
#define MAGIC_UNSWAP_RALT_RGUI           0x5009
#define MAGIC_NO_GUI                     0x500a
#define MAGIC_UNNO_GUI                   0x500b
#define MAGIC_SWAP_GRAVE_ESC             0x500c
#define MAGIC_UNSWAP_GRAVE_ESC           0x500d
#define MAGIC_SWAP_BACKSLASH_BACKSPACE   0x500e
#define MAGIC_UNSWAP_BACKSLASH_BACKSPACE 0x500f
#define MAGIC_HOST_NKRO                  0x5010
#define MAGIC_UNHOST_NKRO                0x5011
#define MAGIC_SWAP_ALT_GUI               0x5012
#define MAGIC_UNSWAP_ALT_GUI             0x5013

#define AG_SWAP MAGIC_SWAP_ALT_GUI
#define AG_NORM MAGIC_UNSWAP_ALT_GUI

#define KC_LEAD 0x5014

// Audio on/off
#define AU_ON  0x5020
#define AU_OFF 0x5021
#define AU_TOG 0x5022

// Music mode on/off
#define MU_ON  0x5023
#define MU_OFF 0x5024
#define MU_TOG 0x5025

// Music voice iterate
#define MUV_IN 0x5026
#define MUV_DE 0x5027

// Midi mode on/off
#define MI_ON  0x5028
#define MI_OFF 0x5029

// These affect the backlight (if your keyboard has one).
// We don't need to comment them out if your keyboard doesn't have a backlight,
// since they don't take up any space.
#define BL_ON 0x5079
#define BL_OFF 0x5070
#define BL_0 0x5070
#define BL_1 0x5071
#define BL_2 0x5072
#define BL_3 0x5073
#define BL_4 0x5074
#define BL_5 0x5075
#define BL_6 0x5076
#define BL_7 0x5077
#define BL_8 0x5078
#define BL_9 0x5079
#define BL_10 0x507A
#define BL_11 0x507B
#define BL_12 0x507C
#define BL_13 0x507D
#define BL_14 0x507E
#define BL_15 0x507F
#define BL_DEC 0x5080
#define BL_INC 0x5081
#define BL_TOGG 0x5082
#define BL_STEP 0x5083

#define KC_LSPO 0x5084 // Left shift, open parens when tapped
#define KC_RSPC 0x5085 // Right shift, close parens when tapped
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

// Toggle to layer - 256 layer max
#define TG(layer) (layer | 0x5400)

// One-shot layer - 256 layer max
#define OSL(layer) (layer | 0x5500)

// One-shot mod
#define OSM(layer) (layer | 0x5600)

// chording is currently at 0x57xx

// M-od, T-ap - 256 keycode max
#define MT(mod, kc) (kc | 0x7000 | ((mod & 0xF) << 8))
#define CTL_T(kc) MT(0x1, kc)
#define SFT_T(kc) MT(0x2, kc)
#define ALT_T(kc) MT(0x4, kc)
#define GUI_T(kc) MT(0x8, kc)
#define C_S_T(kc) MT(0x3, kc) // Control + Shift e.g. for gnome-terminal
#define MEH_T(kc) MT(0x7, kc) // Meh is a less hyper version of the Hyper key -- doesn't include Win or Cmd, so just alt+shift+ctrl
#define LCAG_T(kc) MT(0xD, kc) // Left control alt and gui
#define ALL_T(kc) MT(0xF, kc) // see http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/

// Dedicated keycode versions for Hyper and Meh, if you want to use them as standalone keys rather than mod-tap
#define KC_HYPR HYPR(KC_NO)
#define KC_MEH  MEH(KC_NO)

#ifdef UNICODE_ENABLE
    // For sending unicode codes.
    // You may not send codes over 7FFF -- this supports most of UTF8.
    // To have a key that sends out Œ, go UC(0x0152)
    #define UNICODE(n) (n | 0x8000)
    #define UC(n) UNICODE(n)
#endif

// For tri-layer
void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3);
#define IS_LAYER_ON(layer)  (layer_state & (1UL << (layer)))
#define IS_LAYER_OFF(layer) (~layer_state & (1UL << (layer)))


#endif
