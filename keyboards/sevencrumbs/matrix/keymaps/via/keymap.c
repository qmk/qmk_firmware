// Copyright 2023 Chris H <chris@zoid.com.au>
// SPDX-License-Identifier: GPL-3.0-only

#include QMK_KEYBOARD_H
#include "eeprom.h"
#include "color.h"
#include "rgb_matrix_direct.h"

typedef struct {
	uint8_t hue;
	uint8_t saturation;
} color_t;

typedef struct {
	uint8_t brightness;
	color_t color[RGB_MATRIX_LED_COUNT];
} config_t;

static_assert(VIA_EEPROM_CUSTOM_CONFIG_SIZE == sizeof(config_t), "VIA EEPROM custom configuration size must match configuration size");

enum values {
	brightness = 1,
	color = 2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT(
		KC_1, KC_2,
		KC_3, KC_4
	)
};

static bool initialized;
static bool suspended;
static config_t config = {.brightness = 255};

static void save(void) {
	eeprom_update_block(&config, (void*) VIA_EEPROM_CUSTOM_CONFIG_ADDR, VIA_EEPROM_CUSTOM_CONFIG_SIZE);
}

static void update(void) {
	if (!initialized) {
		rgb_matrix_direct_init();
		eeprom_read_block(&config, (void*) VIA_EEPROM_CUSTOM_CONFIG_ADDR, VIA_EEPROM_CUSTOM_CONFIG_SIZE);
		initialized = true;
	}

	if (suspended) {
		rgb_matrix_direct_set_color_all(0, 0, 0);
	} else {
		HSV color_hsv = {.v = config.brightness};

		for (int index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
			color_t color_hs = config.color[index];

			color_hsv.h = color_hs.hue;
			color_hsv.s = color_hs.saturation;

			RGB color_rgb = hsv_to_rgb(color_hsv);

			rgb_matrix_direct_set_color(index, color_rgb.r, color_rgb.g, color_rgb.b);
		}
	}

	rgb_matrix_direct_flush();
}

void eeconfig_init_user(void) {
	save();
}

void suspend_power_down_user(void) {
	suspended = true;
	update();
}

void suspend_wakeup_init_user(void) {
	suspended = false;
	update();
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
	uint8_t command = data[0];

	if (data[1] == id_custom_channel) {
		if (command == id_custom_save) {
			save();
			return;
		}

		if (data[2] == brightness) {
			if (command == id_custom_set_value) {
				config.brightness = data[3];
				update();
				return;
			}

			if (command == id_custom_get_value) {
				data[3] = config.brightness;
				return;
			}
		}

		if (data[2] == color) {
			uint8_t index = data[3];

			if (index < RGB_MATRIX_LED_COUNT) {
				color_t *color = config.color + index;

				if (command == id_custom_set_value) {
					color->hue = data[4];
					color->saturation = data[5];
					update();
					return;
				}

				if (command == id_custom_get_value) {
					data[4] = color->hue;
					data[5] = color->saturation;
					return;
				}
			}
		}
	}

	data[0] = id_unhandled;
}
