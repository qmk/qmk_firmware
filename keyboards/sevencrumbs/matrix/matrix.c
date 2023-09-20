// Copyright 2023 Chris H <chris@zoid.com.au>
// SPDX-License-Identifier: GPL-3.0-only

#include "quantum.h"
#include "rgb_matrix_direct.h"

void bootmagic_lite(void) {
	matrix_scan();
	wait_ms(10); // Must be equal or greater than the debounce time
	matrix_scan();

	if (matrix_get_row(0) == 3 && matrix_get_row(1) == 3) {
		eeconfig_disable();
		bootloader_jump();
	}
}

#ifdef RGB_MATRIX_ENABLE

const rgb_matrix_driver_t rgb_matrix_driver = {
	.init = rgb_matrix_direct_init,
	.set_color = rgb_matrix_direct_set_color,
	.set_color_all = rgb_matrix_direct_set_color_all,
	.flush = rgb_matrix_direct_flush
};

#endif
