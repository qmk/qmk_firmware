#include "oryx.h"

bool webusb_state_live_training_enabled;

bool webusb_receive_oryx(uint8_t *data, uint8_t length) {
    uint8_t command = data[0];

    switch (command) {
        case ORYX_GET_LAYER:
            oryx_layer_event();
            return true; break;

    }

    return false;
}


void oryx_layer_event(void) {
    uint8_t layer;
    uint8_t event[4];
    layer = get_highest_layer(layer_state);
#ifdef WEBUSB_ENABLE
    event[0] = WEBUSB_STATUS_OK;
    event[1] = ORYX_EVT_LAYER;
    event[2] = layer;
    event[3] = WEBUSB_STOP_BIT;
    webusb_send(event, sizeof(event));
#endif
}
