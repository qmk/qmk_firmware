 /* 
 Copyright 2020 Alec Penland
 Copyright 2020 Garret Gartner
  
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

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *         ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *å
*/

// Checked with Eagle Schematic
#define MATRIX_ROW_PINS { F7, F6, F5, F4, F1, F0}
#define MATRIX_COL_PINS { E6, B0, B1, B2, B3, B7, D2, D3, D5, D4, D6, C6, B4, B5, B6, E2}
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Define less important options */

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
#define FORCE_NKRO MAGIC_TOGGLE_NKRO

/*
 * Feature disable options
 * These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

/* disable user print */
#define USER_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* USB Device descriptor parameter */
#define VENDOR_ID       0x320f
#define PRODUCT_ID      0x5058
#define DEVICE_VER      0x0100
#define MANUFACTURER    RDR
#define PRODUCT         DYMIUM65

/* Encoders */
#define ENCODERS_PAD_A { C7 }
#define ENCODERS_PAD_B { D1 }

/* If your encoder’s clockwise directions are incorrect, you can swap the A & B pad definitions. They can also be flipped with a define */
//#define ENCODER_DIRECTION_FLIP

/* Additionally, the resolution, which defines how many pulses the encoder registers between each detent, can be defined with */
//#define ENCODER_RESOLUTION  4  

/* The Bootmagic Lite feature that only handles jumping into the bootloader.
   This is great for boards that don’t have a physical reset button,
   giving you a way to jump into the bootloader */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0


// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN D7
// The number of LEDs connected
#define DRIVER_LED_TOTAL 66

//Whether to react to the key
#define RGB_MATRIX_KEYPRESSES

//Respond to key release (not keys)
#define RGB_MATRIX_KEYRELEASES

//Enable framebuffer effect
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//Light timeout waiting time
#define RGB_DISABLE_AFTER_TIMEOUT 0

//Whether to enable to close SUB suspended
//#define RGB_DISABLE_WHEN_USB_SUSPENDED

//Light refresh time 16MS 60FPS
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
//Maximum light brightness 255
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200

//Maximum light brightness 255 Set the default saturation value (if not set)
//#define RGB_MATRIX_STARTUP_SAT 255

//Default light mode
//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects

//#define ENABLE_RGB_MATRIX_ALPHAS_MODS	            //Red constant 0
                                            
//#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN        //Static meteor chasing the moon 
                                         
//#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT     //Static wave effect  
                                            
#define ENABLE_RGB_MATRIX_BREATHING	            //Static breathing effect  
                                           
//#define ENABLE_RGB_MATRIX_BAND_SAT                //Dynamic white small waves with background color, 
                                        
//#define ENABLE_RGB_MATRIX_BAND_VAL                //Dynamic small waves without background

                                      
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT       //Radar with white background
                                          
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL       //Radar without background color 
                                         
//#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT         //Large windmill with white background
                                    
//#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL         //Large windmill without background color

#define ENABLE_RGB_MATRIX_CYCLE_ALL               //spectrum

#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT        //wave 

#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN           //swiftly 

//#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  //Arrow wave (small wave)

//#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN            //Speed passion

#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL       //Two central points, speed and passion

//#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL          //Color radar

#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL            //Color windmill

//#define ENABLE_RGB_MATRIX_DUAL_BEACON             //Color clockwise ladder rotation

//#define ENABLE_RGB_MATRIX_RAINBOW_BEACON          //Color clockwise fine step rotation

//#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS       //Step rotation of two center points

//#define ENABLE_RGB_MATRIX_RAINDROPS                 //Colorful rain

//#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS       //Fast color rain

//#define ENABLE_RGB_MATRIX_HUE_BREATHING            //Color respiration

//#define ENABLE_RGB_MATRIX_HUE_PENDULUM            //Left and right storms

//#define ENABLE_RGB_MATRIX_HUE_WAVE                //Storm without lightning, wave with background color 

//#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL          //Starry dots 

#define ENABLE_RGB_MATRIX_PIXEL_FLOW              //The digital age

//#define ENABLE_RGB_MATRIX_PIXEL_RAIN           //Ghost fire   


//The following modes require key triggering
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE	  //Single light, color can be adjusted

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE	        //Single light color with background color, color can be adjusted 

//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE	 //Six palace squares, can adjust the color     

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE	 //Six palaces, diffusion and reunion

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS	     //Press the cross button to release diffusion and then retract

//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS	 //Press the cross button to release diffusion and then retract

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS       //Press the cross key to release the diffusion without retracting

//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS	 //Press the cross key to release the diffusion without retracting

#define ENABLE_RGB_MATRIX_SPLASH	          //Ripple, color, similar to speed passion, repeated press will delay diffusion             

//#define ENABLE_RGB_MATRIX_MULTISPLASH	   // Ripple, color, similar to speed passion, repeated press will not retract diffusion             

//#define ENABLE_RGB_MATRIX_SOLID_SPLASH   // Ripples, monochrome, similar to speed passion, adjustable color	             

//#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH    //Ripples, monochrome, similar to speed passion, adjustable color, repeatedly press No    
