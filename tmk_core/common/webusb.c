#include "webusb.h"
#include "wait.h"

webusb_state_t webusb_state = {
  .paired = false,
  .pairing = false,
};

void webusb_receive(uint8_t *data, uint8_t length) {
    uint8_t command = data[0];

    if(command == WEBUSB_CMD_PAIR && webusb_state.pairing == true) {
        uint8_t event[3];
        webusb_state.pairing = false;
        webusb_state.paired = true;
        event[0] = WEBUSB_STATUS_OK;
        event[1] = WEBUSB_EVT_PAIRED;
        event[2] = WEBUSB_STOP_BIT;
        webusb_send(event, sizeof(event));
        return;
    }

    if(webusb_state.paired == true) {
        switch(command) {
          //Handle commands in here
        }
    } else {
        webusb_error(WEBUSB_STATUS_NOT_PAIRED);
    }
};

void webusb_error(uint8_t code) {
    uint8_t buffer[1];
    buffer[0] = code;
    webusb_send(buffer, 1);
}
