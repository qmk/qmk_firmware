#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

/* Check port settings for clock and data line */
#if !(defined(PS2_CLOCK_PORT) && \
      defined(PS2_CLOCK_PIN) && \
      defined(PS2_CLOCK_DDR) && \
      defined(PS2_CLOCK_BIT))
#   error "PS/2 clock port setting is required in config.h"
#endif

#if !(defined(PS2_DATA_PORT) && \
      defined(PS2_DATA_PIN) && \
      defined(PS2_DATA_DDR) && \
      defined(PS2_DATA_BIT))
#   error "PS/2 data port setting is required in config.h"
#endif


/*
 * Clock
 */
void clock_init(void)
{
}

void clock_lo(void)
{
    PS2_CLOCK_PORT &= ~(1<<PS2_CLOCK_BIT);
    PS2_CLOCK_DDR  |=  (1<<PS2_CLOCK_BIT);
}

void clock_hi(void)
{
    /* input with pull up */
    PS2_CLOCK_DDR  &= ~(1<<PS2_CLOCK_BIT);
    PS2_CLOCK_PORT |=  (1<<PS2_CLOCK_BIT);
}

bool clock_in(void)
{
    PS2_CLOCK_DDR  &= ~(1<<PS2_CLOCK_BIT);
    PS2_CLOCK_PORT |=  (1<<PS2_CLOCK_BIT);
    _delay_us(1);
    return PS2_CLOCK_PIN&(1<<PS2_CLOCK_BIT);
}

/*
 * Data
 */
void data_init(void)
{
}

void data_lo(void)
{
    PS2_DATA_PORT &= ~(1<<PS2_DATA_BIT);
    PS2_DATA_DDR  |=  (1<<PS2_DATA_BIT);
}

void data_hi(void)
{
    /* input with pull up */
    PS2_DATA_DDR  &= ~(1<<PS2_DATA_BIT);
    PS2_DATA_PORT |=  (1<<PS2_DATA_BIT);
}

bool data_in(void)
{
    PS2_DATA_DDR  &= ~(1<<PS2_DATA_BIT);
    PS2_DATA_PORT |=  (1<<PS2_DATA_BIT);
    _delay_us(1);
    return PS2_DATA_PIN&(1<<PS2_DATA_BIT);
}
