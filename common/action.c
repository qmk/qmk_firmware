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


static void process(keyevent_t event);

void test_func(keyevent_t event, uint8_t opt)
{
    if (event.pressed) {
        debug("test_func:pressed: "); debug_hex(opt); debug("\n");
    } else {
        debug("test_func:released: "); debug_hex(opt); debug("\n");
    }
}

/* layer */
uint8_t default_layer = 0;
uint8_t current_layer = 0;

/* tap term(ms) */
#define TAP_TIME    200

/* This counts up when tap occurs */
uint8_t tap_count = 0;
keyevent_t tapping_event = {};

/* TAPPING: This indicates that whether tap or not is not decided yet. */
// NOTE:  keyevent_t.time 0 means no event.
#define IS_TAPPING(k)   (tapping_event.time != 0 && KEYEQ(tapping_event.key, (k)))

/* waiting keys buffer */
#define WAITING_KEYS_BUFFER 8
static keyevent_t waiting_events[WAITING_KEYS_BUFFER] = {};
static uint8_t waiting_events_head = 0;
static uint8_t waiting_events_tail = 0;

static bool waiting_events_enqueue(keyevent_t event)
{
    if (IS_NOEVENT(event)) { return true; }

    if ((waiting_events_head + 1) % WAITING_KEYS_BUFFER == waiting_events_tail) {
        debug("waiting_events_enqueue: Over flow.\n");
        return false;
    }

    debug("waiting_events["); debug_dec(waiting_events_head); debug("] = ");
    debug_hex16(event.key.raw); debug("\n");

    waiting_events[waiting_events_head] = event;
    waiting_events_head = (waiting_events_head + 1)% WAITING_KEYS_BUFFER;
    return true;
}
static keyevent_t waiting_events_dequeue(void)
{
    if (waiting_events_head == waiting_events_tail) {
        return (keyevent_t){};
    }
    uint8_t tail = waiting_events_tail;
    waiting_events_tail = waiting_events_tail + 1 % WAITING_KEYS_BUFFER;
    return waiting_events[tail];
}
static void waiting_events_clear(void)
{
    waiting_events_head = 0;
    waiting_events_tail = 0;
}
static bool waiting_events_has(key_t key)
{
    for (uint8_t i = waiting_events_tail; i != waiting_events_head; i = (i + 1) % WAITING_KEYS_BUFFER) {
        if KEYEQ(key, waiting_events[i].key) return true;
    }
    return false;
}
static void waiting_events_process_in_current_layer(void)
{
    // TODO: in case of including tap key in waiting keys
    for (uint8_t i = waiting_events_tail; i != waiting_events_head; i = (i + 1) % WAITING_KEYS_BUFFER) {
        debug("waiting_events_process_in_current_layer["); debug_dec(i); debug("]\n");
        process(waiting_events[i]);
    }
    waiting_events_clear();
}
static bool waiting_events_has_anykey_pressed(void)
{
    for (uint8_t i = waiting_events_tail; i != waiting_events_head; i = (i + 1) % WAITING_KEYS_BUFFER) {
        if (waiting_events[i].pressed) return true;
    }
    return false;
}


