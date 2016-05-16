#include <stdint.h>
#include "keyboard.h"
#include "action.h"
#include "util.h"
#include "action_layer.h"

#ifdef DEBUG_ACTION
#include "debug.h"
#else
#include "nodebug.h"
#endif


/*
 * Default Layer State
 */
uint32_t default_layer_state = 0;

static void default_layer_state_set(uint32_t state)
{
    debug("default_layer_state: ");
    default_layer_debug(); debug(" to ");
    default_layer_state = state;
    default_layer_debug(); debug("\n");
    clear_keyboard_but_mods(); // To avoid stuck keys
}

void default_layer_debug(void)
{
    dprintf("%08lX(%u)", default_layer_state, biton32(default_layer_state));
}

void default_layer_set(uint32_t state)
{
    default_layer_state_set(state);
}

#ifndef NO_ACTION_LAYER
void default_layer_or(uint32_t state)
{
    default_layer_state_set(default_layer_state | state);
}
void default_layer_and(uint32_t state)
{
    default_layer_state_set(default_layer_state & state);
}
void default_layer_xor(uint32_t state)
{
    default_layer_state_set(default_layer_state ^ state);
}
#endif


#ifndef NO_ACTION_LAYER
/*
 * Keymap Layer State
 */
uint32_t layer_state = 0;

static void layer_state_set(uint32_t state)
{
    dprint("layer_state: ");
    layer_debug(); dprint(" to ");
    layer_state = state;
    layer_debug(); dprintln();
    clear_keyboard_but_mods(); // To avoid stuck keys
}

void layer_clear(void)
{
    layer_state_set(0);
}

void layer_move(uint8_t layer)
{
    layer_state_set(1UL<<layer);
}

void layer_on(uint8_t layer)
{
    layer_state_set(layer_state | (1UL<<layer));
}

void layer_off(uint8_t layer)
{
    layer_state_set(layer_state & ~(1UL<<layer));
}

void layer_invert(uint8_t layer)
{
    layer_state_set(layer_state ^ (1UL<<layer));
}

void layer_or(uint32_t state)
{
    layer_state_set(layer_state | state);
}
void layer_and(uint32_t state)
{
    layer_state_set(layer_state & state);
}
void layer_xor(uint32_t state)
{
    layer_state_set(layer_state ^ state);
}

void layer_debug(void)
{
    dprintf("%08lX(%u)", layer_state, biton32(layer_state));
}
#endif

#if !defined(NO_ACTION_LAYER) && defined(PREVENT_STUCK_KEYS)
static uint8_t source_layers_cache[(MATRIX_ROWS * MATRIX_COLS + 7) / 8][MAX_LAYER_BITS];

static void update_source_layers_cache(keypos_t key, uint8_t layer);
static uint8_t read_source_layers_cache(keypos_t key);

static void update_source_layers_cache(keypos_t key, uint8_t layer) {
    uint8_t number = key.col + key.row * MATRIX_COLS;
    uint8_t row = number / 8;
    uint8_t mask = 1U << number % 8;
    for (int8_t column = MAX_LAYER_BITS - 1; column >= 0; --column) {
        mask_byte(&source_layers_cache[row][column], layer & _BV(column), mask);
    }
}

static uint8_t read_source_layers_cache(keypos_t key) {
    uint8_t number = key.col + key.row * MATRIX_COLS;
    uint8_t row = number / 8;
    uint8_t mask = 1U << number % 8;
    uint8_t layer = 0;
    for (int8_t column = MAX_LAYER_BITS - 1; column >= 0; --column) {
        if (source_layers_cache[row][column] & mask) layer |= _BV(column);
    }
    return layer;
}

uint8_t find_source_layer(keypos_t key) {
    uint32_t master_layer_state = layer_state | default_layer_state;
    /* scan from the highest layer to the lowest layer */
    for (int8_t layer = 31; layer >= 0; --layer) {
        if (master_layer_state & 1UL << layer) {
            if (action_for_key(layer, key).code != ACTION_TRANSPARENT) {
                return layer;
            }
        }
    }
    /* fall back to layer 0 */
    return 0;
}

/*
 * This function makes sure that the action triggered when each key is released
 * is the same as the one that was triggered when it was pressed. This is
 * important for the modifier keys because they can get stuck if layer
 * operations are performed while they are held down.
 */
uint8_t get_source_layer(keypos_t key, bool pressed) {
    if (pressed) {
        uint8_t layer = find_source_layer(key);
        update_source_layers_cache(key, layer);
        return layer;
    }
    return read_source_layers_cache(key);
}

#else
action_t layer_switch_get_action(keypos_t key) {
#   ifndef NO_ACTION_LAYER
    uint32_t master_layer_state = layer_state | default_layer_state;
    /* scan from the highest layer to the lowest layer */
    for (int8_t layer = 31; layer >= 0; --layer) {
        if (master_layer_state & 1UL << layer) {
            action_t action = action_for_key(layer, key);
            if (action.code != ACTION_TRANSPARENT) {
                return action;
            }
        }
    }
    /* fall back to layer 0 */
    return action_for_key(0, key);
#   else
    return action_for_key(biton32(default_layer_state), key);
#   endif
}

#endif
