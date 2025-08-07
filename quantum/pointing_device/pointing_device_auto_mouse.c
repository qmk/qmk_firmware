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

#    include <stdlib.h>
#    include <string.h>
#    include "pointing_device_auto_mouse.h"
#    include "debug.h"
#    include "action_util.h"
#    include "quantum_keycodes.h"

/* local data structure for tracking auto mouse */
static auto_mouse_context_t auto_mouse_context = {
    .config.layer    = (uint8_t)(AUTO_MOUSE_DEFAULT_LAYER),
    .config.timeout  = (uint16_t)(AUTO_MOUSE_TIME),
    .config.debounce = (uint8_t)(AUTO_MOUSE_DEBOUNCE),
};

/* local functions */
static bool is_mouse_record(uint16_t keycode, keyrecord_t* record);
static void auto_mouse_reset(void);

/* check for target layer deactivation overrides */
static inline bool layer_hold_check(void) {
    return get_auto_mouse_toggle() ||
#    ifndef NO_ACTION_ONESHOT
           get_oneshot_layer() == (AUTO_MOUSE_TARGET_LAYER) ||
#    endif
           false;
}

/* check all layer activation criteria */
bool is_auto_mouse_active(void) {
    return auto_mouse_context.status.is_activated || auto_mouse_context.status.mouse_key_tracker || layer_hold_check();
}

/**
 * @brief Get auto mouse enable state
 *
 * Return is_enabled value
 *
 * @return bool true: auto mouse enabled false: auto mouse disabled
 */
bool get_auto_mouse_enable(void) {
    return auto_mouse_context.config.is_enabled;
}

/**
 * @brief get current target layer index
 *
 * NOTE: (AUTO_MOUSE_TARGET_LAYER) is an alias for this function
 *
 * @return uint8_t target layer index
 */
uint8_t get_auto_mouse_layer(void) {
    return auto_mouse_context.config.layer;
}

/**
 * @brief Get the current timeout to turn off mouse layer
 *
 * @return uint16_t timeout in ms
 */
uint16_t get_auto_mouse_timeout(void) {
    return auto_mouse_context.config.timeout;
}

/**
 * @brief Get the auto mouse debouncing timeout
 *
 * @return uint8_t
 */
uint8_t get_auto_mouse_debounce(void) {
    return auto_mouse_context.config.debounce;
}

/**
 * @brief get layer_toggled value
 *
 * @return bool of current layer_toggled state
 */
bool get_auto_mouse_toggle(void) {
    return auto_mouse_context.status.is_toggled;
}

/**
 * @brief get key tracker value
 *
 * @return bool of current layer_toggled state
 */
int8_t get_auto_mouse_key_tracker(void) {
    return auto_mouse_context.status.mouse_key_tracker;
}

/**
 * @brief Reset auto mouse context
 *
 * Clear timers and status
 *
 * NOTE: this will set is_toggled to false so careful when using it
 */
static void auto_mouse_reset(void) {
    memset(&auto_mouse_context.status, 0, sizeof(auto_mouse_context.status));
    memset(&auto_mouse_context.timer, 0, sizeof(auto_mouse_context.timer));
}

/**
 * @brief Set auto mouse enable state
 *
 * Set local auto mouse enabled state
 *
 * @param[in] state bool
 */
void set_auto_mouse_enable(bool enable) {
    // skip if unchanged
    if (auto_mouse_context.config.is_enabled == enable) return;
    auto_mouse_context.config.is_enabled = enable;
    auto_mouse_reset();
}

/**
 * @brief Change target layer for auto mouse
 *
 * Sets input as the new target layer if different from current and resets auto mouse
 *
 * NOTE: remove_auto_mouse_layer(state, false) or auto_mouse_layer_off should be called
 *       before this function to avoid issues with layers getting stuck
 *
 * @param[in] layer uint8_t
 */
void set_auto_mouse_layer(uint8_t layer) {
    // skip if unchanged
    if (auto_mouse_context.config.layer == layer) return;
    auto_mouse_context.config.layer = layer;
    auto_mouse_reset();
}

/**
 * @brief Changes the timeout for the mouse auto layer to be disabled
 *
 * @param timeout
 */
void set_auto_mouse_timeout(uint16_t timeout) {
    if (auto_mouse_context.config.timeout == timeout) return;
    auto_mouse_context.config.timeout = timeout;
    auto_mouse_reset();
}

