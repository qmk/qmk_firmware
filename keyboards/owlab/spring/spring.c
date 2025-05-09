/* 
Copyright 2021 OwLab

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
#include "quantum.h"

enum caps_modes{
    CAPS_MODE_UPPER = 0, //UPPER CASE 
    CAPS_MODE_LOWER      //LOWER CASE
};

uint8_t caps_mode_index;
rgblight_config_t pre_rgb;
uint8_t dir_hue, dir_sat;

bool caps_in = false; 
uint32_t caps_timer; 




void switch_caps_mode(uint8_t mode){
       switch(mode){
            case CAPS_MODE_UPPER:
            dir_hue = 0;
            dir_sat = 240; 
            break;

            case CAPS_MODE_LOWER: 
            dir_hue = 88;
            dir_sat = 255;
            break;

            default:
            break;           
        }
        rgblight_sethsv_noeeprom(dir_hue,dir_sat,pre_rgb.val); 
    
}


void init_caps_mode(uint8_t mode){
    pre_rgb.mode = rgblight_get_mode();
    pre_rgb.hue = rgblight_get_hue();
    pre_rgb.sat = rgblight_get_sat();
    pre_rgb.val = rgblight_get_val();
    caps_in = true;

    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);  
    switch_caps_mode(mode);

}


void set_caps_mode(uint8_t mode){
    if(caps_in == false){
       init_caps_mode(mode);
    }else{
        switch_caps_mode(mode);
    }
    caps_timer = timer_read32();
    
    
}


void housekeeping_task_kb(void) {
	if(caps_in){
		if(timer_elapsed32(caps_timer) > 3000){
            rgblight_sethsv(pre_rgb.hue, pre_rgb.sat, pre_rgb.val);	
			rgblight_mode(pre_rgb.mode);
            caps_in = false;
		}
	}
}


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
        case QK_UNDERGLOW_TOGGLE:
        case QK_UNDERGLOW_MODE_NEXT:
        case QK_UNDERGLOW_MODE_PREVIOUS:
        case QK_UNDERGLOW_HUE_UP:
        case QK_UNDERGLOW_HUE_DOWN:
        case QK_UNDERGLOW_SATURATION_UP:
        case QK_UNDERGLOW_SATURATION_DOWN:
        case QK_UNDERGLOW_VALUE_UP:
        case QK_UNDERGLOW_VALUE_DOWN:
            if(caps_in){  
                return false;
            }  
        break;


        case KC_CAPS:
            if(host_keyboard_led_state().caps_lock){ 
                caps_mode_index = CAPS_MODE_LOWER;
            } else{
                caps_mode_index = CAPS_MODE_UPPER;
            }
            set_caps_mode(caps_mode_index); 
        break;

   
        default:
        break;
    }
  }
  return process_record_user(keycode, record);
}
