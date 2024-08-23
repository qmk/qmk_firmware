#include "rawhid.h"
#include "pcilabs_common.h"
#include "analogkeys.h"
#include "scanfunctions.h"
#include "quantum.h"
#include <stdint.h>
#include <string.h>
#include "config.h"
#include "raw_hid.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    report_id_t report_id = data[0];
    switch (report_id) {
        case SEND_KEYBOARD_DATA:;
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
            for (int i = 1; i < length && data[i] != 69; i++) {
                uint8_t  layer   = data[i];
                uint8_t  row     = data[i + 1];
                uint8_t  col     = data[i + 2];
                uint16_t keycode = data[i + 3];
                dynamic_keymap_set_keycode(layer, row, col, keycode);
            }
            break;
        case BOOTLOADER_JUMP:;
            bootloader_jump();
            break;

        case EEPROM_RESET:;
            eeconfig_init();
            reset_keyboard();
    }
}
