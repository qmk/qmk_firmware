// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "n8x.h"
#include "quantum.h"
#include "eeprom.h"
#include "backlight.h"

my_config_t g_my_config;
backlight_config_t backlight_config;

static bool countstart = false;
static uint32_t blink_timer = 0;

static void read_my_config_from_eeprom(my_config_t* config) {
    config->raw = eeconfig_read_kb() & 0xffffff;
}

static void write_my_config_to_eeprom(my_config_t* config) {
    eeconfig_update_kb(config->raw);
}

void matrix_init_kb(void) {
	read_my_config_from_eeprom(&g_my_config);
    breathing_period_set(g_my_config.breathing_period);
    matrix_init_user();
}

void eeconfig_init_kb(void) {
    g_my_config.raw = 0;
    g_my_config.breathing_period = 5;
    g_my_config.blink_value = 0;
    g_my_config.blink_speed = 3;
    write_my_config_to_eeprom(&g_my_config);
    eeconfig_init_user();
}

void housekeeping_task_kb(void){
	if (countstart) {
		if (timer_elapsed32(blink_timer) > (g_my_config.blink_speed * 20)) {
            if (g_my_config.blink_value == 1) {
                backlight_set(backlight_config.level);
            } else if (g_my_config.blink_value == 2) {
                backlight_set(0);
            }
			countstart = false;
		}
	}
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (g_my_config.blink_value) {
            case 1:
                if (!countstart) {
                    blink_timer = timer_read32();
                    backlight_set(0);
                    countstart = true;
                }
                break;
            case 2:
                if (!countstart) {
                    blink_timer = timer_read32();
                    backlight_set(backlight_config.level);
                    countstart = true;
                }
                break;
        }
        switch(keycode) {
            case BR_UP:
                if (g_my_config.breathing_period < 10) {
                    g_my_config.breathing_period++;
                }
                breathing_period_set(g_my_config.breathing_period);
                write_my_config_to_eeprom(&g_my_config);
                return false;
            case BR_DOWN:
                if (g_my_config.breathing_period > 1) {
                    g_my_config.breathing_period--;
                }
                breathing_period_set(g_my_config.breathing_period);
                write_my_config_to_eeprom(&g_my_config);
                return false;
            case BK_OUT:
                g_my_config.blink_value = (g_my_config.blink_value == 1) ? 0 : 1;
                write_my_config_to_eeprom(&g_my_config);
                return false;
            case BK_IN:
                g_my_config.blink_value = (g_my_config.blink_value == 2) ? 0 : 2;
                write_my_config_to_eeprom(&g_my_config);
                return false;
            case BK_UP:
                if (g_my_config.blink_speed < 10) {
                    g_my_config.blink_speed++;
                }
                write_my_config_to_eeprom(&g_my_config);
                return false;
            case BK_DOWN:
                if (g_my_config.blink_speed > 1) {
                    g_my_config.blink_speed--;
                }
                write_my_config_to_eeprom(&g_my_config);
                return false;
        }
    }
    return process_record_user(keycode, record);
}