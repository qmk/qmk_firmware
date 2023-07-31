#include "2k.h"
#include "quantum.h"
#include "analog.h"
#include "rgbMatrix.h"
#include "eeprom.h"

key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};
pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS] = MATRIX_PINS;

#ifdef DEBUG_MATRIX
static uint8_t i = 0;
void housekeeping_task_user(void) {
    if (i == 0) {
        uprintf("Mode: %d AP: %d PS/RS: %d/%d    ",
                g_config.mode,
                g_config.actuation_point,
                g_config.press_sensitivity,
                g_config.release_sensitivity);
        uprintf("K1: V: %d O: %d  ", keys[0][0].value, keys[0][0].offset);
        uprintf("K2: V: %d O: %d  ", keys[0][1].value, keys[0][1].offset);
        uprintf("RAW %d %d\n", analogReadPin(matrix_pins[0][0]), analogReadPin(matrix_pins[0][1]));
    }
    i++;
}
#endif

via_config g_config = {
        .mode = 1,
        .actuation_point = 32,
        .press_sensitivity = 32,
        .release_sensitivity = 32,
        .press_hysteresis = 5,
        .release_hysteresis = 5,
};

void values_load(void) {
    eeprom_read_block(&g_config, ((void *) VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
}

void values_save(void) {
    eeprom_update_block(&g_config, ((void *) VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
}

void via_init_kb(void) {
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        values_load();
    } else {
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
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
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_mode:
            g_config.mode = *value_data;
            break;
        case id_actuation_point:
            g_config.actuation_point = *value_data;
            break;
        case id_press_sensitivity:
            g_config.press_sensitivity = *value_data;
            break;
        case id_release_sensitivity:
            g_config.release_sensitivity = *value_data;
            break;
        case id_press_hysteresis:
            g_config.press_hysteresis = *value_data;
            break;
        case id_release_hysteresis:
            g_config.release_hysteresis = *value_data;
            break;
    }
}

void via_config_get_value(uint8_t *data) {
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_mode:
            *value_data = g_config.mode;
            break;
        case id_actuation_point:
            *value_data = g_config.actuation_point;
            break;
        case id_press_sensitivity:
            *value_data = g_config.press_sensitivity;
            break;
        case id_release_sensitivity:
            *value_data = g_config.release_sensitivity;
            break;
        case id_press_hysteresis:
            *value_data = g_config.press_hysteresis;
            break;
        case id_release_hysteresis:
            *value_data = g_config.release_hysteresis;
            break;
    }
}