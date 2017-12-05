/* Copyright 2017 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
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

//**!! Currently after reboot the set rgb mode does not persist after reboot.  Need to find a way to "save" the rgb mode.  Color remains after reboot though.

#include "turbomech.h"
#include "quantum.h"
#include "action_layer.h"
#include "action.h"
#include "rgblight.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;
bool RGB_INIT = false;
bool TOG_STATUS = false;
bool NUMLAY_STATUS = false;
int RGB_current_mode;

bool caps_is_active = false;

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}
__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

//bool rgb_layer_change = true;

/*uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  switch (layer) {
      case _FUNCTION:

          rgblight_set_blue;
          rgblight_mode(1);


    break;

      default:
        break;
    }

  return state;
};*/

/*void rgblight_setrgb_indicator_caps(uint8_t r, uint8_t g, uint8_t b) {
  dprintf("rgblight set rgb: %u,%u,%u\n", r,g,b);
  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    led[i].r = 0;
    led[i].g = 0;
    led[i].b = 0;
  }
    led[5].r = 255;
    led[5].g = 0;
    led[5].b = 0;
  rgblight_set();
}*/
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    rgblight_mode(RGB_current_mode);
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}


void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  switch (layer) {
    case _FUNCTION:
        if (RGB_INIT) {} else {
          RGB_current_mode = rgblight_config.mode;
          RGB_INIT = true;
        }
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_set_cyan;
          rgblight_mode(3);
        }
        break;
    case _QWERTY:
       if (RGB_INIT) {} else {
          RGB_current_mode = rgblight_config.mode;
          RGB_INIT = true;
        }
        rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
       break;
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CAPS:
     if (record->event.pressed) {
           register_code(KC_CAPS);
            caps_is_active = !caps_is_active;
            if (caps_is_active) {
                    rgblight_mode(14);
                } else if (!caps_is_active) {
                  unregister_code(KC_CAPS);
                  rgblight_mode(RGB_current_mode);
                  //  rgblight_mode(rgblight_config.mode);
                }
            //rgblight_set();
            return false;
                break;
      case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
        //uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
       // if(shifted) {
       // rgblight_step_reverse();
       // }
        //else {
        rgblight_step();
        RGB_current_mode = rgblight_config.mode;
       // rgblight_set();
      }
      return false;
     // break;
          }
          break;
          return true;
  }
  return process_record_keymap(keycode, record);
};
