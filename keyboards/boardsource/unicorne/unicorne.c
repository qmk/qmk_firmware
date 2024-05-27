// Copyright 2023 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "unicorne.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
#    ifdef MASTER_RIGHT
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    else
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    endif
    return rotation;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return true;
}

uint16_t timer            = 0;
uint8_t  downtaunt_toggle = 0;

bool oled_task_kb() {
    if (!oled_task_user()) {
        return false;
    }
    if (!is_keyboard_left()) {
        oled_write_raw(logo, sizeof(logo));
        return false;
    }

    const uint16_t TOGGLE_GAP_MS = 1000;
    if (timer_elapsed(timer) > TOGGLE_GAP_MS) {
        // Reset timer.
        timer = timer_read();
        downtaunt_toggle ^= 1;
    }

    const uint16_t DOWNTAUNT_WAIT_MS = 10000;
    if (last_matrix_activity_elapsed() > DOWNTAUNT_WAIT_MS) {
        write_downtaunt_anim();
    } else {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_raw(gw_idle, sizeof(gw_idle));
                break;
            case 1:
                oled_write_raw(gw_diver, sizeof(gw_diver));
                break;
            case 2:
                oled_write_raw(gw_parachute, sizeof(gw_parachute));
                break;
            case 3:
                oled_write_raw(gw_key, sizeof(gw_key));
                break;
        }
    }

    return false;
}

void write_downtaunt_anim(void) {
    if (downtaunt_toggle) {
        oled_write_raw(gw_downtaunt_f1, sizeof(gw_idle));
    } else {
        oled_write_raw(gw_downtaunt_f2, sizeof(gw_idle));
    }
}

#endif
