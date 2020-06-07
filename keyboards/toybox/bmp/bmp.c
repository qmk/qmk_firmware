 /* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "toybox.h"
#include "bmp_matrix.h"
#include "mtch6102.h"

#include "debug.h"
#include "i2c_master.h"

bool bmp_config_overwrite(bmp_api_config_t const *const config_on_storage,
                          bmp_api_config_t *const       keyboard_config) {
    // get battery voltage from A3
    // setting for two series Ni-MH battery
    BMPAPI->adc.config_vcc_channel(3, 2400, 2000);

    // User can overwrite partial settings
    keyboard_config->mode            = config_on_storage->mode;
    keyboard_config->startup         = config_on_storage->startup;
    keyboard_config->matrix.debounce = config_on_storage->matrix.debounce;
    keyboard_config->matrix.is_left_hand =
        config_on_storage->matrix.is_left_hand;
    keyboard_config->param_central    = config_on_storage->param_central;
    keyboard_config->param_peripheral = config_on_storage->param_peripheral;
    keyboard_config->keymap           = config_on_storage->keymap;
    keyboard_config->reserved[2]      = config_on_storage->reserved[2];

    return true;
}

static void create_status_file() {
    static char status_str[64];
    // clang-format off
    tfp_sprintf(status_str,
                "IO Left:%s\r\n"
                "IO Right:%s\r\n"
                "TouchPad:%s\r\n",
                (get_toybox_mode() & TOYBOX_LEFT) ? "OK" : "NG",
                (get_toybox_mode() & TOYBOX_RIGHT) ? "OK" : "NG",
                is_touchpad_enabled() ? "OK" : "NG");
    // clang-format on
    BMPAPI->usb.create_file("STATUS  TXT", (uint8_t *)status_str,
                            strlen(status_str));
}

void keyboard_post_init_kb() {
    create_status_file();

    // check hardware status and overwrite config
    bmp_api_config_t config = *BMPAPI->app.get_config();
    if (config.mode == SPLIT_MASTER) {
        if (get_toybox_mode() == TOYBOX_RIGHT) {
            // if split master right configuration, this device has only five rows
            config.matrix.device_rows  = 5;
            config.matrix.is_left_hand = 0;
        } else if (get_toybox_mode() == TOYBOX_LEFT) {
            // if split master left configuration, this device has only five rows
            config.matrix.device_rows  = 5;
            config.matrix.is_left_hand = 1;
        } else if (get_toybox_mode() == TOYBOX_SINGLE) {
            // if this device has all rows, this should be SINGLE configuration
            config.mode = SINGLE;
        }
        BMPAPI->app.set_config(&config);
    }

    debug_enable   = false;
    debug_keyboard = false;
    debug_mouse    = false;
}

static const bmp_matrix_func_t matrix_func = {
    toybox_matrix_init, toybox_matrix_get_row, toybox_matrix_get_col,
    toybox_matrix_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &matrix_func; }

void bmp_before_sleep() {
    uint8_t data    = 0xEF;
    uint8_t read[2] = {0};

    if (is_touchpad_enabled()) {
        sleep_mtch6102();
    }

    if (get_toybox_mode() & TOYBOX_LEFT) {
        // select row
        i2c_writeReg(ioexp_left_addr, pca9555_config1, &data, 1, I2C_TIMEOUT);
        // clear INT
        i2c_readReg(ioexp_left_addr, pca9555_input0, read, 2, I2C_TIMEOUT);
        // select row to avoid errata
        i2c_writeReg(ioexp_left_addr, pca9555_config1, &data, 1, I2C_TIMEOUT);
    }

    if (get_toybox_mode() & TOYBOX_RIGHT) {
        // select row
        i2c_writeReg(ioexp_right_addr, pca9555_config1, &data, 1, I2C_TIMEOUT);
        // clear INT
        i2c_readReg(ioexp_right_addr, pca9555_input0, read, 2, I2C_TIMEOUT);
        // select row to avoid errata
        i2c_writeReg(ioexp_right_addr, pca9555_config1, &data, 1, I2C_TIMEOUT);
    }
}

bool checkSafemodeFlag(bmp_api_config_t const * const config) {
    return false;
}

#include "microshell/util/mscmd.h"

MSCMD_USER_RESULT usrcmd_trackpad_test(MSOPT *           msopt,
                                         MSCMD_USER_OBJECT usrobj) {
    test_mtch6102();
    return 0;
}

MSCMD_USER_RESULT usrcmd_trackpad_read_ram(MSOPT *           msopt,
                                           MSCMD_USER_OBJECT usrobj) {
    uint8_t ram[(MTCH6102_CFG_LEN / 8 + 1) * 8] = {0};
    i2c_readReg(I2C_7BIT_ADDR(MTCH6102_READ_ADDR), MTCH6102_REG_CFG_START, ram,
                MTCH6102_CFG_LEN, I2C_TIMEOUT);

    int idx = 0;

    while (idx < MTCH6102_CFG_LEN) {
        for (int r = 0; r < 8; r++) {
            xprintf("0x%02x ", ram[idx]);
            idx++;
        }
        xprintf("\n");
    }

    return 0;
}
