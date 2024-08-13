/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2015 ZSA Technology Labs Inc (@zsa)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "ez.h"
#include <ch.h>
#include <hal.h>

keyboard_config_t keyboard_config;
#ifdef RGB_MATRIX_ENABLE
const is31fl3737_led_t PROGMEM g_is31fl3737_leds[IS31FL3737_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, SW2_CS12,  SW1_CS12,  SW3_CS12},
    {0, SW2_CS11,  SW1_CS11,  SW3_CS11},
    {0, SW2_CS10,  SW1_CS10,  SW3_CS10},
    {0, SW2_CS9,   SW1_CS9,   SW3_CS9},
    {0, SW2_CS8,   SW1_CS8,   SW3_CS8},
    {0, SW2_CS7,   SW1_CS7,   SW3_CS7},

    {0, SW8_CS12,  SW7_CS12,  SW9_CS12},
    {0, SW8_CS11,  SW7_CS11,  SW9_CS11},
    {0, SW8_CS10,  SW7_CS10,  SW9_CS10},
    {0, SW8_CS9,   SW7_CS9,   SW9_CS9},
    {0, SW8_CS8,   SW7_CS8,   SW9_CS8},
    {0, SW8_CS7,   SW7_CS7,   SW9_CS7},

    {0, SW2_CS6,   SW1_CS6,   SW3_CS6},
    {0, SW2_CS5,   SW1_CS5,   SW3_CS5},
    {0, SW2_CS4,   SW1_CS4,   SW3_CS4},
    {0, SW2_CS3,   SW1_CS3,   SW3_CS3},
    {0, SW2_CS2,   SW1_CS2,   SW3_CS2},
    {0, SW2_CS1,   SW1_CS1,   SW3_CS1},

    {0, SW8_CS6,   SW7_CS6,   SW9_CS6},
    {0, SW8_CS5,   SW7_CS5,   SW9_CS5},
    {0, SW8_CS4,   SW7_CS4,   SW9_CS4},
    {0, SW8_CS3,   SW7_CS3,   SW9_CS3},
    {0, SW8_CS2,   SW7_CS2,   SW9_CS2},
    {0, SW8_CS1,   SW7_CS1,   SW9_CS1},

    {0, SW5_CS12,  SW4_CS12,  SW6_CS12},
    {0, SW5_CS11,  SW4_CS11,  SW6_CS11},
    {0, SW5_CS10,  SW4_CS10,  SW6_CS10},
    {0, SW5_CS9,   SW4_CS9,   SW6_CS9},
    {0, SW5_CS8,   SW4_CS8,   SW6_CS8},
    {0, SW5_CS7,   SW4_CS7,   SW6_CS7},

    {0, SW11_CS12,  SW10_CS12,  SW12_CS12},
    {0, SW11_CS11,  SW10_CS11,  SW12_CS11},
    {0, SW11_CS10,  SW10_CS10,  SW12_CS10},
    {0, SW11_CS9,   SW10_CS9,   SW12_CS9},
    {0, SW11_CS8,   SW10_CS8,   SW12_CS8},
    {0, SW11_CS7,   SW10_CS7,   SW12_CS7},

    {0, SW5_CS6,   SW4_CS6,   SW6_CS6},
    {0, SW5_CS5,   SW4_CS5,   SW6_CS5},
    {0, SW5_CS4,   SW4_CS4,   SW6_CS4},
    {0, SW5_CS3,   SW4_CS3,   SW6_CS3},
    {0, SW5_CS2,   SW4_CS2,   SW6_CS2},
    {0, SW5_CS1,   SW4_CS1,   SW6_CS1},

    {0, SW11_CS6,   SW10_CS6,   SW12_CS6},
    {0, SW11_CS5,   SW10_CS5,   SW12_CS5},
    {0, SW11_CS4,   SW10_CS4,   SW12_CS4},
    {0, SW11_CS3,   SW10_CS3,   SW12_CS3},
    {0, SW11_CS2,   SW10_CS2,   SW12_CS2},

};

