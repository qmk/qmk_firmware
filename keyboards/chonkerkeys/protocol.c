#include "protocol.h"
#include "light_type.h"
#include "command_type.h"
#include "event_type.h"
#include "event.h"
#include "command.h"
#include <stdio.h>

uint8_t get_key_light_type(uint8_t x, uint8_t y) {
    return mute;
}

void update_light(uint8_t type, uint8_t state) {
    // TODO
    if (type == mute) {
        if (state == 0) {
            SEND_STRING("mute light is off");
        } else if (state == 1) {
            SEND_STRING("mute light is on");
        }
    } else if (type == share_screen) {
        if (state == 0) {
            SEND_STRING("share screen light is off");
        } else if (state == 1) {
            SEND_STRING("share screen light is intermediate");
        } else if (state == 2) {
            SEND_STRING("share screen light is on");
        }
    }
}

const extern uint32_t firmware_version;
void on_get_version() {
    struct event_get_version_response resp;
    resp.version = firmware_version;
    _send_event(event_type_get_version_response, (uint8_t*) &resp);
}

void _get_config_data_writer() {
    const uint8_t layer_count = get_layer_count();
    send_protocol(layer_count);
    for (uint8_t layer = 0; layer < layer_count; ++layer) {
        send_protocol(get_layer_type(layer));
        // QMK origin is top-left, chonkerkeys is bottom-left, invert Y.
        for (int8_t y = MATRIX_ROWS - 1; y >= 0; --y) {
            for (uint8_t x = 0; x < MATRIX_COLS; ++x) {
                send_protocol(get_key_size_and_ordinal(layer, x, y));
                send_protocol(get_key_action_type(layer, x, y));
                _send_uint32(get_key_icon(layer, x, y));
            }
        }
    }
}

#define LAYER_TYPE_SIZE 1
#define KEY_SIZE 6

void on_get_config() {
    const uint8_t layer_count = get_layer_count();
    const uint16_t data_length = 1 + ((LAYER_TYPE_SIZE + (MATRIX_ROWS * MATRIX_COLS * KEY_SIZE)) * layer_count);
    _send_event_raw(event_type_get_config_response, data_length, &_get_config_data_writer);
}

uint32_t command_index = 0;
// Assume little endian
uint8_t command_type = 0;
uint16_t remaining_bytes = 0;
union command_t {
    struct command_update_light update_light;
} command;

const uint8_t index_command_type = 0;
const uint8_t index_length_low_byte = 1;
const uint8_t index_length_high_byte = 2;
const uint8_t index_data = 3;

void try_end_command(void) {
    if (remaining_bytes == 0) {
        _dispatch_command();
        command_index = 0;
        remaining_bytes = 0;
        // TODO: zero memory command
    }
}

void process_protocol(uint8_t c) {
    if (command_index == index_command_type) {
        command_type = c;
        ++command_index;
    } else if (command_index == index_length_low_byte) {
        remaining_bytes = c;
        ++command_index;
    } else if (command_index == index_length_high_byte) {
        remaining_bytes |= c << 8;
        ++command_index;
        // Some command might have no data.
        try_end_command();
    } else if (command_index >= index_data) {
        _parse_data(command_index - index_data, c);
        ++command_index;
        --remaining_bytes;
        try_end_command();
    }
}

void _parse_data(uint8_t index, uint8_t c) {
    // TODO: Is jump table easier to maintain and has smaller binary size?
    if (command_type == command_type_get_version) {
        // No-op
    } else if (command_type == command_type_get_config) {
        // No-op
    } else if (command_type == command_type_connect) {

    } else if (command_type == command_type_update_light) {
        uint8_t* update_light = (uint8_t*) &command.update_light;
        update_light[index] = c;
    }
}

void _send_event(uint8_t event_type, uint8_t* event) {
    send_protocol(event_type);
    if (event_type == event_type_get_version_response) {
        struct event_get_version_response* resp = (struct event_get_version_response*) event;
        _send_uint16(4);
        _send_uint32(resp->version);
    }
}

void _send_event_raw(uint8_t event_type, uint16_t data_length, void(*data_writer)(void)) {
    send_protocol(event_type);
    _send_uint16(data_length);
    data_writer();
}

// Assume little endian.
void _send_uint16(uint16_t buffer) {
    send_protocol(buffer);
    send_protocol(buffer >> 8);
}

// Assume little endian.
void _send_uint32(uint32_t buffer) {
    send_protocol(buffer);
    send_protocol(buffer >> 8);
    send_protocol(buffer >> 16);
    send_protocol(buffer >> 24);
}

void _dispatch_command(void) {
    // TODO: Is jump table easier to maintain and has smaller binary size?
    if (command_type == command_type_get_version) {
        on_get_version();
    } else if (command_type == command_type_get_config) {
        on_get_config();
    } else if (command_type == command_type_connect) {

    } else if (command_type == command_type_update_light) {
        // TODO: Look up light type from key_x and key_y
        uint8_t light_type = get_key_light_type(command.update_light.key_x, command.update_light.key_y);
        update_light(light_type, command.update_light.state);
    }
}
