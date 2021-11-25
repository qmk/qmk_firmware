#include "protocol.h"
#include "light_type.h"
#include "command_type.h"
#include "command.h"

uint8_t get_key_light_type(uint8_t x, uint8_t y);

void update_light(uint8_t type, uint8_t state) {
    // TODO
    if (type == mute) {

    } else if (type == share_screen) {

    }
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
    if (remaining_bytes > 0) {
        ++command_index;
    } else {
        _dispatch_command();
        command_index = 0;
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
        // TODO
    } else if (command_type == command_type_get_config) {

    } else if (command_type == command_type_connect) {

    } else if (command_type == command_type_update_light) {
        uint8_t* update_light = (uint8_t*) &command.update_light;
        update_light[index] = c;
    }
}

void _dispatch_command(void) {
    // TODO: Is jump table easier to maintain and has smaller binary size?
    if (command_type == command_type_get_version) {
        // TODO
    } else if (command_type == command_type_get_config) {

    } else if (command_type == command_type_connect) {

    } else if (command_type == command_type_update_light) {
        // TODO: Look up light type from key_x and key_y
        uint8_t light_type = get_key_light_type(command.update_light.x, command.update_light.y);
        update_light(light_type, command.update_light.state);
    }
}
