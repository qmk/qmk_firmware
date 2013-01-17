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
static void register_code(uint8_t code);
static void unregister_code(uint8_t code);
static void add_mods(uint8_t mods);
static void del_mods(uint8_t mods);
static void set_mods(uint8_t mods);
static void clear_keyboard(void);
static void clear_keyboard_but_mods(void);
static bool sending_anykey(void);
static void layer_switch(uint8_t new_layer);


/* tap */
#define TAP_TIME    200
static keyevent_t last_event = {};
static uint8_t tap_count = 0;

/* layer */
uint8_t default_layer = 0;
uint8_t current_layer = 0;
static keyrecord_t tapping_key = {};
// time 0 means no event.
#define IS_TAPPING      (tapping_key.event.time != 0)
/* TODO: 
#define IS_TAPPING_KEY(key) (tapping_key.event.time != 0 && KEYEQ(tapping_key.event.key, key))
 */

/* waiting keys buffer */
#define WAITING_KEYS_BUFFER 3
static keyrecord_t waiting_keys[WAITING_KEYS_BUFFER] = {};
// TODO: double buffer?
static keyrecord_t waiting_keys0[WAITING_KEYS_BUFFER] = {};
static keyrecord_t waiting_keys1[WAITING_KEYS_BUFFER] = {};
static uint8_t waiting_keys_head = 0;
static bool waiting_keys_enqueue(keyevent_t event)
{
    debug("waiting_keys["); debug_dec(waiting_keys_head); debug("] = ");
    debug_hex16(event.key.raw); debug("\n");
    if (waiting_keys_head < WAITING_KEYS_BUFFER) {
        waiting_keys[waiting_keys_head++] = (keyrecord_t){ .event = event,
                                                           .mods = host_get_mods() };
    } else {
        return true;
    }
}
static void waiting_keys_clear(void)
{
    waiting_keys_head = 0;
}
static bool waiting_keys_has(key_t key)
{
    for (uint8_t i = 0; i < waiting_keys_head; i++) {
        if KEYEQ(key, waiting_keys[i].event.key) return true;
    }
    return false;
}
static void waiting_keys_process_in_current_layer(void)
{
    // TODO: in case of including layer key in waiting keys
    for (uint8_t i = 0; i < waiting_keys_head; i++) {
        debug("waiting_keys_process_in_current_layer["); debug_dec(i); debug("]\n");
        process(waiting_keys[i].event);
    }
    waiting_keys_clear();
}


void action_exec(keyevent_t event)
{
    if (!IS_NOEVENT(event)) {
        debug("event: "); debug_hex16(event.key.raw);
        debug("[");
        if (event.pressed) debug("down"); else debug("up");
        debug("]\n");
    }
    if (IS_TAPPING) {
        /* when tap time elapses or waiting key is released */
        if ((timer_elapsed(tapping_key.event.time) > TAP_TIME) ||
            (!event.pressed && waiting_keys_has(event.key))) {

            // TODO process tapping_key: layer swich, modifier, ...
            // action is needed?
            debug("notap: process tapping_key.\n");
            process(tapping_key.event);

            /* Process waiting keys in new layer */
            waiting_keys_process_in_current_layer();
        }
        /* when tapping key is released within tap time */
        else if (!event.pressed && KEYEQ(event.key, tapping_key.event.key)) {
            /* tap key down */
            debug("tap("); debug_hex8(tap_count); debug(")[tapping_key](register): "); debug_hex8(tapping_key.action.layer.code);  debug("\n");
            register_code(tapping_key.action.layer.code);
            tapping_key = (keyrecord_t){};

            /* process waiting keys */
            waiting_keys_process_in_current_layer();
        }
    }

    // not real event. event just to handle time out of tapping key.
    if (IS_NOEVENT(event)) {
        return;
    }

    /* count up tap when key is up */
    // key: d u d u d
    // tap: 0 1 1 2 2
    // key: u d u d u
    // tap: 0 0 1 1 2
    if (KEYEQ(event.key, last_event.key) && timer_elapsed(last_event.time) <= TAP_TIME) {
        if (!event.pressed) tap_count++;
    } else {
        tap_count = 0;
    }

    /* store key events while tapping */
    if (IS_TAPPING) {
        // TODO: action is needed?
        waiting_keys_enqueue(event);
    } else {
        process(event);
    }

    /* last event */
    last_event = event;
}


