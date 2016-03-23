#include "jd45.h"

__attribute__ ((weak))
void matrix_init_user(void) {

};

__attribute__ ((weak))
void matrix_scan_user(void) {

};

void matrix_init_kb(void) {
	#ifdef BACKLIGHT_ENABLE
    	backlight_init_ports();
	#endif

	if (matrix_init_user) {
		(*matrix_init_user)();
	}
};

void matrix_scan_kb(void) {
	if (matrix_scan_user) {
		(*matrix_scan_user)();
	}
};
