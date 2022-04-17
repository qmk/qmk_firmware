#pragma once
#include QMK_KEYBOARD_H
#include "tap_dances.h"
#include "caps_word.h"

typedef enum {
    WLX,
    OSX
} os_type;

enum layers {
    QWERTY,
    QWERTY_PG,
    WORKMAN,
    WORKMAN_PG,
    SYMBOLS,
    GAMES
};

typedef enum {
    COPY,
    CUT,
    PASTE,
    SAVE,
    UNDO,
    REDO,
    NEW_TAB,
    LAST_TAB,
    FIND,
    FIND_ALL,
    REPLACE,
    REPLACE_ALL
} shortcut;

os_type get_current_os(void);
void set_current_os(os_type val);
uint16_t get_os_shortcut(shortcut intended);
