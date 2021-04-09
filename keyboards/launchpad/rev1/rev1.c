#include "launchpad.h"

void matrix_init_kb(void) {
	// Undo init of RX LED, we use that port currently
	//DDRB &= ~(1<<0);
	
	matrix_init_user();
	
};
