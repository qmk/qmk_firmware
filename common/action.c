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


static void process(keyrecord_t *record);

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
#define TAP_TERM    200

/* This counts up when tap occurs */
uint8_t tap_count = 0;
keyevent_t tapping_event = {};
keyrecord_t tapping_key = {};

/* TAPPING: This indicates that whether tap or not is not decided yet. */
// NOTE:  keyevent_t.time 0 means no event.
#define IS_TAPPING()            (tapping_key.event.time != 0)
#define IS_TAPPING_PRESSED()    (IS_TAPPING() && tapping_key.event.pressed)
#define IS_TAPPING_RELEASED()   (IS_TAPPING() && !tapping_key.event.pressed)
#define IS_TAPPING_KEY(k)       (IS_TAPPING() && KEYEQ(tapping_key.event.key, (k)))
#define WITHIN_TAP_TERM(e)      (TIMER_DIFF_16(e.time, tapping_key.event.time) < TAP_TERM)

/* waiting keys buffer */
#define WAITING_BUFFER_SIZE 8
static keyrecord_t waiting_buffer[WAITING_BUFFER_SIZE] = {};
/* point to empty cell to enq */
static uint8_t waiting_buffer_head = 0;
/* point to the oldest data cell to deq */
static uint8_t waiting_buffer_tail = 0;

static bool waiting_buffer_enq(keyrecord_t record)
{
    if (IS_NOEVENT(record.event)) {
        return true;
    }

    if ((waiting_buffer_head + 1) % WAITING_BUFFER_SIZE == waiting_buffer_tail) {
        debug("waiting_buffer_enq: Over flow.\n");
        return false;
    }

    debug("waiting_buffer_enq["); debug_dec(waiting_buffer_head); debug("] = ");
    debug_hex16(record.event.key.raw); debug("\n");

    waiting_buffer[waiting_buffer_head] = record;
    waiting_buffer_head = (waiting_buffer_head + 1) % WAITING_BUFFER_SIZE;
    return true;
}
static keyrecord_t waiting_buffer_deq(void)
{
    if (waiting_buffer_head == waiting_buffer_tail) {
        return (keyrecord_t){};
    }
    uint8_t last_tail = waiting_buffer_tail;
    waiting_buffer_tail = waiting_buffer_tail + 1 % WAITING_BUFFER_SIZE;
    return waiting_buffer[last_tail];
}
static bool waiting_buffer_is_empty(void)
{
    return (waiting_buffer_head == waiting_buffer_tail);
}
static void waiting_buffer_clear(void)
{
    waiting_buffer_head = 0;
    waiting_buffer_tail = 0;
}
static bool waiting_buffer_typed(keyevent_t event)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (KEYEQ(event.key, waiting_buffer[i].event.key) && event.pressed !=  waiting_buffer[i].event.pressed) {
            return true;
        }
    }
    return false;
}
static bool waiting_buffer_has_anykey_pressed(void)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (waiting_buffer[i].event.pressed) return true;
    }
    return false;
}
static void waiting_buffer_process(void)
{
}


/*
 * Rule to judge tap:
 * Tap key is typed(pressed and released) within TAP_TERM
 * without interfaring by typing other key.
 */
