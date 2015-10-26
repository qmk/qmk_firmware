#ifndef _analog_h_included__
#define _analog_h_included__

#include <stdint.h>

void analogReference(uint8_t mode);
int16_t analogRead(uint8_t pin);
int16_t adc_read(uint8_t mux);

#define ADC_REF_POWER     (1<<REFS0)
#define ADC_REF_INTERNAL  ((1<<REFS1) | (1<<REFS0))
#define ADC_REF_EXTERNAL  (0)

// These prescaler values are for high speed mode, ADHSM = 1
#if F_CPU == 16000000L
#define ADC_PRESCALER ((1<<ADPS2) | (1<<ADPS1))
#elif F_CPU == 8000000L
#define ADC_PRESCALER ((1<<ADPS2) | (1<<ADPS0))
#elif F_CPU == 4000000L
#define ADC_PRESCALER ((1<<ADPS2))
#elif F_CPU == 2000000L
#define ADC_PRESCALER ((1<<ADPS1) | (1<<ADPS0))
#elif F_CPU == 1000000L
#define ADC_PRESCALER ((1<<ADPS1))
#else
#define ADC_PRESCALER ((1<<ADPS0))
#endif

// some avr-libc versions do not properly define ADHSM
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#if !defined(ADHSM)
#define ADHSM (7)
#endif
#endif

#endif
