#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef LUTS_H
#define LUTS_H

#define VIBRATO_LUT_LENGTH 20

#define FREQUENCY_LUT_LENGTH 349

extern const float vibrato_lut[VIBRATO_LUT_LENGTH];
extern const uint16_t frequency_lut[FREQUENCY_LUT_LENGTH];

#endif /* LUTS_H */