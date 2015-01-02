//#include "mbed.h"
#include "MK20D5.h"
#include "wait.h"
#include "gpio_api.h"
#include "PinNames.h"


//DigitalOut led(PTA19);

int main() {
    gpio_t led;
    gpio_init_out(&led, PTA19);
    while(1) {
        gpio_write(&led, 1);
        wait_ms(500);
        gpio_write(&led, 0);
        wait_ms(500);
    }
/*
    SIM->SCGC6 |= SIM_SCGC5_PORTA_MASK;
    PORTA->PCR[19] = PORT_PCR_SRE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_MUX(1);
    PTA->PDDR |= (1<<19);
    PTA->PSOR |= (1<<19);
    while(1) {
        PTA->PTOR |= (1<<19);
        wait_ms(500);
    }
*/
}
