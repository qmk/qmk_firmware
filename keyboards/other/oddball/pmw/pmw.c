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
#include "pmw3360_srom_0x04.h"
#include "pmw.h"

// registers
#define Product_ID  0x00
#define Revision_ID 0x01
#define Motion  0x02
#define Delta_X_L 0x03
#define Delta_X_H 0x04
#define Delta_Y_L 0x05
#define Delta_Y_H 0x06
#define SQUAL 0x07
#define Raw_Data_Sum  0x08
#define Maximum_Raw_data  0x09
#define Minimum_Raw_data  0x0A
#define Shutter_Lower 0x0B
#define Shutter_Upper 0x0C
#define Control 0x0D
#define Config1 0x0F
#define Config2 0x10
#define Angle_Tune  0x11
#define Frame_Capture 0x12
#define SROM_Enable 0x13
#define Run_Downshift 0x14
#define Rest1_Rate_Lower  0x15
#define Rest1_Rate_Upper  0x16
#define Rest1_Downshift 0x17
#define Rest2_Rate_Lower  0x18
#define Rest2_Rate_Upper  0x19
#define Rest2_Downshift 0x1A
#define Rest3_Rate_Lower  0x1B
#define Rest3_Rate_Upper  0x1C
#define Observation 0x24
#define Data_Out_Lower  0x25
#define Data_Out_Upper  0x26
#define Raw_Data_Dump 0x29
#define SROM_ID 0x2A
#define Min_SQ_Run  0x2B
#define Raw_Data_Threshold  0x2C
#define Config5 0x2F
#define Power_Up_Reset  0x3A
#define Shutdown  0x3B
#define Inverse_Product_ID  0x3F
#define LiftCutoff_Tune3  0x41
#define Angle_Snap  0x42
#define LiftCutoff_Tune1  0x4A
#define Motion_Burst  0x50
#define LiftCutoff_Tune_Timeout 0x58
#define LiftCutoff_Tune_Min_Length  0x5A
#define SROM_Load_Burst 0x62
#define Lift_Config 0x63
#define Raw_Data_Burst  0x64
#define LiftCutoff_Tune2  0x65

#define PMW_CLOCK_SPEED 70000000
#define MIN_CPI 100
#define MAX_CPI 12000
#define CPI_STEP 100
#define CLAMP_CPI(value) value < MIN_CPI ? MIN_CPI : value > MAX_CPI ? MAX_CPI : value
#define SPI_MODE 3
#define SPI_DIVISOR (F_CPU / PMW_CLOCK_SPEED)
#define US_BETWEEN_WRITES 180
#define US_BETWEEN_READS 20
#define US_BEFORE_MOTION 35

#define MSB1 0x80

extern const uint16_t pmw_firmware_length;
extern const uint8_t pmw_firmware_data[];

void pmw_spi_start(void){
    spi_start(SPI_SS_PIN, false, SPI_MODE, SPI_DIVISOR);
}

void pmw_write(uint8_t reg_addr, uint8_t data){

    pmw_spi_start();
    spi_write(reg_addr | MSB1 );
    spi_write(data);
    spi_stop();
    wait_us(US_BETWEEN_WRITES);
}

uint8_t pmw_read(uint8_t reg_addr){

    pmw_spi_start();
    spi_write(reg_addr & 0x7f );
    uint8_t data = spi_read();
    spi_stop();
    wait_us(US_BETWEEN_READS);

    return data;
}

void pmw_init() {

    setPinOutput(SPI_SS_PIN);

    spi_init();

    // reboot
    pmw_write(Power_Up_Reset, 0x5a);
    wait_ms(50);

    // read registers and discard
    pmw_read(Motion);
    pmw_read(Delta_X_L);
    pmw_read(Delta_X_H);
    pmw_read(Delta_Y_L);
    pmw_read(Delta_Y_H);

    // upload firmware

    // disable rest mode
    pmw_write(Config2, 0x20);

    // enable initialisation
    pmw_write(SROM_Enable, 0x1d);

    // wait a frame
    wait_ms(10);

    // start SROM download
    pmw_write(SROM_Enable, 0x18);

    // write the SROM file

    pmw_spi_start();

    spi_write(SROM_Load_Burst | 0x80);
    wait_us(15);

    // send all bytes of the firmware
    unsigned char c;
    for(int i = 0; i < pmw_firmware_length; i++){
        c = (unsigned char)pgm_read_byte(pmw_firmware_data + i);
        spi_write(c);
        wait_us(15);
    }

    spi_stop();
    wait_us(US_BETWEEN_WRITES);

    // read id
    pmw_read(SROM_ID);

    // wired mouse
    pmw_write(Config2, 0x00);

    // first motion burst; write anything
    pmw_write(Motion_Burst, 0xFF);
    writePinLow(SPI_SS_PIN);
}

config_pmw_t pmw_get_config(void) {
    uint8_t config_1 = pmw_read(Config1);
    return (config_pmw_t){ (config_1 & 0xFF) * CPI_STEP };
}

void pmw_set_config(config_pmw_t config) {
    uint8_t config_1 = (CLAMP_CPI(config.cpi) / CPI_STEP) & 0xFF;
    pmw_write(Config1, config_1);
}

static int16_t convertDeltaToInt(uint8_t high, uint8_t low){

    // join bytes into twos compliment
    uint16_t twos_comp = (high << 8) | low;

    // convert twos comp to int
    if (twos_comp & 0x8000)
        return -1 * (~twos_comp + 1);

    return twos_comp;
}

report_pmw_t pmw_get_report(void) {

    report_pmw_t report = {0, 0};

    pmw_spi_start();

    // start burst mode
    spi_write(Motion_Burst & 0x7f);

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

    spi_stop();

    return report;
}
