#pragma once

enum poly_flag {
    STATUS_DISP_ON      = 1 << 0,
    IDLE_TRANSITION     = 1 << 1,
    DISP_IDLE           = 1 << 2,
    DEAD_KEY_ON_WAKEUP  = 1 << 3,

    DBG_ON              = 1 << 4,
    MODS_AS_TEXT        = 1 << 5,
    MORE_TEXT           = 1 << 6,
    RGB_ON              = 1 << 7
};

enum overlay_flag {
    DISPLAY_OVERLAYS    = 1 << 0,
    CLEAR_LEFT_TOP      = 1 << 1,
    CLEAR_LEFT_BOTTOM   = 1 << 2,
    CLEAR_RIGHT_TOP     = 1 << 3,
    CLEAR_RIGHT_BOTTOM  = 1 << 4,
    RESET_BUFFERS       = 1 << 5,
};

bool test_flag(uint8_t flags, uint8_t f) ;

uint8_t flag_on(uint8_t flags, uint8_t f) ;

uint8_t flag_off(uint8_t flags, uint8_t f);

uint8_t toggle_flag(uint8_t flags, uint8_t f);

uint8_t set_flag(uint8_t flags, uint8_t f, bool set);

bool has_flag_changed(uint8_t flags1, uint8_t flags2, uint8_t f);

bool flag_turned_off(uint8_t flags1, uint8_t flags2, uint8_t f);

bool flag_turned_on(uint8_t flags1, uint8_t flags2, uint8_t f);
