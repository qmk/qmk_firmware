#pragma once

#include "edvorakjp.h"
/*
 * enum custom_keycodes {
 *   KC_LOCK = NEW_SAFE_RANGE,
 * };
 */

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define __KC_TRNS_x4__ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
#define __KC_TRNS_x6__ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
