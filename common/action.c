#include "host.h"
#include "timer.h"
#include "keymap.h"
#include "keycode.h"
#include "keyboard.h"
#include "mousekey.h"
#include "command.h"
#include "util.h"
#include "debug.h"
#include "action.h"




static void process(keyevent_t event, action_t action);
static void register_code(uint8_t code);
static void unregister_code(uint8_t code);
static void clear_keyboard(void);
static void clear_keyboard_but_mods(void);
static bool sending_anykey(void);
static void layer_switch(uint8_t new_layer);


/* tap */
#define TAP_TIME    200
static keyevent_t last_event = {};
static uint16_t last_event_time = 0;
static uint8_t tap_count = 0;

/* layer */
uint8_t default_layer = 0;
uint8_t current_layer = 0;
keyrecord_t delaying_layer = {};

#define WAITING_KEYS_BUFFER 3
static keyrecord_t waiting_keys[WAITING_KEYS_BUFFER] = {};
static uint8_t waiting_keys_head = 0;
static bool waiting_keys_enqueue(keyevent_t event, action_t action)
{
    debug("waiting_keys["); debug_dec(waiting_keys_head); debug("] = ");
    debug_hex16(action.code); debug("\n");
    if (waiting_keys_head < WAITING_KEYS_BUFFER) {
        waiting_keys[waiting_keys_head++] = (keyrecord_t){ .event = event,
                                                           .action = action,
                                                           .mods = host_get_mods() };
    } else {
        return true;
    }
}
static void waiting_keys_clear(void)
{
    waiting_keys_head = 0;
}
static bool waiting_keys_has(keypos_t key)
{
    for (uint8_t i = 0; i < waiting_keys_head; i++) {
        if KEYEQ(key, waiting_keys[i].event.key) return true;
    }
    return false;
}
static void waiting_keys_process_in_current_layer(void)
{
    // TODO: in case of including layer key in waiting keys
    uint8_t tmp_mods = host_get_mods();
    for (uint8_t i = 0; i < waiting_keys_head; i++) {
        /* revive status of mods */
        host_set_mods(waiting_keys[i].mods);
        process(waiting_keys[i].event, keymap_get_action(current_layer,
                                                         waiting_keys[i].event.key.row,
                                                         waiting_keys[i].event.key.col));
        debug("waiting_keys_process_in_current_layer["); debug_dec(i); debug("]\n");
    }
    host_set_mods(tmp_mods);
    waiting_keys_clear();
}