led_config_t g_led_config = { {
    {   0,   1,   2,   3,   4,   5 },
    {  12,  13,  14,  15,  16,  17 },
    {  24,  25,  26,  27,  28,  29 },
    {  36,  37,  38,  45,  46, NO_LED },
    {   6,   7,   8,   9,  10,  11 },
    {  18,  19,  20,  21,  22,  23 },
    {  30,  31,  32,  33,  34,  35 },
    {  42,  43,  44,  39,  40,  41 }
}, {
    {   0,   0 }, {  20,   0 }, {  40,   0 }, {  61,   0 }, {  81,   0 }, { 101,   0 }, { 122,   0 }, { 142,   0 }, { 162,   0 }, { 183,   0 }, { 203,   0 }, { 223,   0 },
    {   0,  21 }, {  20,  21 }, {  40,  21 }, {  61,  21 }, {  81,  21 }, { 101,  21 }, { 122,  21 }, { 142,  21 }, { 162,  21 }, { 183,  21 }, { 203,  21 }, { 223,  21 },
    {   0,  42 }, {  20,  42 }, {  40,  42 }, {  61,  42 }, {  81,  42 }, { 101,  42 }, { 122,  42 }, { 142,  42 }, { 162,  42 }, { 183,  42 }, { 203,  42 }, { 223,  42 },
    {   0,  63 }, {  20,  63 }, {  40,  63 }, {  61,  63 }, {  81,  63 }, { 111,  63 }, { 142,  63 }, { 162,  63 }, { 183,  63 }, { 203,  63 }, { 223,  63 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1
} };

#endif

/* Left B9   Right B8 */

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
  if (v <= 5243) // if below 8% of max
    return v / 9; // same as dividing by 900%
  else {
    uint32_t y = (((uint32_t) v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
    // to get a useful result with integer division, we shift left in the expression above
    // and revert what we've done again after squaring.
    y = y * y * y >> 8;
    if (y > 0xFFFFUL) // prevent overflow
      return 0xFFFFU;
    else
      return (uint16_t) y;
  }
}

static PWMConfig pwmCFG = {
    0xFFFF,/* PWM clock frequency  */
    256,/* initial PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
    NULL,
    {
        {PWM_OUTPUT_DISABLED, NULL}, /* channel 0 -> TIM1-CH1 = PA8 */
        {PWM_OUTPUT_DISABLED, NULL}, /* channel 1 -> TIM1-CH2 = PA9 */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}
    },
    0, /* HW dependent part.*/
    0
};

static uint32_t planck_ez_right_led_duty;
static uint32_t planck_ez_left_led_duty;

void planck_ez_right_led_level(uint8_t level) {
    planck_ez_right_led_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) level / 255));
    if (level == 0) {
        // Turn backlight off
        pwmDisableChannel(&PWMD4, 2);
    } else {
        // Turn backlight on
        pwmEnableChannel(&PWMD4, 2, PWM_FRACTION_TO_WIDTH(&PWMD4,0xFFFF,planck_ez_right_led_duty));
    }
}


void planck_ez_right_led_on(void){
    pwmEnableChannel(&PWMD4, 2, PWM_FRACTION_TO_WIDTH(&PWMD4,0xFFFF,planck_ez_right_led_duty));
}

void planck_ez_right_led_off(void){
    pwmDisableChannel(&PWMD4, 2);
}

void planck_ez_left_led_level(uint8_t level) {
    planck_ez_left_led_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) level / 255));
    if (level == 0) {
        // Turn backlight off
        pwmDisableChannel(&PWMD4, 3);
    } else {
        // Turn backlight on
        pwmEnableChannel(&PWMD4, 3, PWM_FRACTION_TO_WIDTH(&PWMD4,0xFFFF,planck_ez_left_led_duty));
    }
}

void planck_ez_left_led_on(void){
    pwmEnableChannel(&PWMD4, 3, PWM_FRACTION_TO_WIDTH(&PWMD4,0xFFFF,planck_ez_left_led_duty));
}

void planck_ez_left_led_off(void){
    pwmDisableChannel(&PWMD4, 3);
}


