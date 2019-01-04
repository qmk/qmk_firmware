#include "samd51j18a.h"
#include "timer.h"
#include "tmk_core/protocol/arm_atsam/clks.h"

void set_time(uint64_t tset)
{
    ms_clk = tset;
}

void timer_init(void)
{
    ms_clk = 0;
}

uint16_t timer_read(void)
{
    return (uint16_t)ms_clk;
}

uint32_t timer_read32(void)
{
    return (uint32_t)ms_clk;
}

uint64_t timer_read64(void)
{
    return ms_clk;
}

uint16_t timer_elapsed(uint16_t tlast)
{
    return TIMER_DIFF_16(timer_read(), tlast);
}

uint32_t timer_elapsed32(uint32_t tlast)
{
    return TIMER_DIFF_32(timer_read32(), tlast);
}

uint32_t timer_elapsed64(uint32_t tlast)
{
    uint64_t tnow = timer_read64();
    return (tnow >= tlast ? tnow - tlast : UINT64_MAX - tlast + tnow);
}

void timer_clear(void)
{
    ms_clk = 0;
}

void wait_ms(uint64_t msec)
{
    CLK_delay_ms(msec);
}

void wait_us(uint16_t usec)
{
    CLK_delay_us(usec);
}
