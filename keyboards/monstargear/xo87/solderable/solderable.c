#include "usb_descriptor.h"
#include "solderable.h"
#include "quantum.h"

#define noLed {255,255}

#define ledSollSP (80+3)
#define ledNumSP (80+7)
#define ledCapSP (80+8)


void backlight_init_ports(void) {
    // Optional - runs on startup
    //   Usually you want to configure pins here
    setPinOutput(Lseg0);
    setPinOutput(Lseg1);
    setPinOutput(Lseg2);
    setPinOutput(Lseg3);
    setPinOutput(Lseg4);
    setPinOutput(Lseg5);
    setPinOutput(Lcom0);
    setPinOutput(Lcom1);
    setPinOutput(Lcom2);
    setPinOutput(Lcom3);
    setPinOutput(Lcom4);
    setPinOutput(Lcom5);
    setPinOutput(Lcom6);
    setPinOutput(Lcom7);
    setPinOutput(Lcom8);
    setPinOutput(Lcom9);
    setPinOutput(Lcom10);
    setPinOutput(Lcom11);
    setPinOutput(Lcom12);
    setPinOutput(Lcom13);
    setPinOutput(Lcom14);
    setPinOutput(Lcom15);
}

void backlight_set(uint8_t level) {
    // Optional - runs on level change
    //   Usually you want to respond to the new value
}

void backlight_task(void) {
    // Optional - runs periodically
    //   Note that this is called in the main keyboard loop,
    //   so long running actions here can cause performance issues
    // This is a temporary workaround to get the status LEDs working until we can figure out the LED matrix
    led_t host_leds = host_keyboard_led_state();
    if (host_leds.scroll_lock) {
    writePinHigh(Lcom3);
    writePinHigh(Lseg5);
    } else {
    writePinLow(Lcom3);
    }
    if (host_leds.num_lock) {
    writePinHigh(Lcom7);
    writePinHigh(Lseg5);
    } else {
    writePinLow(Lcom7);
    }
    if (host_leds.caps_lock) {
    writePinHigh(Lcom8);
    writePinHigh(Lseg5);
    } else {
    writePinLow(Lcom8);
    }

}

