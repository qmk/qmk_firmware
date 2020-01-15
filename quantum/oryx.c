#include "oryx.h"

bool oryx_state_live_training_enabled;

bool webusb_receive_oryx(uint8_t *data, uint8_t length) {
    uint8_t command = data[0];
    uint8_t param = data[1];

    switch (command) {
        case ORYX_GET_LAYER:
            oryx_layer_event();
            return true; break;
        case ORYX_CMD_LIVE_TRAINING: {
            uint8_t event[4];
            switch (param) { // 0 for state, 1 for off, 2 for on
                case 0:
                    break;
                case 1:
                    oryx_state_live_training_enabled = false;
                    break;
                case 2:
                    oryx_state_live_training_enabled = true;
                    break;
                default:
                    webusb_error(WEBUSB_STATUS_UNKNOWN_COMMAND);
                    return true;
            }
            event[0] = WEBUSB_STATUS_OK;
            event[1] = WEBUSB_EVT_PAIRED;
            event[2] = oryx_state_live_training_enabled;
            event[3] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
            }
        default:
            return webusb_receive_kb(data, length);

    }
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

bool is_oryx_live_training_enabled(void) {
    return oryx_state_live_training_enabled;
}
