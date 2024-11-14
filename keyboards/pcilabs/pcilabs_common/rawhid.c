#include "rawhid.h"
#include "pcilabs_common.h"
#include "analogkeys.h"
#include "scanfunctions.h"
#include "quantum.h"
#include <stdint.h>
#include <string.h>
#include "config.h"
#include "color.h"
#include "rgb_matrix.h"
#include "raw_hid.h"

void raw_hid_send_rgb_settings(void){
    uint8_t data[32] = {0};
    data[0] = RECIEVE_RGB_SETTINGS;
    data[1] = rgb_matrix_get_hue();
    data[2] = rgb_matrix_get_sat();
    data[3] = rgb_matrix_get_val();
    data[4] = rgb_matrix_get_mode();
    data[5] = rgb_matrix_get_speed();
    raw_hid_send(data, 32);
}

void raw_hid_send_key_rebinds(void){
    /* new rebind structure: id, [layer, row, col, keycode], ..., 69 {finish marker} */
    // /* new rebind structure: id, [layer, row, col, keycode_low, keycode_high], ..., 69 {finish marker} */
    uint8_t data[32] = {0};
    data[0] = RECIEVE_KEY_REBIND;
    uint8_t data_idx = 1;
    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++){
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t keycode = dynamic_keymap_get_keycode(layer, row, col); // TODO: make it 16 bit when software will be ready
                // uint16_t keycode = dynamic_keymap_get_keycode(layer, row, col);
                // uint8_t keycode_low  = keycode & 255;
                // uint8_t keycode_high = keycode >> 8;
                if(data_idx + 4 >= 31) {
                // if(data_idx + 5 >= 31) {
                    data[data_idx] = 69;
                    raw_hid_send(data, 32);
                    data_idx = 1;
                    memset(&data[1], 0, 31);
                }
                uint8_t rebind[4] = {layer, row, col, keycode};
                // uint8_t rebind[5] = {layer, row, col, keycode_low, keycode_high};
                memcpy(&data[data_idx], rebind, 4);
                data_idx += 4;
                // memcpy(&data[data_idx], rebind, 5);
                // data_idx += 5;
            }
        }
    }
    if(data[data_idx] != 0){
        data[data_idx + 1] = 69;
        raw_hid_send(data, 32);
    }
}

void raw_hid_send_key_config(uint8_t row_num, uint16_t row_val, key_config_t* key_config){
    /* new report structure:
        id, row_num, row_low, row_high, switch_type, mode,
        actuation_point_low, actuation_point_high, press_sensitivity,
        release_sensitivity, press_hysteresis, release_hysteresis
    */
    uint8_t data[32] = {0};
    data[0] = RECIEVE_KEY_CONFIG;
    data[1] = row_num;
    data[2] = (uint8_t) row_val & 255;
    data[3] = (uint8_t) row_val >> 8;
    memcpy(&data[4], key_config, EECONFIG_KEY_DATA_SIZE);
    raw_hid_send(data, 32);
}

void raw_hid_send_all_key_configs(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++){
        key_config_t unique_configs[MATRIX_COLS];
        uint8_t unique_count = 0;

        for (key_config_t* key_config_ptr = (key_config_t*)&keys[row][0].config_raw; key_config_ptr <= (key_config_t*)&keys[row][MATRIX_COLS - 1].config_raw; key_config_ptr++) {
            bool is_unique = true;
            for (uint8_t i = 0; i < unique_count; i++){
                if (memcmp(key_config_ptr, &unique_configs[i], EECONFIG_KEY_DATA_SIZE) == 0){
                    is_unique = false;
                    break;
                }
            }
            if (is_unique == true){
                unique_configs[unique_count] = *key_config_ptr;
                unique_count++;
            }
        }

        for (key_config_t* key_config_ptr = &unique_configs[0]; key_config_ptr <= &unique_configs[unique_count - 1]; key_config_ptr++){
            uint16_t row_val = 0;
            for (uint8_t col = 0; col < MATRIX_COLS; col++){
                if (memcmp(key_config_ptr, &keys[row][col].config_raw, EECONFIG_KEY_DATA_SIZE) == 0) {
                    row_val |= 1 << col;
                }
            }
            raw_hid_send_key_config(row, row_val, key_config_ptr);
        }
    }
}

