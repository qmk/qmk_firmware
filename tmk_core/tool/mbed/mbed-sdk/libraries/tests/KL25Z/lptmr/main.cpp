#include "mbed.h"

volatile unsigned int ticks = 0;

DigitalOut led(LED_BLUE);

extern "C" void lptmr_isr(void) {
    // write 1 to TCF to clear the LPT timer compare flag
    LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;

    ticks++;
}

int main() {
    /* Clock the timer */
    SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;

    /* Reset */
    LPTMR0->CSR = 0;

    /* Compare value */
    LPTMR0->CMR = 1000;

    /* Enable interrupt */
    LPTMR0->CSR |= LPTMR_CSR_TIE_MASK;

    /* Set interrupt handler */
    NVIC_SetVector(LPTimer_IRQn, (uint32_t)lptmr_isr);
    NVIC_EnableIRQ(LPTimer_IRQn);

    /* select LPO for RTC and LPTMR */
    LPTMR0->PSR = LPTMR_PSR_PCS(3);       // ERCLK32K -> 8MHz
    LPTMR0->PSR |= LPTMR_PSR_PRESCALE(2); // divide by 8

    /* Start the timer */
    LPTMR0->CSR |= LPTMR_CSR_TEN_MASK;

    led = 0;
    while (true) {
        wait(1);
        led = 1;
        printf("%d\n", ticks);

        wait(1);
        led = 0;
        printf("%d\n", ticks);
    }
}