void action_exec(keyevent_t event)
{
    if (!IS_NOEVENT(event)) {
        debug("event: "); debug_hex16(event.key.raw);
        debug("[");
        if (event.pressed) debug("down"); else debug("up");
        debug("]\n");
    }

    // In tapping term
    if (tapping_event.time && timer_elapsed(tapping_event.time) < TAP_TIME) {
        if (tapping_event.pressed) {
            if (!event.pressed && KEYEQ(tapping_event.key, event.key)) {
                debug("Tapping: Release tap key.\n");
                if (tap_count == 0) {
                    debug("Tapping: First tap.\n");
                    // count up on release
                    tap_count++;

                    process(tapping_event);
                    waiting_events_process_in_current_layer();
                }
                tapping_event = event;
                process(event);
            } else if (!event.pressed && waiting_events_has(event.key)) {
                debug("Tapping: End(No tap by typing waiting key).\n");

                process(tapping_event);
                waiting_events_process_in_current_layer();
                process(event);

                tap_count = 0;
                tapping_event = (keyevent_t){};
            } else {
                if (!IS_NOEVENT(event)) debug("Tapping: other key while tapping.\n");
                if (tap_count == 0) {
                    // store event
                    waiting_events_enqueue(event);
                    return;
                }
                process(event);
            }
        } else {
            // Waiting for sequential tap
            if (tap_count && event.pressed && KEYEQ(tapping_event.key, event.key)) {
                tap_count++;
                tapping_event = event;
                debug("Tapping: Sequential tap("); debug_hex(tap_count); debug(")\n");
                process(event);
            } else if (event.pressed && is_tap_key(event)) {
                // Sequential tap can be interfered with other tap key.
                debug("Tapping: Start with interfering other tap.\n");
                tapping_event = event;
                tap_count = 0;
                waiting_events_clear();
            } else {
                if (!IS_NOEVENT(event)) debug("Tapping: other key just after tap.\n");
                process(event);
            }
        }
    }
    // Not in tapping term
    else {
        if (tapping_event.time) {
            if (tapping_event.pressed) {
                if (tap_count == 0) {
                    // Not tap, holding down normal key.
                    debug("Tapping: End. Not tap(time out).\n");
                    process(tapping_event);
                    waiting_events_process_in_current_layer();

                    tap_count = 0;
                    tapping_event = (keyevent_t){};
                    process(event);
                } else {
                    // Holding down last tap key. waiting for releasing last tap key.
                    if (!event.pressed && KEYEQ(tapping_event.key, event.key)) {
                        debug("Tapping: End. Release holding last tap(time out).\n");
                        process(event);
                        // clear after release last tap key
                        tap_count = 0;
                        tapping_event = (keyevent_t){};
                        waiting_events_clear();
                    } else if (event.pressed && is_tap_key(event)) {
                        debug("Tapping: Start with forcing to release last tap(time out).\n");
                        process((keyevent_t){
                                .key = tapping_event.key,
                                .time = event.time,
                                .pressed = false });

                        tap_count = 0;
                        tapping_event = event;
                        waiting_events_clear();
                    } else {
                        if (!IS_NOEVENT(event)) debug("Tapping: other key while waiting for release of last tap(time out).\n");
                        process(event);
                    }
                }
            } else {
                // time out for sequential tap after complete last tap
                debug("Tapping: End(Time out after releasing last tap).\n");
                tap_count = 0;
                tapping_event = (keyevent_t){};
                waiting_events_clear();

                process(event);
            }
        } else {
            // Normal state without tapping
            if (event.pressed && is_tap_key(event)) {
                debug("Tapping: Start(Press tap key).\n");
                tapping_event = event;
                tap_count = 0;
                waiting_events_clear();
            } else {
                //debug("Normal event(No tapping)\n");
                process(event);
            }
        }

    }
}

