#include "diverge3.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;
qk_tap_dance_action_t tap_dance_actions[] = {};

#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#include "dist/_keymap.c"
