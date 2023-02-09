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
#include "eeconfig.h"
#include "quantum.h"

enum __layers {
    WIN_B,
    WIN_WASD,
    WIN_FN,
    MAC_B,
    MAC_WASD,
    MAC_FN
};

enum colors { WHITE, RED, GREEN, BLUE };
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

HSV hsv;

void led_test(uint8_t color);
void clear_eeprom(void);

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

dprintf("keycode = 0x%X,TG(WIN_B) = 0x%X,TG(MAC_B) = 0x%X\r\n",keycode,TG(WIN_B),TG(MAC_B));
//    uint8_t s = rgblight_get_sat();
 //   uint8_t v = rgblight_get_val();

    switch (keycode) {
        case MO(WIN_FN):
        case MO(MAC_FN):
            fn_make_flag = false;
            if (record->event.pressed) {
                fn_make_flag = true;
            } 
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
                set_single_persistent_default_layer(WIN_B);
                return false;  
            }
            return true;
        case DF(MAC_B):
          if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                alarm_flag = true;
                rgb_matrix_toggle_noeeprom();
                current_time     = timer_read();
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
            }
            return true;
        case RGB_VAI:
                if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                    if(rgblight_get_val()<180){
                         alarm_cnt = 2;
                    }
                }
            return true;
        case RGB_VAD:
                if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                    if(rgblight_get_val()>10){
                        alarm_cnt = 2;
                    }
                }
            return true;
        case RGB_SAI:
                if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                    if(rgblight_get_sat()<240){
                         alarm_cnt = 2;
                    }
                }
            return true;
        case RGB_SAD:
                if ((fn_make_flag && record->event.pressed)&&(alarm_flag == 0)) {
                    if(rgblight_get_sat()>10){
                        alarm_cnt = 2;
                    }
                }
            return true;
        default:
            return process_record_user(keycode, record);
    }
}

void matrix_scan_kb(void) {
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
    default_layer_set(default_layer_temp);

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

