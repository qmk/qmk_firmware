#pragma once

struct event_get_version_response {
    uint32_t version;
};

struct event_key_down {
    uint8_t layer;
    uint8_t x;
    uint8_t y;
};
