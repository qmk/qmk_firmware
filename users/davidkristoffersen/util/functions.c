// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "functions.h"

// Get current language layer
#ifdef MULTI_LANGUAGE
int get_language() {
#ifdef LAYER_NO
    if (layer_state_cmp(default_layer_state, LAYER_NO)) {
        return LAYER_NO;
    }
#endif
#ifdef LAYER_EN
    if (layer_state_cmp(default_layer_state, LAYER_EN)) {
        return LAYER_EN;
    }
#endif
    return -1;
}
#endif
