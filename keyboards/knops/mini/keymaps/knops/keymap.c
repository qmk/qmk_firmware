#include "mini.h"

/*KNOPS_MISC*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/*KNOPS_KEYMAP*/

};

void set_led_state(int ledId, bool state) {
	if(state) {
		switch(ledId) {
			/* LED 0 to 5 are the leds of each keyswitch. From left to right, top to bottom. These are equal to the numbers in the legends of the default keycaps. */
			case 0:
				PORTD |= (1<<7);
				break;
			case 1:
				if((PINB & (1 << 7)) != 0) {
					PORTC |= (1<<6);
				} else {
					PORTC |= (1<<7);
				}
				break;
			case 2:
				PORTD |= (1<<4);
				break;
			case 3:
				PORTE |= (1<<6);
				break;
			case 4:
				PORTB |= (1<<4);
				break;
			case 5:
				PORTD |= (1<<6);
				break;
				/* LED 6 to 8 are the three layer leds in front of the device from left to right. */
			case 6:
				PORTD &= ~(1<<5);
				break;
			case 7:
				PORTB |= (1<<6);
				break;
			case 8:
				PORTB &= ~(1<<0);
				break;
		}
	} else {
		switch(ledId) {
			case 0:
				PORTD &= ~(1<<7);
				break;
			case 1:
				if((PINB & (1 << 7)) != 0) {
					PORTC &= ~(1<<6);
				} else {
					PORTC &= ~(1<<7);
				}
				break;
			case 2:
				PORTD &= ~(1<<4);
				break;
			case 3:
				PORTE &= ~(1<<6);
				break;
			case 4:
				PORTB &= ~(1<<4);
				break;
			case 5:
				PORTD &= ~(1<<6);
				break;
			case 6:
				PORTD |= (1<<5);
				break;
			case 7:
				PORTB &= ~(1<<6);
				break;
			case 8:
				PORTB |= (1<<0);
				break;
		}
	}
}

void led_init_ports() {
	PORTB |= (1 << 7);
	DDRB &= ~(1<<7);
	
	DDRD |= (1<<7);
	DDRC |= (1<<6);
	DDRC |= (1<<7);
	DDRD |= (1<<4);
	DDRE |= (1<<6);
	DDRB |= (1<<4);
	DDRD |= (1<<6);

	DDRD |= (1<<5);
	DDRB |= (1<<6);
	DDRB |= (1<<0);
}

void led_set_layer(int layer) {

	/*KNOPS_SIMPLELED_STATES*/

}

void matrix_init_user(void) {
	led_init_ports();
	
	led_set_layer(1);
	
	/*KNOPS_INIT*/
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	//keyevent_t event = record->event;

	/*KNOPS_MACRO*/
	return NULL;
}


void matrix_scan_user(void) {
	/*KNOPS_SCAN*/
}

void led_set_user(uint8_t usb_led) {

	/*KNOPS_FUNCTIONALLED_STATES*/

}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  
	/*KNOPS_PROCESS_STATE*/

	return NULL;
  
}


