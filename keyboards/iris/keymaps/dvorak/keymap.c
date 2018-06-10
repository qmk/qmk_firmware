#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Layers
#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
	DVORAK = SAFE_RANGE,
	LOWER,
	RAISE,
	ADJUST
};

#include "dist/_keymap.c"
