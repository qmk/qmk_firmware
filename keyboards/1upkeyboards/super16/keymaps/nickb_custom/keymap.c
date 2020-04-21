/* Copyright 2019 MechMerlin
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
//#define RBG_VAL 16 //Define 16 RGB LEDs

uint16_t copy_paste_timer;
uint16_t enter_timer;

extern rgblight_config_t rgblight_config;

// Define custom keycodes
enum my_keycodes {
	KC_CCCV = SAFE_RANGE,
	KC_2ENTER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//Layer 0 - Base Layer (F13 to F24, and One Shot Layer 1,2,3,4)

	[0] = LAYOUT_ortho_4x4(
		KC_F13, KC_F14, KC_F15, KC_F16, 
		KC_F17, KC_CCCV, KC_F19, KC_F20, //Changing KC_F18 to KC_CCCV 
		KC_F21, KC_F22, KC_F23, KC_2ENTER, //Changing KC_F24 to KC_2ENTER
		OSL(1), OSL(2), OSL(3), TG(4)  //One Shot Layer Activation
		),
//Layer 1 - Alt + Function Key Layer
	[1] = LAYOUT_ortho_4x4(
		LALT(KC_F13), LALT(KC_F14), LALT(KC_F15), LALT(KC_F16), 
		LALT(KC_F17), LALT(KC_F18), LALT(KC_F19), LALT(KC_F20), 
		LALT(KC_F21), LALT(KC_F22), LALT(KC_F23), LALT(KC_F24), 
	        KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS         //Transparent to let you go between layers
		),

//Layer 2 - Shift + Function Key Layer
	[2] = LAYOUT_ortho_4x4(
		LSFT(KC_F13), LSFT(KC_F14), LSFT(KC_F15), LSFT(KC_F16), 
		LSFT(KC_F17), LSFT(KC_F18), LSFT(KC_F19), LSFT(KC_F20), 
		LSFT(KC_F21), LSFT(KC_F22), LSFT(KC_F23), LSFT(KC_F24), 
	        KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS         //Transparent to let you go between layers
		),

//Layer 3 - Control + Function Key 
	[3] = LAYOUT_ortho_4x4(
		LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), LCTL(KC_F16), 
		LCTL(KC_F17), LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F20), 
		LCTL(KC_F21), LCTL(KC_F22), LCTL(KC_F23), LCTL(KC_F24), 
	        KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS         //Transparent to let you go between layers
		),

//Layer 4 - Keyboard Lights. Programming and Special Functions
	[4] = LAYOUT_ortho_4x4(
		KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, 
		RGB_TOG, RGB_MOD, RGB_RMOD, KC_MUTE, 
		TO(0), RESET, KC_2ENTER, KC_VOLD, 
	        KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS         //Transparent to let you go between layers
		),
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else {  // Tap, paste
                    tap_code16(KC_F18);
                }
            } return true;
		case KC_2ENTER:
		    if (record->event.pressed) {
                enter_timer = timer_read();
            } else {
                if (timer_elapsed(enter_timer) > TAPPING_TERM) {  // Hold, shift+enter
                    tap_code16(LSFT(KC_ENTER));
                } else {  // Tap, enter
                    tap_code16(KC_F24);
                }
            } return true;
		
        default:
            return true;
    }
}

 void eeconfig_init_user(void) {  // EEPROM is getting reset!
  // use the non noeeprom versions, to write these values to EEPROM too
//  rgblight_enable(); // Enable RGB by default
    rgblight_sethsv_noeeprom(HSV_WHITE);  // Set it to white by default
//  rgblight_mode(RGBLIGHT_MODE_BREATHING); // set to breathing by default
}

/*
//Modifying the Layer RGB using the new method
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{1,16,HSV_WHITE}
	);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{1,16,HSV_GREEN}
	);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{1,16,HSV_RED}
	);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{1,16,HSV_BLUE}
	);
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{1,16,HSV_ORANGE}
	);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		my_layer4_layer,
		my_layer3_layer,
		my_layer2_layer,
		my_layer1_layer,
		my_base_layer
	);
void keyboard_post_init_user(void) {
	//Enable the LED layers
	rgblight_layers = my_rgb_layers;
}



layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(1, layer_state_cmp(state, 1));
	rgblight_set_layer_state(2, layer_state_cmp(state, 2));
	rgblight_set_layer_state(3, layer_state_cmp(state, 3));
	rgblight_set_layer_state(4, layer_state_cmp(state, 4));
	rgblight_set_layer_state(5, layer_state_cmp(state, 5));
	return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

// END of New RGB method
*/ 

void keyboard_post_init_user(void){
	layer_state_set_user(layer_state);
}


layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_sethsv_noeeprom(HSV_WHITE);
  switch(biton32(state)) {
  case 1:
    // Green
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_GREEN);
    break;
  case 2:
    // Red
    rgblight_enable_noeeprom();	
    rgblight_sethsv_noeeprom(HSV_RED);
    break;
  case 3:
    // Blue
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLUE);
    break;
  case 4:
    // Orange
    rgblight_enable_noeeprom();
//    rgblight_sethsv_noeeprom(HSV_PURPLE);
    rgblight_sethsv_noeeprom(HSV_ORANGE);
    break;
  default:
    // White
    //Read RGB Light State
    rgblight_config.raw = eeconfig_read_rgblight();
    //If enabled, set white
    if (rgblight_config.enable) {
		rgblight_sethsv_noeeprom(HSV_WHITE);
	} else { //Otherwise go back to disabled
		rgblight_disable_noeeprom();
	}
    break;
}
return state;
}


