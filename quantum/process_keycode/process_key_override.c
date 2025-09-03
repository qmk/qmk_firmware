/*
 * Copyright 2021 Jonas Gessner
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

#include "process_key_override.h"
#include "report.h"
#include "timer.h"
#include "debug.h"
#include "wait.h"
#include "action_util.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "keymap_introspection.h"

#ifndef KEY_OVERRIDE_REPEAT_DELAY
#    define KEY_OVERRIDE_REPEAT_DELAY 500
#endif

// For benchmarking the time it takes to call process_key_override on every key press (needs keyboard debugging enabled as well)
// #define BENCH_KEY_OVERRIDE

// For debug output (needs keyboard debugging enabled as well)
// #define DEBUG_KEY_OVERRIDE

#ifdef DEBUG_KEY_OVERRIDE
#    define key_override_printf dprintf
#else
#    define key_override_printf(str, ...) \
        {}
#endif

// Helpers

// Private functions implemented elsewhere in qmk/tmk
extern uint8_t extract_mod_bits(uint16_t code);
extern void    set_weak_override_mods(uint8_t mods);
extern void    clear_weak_override_mods(void);
extern void    set_suppressed_override_mods(uint8_t mods);
extern void    clear_suppressed_override_mods(void);

static uint16_t clear_mods_from(uint16_t keycode) {
    switch (keycode) {
        case QK_MODS ... QK_MODS_MAX:
            break;
        default:
            return keycode;
    }

    static const uint16_t all_mods = QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI | QK_RCTL | QK_RSFT | QK_RALT | QK_RGUI;

    return (keycode & ~(all_mods));
}

// Internal variables
static const key_override_t *active_override                 = NULL;
static bool                  active_override_trigger_is_down = false;

// Used to keep track of what non-modifier key was last pressed down. We never want to activate an override for a trigger key that is not the last non-mod key that was pressed down. OSes internally completely unregister a key that is held when a different key is held down after. We want to respect this here.
static uint16_t last_key_down = 0;
// When was the last key pressed down?
static uint32_t last_key_down_time = 0;

// What timestamp are we comparing to when waiting to register a deferred key?
static uint32_t defer_reference_time = 0;
// What delay should pass until deferred key is registered?
static uint32_t defer_delay = 0;

// Holds the keycode that should be registered at a later time, in order to not get false key presses
static uint16_t deferred_register = 0;

// TODO: in future maybe save in EEPROM?
static bool enabled = true;

// Forward decls
static const key_override_t *clear_active_override(const bool allow_reregister);

void key_override_on(void) {
    enabled = true;
    key_override_printf("Key override ON\n");
}

void key_override_off(void) {
    enabled = false;
    clear_active_override(false);
    key_override_printf("Key override OFF\n");
}

void key_override_toggle(void) {
    if (key_override_is_enabled()) {
        key_override_off();
    } else {
        key_override_on();
    }
}

bool key_override_is_enabled(void) {
    return enabled;
}

// Returns whether the modifiers that are pressed are such that the override should activate
static bool key_override_matches_active_modifiers(const key_override_t *override, const uint8_t mods) {
    // Check that negative keys pass
    if ((override->negative_mod_mask & mods) != 0) {
        return false;
    }

    // Immediately return true if the override requires no mods down
    if (override->trigger_mods == 0) {
        return true;
    }

    if ((override->options & ko_option_one_mod) != 0) {
        // At least one of the trigger modifiers must be down
        return (override->trigger_mods & mods) != 0;
    } else {
        // All trigger modifiers must be down, but each mod can be active on either side (if both sides are specified).

        // Which mods, regardless of side, are required?
        uint8_t one_sided_required_mods = (override->trigger_mods & 0b1111) | (override->trigger_mods >> 4);

        // Which of the required modifiers are active?
        uint8_t active_required_mods = override->trigger_mods & mods;

        // Move the active requird mods to one side
        uint8_t one_sided_active_required_mods = (active_required_mods & 0b1111) | (active_required_mods >> 4);

        // Check that there is a full match between the required one-sided mods and active required one sided mods
        return one_sided_active_required_mods == one_sided_required_mods;
    }

    return false;
}

static void schedule_deferred_register(const uint16_t keycode) {
    if (timer_elapsed32(last_key_down_time) < KEY_OVERRIDE_REPEAT_DELAY) {
        // Defer until KEY_OVERRIDE_REPEAT_DELAY has passed since the trigger key was pressed down. This emulates the behavior as holding down a key x, then holding down shift shortly after. Usually the shifted key X is not immediately produced, but rather a 'key repeat delay' passes before any repeated character is output.
        defer_reference_time = last_key_down_time;
        defer_delay          = KEY_OVERRIDE_REPEAT_DELAY;
    } else {
        // Wait a very short time when a modifier event triggers the override to avoid false activations when e.g. a modifier is pressed just before a key is released (with the intention of pairing the modifier with a different key), or a modifier is lifted shortly before the trigger key is lifted. Operating systems by default reject modifier-events that happen very close to a non-modifier event.
        defer_reference_time = timer_read32();
        defer_delay          = 50; // 50ms
    }
    deferred_register = keycode;
}

const key_override_t *clear_active_override(const bool allow_reregister) {
    if (active_override == NULL) {
        return NULL;
    }

    key_override_printf("Deactivating override\n");

    deferred_register = 0;

    // Clear the suppressed mods
    clear_suppressed_override_mods();

    // Unregister the replacement. First remove the weak override mods
    clear_weak_override_mods();

    const key_override_t *const old = active_override;

    const uint8_t mod_free_replacement = clear_mods_from(active_override->replacement);

    bool unregister_replacement = mod_free_replacement != KC_NO &&   // KC_NO is never registered
                                  mod_free_replacement < SAFE_RANGE; // Custom keycodes are never registered

    // Try firing the custom handler
    if (active_override->custom_action != NULL) {
        unregister_replacement &= active_override->custom_action(false, active_override->context);
    }

    // Then unregister the mod-free replacement key if desired
    if (unregister_replacement) {
        if (IS_BASIC_KEYCODE(mod_free_replacement)) {
            del_key(mod_free_replacement);
        } else {
            key_override_printf("NOT KEY 1\n");
            send_keyboard_report();
            unregister_code(mod_free_replacement);
        }
    }

    const uint16_t trigger = active_override->trigger;

    const bool reregister_trigger = allow_reregister &&                                                  // Check if allowed from caller
                                    (active_override->options & ko_option_no_reregister_trigger) == 0 && // Check if override allows
                                    active_override_trigger_is_down &&                                   // Check if trigger is even down
                                    trigger != KC_NO &&                                                  // KC_NO is never registered
                                    trigger < SAFE_RANGE;                                                // A custom keycode should not be registered

    // Optionally re-register the trigger if it is still down
    if (reregister_trigger) {
        key_override_printf("Re-registering trigger deferred: %u\n", trigger);

        // This will always be a modifier event, so defer always
        schedule_deferred_register(trigger);
    }

    send_keyboard_report();

    active_override                 = NULL;
    active_override_trigger_is_down = false;

    return old;
}

/** Checks if the key event is an allowed activation event for the provided override. Does not check things like whether the correct mods or correct trigger key is down. */
static bool check_activation_event(const key_override_t *override, const bool key_down, const bool is_mod) {
    ko_option_t options = override->options;

    if ((options & ko_options_all_activations) == 0) {
        // No activation option provided at all. This is wrong, but let's assume the default activations (ko_options_all_activations) were meant...
        options = ko_options_all_activations;
    }

    if (is_mod) {
        if (key_down) {
            return (options & ko_option_activation_required_mod_down) != 0;
        } else {
            return (options & ko_option_activation_negative_mod_up) != 0;
        }
    } else {
        if (key_down) {
            return (options & ko_option_activation_trigger_down) != 0;
        } else {
            return false;
        }
    }
}

