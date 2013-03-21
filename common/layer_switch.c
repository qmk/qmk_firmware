#include <stdint.h>
#include "keyboard.h"
#include "action.h"
#include "debug.h"
#include "util.h"
#include "layer_switch.h"


/* 
 * Default Layer (0-15)
 */
uint8_t default_layer = 0;

void default_layer_set(uint8_t layer)
{
    debug("default_layer_set: ");
    debug_dec(default_layer); debug(" to ");

    default_layer = layer;

    debug_dec(default_layer); debug("\n");

    clear_keyboard_but_mods(); // To avoid stuck keys
}


#ifndef NO_ACTION_KEYMAP
/* 
 * Keymap Layer (0-15)
 */
uint16_t keymap_stat = 0;

/* return highest layer whose state is on */
uint8_t keymap_get_layer(void)
{
    return biton16(keymap_stat);
}

static void keymap_stat_set(uint16_t stat)
{
    debug("keymap: ");
    keymap_debug(); debug(" to ");

    keymap_stat = stat;

    keymap_debug(); debug("\n");

    clear_keyboard_but_mods(); // To avoid stuck keys
}

void keymap_clear(void)
{
    keymap_stat_set(0);
}


void keymap_set(uint16_t stat)
{
    keymap_stat_set(stat);
}

void keymap_move(uint8_t layer)
{
    keymap_stat_set(1<<layer);
}

void keymap_on(uint8_t layer)
{
    keymap_stat_set(keymap_stat | (1<<layer));
}

void keymap_off(uint8_t layer)
{
    keymap_stat_set(keymap_stat & ~(1<<layer));
}

void keymap_invert(uint8_t layer)
{
    keymap_stat_set(keymap_stat ^ (1<<layer));
}

void keymap_or(uint16_t stat)
{
    keymap_stat_set(keymap_stat | stat);
}
void keymap_and(uint16_t stat)
{
    keymap_stat_set(keymap_stat & stat);
}
void keymap_xor(uint16_t stat)
{
    keymap_stat_set(keymap_stat ^ stat);
}

void keymap_debug(void)
{
    debug_hex16(keymap_stat); debug("("); debug_dec(keymap_get_layer()); debug(")");
}
#endif



#ifndef NO_ACTION_OVERLAY
/* 
 * Overlay Layer (16-31 = 0-15|0x10)
 */
uint16_t overlay_stat = 0;

/* return highest layer whose state is on */
uint8_t overlay_get_layer(void)
{
    return biton16(overlay_stat);
}

static void overlay_stat_set(uint16_t stat)
{
    debug("overlay: ");
    overlay_debug(); debug(" to ");

    overlay_stat = stat;

    overlay_debug(); debug("\n");

    clear_keyboard_but_mods(); // To avoid stuck keys
}

void overlay_clear(void)
{
    overlay_stat_set(0);
}


void overlay_set(uint16_t stat)
{
    overlay_stat_set(stat);
}

void overlay_move(uint8_t layer)
{
    overlay_stat_set(1<<layer);
}

void overlay_on(uint8_t layer)
{
    overlay_stat_set(overlay_stat | (1<<layer));
}

void overlay_off(uint8_t layer)
{
    overlay_stat_set(overlay_stat & ~(1<<layer));
}

void overlay_invert(uint8_t layer)
{
    overlay_stat_set(overlay_stat ^ (1<<layer));
}

void overlay_or(uint16_t stat)
{
    overlay_stat_set(overlay_stat | stat);
}
void overlay_and(uint16_t stat)
{
    overlay_stat_set(overlay_stat & stat);
}
void overlay_xor(uint16_t stat)
{
    overlay_stat_set(overlay_stat ^ stat);
}

void overlay_debug(void)
{
    debug_hex16(overlay_stat); debug("("); debug_dec(overlay_get_layer()); debug(")");
}
#endif

action_t layer_switch_get_action(key_t key)
{
    action_t action;
    action.code = ACTION_TRANSPARENT;

#ifndef NO_ACTION_OVERLAY
    /* overlay: top layer first */
    for (int8_t i = 15; i >= 0; i--) {
        if (overlay_stat & (1<<i)) {
            action = action_for_key(i | OVERLAY_BIT, key);
            if (action.code != ACTION_TRANSPARENT) {
                return action;
            }
        }
    }
#endif

#ifndef NO_ACTION_KEYMAP
    /* keymap: top layer first */
    for (int8_t i = 15; i >= 0; i--) {
        if (keymap_stat & (1<<i)) {
            action = action_for_key(i, key);
            if (action.code != ACTION_TRANSPARENT) {
                return action;
            }
        }
    }
#endif

    /* default layer */
    action = action_for_key(default_layer, key);
    return action;
}
