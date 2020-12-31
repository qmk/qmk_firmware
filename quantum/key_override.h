#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "action_layer.h"

/**
 * Key overrides allow you to perform custom actions when a certain modifier-key combination is pressed. 
 * 
 * You can define custom actions for arbitrary modifier+key combinations: if modifiers x + key y are pressed, send modifiers w + key z instead of modifiers x + key y in the keyboard report.
 * This feature basically gives you the power of layers without having to use dedicated layer keys, allowing you to use arbitary modifier key combinations similarly to layers.
 * 
 * You may for example use a single key for media controls and use key overrides to trigger different actions:
 * - Simple key press: play/pause
 * - Ctrl + key: volume up
 * - Ctrl + shift + key: volume down
 * - Alt + key: next track
 * - Alt + shift + key: previous track
 * 
 * This list could continue, for example:
 * - Ctrl + alt + key: screen brightness up
 * - Ctrl + alt + shift + key: screen brightness down
 */

typedef struct {
    // The basic keycode that triggers the override. This keycode MUST exclude modifiers. It can also be a custom keycode.
    uint16_t trigger; 

    // Which mods need to be down for activation. If both sides of mod are set (e.g. left ctrl and right ctrl) then only one is required to trigger (e.g. left ctrl suffices).
    uint8_t trigger_modifiers;

    // This is a BITMASK (!), defining which layers this override applies to. To use this override on layer i set the ith bit (1 << i).
    layer_state_t layers;

    // If set to true, any of the modifiers in trigger_modifiers will be enough to activate the override (logical OR of modifiers). If set to false all the modifiers in trigger_modifiers have to be pressed (logical AND of modifiers).
    bool one_mod;

    // Which keys cannot be down: get_mods() & negative_modifier_mask must be 0. Can be used to disallow specific modifiers for fine-grained control.
    uint8_t negative_modifier_mask;

    // Whether allowing to activate this override when other keys are already down. This only concerns non-modifier keys.
    bool allows_other_keys_down_at_trigger;

    // Whether to deactivate the override an when another key is pressed down (while the override is active). This only concerns non-modifier keys.
    bool allows_other_keys_down_while_active;

    // Whether to only activate when the trigger key is pressed down while the necessary modifiers are already down. This can be useful for some overrides that would otherwise falsely trigger during quick typing. Setting this to false only works as expected for basic trigger keycodes (keys that appear in the keyboard report), and behaves like setting to true for non-basic trigger keycodes.
    bool trigger_only_on_trigger_down;

    // Modifiers to suppress when active. Can be used to suppress the trigger modifiers, as a trivial example.
    uint8_t suppressed_mods;

    // The complex keycode to send as replacement when this override is triggered. This may be a custom keycode or a key-modifier combination. Use in combination with suppressed_mods to get the correct modifiers to be sent if needed.
    uint16_t replacement;

    // Whether the trigger key should be registered again after the override is deactivated (only in case it is still physically pressed).
    bool reregister_trigger_after_completion;

    // If not NULL, this function will be called right before the replacement key is registered, along with the provided context and a flag indicating whether the override was activated or deactivated. This function allows you to run some custom actions for specific key overrides. If you return `false`, the replacement key is not registered/unregistered as it would normally. Return `true` to register and unregister the override normally.
    bool (*custom_action)(bool activated, void *context);

    // A context that will be passed to the custom action function if that is set.
    void *context;

    // If this points to false this override will not be used. Set to NULL to always have this override enabled.
    bool *enabled;
} key_override_t;

/**
 *  Define this as an array of pointers to key overrides.
 */
extern key_override_t **key_overrides;

// On/Off
extern void key_override_on(void);
extern void key_override_off(void);
extern void key_override_toggle(void);

extern bool key_override_is_enabled(void);

/**
 *  Preferrably use these macros to create key overrides. They fix many of the options to a standard setting that should satisfy most basic use-cased. Only directly create a key_override_t struct when you need more fine grained control and these macros are not sufficient.
*/

/**
 * Convenience initializer to create a basic key override. Activates the override on all layers.
 */
#define key_override_make_basic(trigger_mods, trigger_key, replacement_key) \
    key_override_make_for_layers(trigger_mods, trigger_key, replacement_key, ~0)

/**
 * Convenience initializer to create a basic key override. Provide a bitmap (of type layer_state_t) with the bits set for each layer on which the override should activate.
 */
#define key_override_make_for_layers(trigger_mods, trigger_key, replacement_key, layers) key_override_make_for_layers_and_negative_mods(trigger_mods, trigger_key, replacement_key, layers, 0)

/**
 * Convenience initializer to create a basic key override. Provide a bitmap with the bits set for each layer on which the override should activate. Also provide a negative modifier mask, that is used to define which modifiers may not be pressed.
 */
#define key_override_make_for_layers_and_negative_mods(trigger_mods, trigger_key, replacement_key, layer_mask, negative_mask) \
    ((key_override_t){                                                      \
        .trigger_modifiers                      = (trigger_mods),           \
        .one_mod                                = false,                    \
        .layers                                 = (layer_mask),                 \
        .suppressed_mods                        = (trigger_mods),           \
        .allows_other_keys_down_at_trigger      = true,                     \
        .allows_other_keys_down_while_active    = false,                    \
        .reregister_trigger_after_completion    = false,                    \
        .trigger_only_on_trigger_down           = true,                     \
        .negative_modifier_mask                 = (negative_mask),                        \
        .custom_action                          = NULL,                     \
        .context                                = NULL,                     \
        .trigger                                = (trigger_key),            \
        .replacement                            = (replacement_key),        \
        .enabled                                = NULL                      \
    })
