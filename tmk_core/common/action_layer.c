#include <stdint.h>
#include "keyboard.h"
#include "action.h"
#include "util.h"
#include "action_layer.h"

#ifdef DEBUG_ACTION
#    include "debug.h"
#else
#    include "nodebug.h"
#endif

/** \brief Default Layer State
 */
layer_state_t default_layer_state = 0;

/** \brief Default Layer State Set At user Level
 *
 * Run user code on default layer state change
 */
__attribute__((weak)) layer_state_t default_layer_state_set_user(layer_state_t state) { return state; }

/** \brief Default Layer State Set At Keyboard Level
 *
 *  Run keyboard code on default layer state change
 */
__attribute__((weak)) layer_state_t default_layer_state_set_kb(layer_state_t state) { return default_layer_state_set_user(state); }

/** \brief Default Layer State Set
 *
 * Static function to set the default layer state, prints debug info and clears keys
 */
static void default_layer_state_set(layer_state_t state) {
    state = default_layer_state_set_kb(state);
    debug("default_layer_state: ");
    default_layer_debug();
    debug(" to ");
    default_layer_state = state;
    default_layer_debug();
    debug("\n");
#ifdef STRICT_LAYER_RELEASE
    clear_keyboard_but_mods();  // To avoid stuck keys
#else
    clear_keyboard_but_mods_and_keys();  // Don't reset held keys
#endif
}

/** \brief Default Layer Print
 *
 * Print out the hex value of the 32-bit default layer state, as well as the value of the highest bit.
 */
void default_layer_debug(void) { dprintf("%08lX(%u)", default_layer_state, biton32(default_layer_state)); }

/** \brief Default Layer Set
 *
 * Sets the default layer state.
 */
void default_layer_set(layer_state_t state) { default_layer_state_set(state); }

#ifndef NO_ACTION_LAYER
/** \brief Default Layer Or
 *
 * Turns on the default layer based on matching bits between specifed layer and existing layer state
 */
void default_layer_or(layer_state_t state) { default_layer_state_set(default_layer_state | state); }
/** \brief Default Layer And
 *
 * Turns on default layer based on matching enabled bits between specifed layer and existing layer state
 */
void default_layer_and(layer_state_t state) { default_layer_state_set(default_layer_state & state); }
/** \brief Default Layer Xor
 *
 * Turns on default layer based on non-matching bits between specifed layer and existing layer state
 */
void default_layer_xor(layer_state_t state) { default_layer_state_set(default_layer_state ^ state); }
#endif

#ifndef NO_ACTION_LAYER
/** \brief Keymap Layer State
 */
layer_state_t layer_state = 0;

/** \brief Layer state set user
 *
 * Runs user code on layer state change
 */
__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) { return state; }

/** \brief Layer state set keyboard
 *
 * Runs keyboard code on layer state change
 */
__attribute__((weak)) layer_state_t layer_state_set_kb(layer_state_t state) { return layer_state_set_user(state); }

/** \brief Layer state set
 *
 * Sets the layer to match the specifed state (a bitmask)
 */
void layer_state_set(layer_state_t state) {
    state = layer_state_set_kb(state);
    dprint("layer_state: ");
    layer_debug();
    dprint(" to ");
    layer_state = state;
    layer_debug();
    dprintln();
#    ifdef STRICT_LAYER_RELEASE
    clear_keyboard_but_mods();  // To avoid stuck keys
#    else
    clear_keyboard_but_mods_and_keys();  // Don't reset held keys
#    endif
}

/** \brief Layer clear
 *
 * Turn off all layers
 */
void layer_clear(void) { layer_state_set(0); }

/** \brief Layer state is
 *
 * Return whether the given state is on (it might still be shadowed by a higher state, though)
 */
bool layer_state_is(uint8_t layer) { return layer_state_cmp(layer_state, layer); }

/** \brief Layer state compare
 *
 * Used for comparing layers {mostly used for unit testing}
 */
bool layer_state_cmp(layer_state_t cmp_layer_state, uint8_t layer) {
    if (!cmp_layer_state) {
        return layer == 0;
    }
    return (cmp_layer_state & (1UL << layer)) != 0;
}

/** \brief Layer move
 *
 * Turns on the given layer and turn off all other layers
 */
void layer_move(uint8_t layer) { layer_state_set(1UL << layer); }

/** \brief Layer on
 *
 * Turns on given layer
 */
