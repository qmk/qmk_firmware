#include "mbed.h"
#include "USBSerial.h"

//Virtual serial port over USB
USBSerial serial;
DigitalOut l1(LED1);

int main(void) {
    int i = 0;

    while(1)
    {
        l1 = !l1;
        printf("Hello\r\n");
        serial.printf("I am a virtual serial port: %d\r\n", i++);
        wait(0.1);
    }
}
