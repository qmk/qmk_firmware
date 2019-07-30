#include "timer_utils.h"

bool timer_expired(uint16_t last)
{
    return timer_read() - last < 0x8000;
}

bool timer_expired32(uint32_t last)
{
    return timer_read32() - last < 0x80000000;
}

