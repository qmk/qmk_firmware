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
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_12,  A_12,  C_12},
    {0, B_11,  A_11,  C_11},
    {0, B_10,  A_10,  C_10},
    {0, B_9,   A_9,   C_9},
    {0, B_8,   A_8,   C_8},
    {0, B_7,   A_7,   C_7},

    {0, H_12,  G_12,  I_12},
    {0, H_11,  G_11,  I_11},
    {0, H_10,  G_10,  I_10},
    {0, H_9,   G_9,   I_9},
    {0, H_8,   G_8,   I_8},
    {0, H_7,   G_7,   I_7},

    {0, B_6,   A_6,   C_6},
    {0, B_5,   A_5,   C_5},
    {0, B_4,   A_4,   C_4},
    {0, B_3,   A_3,   C_3},
    {0, B_2,   A_2,   C_2},
    {0, B_1,   A_1,   C_1},

    {0, H_6,   G_6,   I_6},
    {0, H_5,   G_5,   I_5},
    {0, H_4,   G_4,   I_4},
    {0, H_3,   G_3,   I_3},
    {0, H_2,   G_2,   I_2},
    {0, H_1,   G_1,   I_1},

    {0, E_12,  D_12,  F_12},
    {0, E_11,  D_11,  F_11},
    {0, E_10,  D_10,  F_10},
    {0, E_9,   D_9,   F_9},
    {0, E_8,   D_8,   F_8},
    {0, E_7,   D_7,   F_7},

    {0, K_12,  J_12,  L_12},
    {0, K_11,  J_11,  L_11},
    {0, K_10,  J_10,  L_10},
    {0, K_9,   J_9,   L_9},
    {0, K_8,   J_8,   L_8},
    {0, K_7,   J_7,   L_7},

    {0, E_6,   D_6,   F_6},
    {0, E_5,   D_5,   F_5},
    {0, E_4,   D_4,   F_4},
    {0, E_3,   D_3,   F_3},
    {0, E_2,   D_2,   F_2},
    {0, E_1,   D_1,   F_1},

    {0, K_6,   J_6,   L_6},
    {0, K_5,   J_5,   L_5},
    {0, K_4,   J_4,   L_4},
    {0, K_3,   J_3,   L_3},
    {0, K_2,   J_2,   L_2},

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
    case QK_LAYER_TAP ... QK_ONE_SHOT_LAYER_MAX:
    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_MOD_MAX:
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    case AU_ON ... MUV_DE:
    case RESET:
    case EEP_RST:
        return false;
    default:
        return music_mask_user(keycode);
    }
}
#endif
