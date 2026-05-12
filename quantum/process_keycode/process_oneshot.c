// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_oneshot.h"
#include "action_util.h"

bool process_oneshot(uint16_t keycode, keyrecord_t *record) {
#ifndef NO_ACTION_ONESHOT
    if (record->event.pressed) {
        switch (keycode) {
            case QK_ONE_SHOT_TOGGLE:
                oneshot_toggle();
                return false;
            case QK_ONE_SHOT_ON:
                oneshot_enable();
                return false;
            case QK_ONE_SHOT_OFF:
                oneshot_disable();
                return false;
        }
    }
#endif

    return true;
}
