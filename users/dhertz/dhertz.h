#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define SRCH_CTL CTL_T(KC_F19)
#define LYR_SPC LT(1, KC_SPC)
#define NC_CTL CTL_T(KC_F18)

enum custom_keycodes {
    HSH_TLD = SAFE_RANGE,
    CTRL_A,
    CMD_ALT_C,
    CMD_SFT_L,
    ISO_COUNTRY_CODE,
    CMD_TAB_CMD,
    CMD_GRV_CMD,
    NEW_SAFE_RANGE,
};

void mod_or_mod_with_macro(keyrecord_t *record, uint16_t kc_mod, char* cmd_or_macro);

#endif
