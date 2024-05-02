#include QMK_KEYBOARD_H

enum custom_keycodes {
	M_TGLHF = SAFE_RANGE,
	M_TGG
};

/*
*  Copy of knopps mini default May 16,2018
*  Added comments in code to more easilly understand it.
*
*   Key Layout
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	|  1  | |  2  | |  3  |
*	|_____| |_____| |_____|
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	|  4  | |  5  | |  6  |
*	|_____| |_____| |_____|
*
*  Each Layout row below keys. 1,2,3,4,5,6
*
*  Hold 3 when powering on for DFU Program Mode
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
*   Layer 0 (Default)
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	 Stop    VolUp   Play
*	|_____| |_____| |_____|
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	 Prev    VolDwn  Next
*	|_____| |_____| |_____|
*
* Button 1 (stop) is Held to activate Layer 3 only while held, User then selects the keymap to change to
*/
  	LAYOUT(
		LT(3, KC_MSTP), KC_VOLU, KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT),

/*
*   Layer 1
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	  ESC    Ctl+Z   CSf+Z
*	|_____| |_____| |_____|
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	 Ctl+X   Ctl+C   Ctl+V
*	|_____| |_____| |_____|
*
*/
	LAYOUT(
		LT(3, KC_ESC), C(KC_Z), C(S(KC_Z)), C(KC_X), C(KC_C), C(KC_V)),

/*
*   Layer 2
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	|  1  | |  2  | |  3  |
*	|_____| |_____| |_____|
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	|  4  | |Macro0  Macro1
*	|_____| |_____| |_____|
*
*/
	LAYOUT(
		LT(3, KC_1), KC_2, KC_3, KC_4, M_TGLHF, M_TGG),

/*
*  Layer 3 Key Layout
*  This Layer does the Layer Selection
*	 _____	 _____	 _____
*	| 	  | | 	  | | DFU
*	|None | |None | | FLash
*	|_____| |_____| |_____|
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	 Layer   Layer  Layer
*    0       1       2
*	|_____| |_____| |_____|
*
* Layers 0,1,2 have Button 1 held to activate this layer. Then press the specific layer to switch to it.
*
*/
	LAYOUT(
		KC_TRNS, KC_TRNS, QK_BOOT, TO(0), TO(1), TO(2)),

// More Layers that can be used, but are not by default

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};

void set_switch_led(int ledId, bool state) {
	if(state) {
		switch(ledId) {
			case 1:
				gpio_write_pin_high(D7);
				break;
			case 2:
				if(gpio_read_pin(B7)) {
					gpio_write_pin_high(C6);
				} else {
					gpio_write_pin_high(C7);
				}
				break;
			case 3:
				gpio_write_pin_high(D4);
				break;
			case 4:
				gpio_write_pin_high(E6);
				break;
			case 5:
				gpio_write_pin_high(B4);
				break;
			case 6:
				gpio_write_pin_high(D6);
				break;
		}
	} else {
		switch(ledId) {
			case 1:
				gpio_write_pin_low(D7);
				break;
			case 2:
				if(gpio_read_pin(B7)) {
					gpio_write_pin_low(C6);
				} else {
					gpio_write_pin_low(C7);
				}
				break;
			case 3:
				gpio_write_pin_low(D4);
				break;
			case 4:
				gpio_write_pin_low(E6);
				break;
			case 5:
				gpio_write_pin_low(B4);
				break;
			case 6:
				gpio_write_pin_low(D6);
				break;
		}
	}
}


void set_layer_led(int layerId) {
	gpio_write_pin_high(D5);
	gpio_write_pin_low(B6);
	gpio_write_pin_high(B0);
	switch(layerId) {
		case 0:
			gpio_write_pin_low(D5);
			break;
		case 1:
			gpio_write_pin_high(B6);
			break;
		case 2:
			gpio_write_pin_low(B0);
			break;
	}
}