/**
 * @brief Set the auto mouse key debounce
 *
 * @param debounce
 */
void set_auto_mouse_debounce(uint8_t debounce) {
    if (auto_mouse_context.config.debounce == debounce) return;
    auto_mouse_context.config.debounce = debounce;
    auto_mouse_reset();
}

/**
 * @brief Changes the timeout for the mouse auto layer to be disabled
 *
 * @param key_tracker
 */
void set_auto_mouse_key_tracker(int8_t key_tracker) {
    auto_mouse_context.status.mouse_key_tracker = key_tracker;
}

/**
 * @brief toggle mouse layer setting
 *
 * Change state of local layer_toggled bool meant to track when the mouse layer is toggled on by other means
 *
 * NOTE: While is_toggled is true it will prevent deactiving target layer (but not activation)
 */
void auto_mouse_toggle(void) {
    auto_mouse_context.status.is_toggled ^= 1;
    auto_mouse_context.timer.delay = 0;
}

/**
 * @brief Remove current auto mouse target layer from layer state
 *
 * Will remove auto mouse target layer from given layer state if appropriate.
 *
 * NOTE: Removal can be forced, ignoring appropriate critera
 *
 * @params state[in] layer_state_t original layer state
 * @params force[in] bool force removal
 *
 * @return layer_state_t modified layer state
 */
layer_state_t remove_auto_mouse_layer(layer_state_t state, bool force) {
    if (force || ((AUTO_MOUSE_ENABLED) && !layer_hold_check())) {
        state &= ~((layer_state_t)1 << (AUTO_MOUSE_TARGET_LAYER));
    }
    return state;
}

/**
 * @brief Disable target layer
 *
 * Will disable target layer if appropriate.
 * NOTE: NOT TO BE USED in layer_state_set stack!!!
 */
void auto_mouse_layer_off(void) {
    if (layer_state_is((AUTO_MOUSE_TARGET_LAYER)) && (AUTO_MOUSE_ENABLED) && !layer_hold_check()) {
        layer_off((AUTO_MOUSE_TARGET_LAYER));
    }
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
    auto_mouse_context.total_mouse_movement.x += mouse_report.x;
    auto_mouse_context.total_mouse_movement.y += mouse_report.y;
    auto_mouse_context.total_mouse_movement.h += mouse_report.h;
    auto_mouse_context.total_mouse_movement.v += mouse_report.v;
    return abs(auto_mouse_context.total_mouse_movement.x) > AUTO_MOUSE_THRESHOLD || abs(auto_mouse_context.total_mouse_movement.y) > AUTO_MOUSE_THRESHOLD || abs(auto_mouse_context.total_mouse_movement.h) > AUTO_MOUSE_THRESHOLD || abs(auto_mouse_context.total_mouse_movement.v) > AUTO_MOUSE_THRESHOLD || mouse_report.buttons;
}

/**
 * @brief Update the auto mouse based on mouse_report
 *
 * Handel activation/deactivation of target layer based on auto_mouse_activation and state timers and local key/layer tracking data
 *
 * @param[in] mouse_report report_mouse_t
 */
void pointing_device_task_auto_mouse(report_mouse_t mouse_report) {
    // skip if disabled, delay timer running, or debounce
    if (!(AUTO_MOUSE_ENABLED) || timer_elapsed(auto_mouse_context.timer.active) <= auto_mouse_context.config.debounce || timer_elapsed(auto_mouse_context.timer.delay) <= AUTO_MOUSE_DELAY) {
        return;
    }
    // update activation and reset debounce
    auto_mouse_context.status.is_activated = auto_mouse_activation(mouse_report);
    if (is_auto_mouse_active()) {
        auto_mouse_context.total_mouse_movement = (total_mouse_movement_t){.x = 0, .y = 0, .h = 0, .v = 0};
        auto_mouse_context.timer.active         = timer_read();
        auto_mouse_context.timer.delay          = 0;
        if (!layer_state_is((AUTO_MOUSE_TARGET_LAYER))) {
            layer_on((AUTO_MOUSE_TARGET_LAYER));
        }
    } else if (layer_state_is((AUTO_MOUSE_TARGET_LAYER)) && timer_elapsed(auto_mouse_context.timer.active) > auto_mouse_context.config.timeout) {
        layer_off((AUTO_MOUSE_TARGET_LAYER));
        auto_mouse_context.timer.active         = 0;
        auto_mouse_context.total_mouse_movement = (total_mouse_movement_t){.x = 0, .y = 0, .h = 0, .v = 0};
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
        auto_mouse_context.status.mouse_key_tracker++;
    } else {
        auto_mouse_context.status.mouse_key_tracker--;
    }
    auto_mouse_context.timer.delay = 0;
}

/**
 * @brief Handle auto mouse non mousekey reset
 *
 * Start/restart delay timer and reset auto mouse on keydown as well as turn the
 * target layer off if on and reset toggle status
 *
 * NOTE: NOT TO BE USED in layer_state_set stack!!!
 *
 * @param[in] pressed bool
 */
void auto_mouse_reset_trigger(bool pressed) {
    if (pressed) {
        if (layer_state_is((AUTO_MOUSE_TARGET_LAYER))) {
            layer_off((AUTO_MOUSE_TARGET_LAYER));
        };
        auto_mouse_reset();
    }
    auto_mouse_context.timer.delay = timer_read();
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
    if (!(AUTO_MOUSE_ENABLED)) return true;

    switch (keycode) {
        // Skip Mod keys to avoid layer reset
        case KC_LEFT_CTRL ... KC_RIGHT_GUI:
        case QK_MODS ... QK_MODS_MAX:
            break;
        // TO((AUTO_MOUSE_TARGET_LAYER))-------------------------------------------------------------------------------
        case QK_TO ... QK_TO_MAX:
            if (QK_TO_GET_LAYER(keycode) == (AUTO_MOUSE_TARGET_LAYER)) {
                if (!(record->event.pressed)) auto_mouse_toggle();
            }
            break;
        // TG((AUTO_MOUSE_TARGET_LAYER))-------------------------------------------------------------------------------
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            if (QK_TOGGLE_LAYER_GET_LAYER(keycode) == (AUTO_MOUSE_TARGET_LAYER)) {
                if (!(record->event.pressed)) auto_mouse_toggle();
            }
            break;
        // MO((AUTO_MOUSE_TARGET_LAYER))-------------------------------------------------------------------------------
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            if (QK_MOMENTARY_GET_LAYER(keycode) == (AUTO_MOUSE_TARGET_LAYER)) {
                auto_mouse_keyevent(record->event.pressed);
            }
        // DF ---------------------------------------------------------------------------------------------------------
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        // PDF --------------------------------------------------------------------------------------------------------
        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
#    ifndef NO_ACTION_ONESHOT
        // OSL((AUTO_MOUSE_TARGET_LAYER))------------------------------------------------------------------------------
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#    endif
            break;
        // LM((AUTO_MOUSE_TARGET_LAYER), mod)--------------------------------------------------------------------------
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            if (QK_LAYER_MOD_GET_LAYER(keycode) == (AUTO_MOUSE_TARGET_LAYER)) {
                auto_mouse_keyevent(record->event.pressed);
            }
            break;
            // TT((AUTO_MOUSE_TARGET_LAYER))---------------------------------------------------------------------------
#    ifndef NO_ACTION_TAPPING
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            if (QK_LAYER_TAP_TOGGLE_GET_LAYER(keycode) == (AUTO_MOUSE_TARGET_LAYER)) {
                auto_mouse_keyevent(record->event.pressed);
#        if TAPPING_TOGGLE != 0
                if (record->tap.count == TAPPING_TOGGLE) {
                    if (record->event.pressed) {
                        auto_mouse_context.status.mouse_key_tracker--;
                    } else {
                        auto_mouse_toggle();
                        auto_mouse_context.status.mouse_key_tracker++;
                    }
                }
#        endif
            }
            break;
        // LT((AUTO_MOUSE_TARGET_LAYER), kc)---------------------------------------------------------------------------
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (!record->tap.count) {
                if (QK_LAYER_TAP_GET_LAYER(keycode) == (AUTO_MOUSE_TARGET_LAYER)) {
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
            // skip on no event
            if (IS_NOEVENT(record->event)) break;
            // check if keyrecord is mousekey
            if (is_mouse_record(keycode, record)) {
                auto_mouse_keyevent(record->event.pressed);
            } else if (!is_auto_mouse_active()) {
                // all non-mousekey presses restart delay timer and reset status
                auto_mouse_reset_trigger(record->event.pressed);
            }
    }
    if (auto_mouse_context.status.mouse_key_tracker < 0) {
        auto_mouse_context.status.mouse_key_tracker = 0;
        dprintf("key tracker error (<0) \n");
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
