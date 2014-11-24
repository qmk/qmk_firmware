#include "mbed.h"
#include "action.h"
#include "keycode.h"
#include "host.h"
#include "mbed_driver.h"
 

// Button and LEDs of LPC11U35 board
DigitalIn isp(P0_1);            // ISP button
DigitalOut led_red(P0_20);
DigitalOut led_green(P0_21);


int main(void) {
    isp.mode(PullUp);
    led_red = 1;
    led_green = 0;

    host_set_driver(&mbed_driver);

    bool last_isp = isp;
    while (1) {
        if (last_isp == isp) continue;
        last_isp = isp;
        if (last_isp == 0) {
            led_red = 0;    // on
            register_code(KC_A);
        } else {
            led_red = 1;    // off
            unregister_code(KC_A);
        }
    }
}
