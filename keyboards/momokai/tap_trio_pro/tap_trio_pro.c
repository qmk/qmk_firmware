/* Copyright 2023 RephlexZero (@RephlexZero)
             2023 peepeetee (@peepeetee)
             2025 Jenna Fligor (@Ex-32)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tap_trio_pro.h"
#include "quantum.h"
#include "analog.h"
#include "eeprom.h"
#include "scanfunctions.h"
#include "print.h"


analog_config g_config = {
    .mode = dynamic_actuation,
    .actuation_point = 32,
    .press_sensitivity = 32,
    .release_sensitivity = 32,
    .press_hysteresis = 5,
    .release_hysteresis = 5
};

#ifdef BOOTMAGIC_ENABLE
extern pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS];
void         bootmagic_lite(void) {
    if (analogReadPin(matrix_pins[BOOTMAGIC_ROW][BOOTMAGIC_COLUMN]) < 1350) {
        bootloader_jump();
    }
}
#endif

#ifdef DEFERRED_EXEC_ENABLE

#    ifdef DEBUG_ENABLE
deferred_token debug_token;
bool           debug_print(void) {
    // uint8_t hall_effect_rows = 1;
    // char buffer[hall_effect_rows * MATRIX_COLS * 5 + MATRIX_ROWS * 2];
    // buffer[0] = '\0';

    // // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //     uint8_t row = 1;
    //     for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    //         hybrid_key_t *key = &keys[row][col];
    //         char   temp[6];
    //         snprintf(temp, sizeof(temp), "%5u", key->value);
    //         strcat(buffer, temp);
    //     }
    //      strcat(buffer, "\n");
    // // }

    // uprintf("%s", buffer);

    int raw_analog_value[3];
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {

        raw_analog_value[col] = analogReadPin(matrix_pins[0][col]);
    }
    printf("raw_analog_value = %d, %d, %d\n", raw_analog_value[0], raw_analog_value[1], raw_analog_value[2]);

    return true;
}

uint32_t debug_print_callback(uint32_t trigger_time, void *cb_arg) {
    debug_print();
    return 25;
}
#    endif

deferred_token idle_recalibrate_token;
bool           process_record_kb(uint16_t keycode, keyrecord_t *record) {
    extend_deferred_exec(idle_recalibrate_token, 300000);
    return true;
}

uint32_t idle_recalibrate_callback(uint32_t trigger_time, void *cb_arg) {
    get_sensor_offsets();
    return 10000;
}
#endif

void values_load(void) {
    eeconfig_read_kb_datablock(&g_config, 0, EECONFIG_KB_DATA_SIZE);
}

void values_save(void) {
    eeconfig_update_kb_datablock(&g_config, 0, EECONFIG_KB_DATA_SIZE);
}

void eeconfig_init_kb() {
    values_save();
}

void keyboard_post_init_kb(void) {
#ifdef DEFERRED_EXEC_ENABLE
#    ifdef DEBUG_ENABLE
    debug_token = defer_exec(1000, debug_print_callback, NULL);
#    endif
    idle_recalibrate_token = defer_exec(300000, idle_recalibrate_callback, NULL);
#endif
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
    id_actuation_point = 2,
    id_press_sensitivity = 3,
    id_release_sensitivity = 4,
    id_press_hysteresis = 5,
    id_release_hysteresis = 6,
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



