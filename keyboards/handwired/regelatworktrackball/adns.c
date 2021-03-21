/* Copyright 2020 Richard Sutherland <rich@brickbots.com>
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
#include QMK_KEYBOARD_H
#include "spi_master.h"
#include "adns.h"
#include "debug.h"
#include "quantum.h"
#include "pointing_device.h"
#include "adns9800_srom_A6.h"
#include "regelatworktrackball.h"

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

// pins
#define NCS F7

extern const uint16_t firmware_length;
extern const uint8_t firmware_data[];

enum motion_burst_propertr{
    motion = 0,
    observation,
    delta_x_l,
    delta_x_h,
    delta_y_l,
    delta_y_h,
    squal,
    pixel_sum,
    maximum_pixel,
    minimum_pixel,
    shutter_upper,
    shutter_lower,
    frame_period_upper,
    frame_period_lower,
    end_data
};


// used to track the motion delta between updates
volatile int16_t delta_x;
volatile int16_t delta_y;
volatile uint8_t motion_ind = 0;
volatile bool wheel_shift = false;

// Used to accumulate movement for the wheel.
int16_t wheel_accum_v = 0;
int16_t wheel_accum_h = 0;

void adns_begin(void){
    spi_start(NCS, false, 3, 8);
}

void adns_end(void){
    spi_stop();
}

void adns_write(uint8_t reg_addr, uint8_t data){

    adns_begin();
    //send address of the register, with MSBit = 1 to indicate it's a write
    spi_write(reg_addr | 0x80 );
    spi_write(data);

    // tSCLK-NCS for write operation
    wait_us(20);


    // tSWW/tSWR (=120us) minus tSCLK-NCS. Could be shortened, but is looks like a safe lower bound
    wait_us(100);
    adns_end();
}

uint8_t adns_read(uint8_t reg_addr){


    adns_begin();
    // send adress of the register, with MSBit = 0 to indicate it's a read
    spi_write(reg_addr & 0x7f );
    uint8_t data = spi_read();

    // tSCLK-NCS for read operation is 120ns
    wait_us(1);


    //  tSRW/tSRR (=20us) minus tSCLK-NCS
    wait_us(19);

    adns_end();
    return data;
}

void pointing_device_init(void) {
    dprint("STARTING INTI\n");

    spi_init();
    // reset serial port
    adns_begin();
    adns_end();

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

    // set the configuration_IV register in 3k firmware mode
    // bit 1 = 1 for 3k mode, other bits are reserved
    adns_write(REG_Configuration_IV, 0x02);

    // write 0x1d in SROM_enable reg for initializing
    adns_write(REG_SROM_Enable, 0x1d);

    // wait for more than one frame period
    // assume that the frame rate is as low as 100fps... even if it should never be that low
    wait_ms(10);

    // write 0x18 to SROM_enable to start SROM download
    adns_write(REG_SROM_Enable, 0x18);

    // write the SROM file (=firmware data)

    // write burst destination adress
    adns_begin();
    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);
    // send all bytes of the firmware
    unsigned char c;
    for(int i = 0; i < firmware_length; i++){
        c = (unsigned char)pgm_read_byte(firmware_data + i);
        spi_write(c);
        wait_us(15);
    }

    adns_end();
    wait_ms(10);

    // enable laser(bit 0 = 0b), in normal mode (bits 3,2,1 = 000b)
    // reading the actual value of the register is important because the real
    // default value is different from what is said in the datasheet, and if you
    // change the reserved bytes (like by writing 0x00...) it would not work.
    uint8_t laser_ctrl0 = adns_read(REG_LASER_CTRL0);
    adns_write(REG_LASER_CTRL0, laser_ctrl0 & 0xf0);

    wait_ms(1);

    // set the configuration_I register to set the CPI
    // 0x01 = 50, minimum
    // 0x44 = 3400, default
    // 0x8e = 7100
    // 0xA4 = 8200, maximum
    adns_write(REG_Configuration_I, 0x10);

    wait_ms(100);
    dprint("INIT ENDED\n");
}

int16_t convertDeltaToInt(uint8_t high, uint8_t low){

    // join bytes into twos compliment
    uint16_t twos_comp = (high << 8) | low;

    // convert twos comp to int
    if (twos_comp & 0x8000)
        return -1 * ((twos_comp ^ 0xffff) + 1);

    return twos_comp;
}

void readSensor(void) {

    adns_begin();

    // send adress of the register, with MSBit = 1 to indicate it's a write
    spi_write(REG_Motion_Burst & 0x7f);

    uint8_t burst_data[pixel_sum];

    for (int i = 0; i < pixel_sum; ++i) {
        burst_data[i] = spi_read();
    }

    delta_x += convertDeltaToInt(burst_data[delta_x_h], burst_data[delta_x_l]);
    delta_y += convertDeltaToInt(burst_data[delta_y_h], burst_data[delta_y_l]);
    motion_ind = burst_data[motion];
    adns_end();

}

int16_t clamp(int16_t value, int16_t min, int16_t max) {
    return value < min ? min : (value > max ? max : value);
}

void update_wheel(int16_t * accum, int8_t * report) {
    if (abs(*accum) >= 16) {
        *report = clamp(*accum / 16, -127, 127);
        *accum = *accum - (*accum / 16 * 16);
    }
}

void pointing_device_task(void) {
    readSensor();
    report_mouse_t report = pointing_device_get_report();

    if(motion_ind) {
        // Switch y and x to get the trackball rotated -90 degrees.
        // clamp deltas from -127 to 127
        if (!wheel_shift) {
            report.y = clamp(delta_x,  -127, 127);
            report.x = clamp(delta_y,  -127, 127);
        } else {
            wheel_accum_h += delta_y;
            update_wheel(&wheel_accum_h, &(report.h));
            wheel_accum_v += delta_x;
            update_wheel(&wheel_accum_v, &(report.v));
            report.v = -report.v;
        }
        pointing_device_set_report(report);
        pointing_device_send();
    }
    // reset deltas
    delta_x = 0;
    delta_y = 0;

}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    report_mouse_t report = pointing_device_get_report();
    int button = -1;
    bool pressed = record->event.pressed;
    switch (keycode) {
      case KC_MS_BTN1:
        button = 1;
        break;
      case KC_MS_BTN2:
        button = 2;
        break;
      case KC_MS_BTN3:
        button = 4;
        break;
      case KC_MS_BTN4:
        button = 8;
        break;
      case KC_MS_BTN5:
        button = 16;
        break;
      case KC_WH_SHIFT:
        if (wheel_shift && !pressed) {
            wheel_accum_h = 0;
            wheel_accum_v = 0;
        }
        wheel_shift = pressed;
        return false;
      default:
        return process_record_user(keycode, record);
    }
    if (pressed) {
        report.buttons |= button;
    } else {
        report.buttons &= ~button;
    }
    pointing_device_set_report(report);
    return false;
}
