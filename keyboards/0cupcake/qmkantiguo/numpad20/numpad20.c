#include "numpad20.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	backlight_level(0);
	matrix_init_user();
}
