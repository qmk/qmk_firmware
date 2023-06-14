// Copyright 2023 Technorage Developments (@St0RM53)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

//#define LED_NUM_LOCK_PIN C9
//#define LED_CAPS_LOCK_PIN C8
//#define LED_SCROLL_LOCK_PIN E0
//#define LED_PIN_ON_STATE 1

//#define ENCODERS_PAD_B { B18 }
//#define ENCODERS_PAD_A { A4 }
//#define ENCODER_RESOLUTION 4

// The pin connected to the data pin of the LEDs
#define WS2812_DI_PIN E1


//#define WS2812_TRST_US 80
//#define WS2812_TRST_US 600

//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB


///*
//for SK6805

#define WS2812_T0H 300
#define WS2812_T0L 900
#define WS2812_T1H 600
#define WS2812_T1L 600
#define NOP_FUDGE 0.5
//*/




/*
//for SK9816 
#define SK9816
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#define WS2812_T0H 300
#define WS2812_T0L 900
#define WS2812_T1H 900
#define WS2812_T1L 300
#define NOP_FUDGE 0.5
*/

#define OLED_TIMEOUT 5000

// The number of LEDs connected
#define RGB_MATRIX_LED_COUNT 101



//#define CYCLES_PER_SEC (KINETIS_SYSCLK_FREQUENCY / NUMBER_NOPS * NOP_FUDGE)
//#define STM32_SYSCLK KINETIS_SYSCLK_FREQUENCY
//#define NOP_FUDGE 0.45

#define FORCE_NKRO //for test only

//#define USE_I2CV1
//#define I2C_DRIVER I2CD1
#define I2C_DRIVER I2CD2 //On K20x I2C1 = I2CD2, https://github.com/qmk/ChibiOS-Contrib/blob/qmk-master/os/hal/ports/KINETIS/LLD/I2Cv1/hal_i2c_lld.c#L41-L50

//#define I2C1_OPMODE 1
//#define I2C1_CLOCK_SPEED 100000
//#define I2C1_DUTY_CYCLE 1

//#define I2C1_SCL_BANK GPIOC
//#define I2C1_SDA_BANK GPIOC
//#define I2C1_SCL 10
//#define I2C1_SDA 11
//#define I2C1_SCL_PAL_MODE 2
//#define I2C1_SDA_PAL_MODE 2

#define I2C1_SCL_PIN C10 
#define I2C1_SDA_PIN C11 
#define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
#define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2

#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_RAIN

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH



#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
//#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
//#define RGB_MATRIX_TIMEOUT 0 // number of milliseconds to wait until rgb automatically turns off
//#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
//#define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
//#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
//#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255

//#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE // Sets the default mode, if none has been set
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_ALPHAS_MODS

//#define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
//#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
//#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
//#define RGB_MATRIX_DEFAULT_SPD 0 // Sets the default animation speed, if none has been set
//#define RGB_MATRIX_DISABLE_KEYCODES // disables control of rgb matrix by keycodes (must use code functions to control the feature)
//#define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards

#define RGB_MATRIX_HUE_STEP 1
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 8