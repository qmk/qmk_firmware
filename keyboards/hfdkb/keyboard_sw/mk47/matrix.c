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

#ifdef VIA_ENABLE
enum custom_keycodes {
    KC_RESET = USER00,   
};
#endif

enum colors { WHITE, RED, GREEN, BLUE };
enum colors led_color_status = WHITE;

static bool     fn_make_flag        = false;
static bool     Lkey_flag           = false;
static bool     reset_glint_flag    = false;
static bool     while_test_flag     = false;
static uint16_t current_time        = 0;
static uint8_t  glint_cnt           = 0;
static uint16_t scancode           = 0;

HSV hsv;

void led_test(uint8_t color);
void clear_eeprom(void);

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(1):
            fn_make_flag = false;
            if (record->event.pressed) {
                fn_make_flag = true;
            } 
            return true;
        case KC_DEL:
            if (fn_make_flag && record->event.pressed) {
                    Lkey_flag           = true;
                    current_time     = timer_read();
                    scancode = KC_DEL;
                    return false;
            } else {
                Lkey_flag = 0;
            }
            return true;
        case KC_SPC:
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
                    scancode = KC_SPC;
                }
                return false;   
            } else {
                Lkey_flag = 0;
            }
            return true;
#ifdef VIA_ENABLE
        case KC_RESET: {
        if (record->event.pressed) {

        #include "via.h"
        via_eeprom_set_valid(false);
        eeconfig_init_via();
        }
            return false;
        }
#endif
     default:
            return process_record_user(keycode, record);
    }
}

void housekeeping_task_kb(void) {
    if(Lkey_flag){
        if(scancode == KC_DEL)
        {
            if (timer_elapsed(current_time) >= 5000) {
                Lkey_flag = false;
                clear_eeprom();

                current_time  = timer_read();
                reset_glint_flag = true;
                glint_cnt = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        }
        else if(scancode == KC_SPC)
        {
            if (timer_elapsed(current_time) >= 3000) {
                Lkey_flag = false;
                clear_eeprom();

                while_test_flag = true;
                glint_cnt = 0;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            }
        }
    }
    else if(reset_glint_flag)
    {
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
        if ((timer_elapsed(current_time)) >= 1500) {
            current_time = timer_read();
            if ((glint_cnt%3) == 0) {
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            } else if ((glint_cnt%3)== 1) {
                rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            } else if ((glint_cnt%3)== 2) {
                rgb_matrix_sethsv_noeeprom(HSV_BLUE);
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

