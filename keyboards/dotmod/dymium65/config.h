// Copyright 2023 <felix@fjlaboratories.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROW_PINS { F7, F6, F5, F4, F1, F0}
#define MATRIX_COL_PINS { E6, B0, B1, B2, B3, B7, D2, D3, D5, D4, D6, C6, B4, B5, B6, E2}

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define FORCE_NKRO

#define NO_ACTION_ONESHOT

#define RGB_DI_PIN D7
#define RGB_MATRIX_LED_COUNT 66
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define ENABLE_RGB_MATRIX_BREATHING	            
#define ENABLE_RGB_MATRIX_CYCLE_ALL             
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT      
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN           
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL       
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL            
#define ENABLE_RGB_MATRIX_PIXEL_FLOW              
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE	         
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE	 
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS	     
