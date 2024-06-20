#include <string.h>
#include "oryx.h"

rawhid_state_t rawhid_state = {.paired = false, .rgb_control = false};

uint8_t pairing_input_index = 0;

void oryx_error(uint8_t code) {
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_ERROR;
    event[1] = code;
    raw_hid_send(event, RAW_EPSIZE);
}

void oryx_layer_event(void) {
    uint8_t layer;
    uint8_t event[RAW_EPSIZE];
    layer    = get_highest_layer(layer_state);
    event[0] = ORYX_EVT_LAYER;
    event[1] = layer;
    event[2] = ORYX_STOP_BIT;
    raw_hid_send(event, sizeof(event));
}

void pairing_failed_event(void) {
    rawhid_state.paired = false;
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_PAIRING_FAILED;
    event[1] = ORYX_STOP_BIT;
    raw_hid_send(event, sizeof(event));
}

void pairing_success_event(void) {
    rawhid_state.paired = true;
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_PAIRING_SUCCESS;
    event[1] = ORYX_STOP_BIT;
    raw_hid_send(event, sizeof(event));
}

void toggle_smart_layer(void) {
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_TOGGLE_SMART_LAYER;
    event[1] = ORYX_STOP_BIT;
    raw_hid_send(event, sizeof(event));
}

void trigger_smart_layer(void) {
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_TRIGGER_SMART_LAYER;
    event[1] = ORYX_STOP_BIT;
    raw_hid_send(event, sizeof(event));
}

void set_webhid_effect(void) {
#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_oryx_webhid_effect);
    rawhid_state.rgb_control = true;
#endif
}

void clear_webhid_effect(void) {
#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
    // Clear the pattern
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        webhid_leds[i] = (RGB){.r = 0, .g = 0, .b = 0};
    }
    rgb_matrix_reload_from_eeprom();
    rawhid_state.rgb_control = false;
#endif
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t  command = data[0];
    uint8_t *param   = &data[1];

    switch (command) {
        case ORYX_CMD_GET_FW_VERSION: {
            uint8_t event[RAW_EPSIZE];
            uint8_t fw_version_size = sizeof(FIRMWARE_VERSION);
            uint8_t stop[1];

            event[0] = ORYX_EVT_GET_FW_VERSION;
            stop[0]  = ORYX_STOP_BIT;

            memcpy(event + 1, FIRMWARE_VERSION, fw_version_size);
            memcpy(event + fw_version_size, stop, 1);

            raw_hid_send(event, RAW_EPSIZE);
            break;
        }

        case ORYX_GET_PROTOCOL_VERSION: {
            uint8_t event[RAW_EPSIZE];
            event[0] = ORYX_EVT_GET_PROTOCOL_VERSION;
            event[1] = ORYX_PROTOCOL_VERSION;
            event[2] = ORYX_STOP_BIT;

            raw_hid_send(event, RAW_EPSIZE);
            break;
        }

        case ORYX_CMD_PAIRING_INIT:
            pairing_success_event();

        case ORYX_CMD_PAIRING_VALIDATE:
            break; // Keeping this for backwards compatibility with older versions of Wally / Keymapp

        case ORYX_SET_LAYER:
            // The first param's byte is on / off
            // The second param's byte is the layer number
            if (rawhid_state.paired == true) {
                if (param[0] == 0) {
                    layer_off(param[1]);
                } else {
                    layer_move(param[1]);
                }
            }
            break;

        case ORYX_RGB_CONTROL:
#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
            if (param[0] == 0) {
                clear_webhid_effect();
            } else {
                set_webhid_effect();
            }
            uint8_t event[RAW_EPSIZE];
            event[0] = ORYX_EVT_RGB_CONTROL;
            event[1] = rawhid_state.rgb_control;
            raw_hid_send(event, RAW_EPSIZE);
#else
            oryx_error(ORYX_ERR_RGB_MATRIX_NOT_ENABLED);
#endif
            break;

        case ORYX_SET_RGB_LED:
#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
            webhid_leds[param[0]] = (RGB){.r = param[1], .g = param[2], .b = param[3]};
            if (rawhid_state.rgb_control == false) {
                set_webhid_effect();
            }
#else
            oryx_error(ORYX_ERR_RGB_MATRIX_NOT_ENABLED);
#endif
            break;
        case ORYX_SET_RGB_LED_ALL:
#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                webhid_leds[i] = (RGB){.r = param[0], .g = param[1], .b = param[2]};
            }
            if (rawhid_state.rgb_control == false) {
                set_webhid_effect();
            }
