#include "mbed.h"
#include "SRF08.h"

DigitalOut led(LED1);

SRF08 srf08(p28, p27, 0xE0); // SDA, SCL pin and I2C address

int main() {
    printf("started\n");
    while (1) {
       printf("Measured range : %.2f cm\n",srf08.read());
       wait(1.0);
       led = !led;
    }
}
