// Copyright 2023 Chris H <chris@zoid.com.au>
// SPDX-License-Identifier: GPL-3.0-only

#include "quantum.h"
#include "rgb_matrix_direct.h"

#define COMPONENT_COUNT 3
#define CHANNEL_COUNT (RGB_MATRIX_LED_COUNT * COMPONENT_COUNT)
#define CHANNEL_OFFSET (MATRIX_COLS * MATRIX_ROWS)

static PWMDriver *drivers[] = {&PWMD2, &PWMD3, &PWMD4, &PWMD5, &PWMD6, &PWMD7};
static uint8_t buffer[CHANNEL_COUNT];

void rgb_matrix_direct_init(void) {
	PWMConfig config = {
		.frequency = 2000 * 255, // Ensure this is never below the system clock divided by 256
		.period = 254, // Must be set to 1 less than the maximum value for toggle-free output at 100%
		.channels = {
			{.mode = PWM_OUTPUT_ACTIVE_HIGH},
			{.mode = PWM_OUTPUT_ACTIVE_HIGH}
		}
	};

	for (int channel = 0; channel < CHANNEL_COUNT; channel++) {
		PWMDriver *driver = drivers[channel >> 1];
		int output = channel & 1;

		if (output == 0) {
			pwmStart(driver, &config);
		}

		pwmEnableChannel(driver, output, 0);
		palSetPadMode(0, channel + CHANNEL_OFFSET, PAL_MODE_ALTERNATE_PWM);
	}
}

void rgb_matrix_direct_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
	index *= COMPONENT_COUNT;

	buffer[index] = red;
	buffer[index + 1] = green;
	buffer[index + 2] = blue;
}

void rgb_matrix_direct_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
	for (int index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
		rgb_matrix_direct_set_color(index, red, green, blue);
	}
}

void rgb_matrix_direct_flush(void) {
	for (int channel = 0; channel < CHANNEL_COUNT; channel++) {
		PWMDriver *driver = drivers[channel >> 1];
		pwmEnableChannel(driver, channel & 1, buffer[channel]);
	}
}