void raw_hid_send_debug_key_state(uint8_t row, uint8_t col, uint16_t raw, uint16_t value, bool state){
    /* debug report structure: id, row, col, raw_low, raw_high, value_low, value_high, state */
    uint8_t data[32];
    data[0] = SEND_DEBUG_KEY_STATE;
    data[1] = row;
    data[2] = col;
    data[3] = (uint8_t) raw & 255;
    data[4] = (uint8_t) raw >> 8;
    data[5] = (uint8_t) value & 255;
    data[6] = (uint8_t) value >> 8;
    data[7] = state;
    raw_hid_send(data, 32);
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    report_id_t report_id = data[0];
    switch (report_id) {
        case SEND_KEYBOARD_DATA:;
            break;
        case RECIEVE_RGB_SETTINGS:;
            uint8_t hue   = data[1];
            uint8_t sat   = data[2];
            uint8_t val   = data[3];
            uint8_t mode  = data[4];
            uint8_t speed = data[5];
            rgb_matrix_sethsv(hue, sat, val);
            rgb_matrix_mode(mode);
            rgb_matrix_set_speed(speed);
            break;
        case RECIEVE_KEY_CONFIG:;
            /* new report structure:
                id, row_num, row_low, row_high, switch_type, mode,
                actuation_point_low, actuation_point_high, press_sensitivity,
                release_sensitivity, press_hysteresis, release_hysteresis
            */
            uint8_t      row         = data[1];
            uint16_t     row_val     = (uint16_t)data[2] | (uint16_t)data[3] << 8;
            key_config_t new_config  = {
                .switch_type         = data[4],
                .mode                = data[5],
                .actuation_point     = (uint16_t)data[6] | (uint16_t)data[7] << 8,
                .press_sensitivity   = data[8],
                .release_sensitivity = data[9],
                .press_hysteresis    = data[10],
                .release_hysteresis  = data[11]
            };
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if ((row_val >> col) & 1) {
                    memcpy(keys[row][col].config_raw, new_config.config_raw, EECONFIG_KEY_DATA_SIZE);
                }
            }
            lut_init();
            values_save();
            get_sensor_offsets();
            break;
        case RECIEVE_KEY_REBIND:;
            /* new rebind structure: id, [layer, row, col, keycode], ..., 69 {finish marker} */
            // /* new rebind structure: id, [layer, row, col, keycode_low, keycode_high], ..., 69 {finish marker} */
            for (int i = 1; i < length && data[i] != 69; i+=5) {
                uint8_t  layer   = data[i];
                uint8_t  row     = data[i + 1];
                uint8_t  col     = data[i + 2];
                //uint16_t keycode = data[i + 3];
                uint16_t keycode = (uint16_t)data[i + 3] | (uint16_t)data[i + 4] << 8;
                dynamic_keymap_set_keycode(layer, row, col, keycode);
            }
            break;
        case BOOTLOADER_JUMP:;
            bootloader_jump();
            break;
        case EEPROM_RESET:;
            eeconfig_init();
            reset_keyboard();
            break;
        case SEND_RGB_SETTINGS:;
            raw_hid_send_rgb_settings();
            break;
        case SEND_KEY_CONFIG:;
            raw_hid_send_all_key_configs();
            break;
        case SEND_KEY_REBIND:;
            raw_hid_send_key_rebinds();
            break;
        case SWITCH_RGB_MODE:;
            if (data[1] == 1)
                rgb_matrix_step();
            else if (data[1] == 2)
                rgb_matrix_step_reverse();
            raw_hid_send_rgb_settings();
            break;
    }
}
