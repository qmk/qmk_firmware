#include "quantum.h"
#include <string.h>
#include "webusb.h"
#include "wait.h"

webusb_state_t webusb_state = {
  .paired = false,
  .pairing = false,
};

__attribute__((weak)) bool webusb_receive_quantum(uint8_t *data, uint8_t length) { return false; }

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

    if(command == WEBUSB_CMD_GET_FW_VERSION) {
        // Landing page + packet headers(2) + stop bit(1)
        uint8_t lp_size = sizeof(FIRMWARE_VERSION) + 3;
        uint8_t url[lp_size];

        uint8_t event[2];
        event[0] = WEBUSB_STATUS_OK;
        event[1] = WEBUSB_EVT_FW_VERSION;

        uint8_t stop[1];
        stop[0] = WEBUSB_STOP_BIT;

        memcpy(url, event, 2);
        memcpy(url + 2, FIRMWARE_VERSION, sizeof(FIRMWARE_VERSION));
        memcpy(url + 2 + sizeof(FIRMWARE_VERSION), stop, 1);
        webusb_send(url, lp_size);
        return;
    }

    if(webusb_state.paired == true) {
        if (!webusb_receive_quantum(data, length)) {
            webusb_error(WEBUSB_STATUS_UNKNOWN_COMMAND);
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
