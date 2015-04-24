#include "mbed.h"
#include "TSISensor.h"

int main(void) {
    DigitalOut led(LED_GREEN);
    TSISensor tsi;

    while (true) {
        printf("slider percentage: %f%\r\n", tsi.readPercentage());
        printf("slider distance: %dmm\r\n", tsi.readDistance());
        wait(1);
        led = !led;
    }
}
