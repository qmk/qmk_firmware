#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum custom_keycodes {
    HSH_TLD = SAFE_RANGE,
    CTRL_A,
    CMD_ALT_C,
    CMD_SFT_L,
    NEW_SAFE_RANGE,
};

enum function_id {
    CMD_TAB_CMD,
    CMD_GRV_CMD
};

void cmd_or_macro(keyrecord_t *record, uint16_t kc_mod, char* macro);

#endif
