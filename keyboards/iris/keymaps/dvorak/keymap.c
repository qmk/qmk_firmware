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

// Tap dances
enum {
  BACKSLASH_CAPS = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [BACKSLASH_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_BSLASH, KC_CAPSLOCK)
};

#include "dist/_keymap.c"
