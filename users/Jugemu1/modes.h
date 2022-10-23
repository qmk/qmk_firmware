#pragma once

#include "jugemu.h"

typedef enum {
    MODE_WINDOWS,
    MODE_MAC,
    MODE_LAST,          // keep this last
} modes;

modes get_mode(void);
void set_mode(modes new_mode);
void cycle_mode(void);
const char *get_current_mode_name(void);
void init_mode(void);
