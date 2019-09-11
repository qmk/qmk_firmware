#include QMK_KEYBOARD_H

#define WIN_TAB LGUI(KC_TAB)
#define WIN_LOCK LGUI(KC_L)

enum layers {
  NORMAL_LAYER = 0,
  MEDIA_LAYER,
  TBD_LAYER2,
  FRENCH_LAYER
};

#define A_GRAVE UC(0x00E0)
#define E_AIGU  UC(0x00E9)
#define E_GRAVE UC(0x00E8)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NORMAL_LAYER] = LAYOUT(TO(1),    WIN_TAB, KC_HOME, KC_UP,   KC_END, 
			    WIN_LOCK, KC_MUTE, KC_LEFT, KC_DOWN, KC_RGHT),

    [MEDIA_LAYER]  = LAYOUT(TO(2),    KC_CALC, KC_MPRV, KC_MNXT, KC_VOLU, 
			    KC_TRNS,  KC_TRNS, KC_MSTP, KC_MPLY, KC_VOLD),

    [TBD_LAYER2]   = LAYOUT(TO(3),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [FRENCH_LAYER] = LAYOUT(TO(0),    A_GRAVE, E_AIGU,  E_GRAVE, KC_TRNS, 
			    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};


/* DISABLED
void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}
*/


void matrix_init_user(void)
{
    set_unicode_input_mode(UC_WINC);  /* See https://jayliu50.github.io/qmk-cheatsheet/ */
}


layer_state_t layer_state_set_user(layer_state_t state)
{
    turn_off_leds();

    switch (biton32(state))
    {
    case NORMAL_LAYER:
	break;

    case MEDIA_LAYER:
	turn_on_led(RED_LED);
	break;

    case TBD_LAYER2:
	turn_on_led(BLUE_LED);
	break;

    case FRENCH_LAYER:
	turn_on_led(GREEN_LED);
	break;
	}
    return state;
}
