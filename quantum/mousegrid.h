#pragma once

#include <stdint.h>

#include "action.h"

// Directional grid of 3x3 by default. But 2x2 or 3x2 should also work.
#ifndef MG_HORIZONTAL_GRID
#    define MG_HORIZONTAL_GRID 3
#endif
#ifndef MG_VERTICAL_GRID
#    define MG_VERTICAL_GRID 3
#endif

// Stop zooming in once we reach this scale.
#ifndef MG_MIN_SCALE
#    define MG_MIN_SCALE 0.01
#endif
// Scale to set for MG_NEAR.
#ifndef MG_LOCAL_SCALE
#    define MG_LOCAL_SCALE 0.2
#endif

// Rather than to zoom in to precisely 1/3 per dimension, leave a little bit of
// overlap to be more forgiving of inaccuracies where the optimal path is
// ambiguous.
#ifndef MG_RESCALE_MULTIPLIER
#    define MG_RESCALE_MULTIPLIER (1.0 + (1.0 / 9.0))
#endif

// Which layer to use for the alphabet key lookups.
#ifndef MG_ALPHABET_LAYER
#    define MG_ALPHABET_LAYER 0
#endif
// Default to English A-Z. Must exactly match the keycodes (eg: taps, etc).
#ifndef MG_ALPHABET
#    define MG_ALPHABET \
         KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, \
         KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, \
         KC_W, KC_X, KC_Y, KC_Z
#    define MG_ALPHABET_SIZE 26
#endif
// Little bit of overlap when using directional grid to further refine cursor
// position.
#ifndef MG_ALPHABET_RESCALE_MULTIPLIER
#    define MG_ALPHABET_RESCALE_MULTIPLIER 2.0
#endif
#ifndef MG_ALPHABET_HOOK_TIMEOUT
#    define MG_ALPHABET_HOOK_TIMEOUT 5000
#endif

// Either "full" or "corners"
#ifndef MG_ANIMATION
#    define MG_ANIMATION full
#endif
// Shorter step appeared to cause reports to be dropped or ignored.
#define MG_ANIMATION_STEP 75

#ifndef MG_UNDO_DEPTH
#    define MG_UNDO_DEPTH 6
#endif

#ifdef __cplusplus
extern "C" {
#endif

void mousegrid_init(void);
bool process_mousegrid(uint16_t keycode, keyrecord_t *record);

#ifdef __cplusplus
}
#endif
