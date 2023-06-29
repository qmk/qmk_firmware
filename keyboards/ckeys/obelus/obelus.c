#include "quantum.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	// Turn status LED on
	DDRD |= (1<<6);
	PORTD |= (1<<6);

	matrix_init_user();
}
