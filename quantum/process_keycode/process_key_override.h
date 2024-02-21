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
#include <stdint.h>
#include "action.h"
#include "action_layer.h"

/**
 * Key overrides allow you to send a different key-modifier combination or perform a custom action when a certain modifier-key combination is pressed.
 *
 * For example, you may configure a key override to send the delete key when shift + backspace are pressed together, or that your volume keys become screen brightness keys when holding ctrl. The possibilities are quite vast and the documentation contains a few examples for inspiration.
 *
 * See the documentation and examples here: https://docs.qmk.fm/#/feature_key_overrides
 */

/** Bitfield with various options controlling the behavior of a key override. */
typedef enum {
    /** Allow activating when the trigger key is pressed down. */
    ko_option_activation_trigger_down = (1 << 0),
    /** Allow activating when a necessary modifier is pressed down. */
    ko_option_activation_required_mod_down = (1 << 1),
    /** Allow activating when a negative modifier is released. */
    ko_option_activation_negative_mod_up = (1 << 2),

    ko_options_all_activations = ko_option_activation_negative_mod_up | ko_option_activation_required_mod_down | ko_option_activation_trigger_down,

    /** If set, any of the modifiers in trigger_mods will be enough to activate the override (logical OR of modifiers). If not set, all the modifiers in trigger_mods have to be pressed (logical AND of modifiers). */
    ko_option_one_mod = (1 << 3),

    /** If set, the trigger key will never be registered again after the override is deactivated. */
    ko_option_no_reregister_trigger = (1 << 4),

    /** If set, the override will not deactivate when another key is pressed down. Use only if you really know you need this. */
    ko_option_no_unregister_on_other_key_down = (1 << 5),

    /** The default options used by the ko_make_xxx functions. */
    ko_options_default = ko_options_all_activations,
} ko_option_t;

/** Defines a single key override */
typedef struct {
    // The non-modifier keycode that triggers the override. This keycode, and the necessary modifiers (trigger_mods) must be pressed to activate this override. Set this to the keycode of the key that should activate the override. Set to KC_NO to require only the necessary modifiers to be pressed and no non-modifier.
    uint16_t trigger;

    // Which mods need to be down for activation. If both sides of a modifier are set (e.g. left ctrl and right ctrl) then only one is required to be pressed (e.g. left ctrl suffices). Use the MOD_MASK_XXX and MOD_BIT() macros for this.
    uint8_t trigger_mods;

    // This is a BITMASK (!), defining which layers this override applies to. To use this override on layer i set the ith bit (1 << i).
    layer_state_t layers;

    // Which modifiers cannot be down. It must hold that (active_mods & negative_mod_mask) == 0, otherwise the key override will not be activated. An active override will be deactivated once this is no longer true.
    uint8_t negative_mod_mask;

    // Modifiers to 'suppress' while the override is active. To suppress a modifier means that even though the modifier key is held down, the host OS sees the modifier as not pressed. Can be used to suppress the trigger modifiers, as a trivial example.
    uint8_t suppressed_mods;

    // The complex keycode to send as replacement when this override is triggered. This can be a simple keycode, a key-modifier combination (e.g. C(KC_A)), or KC_NO (to register no replacement keycode). Use in combination with suppressed_mods to get the correct modifiers to be sent.
    uint16_t replacement;

    // Options controlling the behavior of the override, such as what actions are allowed to activate the override.
    ko_option_t options;

    // If not NULL, this function will be called right before the replacement key is registered, along with the provided context and a flag indicating whether the override was activated or deactivated. This function allows you to run some custom actions for specific key overrides. If you return `false`, the replacement key is not registered/unregistered as it would normally. Return `true` to register and unregister the override normally.
    bool (*custom_action)(bool activated, void *context);

    // A context that will be passed to the custom action function.
    void *context;

    // If this points to false this override will not be used. Set to NULL to always have this override enabled.
    bool *enabled;
} key_override_t;

/** Define this as a null-terminated array of pointers to key overrides. These key overrides will be used by qmk. */
extern const key_override_t **key_overrides;

/** Turns key overrides on */
void key_override_on(void);

/** Turns key overrides off */
void key_override_off(void);

/** Toggles key overrides on */
void key_override_toggle(void);

/** Returns whether key overrides are enabled */
bool key_override_is_enabled(void);

/** Handling of key overrides and its implemented keycodes */
bool process_key_override(const uint16_t keycode, const keyrecord_t *const record);

/** Perform any deferred keys */
void key_override_task(void);

/**
 *  Preferrably use these macros to create key overrides. They fix many of the options to a standard setting that should satisfy most basic use-cases. Only directly create a key_override_t struct when you really need to.
 */

// clang-format off

/**
 * Convenience initializer to create a basic key override. Activates the override on all layers.
 */
#define ko_make_basic(trigger_mods, trigger_key, replacement_key) \
    ko_make_with_layers(trigger_mods, trigger_key, replacement_key, ~0)

/**
 * Convenience initializer to create a basic key override. Provide a bitmap (of type layer_state_t) with the bits set for each layer on which the override should activate.
 */
#define ko_make_with_layers(trigger_mods, trigger_key, replacement_key, layers) \
    ko_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, layers, 0)

/**
 * Convenience initializer to create a basic key override. Provide a bitmap with the bits set for each layer on which the override should activate. Also provide a negative modifier mask, that is used to define which modifiers may not be pressed.
 */
#define ko_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, layers, negative_mask) \
    ko_make_with_layers_negmods_and_options(trigger_mods, trigger_key, replacement_key, layers, negative_mask, ko_options_default)

 /**
  *  Convenience initializer to create a basic key override. Provide a bitmap with the bits set for each layer on which the override should activate. Also provide a negative modifier mask, that is used to define which modifiers may not be pressed. Provide options for additional control of the behavior of the override.
 */
#define ko_make_with_layers_negmods_and_options(trigger_mods_, trigger_key, replacement_key, layer_mask, negative_mask, options_) \
    ((const key_override_t){                                                                \
        .trigger_mods                           = (trigger_mods_),                          \
        .layers                                 = (layer_mask),                             \
        .suppressed_mods                        = (trigger_mods_),                          \
        .options                                = (options_),                               \
        .negative_mod_mask                      = (negative_mask),                          \
        .custom_action                          = NULL,                                     \
        .context                                = NULL,                                     \
        .trigger                                = (trigger_key),                            \
        .replacement                            = (replacement_key),                        \
        .enabled                                = NULL                                      \
    })

// clang-format on
