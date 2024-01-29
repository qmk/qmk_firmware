/* Copyright 2024 Aplusx Inc.
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

#define WAIT_US_TIMER           GPTD3       //  Encoder 및 RGB ANI가 부드러워짐

// Dynamic EEPROM
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  4095

/* Bootmagic Lite key configuration */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#define BOOTMAGIC_LITE_ROW              2
#define BOOTMAGIC_LITE_COLUMN           7

/* USB Hub Control pins  */
#define GPIO_KM_PWEN        C1      // Hub Device Power on/off
#define GPIO_KM_OE          C2      // Hub Host Connection on/off
#define GPIO_KM_SEL         C0      // Hub Host Selection
#define GPIO_TEST_DEBUG     C9      // C3-LED / C9-GPIO PAD

/* Encoder used pins */
#define ENCODERS_PAD_A { C13 }
#define ENCODERS_PAD_B { C14 } 

#ifdef RGB_MATRIX_ENABLE
/* RGB Underglow or WS2812 RGB Matirx  <spi driver > */
    #define WS2812_SPI_DRIVER           SPID2    
    #define WS2812_SPI_MOSI_PAL_MODE    0      
    #define WS2812_SPI_SCK_PIN          B13
    #define WS2812_SPI_SCK_PAL_MODE     5   
    #define WS2812_SPI_DIVISOR          16  
    #define WS2812_SPI_USE_CIRCULAR_BUFFER

#define RGB_MATRIX_LED_COUNT 111

#define RGB_MATRIX_DEFAULT_VAL 60 
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 220   // 200-> 440mA / 220-> 500mA / 255 -> 620mA
#define RGB_MATRIX_CENTER   {94,21}
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED 
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8

/* RGB Matrix Animation modes */
#define ENABLE_RGB_MATRIX_SOLID_COLOR               // 1
#define ENABLE_RGB_MATRIX_ALPHAS_MODS           
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING                 // 5 
#define ENABLE_RGB_MATRIX_BAND_SAT                       
#define ENABLE_RGB_MATRIX_BAND_VAL                       
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT           // 10
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL                  
#define ENABLE_RGB_MATRIX_CYCLE_ALL                         
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT                  /
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN                     
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON    // 15 
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN                   
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL                 
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL             

#define ENABLE_RGB_MATRIX_RAINBOW_BEACON            // 20 
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS              
#define ENABLE_RGB_MATRIX_DUAL_BEACON                   

#define ENABLE_RGB_MATRIX_RAINDROPS                 
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING              // 25 
#define ENABLE_RGB_MATRIX_HUE_PENDULUM              
#define ENABLE_RGB_MATRIX_HUE_WAVE 
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_PIXEL_FLOW

#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL             // 30

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP      
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN         

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE             
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE                    
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // 35   
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS              
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS 
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS          
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // 40 
#define ENABLE_RGB_MATRIX_SPLASH                            
#define ENABLE_RGB_MATRIX_MULTISPLASH                      
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH         // 44    

#endif
