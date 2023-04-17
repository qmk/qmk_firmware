#include "3x3.h"
enum {
    LAYER_0 = 0,
    LAYER_1 = 1,
	LAYER_2 = 2,
	// ..., the rest of your layers
};

enum custom_keycodes {
    CK_1 ,
	CK_2 ,
	
	// ..., the rest of your keycodes
	
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	
	[LAYER_0] = LAYOUT_9(
		MEH(KC_A), MEH(KC_B), MEH(KC_C),
		MEH(KC_D), MEH(KC_E), MEH(KC_F), 
		MEH(KC_G), MEH(KC_H), TO(1)),

	[LAYER_1] = LAYOUT_9(
		MEH(KC_1), MEH(KC_2), MEH(KC_3),
		MEH(KC_4), MEH(KC_5), MEH(KC_6), 
		MEH(KC_7), MEH(KC_8), TO(2)),
		
	[LAYER_2] = LAYOUT_9(
		KC_F13, KC_F14, KC_F15,
		KC_F16, KC_F17, KC_F18, 
		KC_F19, KC_F20, TO(0)),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_1:
            if (record->event.pressed) {
                SEND_STRING("Custom Text 1");
            }
            return false;
			
		case CK_2:
            if (record->event.pressed) {
                SEND_STRING("Custom Text 2");
            }
            return false;
    }

    return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case LAYER_0:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_1
			rgblight_setrgb(RGB_BLUE);
            break;
        case LAYER_1:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
			rgblight_setrgb(RGB_RED);
            break;
        case LAYER_2:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_2
			rgblight_setrgb(RGB_GREEN);
            break;
        // add case for each layer
    }
};
