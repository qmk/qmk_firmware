#include "clueboard1.h"

__attribute__ ((weak))
void matrix_init_user(void) {
	// leave these blank
}

__attribute__ ((weak))
void matrix_scan_user(void) {
	// leave these blank
}

void matrix_init_kb(void) {
	#ifdef RGBLIGHT_ENABLE
		rgblight_init();
	#endif

	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}