/** Iterates through the list of key overrides and tries activating each, until it finds one that activates or reaches the end of overrides. Returns true if the key action for `keycode` should be sent */
static bool try_activating_override(const uint16_t keycode, const uint8_t layer, const bool key_down, const bool is_mod, const uint8_t active_mods, bool *activated) {
    if (key_override_count() == 0) {
        return true;
    }

    for (uint8_t i = 0; i < key_override_count(); i++) {
        const key_override_t *const override = key_override_get(i);

        // End of array
        if (override == NULL) {
            break;
        }

        // Fast, but not full mods check. Most key presses will not have any mods down, and most overrides will require mods. Hence here we filter overrides that require mods to be down while no mods are down
        if (active_mods == 0 && override->trigger_mods != 0) {
            key_override_printf("Not activating override: Modifiers don't match\n");
            continue;
        }

        // Check layer
        if ((override->layers & (1 << layer)) == 0) {
            key_override_printf("Not activating override: Not set to activate on pressed layer\n");
            continue;
        }

        // Check allowed activation events
        if (!check_activation_event(override, key_down, is_mod)) {
            key_override_printf("Not activating override: Activation event not allowed\n");
            continue;
        }

        const bool is_trigger = override->trigger == keycode;

        // Check if trigger lifted. This is a small optimization in order to skip the remaining checks
        if (is_trigger && !key_down) {
            key_override_printf("Not activating override: Trigger lifted\n");
            continue;
        }

        // If the trigger is KC_NO it means 'no key', so only the required modifiers need to be down.
        const bool no_trigger = override->trigger == KC_NO;

        // Check if aleady active
        if (override == active_override) {
            key_override_printf("Not activating override: Alerady actived\n");
            continue;
        }

        // Check if enabled
        if (override->enabled != NULL && !((*(override->enabled) & 1))) {
            key_override_printf("Not activating override: Not enabled\n");
            continue;
        }

        // Check mods precisely
        if (!key_override_matches_active_modifiers(override, active_mods)) {
            key_override_printf("Not activating override: Modifiers don't match\n");
            continue;
        }

        // Check if trigger key is down.
        const bool trigger_down = is_trigger && key_down;

        // At this point, all requirements for activation are checked, except whether the trigger key is pressed. Now we check if the required trigger is down
        // If no trigger key is required, yes.
        // If the trigger was just pressed, yes.
        // If the last non-mod key that was pressed down is the trigger key, yes.
        bool should_activate = no_trigger || trigger_down || last_key_down == override->trigger;

        if (!should_activate) {
            key_override_printf("Not activating override. Trigger not down\n");
            continue;
        }

        key_override_printf("Activating override\n");

        clear_active_override(false);

#ifdef DUMMY_MOD_NEUTRALIZER_KEYCODE
        // Send a dummy keycode before unregistering the modifier(s)
        // so that suppressing the modifier(s) doesn't falsely get interpreted
        // by the host OS as a tap of a modifier key.
        // For example, unintended activations of the start menu on Windows when
        // using a GUI+<kc> key override with suppressed mods.
        neutralize_flashing_modifiers(active_mods);
#endif

        active_override                 = override;
        active_override_trigger_is_down = true;

        set_suppressed_override_mods(override->suppressed_mods);

        if (!trigger_down && !no_trigger) {
            // When activating a key override the trigger is is always unregistered. In the case where the key that newly pressed is not the trigger key, we have to explicitly remove the trigger key from the keyboard report. If the trigger was just pressed down we simply suppress the event which also has the effect of the trigger key not being registered in the keyboard report.
            if (IS_BASIC_KEYCODE(override->trigger)) {
                del_key(override->trigger);
            } else {
                unregister_code(override->trigger);
            }
        }

        const uint16_t mod_free_replacement = clear_mods_from(override->replacement);

        bool register_replacement = mod_free_replacement != KC_NO &&   // KC_NO is never registered
                                    mod_free_replacement < SAFE_RANGE; // Custom keycodes are never registered

        // Try firing the custom handler
        if (override->custom_action != NULL) {
            register_replacement &= override->custom_action(true, override->context);
        }

        if (register_replacement) {
            const uint8_t override_mods = extract_mod_bits(override->replacement);
            set_weak_override_mods(override_mods);

            // If this is a modifier event that activates the key override we _always_ defer the actual full activation of the override
            if (is_mod) {
                key_override_printf("Deferring register replacement key\n");
                schedule_deferred_register(mod_free_replacement);
                send_keyboard_report();
            } else {
                if (IS_BASIC_KEYCODE(mod_free_replacement)) {
                    add_key(mod_free_replacement);
                } else {
                    key_override_printf("NOT KEY 2\n");
                    send_keyboard_report();
                    // On macOS there seems to be a race condition when it comes to the keyboard report and consumer keycodes. It seems the OS may recognize a consumer keycode before an updated keyboard report, even if the keyboard report is actually sent before the consumer key. I assume it is some sort of race condition because it happens infrequently and very irregularly. Waiting for about at least 10ms between sending the keyboard report and sending the consumer code has shown to fix this.
                    wait_ms(10);
                    register_code(mod_free_replacement);
                }
            }
        } else {
            // If not registering the replacement key send keyboard report to update the unregistered keys.
            send_keyboard_report();
        }

        *activated = true;

        // If the trigger is down, suppress the event so that it does not get added to the keyboard report.
        return !trigger_down;
    }

    *activated = false;

    return true;
}

