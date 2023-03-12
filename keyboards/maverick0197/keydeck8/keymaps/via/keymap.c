#include QMK_KEYBOARD_H

enum layers {
    DEFAULT,
	L02,
	L03,
	L04
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	 /*
     * ┌────┬────┬────┐
     * │ D0 │ D1 │ D4 │
     * ├────┼────┼────┤
     * │ C6 │ D7 │ E6 │
     * ├────┼────┼────┤
     * │ B4 │ B5 │ B6 │
     * └────┴────┴────┘
     */
	 [DEFAULT] = LAYOUT(
	 KC_MEDIA_PREV_TRACK, 	KC_MEDIA_PLAY_PAUSE, 	KC_MEDIA_NEXT_TRACK,
	 KC_1, 	KC_2, 	KC_3,
	 KC_4, 	KC_5, 	KC_6
	),
	[L02] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
	),
	[L03] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
	),
	[L04] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
	)
};
#if defined(ENCODER_MAP_ENABLE)
	const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
		[DEFAULT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
		[L02] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
		[L03] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
		[L04] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
	};
#else
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } 
		else {
            tap_code_delay(KC_VOLD, 10);
        }
    } 
    return false;
};
#endif // ENCODER_MAP_ENABLE