/* Copyright 2023 RephlexZero (@RephlexZero) peepeetee (@peepeetee)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>
#include "tap_trio_pro.h"
#include "quantum.h"
#include "analog.h"
#include "eeprom.h"
#include "scanfunctions.h"

analog_config g_config = {
    .mode = dynamic_actuation,
    .actuation_point = 32,
    .press_sensitivity = 32,
    .release_sensitivity = 32,
    .press_hysteresis = 0,
    .release_hysteresis = 5
};

extern pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS];
void         bootmagic_lite(void) {
    if (analogReadPin(matrix_pins[BOOTMAGIC_LITE_ROW][BOOTMAGIC_LITE_COLUMN]) < 1350) {
        bootloader_jump();
    }
}

uint32_t idle_recalibrate_callback(uint32_t trigger_time, void *cb_arg) {
    get_sensor_offsets();
    return 10000;
}

deferred_token idle_recalibrate_token;
bool           process_record_kb(uint16_t keycode, keyrecord_t *record) {
    extend_deferred_exec(idle_recalibrate_token, 300000);
    return true;
}

#ifdef DEBUG_ENABLE
static uint8_t i = 0;
void           housekeeping_task_kb(void) {
    if (i == 0) {
        char formattedString[200]; // Adjust the buffer size as needed

        snprintf(formattedString, sizeof(formattedString), "Mode: %d Actuation Point: %d Press/Release Sensitivity: %d/%d\n", g_config.mode, g_config.actuation_point, g_config.press_sensitivity, g_config.release_sensitivity);

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                snprintf(formattedString + strlen(formattedString), sizeof(formattedString) - strlen(formattedString), "%d/%d/%d ", keys[row][col].value, keys[row][col].extremum, analogReadPin(matrix_pins[row][col]));
            }
            strcat(formattedString, "\n\n");
        }

        uprintf("%s", formattedString);
    }
    i++;
}
#endif

void values_load(void) {
    eeconfig_read_kb_datablock(&g_config);
}

void values_save(void) {
    eeconfig_update_kb_datablock(&g_config);
}

void          eeconfig_init_kb() {
    values_save();
}

void keyboard_post_init_kb(void) {
    idle_recalibrate_token = defer_exec(300000, idle_recalibrate_callback, NULL);
    values_load();
}

#ifdef VIA_ENABLE
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    /* data = [ command_id, channel_id, value_id, value_data ] */
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                values_save();
                break;
            }
            default: {
                /* Unhandled message */
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    /* Return the unhandled state */
    *command_id = id_unhandled;

    /* DO NOT call raw_hid_send(data,length) here, let caller do this */
}

enum via_dynamic_actuation {
    id_mode = 1,
    id_actuation_point,
    id_press_sensitivity,
    id_release_sensitivity,
    id_press_hysteresis,
    id_release_hysteresis,
};

void via_config_set_value(uint8_t *data) {
    /* data = [ value_id, value_data ] */
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_mode:
            g_config.mode = *value_data;
            break;
        case id_actuation_point:
            g_config.actuation_point = *value_data * 255 / 40;
            break;
        case id_press_sensitivity:
            g_config.press_sensitivity = *value_data * 255 / 40;
            break;
        case id_release_sensitivity:
            g_config.release_sensitivity = *value_data * 255 / 40;
            break;
        case id_press_hysteresis:
            g_config.press_hysteresis = *value_data * 255 / 40;
            break;
        case id_release_hysteresis:
            g_config.release_hysteresis = *value_data * 255 / 40;
            break;
    }
}

void via_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_mode:
            *value_data = g_config.mode;
            break;
        case id_actuation_point:
            *value_data = g_config.actuation_point * 40 / 255;
            break;
        case id_press_sensitivity:
            *value_data = g_config.press_sensitivity * 40 / 255;
            break;
        case id_release_sensitivity:
            *value_data = g_config.release_sensitivity * 40 / 255;
            break;
        case id_press_hysteresis:
            *value_data = g_config.press_hysteresis * 40 / 255;
            break;
        case id_release_hysteresis:
            *value_data = g_config.release_hysteresis * 40 / 255;
            break;
    }
}
#endif


