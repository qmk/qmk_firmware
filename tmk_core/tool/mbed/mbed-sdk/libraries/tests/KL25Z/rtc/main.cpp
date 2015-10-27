#include "mbed.h"

DigitalOut status_led(LED_BLUE);
DigitalOut error_led(LED_RED);

extern "C" void RTC_IRQHandler(void) {
    error_led = 0;
}

extern "C" void RTC_Seconds_IRQHandler(void) {
    error_led = 0;
}

extern "C" void HardFault_Handler(void) {
    error_led = 0;
}

extern "C" void NMI_Handler_Handler(void) {
    error_led = 0;
}

void rtc_init(void) {
    // enable the clock to SRTC module register space
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    SIM->SOPT1 = (SIM->SOPT1 & ~SIM_SOPT1_OSC32KSEL_MASK) | SIM_SOPT1_OSC32KSEL(0);

    // disable interrupts
    NVIC_DisableIRQ(RTC_Seconds_IRQn);
    NVIC_DisableIRQ(RTC_IRQn);

    // Reset
    RTC->CR = RTC_CR_SWR_MASK;
    RTC->CR &= ~RTC_CR_SWR_MASK;

    // Allow write
    RTC->CR = RTC_CR_UM_MASK | RTC_CR_SUP_MASK;

    NVIC_EnableIRQ(RTC_Seconds_IRQn);
    NVIC_EnableIRQ(RTC_Seconds_IRQn);

    printf("LR: 0x%x\n", RTC->LR);
    printf("CR: 0x%x\n", RTC->CR);
    wait(1);
    if (RTC->SR & RTC_SR_TIF_MASK){
        RTC->TSR = 0;
    }
    RTC->TCR = 0;

    // After setting this bit, wait the oscillator startup time before enabling
    // the time counter to allow the clock time to stabilize
    RTC->CR |= RTC_CR_OSCE_MASK;
    for (volatile int i=0; i<0x600000; i++);

    //enable seconds interrupts
    RTC->IER |= RTC_IER_TSIE_MASK;

    // enable time counter
    RTC->SR |= RTC_SR_TCE_MASK;


}

int main() {
    error_led = 1;
    rtc_init();

    while (true) {
        wait(1);
        status_led = !status_led;
        printf("%u\n", RTC->TSR);
    }
}
