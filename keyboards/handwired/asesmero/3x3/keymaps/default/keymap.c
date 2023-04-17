#include "3x3.h"

enum {
    LAYER_0 = 0,
	// ..., the rest of your layers
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	
	[LAYER_0] = LAYOUT_9(
		MEH(KC_A), MEH(KC_B), MEH(KC_C),
		MEH(KC_D), MEH(KC_E), MEH(KC_F), 
		MEH(KC_G), MEH(KC_H), MEH(KC_I)),

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case LAYER_0:
            // INSERT CODE HERE: turn on leds that correspond to YOUR_LAYER_0
			rgblight_setrgb(RGB_BLUE);
            break;

        // add case for each layer
    }
};