void led_init_ports_user(void) {
  // led voor switch #1
	gpio_set_pin_output(D7);
	gpio_write_pin_low(D7);

  // led voor switch #2
	gpio_set_pin_output(C6);
	gpio_set_pin_output(C7);
	gpio_write_pin_low(C6);
	gpio_write_pin_low(C7);

  // led voor switch #3
	gpio_set_pin_output(D4);
	gpio_write_pin_low(D4);

  // led voor switch #4
	gpio_set_pin_output(E6);
	gpio_write_pin_low(E6);

  // led voor switch #5
	gpio_set_pin_output(B4);
	gpio_write_pin_low(B4);

  // led voor switch #6
	gpio_set_pin_output(D6);
	gpio_write_pin_low(D6);

	/*
	gpio_set_pin_output(D7);
	gpio_write_pin_high(D7);

	gpio_set_pin_output(C6);
	gpio_write_pin_high(C6);

	gpio_set_pin_output(D4);
	gpio_write_pin_high(D4);

	gpio_set_pin_output(E6);
	gpio_write_pin_high(E6);

	gpio_set_pin_output(B4);
	gpio_write_pin_high(B4);

	gpio_set_pin_output(D6);
	gpio_write_pin_high(D6);
	// */

	gpio_set_pin_output(D5);
	gpio_set_pin_output(B6);
	gpio_set_pin_output(B0);
	//led_set_layer(0);
}

void matrix_init_user(void) {
	led_init_ports_user();

	gpio_write_pin_high(B7);
	gpio_set_pin_input(B7);

	gpio_write_pin_high(D7);
	gpio_write_pin_high(C6);
	gpio_write_pin_high(C7);
	gpio_write_pin_high(D4);
	gpio_write_pin_high(E6);
	gpio_write_pin_high(B4);
	gpio_write_pin_high(D6);

	set_layer_led(0);
}

/*
*   NOTE:
*
*   In case you don't understand this coding stuff, please
*   feel free to mail me or post something
*   at the /r/knops subreddit and I will configure the code as
*   you wish for your needs to make the LEDs do what you want :-).
*
*   Contact me at:    support@knops.io
*
*
*	Knops Mini LED Numbers:
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	|  1  | |  2  | |  3  |    <---
*	|_____| |_____| |_____|       |      These LEDs are called 'Switch LEDs'
*	 _____	 _____	 _____        |----- To turn on/off these leds, use:
*	| 	  | | 	  | | 	  |       |	  set_switch_led( [1-6], [true/false]);
*	|  4  | |  5  | |  6  |    <---
*	|_____| |_____| |_____|
*
*	 < 0 >   < 1 >   < 2 >     <---      These front-LEDs are called 'Layer LEDs'
*							             To turn one of them on, use:
*										 set_layer_led( [0-2] );
*
*/

/*
* This function led_set_layer gets called when you switch between layers.
* It allows you to turn on and off leds for each different layer and do
* other cool stuff. Currently the GUI does not have LED support. I am working
* on that, but takes time.
*/
void led_set_layer(int layer) {
	switch(layer) {

			/**
			*   Here is an example to turn LEDs on and of. By default:
			*   - the LEDs are turned on in layer 0
			*   - the LEDs are turned off in layer 1
			*   - the LEDs don't change from state for layer 2
			*/

		case 0:
			set_layer_led(0); // Turn on only the first/left layer indicator
			set_switch_led(1, true);
			set_switch_led(2, true);
			set_switch_led(3, true);
			set_switch_led(4, true);
			set_switch_led(5, true);
			set_switch_led(6, true);
			break;

		case 1:
			set_layer_led(1); // Turn on only the second/middle layer indicator
			set_switch_led(1, false);
			set_switch_led(2, false);
			set_switch_led(3, false);
			set_switch_led(4, false);
			set_switch_led(5, false);
			set_switch_led(6, false);
			break;

		case 2:
			set_layer_led(2); // Turn on only the third/right layer indicator

			// Keep leds for layer two in their current state, since we don't use set_switch_led(SWITCH_ID, TRUE_OR_FALSE)

			break;
	}
}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case TO(0):
      if (record->event.pressed) {
        led_set_layer(0);
     }
     break;
  case TO(1):
      if (record->event.pressed) {
        led_set_layer(1);
     }
     break;
  case TO(2):
      if (record->event.pressed) {
        led_set_layer(2);
     }
     break;
  case M_TGLHF:
    if (record->event.pressed) {
      SEND_STRING("tglhf");
      tap_code(KC_ENT);
    }
  case M_TGG:
    if (record->event.pressed) {
      SEND_STRING("tgg");
      tap_code(KC_ENT);
    }
    return false;
  }
  return true;
}
