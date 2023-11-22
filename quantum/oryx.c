#include <string.h>
#include "oryx.h"
#ifdef KEYBOARD_voyager
#    include "voyager.h"
#endif

rawhid_state_t rawhid_state = {.pairing = false, .paired = false};

uint8_t  pairing_input_index = 0;

void oryx_error(uint8_t code) {
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_ERROR;
    event[1] = code;
    raw_hid_send(event, RAW_EPSIZE);
}

void get_pairing_code(keypos_t positions[], int size) {
    const char *version = FIRMWARE_VERSION;

    // Initialize all positions to {1, 1}
    for (int i = 0; i < size; ++i) {
        positions[i].col = 1;
        positions[i].row = 1;
    }

    // Find the position of '/'
    const char *slash_pos = strchr(version, '/');
    int max_index = (slash_pos != NULL) ? (slash_pos - version) : strlen(version);
    max_index = (max_index / 2 < size) ? max_index / 2 : size;

    for (int i = 0; i < max_index; ++i) {
        positions[i].col = version[i * 2] % ORYX_PAIRING_MAX_INDEX + 1;
        positions[i].row = version[i * 2 + 1] % ORYX_PAIRING_MAX_INDEX + 1;
    }
}

void pairing_init_handler(void) {
    uint8_t event[RAW_EPSIZE];
    uint8_t event_index  = 0;

    keypos_t positions[PAIRING_SEQUENCE_SIZE];
    get_pairing_code(positions, PAIRING_SEQUENCE_SIZE);

    event[event_index++] = ORYX_EVT_PAIRING_INPUT;
    for (uint8_t i = 0; i < PAIRING_SEQUENCE_SIZE; i++) {
        event[event_index++] = positions[i].col;
        event[event_index++] = positions[i].row;
    }
    event[event_index++] = ORYX_STOP_BIT;

    rawhid_state.pairing = true;
    raw_hid_send(event, RAW_EPSIZE);
}

void pairing_key_input_event(void) {
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_PAIRING_KEY_INPUT;
    raw_hid_send(event, sizeof(event));
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
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_PAIRING_FAILED;
    event[1] = ORYX_STOP_BIT;
    raw_hid_send(event, sizeof(event));
}

void pairing_success_event(void) {
    uint8_t event[RAW_EPSIZE];
    event[0] = ORYX_EVT_PAIRING_SUCCESS;
    event[1] = ORYX_STOP_BIT;
    raw_hid_send(event, sizeof(event));
}

bool pairing_key_input_handler(keypos_t pos) {
    keypos_t positions[PAIRING_SEQUENCE_SIZE];
    get_pairing_code(positions, PAIRING_SEQUENCE_SIZE);
    keypos_t key = positions[pairing_input_index];

    if (pos.col != key.col || pos.row != key.row) {
        rawhid_state.pairing = false;
        pairing_input_index  = 0;
        pairing_failed_event();
        return false;
    } else {
        pairing_input_index++;
        pairing_key_input_event();
        return true;
    }
}

void pairing_validate_handler(uint8_t *param) {
    bool valid = true;
    uint8_t cmd_index = 0;
    keypos_t positions[PAIRING_SEQUENCE_SIZE];
    get_pairing_code(positions, PAIRING_SEQUENCE_SIZE);
    for (uint8_t i = 0; i < PAIRING_SEQUENCE_SIZE; i++) {
        keypos_t pos;
        pos.col                  = param[cmd_index++];
        pos.row                  = param[cmd_index++];
        if (pos.col != positions[i].col || pos.row != positions[i].row) {
            rawhid_state.pairing = false;
            pairing_failed_event();
            break;
        }
    }
    if (valid) {
        rawhid_state.pairing = false;
        rawhid_state.paired  = true;
        pairing_input_index  = 0;
        pairing_success_event();
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t  command   = data[0];
    uint8_t *param     = &data[1];

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

        case ORYX_CMD_PAIRING_INIT:
            pairing_init_handler();
            break;

        case ORYX_CMD_PAIRING_VALIDATE:
            pairing_validate_handler(param);
            break;

        case ORYX_SET_LAYER:
            if (rawhid_state.paired == true) {
                layer_clear();
                layer_on(param[0]);
            }
            break;

        case ORYX_RGB_CONTROL:
#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
            if (param[0] == 0) {
                rgb_matrix_reload_from_eeprom();
                rawhid_state.rgb_control = false;
            } else {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_oryx_webhid_effect);
                rawhid_state.rgb_control = true;
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
#else
            oryx_error(ORYX_ERR_RGB_MATRIX_NOT_ENABLED);
#endif
            break;
        case ORYX_SET_STATUS_LED:
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
        case ORYX_UPDATE_BRIGHTNESS:
#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
            if (param[0]) {
                rgb_matrix_increase_val_noeeprom();
            } else {
                rgb_matrix_decrease_val_noeeprom();
            }
#else
            oryx_error(ORYX_ERR_RGB_MATRIX_NOT_ENABLED);
#endif
            break;
        default:
            oryx_error(ORYX_ERR_UNKNOWN_COMMAND);
    }
}


bool process_record_oryx(uint16_t keycode, keyrecord_t *record) {
    // In pairing mode, key events are absorbed, and the host pairing sequence is filled.
    // Once filled, the keyboard and host sequence are compaired, pairing state set to false
    // and the proper pairing validation event is sent to the host
    if (rawhid_state.pairing == true) {
        // The host pairing sequence is filled on key up only
        if (!record->event.pressed) {
            if (pairing_input_index < PAIRING_SEQUENCE_SIZE) {
                pairing_key_input_handler(record->event.key);
            }
            wait_ms(1000);
            if (pairing_input_index == PAIRING_SEQUENCE_SIZE) {
                rawhid_state.pairing = false;
                rawhid_state.paired  = true;
                pairing_input_index  = 0;
                pairing_success_event();
            }
        }
        return false;
    }
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
        wait_ms(50);
        uint8_t event[RAW_EPSIZE];
        event[0] = ORYX_EVT_LAYER;
        event[1] = get_highest_layer(state);
        event[2] = ORYX_STOP_BIT;
        raw_hid_send(event, sizeof(event));
    }
}
