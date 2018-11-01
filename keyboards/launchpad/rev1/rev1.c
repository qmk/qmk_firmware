#include "launchpad.h"

void matrix_init_kb(void) {
	
	// JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
	
	// Undo init of RX LED, we use that port currently
	//DDRB &= ~(1<<0);
	
	matrix_init_user();
	
};