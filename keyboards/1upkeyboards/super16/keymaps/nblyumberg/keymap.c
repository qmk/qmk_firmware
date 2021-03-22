#include QMK_KEYBOARD_H

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
                KC_F17, KC_CCCV, KC_F19, KC_F20,
                KC_F21, KC_F22, KC_F23, KC_2ENTER,
                OSL(1), OSL(2), OSL(3), TG(4)    //Transparent to let you go between layers
		),

        [1] = LAYOUT_ortho_4x4(
                LALT(KC_F13), LALT(KC_F14), LALT(KC_F15), LALT(KC_F16),
                LALT(KC_F17), LALT(KC_F18), LALT(KC_F19), LALT(KC_F20),
                LALT(KC_F21), LALT(KC_F22), LALT(KC_F23), LALT(KC_F24),
                KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS         //Transparent to let you go between layers
        ),

        //Layer 2 - Shift + Function Key Layer
        [2] = LAYOUT_ortho_4x4(
                LSFT(KC_F13), LSFT(KC_F14), LSFT(KC_F15), LSFT(KC_F16),
                LSFT(KC_F17), LSFT(KC_F18), LSFT(KC_F19), LSFT(KC_F20),
                LSFT(KC_F21), LSFT(KC_F22), LSFT(KC_F23), LSFT(KC_F24),
                KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS         //Transparent to let you go between layers
        ),

        //Layer 3 - Control + Function Key
        [3] = LAYOUT_ortho_4x4(
                LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), LCTL(KC_F16),
                LCTL(KC_F17), LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F20),
                LCTL(KC_F21), LCTL(KC_F22), LCTL(KC_F23), LCTL(KC_F24),
                KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS         //Transparent to let you go between layers
        ),

        //Layer 4 - Keyboard Lights. Programming and Special Functions
        [4] = LAYOUT_ortho_4x4(
                KC_MPRV, KC_MPLY, KC_MNXT,   KC_VOLU,
                RGB_TOG, RGB_MOD, RGB_RMOD,  KC_MUTE,
                TO(0),   RESET,   EEP_RST, KC_VOLD,
                KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS         //Transparent to let you go between layers
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
                    tap_code16(LCTL(KC_V));
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
            } 
			return true;
        default:
            return true;
    }
}


void keyboard_post_init_user(void) {
	//Enable the LED layers
	layer_state_set_user(layer_state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_sethsv_noeeprom(HSV_WHITE);
  switch(get_highest_layer(state)) {
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