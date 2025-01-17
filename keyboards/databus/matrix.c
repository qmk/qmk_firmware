// Created/amended by OleVoip 2025.
// SPDX-License-Identifier: GPL-2.0-or-later

#include "databus.h"
#include "databus-kb.h"

// timer as a safety measure
static uint16_t timer;

// scan codes
typedef uint8_t scancode_t;

static inline uint8_t driver(scancode_t sc) {
    return sc & ((1 << 3) - 1);
}
static inline uint8_t sensor(scancode_t sc) {
    return sc >> 3;
}

// drive lines
#ifndef DRIVER_ADDR_TRANSF
#define DRIVER_ADDR_TRANSF(u) u
#endif
#define DRIVER_MASK DRIVER_ADDR_TRANSF(accomodating_bitmask(DRIVE_LINES))

static inline void drive_line(uint8_t iLine) {
    PORT(DRIVER_ADDR_PORT) &= ~DRIVER_MASK;
    PORT(DRIVER_ADDR_PORT) |= DRIVER_ADDR_TRANSF(iLine);
}

static inline void init_line_drivers(void){
    DDR(DRIVER_ADDR_PORT) |= DRIVER_MASK;
    PORT(DRIVER_ADDR_PORT) &= ~DRIVER_MASK;
}

// sense lines
typedef uint8_t sense_t;
static sense_t matrix[DRIVE_LINES];
static uint8_t scan_times[DRIVE_LINES];

sense_t matrix_get_row(uint8_t iLine) {
    return matrix[iLine];
}

static inline sense_t read_sense_lines(uint8_t iLine) {
    drive_line(iLine);
    wait_us(MATRIX_IO_DELAY);
    return read_bus();
}

// pressed key at keyboard start causes jump to bootloader
__attribute__((constructor)) void maybe_bootloader(void) {
    init_bus();
    init_line_drivers();
    set_bus_input();
    write_pin(SENSE_OE_PIN, SENSE_OE_ACTIVE);
    uint8_t signal = read_sense_lines(driver(0));
    toggle_pin(SENSE_OE_PIN);
    if (signal) {
        bootloader_jump();
    }
}

void matrix_init(void) {
    timer = timer_read();
    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    uint8_t time = timer_read8();
    bool changed = false;

    write_pin(SENSE_OE_PIN, SENSE_OE_ACTIVE);
    for (uint8_t iLine = DRIVE_LINES; iLine--;) {
        uint8_t last_time = scan_times[iLine];
        if (last_time) {
            if ((uint8_t)(time - last_time) >= DEBOUNCE) {
                scan_times[iLine] = 0;
            }
        } else {
            sense_t signal = read_sense_lines(iLine);
            if (signal ^ matrix[iLine]) {
                changed = true;
                matrix[iLine] = signal;
                scan_times[iLine] = time ? time : 1;
                if (signal==3 && !iLine) {
                    reset_keyboard();
                }
            }
        }
    }
    toggle_pin(SENSE_OE_PIN);

    matrix_scan_kb();
    if (changed) {
        matrix_print();
    }
    return changed;
}

void matrix_print(void) {
    print("\nActive keys:");
    for (uint8_t iLine = 0; iLine < DRIVE_LINES; iLine++) {
        sense_t signal = matrix[iLine];
        if (signal) {
            uint8_t jLine=0, line = 1;
            do {
                if (signal & line) {
                    print(" ");
                    xputs(key_position_labels[iLine][jLine]);
                }
            } while (++jLine, line <<= 1);
        }
    }
    print("\n");
}

__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}
__attribute__((weak)) void matrix_scan_user(void) {}
__attribute__((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}

/*
Read matrix:
+ Put the address of the next drive line on the inputs of the line decoder
+ (If there are more drive lines than decoder outputs, the decoder needs to
  be enabled and disabled again.)
+ The selected drive line becomes 'hot', here: tied to ground.
+ Where one of the keys along the drive line is pressed, it pulls the
  corresponding sense line down. This will be detected by the output buffer
  inputs after a propagation time of several (tens of) microseconds.
+ After waiting accordingly, the corresponding data-bus bit will go low
  when the buffer output is activated.
*/

/*
Init:
+ Determine ports for data bus (DATA_PORT) and line address
  (ADDRESS_PORT). Whilst all 8 bits must be available on the DATA_PORT,
  only 4 (or 5) bits are needed on the ADDRESS_PORT, the remaining 3 or 4
  may serve other purposes. However, as the address will be determined by
  a counter, it should be consecutive bits; hence, there should be a
  provision to choose bits 1–4 (+5) or 5–8 (+1).
+ Make address bits of the ADDRESS_PORT outputs (with pull-ups)
+ Prepare the DATA_PORT for input
+ If there are other members on the data bus, disable them
+ Enable the sense line buffers
Keeping the data bus prepared for reading the sense wires is the normal
state as scanning the matrix is what the system will be busy with.

For bootmagic:
+ Set the line address on the ADDRESS_PORT such that the drive line where
  the Escape key is on gets 'hot'
+ Do other things, or wait, until 30 µs have passed.
+ Provided the keyboard is not prone to noise on the sense wire,
  no debouncing is needed: if there is a signal, the key has been pressed.
+ Read the state of the eight sense wires from the data bus.
+ We also accept signals on other sense wires from other keys driven by
  the same line

Scanning:

*/
