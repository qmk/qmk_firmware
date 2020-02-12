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

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif

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

// Mouse Processing
static void process_mouse(bool bMotion, bool* bBurst) {
    // Read state
    PMWState d        = point_burst_read(bMotion, bBurst);
    bool     isMoving = (d.X != 0) || (d.Y != 0);
    // Reset timer if stopped moving
    if (!isMoving) {
        if (MotionStart != 0) MotionStart = 0;
        return;
    }

    // Set timer if new motion
    if ((MotionStart == 0) && isMoving) {
        if (DEBUGMOUSE) dprintf("Starting motion.\n");
        MotionStart = timer_read();
    }

    if (DEBUGMOUSE) {
        dprintf("Delt] d: %d t: %u\n", abs(d.X) + abs(d.Y), MotionStart);
    }
    if (DEBUGMOUSE) {
        dprintf("Pre ] X: %d, Y: %d\n", d.X, d.Y);
    }

    // Apply any post processing required
#if defined(PROFILE_LINEAR)
    float scale = float(timer_elaspsed(MotionStart)) / 1000.0;
    x           = x * scale;
    y           = y * scale;
#elif defined(PROFILE_INVERSE)
// TODO
#else
// no post processing
#endif

    // Wrap to HID size
    int16_t x = constrain(d.X, -127, 127);
    int16_t y = constrain(d.Y, -127, 127);
    if (DEBUGMOUSE) dprintf("Cons] X: %d, Y: %d\n", x, y);
    // dprintf("Elapsed:%u, X: %f Y: %\n", i, pgm_read_byte(firmware_data+i));

    report_mouse_t currentReport = pointing_device_get_report();
    currentReport.x              = (int)x;
    currentReport.y              = (int)y;
    pointing_device_set_report(currentReport);
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

void process_wheel(void) {
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
    report_mouse_t cRep = pointing_device_get_report();
    cRep.v += dir * OPT_SCALE;
    pointing_device_set_report(cRep);
}

// Hardware Setup
void keyboard_pre_init_kb(void) {
    // debug_enable = false;
    // debug_matrix = true;
    // debug_mouse  = false;

    // Set up all the hardware
    setPinOutput(SENSOR_CS);

    // These should probably be moved into the matrix itself
    // using DIRECT_PINS, and then custom keycodes added for the
    // mouse buttons.
    setPinInputHigh(MOUSE_LEFT_PIN);
    setPinInputHigh(MOUSE_RIGHT_PIN);
    setPinInputHigh(MOUSE_MIDDLE_PIN);
    setPinInputHigh(MOUSE_BACK_PIN);
    setPinInputHigh(MOUSE_FORWARD_PIN);

    // This can probably be replaced with rotary encoder config,
    setPinInput(OPT_ENC1);
    setPinInput(OPT_ENC2);

    // This is the debug LED.
    setPinOutput(F7);
    if (debug_enable) {
        writePinHigh(F7);
    } else {
        writePinLow(F7);
    }

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

    // Initialize SPI for MCU
    SPI_Init(SPI_OPTION);
    DDRB |= (1 << SS_TB);
    PORTB |= (1 << SS_TB);  // pull up to diable all comm
    point_init(SS_TB);
}
void matrix_scan_kb(void) {
    process_mouse(Motion, &BurstState);
    process_wheel();
    matrix_scan_user();
}
