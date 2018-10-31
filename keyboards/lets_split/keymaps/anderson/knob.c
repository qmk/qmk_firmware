#include "knob.h"

bool knob_prev_a = false;
int8_t knob_score = 0;

void knob_init(void) {
    // I use pins D4 & C6 for a knob.

    // Set pin modes as input.
    DDRD &= ~(0UL << PD4);
    DDRC &= ~(0UL << PC6);

    // Enable internal pull-up.
    // This is done by "writing" 1 to a pin that has its mode set to input.
    PORTD |= (1 << PD4);
    PORTC |= (1 << PC6);
}

int8_t knob_read(void) {
    // Determine if the knob is being rotated right now.
    // Return 0 if not, -1 or 1 if yes.
    // Call this as often as possible (likely from within matrix_scan_*)
    bool a = PIND & (1 << PD4);
    int8_t dir = 0;

    if (knob_prev_a != a) {
        // 'a' has changed
        knob_prev_a = a;
        bool b = PINC & (1 << PC6);
        if (a == b) {
            // Halfway through CCW rotation
            //
            //         +---YOU ARE HERE
            //         |
            //         v
            // A: _____/^^^^^\__
            // B: __/^^^^^\_____
            knob_score++;
        } else {
            // Halfway through CW rotation
            //
            //         +---YOU ARE HERE
            //         |
            //         v
            // A: _____/^^^^^\_____
            // B: ________/^^^^^\__
            knob_score--;
        }
        if (abs(knob_score) > 1) {
            // A changes twice and both times the direction matched
            dir = (knob_score > 0) ? 1 : -1;
            knob_score = 0;
        }
        if (a && b) {
            // Keep score & knob pins in sync.
            knob_score = 0;
        }
    }

    return dir;

    /*Old method (without stabilization)*/
    /*bool a = PIND & (1 << PD4);*/
    /*int8_t dir = 0;*/
    /*if (prev_a != a) {*/
    /*    bool b = PINC & (1 << PC6);*/
    /*    [>bool b = digitalRead(C6);<]*/
    /*    dir = (a == b) ? 1 : -1;*/
    /*}*/
    /*prev_a = a;*/
    /*return dir;*/
}

