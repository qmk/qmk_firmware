/*
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
#include "hlb60_h.h"

/* Data structure*/
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} kb_config_t;

/* keyboard preference */
kb_config_t kb_config;

/* Predefined colors */
const hsv_t OFF_COLOR = {HSV_OFF};
const hsv_t CONF_CHANGED_COLOR = {HSV_WHITE};
const hsv_t LAYER_FN_COLOR = {HSV_PURPLE};
const hsv_t LAYER_MEDIA_COLOR = {HSV_ORANGE};
const hsv_t LAYER_GAMING_COLOR = {HSV_CYAN};
const hsv_t LAYER_MAC_COLOR = {HSV_RED};
const hsv_t LAYER_INDIC_COLOR = {HSV_WHITE};
const hsv_t CAPS_INDIC_COLOR = {HSV_GREEN};

/* handling user indicator mode change */
uint8_t layerIndicatorChanged = 0;

/* Initial data container */
void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  kb_config.raw = 0;
  kb_config.rgb_layer_change = false; // We want this enabled by default
  eeconfig_update_kb(kb_config.raw); // Write default value to EEPROM now
}

/* Read indicator preference */
void keyboard_post_init_kb(void) {
    // Read the user config from EEPROM
    kb_config.raw = eeconfig_read_kb();
}

/* Activate LED for indicator */
void keyboard_pre_init_kb(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
    keyboard_pre_init_user();
}

/* Update user preference on layer indicator*/
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    process_record_user(keycode, record);

    switch (keycode) {
    case LAY_INDIC_RGB:
      if (record->event.pressed) {
        kb_config.rgb_layer_change ^= 1; // Toggles the status
        eeconfig_update_kb(kb_config.raw); // Writes the new status to EEPROM

        //We need a led status update
        layerIndicatorChanged = 1;
      }
      return false; // Skip all further processing of this key

    default:
      return true; // Process all other keycodes normally
  }
}

/* Managing indicator color based on state and layer */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    //default
    rgb_t rgbValue = hsv_to_rgb(OFF_COLOR);

    //Handling user mode toggle by updating indicator LED for few seconds
    if (layerIndicatorChanged == 1){
        //White color to warm
        rgb_t rgbValue = hsv_to_rgb(CONF_CHANGED_COLOR);
        RGB_MATRIX_INDICATOR_SET_COLOR(RGB_INDICATOR_LED_IDX, rgbValue.r, rgbValue.g, rgbValue.b);
        //Few seconds before getting back to normal
        wait_ms(RGB_BLINK_DURATION);
        //Default state
        rgbValue = hsv_to_rgb(OFF_COLOR);
        RGB_MATRIX_INDICATOR_SET_COLOR(RGB_INDICATOR_LED_IDX, rgbValue.r, rgbValue.g, rgbValue.b);
        //Done
        layerIndicatorChanged = 0;
    }

    //Capslock
    if (host_keyboard_led_state().caps_lock) {
        rgbValue = hsv_to_rgb(CAPS_INDIC_COLOR);
    } else if(kb_config.rgb_layer_change) {
        //Color depending current activated layer
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _FN:
                rgbValue = hsv_to_rgb(LAYER_FN_COLOR);
                break;
            case _MEDIA:
                rgbValue = hsv_to_rgb(LAYER_MEDIA_COLOR);
                break;
            case _GAME:
                rgbValue = hsv_to_rgb(LAYER_GAMING_COLOR);
                break;
            case _MAC:
                rgbValue = hsv_to_rgb(LAYER_MAC_COLOR);
                break;
            default:
                break;
        }
    }

    //Update indicator LED
    RGB_MATRIX_INDICATOR_SET_COLOR(RGB_INDICATOR_LED_IDX, rgbValue.r, rgbValue.g, rgbValue.b);
    return false;
}
