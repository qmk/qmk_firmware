#include "atreus.h"

__attribute__ ((weak))
void * matrix_init_user(void) {
	// leave these blank
};

__attribute__ ((weak))
void * matrix_scan_user(void) {
	// leave these blank
};

void * matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	if (matrix_init_user) {
		(*matrix_init_user)();
	}
};

void * matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	if (matrix_scan_user) {
		(*matrix_scan_user)();
	}
};
