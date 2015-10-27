#include "mbed.h"
#include "USBMouseKeyboard.h"

//LED1: NUM_LOCK
//LED2: CAPS_LOCK
//LED3: SCROLL_LOCK
BusOut leds(LED1, LED2, LED3);

//USBMouseKeyboard
USBMouseKeyboard key_mouse;

int main(void) {
    while (1) {
        key_mouse.mediaControl(KEY_VOLUME_DOWN);
        key_mouse.printf("Hello World from Mbed\r\n");
        key_mouse.keyCode('s', KEY_CTRL);
        key_mouse.move(20, 0);
        key_mouse.keyCode(KEY_SCROLL_LOCK);
        leds = key_mouse.lockStatus();
        wait(1);
    }
}
