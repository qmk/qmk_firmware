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

static bool is_mouse_record(uint16_t keycode, keyrecord_t* record);
static void auto_mouse_status_update(report_mouse_t mouse_report);

/* local data structure for tracking auto mouse */
static auto_mouse_context_t auto_mouse_data = {.config.layer = (uint8_t)AUTO_MOUSE_DEFAULT_LAYER};

/**
 * @brief Reset auto mouse status
 *
 * Will zero all timers and status and disable target layer if on
 */
void auto_mouse_reset(void) {
    if (!layer_state_is(auto_mouse_data.config.layer) && !get_auto_mouse_toggle() &&
#    ifndef NO_ACTION_ONESHOT
        get_oneshot_layer() == auto_mouse_data.config.layer &&
#    endif
        true)
        layer_off(auto_mouse_data.config.layer);
    memset(&auto_mouse_data.status, 0, sizeof(auto_mouse_data.status));
    memset(&auto_mouse_data.timer, 0, sizeof(auto_mouse_data.timer));
}

/**
 * @brief Set auto mouse enable state
 *
 * Will set local auto mouse enabled state if different than input
 *
 * @param[in] state bool
 */
void set_auto_mouse_state(bool state) {
    // skip if already set
    if (auto_mouse_data.config.is_enabled != state) {
        auto_mouse_data.config.is_enabled = state;
        // reset layer related settings and timers
        auto_mouse_reset();
    }
}

/**
 * @brief Get auto mouse state
 *
 * Will return local auto mouse enabled state value
 *
 * @return bool true: auto mouse enabled false: auto mouse disabled
 */
bool get_auto_mouse_state(void) {
    return auto_mouse_data.config.is_enabled;
}

/**
 * @brief Change target layer for auto mouse
 *
 * Sets input as the new target layer if different from current
 *
 * NOTE: Input is the index of the layer not the mask
 *
 * @param[in] layer uint8_t
 */
void set_auto_mouse_layer(uint8_t layer) {
    if (auto_mouse_data.config.layer != layer) {
        // reset layer related settings and timers
        auto_mouse_reset();
        auto_mouse_data.config.layer = layer;
    }
}

/**
 * @brief toggle mouse layer setting
 *
 * Change state of local layer_toggled bool meant to track when the mouse layer is toggled on by other means
 *
 * NOTE: While layer_toggled is true it will prevent deactiving target layer
 */
void auto_mouse_toggle(void) {
    auto_mouse_data.status.is_toggled ^= 1;
    dprintf("Auto mouse toggled %s \n", get_auto_mouse_toggle() ? "on" : "off");
}

/**
 * @brief get layer_toggled value
 *
 * @return bool of current layer_toggled state
 */
bool get_auto_mouse_toggle(void) {
    return auto_mouse_data.status.is_toggled;
}

/**
 * @brief Weak function to handel testing if pointing_device is active
 *
 * Will trigger target layer activation(if delay timer has expired) and prevent deactivation when true.
 * May be replaced by bool in report_mouse_t in future
 *
 * NOTE: defined weakly to allow for changing and adding conditions for specific hardware/customization
 *
 * @param[in] mouse_report report_mouse_t
 * @return bool of pointing_device activation
 */
__attribute__((weak)) bool auto_mouse_activation(report_mouse_t mouse_report) {
    return mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.h != 0 || mouse_report.v != 0 || mouse_report.buttons;
}

/**
 * @brief update active status of auto_mouse
 *
 * will check all conditions that keep mouse layer active/prevent deactivation
 *
 * @param[in] mouse_report report_mouse_t
 */
static void auto_mouse_status_update(report_mouse_t mouse_report) {
    // check for key tracker errors
    if (auto_mouse_data.status.mouse_key_tracker < 0) {
        auto_mouse_data.status.mouse_key_tracker = 0;
        dprintf("mouse_key_tracker_error! (<0) \n");
    }
    // check for toggle error
    if (get_auto_mouse_toggle() && !layer_state_is(auto_mouse_data.config.layer)) {
        layer_on(auto_mouse_data.config.layer);
        dprintf("toggle layer error! \n");
    }

    // update mouse activation status
    auto_mouse_data.status.is_active = (auto_mouse_activation(mouse_report) || auto_mouse_data.status.mouse_key_tracker || get_auto_mouse_toggle() ||
#    ifndef NO_ACTION_ONESHOT
                                        get_oneshot_layer() == auto_mouse_data.config.layer ||
#    endif
                                        false);
}

