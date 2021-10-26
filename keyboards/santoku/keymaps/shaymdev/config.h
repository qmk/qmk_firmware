/* Copyright 2021 Tye (@tyetye)
 * Copyright 2021 Shay Merrill (@shaymdev)
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

// #define LAYOUT_3x6_3
#define COMBO_COUNT 2

#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 220
#define TAPPING_TERM_PER_KEY
//#define PERMISSIVE_HOLD
//#define TAPPING_FORCE_HOLD

#undef ENCODER_RESOLUTION 
#define ENCODER_RESOLUTION 1

#undef PS2_MOUSE_SCROLL_BTN_MASK  //shaymdev: maybe set his to middle (default?) possible good info here: https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_ps2_mouse
#define PS2_MOUSE_SCROLL_BTN_MASK (1 << PS2_MOUSE_BTN_MIDDLE)
#undef PS2_MOUSE_SCROLL_MASK
#define PS2_MOUSE_SCROLL_MASK 0x0F

//#define PS2_MOUSE_SCROLL_BTN_SEND 500 /* Default is 300 */ //shaymdev: might want to turn this back on with scroll_btn_mask

// Shaymdev: I think I might want this one enabled... play with that.... maybe I don't: https://github.com/qmk/qmk_firmware/issues/10957
// #define PS2_MOUSE_ENABLE_SCROLLING