static void process(keyevent_t event)
{
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
            if (event.pressed) {
                if (tap_count == 0) {
                    if (host_has_anykey()) {
                        // This key is a modifier essentially.
                        // Prioritize mods when key jam or rollover
                        add_mods(action.key.mods);
                    } else {
                        if (IS_TAPPING && KEYEQ(tapping_key.event.key, event.key)) {
                            // no tapping
                            add_mods(action.key.mods);
                            tapping_key = (keyrecord_t){};
                        } else {
                            debug("tapping lmods("); debug_hex8(action.key.mods); debug(")\n");
                            tapping_key = (keyrecord_t){
                                .event = event,
                                .action = action,
                                .mods = host_get_mods()
                            };
                        }
                    }
                } else {
                    // pressed after tapping
                    debug("tap("); debug_hex(tap_count); debug(")[lmods](register): "); debug_hex8(action.key.code); debug("\n");
                    register_code(action.key.code);
                }
            } else {
                if (tap_count == 0) {
                    debug("tap(00)[lmods](del_mods): "); debug_hex8(action.key.mods); debug("\n");
                    del_mods(action.key.mods);
                } else if (tap_count == 1) {
                    debug("tap(01)[lmods](del_mods/unregister): "); debug_hex8(action.key.mods); debug(" "); debug_hex8(action.key.code); debug("\n");
                    del_mods(action.key.mods);
                    unregister_code(action.key.code);
                } else {
                    debug("tap("); debug_hex(tap_count); debug(")[lmods](unregister): "); debug_hex8(action.key.code); debug("\n");
                    unregister_code(action.key.code);
                }
            }
            break;
        case ACT_RMODS_TAP:
            if (event.pressed) {
                if (tap_count == 0) {
                    if (host_has_anykey()) {
                        // This key is a modifier essentially.
                        // Prioritize mods when key jam or rollover
                        add_mods(action.key.mods<<4);
                    } else {
                        if (IS_TAPPING && KEYEQ(tapping_key.event.key, event.key)) {
                            // no tapping
                            add_mods(action.key.mods<<4);
                            tapping_key = (keyrecord_t){};
                        } else {
                            debug("tapping rmods("); debug_hex8(action.key.mods); debug(")\n");
                            tapping_key = (keyrecord_t){
                                .event = event,
                                .action = action,
                                .mods = host_get_mods()
                            };
                        }
                    }
                } else {
                    // pressed after tapping
                    debug("tap("); debug_hex(tap_count); debug(")[rmods](register): "); debug_hex8(action.key.code); debug("\n");
                    register_code(action.key.code);
                }
            } else {
                if (tap_count == 0) {
                    debug("tap(00)[rmods](del_mods): "); debug_hex8(action.key.mods); debug("\n");
                    del_mods(action.key.mods<<4);
                } else if (tap_count == 1) {
                    debug("tap(01)[rmods](del_mods/unregister): "); debug_hex8(action.key.mods); debug(" "); debug_hex8(action.key.code); debug("\n");
                    del_mods(action.key.mods<<4);
                    unregister_code(action.key.code);
                } else {
                    debug("tap("); debug_hex(tap_count); debug(")[rmods](unregister): "); debug_hex8(action.key.code); debug("\n");
                    unregister_code(action.key.code);
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
                        if (tap_count == 0) {
                            if (host_has_anykey()) {
                                // This key is a normal key than a leyar key essentially.
                                // Prioritize 'tap key' when key jam or rollover
                                register_code(action.layer.code);
                            } else {
                                if (IS_TAPPING && KEYEQ(tapping_key.event.key, event.key)) {
                                    layer_switch(action.layer.opt);
                                    tapping_key = (keyrecord_t){};
                                } else {
                                    debug("tapping layer("); debug_hex8(action.layer.opt); debug(")\n");
                                    tapping_key = (keyrecord_t){
                                        .event = event,
                                        .action = action,
                                        .mods = host_get_mods()
                                    };
                                }
                            }
                        } else if (tap_count > 0) {
                            // pressed after tapping
                            debug("tap[layer](register): "); debug_hex(tap_count); debug("\n");
                            register_code(action.layer.code);
                        }
                    } else {
                        // released after tapping
                        debug("tap[layer](unregister): "); debug_hex(tap_count); debug("\n");
                        unregister_code(action.layer.code);
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
                    // TODO: see ACT_LAYER_PRESSED code
                    // with tap key
                    if (event.pressed) {
                        if (tap_count == 0) {
                            if (host_has_anykey()) {
                                register_code(action.layer.code);
                            } else {
                                tapping_key = (keyrecord_t){
                                    .event = event,
                                    .action = action,
                                    .mods = keyboard_report->mods
                                };
                            }
                        } else if (tap_count > 0) {
                            debug("tap[layer_bit](register): "); debug_hex(tap_count); debug("\n");
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

static void add_mods(uint8_t mods)
{
    if (mods) {
        host_add_mods(mods);
        host_send_keyboard_report();
    }
}

static void del_mods(uint8_t mods)
{
    if (mods) {
        host_del_mods(mods);
        host_send_keyboard_report();
    }
}

static void set_mods(uint8_t mods)
{
    host_set_mods(mods);
    host_send_keyboard_report();
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
