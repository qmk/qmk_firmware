#include "mbed.h"
#include "TextLCD.h"

int main() {
    printf("printf to stdout\n");

    // printf to specific peripherals
    Serial pc(USBTX, USBRX);
    pc.printf("Serial(USBTX, USBRX).printf\n");

    TextLCD lcd(p14, p15, p16, p17, p18, p19, p20, "lcd"); // rs, rw, e, d0-d3, name
    lcd.printf("TextLCD.printf\n");

    // change stdout to file
    LocalFileSystem local("local");
    freopen("/local/output.txt", "w", stdout);
    printf("printf redirected to LocalFileSystem\n");
    fclose(stdout);

    // change stdout to LCD
    freopen("/lcd", "w", stdout);
    printf("printf redirected to TextLCD\n");
    fclose(stdout);

    DigitalOut led(LED1);
    while (true) {
        led = !led;
        wait(1);
    }
}
