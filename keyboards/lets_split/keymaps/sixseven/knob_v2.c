#include "knob_v2.h"

bool knob_prev_a = false;
knob_report_t knob_report = {.dir = 0, .phase = 0};

void knob_init(void) {
    // I use pins D1 (ISR1) & D4 for a knob.

    // Set pin mode for D4 as input.
    DDRD &= ~(0UL << PD4);

    // Enable internal pull-up for D4.
    // This is done by "writing" 1 to a pin that has its mode set to input.
    PORTD |= (1 << PD4);

    // Enable interrupt for D1
    // For more info on the below flags see this awesome section 11.1 (pages 89-90) here:
    // https://cdn-shop.adafruit.com/datasheets/atmel-7766-8-bit-avr-atmega16u4-32u4_datasheet.pdf
    // Set pin mode & pull-up.
    DDRD &= ~(0UL << PD1);
    PORTD |= (1UL << PD1);

    // INT:    33221100
    EICRA |= 0b00000100;  // 0b01 - any edge
    // INT:     6  3210
    EIMSK |= 0b00000010;
}

ISR(INT1_vect) {
    // Pin D2 (PD1)
    bool a = PIND & (1 << PD1);

    if (knob_prev_a != a) {
        // "A" channel has REALLY changed.
        knob_report.phase = a;
        knob_prev_a = a;
        bool b = PIND & (1 << PD4);
        if (a == b) {
            // Halfway through CCW rotation (A == B)
            //
            //         +---YOU ARE HERE (A=1, B=1)
            //         |     +---OR HERE (A=0, B=0)
            //         |     |
            //         v     v
            // A: _____/^^^^^\__
            // B: __/^^^^^\_____
            knob_report.dir++;
        } else {
            // Halfway through CW rotation (A != B)
            //
            //         +---YOU ARE HERE (A=1, B=0)
            //         |     +---OR HERE (A=0, B=1)
            //         |     |
            //         v     v
            // A: _____/^^^^^\_____
            // B: ________/^^^^^\__
            knob_report.dir--;
        }
    }
}

knob_report_t knob_report_read(void) {
    // Determine if the knob was rotated since last call.
    // Return 0 if not, non-zero if N rotations occured.
    // Call this as often as possible (likely from within matrix_scan_*)
    return knob_report;
}

void knob_report_reset(void) {
    knob_report = (knob_report_t){.dir = 0, .phase = 0};
}

