#include <stdbool.h>
#include "ps2_io.h"


// chibiOS headers
#include "ch.h"
#include "hal.h"


/* Check port settings for clock and data line */
#if !(defined(PS2_CLOCK))
#   error "PS/2 clock setting is required in config.h"
#endif

#if !(defined(PS2_DATA))
#   error "PS/2 data setting is required in config.h"
#endif



/*
 * Clock
 */
void clock_init(void)
{
}

void clock_lo(void)
{
    palSetLineMode(PS2_CLOCK, PAL_MODE_OUTPUT_OPENDRAIN);
    palWriteLine(PS2_CLOCK, PAL_LOW);
}

void clock_hi(void)
{
    palSetLineMode(PS2_CLOCK, PAL_MODE_OUTPUT_OPENDRAIN);
    palWriteLine(PS2_CLOCK, PAL_HIGH);
}

bool clock_in(void)
{
    palSetLineMode(PS2_CLOCK, PAL_MODE_INPUT);
    return palReadLine(PS2_CLOCK);
}

/*
 * Data
 */
void data_init(void)
{
}

void data_lo(void)
{
    palSetLineMode(PS2_DATA, PAL_MODE_OUTPUT_OPENDRAIN);
    palWriteLine(PS2_DATA, PAL_LOW);
}

void data_hi(void)
{
    palSetLineMode(PS2_DATA, PAL_MODE_OUTPUT_OPENDRAIN);
    palWriteLine(PS2_DATA, PAL_HIGH);
}

bool data_in(void)
{
    palSetLineMode(PS2_DATA, PAL_MODE_INPUT);
    return palReadLine(PS2_DATA);
}
