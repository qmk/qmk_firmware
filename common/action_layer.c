#include <stdint.h>
#include "keyboard.h"
#include "action.h"
#include "debug.h"
#include "util.h"
#include "action_layer.h"


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
    debug_hex32(default_layer_state);
    debug("("); debug_dec(biton32(default_layer_state)); debug(")");
}

void default_layer_set(uint8_t layer)
{
    default_layer_state_set(1UL<<layer);
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
    debug("layer_state: ");
    layer_debug(); debug(" to ");
    layer_state = state;
    layer_debug(); debug("\n");
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
    debug_hex32(layer_state);
    debug("("); debug_dec(biton32(layer_state)); debug(")");
}
#endif



action_t layer_switch_get_action(key_t key)
{
    action_t action;
    action.code = ACTION_TRANSPARENT;

#ifndef NO_ACTION_LAYER
    uint32_t layers = layer_state | default_layer_state;
    /* check top layer first */
    for (int8_t i = 31; i >= 0; i--) {
        if (layers & (1UL<<i)) {
            action = action_for_key(i, key);
            if (action.code != ACTION_TRANSPARENT) {
                return action;
            }
        }
    }
    /* fall back to layer 0 */
    action = action_for_key(0, key);
    return action;
#else
    action = action_for_key(biton32(default_layer_state), key);
    return action;
#endif
}
