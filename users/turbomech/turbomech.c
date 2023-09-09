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
//#include "process_unicode.h"

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;
bool RGB_INIT = false;
bool TOG_STATUS = false;
bool caps_is_active = false;
int RGB_current_mode;

void matirx_scan_kb (void) {
  if (RGB_INIT) {}
  else {
    RGB_current_mode = rgblight_config.mode;
    RGB_INIT = true;
        }
  rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
  TOG_STATUS = false;
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
/*void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    rgblight_mode(RGB_current_mode);
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}*/

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CAPS:
     if (record->event.pressed) {
        register_code(KC_CAPS);
        caps_is_active = !caps_is_active;
      if (caps_is_active) {
        rgblight_mode(14);
      }
      else if (!caps_is_active) {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);
      }
    }
    return false;
    break;

    case RGB_MOD:
    //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    if (record->event.pressed) {
      rgblight_mode(RGB_current_mode);
      rgblight_step();
      RGB_current_mode = rgblight_config.mode;
      // rgblight_set();
    }
    return false;
    break;

    case KC_RESET:
    if (record->event.pressed) {
      rgblight_enable();
      rgblight_mode(1);
      rgblight_setrgb(255, 255, 255);
      //_delay_ms(2000);
      reset_keyboard();
    }
    return false;
    break;

    /*case _FLIP:  //(╯°□°）╯︵ ┻━┻
      if (record->event.pressed) {
       register_code(KC_LPRN);
       unregister_code(KC_LPRN);
       register_unicode(0x00B0);

        UC(0x256F);
        PROCESS_UNICODE(UC(0x00B0));
        SEND_TAP(UC(0x25A1));
        SEND_TAP(UC(0x00B0));
        SEND_STRING(")");
        SEND_TAP(UC(0x256F));
        SEND_TAP(UC(0xFE35));
        SEND_TAP(UC(0x253B));
        SEND_TAP(UC(0x2501));
        SEND_TAP(UC(0x253B));
			}
			return false;
			break;*/

  return true;
  break;
  }
return process_record_keymap(keycode, record);
}
