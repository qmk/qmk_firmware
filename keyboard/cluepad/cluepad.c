#include "cluepad.h"

__attribute__ ((weak))
void matrix_init_user(void) {
    // leave these blank
};

__attribute__ ((weak))
void matrix_scan_user(void) {
    // leave these blank
};

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    if (matrix_init_user) {
        (*matrix_init_user)();
    }

    #ifdef BACKLIGHT_ENABLE
        init_backlight_pin();
    #endif

    #ifdef RGBLIGHT_ENABLE
        rgblight_init();
    #endif

    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
};

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	if (matrix_scan_user) {
		(*matrix_scan_user)();
	}
};
