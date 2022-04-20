// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "functions.h"

// Get current language layer
inline int get_language() {
    if (layer_state_cmp(default_layer_state, QGMLW_NO)) {
        return QGMLW_NO;
    }
    if (layer_state_cmp(default_layer_state, QGMLW_US)) {
        return QGMLW_US;
    }
    return -1;
}
