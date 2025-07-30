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
#include "poorkoi.h"

typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

/* User preference */
user_config_t user_config;

/* Feature toggle blink duration */
const uint16_t rgbBlinkDuration = 300;

/* RGB Layers definition*/
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, HSV_OFF}
);
const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, LAYER_FN_COLOR}
);
const rgblight_segment_t PROGMEM my_media_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, LAYER_MEDIA_COLOR}
);
const rgblight_segment_t PROGMEM my_gaming_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, LAYER_GAMING_COLOR}
);
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, LAYER_MAC_COLOR}
);
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, CAPS_LOCK_COLOR}
);
const rgblight_segment_t PROGMEM my_indicator_on_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, LAYER_INDIC_COLOR},
    {9, 5, LAYER_INDIC_COLOR}
);
const rgblight_segment_t PROGMEM my_indicator_off_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {16, 1, LAYER_INDIC_COLOR},
    {2, 5, LAYER_INDIC_COLOR}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,
    my_fn_layer,
    my_media_layer,
    my_gaming_layer,
    my_mac_layer,
    my_capslock_layer,
    my_indicator_on_layer,
    my_indicator_off_layer
);


void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.rgb_layer_change = false; // We want this enabled by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv(HSV_PURPLE);  // Set it to PURPLE by default
  rgblight_mode(1); // set to solid by default
}

void keyboard_pre_init_kb(void) {
    rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT - 1);
    keyboard_pre_init_user();
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
}

/* Updating LED located under capslock */
bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(5, host_keyboard_led_state().caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_BASE, layer_state_cmp(state, _BASE));
    return state;
}

/* Use capslock led for layer indicator */
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_BASE, layer_state_cmp(state, _BASE));

    if(user_config.rgb_layer_change){
        rgblight_set_layer_state(_FN, layer_state_cmp(state, _FN));
        rgblight_set_layer_state(_MEDIA, layer_state_cmp(state, _MEDIA));
        rgblight_set_layer_state(_GAME, layer_state_cmp(state, _GAME));
        rgblight_set_layer_state(_MAC, layer_state_cmp(state, _MAC));
    }

    return state;
}

/* Update user preference on layer indicator*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LAY_INDIC_RGB:
      if (record->event.pressed) {
        user_config.rgb_layer_change ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM

        if (user_config.rgb_layer_change) { // if layer state indication is enabled,
            rgblight_blink_layer(6, rgbBlinkDuration);
        }else{
            rgblight_blink_layer(7, rgbBlinkDuration);
        }

        layer_state_set(layer_state);   // then immediately update the layer color
      }
      return false; // Skip all further processing of this key

    default:
      return true; // Process all other keycodes normally
  }
}
