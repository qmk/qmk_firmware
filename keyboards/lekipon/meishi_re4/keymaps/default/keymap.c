/* Copyright 2019 Lekipon
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

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  RGB_RST = SAFE_RANGE
};

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _HSV = 0,
};

// Defines the keycodes used by our macros in process_record_user
#define XXXXXXX KC_NO

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
      }
      #endif
      return false;
      break;
  }
  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_HSV] = LAYOUT( /* Base HSV */
        RGB_TOG , RGB_RST , RGB_M_R , RGB_M_SW )
};


#ifdef RGBLIGHT_ENABLE
// The first three LEDs are used as indicators for CAPS_LOCK, NUM_LOCK and SCROLL_LOCK.
void keyboard_post_init_user(void) {
	rgblight_set_effect_range(3, RGBLED_NUM-3);
	
	led_set_user((1<<USB_LED_CAPS_LOCK)|(1<<USB_LED_NUM_LOCK)|(1<<USB_LED_SCROLL_LOCK));
    wait_ms(200);
    led_set_user(0);
}

#define HSV_CAPS        0, 255, 128
#define HSV_CAPS_OFF    0, 255,  16
#define HSV_NUMLK      32, 255,  96
#define HSV_NUMLK_OFF  32, 255,  16
#define HSV_SCRLK      84, 255, 128
#define HSV_SCRLK_OFF  84, 255,  16



void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        sethsv(HSV_CAPS , (LED_TYPE *)&led[0]);
    } else {
        sethsv(HSV_CAPS_OFF, (LED_TYPE *)&led[0]);
    }
    	if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        sethsv(HSV_NUMLK, (LED_TYPE *)&led[1]);
    } else {
        sethsv(HSV_NUMLK_OFF, (LED_TYPE *)&led[1]);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        sethsv(HSV_SCRLK, (LED_TYPE *)&led[2]);
    } else {
        sethsv(HSV_SCRLK_OFF, (LED_TYPE *)&led[2]);
    }
    rgblight_set();
}
#endif




/* Rotary encoder settings */
void encoder_update_user(uint8_t index, bool clockwise) {
	if (index == 0) { /* First encoder */
  	if (clockwise) {
          rgblight_increase_hue_noeeprom();
        } else {
          rgblight_decrease_hue_noeeprom();
     }

  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
          rgblight_increase_sat_noeeprom();
        } else {
          rgblight_decrease_sat_noeeprom();
     }

  } else if (index == 2) { /* Third encoder */  
    if (clockwise) {
          rgblight_increase_val_noeeprom();
        } else {
          rgblight_decrease_val_noeeprom();
     }

  } else if (index == 3) { /* Fourth encoder */  
    if (clockwise) {
          rgblight_step_noeeprom();
        } else {
          rgblight_step_reverse_noeeprom();
     }

  }
}


void matrix_init_user(void) {

}


void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}


