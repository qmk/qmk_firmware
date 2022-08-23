/* Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2022 Alabastard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE

#    include "pointing_device_auto_mouse.h"

/* needed variables for tracking auto mouse */
static auto_mouse_context_t local_auto_mouse = {.config.layer = (uint8_t)AUTO_MOUSE_DEFAULT_LAYER};

/* Handle checking if a keycode is a mouse button */
static bool is_mouse_record(uint16_t keycode, keyrecord_t* record) {
    // allow for keyboard to hook in and override if need be
    if (is_mouse_record_kb(keycode, record) || IS_MOUSEKEY(keycode)) {
        return true;
    }
    return false;
}

/* set which layer will act as the mouse layer */
void set_auto_mouse_layer(uint8_t layer) {
    if (local_auto_mouse.config.layer != layer) {
        local_auto_mouse.config.layer = layer;
    }
}

/* handle mouskey event */
void auto_mouse_keyevent(bool pressed) {
    if (pressed) {
        local_auto_mouse.status.mouse_key_tracker++;
    } else {
        local_auto_mouse.status.mouse_key_tracker--;
        local_auto_mouse.timer.active = timer_read();
    }
}

void auto_mouse_reset_trigger(void) {
    local_auto_mouse.status.mouse_key_tracker = 0;
    local_auto_mouse.timer.active             = 0;
    local_auto_mouse.timer.delay              = timer_read();
}

/* Allow for getting auto mouse state */
bool get_auto_mouse_state(void) {
    return local_auto_mouse.config.enabled;
}

/* Allow for setting auto mouse enable state */
void set_auto_mouse_state(bool state) {
    // skip if already set
    if (local_auto_mouse.config.enabled != state) {
        local_auto_mouse.config.enabled = state;
        // reset settings on state change
        local_auto_mouse.status.mouse_key_tracker = 0;
        local_auto_mouse.timer.active             = 0;
        local_auto_mouse.timer.delay              = 0;
        local_auto_mouse.status.layer_toggled     = false;
    }
}

/* toggle mouse layer setting (disabling automouse layer changes) */
void toggle_mouse_layer(void) {
    local_auto_mouse.status.layer_toggled ^= 1;
}

/* Allow for accessing toggle mouse bool value */
bool get_toggle_mouse_state(void) {
    return local_auto_mouse.status.layer_toggled;
}

/* control activation of target layer */
__attribute__((weak)) bool auto_mouse_activation(report_mouse_t mouse_report) {
    return mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.h != 0 || mouse_report.v != 0;
}

/* Update the auto mouse if auto_mouse_activation is true or timer expires on the base layer */
void pointing_device_task_auto_mouse(report_mouse_t mouse_report) {
    // skip if disabled or layer not set
    if (!local_auto_mouse.config.enabled) {
        return;
    }
    // Check for mouse movement and update
    if (auto_mouse_activation(mouse_report)) {
        local_auto_mouse.timer.active = timer_read();
        if (!layer_state_is(local_auto_mouse.config.layer) && timer_elapsed(local_auto_mouse.timer.delay) > AUTO_MOUSE_DELAY) {
            layer_on(local_auto_mouse.config.layer);
            local_auto_mouse.timer.delay = 0;
        }
    } else if (timer_elapsed(local_auto_mouse.timer.active) > AUTO_MOUSE_TIME && layer_state_is(local_auto_mouse.config.layer) && !local_auto_mouse.status.mouse_key_tracker && !local_auto_mouse.status.layer_toggled
#    ifndef NO_ACTION_ONESHOT
               && get_oneshot_layer() != local_auto_mouse.config.layer // skip layer off if target layer one shot is active
#    endif
    ) {
        layer_off(local_auto_mouse.config.layer);
    }
}

/* handle key presses for auto mouse
 * mouse keys           : auto_mouse_keyevent()
 * non-mouse keys       : auto_mouse_reset_trigger()
 * mod keys             : skip auto mouse key processing
 * non target layer keys: skip auto mouse key processing
 * MO(target layer)     : treat as mousekey
 * target layer toggles : toggle_mouse_layer()
 * target layer tap     : default processing on tap mouse key on hold
 * mod tap
 */
