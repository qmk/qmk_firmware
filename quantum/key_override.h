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

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "action_layer.h"

/**
 * Key overrides allow you to send a different key-modifier combination or perform a custom action when a certain modifier-key combination is pressed.
 *
 * For example, you may configure a key override to send the delete key when shift + backspace are pressed together, or that your volume keys become screen brightness keys when holding ctrl. The possibilities are quite vast and the documentation contains a few examples for inspiration.
 *
 * See the documentation here: https://docs.qmk.fm/#/feature_key_overrides
 */

/** Bitfield defining which events are allowed to activate a key override. */
typedef enum {
    /** When the trigger key is pressed down. */
    ko_activation_key_down = (1 << 0),
    /** When another key is released. Only has an effect in conjunction with ko_option_exclusive_key_on_activate. */
    ko_activation_key_up = (1 << 1),
    /** When a necessary modifier is pressed down. */
    ko_activation_mod_down = (1 << 2),
    /** When a negative modifier is released. */
    ko_activation_mod_up = (1 << 3),

    ko_activation_events_all = ko_activation_key_down | ko_activation_key_up | ko_activation_mod_down | ko_activation_mod_up,
    /** The default activation events used by the ko_make_xxx functions. */
    ko_activation_events_default = ko_activation_key_down,
} ko_activation_event_t;

/** Bitfield with various options controlling the behavior of a key override. */
typedef enum {
    /** If set, any of the modifiers in trigger_modifiers will be enough to activate the override (logical OR of modifiers). If not set, all the modifiers in trigger_modifiers have to be pressed (logical AND of modifiers). */
    ko_option_one_mod = (1 << 0),
    /** If set, the override can only activate if no non-modifier key except the trigger key is down. */
    ko_option_exclusive_key_on_activate = (1 << 1),
    /** If set, the trigger key has to be the only non-modifier key that is pressed while the override is active. If another key is pressed, the opverride will be deactivated. */
    ko_option_exclusive_key_during_active = (1 << 2),
    /** Whether the trigger key should be registered again after the override is deactivated (only in case it is still physically pressed). */
    ko_option_reregister_trigger_on_deactivation = (1 << 3),

    /** The default options used by the ko_make_xxx functions. */
    ko_options_default = ko_option_exclusive_key_during_active,
} ko_option_t;

/** Defines a single key override */
typedef struct {
    // The basic keycode that triggers the override. This keycode MUST exclude modifiers. It can also be a custom keycode.
    uint16_t trigger; 

    // Which mods need to be down for activation. If both sides of mod are set (e.g. left ctrl and right ctrl) then only one is required to trigger (e.g. left ctrl suffices).
    uint8_t trigger_modifiers;

    // All activation events that may activate this override.
    ko_activation_event_t allowed_activation_events;

    // This is a BITMASK (!), defining which layers this override applies to. To use this override on layer i set the ith bit (1 << i).
    layer_state_t layers;

    // Which keys cannot be down: get_mods() & negative_modifier_mask must be 0. Can be used to disallow specific modifiers for fine-grained control.
    uint8_t negative_modifier_mask;

    // Modifiers to suppress when active. Can be used to suppress the trigger modifiers, as a trivial example.
    uint8_t suppressed_mods;

    // The complex keycode to send as replacement when this override is triggered. This may be a custom keycode or a key-modifier combination. Use in combination with suppressed_mods to get the correct modifiers to be sent if needed.
    uint16_t replacement;

    // Additional options controlling the behavior of the override.
    ko_option_t options;

    // If not NULL, this function will be called right before the replacement key is registered, along with the provided context and a flag indicating whether the override was activated or deactivated. This function allows you to run some custom actions for specific key overrides. If you return `false`, the replacement key is not registered/unregistered as it would normally. Return `true` to register and unregister the override normally.
    bool (*custom_action)(bool activated, void *context);

    // A context that will be passed to the custom action function if that is set.
    void *context;

    // If this points to false this override will not be used. Set to NULL to always have this override enabled.
    bool *enabled;
} key_override_t;

/** Define this as a null-terminated array of pointers to key overrides. These key overrides will be used by qmk. */
extern const key_override_t **key_overrides;

/** Turns key overrides on */
extern void key_override_on(void);

/** Turns key overrides off */
extern void key_override_off(void);

/** Toggles key overrides on */
extern void key_override_toggle(void);

/** Returns whether key overrides are enabled */
extern bool key_override_is_enabled(void);

/**
 *  Preferrably use these macros to create key overrides. They fix many of the options to a standard setting that should satisfy most basic use-cased. Only directly create a key_override_t struct when you need more fine grained control and these macros are not sufficient.
*/

/**
 * Convenience initializer to create a basic key override. Activates the override on all layers.
 */
#define ko_make_basic(trigger_mods, trigger_key, replacement_key) \
    ko_make_for_layers(trigger_mods, trigger_key, replacement_key, ~0)

/**
 * Convenience initializer to create a basic key override. Provide a bitmap (of type layer_state_t) with the bits set for each layer on which the override should activate.
 */
#define ko_make_for_layers(trigger_mods, trigger_key, replacement_key, layers) \
    ko_make_for_layers_and_negative_mods(trigger_mods, trigger_key, replacement_key, layers, 0)
/**                                                                                                                                                                                                                                                   \
 * Convenience initializer to create a basic key override. Provide a bitmap with the bits set for each layer on which the override should activate. Also provide a negative modifier mask, that is used to define which modifiers may not be pressed. \
 */
#define ko_make_for_layers_and_negative_mods(trigger_mods, trigger_key, replacement_key, layer_mask, negative_mask) \
    ((const key_override_t){                                                                \
        .trigger_modifiers                      = (trigger_mods),                           \
        .layers                                 = (layer_mask),                             \
        .suppressed_mods                        = (trigger_mods),                           \
        .allowed_activation_events              = ko_activation_events_default,             \
        .options                                = ko_options_default,                       \
        .negative_modifier_mask                 = (negative_mask),                          \
        .custom_action                          = NULL,                                     \
        .context                                = NULL,                                     \
        .trigger                                = (trigger_key),                            \
        .replacement                            = (replacement_key),                        \
        .enabled                                = NULL                                      \
    })
