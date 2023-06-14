/* Copyright 2023 temp4gh
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

#include QMK_KEYBOARD_H
#include "config.h"
#include <stdarg.h>
#include <stdio.h>
//#include "quantum.h"
#include "gpio.h"
#include "encoder.h"

#include "spi_master.h"

#include "ak84bt.h"

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
    bool     winlock_state :1;
  };
}user_config_t;

user_config_t user_config;

enum layer_names
{
    _BASE,
    _FnLay,
    _NONE1,
    _NONE2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {  
    [_BASE] = LAYOUT(    
    KC_ESC  , XXXXXXX  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5    , KC_F6   , KC_F7   , KC_F8    , KC_F9   ,   KC_F10  , KC_F11  , KC_F12  , XXXXXXX , KC_END  ,
    KC_GRV  , KC_1     , KC_2    , KC_3    , KC_4    , KC_5    , KC_6     , KC_7    , KC_8    , KC_9     , KC_0    ,   KC_MINS , KC_EQL  , KC_BSPC , KC_HOME , XXXXXXX ,
    KC_TAB  , KC_Q     , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y     , KC_U    , KC_I    , KC_O     , KC_P    ,   KC_LBRC , KC_RBRC , KC_BSLS , KC_DEL  , XXXXXXX ,
    KC_CAPS , KC_A     , KC_S    , KC_D    , KC_F    , KC_G    , KC_H     , KC_J    , KC_K    , KC_L     , KC_SCLN ,   KC_QUOT , XXXXXXX , KC_ENT  , KC_PGUP , XXXXXXX ,
    KC_LSFT , XXXXXXX  , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B     , KC_N    , KC_M    , KC_COMM  , KC_DOT  ,   KC_SLSH , KC_RSFT , KC_UP   , KC_PGDN , XXXXXXX ,
    KC_LCTL , KC_LGUI  , KC_LALT , XXXXXXX , XXXXXXX , XXXXXXX , KC_SPC   , XXXXXXX , XXXXXXX , KC_RALT  , MO(_FnLay), KC_RCTL , KC_LEFT , KC_DOWN , KC_RIGHT, XXXXXXX
    ),
    [_FnLay] = LAYOUT(
    KC_RESET_FACTORY , XXXXXXX  , KC_MY_COMPUTER , KC_WWW_HOME, KC_CALCULATOR, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY,  KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_MAIL, XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_BT1   , KC_BT2  , KC_BT3  , KC_2D4G , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX ,   XXXXXXX , XXXXXXX , XXXXXXX , RGB_MOD , XXXXXXX ,
    XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX , KC_SCRL , KC_INS   , KC_PSCR ,   XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX ,   XXXXXXX , KC_BK_LIGHT_HSV_SWITCH, XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , RGB_TOG  , RGB_MOD , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX ,   XXXXXXX , XXXXXXX , KC_BK_LIGHTNESS_UP , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_WINLOCK_ONOFF, XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BK_LIGHT_ONOFF, XXXXXXX , XXXXXXX , XXXXXXX  , MO(_FnLay), XXXXXXX , KC_BK_LIGHT_SPEED_DOWN , KC_BK_LIGHTNESS_DOWN , KC_BK_LIGHT_SPEED_UP , XXXXXXX
    )    
};

void keyboard_post_init_user(void)
{ 
}

void keyboard_pre_init_user(void)
{
}

bool winlock_state = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{    
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\r\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif    

    switch (keycode)
    {                             
        case KC_WINLOCK_ONOFF:
        {
            if (record->event.pressed)
            {
                winlock_state ^= 1;
            }

            return false;
        }

        case KC_BK_LIGHT_ONOFF:
        {
#ifdef RGB_MATRIX_ENABLE    
            if (record->event.pressed)
            {        
                rgb_matrix_toggle();
            }
#endif

            return false;
        }        

        case KC_BK_LIGHTNESS_UP:
        {
#ifdef RGB_MATRIX_ENABLE            
            if (record->event.pressed)
            {        
                rgb_matrix_increase_val();
            }
#endif            
            return false;
        }

        case KC_BK_LIGHTNESS_DOWN:
        {
#ifdef RGB_MATRIX_ENABLE            
            if (record->event.pressed)
            {        
                rgb_matrix_decrease_val();
            }
#endif            
            return false;
        }

        case KC_BK_LIGHT_SPEED_UP:
        {
#ifdef RGB_MATRIX_ENABLE            
            if (record->event.pressed)
            {        
                rgb_matrix_increase_speed();
            }
#endif            
            return false;
        }

        case KC_BK_LIGHT_SPEED_DOWN:
        {
#ifdef RGB_MATRIX_ENABLE            
            if (record->event.pressed)
            {        
                rgb_matrix_decrease_speed();
            }
#endif            
            return false;
        }
        
        case KC_RGB_SWITCH_EFFECT:
        {
#ifdef RGB_MATRIX_ENABLE            
            if (record->event.pressed)
            {        
                rgb_matrix_step();
            }
#endif            
            return false;
        }

        case KC_LGUI:
        case KC_RGUI:
        {
            if (record->event.pressed)
            {                
                if(winlock_state)
                {
                    return false;
                }
            }
        }

        default:
        {
            return true;
        }
    }

    return true;
}
