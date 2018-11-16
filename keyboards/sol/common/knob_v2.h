// Rotary knob implementation - Version 2.
// Uses 2 digital pins - D2 (via interrupt) & D6.
// #include "rev1.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#ifndef ENCODER_PIN_1
  #define ENCODER_PIN_1 PD2
#endif
#ifndef ENCODER_PIN_2
  #define ENCODER_PIN_2 PD6
#endif
#ifndef ENCODER_INT
  #define ENCODER_INT   INT2_vect
#endif

typedef struct knob_report_t {
    int8_t dir;  // Contains number of rotations that happened
    int8_t phase;  // Contains 0 if last rotation happened on 90 degrees, 1 if on 270
}  knob_report_t;

void knob_init(void);
knob_report_t knob_report_read(void);
void knob_report_reset(void);

bool knob_prev_a;
int8_t knob_dir;