void process_auto_mouse(uint16_t keycode, keyrecord_t* record) {
    // skip if not enabled or mouse_layer not set
    if (!local_auto_mouse.config.enabled) {
        return;
    }

    switch (keycode) {
        // Skip Mod keys to avoid layer reset
        case KC_LEFT_CTRL ... KC_RIGHT_GUI:
#    ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#    endif
            break;
        // TO(local_auto_mouse.config.layer)-----------------------------------------------------------------
        case QK_TO ... QK_TO_MAX: // same proccessing as next
        // TG(local_auto_mouse.config.layer)-----------------------------------------------------------------
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            if ((keycode & 0xff) == local_auto_mouse.config.layer) {
                toggle_mouse_layer();
            }
            break;
        // MO(local_auto_mouse.config.layer)-----------------------------------------------------------------
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            if ((keycode & 0xff) == local_auto_mouse.config.layer) {
                auto_mouse_keyevent(record->event.pressed);
            }
            break;
        // DF ---------------------------------------------------------------------------------------------
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            break;
#    ifndef NO_ACTION_ONESHOT
        // OSL(MOUSE_LAYER)--------------------------------------------------------------------------------
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            if ((keycode & 0xff) == local_auto_mouse.config.layer) {
                if (keymap_config.oneshot_enable) {
                    auto_mouse_keyevent(record->event.pressed);
                    break;
                }
                if (record->event.pressed) {
                    local_auto_mouse.status.mouse_key_tracker++;
                } else {
#        if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE != 0 && !defined(NO_ACTION_TAPPING)
                    if (record->tap.count == ONESHOT_TAP_TOGGLE) {
                        toggle_mouse_layer();
#            if ONESHOT_TAP_TOGGLE == 1
                        if (!local_auto_mouse.status.layer_toggled) {
                            local_auto_mouse.status.mouse_key_tracker -= record->tap.count + 1;
                        }
#            else
                        if (!local_auto_mouse.status.layer_toggled) {
                            local_auto_mouse.status.mouse_key_tracker -= record->tap.count;
                        }
#            endif
                    } else {
                        local_auto_mouse.status.mouse_key_tracker--;
                    }
#        else
                    local_auto_mouse.status.mouse_key_tracker--;
#        endif
                    local_auto_mouse.timer.active = timer_read();
                }
            }
            break;
#    endif
        // TT(local_auto_mouse.config.layer)---------------------------------------------------------------
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            if ((keycode & 0xff) == local_auto_mouse.config.layer) {
                if (record->event.pressed) {
                    local_auto_mouse.status.mouse_key_tracker++;
                } else {
#    if TAPPING_TOGGLE != 0 && !defined(NO_ACTION_TAPPING)
                    if (record->tap.count == TAPPING_TOGGLE) {
                        toggle_mouse_layer();
#        if TAPPING_TOGGLE == 1
                        if (!local_auto_mouse.status.layer_toggled) {
                            local_auto_mouse.status.mouse_key_tracker -= record->tap.count + 1;
                        }
#        else
                        if (!local_auto_mouse.status.layer_toggled) {
                            local_auto_mouse.status.mouse_key_tracker -= record->tap.count;
                        }
#        endif
                    } else {
                        local_auto_mouse.status.mouse_key_tracker--;
                    }
#    else
                    local_auto_mouse.status.mouse_key_tracker--;
#    endif
                    local_auto_mouse.timer.active = timer_read();
                }
            }
            break;
        // LM(local_auto_mouse.config.layer, mod)------------------------------------------------------------
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            if (local_auto_mouse.config.layer < MAX_LAYER && (((keycode >> 4) & 0xf) == local_auto_mouse.config.layer)) {
                auto_mouse_keyevent(record->event.pressed);
            }
            break;
#    ifndef NO_ACTION_TAPPING
        // LT(local_auto_mouse.config.layer, kc)------------------------------------------------------------
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (!record->tap.count) {
                if (local_auto_mouse.config.layer < MAX_LAYER && ((keycode >> 8) & 0xf) == local_auto_mouse.config.layer) {
                    auto_mouse_keyevent(record->event.pressed);
                }
                break;
            }
        // MT(kc) only skip on hold
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (!record->tap.count && record->event.pressed) {
                break;
            }
#    endif
        case QK_MODS ... QK_MODS_MAX:
        default:
            if (IS_NOEVENT(record->event)) {
                break;
            } // skip if no key has been pressed
            if (is_mouse_record(keycode, record)) {
                auto_mouse_keyevent(record->event.pressed);
            } else {
                // all non-mousekey presses while a mouse key is not active reset delay timer
                if (!(local_auto_mouse.status.mouse_key_tracker > 0)) {
                    auto_mouse_reset_trigger();
                }
                // turn off mouse layer if no non mouse key is pressed and start/restart debounce timer
                if (layer_state_is(local_auto_mouse.config.layer) && !(local_auto_mouse.status.mouse_key_tracker > 0) && !local_auto_mouse.status.layer_toggled && !auto_mouse_activation(pointing_device_get_report())
#    ifndef NO_ACTION_ONESHOT
                    && get_oneshot_layer() != local_auto_mouse.config.layer // skip layer change if target layer one shot is active
#    endif
                ) {
                    layer_off(local_auto_mouse.config.layer);
                }
            }
    }
    // sanity check for mouse_key_tracker
    if (local_auto_mouse.status.mouse_key_tracker < 0) {
        local_auto_mouse.status.mouse_key_tracker = 0;
    }
}

/* Callbacks for adding keyrecords as mouse keys */
__attribute__((weak)) bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    return is_mouse_record_user(keycode, record);
}
__attribute__((weak)) bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    return is_mouse_record_keymap(keycode, record);
}
__attribute__((weak)) bool is_mouse_record_keymap(uint16_t keycode, keyrecord_t* record) {
    return false;
}
#endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE