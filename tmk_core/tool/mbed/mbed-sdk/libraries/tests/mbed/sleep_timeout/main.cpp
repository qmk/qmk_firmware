#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
Timeout to1;
Timeout to2;

void led1_on() {
    led1 = !led1;
    printf("led1\n\r");
    fflush(stdout);
}
void led2_on() {
    led2 = !led2;
    printf("led2\n\r");
    fflush(stdout);
}

int main() {
    led1 = 0;
    led2 = 0;
    to1.attach_us(led1_on, 1000000);
    to2.attach_us(led2_on, 2000000);
    while (1) {
        printf("Entering sleep.\n");
        sleep();
    }
}