void layer_on(uint8_t layer) { layer_state_set(layer_state | (1UL << layer)); }

/** \brief Layer off
 *
 * Turns off given layer
 */
void layer_off(uint8_t layer) { layer_state_set(layer_state & ~(1UL << layer)); }

/** \brief Layer invert
 *
 * Toggle the given layer (set it if it's unset, or unset it if it's set)
 */
void layer_invert(uint8_t layer) { layer_state_set(layer_state ^ (1UL << layer)); }

/** \brief Layer or
 *
 * Turns on layers based on matching bits between specifed layer and existing layer state
 */
void layer_or(layer_state_t state) { layer_state_set(layer_state | state); }
/** \brief Layer and
 *
 * Turns on layers based on matching enabled bits between specifed layer and existing layer state
 */
void layer_and(layer_state_t state) { layer_state_set(layer_state & state); }
/** \brief Layer xor
 *
 * Turns on layers based on non-matching bits between specifed layer and existing layer state
 */
void layer_xor(layer_state_t state) { layer_state_set(layer_state ^ state); }

/** \brief Layer debug printing
 *
 * Print out the hex value of the 32-bit layer state, as well as the value of the highest bit.
 */
void layer_debug(void) { dprintf("%08lX(%u)", layer_state, biton32(layer_state)); }
#endif

#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)
/** \brief source layer cache
 */

uint8_t source_layers_cache[(MATRIX_ROWS * MATRIX_COLS + 7) / 8][MAX_LAYER_BITS] = {{0}};

/** \brief update source layers cache
 *
 * Updates the cached keys when changing layers
 */
void update_source_layers_cache(keypos_t key, uint8_t layer) {
    const uint8_t key_number  = key.col + (key.row * MATRIX_COLS);
    const uint8_t storage_row = key_number / 8;
    const uint8_t storage_bit = key_number % 8;

    for (uint8_t bit_number = 0; bit_number < MAX_LAYER_BITS; bit_number++) {
        source_layers_cache[storage_row][bit_number] ^= (-((layer & (1U << bit_number)) != 0) ^ source_layers_cache[storage_row][bit_number]) & (1U << storage_bit);
    }
}

/** \brief read source layers cache
 *
 * reads the cached keys stored when the layer was changed
 */
uint8_t read_source_layers_cache(keypos_t key) {
    const uint8_t key_number  = key.col + (key.row * MATRIX_COLS);
    const uint8_t storage_row = key_number / 8;
    const uint8_t storage_bit = key_number % 8;
    uint8_t       layer       = 0;

    for (uint8_t bit_number = 0; bit_number < MAX_LAYER_BITS; bit_number++) {
        layer |= ((source_layers_cache[storage_row][bit_number] & (1U << storage_bit)) != 0) << bit_number;
    }

    return layer;
}
#endif

/** \brief Store or get action (FIXME: Needs better summary)
 *
 * Make sure the action triggered when the key is released is the same
 * one as the one triggered on press. It's important for the mod keys
 * when the layer is switched after the down event but before the up
 * event as they may get stuck otherwise.
 */
action_t store_or_get_action(bool pressed, keypos_t key) {
#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)
    if (disable_action_cache) {
        return layer_switch_get_action(key);
    }

    uint8_t layer;

    if (pressed) {
        layer = layer_switch_get_layer(key);
        update_source_layers_cache(key, layer);
    } else {
        layer = read_source_layers_cache(key);
    }
    return action_for_key(layer, key);
#else
    return layer_switch_get_action(key);
#endif
}

/** \brief Layer switch get layer
 *
 * Gets the layer based on key info
 */
uint8_t layer_switch_get_layer(keypos_t key) {
#ifndef NO_ACTION_LAYER
    action_t action;
    action.code = ACTION_TRANSPARENT;

    layer_state_t layers = layer_state | default_layer_state;
    /* check top layer first */
    for (int8_t i = sizeof(layer_state_t) * 8 - 1; i >= 0; i--) {
        if (layers & (1UL << i)) {
            action = action_for_key(i, key);
            if (action.code != ACTION_TRANSPARENT) {
                return i;
            }
        }
    }
    /* fall back to layer 0 */
    return 0;
#else
    return biton32(default_layer_state);
#endif
}

/** \brief Layer switch get layer
 *
 * Gets action code based on key position
 */
action_t layer_switch_get_action(keypos_t key) { return action_for_key(layer_switch_get_layer(key), key); }
