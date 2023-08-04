// Copyright 2021 Christoph Rehmann (crehmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "haptic_utils.h"

#ifdef HAPTIC_ENABLE
#include "drivers/haptic/drv2605l.h"
#endif

#ifdef HAPTIC_ENABLE
bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BTN1 ... KC_BTN5:
            return true;
            break;
    }

    return false;
}
#endif

void process_layer_pulse(layer_state_t state) {
#ifdef HAPTIC_ENABLE
    switch (get_highest_layer(state)) {
        case 1:
            drv2605l_pulse(DRV2605L_EFFECT_SOFT_BUMP_100);
            break;
        case 2:
            drv2605l_pulse(DRV2605L_EFFECT_SHORT_DOUBLE_SHARP_TICK_1_100);
            break;
        case 3:
            drv2605l_pulse(DRV2605L_EFFECT_LONG_DOUBLE_SHARP_CLICK_STRONG_1_100);
            break;
        case 4:
            drv2605l_pulse(DRV2605L_EFFECT_SOFT_BUMP_100);
            break;
        case 5:
            drv2605l_pulse(DRV2605L_EFFECT_PULSING_SHARP_1_100);
            break;
    }
#endif
}
