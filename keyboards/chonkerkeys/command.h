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
struct command_update_light {
    uint8_t key_x;
    uint8_t key_y;
    uint8_t state;
};