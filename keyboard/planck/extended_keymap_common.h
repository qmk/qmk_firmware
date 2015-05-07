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
#include "print.h"
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

// Alias for function layers than expand past FN31
#define FUNC(kc) kc | 0x2000

// Aliases
#define S(kc) LSFT(kc)
#define F(kc) FUNC(kc)

// For software implementation of colemak
#define CM_Q    KC_Q
#define CM_W    KC_W
#define CM_F    KC_E
#define CM_P    KC_R
#define CM_G    KC_T
#define CM_J    KC_Y
#define CM_L    KC_U
#define CM_U    KC_I
#define CM_Y    KC_O
#define CM_SCLN KC_P

#define CM_A    KC_A
#define CM_R    KC_S
#define CM_S    KC_D
#define CM_T    KC_F
#define CM_D    KC_G
#define CM_H    KC_H
#define CM_N    KC_J
#define CM_E    KC_K
#define CM_I    KC_L
#define CM_O    KC_SCLN

#define CM_Z    KC_Z
#define CM_X    KC_X
#define CM_C    KC_C
#define CM_V    KC_V
#define CM_B    KC_B
#define CM_K    KC_N
#define CM_M    KC_M
#define CM_COMM KC_COMM
#define CM_DOT  KC_DOT
#define CM_SLSH KC_SLSH

// Make it easy to support these in macros
#define KC_CM_Q    CM_Q    
#define KC_CM_W    CM_W    
#define KC_CM_F    CM_F    
#define KC_CM_P    CM_P    
#define KC_CM_G    CM_G    
#define KC_CM_J    CM_J    
#define KC_CM_L    CM_L    
#define KC_CM_U    CM_U    
#define KC_CM_Y    CM_Y    
#define KC_CM_SCLN CM_SCLN 

#define KC_CM_A    CM_A    
#define KC_CM_R    CM_R    
#define KC_CM_S    CM_S    
#define KC_CM_T    CM_T    
#define KC_CM_D    CM_D    
#define KC_CM_H    CM_H    
#define KC_CM_N    CM_N    
#define KC_CM_E    CM_E    
#define KC_CM_I    CM_I    
#define KC_CM_O    CM_O    

#define KC_CM_Z    CM_Z    
#define KC_CM_X    CM_X    
#define KC_CM_C    CM_C    
#define KC_CM_V    CM_V    
#define KC_CM_B    CM_B    
#define KC_CM_K    CM_K    
#define KC_CM_M    CM_M    
#define KC_CM_COMM CM_COMM 
#define KC_CM_DOT  CM_DOT  
#define KC_CM_SLSH CM_SLSH 

#define M(kc) kc | 0x3000

#define MACRODOWN(...) (record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)

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

#endif
