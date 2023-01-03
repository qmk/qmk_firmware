#include <string.h>
#include "oryx.h"
#include "eeprom.h"

rawhid_state_t rawhid_state = {.pairing = false, .paired = false};

keypos_t keyboard_pairing_sequence[PAIRING_SEQUENCE_SIZE];
keypos_t host_pairing_sequence[PAIRING_SEQUENCE_SIZE];
uint8_t  pairing_input_index = 0;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t  command   = data[0];
    uint8_t *param     = &data[1];
    uint8_t  cmd_index = 0;

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
            store_pairing_sequence(&keyboard_pairing_sequence[0]);
            break;

        case ORYX_CMD_PAIRING_VALIDATE:
            for (uint8_t i = 0; i < PAIRING_SEQUENCE_SIZE; i++) {
                keypos_t pos;
                pos.col                  = param[cmd_index++];
                pos.row                  = param[cmd_index++];
                host_pairing_sequence[i] = pos;
            }
            pairing_validate_eeprom_handler();
            break;

        case ORYX_SET_LAYER:
            if(rawhid_state.paired == true) {
                layer_clear();
                layer_on(param[0]);
            }
            break;
    }
}

void pairing_validate_eeprom_handler(void) {
    bool    match = false;
    uint8_t event[RAW_EPSIZE];
    uint8_t stored_sequences[sizeof(uint16_t) * PAIRING_SEQUENCE_SIZE * PAIRING_SEQUENCE_NUM_STORED];

    eeprom_read_block(&stored_sequences, (uint8_t *)EECONFIG_SIZE, PAIRING_STORAGE_SIZE);
    match = true;

    if (match == true) {
        event[0]            = ORYX_EVT_PAIRING_SUCCESS;
        rawhid_state.paired = true;

    } else {
        event[0]            = ORYX_EVT_PAIRING_FAILED;
        rawhid_state.paired = false;
    }
    event[1]             = ORYX_STOP_BIT;
    rawhid_state.pairing = false;
    raw_hid_send(event, sizeof(event));
}

bool store_pairing_sequence(keypos_t *pairing_sequence) {
    uint8_t stored_sequences[sizeof(uint16_t) * PAIRING_SEQUENCE_SIZE * PAIRING_SEQUENCE_NUM_STORED];

    eeprom_read_block(&stored_sequences, (uint8_t *)EECONFIG_SIZE, PAIRING_STORAGE_SIZE);

    uint8_t shiftLen = sizeof(&pairing_sequence);

    for (int8_t i = PAIRING_STORAGE_SIZE; i >= 0; i--) {
        if (i > shiftLen) {
            stored_sequences[i] = stored_sequences[i - 1];
        } else {
            stored_sequences[i] = 0;
        }
    }
    eeprom_update_block(stored_sequences, (uint8_t *)EECONFIG_SIZE, PAIRING_STORAGE_SIZE);
    return true;
}

void pairing_init_handler(void) {
    create_pairing_code();
    uint8_t event[RAW_EPSIZE];
    uint8_t event_index  = 0;
    event[event_index++] = ORYX_EVT_PAIRING_INPUT;
    for (uint8_t i = 0; i < PAIRING_SEQUENCE_SIZE; i++) {
        event[event_index++] = keyboard_pairing_sequence[i].col;
        event[event_index++] = keyboard_pairing_sequence[i].row;
    }
    event[event_index++] = ORYX_STOP_BIT;
    rawhid_state.pairing = true;
    raw_hid_send(event, RAW_EPSIZE);
}

bool compare_sequences(keypos_t a[PAIRING_SEQUENCE_SIZE], keypos_t b[PAIRING_SEQUENCE_SIZE]) {
    bool valid = true;
    for (uint8_t i = 0; i < PAIRING_SEQUENCE_SIZE; i++) {
        if (a[i].row != b[i].row) {
            valid = false;
            break;
        }
        if (a[i].col != b[i].col) {
            valid = false;
            break;
        }
    }
    return valid;
}

void pairing_validate_handler() {
    
    uint8_t event[RAW_EPSIZE];
    bool    valid = compare_sequences(keyboard_pairing_sequence, host_pairing_sequence);

    if (valid == true) {
        event[0]            = ORYX_EVT_PAIRING_SUCCESS;
        rawhid_state.paired = true;

    } else {
        event[0]            = ORYX_EVT_PAIRING_FAILED;
        rawhid_state.paired = false;
    }

    event[1]             = ORYX_STOP_BIT;
    rawhid_state.pairing = false;
    raw_hid_send(event, sizeof(event));
}

keypos_t get_random_keypos(void) {
    uint8_t  col = rand() % MATRIX_COLS;
    uint8_t  row = rand() % MATRIX_ROWS;
    keypos_t pos = {.col = col, .row = row};

    uint16_t keycode = keymap_key_to_keycode(0, pos);
    if (keycode >= KC_A && keycode <= KC_SLASH) {
        return pos;
    } else {
        return get_random_keypos();
    }
}

void create_pairing_code(void) {
    for (uint8_t i = 0; i < PAIRING_SEQUENCE_SIZE; i++) {
        keypos_t pos                 = get_random_keypos();
        keyboard_pairing_sequence[i] = pos;
    }
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

bool process_record_oryx(uint16_t keycode, keyrecord_t *record) {
    // In pairing mode, key events are absorbed, and the host pairing sequence is filled.
    // Once filled, the keyboard and host sequence are compaired, pairing state set to false
    // and the proper pairing validation event is sent to the host
    if (rawhid_state.pairing == true) {
        // The host pairing sequence is filled on key up only
        if (!record->event.pressed) {
            if (pairing_input_index < PAIRING_SEQUENCE_SIZE) {
                host_pairing_sequence[pairing_input_index++] = record->event.key;
                pairing_key_input_event();
            }
            wait_ms(1000);
            if (pairing_input_index == PAIRING_SEQUENCE_SIZE) {
                rawhid_state.pairing = false;
                pairing_input_index  = 0;
                pairing_validate_handler();
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