#else
            oryx_error(ORYX_ERR_RGB_MATRIX_NOT_ENABLED);
#endif
            break;
        case ORYX_SET_STATUS_LED:
            rawhid_state.status_led_control = true; // Eagerly take control of the status LEDs
            switch (param[0]) {
                case 0:
#ifdef STATUS_LED_1
                    STATUS_LED_1(param[1]);
#else
                    oryx_error(ORYX_ERR_STATUS_LED_OUT_OF_RANGE);
#endif
                    break;
                case 1:
#ifdef STATUS_LED_2
                    STATUS_LED_2(param[1]);
#else
                    oryx_error(ORYX_ERR_STATUS_LED_OUT_OF_RANGE);
#endif
                    break;
                case 2:
#ifdef STATUS_LED_3
                    STATUS_LED_3(param[1]);
#else
                    oryx_error(ORYX_ERR_STATUS_LED_OUT_OF_RANGE);
#endif
                    break;
                case 3:
#ifdef STATUS_LED_4
                    STATUS_LED_4(param[1]);
#else
                    oryx_error(ORYX_ERR_STATUS_LED_OUT_OF_RANGE);
#endif
                    break;
                case 4:
#ifdef STATUS_LED_5
                    STATUS_LED_5(param[1]);
#else
                    oryx_error(ORYX_ERR_STATUS_LED_OUT_OF_RANGE);
#endif
                    break;
                case 5:
#ifdef STATUS_LED_6
                    STATUS_LED_6(param[1]);
#else
                    oryx_error(ORYX_ERR_STATUS_LED_OUT_OF_RANGE);
#endif
                    break;

                default:
                    oryx_error(ORYX_ERR_STATUS_LED_OUT_OF_RANGE);
                    break;
            }
            break;
        case ORYX_UPDATE_BRIGHTNESS: {
#if defined(RGB_MATRIX_ENABLE) && !defined(PROTOCOL_LUFA)
            if (param[0]) {
                rgb_matrix_increase_val_noeeprom();
            } else {
                rgb_matrix_decrease_val_noeeprom();
            }
#else
            oryx_error(ORYX_ERR_RGB_MATRIX_NOT_ENABLED);
#endif
            break;
        }
        case ORYX_STATUS_LED_CONTROL: {
            rawhid_state.status_led_control = param[0];
            uint8_t event[RAW_EPSIZE];
            event[0] = ORYX_EVT_STATUS_LED_CONTROL;
            event[1] = rawhid_state.status_led_control;
            raw_hid_send(event, RAW_EPSIZE);
            break;
        }
        default:
            oryx_error(ORYX_ERR_UNKNOWN_COMMAND);
    }
}

bool process_record_oryx(uint16_t keycode, keyrecord_t *record) {
    // While paired, the keyboard sends keystrokes positions to the host
    if (rawhid_state.paired == true) {
        uint8_t event[RAW_EPSIZE];
        event[0] = record->event.pressed ? ORYX_EVT_KEYDOWN : ORYX_EVT_KEYUP;
        event[1] = record->event.key.col;
        event[2] = record->event.key.row;
        event[3] = ORYX_STOP_BIT;
        raw_hid_send(event, sizeof(event));
    }
    return true;
}

void layer_state_set_oryx(layer_state_t state) {
    if (rawhid_state.paired) {
        uint8_t event[RAW_EPSIZE];
        event[0] = ORYX_EVT_LAYER;
        event[1] = get_highest_layer(state);
        event[2] = ORYX_STOP_BIT;
        raw_hid_send(event, sizeof(event));
    }
}
