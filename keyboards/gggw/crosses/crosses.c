/*
This is the c library for EEPROM and other Crosses features.
You should not need to modify it as config comes from  config.h

Copyright 2024 Vincent Franco <me@vincentfranco.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "crosses.h"
#include "transactions.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif /* ifdef CONSOLE_ENABLE */

bool set_scrolling = false;

float scroll_acc_h = 0.0;
float scroll_acc_v = 0.0;

const uint16_t MIN_DEFAULT_DPI = 100;
const uint16_t MAX_DEFAULT_DPI = 10000;

/***********************************************************************
 * Pointer Stroage
 ***********************************************************************/

global_user_config_t global_user_config = {0};

void write_config_to_eeprom(global_user_config_t* config) {
    eeconfig_update_kb(config->raw);
}

uint16_t get_pointer_dpi(global_user_config_t* config) {
    uint16_t current = config->mse_cpi;

    if (current < MIN_DEFAULT_DPI) {
        return MIN_DEFAULT_DPI;
    }

    if (current > MAX_DEFAULT_DPI) {
        return MAX_DEFAULT_DPI;
    }

    return current;
}

void update_pointer_cpi(global_user_config_t* config) {
#ifdef POINTING_DEVICE_COMBINED
    pointing_device_set_cpi_on_side(true, 1000);
    pointing_device_set_cpi_on_side(false, get_pointer_dpi(config));
#endif /* ifdef POINTING_DEVICE_COMBINED */

#if defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT)
    pointing_device_set_cpi(get_pointer_dpi(config));
#endif /* LEFT || RIGHT */
}

void change_pointer_dpi(global_user_config_t* config, bool inc) {
    uint16_t current   = config->mse_cpi;
    uint16_t requested = current += inc ? 50 : -50;

    if (requested < MIN_DEFAULT_DPI) {
#ifdef CONSOLE_ENABLE
        dprintf("%u is beyond bounds - omitting operation", requested);
#endif // CONSOLE_ENABLE
        return;
    }

    if (requested > MAX_DEFAULT_DPI) {
#ifdef CONSOLE_ENABLE
        dprintf("%u is beyond bounds - omitting operation", requested);
#endif // CONSOLE_ENABLE
        return;
    }

    config->mse_cpi = requested;

#ifdef POINTING_DEVICE_COMBINED
    pointing_device_set_cpi_on_side(false, get_pointer_dpi(config));
#endif /* ifdef POINTING_DEVICE_COMBINED */

#if defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT)
    pointing_device_set_cpi(get_pointer_dpi(config));
#endif /* ifdef POINTING_DEVICE_* */

    write_config_to_eeprom(&global_user_config);
}

void debug_config_to_console(global_user_config_t* config) {
#ifdef CONSOLE_ENABLE
    dprintf("(crosses) process_record_user: config = {\n"
            "\traw = 0x%lu,\n"
            "\t{\n"
            "\t\tmse_cpi=0x%X (%u)\n"
            "\t}\n"
            "}\n",
            (unsigned long)config->raw, config->mse_cpi, get_pointer_dpi(config));
#endif // CONSOLE_ENABLE
}

void eeconfig_init_kb(void) {
    global_user_config.raw     = 0;
    global_user_config.mse_cpi = MIN_DEFAULT_DPI;

    write_config_to_eeprom(&global_user_config);
    debug_config_to_console(&global_user_config);

    eeconfig_init_user();
}

/***********************************************************************
 * Single Trackball Config
 ***********************************************************************/

#if defined(POINTING_DEVICE_RIGHT) || defined(POINTING_DEVICE_LEFT)

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_acc_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_acc_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int16_t)scroll_acc_h;
        mouse_report.v = (int16_t)scroll_acc_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_acc_h -= (int16_t)scroll_acc_h;
        scroll_acc_v -= (int16_t)scroll_acc_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return pointing_device_task_user(mouse_report);
}

#endif /* RIGHT || LEFT */

