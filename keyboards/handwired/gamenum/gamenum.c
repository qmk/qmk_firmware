#include "quantum.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	DDRC |= (1<<6);
	PORTC &= ~(1<<6);
	
	DDRD |= (1<<4);
	PORTD &= ~(1<<4);
	
	matrix_init_user();
	
}
