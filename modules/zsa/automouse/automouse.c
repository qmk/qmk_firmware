// Copyright 2025 ZSA Technology Labs, Inc <@zsa>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "automouse.h"
#include <stdlib.h>

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 1, 0);

static struct {
    uint16_t last_activity;
    uint16_t last_keypress;
    uint16_t last_activation;
    int16_t  accumulated_x;
    int16_t  accumulated_y;
    int16_t  accumulated_h;
    int16_t  accumulated_v;
    int8_t   held_keys;
    bool     is_active;
    bool     is_enabled;
#ifdef AUTOMOUSE_ONESHOT
    bool oneshot_triggered;
#endif
} state = {
    .is_enabled = true,
};

static bool layer_held_externally(void) {
#ifdef LAYER_LOCK_ENABLE
    if (is_layer_locked(AUTOMOUSE_LAYER)) return true;
#endif
    if (is_oneshot_layer_active() && get_oneshot_layer() == AUTOMOUSE_LAYER) return true;
    return false;
}

static void automouse_activate(void) {
    if (!state.is_active) {
        // Don't take ownership if layer is already on by other means
        if (layer_state_is(AUTOMOUSE_LAYER)) {
            return;
        }
        state.is_active = true;
        state.held_keys = 0;
    }
    // Ensure layer is on — it may have been turned off externally (e.g. TO(), TG())
    if (!layer_state_is(AUTOMOUSE_LAYER)) {
        layer_on(AUTOMOUSE_LAYER);
    }
    state.last_activity = timer_read();
#ifdef AUTOMOUSE_ONESHOT
    state.oneshot_triggered = false;
#endif
}

static void automouse_deactivate(void) {
    if (state.is_active) {
        state.is_active = false;
        state.held_keys = 0;
        if (!layer_held_externally()) {
            layer_off(AUTOMOUSE_LAYER);
        }
    }
}

// --- Public API ---

void automouse_enable(void) {
    state.is_enabled = true;
}

void automouse_disable(void) {
    automouse_deactivate();
    state.is_enabled = false;
}

void automouse_toggle(void) {
    if (state.is_enabled) {
        automouse_disable();
    } else {
        automouse_enable();
    }
}

bool automouse_is_enabled(void) {
    return state.is_enabled;
}

bool automouse_is_active(void) {
    return state.is_active;
}

// --- Module hooks ---

report_mouse_t pointing_device_task_automouse(report_mouse_t mouse_report) {
    if (!state.is_enabled) {
        return mouse_report;
    }

    // Keep layer alive while keys are held on it
    if (state.is_active && state.held_keys > 0) {
        state.last_activity = timer_read();
    }

#ifdef AUTOMOUSE_ONESHOT
    if (state.is_active && state.oneshot_triggered && timer_elapsed(state.last_activity) > AUTOMOUSE_TIMEOUT) {
#else
    if (state.is_active && timer_elapsed(state.last_activity) > AUTOMOUSE_TIMEOUT) {
#endif
        automouse_deactivate();
    }

    // Skip activation checks during debounce or post-keypress delay
    if (timer_elapsed(state.last_activation) <= AUTOMOUSE_DEBOUNCE || timer_elapsed(state.last_keypress) <= AUTOMOUSE_DELAY) {
        return mouse_report;
    }

    state.accumulated_x += mouse_report.x;
    state.accumulated_y += mouse_report.y;
    state.accumulated_h += mouse_report.h;
    state.accumulated_v += mouse_report.v;

    bool threshold_exceeded = abs(state.accumulated_x) > AUTOMOUSE_THRESHOLD || abs(state.accumulated_y) > AUTOMOUSE_THRESHOLD || abs(state.accumulated_h) > AUTOMOUSE_SCROLL_THRESHOLD || abs(state.accumulated_v) > AUTOMOUSE_SCROLL_THRESHOLD || (mouse_report.buttons && state.is_active);

    if (threshold_exceeded) {
        state.accumulated_x   = 0;
        state.accumulated_y   = 0;
        state.accumulated_h   = 0;
        state.accumulated_v   = 0;
        state.last_activation = timer_read();
        automouse_activate();
    }

    return mouse_report;
}

bool process_record_automouse(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_AUTOMOUSE_TOGGLE) {
        if (record->event.pressed) {
            automouse_toggle();
        }
        return false;
    }

    if (!state.is_enabled || !state.is_active) {
        // Track keypresses for the post-keypress delay only when layer is inactive
        if (record->event.pressed) {
            state.last_keypress = timer_read();
        }
        return true;
    }

    // Track held keys while automouse layer is active
    if (record->event.pressed) {
        state.held_keys++;
    } else if (state.held_keys > 0) {
        state.held_keys--;
    }

#ifdef AUTOMOUSE_ONESHOT
    // Start timeout on key up so the full tap completes on the mouse layer
    if (!record->event.pressed && !state.oneshot_triggered) {
        state.oneshot_triggered = true;
        state.last_activity     = timer_read();
    }
#else
    if (record->event.pressed) {
        state.last_activity = timer_read();
    }
#endif

    return true;
}