/**
 * @brief Update the auto mouse based on mouse_report
 *
 * Handel activation/deactivation of target layer based on auto_mouse_activation and state timers and local key/layer tracking data
 *
 * @param[in] mouse_report report_mouse_t
 */
void pointing_device_task_auto_mouse(report_mouse_t mouse_report) {
    // skip if disabled or layer not set
    if (!get_auto_mouse_state()) return;
    // update active status
    auto_mouse_status_update(mouse_report);
    // check conditions and update
    if (auto_mouse_data.status.is_active) {
        auto_mouse_data.timer.active = timer_read();
        if (!layer_state_is(auto_mouse_data.config.layer) && timer_elapsed(auto_mouse_data.timer.delay) > AUTO_MOUSE_DELAY) {
            layer_on(auto_mouse_data.config.layer);
            auto_mouse_data.timer.delay = 0;
            dprintf("Auto mouse Layer ON! \n");
        }
    } else if (layer_state_is(auto_mouse_data.config.layer) && timer_elapsed(auto_mouse_data.timer.active) > AUTO_MOUSE_TIME) {
        layer_off(auto_mouse_data.config.layer);
        auto_mouse_data.timer.active = 0;
        dprintf("Auto mouse Layer OFF! \n");
    }
}

/**
 * @brief Handle mouskey event
 *
 * Increments/decrements mouse_key_tracker and restart active timer
 *
 * @param[in] pressed bool
 */
void auto_mouse_keyevent(bool pressed) {
    if (pressed) {
        auto_mouse_data.status.mouse_key_tracker++;
        dprintf("mousekey pressed, count: %d \n", auto_mouse_data.status.mouse_key_tracker);
    } else {
        auto_mouse_data.status.mouse_key_tracker--;
        dprintf("mousekey released, count: %d \n", auto_mouse_data.status.mouse_key_tracker);
    }
    auto_mouse_data.timer.active = timer_read();
}

/**
 * @brief Handle auto mouse non mousekey reset
 *
 * Start/restart delay timer and reset auto mouse on keydown
 *
 * NOTE: this will turn the target layer off if on and reset toggle status
 *
 * @param[in] pressed bool
 */
void auto_mouse_reset_trigger(bool pressed) {
    if (pressed) {
        auto_mouse_reset();
        dprintf("Non-mouskey pressed! \n");
    }
    auto_mouse_data.timer.delay = timer_read();
}

/**
 * @brief handle key events processing for auto mouse
 *
 * Will process keys differently depending on if key is defined as mousekey or not.
 * Some keys have built in behaviour(not overwritable):
 * mouse buttons        : auto_mouse_keyevent()
 * non-mouse keys       : auto_mouse_reset_trigger()
 * mod keys             : skip auto mouse key processing
 * mod tap              : skip on hold (mod keys)
 * QK mods e.g. LCTL(kc): default to non-mouse key, add at kb/user level as needed
 * non target layer keys: skip auto mouse key processing (same as mod keys)
 * MO(target layer)     : auto_mouse_keyevent()
 * target layer toggles : auto_mouse_toggle() (on both key up and keydown)
 * target layer tap     : default processing on tap mouse key on hold
 * all other keycodes   : default to non-mouse key, add at kb/user level as needed
 *
 * Will deactivate target layer once a non mouse key is pressed if nothing is holding the layer active
 * such as held mousekey, toggled current target layer, or auto_mouse_activation is true
 *
 * @params keycode[in] uint16_t
 * @params record[in] keyrecord_t pointer
 */
