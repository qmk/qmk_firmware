#include QMK_KEYBOARD_H

enum custom_keycodes {
	M_TGLHF = SAFE_RANGE,
	M_TGG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		LT(3, KC_MSTP), KC_VOLU, KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT),

	LAYOUT(
		LT(3, KC_ESC), C(KC_Z), C(S(KC_Z)), C(KC_X), C(KC_C), C(KC_V)),

	LAYOUT(
		LT(3, KC_1), KC_2, KC_3, KC_4, M_TGLHF, M_TGG),

	LAYOUT(
		KC_TRNS, KC_TRNS, RESET, TO(0), TO(1), TO(2)),

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

void led_init_ports_user(void) {
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

void matrix_init_user(void) {
	led_init_ports_user();

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
    return false;
  case M_TGG:
    if (record->event.pressed) {
      SEND_STRING("tgg");
      tap_code(KC_ENT);
    }
    return false;
  }
  return true;
}
