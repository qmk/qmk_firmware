#include "webusb.h"
#include "wait.h"

webusb_state_t webusb_state = {
  .paired = false,
  .pairing = false,
};

void webusb_set_pairing_state() {
    webusb_state.pairing = true;
    uint8_t tick = 0;
    do {
        tick++;
        wait_ms(1000);
        //TODO Blink some leds
    } while(webusb_state.paired == false && tick <= 30);
    webusb_state.pairing = false;
}

void webusb_error(uint8_t code) {
    uint8_t buffer[1];
    buffer[0] = code;
    webusb_send(buffer, 1);
}
