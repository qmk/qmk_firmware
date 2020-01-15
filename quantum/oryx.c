#include "oryx.h"

bool oryx_state_live_training_enabled;

bool webusb_receive_oryx(uint8_t *data, uint8_t length) {
    uint8_t command = data[0];
    uint8_t *param   = &(data[1]);

    switch (command) {
        case ORYX_GET_LAYER:
            oryx_layer_event();
            return true;
        case ORYX_CMD_LIVE_TRAINING: {
            uint8_t event[4];
            switch (param[0]) {  // 0 for state, 1 for off, 2 for on
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
            event[1] = ORYX_EVT_LIVE_TRAINING;
            event[2] = oryx_state_live_training_enabled;
            event[3] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_GET_KEYCODE: {
            uint8_t event[5];
            // layer, row, col
            uint16_t keycode = dynamic_keymap_get_keycode(param[0], param[1], param[2]);
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_GET_KEYCODE;
            event[2] = keycode >> 8;
            event[3] = keycode & 0xFF;
            event[4] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_SET_KEYCODE: {
            uint8_t event[5];
            dynamic_keymap_set_keycode(param[0], param[1], param[2], (param[3] << 8) | param[4]);
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_SET_KEYCODE;
            event[2] = param[3];
            event[3] = param[4];
            event[4] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_KEYMAP_RESET: {
            uint8_t event[3];
            dynamic_keymap_reset();
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_KEYMAP_RESET;
            event[2] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_GET_BUFFER: {
            uint16_t offset = (param[0] << 8) | param[1];
            uint16_t size   = param[2];  // size <= 28
            uint8_t event[size+3];
            uint8_t i;
            dynamic_keymap_get_buffer(offset, size, &param[3]);
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_GET_BUFFER;
            for (i = 0; i < size; i++) {
                event[i+2] = param[i];
            }
            event[i+2] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_SET_BUFFER: {
            uint16_t offset = (param[0] << 8) | param[1];
            uint16_t size   = param[2];  // size <= 28
            uint8_t event[3];
            dynamic_keymap_set_buffer(offset, size, &param[3]);
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_SET_BUFFER;
            event[2] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_GET_LAYER_COUNT: {
            uint8_t event[4];
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_GET_LAYER_COUNT;
            event[2] = dynamic_keymap_get_layer_count();
            event[3] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_GET_MACRO_COUNT: {
            uint8_t event[4];
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_GET_MACRO_COUNT;
            event[2] = dynamic_keymap_macro_get_count();
            event[3] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_GET_MACRO_BUFFER_SIZE: {
            uint16_t size   = dynamic_keymap_macro_get_buffer_size();
            uint8_t event[5];
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_GET_MACRO_BUFFER_SIZE;
            event[2] = size >> 8;
            event[3] = size & 0xFF;
            event[4] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_GET_MACRO_BUFFER: {
            uint16_t offset = (param[0] << 8) | param[1];
            uint16_t size   = param[2];  // size <= 28
            uint8_t event[size+3];
            uint8_t i;
            dynamic_keymap_macro_get_buffer(offset, size, &param[3]);
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_GET_MACRO_BUFFER;
            for (i = 0; i < size; i++) {
                event[i+2] = param[i];
            }
            event[i+2] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_SET_MACRO_BUFFER: {
            uint16_t offset = (param[0] << 8) | param[1];
            uint16_t size   = param[2];  // size <= 28
            dynamic_keymap_macro_set_buffer(offset, size, &param[3]);
            uint8_t event[3];
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_SET_MACRO_BUFFER;
            event[2] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_MACRO_RESET: {
            uint8_t event[3];
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_MACRO_RESET;
            event[2] = WEBUSB_STOP_BIT;
            dynamic_keymap_macro_reset();
            webusb_send(event, sizeof(event));
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_EEPROM_RESET: {
            uint8_t event[3];
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_EEPROM_RESET;
            event[2] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            eeconfig_init();
            return true;
        }
        case ORYX_CMD_LIVE_UPDATE_KEYBOARD_RESET: {
            uint8_t event[3];
            event[0] = WEBUSB_STATUS_OK;
            event[1] = ORYX_EVT_LIVE_UPDATE_KEYBOARD_RESET;
            event[2] = WEBUSB_STOP_BIT;
            webusb_send(event, sizeof(event));
            reset_keyboard();
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

bool is_oryx_live_training_enabled(void) { return oryx_state_live_training_enabled; }
