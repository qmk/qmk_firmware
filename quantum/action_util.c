/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "host.h"
#include "report.h"
#include "debug.h"
#include "action_util.h"
#include "action_layer.h"
#include "timer.h"
#include "keycode_config.h"
#include <string.h>

extern keymap_config_t keymap_config;

static uint8_t real_mods = 0;
static uint8_t weak_mods = 0;
#ifdef KEY_OVERRIDE_ENABLE
static uint8_t weak_override_mods = 0;
static uint8_t suppressed_mods    = 0;
#endif

// TODO: pointer variable is not needed
// report_keyboard_t keyboard_report = {};
report_keyboard_t *keyboard_report = &(report_keyboard_t){};

extern inline void add_key(uint8_t key);
extern inline void del_key(uint8_t key);
extern inline void clear_keys(void);

#ifndef NO_ACTION_ONESHOT
static uint8_t oneshot_mods        = 0;
static uint8_t oneshot_locked_mods = 0;
uint8_t        get_oneshot_locked_mods(void) {
    return oneshot_locked_mods;
}
void set_oneshot_locked_mods(uint8_t mods) {
    if (mods != oneshot_locked_mods) {
        oneshot_locked_mods = mods;
        oneshot_locked_mods_changed_kb(oneshot_locked_mods);
    }
}
void clear_oneshot_locked_mods(void) {
    if (oneshot_locked_mods) {
        oneshot_locked_mods = 0;
        oneshot_locked_mods_changed_kb(oneshot_locked_mods);
    }
}
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
static uint16_t oneshot_time = 0;
bool            has_oneshot_mods_timed_out(void) {
    return TIMER_DIFF_16(timer_read(), oneshot_time) >= ONESHOT_TIMEOUT;
}
#    else
bool has_oneshot_mods_timed_out(void) {
    return false;
}
#    endif
#endif

/* oneshot layer */
#ifndef NO_ACTION_ONESHOT
/** \brief oneshot_layer_data bits
 * LLLL LSSS
 * where:
 *   L => are layer bits
 *   S => oneshot state bits
 */
static int8_t oneshot_layer_data = 0;

inline uint8_t get_oneshot_layer(void) {
    return oneshot_layer_data >> 3;
}
inline uint8_t get_oneshot_layer_state(void) {
    return oneshot_layer_data & 0b111;
}

#    ifdef SWAP_HANDS_ENABLE
enum {
    SHO_OFF,
    SHO_ACTIVE,  // Swap hands button was pressed, and we didn't send any swapped keys yet
    SHO_PRESSED, // Swap hands button is currently pressed
    SHO_USED,    // Swap hands button is still pressed, and we already sent swapped keys
} swap_hands_oneshot = SHO_OFF;
#    endif

#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
static uint16_t oneshot_layer_time = 0;
inline bool     has_oneshot_layer_timed_out() {
    return TIMER_DIFF_16(timer_read(), oneshot_layer_time) >= ONESHOT_TIMEOUT && !(get_oneshot_layer_state() & ONESHOT_TOGGLED);
}
#        ifdef SWAP_HANDS_ENABLE
static uint16_t oneshot_swaphands_time = 0;
inline bool     has_oneshot_swaphands_timed_out() {
    return TIMER_DIFF_16(timer_read(), oneshot_swaphands_time) >= ONESHOT_TIMEOUT && (swap_hands_oneshot == SHO_ACTIVE);
}
#        endif
#    endif

#    ifdef SWAP_HANDS_ENABLE

void set_oneshot_swaphands(void) {
    swap_hands_oneshot = SHO_PRESSED;
    swap_hands         = true;
#        if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_swaphands_time = timer_read();
    if (oneshot_layer_time != 0) {
        oneshot_layer_time = oneshot_swaphands_time;
    }
#        endif
}

void release_oneshot_swaphands(void) {
    if (swap_hands_oneshot == SHO_PRESSED) {
        swap_hands_oneshot = SHO_ACTIVE;
    }
    if (swap_hands_oneshot == SHO_USED) {
        clear_oneshot_swaphands();
    }
}

