/* Copyright 2021 kuenhlee, Don Kjer, Tyler Tidman
 * Copyright 2021 Simon Arlott
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

#define WAIT_US_TIMER           GPTD3

/* key matrix size (rows in specific keyboard variant) */
#define MATRIX_COLS 16
#define MATRIX_ROWS 8

 #define MATRIX_ROW_PINS {A0, A1, A2, A3, A4, A5, A6, A7 } 
#define MATRIX_COL_PINS {C4, C5, B0, B1, B2, B10, B11, B12, B13, B14, A15, C6, C7, C10, C11, C12 }

/* COL2ROW, ROW2COL*/    
#define DIODE_DIRECTION ROW2COL

// Dynamic EEPROM
// Something sensible or else VIA may crash, Users may enable more if they wish
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  4095      // 16383
//#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#define BOOTMAGIC_LITE_ROW              2
#define BOOTMAGIC_LITE_COLUMN           7

/* LED indicator pins */  
#define LED_CAPS_LOCK_PIN   C9
#define LED_SCROLL_LOCK_PIN A8
#define LED_NUM_LOCK_PIN    C8
#define LED_WIN_LOCK_PIN    A9
#define LED_MR_LOCK_PIN     A10

#define LED_PIN_ON_STATE    0

/* Original hardware "reset" button on pin D2 */
#define HARDWARE_RESET_PIN  D2

#define GPIO_KM_PWEN        C1      // Hub Device Power on/off
#define GPIO_KM_OE          C2      // Hub Host Connection on/off
#define GPIO_KM_SEL         C0      // Hub Host Selection

/* Encoder used pins */
#define ENCODERS_PAD_A { C13 }
#define ENCODERS_PAD_B { C14 } 
/* Specifies the number of pulses the encoder registers between each detent */
#define ENCODER_RESOLUTION 2       // 4  //#define ENCODER_RESOLUTIONS { 2, 2 }
//#define ENCODER_DIRECTION_FLIP
//#define ENCODER_DEFAULT_POS 0x3

/* DIP switch */
//#define DIP_SWITCH_MATRIX_GRID  { {5,4}, {1.6}, {2,6} }
//#define DIP_SWITCH_PINS { C13 }

//------------------------------------- Add ----------------------------------

// #define FORCE_NKRO

#define TAPPING_TERM            175            //
#define TAPPING_TERM_PER_KEY
#define AUTO_SHIFT_TIMEOUT      170
#define AUTO_SHIFT_REEPAT
#define NO_AUTO_SHIFT_SPECIAL

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define ONESHOT_TAP_TOGGLE  2  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT     5000  /* Time (in ms) before the one shot key is released */

#define LEADER_TIMEOUT      500
#define LEADER_PER_KEY_TIMING
//#define LEADER_NO_TIMEOUT

#define JOYSTICK_BUTTON_COUNT       16      // Min 0, max 32
#define JOYSTICK_AXIS_COUNT         2       // Min 0, max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_RESOLUTION    12      // Min 8, max 16

//-------------------------------------------------------------------------------
/* RGB Underglow or WS2812 RGB Matirx */
#define WS2812_DI_PIN   B15


#ifdef WS2812_DI_PIN
// < pwm driver >
    // #define WS2812_PWM_DRIVER PWMD1
    // #define WS2812_PWM_CHANNEL 3
    // #define WS2812_PWM_PAL_MODE 1                   // 2 <- 072?
    // #define WS2812_PWM_COMPLEMENTARY_OUTPUT         // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
    // #define WS2812_DMA_STREAM STM32_DMA2_STREAM5    // TIM1_UP = STM32_DMA2_STREAM5  / TIM1_CH3 = STM32_DMA2_STREAM6
    // #define WS2812_DMA_CHANNEL 6                    // 2
    // //#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM2_UP // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.
    // //#define WS2812_PWM_TARGET_PERIOD 800000
// <spi driver >
    #define WS2812_SPI                  SPID2
    #define WS2812_SPI_MOSI_PAL_MODE    0      // 0 for F072-B15, 5 for F4x1(F103?) // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5   
//    #define WS2812_SPI_MOSI_PAL_MODE    1      // 1 for F072-C3, 5 for F4x1(F103?) // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5   
    #define WS2812_SPI_SCK_PIN          B13     //
    #define WS2812_SPI_SCK_PAL_MODE     5       // F072, enable = 0 / F401 enable = 5  (disable은 반대인가?)  (enable되어도 매트릭스 할당되면 매트릭스로 동작함)
    #define WS2812_SPI_DIVISOR          16      //4 4와 8만 되나?       //16    
    
    /* F4x1 */
    // #define WS2812_SPI_MOSI_PAL_MODE    5      // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5   // 0 for F072
    // // #define WS2812_SPI_SCK_PIN       B13     //for F072?
    // // #define WS2812_SPI_SCK_PAL_MODE  0       //for F072?
    // #define WS2812_SPI_DIVISOR	        8      //4 4와 8만 되나?       //16

    #define WS2812_SPI_USE_CIRCULAR_BUFFER    // fix Fliker (이 기능을 켜면 access가 많아짐)

// #define LED_LAYOUT(
// )


