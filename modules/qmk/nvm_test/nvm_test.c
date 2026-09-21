// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include "community_modules.h"
#include "debug.h"
#include "timer.h"
#include "eeconfig.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 1, 3);

typedef struct my_config_t {
    uint32_t data;
} my_config_t;

static my_config_t config;

// Helpers required to bind to debounce helper
void eeconfig_read_my_config(my_config_t *value) {
    eeconfig_read_nvm_test_datablock(value, 0, sizeof(my_config_t));
}
void eeconfig_update_my_config(my_config_t *value) {
    eeconfig_update_nvm_test_datablock(value, 0, sizeof(my_config_t));
}

EECONFIG_DEBOUNCE_HELPER(my_config, config);

void eeconfig_init_nvm_test_datablock(void) {
    my_config_t default_config = {
        .data = 42,
    };
    eeconfig_update_nvm_test_datablock(&default_config, 0, sizeof(my_config_t));
}

void keyboard_post_init_nvm_test(void) {
    eeconfig_init_my_config();
}

bool process_record_nvm_test(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        config.data += 1;
        eeconfig_flag_my_config(true);
    }

    return true;
}

void housekeeping_task_nvm_test(void) {
    eeconfig_flush_my_config(false);

    static uint32_t last_sync = 0;
    if (timer_elapsed32(last_sync) > 1000) {
        last_sync = timer_read32();

        dprintf("Config: %ld\n", config.data);
    }
}