void use_oneshot_swaphands(void) {
    if (swap_hands_oneshot == SHO_PRESSED) {
        swap_hands_oneshot = SHO_USED;
    }
    if (swap_hands_oneshot == SHO_ACTIVE) {
        clear_oneshot_swaphands();
    }
}

void clear_oneshot_swaphands(void) {
    swap_hands_oneshot = SHO_OFF;
    swap_hands         = false;
#        if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_swaphands_time = 0;
#        endif
}

#    endif

/** \brief Set oneshot layer
 *
 * FIXME: needs doc
 */
void set_oneshot_layer(uint8_t layer, uint8_t state) {
    if (!keymap_config.oneshot_disable) {
        oneshot_layer_data = layer << 3 | state;
        layer_on(layer);
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        oneshot_layer_time = timer_read();
#    endif
        oneshot_layer_changed_kb(get_oneshot_layer());
    } else {
        layer_on(layer);
    }
}
/** \brief Reset oneshot layer
 *
 * FIXME: needs doc
 */
void reset_oneshot_layer(void) {
    oneshot_layer_data = 0;
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = 0;
#    endif
    oneshot_layer_changed_kb(get_oneshot_layer());
}
/** \brief Clear oneshot layer
 *
 * FIXME: needs doc
 */
void clear_oneshot_layer_state(oneshot_fullfillment_t state) {
    uint8_t start_state = oneshot_layer_data;
    oneshot_layer_data &= ~state;
    if ((!get_oneshot_layer_state() && start_state != oneshot_layer_data) && !keymap_config.oneshot_disable) {
        layer_off(get_oneshot_layer());
        reset_oneshot_layer();
    }
}
/** \brief Is oneshot layer active
 *
 * FIXME: needs doc
 */
bool is_oneshot_layer_active(void) {
    return get_oneshot_layer_state();
}

/** \brief set oneshot
 *
 * FIXME: needs doc
 */
void oneshot_set(bool active) {
    if (keymap_config.oneshot_disable != active) {
        keymap_config.oneshot_disable = active;
        eeconfig_update_keymap(keymap_config.raw);
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        dprintf("Oneshot: active: %d\n", active);
    }
}

/** \brief toggle oneshot
 *
 * FIXME: needs doc
 */
void oneshot_toggle(void) {
    oneshot_set(!keymap_config.oneshot_disable);
}

/** \brief enable oneshot
 *
 * FIXME: needs doc
 */
void oneshot_enable(void) {
    oneshot_set(true);
}

/** \brief disable oneshot
 *
 * FIXME: needs doc
 */
void oneshot_disable(void) {
    oneshot_set(false);
}

bool is_oneshot_enabled(void) {
    return keymap_config.oneshot_disable;
}

#endif

/** \brief Send keyboard report
 *
 * FIXME: needs doc
 */
void send_keyboard_report(void) {
    keyboard_report->mods = real_mods;
    keyboard_report->mods |= weak_mods;

#ifndef NO_ACTION_ONESHOT
    if (oneshot_mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        if (has_oneshot_mods_timed_out()) {
            dprintf("Oneshot: timeout\n");
            clear_oneshot_mods();
        }
#    endif
        keyboard_report->mods |= oneshot_mods;
        if (has_anykey(keyboard_report)) {
            clear_oneshot_mods();
        }
    }

#endif

#ifdef KEY_OVERRIDE_ENABLE
    // These need to be last to be able to properly control key overrides
    keyboard_report->mods &= ~suppressed_mods;
    keyboard_report->mods |= weak_override_mods;
#endif

    static report_keyboard_t last_report;

    /* Only send the report if there are changes to propagate to the host. */
    if (memcmp(keyboard_report, &last_report, sizeof(report_keyboard_t)) != 0) {
        memcpy(&last_report, keyboard_report, sizeof(report_keyboard_t));
        host_keyboard_send(keyboard_report);
    }
}

/** \brief Get mods
 *
 * FIXME: needs doc
 */
uint8_t get_mods(void) {
    return real_mods;
}
/** \brief add mods
 *
 * FIXME: needs doc
 */
void add_mods(uint8_t mods) {
    real_mods |= mods;
}
/** \brief del mods
 *
 * FIXME: needs doc
 */
void del_mods(uint8_t mods) {
    real_mods &= ~mods;
}
/** \brief set mods
 *
 * FIXME: needs doc
 */
