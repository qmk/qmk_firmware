/* Copyright 2019 Jane Bernhardt
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
// Chord Prefixes
#define MEDIA 	( FP11 | FP12 )
#define MOVE		( FP01 | FP11 )
#define NUM			( FP04 | FP14 )

#include "g/keymap_engine.h"

/* 	 	
 *  .---------------------------.
 *	| FP01 | FP02 | FP03 | FP04 | 
 *  |---------------------------|
 *	| FP11 | FP12 | FP13 | FP14 | 
 *  '---------------------------'
 */

// Don't edit your keymap here! Do it in your dicts/ !
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_faunch( 	KC_1,  KC_2,  KC_3,  KC_4,
  										  KC_5,  KC_6,  KC_7,  KC_8)
};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
