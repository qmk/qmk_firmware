/*
Copyright 2018 Massdrop Inc.

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

#ifndef _LED_MATRIX_H_
#define _LED_MATRIX_H_

#include "quantum.h"

// From keyboard
#include "config_led.h"

// CS1-CS16 Current Source "Col"
#define ISSI3733_CS_COUNT 16

// SW1-SW12 Switch "Row"
#define ISSI3733_SW_COUNT 12

#define ISSI3733_LED_RGB_COUNT ISSI3733_CS_COUNT *ISSI3733_SW_COUNT
#define ISSI3733_PG0_BYTES ISSI3733_LED_RGB_COUNT / 8 + 1  //+1 for first byte being memory start offset for I2C transfer
#define ISSI3733_PG1_BYTES ISSI3733_LED_RGB_COUNT + 1      //+1 for first byte being memory start offset for I2C transfer
#define ISSI3733_PG2_BYTES ISSI3733_LED_RGB_COUNT + 1      //+1 for first byte being memory start offset for I2C transfer
#define ISSI3733_PG3_BYTES 18 + 1                          //+1 for first byte being memory start offset for I2C transfer

#define ISSI3733_PG_ONOFF_BYTES ISSI3733_PG0_BYTES
#define ISSI3733_PG_OR_BYTES ISSI3733_PG0_BYTES
#define ISSI3733_PG_SR_BYTES ISSI3733_PG0_BYTES
#define ISSI3733_PG_PWM_BYTES ISSI3733_PG1_BYTES
#define ISSI3733_PG_ABM_BYTES ISSI3733_PG2_BYTES
#define ISSI3733_PG_FN_BYTES ISSI3733_PG3_BYTES

typedef struct issi3733_driver_s {
    uint8_t addr;                            // Address of the driver according to wiring "ISSI3733: Table 1 Slave Address"
    uint8_t onoff[ISSI3733_PG_ONOFF_BYTES];  // PG0 - LED Control Register - LED On/Off Register
    uint8_t open[ISSI3733_PG_OR_BYTES];      // PG0 - LED Control Register - LED Open Register
    uint8_t shrt[ISSI3733_PG_SR_BYTES];      // PG0 - LED Control Register - LED Short Register
    uint8_t pwm[ISSI3733_PG_PWM_BYTES];      // PG1 - PWM Register
    uint8_t abm[ISSI3733_PG_ABM_BYTES];      // PG2 - Auto Breath Mode Register
    uint8_t conf[ISSI3733_PG_FN_BYTES];      // PG3 - Function Register
} issi3733_driver_t;

typedef struct issi3733_rgb_s {
    uint8_t *r;  // Direct access into PWM data
    uint8_t *g;  // Direct access into PWM data
    uint8_t *b;  // Direct access into PWM data
} issi3733_rgb_t;

typedef struct issi3733_rgb_adr_s {
    uint8_t drv;  // Driver from given list
    uint8_t cs;   // CS
    uint8_t swr;  // SW Red
    uint8_t swg;  // SW Green
    uint8_t swb;  // SW Blue
} issi3733_rgb_adr_t;

typedef struct issi3733_led_s {
    uint8_t            id;    // According to PCB ref
    issi3733_rgb_t     rgb;   // PWM settings of R G B
    issi3733_rgb_adr_t adr;   // Hardware addresses
    float              x;     // Physical position X
    float              y;     // Physical position Y
    float              px;    // Physical position X in percent
    float              py;    // Physical position Y in percent
    uint8_t            scan;  // Key scan code from wiring (set 0xFF if no key)
} issi3733_led_t;

extern issi3733_driver_t issidrv[ISSI3733_DRIVER_COUNT];

extern uint8_t gcr_desired;
extern uint8_t gcr_breathe;
extern uint8_t gcr_actual;
extern uint8_t gcr_actual_last;

void gcr_compute(void);

void led_matrix_indicators(void);

/*-------------------------  Legacy Lighting Support  ------------------------*/

#ifdef USE_MASSDROP_CONFIGURATOR

#    define EF_NONE 0x00000000      // No effect
#    define EF_OVER 0x00000001      // Overwrite any previous color information with new
#    define EF_SCR_L 0x00000002     // Scroll left
#    define EF_SCR_R 0x00000004     // Scroll right
#    define EF_SUBTRACT 0x00000008  // Subtract color values

typedef struct led_setup_s {
    float    hs;   // Band begin at percent
    float    he;   // Band end at percent
    uint8_t  rs;   // Red start value
    uint8_t  re;   // Red end value
    uint8_t  gs;   // Green start value
    uint8_t  ge;   // Green end value
    uint8_t  bs;   // Blue start value
    uint8_t  be;   // Blue end value
    uint32_t ef;   // Animation and color effects
    uint8_t  end;  // Set to signal end of the setup
} led_setup_t;

extern const uint8_t led_setups_count;
extern void *        led_setups[];

// LED Extra Instructions
#    define LED_FLAG_NULL 0x00                // Matching and coloring not used (default)
#    define LED_FLAG_MATCH_ID 0x01            // Match on the ID of the LED (set id#'s to desired bit pattern, first LED is id 1)
#    define LED_FLAG_MATCH_LAYER 0x02         // Match on the current active layer (set layer to desired match layer)
#    define LED_FLAG_USE_RGB 0x10             // Use a specific RGB value (set r, g, b to desired output color values)
#    define LED_FLAG_USE_PATTERN 0x20         // Use a specific pattern ID (set pattern_id to desired output pattern)
#    define LED_FLAG_USE_ROTATE_PATTERN 0x40  // Use pattern the user has cycled to manually

typedef struct led_instruction_s {
    uint16_t flags;  // Bitfield for LED instructions
    uint32_t id0;    // Bitwise id, IDs 0-31
    uint32_t id1;    // Bitwise id, IDs 32-63
    uint32_t id2;    // Bitwise id, IDs 64-95
    uint32_t id3;    // Bitwise id, IDs 96-127
    uint8_t  layer;
    uint8_t  r;
    uint8_t  g;
    uint8_t  b;
    uint8_t  pattern_id;
    uint8_t  end;
} led_instruction_t;

extern led_instruction_t led_instructions[];

extern uint8_t led_animation_breathing;
extern uint8_t led_animation_id;
extern float   led_animation_speed;
extern uint8_t led_lighting_mode;
extern uint8_t led_enabled;
extern uint8_t led_animation_breathe_cur;
extern uint8_t led_animation_direction;
extern uint8_t breathe_dir;

#    define LED_MODE_NORMAL 0  // Must be 0
#    define LED_MODE_KEYS_ONLY 1
#    define LED_MODE_NON_KEYS_ONLY 2
#    define LED_MODE_INDICATORS_ONLY 3
#    define LED_MODE_MAX_INDEX LED_MODE_INDICATORS_ONLY  // Must be highest value

#endif  // USE_MASSDROP_CONFIGURATOR

#endif  //_LED_MATRIX_H_
