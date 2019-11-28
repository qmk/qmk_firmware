#include <string.h>
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

    if(command == WEBUSB_GET_LANDING_PAGE) {
        uint8_t lp_size = sizeof(WEBUSB_LANDING_PAGE_URL);
        uint8_t url[lp_size];
        memcpy(url, WEBUSB_LANDING_PAGE_URL, lp_size);

        uint8_t event[2];
        event[0] = WEBUSB_STATUS_OK;
        event[1] = WEBUSB_EVT_LANDING_PAGE;

        uint8_t stop[1];
        stop[0] = WEBUSB_STOP_BIT;

        webusb_send(event, sizeof(event));
        webusb_send(url, lp_size);
        webusb_send(stop, 1);
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
