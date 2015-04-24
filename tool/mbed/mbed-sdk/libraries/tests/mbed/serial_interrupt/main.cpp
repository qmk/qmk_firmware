#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);

Serial computer(USBTX, USBRX);

// This function is called when a character goes into the TX buffer.
void txCallback() {
    led1 = !led1;
}

// This function is called when a character goes into the RX buffer.
void rxCallback() {
    led2 = !led2;
    computer.putc(computer.getc());
}

int main() {
    printf("start test\n");
    computer.attach(&txCallback, Serial::TxIrq);
    computer.attach(&rxCallback, Serial::RxIrq);
    while (true) {
        wait(1);
    }
}
