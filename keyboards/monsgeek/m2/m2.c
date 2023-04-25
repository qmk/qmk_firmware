/* Copyright (C) 2022 jonylee@hfd
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {1, A_1,   B_1,   C_1},
    {1, A_2,   B_2,   C_2},
    {1, A_3,   B_3,   C_3},
    {1, A_4,   B_4,   C_4},
    {1, A_5,   B_5,   C_5},
    {1, A_6,   B_6,   C_6},
    {1, A_7,   B_7,   C_7},
    {1, A_8,   B_8,   C_8},
    {1, A_9,   B_9,   C_9},
    {1, A_10,  B_10,  C_10},
    {1, A_11,  B_11,  C_11},
    {1, A_12,  B_12,  C_12},
    {1, A_13,  B_13,  C_13},
    {1, A_14,  B_14,  C_14},
    {1, D_11,  E_11,  F_11},
    {1, D_12,  E_12,  F_12},
    {1, D_13,  E_13,  F_13},
    {1, D_14,  E_14,  F_14},

    {0, A_1,   B_1,   C_1},
    {0, A_2,   B_2,   C_2},
    {0, A_3,   B_3,   C_3},
    {0, A_4,   B_4,   C_4},
    {0, A_5,   B_5,   C_5},
    {0, A_6,   B_6,   C_6},
    {0, A_7,   B_7,   C_7},
    {0, A_8,   B_8,   C_8},
    {0, A_9,   B_9,   C_9},
    {0, A_10,  B_10,  C_10},
    {0, A_11,  B_11,  C_11},
    {0, A_12,  B_12,  C_12},
    {0, A_13,  B_13,  C_13},
    {0, A_14,  B_14,  C_14},
    {1, D_4,    E_4,   F_4},
    {1, D_5,    E_5,   F_5},
    {1, D_6,    E_6,   F_6},
    {1, D_7,    E_7,   F_7},

    {0, D_1,   E_1,   F_1},
    {0, D_2,   E_2,   F_2},
    {0, D_3,   E_3,   F_3},
    {0, D_4,   E_4,   F_4},
    {0, D_5,   E_5,   F_5},
    {0, D_6,   E_6,   F_6},
    {0, D_7,   E_7,   F_7},
    {0, D_8,   E_8,   F_8},
    {0, D_9,   E_9,   F_9},
    {0, D_10,  E_10,  F_10},
    {0, D_11,  E_11,  F_11},
    {0, D_12,  E_12,  F_12},
    {0, D_13,  E_13,  F_13},
    {0, D_14,  E_14,  F_14},
    {1, D_8,    E_8,   F_8},
    {1, D_9,    E_9,   F_9},
    {1, D_10,  E_10,  F_10},
    {1, G_7,   H_7,   I_7},

    {0, G_1,   H_1,   I_1},
    {0, G_2,   H_2,   I_2},
    {0, G_3,   H_3,   I_3},
    {0, G_4,   H_4,   I_4},
    {0, G_5,   H_5,   I_5},
    {0, G_6,   H_6,   I_6},
    {0, G_7,   H_7,   I_7},
    {0, G_8,   H_8,   I_8},
    {0, G_9,   H_9,   I_9},
    {0, G_10,  H_10,  I_10},
    {0, G_11,  H_11,  I_11},
    {0, G_12,  H_12,  I_12},
    {0, G_13,  H_13,  I_13},
    {1, G_4,   H_4,   I_4},
    {1, G_5,   H_5,   I_5},
    {1, G_6,   H_6,   I_6},

    {0, J_1,   K_1,   L_1},
    {0, J_2,   K_2,   L_2},
    {0, J_3,   K_3,   L_3},
    {0, J_4,   K_4,   L_4},
    {0, J_5,   K_5,   L_5},
    {0, J_6,   K_6,   L_6},
    {0, J_7,   K_7,   L_7},
    {0, J_8,   K_8,   L_8},
    {0, J_9,   K_9,   L_9},
    {0, J_10,  K_10,  L_10},
    {0, J_11,  K_11,  L_11},
    {0, J_12,  K_12,  L_12},
    {1,  J_4,   K_4,  L_4},
    {1,  J_7,   K_7,  L_7},
    {1,  J_8,   K_8,  L_8},
    {1,  J_9,   K_9,  L_9},
    {1,  J_10,  K_10, L_10},

    {0, J_13,  K_13,  L_13},
    {0, J_14,  K_14,  L_14},
    {0, J_15,  K_15,  L_15},
    {0, J_16,  K_16,  L_16},
    {0, G_14,  H_14,  I_14},
    {0, G_15,  H_15,  I_15},
    {0, G_16,  H_16,  I_16},
    {1, J_2,  K_2,  L_2},
    {1, J_3,  K_3,  L_3},
    {1, J_5,  K_5,  L_5},
    {1, J_6,  K_6,  L_6},
};

led_config_t g_led_config = {
    {
        {  0,       1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13, NO_LED,     NO_LED,   NO_LED,  14,      15,     16,     17},
        {  18,      19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31, NO_LED,     NO_LED,   NO_LED,  32,      33,     34,     35},
        {  36,      37,     38,     39,     40,     41,     42,     43,     44,     45,     46,     47,     48,     49, NO_LED,     NO_LED,   NO_LED,  50,      51,     52,     53},
        {  54,      55,     56,     57,     58,     59,     60,     61,     62,     63,     64,     65,     NO_LED,  66, NO_LED,     NO_LED,   NO_LED,  67,     68,     69, NO_LED},
        {  70,      71,     72,     73,     74,     75,     76,     77,     78,     79,     80,   NO_LED,  NO_LED,  81, NO_LED,         82,   NO_LED,  83,      84,     85,     86},
        {  87,      88,     89, NO_LED, NO_LED,     90, NO_LED, NO_LED, NO_LED,     91,     92,     93, NO_LED, NO_LED, NO_LED,         94,     95,NO_LED,      96,     97, NO_LED}
    },
    {
        {  0,  0}, //  0
        { 13,  0}, //  1
        { 26,  0}, //  2
        { 39,  0}, //  3
        { 52,  0}, //  4
        { 65,  0}, //  5
        { 79,  0}, //  6
        { 92,  0}, //  7
        {105,  0}, //  8
        {118,  0}, //  9
        {131,  0}, // 10
        {144,  0}, // 11
        {158,  0}, // 12
        {171,  0}, // 13
        {184,  0}, // 14
        {197,  0}, // 15
        {210,  0}, // 16
        {224,  0}, // 17

        {  0,  12}, //  18
        { 13,  12}, //  19
        { 26,  12}, //  20
        { 39,  12}, //  21
        { 52,  12}, //  22
        { 65,  12}, //  23
        { 79,  12}, //  24
        { 92,  12}, //  25
        {105,  12}, //  26
        {118,  12}, //  27
        {131,  12}, // 28
        {144,  12}, // 29
        {158,  12}, // 30
        {171,  12}, // 31
        {184,  12}, // 32
        {197,  12}, // 33
        {210,  12}, // 34
        {224,  12}, // 35

        {  0,  25}, //  36
        { 13,  25}, //  37
        { 26,  25}, //  38
        { 39,  25}, //  39
        { 52,  25}, //  40
        { 65,  25}, //  41
        { 79,  25}, //  42
        { 92,  25}, //  43
        {105,  25}, //  44
        {118,  25}, //  45
        {131,  25}, // 46
        {144,  25}, // 47
        {158,  25}, // 48
        {171,  25}, // 49
        {184,  25}, // 50
        {197,  25}, // 51
        {210,  25}, // 52
        {224,  25}, // 53

        {  0,  38}, //  54
        { 13,  38}, //  55
        { 26,  38}, //  56
        { 39,  38}, //  57
        { 52,  38}, //  58
        { 65,  38}, //  59
        { 79,  38}, //  60
        { 92,  38}, //  61
        {105,  38}, //  62
        {118,  38}, //  63
        {131,  38}, // 64
        {144,  38}, // 65
        {163,  38}, // 66
        {184,  38}, // 67
        {197,  38}, // 68
        {210,  38}, // 69

        {  0,  51}, //  70
        { 26,  51}, //  71
        { 39,  51}, //  72
        { 52,  51}, //  73
        { 65,  51}, //  74
        { 79,  51}, //  75
        { 92,  51}, //  76
        {105,  51}, //  77
        {118,  51}, //  78
        {131,  51}, // 79
        {144,  51}, // 80
        {158,  51}, // 81
        {171,  51}, // 82
        {184,  51}, // 83
        {197,  51}, // 84
        {210,  51}, // 85
        {224,  51}, // 86

        {  0, 64}, // 87
        { 18, 64}, // 88
        { 37, 64}, // 89
        { 92, 64}, // 90
        {130, 64}, // 91
        {145, 64}, // 92
        {158, 64}, // 93
        {171, 64}, // 94
        {184, 64}, // 95
        {197, 64}, // 96
        {210, 64}, // 97
    },
    {
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,              4,   4,  4,   4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,              4,   4,  4,   4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,              4,   4,  4,   4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,      4,              4,   4,  4,
		4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,          4,      4,      4,   4,  4,   4,
		4,  4,  4,          4,              4,  4,  4,              4,   4,      4,  4,
    }
};

#endif //RGB_MATRIX_ENABLE

enum __layers {
    WIN_B,
    WIN_WASD,
    WIN_FN,
    MAC_B,
    MAC_WASD,
    MAC_FN
};

enum colors { 
    WHITE, 
    RED, 
    GREEN, 
    BLUE 
};

enum colors led_color_status = WHITE;

static bool     fn_make_flag        = false;
static bool     Lkey_flag           = false;
static bool     reset_glint_flag    = false;
static bool     while_test_flag     = false;
static bool     alarm_flag          = false;
static uint16_t current_time        = 0;
static uint8_t  glint_cnt           = 0;
static uint16_t scancode            = 0;
static uint8_t  alarm_cnt           = 0;
static uint8_t  RGB_HSV_level;

HSV hsv;

void led_test(uint8_t color);
void clear_eeprom(void);
void rgb_hsv_updata_user(void);

#ifdef RGB_MATRIX_ENABLE

static uint16_t map_current_time    = 0;
static bool     pwron_flag          = false;

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if(pwron_flag == false){
        map_current_time     = timer_read();
        if(map_current_time<3000){
            map_current_time++;
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 150, 150, 150);
            }
        }
        if(map_current_time >= 3000)
            pwron_flag = true;
    }
    return true;
}

#endif //RGB_MATRIX_ENABLE

void led_init_ports(void){
    //set our LED pings as output
    setPinOutput(LED_NUM_LOCK_PIN); // LED1 Num Lock
    writePinHigh(LED_NUM_LOCK_PIN);
    setPinOutput(LED_CAPS_LOCK_PIN); // LDE2 Caps Lock
    writePinHigh(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_WIN_LOCK_PIN); // LED3 Win Lock
    writePinHigh(LED_WIN_LOCK_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(LED_NUM_LOCK_PIN, led_state.num_lock);
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
        writePin(LED_WIN_LOCK_PIN, keymap_config.no_gui);
 }
    return res;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
       return false;
    }
    switch (keycode) {
#ifndef DISABLE_M2_KEYCODES
        case MO(WIN_FN):
        case MO(MAC_FN):
            fn_make_flag = record->event.pressed;
            return true;
        case KC_GRV:
            if (fn_make_flag && record->event.pressed) {
                    Lkey_flag           = true;
                    current_time     = timer_read();
                    scancode = KC_GRV;
                    return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_LCTL:
            if (fn_make_flag && record->event.pressed) {

                if(while_test_flag)
                {
                    while_test_flag = false;
                    rgb_matrix_init();
                }
                else
                {
                    Lkey_flag           = true;
                    current_time     = timer_read();
                    scancode = KC_LCTL;
                }
                return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case DF(WIN_B):
          if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time     = timer_read();
                layer_state_set(WIN_B);
                set_single_persistent_default_layer(WIN_B);
                return false;
            }
            return true;
        case DF(MAC_B):
          if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time     = timer_read();
                keymap_config.no_gui = 0;
                eeconfig_update_keymap(keymap_config.raw);
                // layer_state_set(MAC_B);
                set_single_persistent_default_layer(MAC_B);
                return false;
            }
            return true;
        case TG(WIN_WASD):
          if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time     = timer_read();
 //               set_single_persistent_default_layer(WIN_WASD);
                return false;
            }
            return true;
        case TG(MAC_WASD):
          if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time     = timer_read();
//                set_single_persistent_default_layer(MAC_WASD);
                return false;
            }
            return true;
        case MAGIC_TOGGLE_GUI:
            if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time     = timer_read();
                writePin(LED_WIN_LOCK_PIN, !keymap_config.no_gui);
            }
            return true;
        case RGB_VAI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) < 4) {
                    alarm_cnt = 2;
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_VAD:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_val() / (RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4)) > 0) {
                    alarm_cnt = 2;
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.v = (uint8_t)(RGB_MATRIX_MAXIMUM_BRIGHTNESS / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_SAI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) < 4) {
                    alarm_cnt = 2;
                    RGB_HSV_level++;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_SAD:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_sat() / (UINT8_MAX / 4)) > 0) {
                    alarm_cnt = 2;
                    RGB_HSV_level--;
                    rgb_matrix_config.hsv.s = (uint8_t)(UINT8_MAX / 4) * RGB_HSV_level;
                }
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_HUI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                alarm_cnt = 2;
                RGB_HSV_level = (uint8_t)rgb_matrix_get_hue() / (UINT8_MAX / 6);
                RGB_HSV_level++;
                RGB_HSV_level %= 7;
                rgb_matrix_config.hsv.h = (uint8_t)(UINT8_MAX / 6) * RGB_HSV_level;     
                rgb_hsv_updata_user();
            }
            return false;
        case RGB_SPI:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 4)) < 4) {
                    alarm_cnt = 2;
                    RGB_HSV_level++;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 4) * RGB_HSV_level);
                }
            }
            return false;
        case RGB_SPD:
            if ((fn_make_flag && record->event.pressed) && (alarm_flag == 0)) {
                if ((RGB_HSV_level = (uint8_t)rgb_matrix_get_speed() / (UINT8_MAX / 4)) > 0) {
                    alarm_cnt = 2;
                    RGB_HSV_level--;
                    rgb_matrix_set_speed((uint8_t)(UINT8_MAX / 4) * RGB_HSV_level);
                }
            }
            return false;
#endif//DISABLE_M2_KEYCODES
        default:
            return true;
    }
}

void housekeeping_task_kb(void) {
    if(Lkey_flag){
        if(scancode == KC_GRV){
            if (timer_elapsed(current_time) >= 3000) {
                Lkey_flag = false;
                clear_eeprom();

                current_time  = timer_read();
                reset_glint_flag = true;
                glint_cnt = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        }
        else if(scancode == KC_LCTL){
            if (timer_elapsed(current_time) >= 3000) {
                Lkey_flag = false;
                clear_eeprom();

                while_test_flag = true;
                glint_cnt = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            }
        }
    }
    else if(reset_glint_flag){
        if ((timer_elapsed(current_time)) >= 300) {
            current_time = timer_read();
            if (((glint_cnt++) & 0x01 )== 0) {
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
            if (glint_cnt >= 3) {
                glint_cnt          = 0;
                reset_glint_flag = false;
                rgb_matrix_init();
            }
        }

    }
    else if(while_test_flag){
        if ((timer_elapsed(current_time)) >= 1000) {
            current_time = timer_read();
            if ((glint_cnt%4) == 0) {
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            } else if ((glint_cnt%4)== 1) {
                rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            } else if ((glint_cnt%4)== 2) {
                rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            } else if ((glint_cnt%4)== 3) {
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            }
            glint_cnt++;
            if(glint_cnt>=30)
            {
                glint_cnt = 0;
                while_test_flag = false;
                rgb_matrix_init();
            }
        }
    }
    else if(alarm_cnt != 0)
    {
        alarm_cnt--;
        if(alarm_cnt == 0){
            alarm_flag = true;
            rgb_matrix_toggle_noeeprom();
            current_time     = timer_read();
        }
    }
    else if(alarm_flag){
        if ((timer_elapsed(current_time)) >= 200) {
            rgb_matrix_toggle_noeeprom();
            alarm_flag = 0;
        }
    }
}


void led_test(uint8_t color) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);

    switch (color) {
        case WHITE:
            rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            break;

        case RED:
            rgb_matrix_sethsv_noeeprom(HSV_RED);
            break;

        case GREEN:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            break;

        case BLUE:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            break;
    }
}


void clear_eeprom(void) {
    layer_state_t default_layer_temp = default_layer_state;
    eeconfig_init();
    layer_state_set(default_layer_temp);
    default_layer_set(default_layer_temp);
    keymap_config.no_gui = 0;
    eeconfig_update_keymap(keymap_config.raw);
    #ifdef VIA_ENABLE
        // This resets the layout options
        via_set_layout_options(VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT);
        // This resets the keymaps in EEPROM to what is in flash.
        dynamic_keymap_reset();
        // This resets the macros in EEPROM to nothing.
        dynamic_keymap_macro_reset();
    #endif

    rgb_matrix_enable_noeeprom();
}

void rgb_hsv_updata_user(void)
{
    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
}