static void process(keyevent_t event, action_t action)
{
    //action_t action = keymap_get_action(current_layer, event.key.row, event.key.col);
    debug("action: "); debug_hex16(action.code); debug("\n");


    switch (action.kind.id) {
        /* Key and Mods */
        case ACT_LMODS:
            // normal key or key plus mods
            if (event.pressed) {
                uint8_t tmp_mods = host_get_mods();
                if (action.key.mods) {
                    host_add_mods(action.key.mods);
                    host_send_keyboard_report();
                }
                register_code(action.key.code);
                if (action.key.mods && action.key.code) {
                    host_set_mods(tmp_mods);
                    host_send_keyboard_report();
                }
            } else {
                if (action.key.mods && !action.key.code) {
                    host_del_mods(action.key.mods);
                    host_send_keyboard_report();
                }
                unregister_code(action.key.code);
            }
            break;
        case ACT_RMODS:
            if (event.pressed) {
                uint8_t tmp_mods = host_get_mods();
                if (action.key.mods) {
                    host_add_mods(action.key.mods<<4);
                    host_send_keyboard_report();
                }
                register_code(action.key.code);
                if (action.key.mods && action.key.code) {
                    host_set_mods(tmp_mods);
                    host_send_keyboard_report();
                }
            } else {
                if (action.key.mods && !action.key.code) {
                    host_del_mods(action.key.mods<<4);
                    host_send_keyboard_report();
                }
                unregister_code(action.key.code);
            }
            break;
        case ACT_LMOD_TAP:
            break;
        case ACT_RMOD_TAP:
            break;

        /* other HID usage */
        case ACT_USAGE:
#ifdef EXTRAKEY_ENABLE
            switch (action.usage.page) {
                case ACTION_USAGE_PAGE_SYSTEM:
                    if (event.pressed) {
                        host_system_send(action.usage.code);
                    } else {
                        host_system_send(0);
                    }
                    break;
                case ACTION_USAGE_PAGE_CONSUMER:
                    if (event.pressed) {
                        host_consumer_send(action.usage.code);
                    } else {
                        host_consumer_send(0);
                    }
                    break;
            }
#endif
            break;

        /* Mouse key */
        case ACT_MOUSEKEY:
#ifdef MOUSEKEY_ENABLE
            if (event.pressed) {
                mousekey_on(action.key.code);
                mousekey_send();
            } else {
                mousekey_off(action.key.code);
                mousekey_send();
            }
#endif
            break;

        /* Layer key */
        case ACT_LAYER_PRESSED:
            // layer action when pressed
            switch (action.layer.code) {
                case 0x00:
                    if (event.pressed) {
                        layer_switch(action.layer.opt);
                    }
                    break;
                case 0xF0:
                    // TODO: tap toggle
                    break;
                case 0xFF:
                    if (event.pressed) {
                        default_layer = action.layer.opt;
                        layer_switch(default_layer);
                    }
                    break;
                default:
                    // with tap key
                    if (event.pressed) {
                        if (tap_count == 0) {
                            if (host_has_anykey()) {
                                register_code(action.layer.code);
                            } else {
                                debug("Delay switching layer("); debug_hex8(action.layer.opt); debug(")\n");
                                delaying_layer = (keyrecord_t){
                                    .event = event,
                                    .action = action,
                                    .mods = host_get_mods()
                                };
                            }
                        } else if (tap_count > 0) {
                            debug("tap: "); debug_hex(tap_count); debug("\n");
                            register_code(action.layer.code);
                        }
                    } else {
                        // tap key
                        if (KEYEQ(event.key, delaying_layer.event.key) &&
                                timer_elapsed(delaying_layer.event.time) <= TAP_TIME) {
                            uint8_t tmp_mods = host_get_mods();
                            host_set_mods(delaying_layer.mods);
                            register_code(delaying_layer.action.layer.code);
                            host_set_mods(tmp_mods);
                            unregister_code(delaying_layer.action.layer.code);
                        } else {
                            unregister_code(action.layer.code);
                        }
                        delaying_layer = (keyrecord_t){};
                    }
                    break;
            }
            break;
        case ACT_LAYER_RELEASED:
            switch (action.layer.code) {
                case 0x00:
                    if (event.pressed) {
                        layer_switch(action.layer.opt);
                    }
                    break;
                case 0xF0:
                    // Ignored. LAYER_RELEASED with tap toggle is invalid action.
                    break;
                case 0xFF:
                    if (!event.pressed) {
                        default_layer = action.layer.opt;
                        layer_switch(default_layer);
                    }
                    break;
                default:
                    // Ignored. LAYER_RELEASED with tap key is invalid action.
                    break;
            }
            break;
        case ACT_LAYER_BIT:
            switch (action.layer.code) {
                case 0x00:
                    if (event.pressed) {
                        layer_switch(current_layer | action.layer.opt);
                    } else {
                        layer_switch(current_layer & ~action.layer.opt);
                    }
                    break;
                case 0xF0:
                    // TODO: tap toggle
                    break;
                case 0xFF:
                    // change default layer
                    if (event.pressed) {
                        default_layer = current_layer | action.layer.opt;
                        layer_switch(default_layer);
                    } else {
                        default_layer = current_layer & ~action.layer.opt;
                        layer_switch(default_layer);
                    }
                    break;
                default:
                    // with tap key
                    if (event.pressed) {
                        if (tap_count == 0) {
                            if (host_has_anykey()) {
                                register_code(action.layer.code);
                            } else {
                                delaying_layer = (keyrecord_t){
                                    .event = event,
                                    .action = action,
                                    .mods = keyboard_report->mods
                                };
                            }
                        } else if (tap_count > 0) {
                            debug("tap: "); debug_hex(tap_count); debug("\n");
                            register_code(action.layer.code);
                        }
                    } else {
                        if (tap_count == 0) {
                            // no tap
                            layer_switch(current_layer & ~action.layer.opt);
                        } else if (tap_count == 1) {
                            // tap
                            register_code(action.layer.code);
                        }
                        unregister_code(action.layer.code);
                    }
                    break;
            }
        case ACT_LAYER_EXT:
            switch (action.layer.opt) {
                case 0x00:
                    // set default layer when pressed
                    switch (action.layer.code) {
                        case 0x00:
                            if (event.pressed) {
                                layer_switch(default_layer);
                            }
                            break;
                        case 0xF0:
                            // TODO: tap toggle
                            break;
                        case 0xFF:
                            if (event.pressed) {
                                default_layer = current_layer;
                                layer_switch(default_layer);
                            }
                            break;
                        default:
                            // TODO: tap key
                            break;
                    }
                    break;
                case 0x01:
                    // set default layer when released
                    switch (action.layer.code) {
                        case 0x00:
                            if (!event.pressed) {
                                layer_switch(default_layer);
                            }
                            break;
                        case 0xFF:
                            if (!event.pressed) {
                                default_layer = current_layer;
                                layer_switch(default_layer);
                            }
                            break;
                        case 0xF0:
                        default:
                            // Ignore tap.
                            if (!event.pressed) {
                                layer_switch(default_layer);
                            }
                            break;
                    }
                    break;
            }
            break;

        /* Extentions */
        case ACT_MACRO:
        case ACT_COMMAND:
        case ACT_FUNCTION:
        default:
            break;
    }
}