bool process_auto_mouse(uint16_t keycode, keyrecord_t* record) {
    // skip if not enabled or mouse_layer not set
    if (!get_auto_mouse_state()) return true;

    switch (keycode) {
        // Skip Mod keys to avoid layer reset
        case KC_LEFT_CTRL ... KC_RIGHT_GUI:
            break;
        // TO(auto_mouse_data.config.layer)-------------------------------------------------------------------------------
        case QK_TO ... QK_TO_MAX: // same proccessing as next
        // TG(auto_mouse_data.config.layer)-------------------------------------------------------------------------------
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            if ((keycode & 0xff) == auto_mouse_data.config.layer) {
                if (!(record->event.pressed)) auto_mouse_toggle();
            }
            break;
        // MO(auto_mouse_data.config.layer)-------------------------------------------------------------------------------
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            if ((keycode & 0xff) == auto_mouse_data.config.layer) {
                auto_mouse_keyevent(record->event.pressed);
            }
            break;
        // DF -------------------------------------------------------------------------------------------------------------
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            break;
#    ifndef NO_ACTION_ONESHOT
        // OSL(auto_mouse_data.config.layer)------------------------------------------------------------------------------
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            if ((keycode & 0xff) == auto_mouse_data.config.layer) {
                auto_mouse_keyevent(record->event.pressed);
            }
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            break;
#    endif
        // LM(auto_mouse_data.config.layer, mod)--------------------------------------------------------------------------
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            if (auto_mouse_data.config.layer < MAX_LAYER && (((keycode >> 4) & 0xf) == auto_mouse_data.config.layer)) {
                auto_mouse_keyevent(record->event.pressed);
            }
            break;
            // TT(auto_mouse_data.config.layer)-------------------------------------------------------------------------------
#    ifndef NO_ACTION_TAPPING
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            if ((keycode & 0xff) == auto_mouse_data.config.layer) {
                auto_mouse_keyevent(record->event.pressed);
#        if TAPPING_TOGGLE != 0
                if (record->tap.count == TAPPING_TOGGLE) {
                    if (record->event.pressed) {
                        auto_mouse_data.status.mouse_key_tracker--;
                    } else {
                        auto_mouse_toggle();
                        auto_mouse_data.status.mouse_key_tracker++;
                    }
                }
#        endif
            }
            break;
        // LT(auto_mouse_data.config.layer, kc)---------------------------------------------------------------------------
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (!record->tap.count) {
                if (auto_mouse_data.config.layer < MAX_LAYER && ((keycode >> 8) & 0xf) == auto_mouse_data.config.layer) {
                    auto_mouse_keyevent(record->event.pressed);
                }
                break;
            }
        // MT(kc) only skip on hold
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (!record->tap.count) break;
#    endif
        // QK_MODS goes to default
        default:
            // skip if no key has been pressed
            if (IS_NOEVENT(record->event)) break;
            // update auto mouse status
            // auto_mouse_status_update(pointing_device_get_report());
            if (is_mouse_record(keycode, record)) {
                auto_mouse_keyevent(record->event.pressed);
            } else if (!auto_mouse_data.status.is_active) {
                // all non-mousekey presses while auto_mouse is not active reset delay timer and status
                auto_mouse_reset_trigger(record->event.pressed);
            }
    }
    return true;
}

/**
 * @brief Local function to handle checking if a keycode is a mouse button
 *
 * Starts code stack for checking keyrecord if defined as mousekey
 *
 * @params keycode[in] uint16_t
 * @params record[in]  keyrecord_t pointer
 * @return bool true: keyrecord is mousekey false: keyrecord is not mousekey
 */
static bool is_mouse_record(uint16_t keycode, keyrecord_t* record) {
    // allow for keyboard to hook in and override if need be
    if (is_mouse_record_kb(keycode, record) || IS_MOUSEKEY(keycode)) return true;
    return false;
}

/**
 * @brief Weakly defined keyboard level callback for adding keyrecords as mouse keys
 *
 * Meant for redefinition at keyboard level and should return is_mouse_record_user by default at end of function
 *
 * @params keycode[in] uint16_t
 * @params record[in] keyrecord_t pointer
 * @return bool true: keyrecord is defined as mouse key false: keyrecord is not defined as mouse key
 */
__attribute__((weak)) bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    return is_mouse_record_user(keycode, record);
}

/**
 * @brief Weakly defined keymap/user level callback for adding keyrecords as mouse keys
 *
 * Meant for redefinition at keymap/user level and should return false by default at end of function
 *
 * @params keycode[in] uint16_t
 * @params record[in] keyrecord_t pointer
 * @return bool true: keyrecord is defined as mouse key false: keyrecord is not defined as mouse key
 */
__attribute__((weak)) bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    return false;
}

#endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE