#include QMK_KEYBOARD_H

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
*	  ESC    Macro3  Macro4
*	|_____| |_____| |_____|
*	 _____	 _____	 _____
*	| 	  | | 	  | | 	  |
*	 Macro5  Macro6  Macro7
*	|_____| |_____| |_____|
*
*/
	LAYOUT(
		LT(3, KC_ESC), M(3), M(4), M(5), M(6), M(7)),

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
		LT(3, KC_1), KC_2, KC_3, KC_4, M(0), M(1)),

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
		KC_TRNS, KC_TRNS, RESET, TO(0), TO(1), TO(2)),

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

//  Older way of Macros found here: https://docs.qmk.fm/features/macros

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	//keyevent_t event = record->event;

	switch (id) {
		case 0:
			if (record->event.pressed) {
			/*
			* This is Macro 0
			* Content:  tglhf<enter>
			*/
				return MACRO( T(T), T(G), T(L), T(H), T(F), T(ENT), END );
			}
			break;
		case 1:
			if (record->event.pressed) {
			/*
			* This is Macro 1
			* Content:  tgg<enter>
			*/
				return MACRO( T(T), T(G), T(G), T(ENT), END );
			}
			break;
		case 2:
			if (record->event.pressed) {
			/*
			* This is Macro 2
			* Content:  Press and hold "no" , type "l", release "no"<enter>
			* I haven't found what this "NO" key maps to
			*/
				return MACRO( D(NO), T(L), U(NO), END );
			}
			break;
		case 3:
			if (record->event.pressed) {
			/*
			* This is Macro 3
			* Content:  press/hold LCTRL, type "2", release LCTRL
			*/
				return MACRO( D(LCTL), T(Z), U(LCTL), END );
			}
			break;
		case 4:
			if (record->event.pressed) {
			/*
			* This is Macro 4
			* Content:  press/hold LCTRL, type "2", release LCTRL
			*/
				return MACRO( D(LCTL), D(LSFT), T(Z), U(LSFT), U(LCTL), END );
			}
			break;
		case 5:
			if (record->event.pressed) {
			/*
			* This is Macro 5
			* Content:  press/hold LCTRL, type "x", release LCTRL
			*/
				return MACRO( D(LCTL), T(X), U(LCTL), END );
			}
			break;
		case 6:
			if (record->event.pressed) {
			/*
			* This is Macro 6
			* Content:  press/hold LCTRL, type "c", release LCTRL
			*/
				return MACRO( D(LCTL), T(C), U(LCTL), END );
			}
			break;
		case 7:
			if (record->event.pressed) {
			/*
			* This is Macro 7
			* Content:  press/hold LCTRL, type "v", release LCTRL
			*/
				return MACRO( D(LCTL), T(V), U(LCTL), END );
			}
			break;
	}
	return MACRO_NONE;
}



void set_switch_led(int ledId, bool state) {
	if(state) {
		switch(ledId) {
			case 1:
				PORTD |= (1<<7);
				break;
			case 2:
				if((PINB & (1 << 7)) != 0) {
					PORTC |= (1<<6);
				} else {
					PORTC |= (1<<7);
				}
				break;
			case 3:
				PORTD |= (1<<4);
				break;
			case 4:
				PORTE |= (1<<6);
				break;
			case 5:
				PORTB |= (1<<4);
				break;
			case 6:
				PORTD |= (1<<6);
				break;
		}
	} else {
		switch(ledId) {
			case 1:
				PORTD &= ~(1<<7);
				break;
			case 2:
				if((PINB & (1 << 7)) != 0) {
					PORTC &= ~(1<<6);
				} else {
					PORTC &= ~(1<<7);
				}
				break;
			case 3:
				PORTD &= ~(1<<4);
				break;
			case 4:
				PORTE &= ~(1<<6);
				break;
			case 5:
				PORTB &= ~(1<<4);
				break;
			case 6:
				PORTD &= ~(1<<6);
				break;
		}
	}
}


void set_layer_led(int layerId) {
	PORTD |= (1<<5);
	PORTB &= ~(1<<6);
	PORTB |= (1<<0);
	switch(layerId) {
		case 0:
			PORTD &= ~(1<<5);
			break;
		case 1:
			PORTB |= (1<<6);
			break;
		case 2:
			PORTB &= ~(1<<0);
			break;
	}
}

void matrix_init_user(void) {
	led_init_ports();

	PORTB |= (1 << 7);
	DDRB &= ~(1<<7);

	PORTD |= (1<<7);
	PORTC |= (1<<6);
	PORTC |= (1<<7);
	PORTD |= (1<<4);
	PORTE |= (1<<6);
	PORTB |= (1<<4);
	PORTD |= (1<<6);

	set_layer_led(0);
}

void matrix_scan_user(void) {
}

void led_init_ports() {
  // led voor switch #1
	DDRD |= (1<<7);
	PORTD &= ~(1<<7);

  // led voor switch #2
	DDRC |= (1<<6);
	DDRC |= (1<<7);
	PORTC &= ~(1<<6);
	PORTC &= ~(1<<7);

  // led voor switch #3
	DDRD |= (1<<4);
	PORTD &= ~(1<<4);

  // led voor switch #4
	DDRE |= (1<<6);
	PORTE &= ~(1<<6);

  // led voor switch #5
	DDRB |= (1<<4);
	PORTB &= ~(1<<4);

  // led voor switch #6
	DDRD |= (1<<6);
	PORTD &= ~(1<<6);

	/*
	DDRD |= (1<<7);
	PORTD |= (1<<7);

	DDRC |= (1<<6);
	PORTC |= (1<<6);

	DDRD |= (1<<4);
	PORTD |= (1<<4);

	DDRE |= (1<<6);
	PORTE |= (1<<6);

	DDRB |= (1<<4);
	PORTB |= (1<<4);

	DDRD |= (1<<6);
	PORTD |= (1<<6);
	// */

	DDRD |= (1<<5);
	DDRB |= (1<<6);
	DDRB |= (1<<0);
	//led_set_layer(0);
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

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
  }
  return true;
}
