#include "2x5keypad.h"
#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL_LAYER]=
	KEYMAP(
		TO(1),    WIN_TAB, KC_HOME, KC_UP,   KC_END, 
		WIN_LOCK, KC_MUTE, KC_LEFT, KC_DOWN, KC_RGHT),

    [MEDIA_LAYER]=
	KEYMAP(
		TO(2),    KC_CALC, KC_MPRV, KC_MNXT, KC_VOLU, 
		KC_TRNS,  KC_TRNS, KC_MSTP, KC_MPLY, KC_VOLD),

    [TBD_LAYER2]=
	KEYMAP(
		TO(3),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [TBD_LAYER3]=
	KEYMAP(
		TO(0),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

    // keyevent_t event = record->event;

    switch (id) {

	}
    return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

uint32_t layer_state_set_user(uint32_t state)
{
    switch (biton32(state))
    {
    case NORMAL_LAYER:
	writePinLow(RED_LED);
	writePinLow(BLUE_LED);
	writePinLow(GREEN_LED);
	break;
    case MEDIA_LAYER:
	writePinHigh(RED_LED);
	writePinLow(BLUE_LED);
	writePinLow(GREEN_LED);
	break;
    case TBD_LAYER2:
	writePinLow(RED_LED);
	writePinHigh(BLUE_LED);
	writePinLow(GREEN_LED);
	break;
    case TBD_LAYER3:
	writePinLow(RED_LED);
	writePinLow(BLUE_LED);
	writePinHigh(GREEN_LED);
	break;
	}
    return state;
}
