// Copyright 2022 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_key_override.h"

#ifndef DYNAMIC_KEY_OVERRIDE_COUNT_MAX
#    define DYNAMIC_KEY_OVERRIDE_COUNT_MAX 64
#endif

static const key_override_t
    *dynamic_key_override[DYNAMIC_KEY_OVERRIDE_COUNT_MAX + 1] = {NULL};
static int16_t key_override_cnt                               = 0;

const key_override_t **key_overrides = dynamic_key_override;

int register_override(const key_override_t *override) {
    if (key_override_cnt >= DYNAMIC_KEY_OVERRIDE_COUNT_MAX) {
        return -1;
    }

    dynamic_key_override[key_override_cnt++] = override;
    dynamic_key_override[key_override_cnt]   = NULL;
    return 0;
}

void remove_all_overrides(void) {
    dynamic_key_override[0] = NULL;
    key_override_cnt        = 0;
}
