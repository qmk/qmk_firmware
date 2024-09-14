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

#include "spi_master.h"
#include "adns9800_srom_A6.h"
#include "adns9800.h"
#include "wait.h"

// registers
// clang-format off
#define REG_Product_ID                   0x00
#define REG_Revision_ID                  0x01
#define REG_Motion                       0x02
#define REG_Delta_X_L                    0x03
#define REG_Delta_X_H                    0x04
#define REG_Delta_Y_L                    0x05
#define REG_Delta_Y_H                    0x06
#define REG_SQUAL                        0x07
#define REG_Pixel_Sum                    0x08
#define REG_Maximum_Pixel                0x09
#define REG_Minimum_Pixel                0x0a
#define REG_Shutter_Lower                0x0b
#define REG_Shutter_Upper                0x0c
#define REG_Frame_Period_Lower           0x0d
#define REG_Frame_Period_Upper           0x0e
#define REG_Configuration_I              0x0f
#define REG_Configuration_II             0x10
#define REG_Frame_Capture                0x12
#define REG_SROM_Enable                  0x13
#define REG_Run_Downshift                0x14
#define REG_Rest1_Rate                   0x15
#define REG_Rest1_Downshift              0x16
#define REG_Rest2_Rate                   0x17
#define REG_Rest2_Downshift              0x18
#define REG_Rest3_Rate                   0x19
#define REG_Frame_Period_Max_Bound_Lower 0x1a
#define REG_Frame_Period_Max_Bound_Upper 0x1b
#define REG_Frame_Period_Min_Bound_Lower 0x1c
#define REG_Frame_Period_Min_Bound_Upper 0x1d
#define REG_Shutter_Max_Bound_Lower      0x1e
#define REG_Shutter_Max_Bound_Upper      0x1f
#define REG_LASER_CTRL0                  0x20
#define REG_Observation                  0x24
#define REG_Data_Out_Lower               0x25
#define REG_Data_Out_Upper               0x26
#define REG_SROM_ID                      0x2a
#define REG_Lift_Detection_Thr           0x2e
#define REG_Configuration_V              0x2f
#define REG_Configuration_IV             0x39
#define REG_Power_Up_Reset               0x3a
#define REG_Shutdown                     0x3b
#define REG_Inverse_Product_ID           0x3f
#define REG_Motion_Burst                 0x50
#define REG_SROM_Load_Burst              0x62
#define REG_Pixel_Burst                  0x64

#define MIN_CPI           200
#define MAX_CPI           8200
#define CPI_STEP          200
#define CLAMP_CPI(value)  value<MIN_CPI ? MIN_CPI : value> MAX_CPI ? MAX_CPI : value
#define US_BETWEEN_WRITES 120
#define US_BETWEEN_READS  20
#define US_BEFORE_MOTION  100
#define MSB1              0x80
// clang-format on

void adns9800_spi_start(void) {
    spi_start(ADNS9800_CS_PIN, false, ADNS9800_SPI_MODE, ADNS9800_SPI_DIVISOR);
}

void adns9800_write(uint8_t reg_addr, uint8_t data) {
    adns9800_spi_start();
    spi_write(reg_addr | MSB1);
    spi_write(data);
    spi_stop();
    wait_us(US_BETWEEN_WRITES);
}

uint8_t adns9800_read(uint8_t reg_addr) {
    adns9800_spi_start();
    spi_write(reg_addr & 0x7f);
    uint8_t data = spi_read();
    spi_stop();
    wait_us(US_BETWEEN_READS);

    return data;
}

void adns9800_init(void) {
    gpio_set_pin_output(ADNS9800_CS_PIN);

    spi_init();

    // reboot
    adns9800_write(REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    // read registers and discard
    adns9800_read(REG_Motion);
    adns9800_read(REG_Delta_X_L);
    adns9800_read(REG_Delta_X_H);
    adns9800_read(REG_Delta_Y_L);
    adns9800_read(REG_Delta_Y_H);

#ifdef ADNS9800_UPLOAD_SROM
    // upload firmware

    // 3k firmware mode
    adns9800_write(REG_Configuration_IV, 0x02);

    // enable initialisation
    adns9800_write(REG_SROM_Enable, 0x1d);

    // wait a frame
    wait_ms(10);

    // start SROM download
    adns9800_write(REG_SROM_Enable, 0x18);

    // write the SROM file

    adns9800_spi_start();

    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    // send all bytes of the firmware
    for (uint16_t i = 0; i < FIRMWARE_LENGTH; i++) {
        spi_write(pgm_read_byte(firmware_data + i));
        wait_us(15);
    }

    spi_stop();

    wait_ms(10);
#else
    // write reset value to REG_Configuration_IV
    adns9800_write(REG_Configuration_IV, 0x0);

    // write reset value to REG_SROM_Enable
    adns9800_write(REG_SROM_Enable, 0x0);

    // wait a frame
    wait_ms(10);
#endif

    // enable laser
    uint8_t laser_ctrl0 = adns9800_read(REG_LASER_CTRL0);
    adns9800_write(REG_LASER_CTRL0, laser_ctrl0 & 0xf0);

    adns9800_set_cpi(ADNS9800_CPI);
}

config_adns9800_t adns9800_get_config(void) {
    uint8_t cpival = adns9800_read(REG_Configuration_I);
    return (config_adns9800_t){(cpival & 0xFF) * CPI_STEP};
}

void adns9800_set_config(config_adns9800_t config) {
    uint8_t config_1 = (CLAMP_CPI(config.cpi) / CPI_STEP) & 0xFF;
    adns9800_write(REG_Configuration_I, config_1);
}

uint16_t adns9800_get_cpi(void) {
    uint8_t cpival = adns9800_read(REG_Configuration_I);
    return (uint16_t)(cpival & 0xFF) * CPI_STEP;
}

void adns9800_set_cpi(uint16_t cpi) {
    uint8_t config_1 = (CLAMP_CPI(cpi) / CPI_STEP) & 0xFF;
    adns9800_write(REG_Configuration_I, config_1);
}

static int16_t convertDeltaToInt(uint8_t high, uint8_t low) {
    // join bytes into twos compliment
    uint16_t twos_comp = (high << 8) | low;

    // convert twos comp to int
    if (twos_comp & 0x8000) return -1 * (~twos_comp + 1);

    return twos_comp;
}

report_adns9800_t adns9800_get_report(void) {
    report_adns9800_t report = {0};

    adns9800_spi_start();

    // start burst mode
    spi_write(REG_Motion_Burst & 0x7f);

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
    spi_write(REG_Motion & 0x7f);

    spi_stop();

    return report;
}
