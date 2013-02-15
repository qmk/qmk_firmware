#include <stdint.h>
#include "keyboard.h"
#include "action.h"
#include "debug.h"
#include "util.h"
#include "layer_switch.h"


uint8_t default_layer = 0;

uint16_t layer_switch_stat = 0;


uint16_t layer_switch_get_stat(void)
{
    return layer_switch_stat;
}

/* return highest layer whose state is on */
uint8_t layer_switch_get_layer(void)
{
    return biton16(layer_switch_stat);
}

static inline void stat_set(uint16_t stat)
{
    debug("layer_switch: ");
    layer_switch_debug(); debug(" to ");

    layer_switch_stat = stat;

    layer_switch_debug(); debug("\n");

    clear_keyboard_but_mods(); // To avoid stuck keys
}

void layer_switch_clear(void)
{
    stat_set(0);
}


void layer_switch_set(uint16_t stat)
{
    stat_set(stat);
}

void layer_switch_move(uint8_t layer)
{
    if (layer)
        stat_set(1<<layer);
    else
        stat_set(0);    // fall back to default layer
}

void layer_switch_on(uint8_t layer)
{
    stat_set(layer_switch_stat | (1<<layer));
}

void layer_switch_off(uint8_t layer)
{
    stat_set(layer_switch_stat & ~(1<<layer));
}

void layer_switch_invert(uint8_t layer)
{
    stat_set(layer_switch_stat ^ (1<<layer));
}

void layer_switch_or(uint16_t stat)
{
    stat_set(layer_switch_stat | stat);
}
void layer_switch_and(uint16_t stat)
{
    stat_set(layer_switch_stat & stat);
}
void layer_switch_xor(uint16_t stat)
{
    stat_set(layer_switch_stat ^ stat);
}

void layer_switch_debug(void)
{
    debug_hex16(layer_switch_stat); debug("("); debug_dec(layer_switch_get_layer()); debug(")");
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
                return action;
            }
        }
    }
    return action;
}