void key_override_task(void) {
    if (deferred_register == 0) {
        return;
    }

    if (timer_elapsed32(defer_reference_time) >= defer_delay) {
        key_override_printf("Registering deferred key\n");
        register_code16(deferred_register);
        deferred_register    = 0;
        defer_reference_time = 0;
        defer_delay          = 0;
    }
}

bool process_key_override(const uint16_t keycode, const keyrecord_t *const record) {
#ifdef BENCH_KEY_OVERRIDE
    uint16_t start = timer_read();
#endif

    const bool key_down = record->event.pressed;
    const bool is_mod   = IS_MODIFIER_KEYCODE(keycode);

    if (key_down) {
        switch (keycode) {
            case QK_KEY_OVERRIDE_TOGGLE:
                key_override_toggle();
                return false;

            case QK_KEY_OVERRIDE_ON:
                key_override_on();
                return false;

            case QK_KEY_OVERRIDE_OFF:
                key_override_off();
                return false;

            default:
                break;
        }
    }

    if (!enabled) {
        return true;
    }

    uint8_t effective_mods = get_mods();

#ifdef KEY_OVERRIDE_INCLUDE_WEAK_MODS
    effective_mods |= get_weak_mods();
#endif

#ifndef NO_ACTION_ONESHOT
    // Locked one shot mods are added to get_mods(), I think (why??) while oneshot mods are in get_oneshot_mods(). Still OR with get_locked_oneshot_mods because that's where those mods _should_ be saved.
    effective_mods |= get_oneshot_locked_mods() | get_oneshot_mods();
#endif

    if (is_mod) {
        // The mods returned from get_mods() will be updated with this new event _after_ this code runs. Hence we manually update the effective mods here to really know the effective mods.
        if (key_down) {
            effective_mods |= MOD_BIT(keycode);
        } else {
            effective_mods &= ~MOD_BIT(keycode);
        }
    } else {
        if (key_down) {
            last_key_down      = keycode;
            last_key_down_time = timer_read32();
            deferred_register  = 0;
        }

        // The last key that was pressed was just released. No more keys are therefore sending input
        if (!key_down && keycode == last_key_down) {
            last_key_down      = 0;
            last_key_down_time = 0;
            // We also cancel any deferred registers because, again, no keys are sending any input. Only the last key that is pressed creates an input – this key was just lifted.
            deferred_register = 0;
        }
    }

    key_override_printf("key down: %u keycode: %u is mod: %u effective mods: %u\n", key_down, keycode, is_mod, effective_mods);

    bool send_key_action = true;
    bool activated       = false;

    // Non-mod key up events never activate a key override
    if (is_mod || key_down) {
        // Get the exact layer that was hit. It will be cached at this point
        const uint8_t layer = read_source_layers_cache(record->event.key);

        // Use blocked to ensure the same override is not activated again immediately after it is deactivated
        send_key_action = try_activating_override(keycode, layer, key_down, is_mod, effective_mods, &activated);

        if (!send_key_action) {
            send_keyboard_report();
        }
    }

    if (!activated && active_override != NULL) {
        if (is_mod) {
            // Check if necessary modifier of current override goes up or a negative mod goes down
            if (!key_override_matches_active_modifiers(active_override, effective_mods)) {
                key_override_printf("Deactivating override because necessary modifier lifted or negative mod pressed\n");
                clear_active_override(true);
            }
        } else {
            // Check if trigger of current override goes up or if override does not allow additional keys to be down and another key goes down
            const bool is_trigger        = keycode == active_override->trigger;
            bool       should_deactivate = false;

            // Check if trigger key lifted
            if (is_trigger && !key_down) {
                should_deactivate               = true;
                active_override_trigger_is_down = false;
                key_override_printf("Deactivating override because trigger key up\n");
            }

            // Check if another key was pressed
            if (key_down && (active_override->options & ko_option_no_unregister_on_other_key_down) == 0) {
                should_deactivate = true;
                key_override_printf("Deactivating override because another key was pressed\n");
            }

            if (should_deactivate) {
                clear_active_override(false);
            }
        }
    }

#ifdef BENCH_KEY_OVERRIDE
    uint16_t elapsed = timer_elapsed(start);

    dprintf("Processing key overrides took: %u ms\n", elapsed);
#endif

    return send_key_action;
}
