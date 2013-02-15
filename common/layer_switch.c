#include <stdint.h>
#include "keyboard.h"
#include "action.h"
#include "debug.h"
#include "layer_switch.h"


uint16_t layer_switch_stat = 0;


uint16_t layer_switch_stat_get(void)
{
    return layer_switch_stat;
}

void layer_switch_stat_set(uint16_t stat)
{
    layer_switch_stat = stat;
    layer_switch_debug();
}

void layer_switch_clear(void)
{
    layer_switch_stat = 0;
    layer_switch_debug();
}

void layer_switch_on(uint8_t layer)
{
    layer_switch_stat |= (1<<layer);
    layer_switch_debug();
}

void layer_switch_off(uint8_t layer)
{
    layer_switch_stat &= ~(1<<layer);
    layer_switch_debug();
}

void layer_switch_inv(uint8_t layer)
{
    layer_switch_stat ^= (1<<layer);
    layer_switch_debug();
}

void layer_switch_debug(void)
{
    debug("layer_switch_stat: "); debug_bin16(layer_switch_stat); debug("\n");
}

action_t layer_switch_get_action(key_t key)
{
    action_t action;
    action.code = ACTION_TRANSPARENT;

    /* higher layer first */
    for (int8_t i = 15; i >= 0; i--) {
        if (layer_switch_stat & (1<<i)) {
            action = action_for_key(i, key);
            if (action.code != ACTION_TRANSPARENT) {
                layer_switch_debug();
                debug("layer_switch: used. "); debug_dec(i); debug("\n");
                return action;
            }
        }
    }
    return action;
}
