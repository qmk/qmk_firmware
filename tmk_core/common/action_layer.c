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


/** \brief Default Layer State
 */
uint32_t default_layer_state = 0;

/** \brief Default Layer State Set At Keyboard Level
 *
 * FIXME: Needs docs
 */
__attribute__((weak))
uint32_t default_layer_state_set_kb(uint32_t state) {
    return state;
}

/** \brief Default Layer State Set
 *
 * FIXME: Needs docs
 */
static void default_layer_state_set(uint32_t state)
{
    state = default_layer_state_set_kb(state);
    debug("default_layer_state: ");
    default_layer_debug(); debug(" to ");
    default_layer_state = state;
    default_layer_debug(); debug("\n");
    clear_keyboard_but_mods(); // To avoid stuck keys
}

/** \brief Default Layer Print
 *
 * FIXME: Needs docs
 */
void default_layer_debug(void)
{
    dprintf("%08lX(%u)", default_layer_state, biton32(default_layer_state));
}

/** \brief Default Layer Set
 *
 * FIXME: Needs docs
 */
void default_layer_set(uint32_t state)
{
    default_layer_state_set(state);
}

#ifndef NO_ACTION_LAYER
/** \brief Default Layer Or
 *
 * FIXME: Needs docs
 */
void default_layer_or(uint32_t state)
{
    default_layer_state_set(default_layer_state | state);
}
/** \brief Default Layer And
 *
 * FIXME: Needs docs
 */
void default_layer_and(uint32_t state)
{
    default_layer_state_set(default_layer_state & state);
}
/** \brief Default Layer Xor
 *
 * FIXME: Needs docs
 */
void default_layer_xor(uint32_t state)
{
    default_layer_state_set(default_layer_state ^ state);
}
#endif


#ifndef NO_ACTION_LAYER
/** \brief Keymap Layer State
 */
uint32_t layer_state = 0;

/** \brief Layer state set user
 *
 * FIXME: Needs docs
 */
__attribute__((weak))
uint32_t layer_state_set_user(uint32_t state) {
    return state;
}

/** \brief Layer state set keyboard
 *
 * FIXME: Needs docs
 */
__attribute__((weak))
uint32_t layer_state_set_kb(uint32_t state) {
    return layer_state_set_user(state);
}

/** \brief Layer state set
 *
 * FIXME: Needs docs
 */
void layer_state_set(uint32_t state)
{
    state = layer_state_set_kb(state);
    dprint("layer_state: ");
    layer_debug(); dprint(" to ");
    layer_state = state;
    layer_debug(); dprintln();
    clear_keyboard_but_mods(); // To avoid stuck keys
}

/** \brief Layer clear
 *
 * FIXME: Needs docs
 */
void layer_clear(void)
{
    layer_state_set(0);
}

/** \brief Layer state is
 *
 * FIXME: Needs docs
 */
bool layer_state_is(uint8_t layer)
{
    return layer_state_cmp(layer_state, layer);
}

/** \brief Layer state compare
 *
 * FIXME: Needs docs
 */
bool layer_state_cmp(uint32_t cmp_layer_state, uint8_t layer) {
    if (!cmp_layer_state) { return layer == 0; }
    return (cmp_layer_state & (1UL<<layer)) != 0;
}

/** \brief Layer move
 *
 * FIXME: Needs docs
 */
void layer_move(uint8_t layer)
{
    layer_state_set(1UL<<layer);
}

/** \brief Layer on
 *
 * FIXME: Needs docs
 */
void layer_on(uint8_t layer)
{
    layer_state_set(layer_state | (1UL<<layer));
}

/** \brief Layer off
 *
 * FIXME: Needs docs
 */
void layer_off(uint8_t layer)
{
    layer_state_set(layer_state & ~(1UL<<layer));
}

/** \brief Layer invert
 *
 * FIXME: Needs docs
 */
void layer_invert(uint8_t layer)
{
    layer_state_set(layer_state ^ (1UL<<layer));
}

/** \brief Layer or
 *
 * FIXME: Needs docs
 */
void layer_or(uint32_t state)
{
    layer_state_set(layer_state | state);
}
/** \brief Layer and
 *
 * FIXME: Needs docs
 */
void layer_and(uint32_t state)
{
    layer_state_set(layer_state & state);
}
/** \brief Layer xor
 *
 * FIXME: Needs docs
 */
void layer_xor(uint32_t state)
{
    layer_state_set(layer_state ^ state);
}

/** \brief Layer debug printing
 *
 * FIXME: Needs docs
 */
void layer_debug(void)
{
    dprintf("%08lX(%u)", layer_state, biton32(layer_state));
}
#endif

#if !defined(NO_ACTION_LAYER) && defined(PREVENT_STUCK_MODIFIERS)
static const uint8_t layer_cache_mask = (1u << MAX_LAYER_BITS) - 1;

/** \brief Get the pointer to the source layer cache for a connected matrix
 *
 * Implement this if you support multiple matrices, see qwiic_keyboard.c for an example
 * NOTE: The matrix index 0 is the first remote matrix, the function is not called for the master
 */
