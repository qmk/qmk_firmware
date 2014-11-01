#include <stdbool.h>
#include "WProgram.h"
#include "ps2_io.h"
#include <util/delay.h>

/* Check port settings for clock and data line */
#if !(defined(PS2_CLOCK_PIN))
#   error "PS/2 clock pin setting is required in config.h"
#endif

#if !(defined(PS2_DATA_PIN))
#   error "PS/2 data pin setting is required in config.h"
#endif

/*
 * Clock
 */
void clock_init(void)
{
}

void clock_lo(void)
{
    pinMode(PS2_CLOCK_PIN, OUTPUT);
    digitalWriteFast(PS2_CLOCK_PIN, LOW);
}

void clock_hi(void)
{
    pinMode(PS2_CLOCK_PIN, OUTPUT);
    digitalWriteFast(PS2_CLOCK_PIN, HIGH);
}

bool clock_in(void)
{
    pinMode(PS2_CLOCK_PIN, INPUT_PULLUP);
    _delay_us(1);
    return digitalReadFast(PS2_CLOCK_PIN);
}

/*
 * Data
 */
void data_init(void)
{
}

void data_lo(void)
{
    pinMode(PS2_DATA_PIN, OUTPUT);
    digitalWriteFast(PS2_DATA_PIN, LOW);
}

void data_hi(void)
{
    pinMode(PS2_DATA_PIN, OUTPUT);
    digitalWriteFast(PS2_DATA_PIN, HIGH);
}

bool data_in(void)
{
    pinMode(PS2_DATA_PIN, INPUT_PULLUP);
    _delay_us(1);
    return digitalReadFast(PS2_DATA_PIN);
}
