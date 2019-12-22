#include "kunai16.h"

__attribute__ ((weak))
void matrix_init_kb(void) {
	matrix_init_user();
}
