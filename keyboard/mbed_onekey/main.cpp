#include "mbed.h"
#include "HIDKeyboard.h"
#include "debug.h"
 
/*
//#define DEBUG 
#ifdef DEBUG
Serial ser(UART_TX, UART_RX);
#define dprintf(fmt, ...)	    ser.printf(fmt, ## __VA_ARGS__)
#else
#define dprintf(fmt, ...)
#endif
*/


// button and LEDs
DigitalIn isp(P0_1);
DigitalOut led_red(P0_20);
DigitalOut led_green(P0_21);

//USBKeyboard
HIDKeyboard keyboard;
 

int main(void) {
    //isp.mode(PullUp);
    //led_red = 0;
    //led_green = 0;
    debug_enable = true;
    dprintf("HIDKeyboard:\n");
    print("aaa");

    report_keyboard_t report = { 2, 0, 4, }; //a
    report_keyboard_t report_off = { 0 };
    while (1) {
        //keyboard.mediaControl(KEY_VOLUME_DOWN);
        //keyboard.printf("Hello World from Mbed\r\n");
        //keyboard.keyCode('s', KEY_CTRL);
        //keyboard.keyCode(KEY_CAPS_LOCK);

        //led_green = !led_green;
        //leds = keyboard.lockStatus();
        //ser.putc(ser.getc());

        if (isp == 0) {
            led_red = 0;    // on
            keyboard.sendReport(report);
        } else {
            led_red = 1;    // off
            keyboard.sendReport(report_off);
        }
        led_green = !led_green;
        //wait(0.5);
    }
}
