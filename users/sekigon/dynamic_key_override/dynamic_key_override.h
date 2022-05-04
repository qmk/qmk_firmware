
// Copyright 2022 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_key_override.h"

// register override to buffer
//  The added override should be static or global (should live long enough)
int register_override(const key_override_t *override);
void remove_all_overrides(void);

// helper macro
#define w_shift(kc, kc_override) &ko_make_basic(MOD_MASK_SHIFT, kc, kc_override)
#define wo_shift(kc, kc_override)                            \
    &ko_make_with_layers_and_negmods(0, kc, kc_override, ~0, \
                                     (uint8_t)MOD_MASK_SHIFT)
