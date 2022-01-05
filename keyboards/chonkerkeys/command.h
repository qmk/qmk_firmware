#pragma once

struct command_get_version {
    // no data
};
struct command_get_config {
    // no data
};
struct command_connect {
    // no data
};
struct command_reset {
    // no data
};
struct command_set_led {
    uint8_t type;
    uint8_t key_x;
    uint8_t key_y;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    union animation_data_t {
        uint8_t blink_frequency;
        uint8_t momentary_duration_10ms;
    } animation_data;
};
