#include "protocol.h"
#include "light_type.h"
#include "command_type.h"
#include "event_type.h"
#include "event.h"
#include "command.h"
#include "rgb_strands.h"
#include "color.h"
#include <stdio.h>
#include <string.h>

uint8_t get_key_light_type(uint8_t x, uint8_t y) {
    return mute;
}

void update_light(uint8_t type, uint8_t state) {
    // TODO: need to figure out the RGB strand for the light type
    //uint8_t strand = key_strand[0][0];
    uint8_t strand = 0;

    if (type == mute) {
        if (state == 0) {
            // off
            rgb_strand_set_color(strand, HSV_OFF);
        } else if (state == 1) {
            // mute
            rgb_strand_set_color(strand, HSV_RED);
        } else if (state == 2) {
            // unmute
            rgb_strand_set_color(strand, HSV_GREEN);
        }
    } else if (type == share_screen) {
        if (state == 0) {
            // off
            rgb_strand_set_color(strand, HSV_OFF);
        } else if (state == 1) {
            // blinking
            const rgb_strand_anim_config_t *dcfg = get_default_rgb_strand_anim_config(RGB_STRAND_EFFECT_BLINKY);
            rgb_strand_anim_config_t cfg;
            memcpy(&cfg, dcfg, sizeof(rgb_strand_anim_config_t));
            cfg.num_times = 0; // blink forever until shared
            rgb_strand_animation_start(strand, RGB_STRAND_EFFECT_BLINKY, &cfg, RGB_STRAND_ANIM_STATE_START);
        } else if (state == 2) {
            // screen sharing
            rgb_strand_set_color(strand, HSV_GREEN);
        }
    }
}

const extern uint32_t firmware_version;
void on_get_version() {
    struct event_get_version_response resp;
    resp.version = firmware_version;
    _send_event(event_type_get_version_response, (uint8_t*) &resp);
}

void _get_config_data_writer(void* user_data) {
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
    _send_event_raw(event_type_get_config_response, data_length, &_get_config_data_writer, 0);
}

void on_reset() {
    reset_keyboard();
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

void _key_down_data_writer(void* user_data) {
    struct event_key_down* key_down = (struct event_key_down*) user_data;
    send_protocol(key_down->layer);
    send_protocol(key_down->x);
    send_protocol(key_down->y);
}

void key_down(uint8_t layer, uint8_t x, uint8_t y) {
    struct event_key_down key_down;
    key_down.layer = layer;
    key_down.x = x;
    key_down.y = y;
    _send_event_raw(event_type_key_down, 3, &_key_down_data_writer, &key_down);
}

void _parse_data(uint8_t index, uint8_t c) {
    // TODO: Is jump table easier to maintain and has smaller binary size?
    if (command_type == command_type_get_version) {
        // No-op
    } else if (command_type == command_type_get_config) {
        // No-op
    } else if (command_type == command_type_connect) {
        // No-op
    } else if (command_type == command_type_reset) {
        // No-op
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

void _send_event_raw(uint8_t event_type, uint16_t data_length, void(*data_writer)(void*), void* user_data) {
    send_protocol(event_type);
    _send_uint16(data_length);
    data_writer(user_data);
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
        on_connected();
    } else if (command_type == command_type_reset) {
        on_reset();
    } else if (command_type == command_type_update_light) {
        // TODO: Look up light type from key_x and key_y
        uint8_t light_type = get_key_light_type(command.update_light.key_x, command.update_light.key_y);
        update_light(light_type, command.update_light.state);
    }
}