/***********************************************************************
 * Dual Trackball Config
 ***********************************************************************/

#ifdef POINTING_DEVICE_COMBINED

report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    // Calculate and accumulate scroll values based on mouse movement and divisors
    scroll_acc_h += (float)left_report.x / SCROLL_DIVISOR_H;
    scroll_acc_v += (float)left_report.y / SCROLL_DIVISOR_V;

    // Assign integer parts of accumulated scroll values to the mouse report
    left_report.h = (int16_t)scroll_acc_h;
    left_report.v = (int16_t)scroll_acc_v;

    // Update accumulated scroll values by subtracting the integer parts
    scroll_acc_h -= (int16_t)scroll_acc_h;
    scroll_acc_v -= (int16_t)scroll_acc_v;

    // Clear the X and Y values of the mouse report
    left_report.x = 0;
    left_report.y = 0;

    return pointing_device_combine_reports(left_report, right_report);
}

#endif /* ifdef POINTING_DEVICE_COMBINED */

layer_state_t layer_state_set_kb(layer_state_t state) {
#if defined(POINTING_DEVICE_RIGHT) || defined(POINTING_DEVICE_LEFT)
    if (get_highest_layer(state) != 5) {
        set_scrolling = false;
    }
#endif /* ifndef POINTING_DEVICE_* */

    return layer_state_set_user(state);
}

void secondary_sync_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    if (in_buflen == sizeof(global_user_config)) {
        memcpy(&global_user_config, in_data, sizeof(global_user_config));
    }
}

void housekeeping_task_kb(void) {
    if (!is_keyboard_master()) {
        return;
    }

    static global_user_config_t last_config = {0};
    static uint32_t             last_sync   = 0;
    bool                        should_sync = false;

    if (memcmp(&global_user_config, &last_config, sizeof(global_user_config))) {
        should_sync = true;
        memcpy(&last_config, &global_user_config, sizeof(global_user_config));
    }

    should_sync = (timer_elapsed32(last_sync) > 500);

    if (!should_sync) {
        return;
    }

    if (transaction_rpc_send(CROSSES_SECONDARY_SYNC_ID, sizeof(global_user_config), &global_user_config)) {
        last_sync = timer_read32();
    }
}

void keyboard_post_init_kb(void) {
    global_user_config.raw = eeconfig_read_kb();
    transaction_register_rpc(CROSSES_SECONDARY_SYNC_ID, secondary_sync_handler);

#if defined(POINTING_DEVICE_COMBINED) || defined(POINTING_DEVICE_RIGHT) || defined(POINTING_DEVICE_LEFT)
    update_pointer_cpi(&global_user_config);
#endif /* ifdef POINTING_DEVICE_* */

    write_config_to_eeprom(&global_user_config);

    keyboard_post_init_user();
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }

    return rotation;
}

#    if defined(POINTING_DEVICE_COMBINED) || defined(POINTING_DEVICE_RIGHT) || defined(POINTING_DEVICE_LEFT)
void pointing_device_init_kb(void) {
    set_auto_mouse_layer(_MOUS);
    set_auto_mouse_enable(false);
}
#    endif /* ifdef POINTING_DEVICE */

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

bool oled_task_kb(void) {
    render_logo();

    // clang-format off
    const char* layer_names[] = {
        [0] = "BASE  CPI: ",
        [1] = "PROG  CPI: ",
        [2] = "NAVI  CPI: ",
        [3] = "MEDIA CPI: ",
        [4] = "FUNC  CPI: ",
        [5] = "MOUSE CPI: ",
    };
    // clang-format on

    char     cpi_str[6];
    uint16_t current_dpi = get_pointer_dpi(&global_user_config);

    snprintf(cpi_str, sizeof(cpi_str), "%u", (unsigned int)current_dpi);

    oled_write(PSTR(layer_names[get_highest_layer(layer_state)]), false);
    oled_write(cpi_str, false);

    return false;
}
#endif /* ifdef OLED_ENABLE */
