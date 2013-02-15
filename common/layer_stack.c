#include <stdint.h>
#include "keyboard.h"
#include "layer_stack.h"
#include "debug.h"


static uint8_t top_layer = 0;

/* [0] always works as sentinel and not used for store.*/
static layer_item_t layer_stack[LAYER_STACK_SIZE] = {};

bool layer_stack_push(uint8_t layer)
{
    for (uint8_t i = 1; i < LAYER_STACK_SIZE; i++) {
        if (!layer_stack[i].used) {
            layer_stack[i] = (layer_item_t){ .layer = layer,
                                              .next = top_layer,
                                              .used = true };
            top_layer = i;
            return true;
        }
    }
    return false;
}

bool layer_stack_pop(void)
{
    if (layer_stack[top_layer].used) {
        uint8_t popped = top_layer;
        top_layer = layer_stack[popped].next;
        layer_stack[popped] = (layer_item_t){};
        return true;
    }
    return false;
}

bool layer_stack_remove(uint8_t layer)
{
    if (layer_stack[top_layer].used && layer_stack[top_layer].layer == layer) {
        layer_stack_pop();
        debug("layer_stack_remove: top_layer\n");
        return true;
    }

    for (uint8_t i = top_layer; layer_stack[i].used; i = layer_stack[i].next) {
        debug("layer_stack_remove: ["); debug_dec(i); debug("]");
        debug_dec(layer_stack[i].layer); debug("\n");
        uint8_t removed = layer_stack[i].next;
        if (layer_stack[removed].used && layer_stack[removed].layer == layer) {
            layer_stack[i].next = layer_stack[removed].next;
            layer_stack[removed] = (layer_item_t){};
            debug("layer_stack_remove: removed.\n");
            return true;
        }
    }
    return false;
}

bool layer_stack_remove_then_push(uint8_t layer)
{
    layer_stack_remove(layer);
    return layer_stack_push(layer);
}

bool layer_stack_remove_or_push(uint8_t layer)
{
    return (layer_stack_remove(layer)) || layer_stack_push(layer);
}

void layer_stack_debug(void)
{
    debug("layer_stack: ");
    layer_item_t item = layer_stack[top_layer];
    while (item.used) {
        debug_dec(item.layer);
        debug("["); debug_dec(item.next); debug("]");
        item = layer_stack[item.next];
    }
    debug("\n");
}



action_t layer_stack_get_action(key_t key)
{
    action_t action;
    action.code = ACTION_TRANSPARENT;

    /* layer stack */
    for (layer_item_t i = layer_stack[top_layer]; i.used; i = layer_stack[i.next]) {
        action = action_for_key(i.layer, key);
        if (action.code != ACTION_TRANSPARENT) {
            layer_stack_debug();
            debug("layer_stack: used. "); debug_dec(i.layer); debug("\n");
            return action;
        }
        debug("layer_stack: through. "); debug_dec(i.layer); debug("\n");
    }
    return action;
}
