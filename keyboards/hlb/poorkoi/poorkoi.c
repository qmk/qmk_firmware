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
} kb_config_t;

/* keyboard preference */
kb_config_t kb_config;

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


void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  kb_config.raw = 0;
  kb_config.rgb_layer_change = false; // We want this enabled by default
  eeconfig_update_kb(kb_config.raw); // Write default value to EEPROM now
}

void keyboard_pre_init_kb(void) {
    rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT - 1);
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    // Read the user config from EEPROM
    kb_config.raw = eeconfig_read_kb();
}

/* Updating LED located under capslock */
bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(5, host_keyboard_led_state().caps_lock);
    led_update_user(led_state);
    return true;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    rgblight_set_layer_state(_BASE, layer_state_cmp(state, _BASE));
    default_layer_state_set_user(state);
    return state;
}

/* Use capslock led for layer indicator */
layer_state_t layer_state_set_kb(layer_state_t state) {
    rgblight_set_layer_state(_BASE, layer_state_cmp(state, _BASE));
    if(kb_config.rgb_layer_change){
        rgblight_set_layer_state(_FN, layer_state_cmp(state, _FN));
        rgblight_set_layer_state(_MEDIA, layer_state_cmp(state, _MEDIA));
        rgblight_set_layer_state(_GAME, layer_state_cmp(state, _GAME));
        rgblight_set_layer_state(_MAC, layer_state_cmp(state, _MAC));
    }

    layer_state_set_user(state);

    return state;
}

/* Update user preference on layer indicator*/
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    process_record_user(keycode, record);

    switch (keycode) {
    case LAY_INDIC_RGB:
      if (record->event.pressed) {
        kb_config.rgb_layer_change ^= 1; // Toggles the status
        eeconfig_update_kb(kb_config.raw); // Writes the new status to EEPROM

        if (kb_config.rgb_layer_change) { // if layer state indication is enabled,
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