static void process(keyevent_t event)
{
    if (IS_NOEVENT(event)) { return; }

    action_t action = keymap_get_action(current_layer, event.key.pos.row, event.key.pos.col);
    debug("action: "); debug_hex16(action.code);
    if (event.pressed) debug("[down]\n"); else debug("[up]\n");

    switch (action.kind.id) {
        /* Key and Mods */
        case ACT_LMODS:
            //               |pressed                          |released
            // --------------+---------------------------------+------------
            // key           |down(key)                        |up(key)
            // mods          |add(mods)                        |del(mods)
            // key with mods |add(mods), down(key), unset(mods)|up(key)
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
            //               |pressed                          |released
            // --------------+---------------------------------+------------
            // key           |down(key)                        |up(key)
            // mods          |add(mods)                        |del(mods)
            // key with mods |add(mods), down(key), unset(mods)|up(key)
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
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            {
                uint8_t tmp_mods = (action.kind.id == ACT_LMODS_TAP) ?  action.key.mods :
                                                                        action.key.mods<<4;
                if (event.pressed) {
                    if (IS_TAPPING(event.key) && tap_count > 0) {
                        if (waiting_events_has_anykey_pressed()) {
                            debug("MODS_TAP: Tap: Cancel: add_mods\n");
                            tap_count = 0;
                            add_mods(tmp_mods);
                        } else {
                            debug("MODS_TAP: Tap: register_code\n");
                            register_code(action.key.code);
                        }
                    } else {
                        debug("MODS_TAP: No tap: add_mods\n");
                        add_mods(tmp_mods);
                    }
                } else {
                    if (IS_TAPPING(event.key) && tap_count > 0) {
                        debug("MODS_TAP: Tap: unregister_code\n");
                        unregister_code(action.key.code);
                    } else {
                        debug("MODS_TAP: No tap: add_mods\n");
                        del_mods(tmp_mods);
                    }
                }
            }
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
                        if (IS_TAPPING(event.key)) {
                           if (tap_count > 0) {
                                debug("LAYER_PRESSED: Tap: register_code\n");
                                register_code(action.layer.code);
                           } else {
                                debug("LAYER_PRESSED: No tap: layer_switch\n");
                                layer_switch(action.layer.opt);
                           }
                        } else {
                            // TODO: while other key tapping
                                debug("LAYER_PRESSED: No tap: layer_switch\n");
                                layer_switch(action.layer.opt);
                        }
/*
                        if (IS_TAPPING(event.key) && tap_count > 0) {
                            debug("LAYER_PRESSED: Tap: register_code\n");
                            register_code(action.layer.code);
                        } else {
                            debug("LAYER_PRESSED: No tap: layer_switch\n");
                            layer_switch(action.layer.opt);
                        }
*/
                    } else {
                        if (IS_TAPPING(event.key) && tap_count > 0) {
                            debug("LAYER_PRESSED: Tap: unregister_code\n");
                            unregister_code(action.layer.code);
                        } else {
                            debug("LAYER_PRESSED: No tap: NO ACTION\n");
                        }
                    }
                    break;
            }
            break;
        case ACT_LAYER_RELEASED:
            switch (action.layer.code) {
                case 0x00:
                    if (!event.pressed) {
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
                        if (IS_TAPPING(event.key) && tap_count > 0) {
                            debug("LAYER_BIT: Tap: register_code\n");
                            register_code(action.layer.code);
                        } else {
                            debug("LAYER_BIT: No tap: layer_switch(bit on)\n");
                            layer_switch(current_layer | action.layer.opt);
                        }
                    } else {
                        if (IS_TAPPING(event.key) && tap_count > 0) {
                            debug("LAYER_BIT: Tap: unregister_code\n");
                            unregister_code(action.layer.code);
                        } else {
                            debug("LAYER_BIT: No tap: layer_switch(bit off)\n");
                            layer_switch(current_layer & ~action.layer.opt);
                        }
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
            break;
        case ACT_COMMAND:
            break;
        case ACT_FUNCTION:
            action_call_function(event, action.func.id);
            //test_func(event, action.func.opt);
            break;
        default:
            break;
    }
}


/*
 * Utilities for actions.
 */
void register_code(uint8_t code)
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

void unregister_code(uint8_t code)
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

void add_mods(uint8_t mods)
{
    if (mods) {
        host_add_mods(mods);
        host_send_keyboard_report();
    }
}

void del_mods(uint8_t mods)
{
    if (mods) {
        host_del_mods(mods);
        host_send_keyboard_report();
    }
}

void set_mods(uint8_t mods)
{
    host_set_mods(mods);
    host_send_keyboard_report();
}

void clear_keyboard(void)
{
    host_clear_mods();
    clear_keyboard_but_mods();
}

void clear_keyboard_but_mods(void)
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

bool sending_anykey(void)
{
    return (host_has_anykey() || host_mouse_in_use() ||
            host_last_sysytem_report() || host_last_consumer_report());
}

void layer_switch(uint8_t new_layer)
{
    if (current_layer != new_layer) {
        debug("Layer Switch: "); debug_hex(current_layer);
        debug(" -> "); debug_hex(new_layer); debug("\n");

        current_layer = new_layer;
        clear_keyboard_but_mods(); // To avoid stuck keys
        // TODO: update mods with full scan of matrix? if modifier changes between layers
    }
}

bool is_tap_key(keyevent_t event)
{
    action_t action = keymap_get_action(current_layer, event.key.pos.row, event.key.pos.col);
    switch (action.kind.id) {
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            return true;
        case ACT_LAYER_PRESSED:
        case ACT_LAYER_BIT:
            switch (action.layer.code) {
                case 0x00:
                case 0xF1 ... 0xFF:
                    return false;
                case 0xF0:
                default:
                    return true;
            }
            return false;
        case ACT_FUNCTION:
            if (action.func.opt & 0x1) {
                return true;
            }
            return false;
    }
    return false;
}
