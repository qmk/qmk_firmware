#include "cmsis.h"
#include "timer.h"

/* Mill second tick count */
volatile uint32_t timer_count = 0;

/* Timer interrupt handler */
void SysTick_Handler(void) { timer_count++; }

void timer_init(void) {
    timer_count = 0;
    SysTick_Config(SystemCoreClock / 1000); /* 1ms tick */
}

void timer_clear(void) { timer_count = 0; }

uint16_t timer_read(void) { return (uint16_t)(timer_count & 0xFFFF); }

uint32_t timer_read32(void) { return timer_count; }

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