//RGB LED Conversion macro from physical array to electric array (+146). This results in better looking animated effects.
//First section is the LED matrix, second section is the electrical wiring order, and the third section is the desired mapping
/*
#define LED_LAYOUT( \  // error
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,  \
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, \
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, \
    63, 43, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, \
    84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104, \
   105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125, \
   126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146, \
   147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167) \
  { \
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,  \
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, \
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, \
    63, 43, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, \
    84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104, \
   105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125, \
   126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146, \
   147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167  \
  }
#define RGBLIGHT_LED_MAP LED_LAYOUT(  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, \
                           41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, \
                           42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, \
                           83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, \
                           84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104, \
                          125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105, \
                          126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146, \
                          167,166,165,164,163,162,161,160,159,158,157,156,155,154,153,152,151,150,149,148,147 )
*/
//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#endif
//-------------------------------------------
#ifdef RGB_MATRIX_ENABLE
/*
#    define DRIVER_ADDR_1 0b1110111
#    define DRIVER_ADDR_2 0b1110100
#    define DRIVER_ADDR_3 0b1110101
#    define DRIVER_ADDR_4 0b1110110
#    define DRIVER_COUNT 4
#    define DRIVER_1_LED_TOTAL 16
#    define DRIVER_2_LED_TOTAL 32
#    define DRIVER_3_LED_TOTAL 32
#    define DRIVER_4_LED_TOTAL 32
#    define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL + DRIVER_3_LED_TOTAL + DRIVER_4_LED_TOTAL )

    //#define ISSI_TIMEOUT    100     // option
    #define ISSI_PERSISTENCE 3     // option

#    define RGB_MATRIX_LED_PROCESS_LIMIT 18
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#    define RGB_DISABLE_AFTER_TIMEOUT 0          // number of ticks to wait until disabling effects
*/

#define RGB_MATRIX_LED_COUNT 111
    #define RGBLED_NUM 111

 #define RGB_MATRIX_DEFAULT_VAL 60 
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_CENTER   {94,21}
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
//#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_GRADIENT_LEFT_RIGHT      // RGB_MATRIX_ALPHAS_MODS

/*
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
*/

#define ENABLE_RGB_MATRIX_SOLID_COLOR               // 1
#define ENABLE_RGB_MATRIX_ALPHAS_MODS           
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING                 // 5    // Single hue brightness cycling animation
#define ENABLE_RGB_MATRIX_BAND_SAT                          // 바탕이 흰색 
#define ENABLE_RGB_MATRIX_BAND_VAL                          // 바탕이 안켜짐
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT           // 10
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL                   // Single hue spinning spiral fades brightness
#define ENABLE_RGB_MATRIX_CYCLE_ALL                         // Full keyboard solid hue cycling through full gradient
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT                  // Full gradient scrolling left to right
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN                     // Full gradient scrolling top to bottom
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON    // 15   // 이것포함 아래 2개 모드가 스펙과 순서가 틀림 - 스펙이 틀린듯)
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN                      // Full gradient scrolling out to in
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL                    // Full gradient spinning pinwheel around center of keyboard
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL                      // Full gradient spinning spiral around center of keyboard

#define ENABLE_RGB_MATRIX_RAINBOW_BEACON            // 20   // ? 
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS                 // Full dual gradients spinning two halfs of keyboard
#define ENABLE_RGB_MATRIX_DUAL_BEACON                   

#define ENABLE_RGB_MATRIX_RAINDROPS                      // Randomly changes a single key's hue
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING              // 25 
#define ENABLE_RGB_MATRIX_HUE_PENDULUM              
#define ENABLE_RGB_MATRIX_HUE_WAVE 
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_PIXEL_FLOW

#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL             // 30

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP        //RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN          //RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE             // Pulses keys hit to hue & value then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE                    // Static single hue, pulses keys hit to shifted hue then fades to current hue
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // 35   // Hue & value pulse near a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS              // Hue & value pulse the same column and row of a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS 
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS          
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // 40   //
#define ENABLE_RGB_MATRIX_SPLASH                            // Full gradient & value pulse away from a single key hit then fades value out
#define ENABLE_RGB_MATRIX_MULTISPLASH                       //
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH         // 44    // Hue & value pulse away from multiple key hits then fades value out
#endif

//-----------------------------------------------------

#ifdef OLED_ENABLE
/*  OLED Configulation */
// #define OLED_DISPLAY_ADDRESS 0x3C
// #define OLED_COM_PINS 0x12           // 크기가 작아짐.. 어디다 사용? 128x64에 사용하는 건가? 뭐지?

// #define OLED_IC OLED_IC_SSD1306      //안해도 default는 SSD1306

/* Required for SH1106 Oled Driver + 128x64 (ex = 0.96inch)*/
/* #define OLED_IC OLED_IC_SH1106      // YwRobot 1.3inch
#define OLED_COLUMN_OFFSET 2        // SH1106 screen is a little off to the left
#define OLED_DISPLAY_128X64           // 0.91inch = 128x32, 0.96inch(1.3inch) = 128x64
*/

/* Default Oled init */
#define OLED_TIMEOUT 20000              // Turns off OLED after said amount of milliseconds
#define OLED_BRIGHTNESS 255
//#define OLED_FONT_END 255         //error: static assertion failed: "OLED_FONT_END references outside array"
#define OLED_FONT_H "gfxfont.c"
//#define OLED_UPDATE_INTERVAL 33 // ~30fps
#endif

/* I2c for 072 */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define I2C1_TIMINGR_PRESC 2U  // 키보드 westm/westm9/rev1 = 00, 03, 01, 03, 09
#define I2C1_TIMINGR_SCLDEL 0U // 2 0 0 9 14--> 100K/Digital Filter off
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 9U
#define I2C1_TIMINGR_SCLL 14U
