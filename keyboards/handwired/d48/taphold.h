#pragma once

#include "quantum.h"

typedef enum taphold_mode_t {
    TAPHOLD_LAYER,
    TAPHOLD_MOD
} taphold_mode_t;

typedef struct taphold_t {
    uint16_t key;
    uint32_t time;
    taphold_mode_t mode;
    uint16_t shortAction;
    uint16_t longAction;
    keypos_t keypos;
    // We store key pos to properly release the key
    // even when a different layer is active and the key has a different action now
} taphold_t;

extern taphold_t taphold_config[];
extern uint16_t taphold_config_size;
// Dual keys tap/hold timeout.
// If key is tapped for less than this value, send key in addition to primary action after completing the action.
extern uint32_t taphold_timeout;

bool taphold_process(uint16_t keycode, keyrecord_t *record);
