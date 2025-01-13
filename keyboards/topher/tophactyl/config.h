// Copyright 2023 Topher (@Topher2014)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define MASTER_LEFT
#define PMW33XX_CS_PIN B0
#define PMW33XX_CPI 300
#define SPLIT_POINTING_ENABLE 
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 1500 
#define AUTO_MOUSE_DELAY 100

#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

//#define ENCODERS_PAD_A { }
//#define ENCODERS_PAD_B { }
//#define ENCODER_RESOLUTION { } 
#define ENCODERS_PAD_A_RIGHT { F6 }
#define ENCODERS_PAD_B_RIGHT { F7 }
//#define ENCODER_RESOLUTION_RIGHT { 4 }
//#define ENCODER_DIRECTION_FLIP

#define DEBOUNCE 12
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE
