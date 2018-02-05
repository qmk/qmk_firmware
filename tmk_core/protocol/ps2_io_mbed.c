#include <stdbool.h>
#include "ps2_io.h"
#include "gpio_api.h"


static gpio_t clock;
static gpio_t data;

/*
 * Clock
 */
void clock_init(void)
{
    gpio_init(&clock, P0_9);
    gpio_mode(&clock, OpenDrain|PullNone);
}

void clock_lo(void)
{
    gpio_dir(&clock, PIN_OUTPUT);
    gpio_write(&clock, 0);
}
void clock_hi(void)
{
    gpio_dir(&clock, PIN_OUTPUT);
    gpio_write(&clock, 1);
}

bool clock_in(void)
{
    gpio_dir(&clock, PIN_INPUT);
    return gpio_read(&clock);
}

/*
 * Data
 */
void data_init(void)
{
    gpio_init(&data, P0_8);
    gpio_mode(&data, OpenDrain|PullNone);
}

void data_lo(void)
{
    gpio_dir(&data, PIN_OUTPUT);
    gpio_write(&data, 0);
}

void data_hi(void)
{
    gpio_dir(&data, PIN_OUTPUT);
    gpio_write(&data, 1);
}

bool data_in(void)
{
    gpio_dir(&data, PIN_INPUT);
    return gpio_read(&data);
}