void action_exec(keyevent_t event)
{
/*
    debug("key["); debug_hex8(event.key.row); debug(":"); debug_hex8(event.key.col);
    if (event.pressed) debug("]down\n"); else debug("]up\n");
*/

    /* When delaying layer switch */
    if (delaying_layer.action.code) {
        /* Layer switch when tap time elapses or waiting key is released */
        if ((timer_elapsed(delaying_layer.event.time) > TAP_TIME) ||
            (!event.pressed && waiting_keys_has(event.key))) {
            /* layer switch */
            switch (delaying_layer.action.kind.id) {
                case ACT_LAYER_PRESSED:
                    layer_switch(delaying_layer.action.layer.opt);
                    break;
                case ACT_LAYER_BIT:
                    layer_switch(current_layer | delaying_layer.action.layer.opt);
                    break;
            }
            delaying_layer = (keyrecord_t){};

            /* Process waiting keys in new layer */
            waiting_keys_process_in_current_layer();
        }
        /* when delaying layer key is released within delay term */
        else if (!event.pressed && KEYEQ(event.key, delaying_layer.event.key)) {
            /* tap key down */
            uint8_t tmp_mods = host_get_mods();
            host_set_mods(delaying_layer.mods);
            register_code(delaying_layer.action.layer.code);
            delaying_layer = (keyrecord_t){};
            host_set_mods(tmp_mods);

            /* process waiting keys */
            waiting_keys_process_in_current_layer();
        }
    }

    // not real event. event just to update delaying layer.
    if (IS_NOEVENT(event)) {
        return;
    }

    /* count tap when key is up */
    if (KEYEQ(event.key, last_event.key) && timer_elapsed(last_event.time) <= TAP_TIME) {
        if (!event.pressed) tap_count++;
    } else {
        tap_count = 0;
    }

    action_t action = keymap_get_action(current_layer, event.key.row, event.key.col);

    // TODO: all key events(pressed, released) should be recorded?
    /* postpone key-down events while delaying layer */
    if (delaying_layer.action.code) {
        if (event.pressed) {
            waiting_keys_enqueue(event, action);
        } else {
            process(event, action);
        }
    } else {
        process(event, action);
    }

    /* last event */
    last_event = event;
}


static void register_code(uint8_t code)
{
    if (code == KC_NO) {
        return;
    }
    else if IS_KEY(code) {
        // TODO: should push command_proc out of this block?
        if (!command_proc(code)) {
            host_add_key(code);
            host_send_keyboard_report();
        }
    }
    else if IS_MOD(code) {
        host_add_mods(MOD_BIT(code));
        host_send_keyboard_report();
    }
}

static void unregister_code(uint8_t code)
{
    if IS_KEY(code) {
        host_del_key(code);
        host_send_keyboard_report();
    }
    else if IS_MOD(code) {
        host_del_mods(MOD_BIT(code));
        host_send_keyboard_report();
    }
}

static void clear_keyboard(void)
{
    host_clear_mods();
    clear_keyboard_but_mods();
}

static void clear_keyboard_but_mods(void)
{
    host_clear_keys();
    host_send_keyboard_report();
#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
    mousekey_send();
#endif
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif
}

static bool sending_anykey(void)
{
    return (host_has_anykey() || host_mouse_in_use() ||
            host_last_sysytem_report() || host_last_consumer_report());
}

static void layer_switch(uint8_t new_layer)
{
    if (current_layer != new_layer) {
        debug("Layer Switch: "); debug_hex(current_layer);
        debug(" -> "); debug_hex(new_layer); debug("\n");

        current_layer = new_layer;
        clear_keyboard_but_mods(); // To avoid stuck keys
        // TODO: update mods with full scan of matrix? if modifier changes between layers
    }
}
