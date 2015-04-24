#include "mbed.h"

Serial pc(USBTX, USBRX);

#if defined(TARGET_LPC4088)
Serial uart(P4_22, P4_23);
#elif defined(TARGET_MAXWSNENV)
Serial uart(P0_1, P0_0);
#else
Serial uart(p9, p10);
#endif

DigitalOut led1(LED1);
DigitalOut led2(LED2);

// This function is called when a character goes into the RX buffer.
void rxCallback(void) {
    led1 = !led1;
    pc.putc(uart.getc());
}


int main() {
    // Use a deliberatly slow baud to fill up the TX buffer
    uart.baud(1200);
    uart.attach(&rxCallback, Serial::RxIrq);

    printf("Starting test loop:\n");
    wait(1);

    int c = 'A';
    for (int loop = 0; loop < 512; loop++) {
        uart.printf("%c", c);
        c++;
        if (c > 'Z') c = 'A';
    }

    while (true) {
        led2 = !led2;
        wait(1);
    }
}
