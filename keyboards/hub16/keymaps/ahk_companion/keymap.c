/*
Copyright 2019 Josh Johnson

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

#include QMK_KEYBOARD_H

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
static uint32_t rgb_preview_timer = 0;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        //Layer 0 - Base Layer (F13 to F24, and One Shot Layer 1,2,3 or Toggle Layer 4)
        [0] = LAYOUT(
                        KC_MPLY, KC_MUTE,
                KC_F13, KC_F14, KC_F15, KC_F16,
                KC_F17, KC_F18, KC_F19, KC_F20,
                KC_F21, KC_F22, KC_F23, KC_F24,
                OSL(1), OSL(2), OSL(3), TG(4)    //Transparent to let you go between layers
		),

        [1] = LAYOUT(
                        KC_MPLY, KC_MUTE,
                LALT(KC_F13), LALT(KC_F14), LALT(KC_F15), LALT(KC_F16),
                LALT(KC_F17), LALT(KC_F18), LALT(KC_F19), LALT(KC_F20),
                LALT(KC_F21), LALT(KC_F22), LALT(KC_F23), LALT(KC_F24),
                KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS         //Transparent to let you go between layers
        ),

        //Layer 2 - Shift + Function Key Layer
        [2] = LAYOUT(
                        KC_MPLY, KC_MUTE,
                LSFT(KC_F13), LSFT(KC_F14), LSFT(KC_F15), LSFT(KC_F16),
                LSFT(KC_F17), LSFT(KC_F18), LSFT(KC_F19), LSFT(KC_F20),
                LSFT(KC_F21), LSFT(KC_F22), LSFT(KC_F23), LSFT(KC_F24),
                KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS         //Transparent to let you go between layers
        ),

        //Layer 3 - Control + Function Key
        [3] = LAYOUT(
                        KC_MPLY, KC_MUTE,
                LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), LCTL(KC_F16),
                LCTL(KC_F17), LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F20),
                LCTL(KC_F21), LCTL(KC_F22), LCTL(KC_F23), LCTL(KC_F24),
                KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS         //Transparent to let you go between layers
        ),

        //Layer 4 - Multimedia
        [4] = LAYOUT(
                        KC_MPLY, KC_MUTE,
                KC_MPRV, KC_MPLY, KC_U,   KC_K,
                KC_NO,   KC_NO,   KC_ENT, KC_X,
                KC_NO,   RESET,   LSFT(KC_HASH),   KC_J,
                TG(5),   KC_TRNS, KC_TRNS,   KC_TRNS         //Transparent to let you go between layers
        ),

        //Layer 5 - Keyboard Lights, Programming and Special Functions
        [5] = LAYOUT(
                        KC_MPLY, KC_MUTE,
                RGB_MOD,  RGB_HUI, RGB_SAI,   RGB_VAI,
                RGB_RMOD, RGB_HUD, RGB_SAD,   RGB_VAD,
                RGB_TOG,  EEP_RST, RESET,     KC_LSHIFT,
                KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS         //Transparent to let you go between layers
        ),
};

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0,16,HSV_ORANGE}
    );
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0,16,HSV_GREEN}
    );
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0,16,HSV_RED}
    );
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0,16,HSV_BLUE}
    );
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0,16,HSV_WHITE}
    );
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0,16,HSV_TEAL}
    );
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        my_layer0_layer,
        my_layer1_layer,
        my_layer2_layer,
        my_layer3_layer,
        my_layer4_layer,
        my_layer5_layer
    );

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            tap_code(KC_MPRV);
        } else {
            tap_code(KC_MNXT);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return true;
}
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Allow for a preview of changes when modifying RGB
# if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
  switch (keycode) {
    case RGB_TOG ... VLK_TOG:
      for (uint8_t i = 0; i < RGBLIGHT_MAX_LAYERS; i++) {
        rgblight_set_layer_state(i, false);
      }
      rgb_preview_timer = timer_read32();
      break;
  }
# endif
  return;
}

//Set the appropriate layer color
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}

void keyboard_post_init_user(void) {
	//Enable the LED layers
	rgblight_layers = my_rgb_layers;
	layer_state_set_user(layer_state);
}

void matrix_scan_user(void) {
# if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    // Allow preview for
    if (rgb_preview_timer && TIMER_DIFF_32(timer_read32(), rgb_preview_timer) > PREVIEW_TIMEOUT) {
        rgb_preview_timer = 0;
        default_layer_state_set_user(default_layer_state);
        layer_state_set_user(layer_state);
        led_update_user((led_t) host_keyboard_leds());
    }
# endif
}

//EEPROM Reset Function
void eeconfig_init_user(void) {
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv_orange();  // Set it to orange by default
}
