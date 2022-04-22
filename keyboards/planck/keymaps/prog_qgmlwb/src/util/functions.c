// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "functions.h"

// Get current language layer
inline int get_language() {
    if (layer_state_cmp(default_layer_state, QGMLWB_NO)) {
        return QGMLWB_NO;
    }
    if (layer_state_cmp(default_layer_state, QGMLWB_US)) {
        return QGMLWB_US;
    }
    return -1;
}
