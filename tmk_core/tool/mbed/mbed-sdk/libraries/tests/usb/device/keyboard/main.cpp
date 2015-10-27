#include "mbed.h"
#include "USBKeyboard.h"

//LED1: NUM_LOCK
//LED2: CAPS_LOCK
//LED3: SCROLL_LOCK
BusOut leds(LED1, LED2, LED3);

//USBKeyboard
USBKeyboard keyboard;

int main(void) {
    while (1) {
        keyboard.mediaControl(KEY_VOLUME_DOWN);
        keyboard.printf("Hello World from Mbed\r\n");
        keyboard.keyCode('s', KEY_CTRL);
        keyboard.keyCode(KEY_CAPS_LOCK);
        leds = keyboard.lockStatus();
        wait(1);
    }
}
