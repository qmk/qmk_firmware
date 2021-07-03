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
#include "quantum.h"
#include "adns9800_srom_A6.h"
#include "adns9800.h"

// registers
#define REG_Product_ID                           0x00
#define REG_Revision_ID                          0x01
#define REG_Motion                               0x02
#define REG_Delta_X_L                            0x03
#define REG_Delta_X_H                            0x04
#define REG_Delta_Y_L                            0x05
#define REG_Delta_Y_H                            0x06
#define REG_SQUAL                                0x07
#define REG_Pixel_Sum                            0x08
#define REG_Maximum_Pixel                        0x09
#define REG_Minimum_Pixel                        0x0a
#define REG_Shutter_Lower                        0x0b
#define REG_Shutter_Upper                        0x0c
#define REG_Frame_Period_Lower                   0x0d
#define REG_Frame_Period_Upper                   0x0e
#define REG_Configuration_I                      0x0f
#define REG_Configuration_II                     0x10
#define REG_Frame_Capture                        0x12
#define REG_SROM_Enable                          0x13
#define REG_Run_Downshift                        0x14
#define REG_Rest1_Rate                           0x15
#define REG_Rest1_Downshift                      0x16
#define REG_Rest2_Rate                           0x17
#define REG_Rest2_Downshift                      0x18
#define REG_Rest3_Rate                           0x19
#define REG_Frame_Period_Max_Bound_Lower         0x1a
#define REG_Frame_Period_Max_Bound_Upper         0x1b
#define REG_Frame_Period_Min_Bound_Lower         0x1c
#define REG_Frame_Period_Min_Bound_Upper         0x1d
#define REG_Shutter_Max_Bound_Lower              0x1e
#define REG_Shutter_Max_Bound_Upper              0x1f
#define REG_LASER_CTRL0                          0x20
#define REG_Observation                          0x24
#define REG_Data_Out_Lower                       0x25
#define REG_Data_Out_Upper                       0x26
#define REG_SROM_ID                              0x2a
#define REG_Lift_Detection_Thr                   0x2e
#define REG_Configuration_V                      0x2f
#define REG_Configuration_IV                     0x39
#define REG_Power_Up_Reset                       0x3a
#define REG_Shutdown                             0x3b
#define REG_Inverse_Product_ID                   0x3f
#define REG_Motion_Burst                         0x50
#define REG_SROM_Load_Burst                      0x62
#define REG_Pixel_Burst                          0x64

#define ADNS_CLOCK_SPEED 2000000
#define MIN_CPI 200
#define MAX_CPI 8200
#define CPI_STEP 200
#define CLAMP_CPI(value) value < MIN_CPI ? MIN_CPI : value > MAX_CPI ? MAX_CPI : value
#define SPI_MODE 3
#define SPI_DIVISOR (F_CPU / ADNS_CLOCK_SPEED)
#define US_BETWEEN_WRITES 120
#define US_BETWEEN_READS 20
#define US_BEFORE_MOTION 100
#define MSB1 0x80

extern const uint16_t adns_firmware_length;
extern const uint8_t adns_firmware_data[];

void adns_spi_start(void){
    spi_start(SPI_SS_PIN, false, SPI_MODE, SPI_DIVISOR);
}

void adns_write(uint8_t reg_addr, uint8_t data){

    adns_spi_start();
    spi_write(reg_addr | MSB1);
    spi_write(data);
    spi_stop();
    wait_us(US_BETWEEN_WRITES);
}

uint8_t adns_read(uint8_t reg_addr){

    adns_spi_start();
    spi_write(reg_addr & 0x7f );
    uint8_t data = spi_read();
    spi_stop();
    wait_us(US_BETWEEN_READS);

    return data;
}

void adns_init() {

    setPinOutput(SPI_SS_PIN);

    spi_init();

    // reboot
    adns_write(REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    // read registers and discard
    adns_read(REG_Motion);
    adns_read(REG_Delta_X_L);
    adns_read(REG_Delta_X_H);
    adns_read(REG_Delta_Y_L);
    adns_read(REG_Delta_Y_H);

    // upload firmware

    // 3k firmware mode
    adns_write(REG_Configuration_IV, 0x02);

    // enable initialisation
    adns_write(REG_SROM_Enable, 0x1d);

    // wait a frame
    wait_ms(10);

    // start SROM download
    adns_write(REG_SROM_Enable, 0x18);

    // write the SROM file

    adns_spi_start();

    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    // send all bytes of the firmware
    unsigned char c;
    for(int i = 0; i < adns_firmware_length; i++){
        c = (unsigned char)pgm_read_byte(adns_firmware_data + i);
        spi_write(c);
        wait_us(15);
    }

    spi_stop();

    wait_ms(10);

    // enable laser
    uint8_t laser_ctrl0 = adns_read(REG_LASER_CTRL0);
    adns_write(REG_LASER_CTRL0, laser_ctrl0 & 0xf0);
}

config_adns_t adns_get_config(void) {
    uint8_t config_1 = adns_read(REG_Configuration_I);
    return (config_adns_t){ (config_1 & 0xFF) * CPI_STEP };
}

void adns_set_config(config_adns_t config) {
    uint8_t config_1 = (CLAMP_CPI(config.cpi) / CPI_STEP) & 0xFF;
    adns_write(REG_Configuration_I, config_1);
}

static int16_t convertDeltaToInt(uint8_t high, uint8_t low){

    // join bytes into twos compliment
    uint16_t twos_comp = (high << 8) | low;

    // convert twos comp to int
    if (twos_comp & 0x8000)
        return -1 * (~twos_comp + 1);

    return twos_comp;
}

report_adns_t adns_get_report(void) {

    report_adns_t report = {0, 0};

    adns_spi_start();

    // start burst mode
    spi_write(REG_Motion_Burst & 0x7f);

    wait_us(US_BEFORE_MOTION);

    uint8_t motion = spi_read();

    if(motion & 0x80) {

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
