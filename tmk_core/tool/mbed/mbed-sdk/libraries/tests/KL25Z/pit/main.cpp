#include "mbed.h"

extern "C" {
volatile uint32_t msTicks;

void SysTick_Handler(void) {
    msTicks++;
}

void Delay(uint32_t dlyTicks) {
    uint32_t curTicks;

    curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks);
}
}

int main() {
    SysTick_Config(SystemCoreClock / 1000);

    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;   // Clock PIT
    PIT->MCR = 0;                       // Enable PIT

    // Timer 1
    PIT->CHANNEL[1].LDVAL = 0xFFFFFFFF;
    PIT->CHANNEL[1].TCTRL = 0x0;                 // Disable Interrupts
    PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_CHN_MASK; // Chain to timer 0
    PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK; // Start timer 1

    // Timer 2
    PIT->CHANNEL[0].LDVAL = 0xFFFFFFFF;
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK;  // Start timer 0, disable interrupts

    DigitalOut led(LED_BLUE);
    while (true) {
        Delay(1000);
        led = !led;

        uint64_t ticks = (uint64_t)PIT->LTMR64H << 32;
        ticks         |= (uint64_t)PIT->LTMR64L;
        printf("ticks: 0x%x%x\n", (uint32_t)(ticks>>32), (uint32_t)(ticks & 0xFFFFFFFF));

        ticks = (~ticks) / 24;
        uint32_t us = (uint32_t)(0xFFFFFFFF & ticks);

        printf("us   : 0x%x\n", us);
    }
}