void led_initialize_hardware(void) {
    pwmStart(&PWMD4, &pwmCFG);

    // set up defaults
    planck_ez_right_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
    palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(2));
    planck_ez_left_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
    palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(2));


    // turn LEDs off by default
    planck_ez_left_led_off();
    planck_ez_right_led_off();
}

void keyboard_pre_init_kb(void) {
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }
    // read kb settings from eeprom
    keyboard_config.raw = eeconfig_read_kb();
#if defined(RGB_MATRIX_ENABLE) && defined(ORYX_CONFIGURATOR)
    if (keyboard_config.rgb_matrix_enable) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
    } else {
        rgb_matrix_set_flags(LED_FLAG_NONE);
    }
#endif
    led_initialize_hardware();
    keyboard_pre_init_user();
}

#if defined(RGB_MATRIX_ENABLE) && defined(ORYX_CONFIGURATOR)
void keyboard_post_init_kb(void) {
    rgb_matrix_enable_noeeprom();
    keyboard_post_init_user();
}
#endif

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw = 0;
    keyboard_config.rgb_matrix_enable = true;
    keyboard_config.led_level = 4;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}


#ifdef ORYX_CONFIGURATOR

#ifndef PLANCK_EZ_USER_LEDS

#ifndef PLANCK_EZ_LED_LOWER
#    define PLANCK_EZ_LED_LOWER 3
#endif
#ifndef PLANCK_EZ_LED_RAISE
#    define PLANCK_EZ_LED_RAISE 4
#endif
#ifndef PLANCK_EZ_LED_ADJUST
#    define PLANCK_EZ_LED_ADJUST 6
#endif

layer_state_t layer_state_set_kb(layer_state_t state) {
    planck_ez_left_led_off();
    planck_ez_right_led_off();
    state = layer_state_set_user(state);
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case PLANCK_EZ_LED_LOWER:
            planck_ez_left_led_on();
            break;
        case PLANCK_EZ_LED_RAISE:
            planck_ez_right_led_on();
            break;
        case PLANCK_EZ_LED_ADJUST:
            planck_ez_right_led_on();
            planck_ez_left_led_on();
            break;
        default:
            break;
    }
    return state;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_LEVEL:
            if (record->event.pressed) {
                 keyboard_config.led_level++;
                 if (keyboard_config.led_level > 4) {
                    keyboard_config.led_level = 0;
                 }
                 planck_ez_right_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
                 planck_ez_left_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
                 eeconfig_update_kb(keyboard_config.raw);
                 layer_state_set_kb(layer_state);
            }
            break;
#ifdef RGB_MATRIX_ENABLE
        case TOGGLE_LAYER_COLOR:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led ^= 1;
                if (keyboard_config.disable_layer_led)
                    rgb_matrix_set_color_all(0, 0, 0);
                eeconfig_update_kb(keyboard_config.raw);
            }
            break;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    keyboard_config.rgb_matrix_enable = false;
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    keyboard_config.rgb_matrix_enable = true;
                  }
                  break;
              }
              eeconfig_update_kb(keyboard_config.raw);
            }
            return false;
#endif
    }
    return process_record_user(keycode, record);
}
#endif

#ifdef AUDIO_ENABLE
bool music_mask_kb(uint16_t keycode) {
    switch (keycode) {
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
    case QK_TO ... QK_TO_MAX:
    case QK_MOMENTARY ... QK_MOMENTARY_MAX:
    case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
    case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
    case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
    case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
    case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    case AU_ON ... AU_PREV:
    case QK_BOOT:
    case QK_CLEAR_EEPROM:
        return false;
    default:
        return music_mask_user(keycode);
    }
}
#endif

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
    {{5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}},
    {{5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
    {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
    
    {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
    {{5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
    {{5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
    {{5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7}},
};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {0};
#    endif
#endif

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = {
    {36, 37, 38, 39, 40, 41},
    {24, 25, 26, 27, 28, 29},
    {12, 13, 14, 15, 16, 17},
    { 0,  1,  2, 10, 11,  6},
    {42, 43, 44, 45, 46, 47},
    {30, 31, 32, 33, 34, 35},
    {18, 19, 20, 21, 22, 23},
    { 7,  8,  9,  3,  4,  5}
};
