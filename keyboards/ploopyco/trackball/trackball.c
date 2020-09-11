/* Copyright 2019 Drashna Jael're (@drashna)
 * Copyright 2019 Sunjun Kim
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
#include "pmw3600_firmware.h"

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif

#ifndef SCROLL_DIVIDER
#    define SCROLL_DIVIDER 12
#endif
#ifndef CPI_1
#    define CPI_1 2000
#endif
#ifndef CPI_2
#    define CPI_2 4000
#endif
#ifndef CPI_3
#    define CPI_3 8000
#endif
#ifndef OPT_DEBOUNCE
#    define OPT_DEBOUNCE 5
#endif
#ifndef OPT_DEBOUNCE
#    define OPT_DEBOUNCE 5  // (ms) 			Time between scroll events
#endif
#ifndef OPT_THRES
#    define OPT_THRES 150  // (0-1024) 	Threshold for actication
#endif
#ifndef OPT_SCALE
#    define OPT_SCALE 1  // Multiplier for wheel
#endif

#define CLAMP_HID(value) value < -127 ? -127 : value > 127 ? 127 : value

// used to track the motion delta between updates
volatile int16_t delta_x;
volatile int16_t delta_y;
volatile uint8_t motion_ind=0;

// TODO: Implement libinput profiles
// https://wayland.freedesktop.org/libinput/doc/latest/pointer-acceleration.html
// Compile time accel selection
// Valid options are ACC_NONE, ACC_LINEAR, ACC_CUSTOM, ACC_QUADRATIC

// Debug Options
#define DEBUGMOUSE false  // Slows down scan rate!
#define DEBUGOPTO false  // Slows down scan rate!

// Trackball State
bool     BurstState   = false;  // init burst state for Trackball module
uint16_t MotionStart  = 0;      // Timer for accel, 0 is resting state
uint16_t lastScroll   = 0;      // Previous confirmed wheel event
uint16_t lastMidClick = 0;      // Stops scrollwheel from being read if it was pressed
uint8_t  OptLowPin    = OPT_ENC1;


__attribute__((unused))
void setCPI(uint16_t cpival) {
    cpival = (cpival / 100 ) - 1;
    if (cpival > 119) { cpival = 119; }

    spi_start_adv();
    spi_write_adv(REG_LASER_CTRL0, cpival);
    spi_stop();

}

int16_t convertDeltaToInt(uint8_t high, uint8_t low) {

    // join bytes into twos compliment
    uint16_t twos_comp = (high << 8) | low;

    // convert twos comp to int
    if (twos_comp & 0x8000)
        return -1 * (~twos_comp + 1);

    return twos_comp;
}

report_pmw_t get_pmw_report(void) {

    report_pmw_t report = {0, 0};

    spi_start_adv();


    // motion register
    uint8_t motion = spi_read_adv(REG_Motion_Burst & 0x7f);

    if(motion & 0x80) {
        // clear observation register

        // delta registers
        uint8_t delta_x_l = spi_read_adv(REG_Delta_X_L);
        uint8_t delta_x_h = spi_read_adv(REG_Delta_X_H);
        uint8_t delta_y_l = spi_read_adv(REG_Delta_Y_L);
        uint8_t delta_y_h = spi_read_adv(REG_Delta_Y_H);

        report.x = convertDeltaToInt(delta_x_h, delta_x_l);
        report.y = convertDeltaToInt(delta_y_h, delta_y_l);

        xprintf("SPI X: %d, Y: %d\n", report.x, report.y);
        xprintf("SPI RAW M: %d, X_L: %d, X_H: %d, Y_L: %d, Y_H: %d, \n", motion, delta_x_l, delta_x_h, delta_y_l, delta_y_h);
    }

    spi_stop();

    return report;
}


void process_wheel(report_mouse_t *mouse_report) {
    // TODO: Replace this with interrupt driven code,  polling is S L O W
    // Lovingly ripped from the Ploopy Source

    // If the mouse wheel was just released, do not scroll.
    // unsigned long elapsed = micros() - middleClickRelease;
    // if (elapsed < SCROLL_BUTT_DEBOUNCE) { return 0; }

    // Limit the number of scrolls per unit time.
    if ((timer_read() - lastScroll) < OPT_DEBOUNCE) return;

    // Don't scroll if the middle button is depressed.
    // int middleButtonPin = digitalRead(MOUSE_MIDDLE_PIN);
    // if (middleButtonPin == LOW) { return 0; }

    lastScroll  = timer_read();
    uint16_t p1 = adc_read(OPT_ENC1_MUX);
    uint16_t p2 = adc_read(OPT_ENC2_MUX);
    if (DEBUGOPTO) dprintf("OPT1: %d, OPT2: %d\n", p1, p2);

    uint8_t dir = 0;
    if (p1 < OPT_THRES && p2 < OPT_THRES) {
        if (OptLowPin == OPT_ENC1) {
            dir = -1;
        }  // scroll down
        else if (OptLowPin == OPT_ENC2) {
            dir = 1;
        }  // scroll up
        OptLowPin = 0;
    } else if (p1 < OPT_THRES) {
        OptLowPin = OPT_ENC1;
    } else if (p2 < OPT_THRES) {
        OptLowPin = OPT_ENC2;
    }

    // Bundle and send if needed
    if (dir == 0) return;
    mouse_report->v += dir * OPT_SCALE;
}



bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (DEBUGMOUSE) {
        dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    }

    // Update Timer to prevent accidental scrolls
    if ((record->event.key.col == 2) && (record->event.key.row == 0) && (record->event.pressed == 0)) {
        lastMidClick = timer_read();
    }

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        if (record->event.pressed) {
            if (keycode == KC_MS_BTN1)
                currentReport.buttons |= MOUSE_BTN1;
            else if (keycode == KC_MS_BTN2)
                currentReport.buttons |= MOUSE_BTN2;
            else if (keycode == KC_MS_BTN3)
                currentReport.buttons |= MOUSE_BTN3;
            else if (keycode == KC_MS_BTN4)
                currentReport.buttons |= MOUSE_BTN4;
            else if (keycode == KC_MS_BTN5)
                currentReport.buttons |= MOUSE_BTN5;
        } else {
            if (keycode == KC_MS_BTN1)
                currentReport.buttons &= ~MOUSE_BTN1;
            else if (keycode == KC_MS_BTN2)
                currentReport.buttons &= ~MOUSE_BTN2;
            else if (keycode == KC_MS_BTN3)
                currentReport.buttons &= ~MOUSE_BTN3;
            else if (keycode == KC_MS_BTN4)
                currentReport.buttons &= ~MOUSE_BTN4;
            else if (keycode == KC_MS_BTN5)
                currentReport.buttons &= ~MOUSE_BTN5;
        }
        pointing_device_set_report(currentReport);
    }
#endif

    return process_record_user(keycode, record);
}



// Hardware Setup
void keyboard_pre_init_kb(void) {
     debug_enable = false;
    // debug_matrix = true;
    // debug_mouse  = false;


    // This can probably be replaced with rotary encoder config,
    setPinInput(OPT_ENC1);
    setPinInput(OPT_ENC2);

    // This is the debug LED.
    setPinOutput(F7);
    writePin(F7, debug_enable);

    /* Ground all output pins connected to ground. This provides additional
     * pathways to ground. If you're messing with this, know this: driving ANY
     * of these pins high will cause a short. On the MCU. Ka-blooey.
     */
    setPinOutput(D3);
    writePinLow(D3);
    setPinOutput(D1);
    writePinLow(D1);
    setPinOutput(B4);
    writePinLow(B4);
    setPinOutput(B6);
    writePinLow(B6);
    setPinOutput(B7);
    writePinLow(B7);
    setPinOutput(D6);
    writePinLow(D6);
    setPinOutput(C7);
    writePinLow(C7);
    setPinOutput(F6);
    writePinLow(F6);
    setPinOutput(F5);
    writePinLow(F5);
    setPinOutput(F3);
    writePinLow(F3);

    spi_init();
    spi_start_adv();
    spi_stop();

    spi_write_adv(REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    spi_read_adv(REG_Motion);
    spi_read_adv(REG_Delta_X_L);
    spi_read_adv(REG_Delta_X_H);
    spi_read_adv(REG_Delta_Y_L);
    spi_read_adv(REG_Delta_Y_H);

    spi_write_adv(REG_Configuration_IV, 0x02);
    spi_write_adv(REG_SROM_Enable, 0x1d);
    wait_ms(10);

    spi_write_adv(REG_SROM_Enable, 0x18);

    spi_start_adv();
    spi_write(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    unsigned char c;
    for(int i = 0; i < 4094; i++){
        c = (unsigned char)pgm_read_byte(firmware_data + i);
        spi_write(c);
        wait_us(15);
    }
    spi_stop();
    wait_ms(10);

    uint8_t laser_ctrl0 = spi_read_adv(REG_LASER_CTRL0);
    spi_write_adv(REG_LASER_CTRL0, laser_ctrl0 & 0xf0);

    wait_ms(1);

    // set the configuration_I register to set the CPI
    // 0x01 = 50, minimum
    // 0x44 = 3400, default
    // 0x8e = 7100
    // 0xA4 = 8200, maximum
    spi_write_adv(REG_Configuration_I, 0x08);

    wait_ms(100);
}

void pointing_device_task(void) {

    report_mouse_t mouse_report = pointing_device_get_report();
    process_wheel(&mouse_report);

    report_pmw_t pmw_report = get_pmw_report();

    int8_t clamped_x = CLAMP_HID(pmw_report.x);
    int8_t clamped_y = CLAMP_HID(pmw_report.y);

    mouse_report.x = -clamped_x;
    mouse_report.y = clamped_y;

    pointing_device_set_report(mouse_report);
    pointing_device_send();

}
