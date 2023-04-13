/* Copyright 2020 Alexander Tulloh
 *
 * This program is free software: you can redistribute it and/or modify
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

#include "pointing_device_internal.h"
#include "spi_master.h"
#include "adns9800_srom_A6.h"
#include "adns9800.h"
#include "wait.h"

// registers

typedef enum {
    ADNS9800_REG_Product_ID                   = 0x00,
    ADNS9800_REG_Revision_ID                  = 0x01,
    ADNS9800_REG_Motion                       = 0x02,
    ADNS9800_REG_Delta_X_L                    = 0x03,
    ADNS9800_REG_Delta_X_H                    = 0x04,
    ADNS9800_REG_Delta_Y_L                    = 0x05,
    ADNS9800_REG_Delta_Y_H                    = 0x06,
    ADNS9800_REG_SQUAL                        = 0x07,
    ADNS9800_REG_Pixel_Sum                    = 0x08,
    ADNS9800_REG_Maximum_Pixel                = 0x09,
    ADNS9800_REG_Minimum_Pixel                = 0x0a,
    ADNS9800_REG_Shutter_Lower                = 0x0b,
    ADNS9800_REG_Shutter_Upper                = 0x0c,
    ADNS9800_REG_Frame_Period_Lower           = 0x0d,
    ADNS9800_REG_Frame_Period_Upper           = 0x0e,
    ADNS9800_REG_Configuration_I              = 0x0f,
    ADNS9800_REG_Configuration_II             = 0x10,
    ADNS9800_REG_Frame_Capture                = 0x12,
    ADNS9800_REG_SROM_Enable                  = 0x13,
    ADNS9800_REG_Run_Downshift                = 0x14,
    ADNS9800_REG_Rest1_Rate                   = 0x15,
    ADNS9800_REG_Rest1_Downshift              = 0x16,
    ADNS9800_REG_Rest2_Rate                   = 0x17,
    ADNS9800_REG_Rest2_Downshift              = 0x18,
    ADNS9800_REG_Rest3_Rate                   = 0x19,
    ADNS9800_REG_Frame_Period_Max_Bound_Lower = 0x1a,
    ADNS9800_REG_Frame_Period_Max_Bound_Upper = 0x1b,
    ADNS9800_REG_Frame_Period_Min_Bound_Lower = 0x1c,
    ADNS9800_REG_Frame_Period_Min_Bound_Upper = 0x1d,
    ADNS9800_REG_Shutter_Max_Bound_Lower      = 0x1e,
    ADNS9800_REG_Shutter_Max_Bound_Upper      = 0x1f,
    ADNS9800_REG_LASER_CTRL0                  = 0x20,
    ADNS9800_REG_Observation                  = 0x24,
    ADNS9800_REG_Data_Out_Lower               = 0x25,
    ADNS9800_REG_Data_Out_Upper               = 0x26,
    ADNS9800_REG_SROM_ID                      = 0x2a,
    ADNS9800_REG_Lift_Detection_Thr           = 0x2e,
    ADNS9800_REG_Configuration_V              = 0x2f,
    ADNS9800_REG_Configuration_IV             = 0x39,
    ADNS9800_REG_Power_Up_Reset               = 0x3a,
    ADNS9800_REG_Shutdown                     = 0x3b,
    ADNS9800_REG_Inverse_Product_ID           = 0x3f,
    ADNS9800_REG_Motion_Burst                 = 0x50,
    ADNS9800_REG_SROM_Load_Burst              = 0x62,
    ADNS9800_REG_Pixel_Burst                  = 0x64,
} adns9800_regs;

#define MIN_CPI 200
#define MAX_CPI 8200
#define CPI_STEP 200
#define CLAMP_CPI(value) value<MIN_CPI ? MIN_CPI : value> MAX_CPI ? MAX_CPI : value
#define US_BETWEEN_WRITES 120
#define US_BETWEEN_READS 20
#define US_BEFORE_MOTION 100
#define MSB1 0x80

config_adns9800_t adns9800_get_config(pointing_device_spi_config_t* spi_config);
void              adns9800_set_config(pointing_device_spi_config_t* spi_config, config_adns9800_t);

const pointing_device_driver_t adns9800_driver_spi_default = {.init = adns9800_init, .get_report = adns9800_get_report, .set_cpi = adns9800_set_cpi, .get_cpi = adns9800_get_cpi};
#if defined(ADNS9800_CS_PIN)
const pointing_device_spi_config_t adns9800_config_spi_default = {.cs = ADNS9800_CS_PIN, .mode = ADNS9800_SPI_MODE, .divisor = ADNS9800_SPI_DIVISOR};
#endif

void adns9800_spi_start(pointing_device_spi_config_t* spi_config) {
    spi_start(spi_config->cs, false, spi_config->mode, spi_config->divisor);
}

void adns9800_write(pointing_device_spi_config_t* spi_config, adns9800_regs reg_addr, uint8_t data) {
    adns9800_spi_start(spi_config);
    spi_write(reg_addr | MSB1);
    spi_write(data);
    spi_stop();
    wait_us(US_BETWEEN_WRITES);
}

uint8_t adns9800_read(pointing_device_spi_config_t* spi_config, adns9800_regs reg_addr) {
    adns9800_spi_start(spi_config);
    spi_write(reg_addr & 0x7f);
    uint8_t data = spi_read();
    spi_stop();
    wait_us(US_BETWEEN_READS);

    return data;
}
bool adns9800_check_device(const void* config) {
    pointing_device_spi_config_t* spi_config = (pointing_device_spi_config_t*)config;
    uint8_t                       product_id = adns9800_read(spi_config, ADNS9800_REG_Product_ID);
    uint8_t                       inverse_id = adns9800_read(spi_config, ADNS9800_REG_Inverse_Product_ID);
    pd_dprintf("ADNS9800: PID: %x IID: %x\n", product_id, inverse_id);
    return (product_id == 0x33 && inverse_id == 0xCC);
}

void adns9800_init(const void* config) {
    pointing_device_spi_config_t* spi_config = (pointing_device_spi_config_t*)config;
    gpio_set_pin_output(spi_config->cs);

    spi_init();

    // reboot
    adns9800_write(spi_config, ADNS9800_REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    // read registers and discard
    adns9800_read(spi_config, ADNS9800_REG_Motion);
    adns9800_read(spi_config, ADNS9800_REG_Delta_X_L);
    adns9800_read(spi_config, ADNS9800_REG_Delta_X_H);
    adns9800_read(spi_config, ADNS9800_REG_Delta_Y_L);
    adns9800_read(spi_config, ADNS9800_REG_Delta_Y_H);

    // upload firmware

    // 3k firmware mode
    adns9800_write(spi_config, ADNS9800_REG_Configuration_IV, 0x02);

    // enable initialisation
    adns9800_write(spi_config, ADNS9800_REG_SROM_Enable, 0x1d);

    // wait a frame
    wait_ms(10);

    // start SROM download
    adns9800_write(spi_config, ADNS9800_REG_SROM_Enable, 0x18);

    // write the SROM file

    adns9800_spi_start(spi_config);

    spi_write(ADNS9800_REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    // send all bytes of the firmware
    for (uint16_t i = 0; i < FIRMWARE_LENGTH; i++) {
        spi_write(pgm_read_byte(firmware_data + i));
        wait_us(15);
    }

    spi_stop();

    wait_ms(10);

    // enable laser
    uint8_t laser_ctrl0 = adns9800_read(spi_config, ADNS9800_REG_LASER_CTRL0);
    adns9800_write(spi_config, ADNS9800_REG_LASER_CTRL0, laser_ctrl0 & 0xf0);

    adns9800_set_cpi(config, ADNS9800_CPI);
}

config_adns9800_t adns9800_get_config(pointing_device_spi_config_t* spi_config) {
    uint8_t cpival = adns9800_read(spi_config, ADNS9800_REG_Configuration_I);
    return (config_adns9800_t){(cpival & 0xFF) * CPI_STEP};
}

void adns9800_set_config(pointing_device_spi_config_t* spi_config, config_adns9800_t config) {
    uint8_t config_1 = (CLAMP_CPI(config.cpi) / CPI_STEP) & 0xFF;
    adns9800_write(spi_config, ADNS9800_REG_Configuration_I, config_1);
}

uint16_t adns9800_get_cpi(const void* config) {
    pointing_device_spi_config_t* spi_config = (pointing_device_spi_config_t*)config;
    uint8_t                       cpival     = adns9800_read(spi_config, ADNS9800_REG_Configuration_I);
    return (uint16_t)(cpival & 0xFF) * CPI_STEP;
}

void adns9800_set_cpi(const void* config, uint16_t cpi) {
    pointing_device_spi_config_t* spi_config = (pointing_device_spi_config_t*)config;
    uint8_t                       config_1   = (CLAMP_CPI(cpi) / CPI_STEP) & 0xFF;
    adns9800_write(spi_config, ADNS9800_REG_Configuration_I, config_1);
}

static int16_t convertDeltaToInt(uint8_t high, uint8_t low) {
    // join bytes into twos compliment
    uint16_t twos_comp = (high << 8) | low;

    // convert twos comp to int
    if (twos_comp & 0x8000) return -1 * (~twos_comp + 1);

    return twos_comp;
}

report_mouse_t adns9800_get_report(const void* config) {
    pointing_device_spi_config_t* spi_config = (pointing_device_spi_config_t*)config;
    report_mouse_t                report     = {0};

    adns9800_spi_start(spi_config);

    // start burst mode
    spi_write(ADNS9800_REG_Motion_Burst & 0x7f);

    wait_us(US_BEFORE_MOTION);

    uint8_t motion = spi_read();

    if (motion & 0x80) {
        // clear observation register
        spi_read();

        // delta registers
        uint8_t delta_x_l = spi_read();
        uint8_t delta_x_h = spi_read();
        uint8_t delta_y_l = spi_read();
        uint8_t delta_y_h = spi_read();

        report.x = convertDeltaToInt(delta_x_h, delta_x_l);
        report.y = convertDeltaToInt(delta_y_h, delta_y_l);
    }

    // clear residual motion
    spi_write(ADNS9800_REG_Motion & 0x7f);

    spi_stop();

    return report;
}
