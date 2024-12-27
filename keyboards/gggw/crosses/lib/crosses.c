
#include "crosses.h"

bool set_scrolling = false;

float scroll_acc_h = 0.0;
float scroll_acc_v = 0.0;

const uint16_t MIN_DEFAULT_DPI = 400;
const uint16_t MAX_DEFAULT_DPI = 10000;


/*
 * Pointer Storage
 */

global_user_config_t global_user_config = {0};

void write_config_to_eeprom(global_user_config_t* config) {
    eeconfig_update_user(config->raw);
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
    pointing_device_set_cpi(get_pointer_dpi(config));
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

    config->mse_cpi += inc ? 10 : -10;
    pointing_device_set_cpi(get_pointer_dpi(config));
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

void eeconfig_init_user(void) {
    global_user_config.raw     = 0;
    global_user_config.mse_cpi = MIN_DEFAULT_DPI;

    write_config_to_eeprom(&global_user_config);
    debug_config_to_console(&global_user_config);
}

/*
 * Pointing Device Config
 */

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_acc_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_acc_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_acc_h;
        mouse_report.v = (int8_t)scroll_acc_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_acc_h -= (int8_t)scroll_acc_h;
        scroll_acc_v -= (int8_t)scroll_acc_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) != 5) {
        set_scrolling = false;
    }

    return state;
}

