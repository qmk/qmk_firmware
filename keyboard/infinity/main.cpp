//#include "mbed.h"
#include "MK20D5.h"
#include "wait.h"
#include "gpio_api.h"
#include "PinNames.h"


int main() {
    gpio_t led;
    gpio_init_out(&led, PTA19);
    while(1) {
        wait_ms(500);
        uint32_t delay = 0xf;
        while (delay--) {
            uint32_t delay2 = 0xffff;
            while (delay2--) ;
        }
        gpio_write(&led, !gpio_read(&led));
    }
}