__attribute__((weak))
uint8_t* multimatrix_get_source_layers_cache(uint8_t matrix) {
    return 0;
}

static uint8_t* get_source_layers_cache(keymatrix_t key) {
  if (key.matrix == 0) {
    static uint8_t source_layers_cache[(MATRIX_ROWS * MATRIX_COLS * MAX_LAYER_BITS + 7) / 8] = {0};
    return source_layers_cache;
  } else {
    return multimatrix_get_source_layers_cache(key.matrix - 1);
  }
}

void update_source_layers_cache(keymatrix_t key, uint8_t layer)
{
  const uint8_t num_cols = keyboard_get_num_cols(key.matrix);
  const uint8_t num_rows = keyboard_get_num_rows(key.matrix);
  const uint16_t num_cache_bytes = get_source_layers_cache_size(num_cols, num_rows);
  uint8_t* cache = get_source_layers_cache(key);
  const uint16_t key_number = key.pos.col + (key.pos.row * num_cols);
  const uint32_t bit_number = key_number * MAX_LAYER_BITS;
  const uint16_t byte_number = bit_number / 8;
  if (byte_number >= num_cache_bytes) {
    return;
  }
  const uint8_t bit_position = bit_number % 8;
  int8_t shift = 16 - MAX_LAYER_BITS - bit_position;

  if (shift > 8 ) {
    // We need to write only one byte
    shift -= 8;
    const uint8_t mask = layer_cache_mask << shift;
    const uint8_t shifted_layer = layer << shift;
    cache[byte_number] = (shifted_layer & mask) | (cache[byte_number] & (~mask));
  } else {
    if (byte_number + 1 >= num_cache_bytes) {
      return;
    }
    // We need to write two bytes
    uint16_t value = layer;
    uint16_t mask = layer_cache_mask;
    value <<= shift;
    mask <<= shift;

    uint16_t masked_value = value & mask;
    uint16_t inverse_mask = ~mask;

    // This could potentially be done with a single write, but then we have to assume the endian
    cache[byte_number + 1] = masked_value | (cache[byte_number + 1] & (inverse_mask));
    masked_value >>= 8;
    inverse_mask >>= 8;
    cache[byte_number] = masked_value | (cache[byte_number] & (inverse_mask));
  }
}

uint8_t read_source_layers_cache(keymatrix_t key)
{
  const uint8_t num_cols = keyboard_get_num_cols(key.matrix);
  const uint8_t num_rows = keyboard_get_num_rows(key.matrix);
  const uint16_t num_cache_bytes = get_source_layers_cache_size(num_cols, num_rows);
  uint8_t* cache = get_source_layers_cache(key);
  const uint16_t key_number = key.pos.col + (key.pos.row * num_cols);
  const uint32_t bit_number = key_number * MAX_LAYER_BITS;
  const uint16_t byte_number = bit_number / 8;
  if (byte_number >= num_cache_bytes) {
    return 0;
  }
  const uint8_t bit_position = bit_number % 8;

  int8_t shift = 16 - MAX_LAYER_BITS - bit_position;

  if (shift > 8 ) {
    // We need to read only one byte
    shift -= 8;
    return (cache[byte_number] >> shift) & layer_cache_mask;
  } else {
    if (byte_number + 1 >= num_cache_bytes) {
      return 0;
    }
    // Otherwise read two bytes
    // This could potentially be done with a single read, but then we have to assume the endian
    uint16_t value = cache[byte_number] << 8 | cache[byte_number + 1];
    return (value >> shift) & layer_cache_mask;
  }
}

uint8_t get_source_layers_cache_size(uint8_t num_cols, uint8_t num_rows) {
  return (num_rows * num_cols * MAX_LAYER_BITS + 7) / 8;
}
#endif

/** \brief Store or get action (FIXME: Needs better summary)
 *
 * Make sure the action triggered when the key is released is the same
 * one as the one triggered on press. It's important for the mod keys
 * when the layer is switched after the down event but before the up
 * event as they may get stuck otherwise.
 */
action_t store_or_get_action(bool pressed, keymatrix_t key)
{
#if !defined(NO_ACTION_LAYER) && defined(PREVENT_STUCK_MODIFIERS)
    if (disable_action_cache) {
        return layer_switch_get_action(key);
    }

    uint8_t layer;

    if (pressed) {
        layer = layer_switch_get_layer(key);
        update_source_layers_cache(key, layer);
    }
    else {
        layer = read_source_layers_cache(key);
    }
    return action_for_key(layer, key);
#else
    return layer_switch_get_action(key);
#endif
}


/** \brief Layer switch get layer
 *
 * FIXME: Needs docs
 */
int8_t layer_switch_get_layer(keymatrix_t key)
{
#ifndef NO_ACTION_LAYER
    action_t action;
    action.code = ACTION_TRANSPARENT;

    uint32_t layers = layer_state | default_layer_state;
    /* check top layer first */
    for (int8_t i = 31; i >= 0; i--) {
        if (layers & (1UL<<i)) {
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
 * FIXME: Needs docs
 */
action_t layer_switch_get_action(keymatrix_t key)
{
    return action_for_key(layer_switch_get_layer(key), key);
}
