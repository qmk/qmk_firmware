#include "atomic.h"

__attribute__ ((weak))
void matrix_init_user(void) {
	// leave these blank
}

__attribute__ ((weak))
void matrix_scan_user(void) {
	// leave these blank
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

#ifdef BACKLIGHT_ENABLE
    backlight_init_ports();
#endif

    // Turn status LED on
    DDRE |= (1<<6);
    PORTE |= (1<<6);

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}