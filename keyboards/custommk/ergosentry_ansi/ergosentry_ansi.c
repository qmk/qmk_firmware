// Copyright 2025 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include "ergosentry_ansi.h"

typedef union {
    uint32_t raw;
    struct {
        bool usb_audio_enabled;
    };
} keyboard_config_t;

keyboard_config_t keyboard_config;

void update_kb_eeprom(void) {
    eeconfig_update_kb(keyboard_config.raw);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    process_record_cmk_cm6646(keycode, record);
    return process_record_user(keycode, record);
}

void keyboard_post_init_kb(void) {
    keyboard_config.raw = eeconfig_read_kb();
    cmk_cmk6646_init(keyboard_config.usb_audio_enabled);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    bool usb_audio_enabled;
    usb_audio_enabled = cmk_cmk6646_housekeeping_task();
    if (usb_audio_enabled != keyboard_config.usb_audio_enabled) {
        keyboard_config.usb_audio_enabled = usb_audio_enabled;
        update_kb_eeprom();
    }
}

void eeconfig_init_kb(void) {
    //enable nkro by default (not forced)
    keymap_config.raw = eeconfig_read_keymap();
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);

    //enable USB audio by default (not forced)
    keyboard_config.raw = eeconfig_read_kb();
    keyboard_config.usb_audio_enabled = 1;
    eeconfig_update_kb(keyboard_config.raw);

    eeconfig_init_user();
}