/* return true when key event is processed. */
static bool process_tap(keyrecord_t *keyp)
{
    keyevent_t event = keyp->event;

    // if tapping
    if (IS_TAPPING_PRESSED()) {
        if (WITHIN_TAP_TERM(event)) {
            if (tapping_key.tap_count == 0) {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    // first tap!
                    debug("Tapping: First tap.\n");
                    tapping_key.tap_count = 1;
                    process(&tapping_key);

                    // enqueue
                    keyp->tap_count = tapping_key.tap_count;
                    return false;
                } else if (!event.pressed && waiting_buffer_typed(event)) {
                    // other key typed. not tap.
                    debug("Tapping: End(No tap. Interfered by typing key).\n");
                    process(&tapping_key);
                    tapping_key = (keyrecord_t){};

                    // enqueue
                    return false;
                } else {
                    // other key events shall be stored till tapping state settles.
                    return false;
                }
            } else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    keyp->tap_count = tapping_key.tap_count;
                    debug("Tapping: tap release("); debug_dec(keyp->tap_count); debug(")\n");
                    tapping_key = *keyp;
                    return false;
                }
                else if (is_tap_key(keyp->event.key) && event.pressed) {
                    debug("Tapping: Start with forcing to release last tap.\n");
                    process(&(keyrecord_t){
                            .tap_count = tapping_key.tap_count,
                            .event.key = tapping_key.event.key,
                            .event.time = event.time,
                            .event.pressed = false
                    });
                    tapping_key = *keyp;
                    return false;
                }
                else {
                    if (!IS_NOEVENT(keyp->event)) debug("Tapping: key event while tap.\n");
                    process(keyp);
                    return true;
                }
            }
        }
        // not within TAP_TERM
        else {
            if (tapping_key.tap_count == 0) {
                // timeout. not tap.
                debug("Tapping: End. Not tap(time out).\n");
                process(&tapping_key);
                tapping_key = (keyrecord_t){};
                return false;
            }  else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    debug("Tapping: End. tap release.");
                    keyp->tap_count = tapping_key.tap_count;
                    process(keyp);
                    tapping_key = (keyrecord_t){};
                    return true;
                } else {
                    // other key after tap time out.
                    process(keyp);
                    return true;
                }
            }
        }
    } else if (IS_TAPPING_RELEASED()) {
        if (WITHIN_TAP_TERM(event)) {
            if (tapping_key.tap_count > 0 && IS_TAPPING_KEY(event.key) && event.pressed) {
                // sequential tap.
                keyp->tap_count = tapping_key.tap_count + 1;
                debug("Tapping: tap press("); debug_dec(keyp->tap_count); debug(")\n");
                process(keyp);
                tapping_key = *keyp;
                return true;
            } else if (event.pressed && is_tap_key(event.key)) {
                // Sequential tap can be interfered with other tap key.
                debug("Tapping: Start with interfering other tap.\n");
                tapping_key = *keyp;
                return true;
            } else {
                if (!IS_NOEVENT(keyp->event)) debug("Tapping: other key just after tap.\n");
                process(keyp);
                return true;
            }
        } else {
            // timeout. no sequential tap.
            debug("Tapping: End(Time out after releasing last tap).\n");
            tapping_key = (keyrecord_t){};
            process(keyp);
            return true;
        }
    } else {
        if (event.pressed && is_tap_key(event.key)) {
            debug("Tapping: Start(Press tap key).\n");
            tapping_key = *keyp;
            return true;
        } else {
            process(keyp);
            return true;
        }
    }
}

void action_exec(keyevent_t event)
{
    if (!IS_NOEVENT(event)) {
        debug("event: "); 
        debug_hex16(event.time); debug(": ");
        debug_hex16(event.key.raw);
        debug("[");
        if (event.pressed) debug("down"); else debug("up");
        debug("]\n");
    }

    keyrecord_t record = { .event = event };

    // pre-process on tapping
    if (process_tap(&record)) {
        if (!IS_NOEVENT(record.event)) debug("processed.\n");
    } else {
        if (!IS_NOEVENT(record.event)) debug("enqueued.\n");
        if (!waiting_buffer_enq(record)) {
            // clear all in case of overflow.
            clear_keyboard();
            waiting_buffer_clear();
            tapping_key = (keyrecord_t){};
        }
    }

    // TODO: need to process every time?
    // process waiting_buffer
    for (; waiting_buffer_tail != waiting_buffer_head; waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE) {
        if (process_tap(&waiting_buffer[waiting_buffer_tail])) {
            debug("processed: waiting_buffer["); debug_dec(waiting_buffer_tail); debug("] = ");
            debug_hex16(waiting_buffer[waiting_buffer_tail].event.key.raw); debug("\n");
        } else {
            break;
        }
    }
}

static void process(keyrecord_t *record)
{
    // TODO: use record
    keyevent_t event = record->event;
    uint8_t tap_count = record->tap_count;

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
                    if (IS_TAPPING_KEY(event.key) && tap_count > 0) {
                        if (waiting_buffer_has_anykey_pressed()) {
                            debug("MODS_TAP: Tap: Cancel: add_mods\n");
                            // ad hoc: set 0 to cancel tap
                            record->tap_count = 0;
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
                    if (IS_TAPPING_KEY(event.key) && tap_count > 0) {
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
                        if (IS_TAPPING_KEY(event.key)) {
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
                        if (IS_TAPPING_KEY(event.key) && tap_count > 0) {
                            debug("LAYER_PRESSED: Tap: register_code\n");
                            register_code(action.layer.code);
                        } else {
                            debug("LAYER_PRESSED: No tap: layer_switch\n");
                            layer_switch(action.layer.opt);
                        }
*/
                    } else {
                        if (IS_TAPPING_KEY(event.key) && tap_count > 0) {
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
                        if (IS_TAPPING_KEY(event.key) && tap_count > 0) {
                            debug("LAYER_BIT: Tap: register_code\n");
                            register_code(action.layer.code);
                        } else {
                            debug("LAYER_BIT: No tap: layer_switch(bit on)\n");
                            layer_switch(current_layer | action.layer.opt);
                        }
                    } else {
                        if (IS_TAPPING_KEY(event.key) && tap_count > 0) {
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

bool is_tap_key(key_t key)
{
    action_t action = keymap_get_action(current_layer, key.pos.row, key.pos.col);
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
