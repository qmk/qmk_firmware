#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// keymap needs oneshot functionality
#undef NO_ACTION_ONESHOT

#undef IS_COMMAND
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#endif