void set_mods(uint8_t mods) {
    real_mods = mods;
}
/** \brief clear mods
 *
 * FIXME: needs doc
 */
void clear_mods(void) {
    real_mods = 0;
}

/** \brief get weak mods
 *
 * FIXME: needs doc
 */
uint8_t get_weak_mods(void) {
    return weak_mods;
}
/** \brief add weak mods
 *
 * FIXME: needs doc
 */
void add_weak_mods(uint8_t mods) {
    weak_mods |= mods;
}
/** \brief del weak mods
 *
 * FIXME: needs doc
 */
void del_weak_mods(uint8_t mods) {
    weak_mods &= ~mods;
}
/** \brief set weak mods
 *
 * FIXME: needs doc
 */
void set_weak_mods(uint8_t mods) {
    weak_mods = mods;
}
/** \brief clear weak mods
 *
 * FIXME: needs doc
 */
void clear_weak_mods(void) {
    weak_mods = 0;
}

#ifdef KEY_OVERRIDE_ENABLE
/** \brief set weak mods used by key overrides. DO not call this manually
 */
void set_weak_override_mods(uint8_t mods) {
    weak_override_mods = mods;
}
/** \brief clear weak mods used by key overrides. DO not call this manually
 */
void clear_weak_override_mods(void) {
    weak_override_mods = 0;
}

/** \brief set suppressed mods used by key overrides. DO not call this manually
 */
void set_suppressed_override_mods(uint8_t mods) {
    suppressed_mods = mods;
}
/** \brief clear suppressed mods used by key overrides. DO not call this manually
 */
void clear_suppressed_override_mods(void) {
    suppressed_mods = 0;
}
#endif

#ifndef NO_ACTION_ONESHOT
/** \brief get oneshot mods
 *
 * FIXME: needs doc
 */
uint8_t get_oneshot_mods(void) {
    return oneshot_mods;
}

void add_oneshot_mods(uint8_t mods) {
    if ((oneshot_mods & mods) != mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        oneshot_time = timer_read();
#    endif
        oneshot_mods |= mods;
        oneshot_mods_changed_kb(mods);
    }
}

void del_oneshot_mods(uint8_t mods) {
    if (oneshot_mods & mods) {
        oneshot_mods &= ~mods;
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        oneshot_time = oneshot_mods ? timer_read() : 0;
#    endif
        oneshot_mods_changed_kb(oneshot_mods);
    }
}

/** \brief set oneshot mods
 *
 * FIXME: needs doc
 */
void set_oneshot_mods(uint8_t mods) {
    if (!keymap_config.oneshot_disable) {
        if (oneshot_mods != mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
            oneshot_time = timer_read();
#    endif
            oneshot_mods = mods;
            oneshot_mods_changed_kb(mods);
        }
    }
}

/** \brief clear oneshot mods
 *
 * FIXME: needs doc
 */
void clear_oneshot_mods(void) {
    if (oneshot_mods) {
        oneshot_mods = 0;
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        oneshot_time = 0;
#    endif
        oneshot_mods_changed_kb(oneshot_mods);
    }
}
#endif

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_locked_mods_changed_user(uint8_t mods) {}

/** \brief Called when the locked one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_locked_mods_changed_kb(uint8_t mods) {
    oneshot_locked_mods_changed_user(mods);
}

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_mods_changed_user(uint8_t mods) {}

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_mods_changed_kb(uint8_t mods) {
    oneshot_mods_changed_user(mods);
}

/** \brief Called when the one shot layers have been changed.
 *
 * \param layer Contains the layer that is toggled on, or zero when toggled off.
 */
__attribute__((weak)) void oneshot_layer_changed_user(uint8_t layer) {}

/** \brief Called when the one shot layers have been changed.
 *
 * \param layer Contains the layer that is toggled on, or zero when toggled off.
 */
__attribute__((weak)) void oneshot_layer_changed_kb(uint8_t layer) {
    oneshot_layer_changed_user(layer);
}

/** \brief inspect keyboard state
 *
 * FIXME: needs doc
 */
uint8_t has_anymod(void) {
    return bitpop(real_mods);
}
