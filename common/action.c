/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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


/* default layer indicates base layer */
uint8_t default_layer = 0;
/* current layer indicates active layer at this time */
uint8_t current_layer = 0;


static void process_action(keyrecord_t *record);
static bool process_tapping(keyrecord_t *record);
static void waiting_buffer_scan_tap(void);

static void debug_event(keyevent_t event);
static void debug_record(keyrecord_t record);
static void debug_action(action_t action);
static void debug_tapping_key(void);
static void debug_waiting_buffer(void);


/*
 * Tapping
 */
/* period of tapping(ms) */
#ifndef TAPPING_TERM
#define TAPPING_TERM    200
#endif

/* tap count needed for toggling a feature */
#ifndef TAPPING_TOGGLE
#define TAPPING_TOGGLE  5
#endif

/* stores a key event of current tap. */
static keyrecord_t tapping_key = {};

#define IS_TAPPING()            !IS_NOEVENT(tapping_key.event)
#define IS_TAPPING_PRESSED()    (IS_TAPPING() && tapping_key.event.pressed)
#define IS_TAPPING_RELEASED()   (IS_TAPPING() && !tapping_key.event.pressed)
#define IS_TAPPING_KEY(k)       (IS_TAPPING() && KEYEQ(tapping_key.event.key, (k)))
#define WITHIN_TAPPING_TERM(e)  (TIMER_DIFF_16(e.time, tapping_key.event.time) < TAPPING_TERM)


/*
 * Waiting buffer
 *
 * stores key events waiting for settling current tap.
 */
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

    waiting_buffer[waiting_buffer_head] = record;
    waiting_buffer_head = (waiting_buffer_head + 1) % WAITING_BUFFER_SIZE;

    debug("waiting_buffer_enq: "); debug_waiting_buffer();
    return true;
}

static void waiting_buffer_clear(void)
{
    waiting_buffer_head = 0;
    waiting_buffer_tail = 0;
}

#if TAPPING_TERM >= 500
static bool waiting_buffer_typed(keyevent_t event)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (KEYEQ(event.key, waiting_buffer[i].event.key) && event.pressed !=  waiting_buffer[i].event.pressed) {
            return true;
        }
    }
    return false;
}
#endif

bool waiting_buffer_has_anykey_pressed(void)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (waiting_buffer[i].event.pressed) return true;
    }
    return false;
}


/* Oneshot modifier
 *
 * Problem: Want to capitalize like 'The' but the result tends to be 'THe'.
 * Solution: Oneshot modifier have its effect on only one key coming next.
 *           Tap Shift, then type 't', 'h' and 'e'. Not need to hold Shift key.
 *
 *  Hold:       works as normal modifier.
 *  Tap:        one shot modifier.
 *  2 Tap:      cancel one shot modifier.
 *  5-Tap:      toggles enable/disable oneshot feature.
 */
static struct {
    uint8_t mods;
    uint8_t time;
    bool    ready;
    bool    disabled;
}   oneshot_state;

static void oneshot_start(uint8_t mods, uint16_t time)
{
    oneshot_state.mods = mods;
    oneshot_state.time = time;
    oneshot_state.ready = true;
}

static void oneshot_cancel(void)
{
    oneshot_state.mods = 0;
    oneshot_state.time = 0;
    oneshot_state.ready = false;
}

static void oneshot_toggle(void)
{
    oneshot_state.disabled = !oneshot_state.disabled;
}



void action_exec(keyevent_t event)
{
    if (!IS_NOEVENT(event)) {
        debug("\n---- action_exec: start -----\n");
        debug("EVENT: "); debug_event(event); debug("\n");
    }

    keyrecord_t record = { .event = event };

    // pre-process on tapping
    if (process_tapping(&record)) {
        if (!IS_NOEVENT(record.event)) {
            debug("processed: "); debug_record(record); debug("\n");
        }
    } else {
        // enqueue
        if (!waiting_buffer_enq(record)) {
            // clear all in case of overflow.
            debug("OVERFLOW: CLEAR ALL STATES\n");
            clear_keyboard();
            waiting_buffer_clear();
            tapping_key = (keyrecord_t){};
        }
    }

    // process waiting_buffer
    if (!IS_NOEVENT(event) && waiting_buffer_head != waiting_buffer_tail) {
        debug("---- action_exec: process waiting_buffer -----\n");
    }

    for (; waiting_buffer_tail != waiting_buffer_head; waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE) {
        if (process_tapping(&waiting_buffer[waiting_buffer_tail])) {
            debug("processed: waiting_buffer["); debug_dec(waiting_buffer_tail); debug("] = ");
            debug_record(waiting_buffer[waiting_buffer_tail]); debug("\n\n");
        } else {
            break;
        }
    }
    if (!IS_NOEVENT(event)) {
        debug("\n");
    }
}

static action_t get_action(key_t key)
{
    action_t action = action_for_key(current_layer, key);

    /* Transparently use default layer */
    if (action.code == ACTION_TRANSPARENT) {
        // TODO: layer stacking
        action = action_for_key(default_layer, key);
        debug("TRNASPARENT: "); debug_hex16(action.code); debug("\n");
    }
    return action;
}

static void process_action(keyrecord_t *record)
{
    keyevent_t event = record->event;
    uint8_t tap_count = record->tap_count;

    if (IS_NOEVENT(event)) { return; }

    action_t action = get_action(event.key);
    debug("ACTION: "); debug_action(action); debug("\n");

    switch (action.kind.id) {
        /* Key and Mods */
        case ACT_LMODS:
        case ACT_RMODS:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS) ?  action.key.mods :
                                                                action.key.mods<<4;
                if (event.pressed) {
                    uint8_t tmp_mods = host_get_mods();
                    if (mods) {
                        host_add_mods(mods);
                        host_send_keyboard_report();
                    }
                    register_code(action.key.code);
                    if (mods && action.key.code) {
                        host_set_mods(tmp_mods);
                        host_send_keyboard_report();
                    }
                } else {
                    if (mods && !action.key.code) {
                        host_del_mods(mods);
                        host_send_keyboard_report();
                    }
                    unregister_code(action.key.code);
                }
            }
            break;
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS_TAP) ?  action.key.mods :
                                                                    action.key.mods<<4;
                switch (action.layer.code) {
                    case 0x00:
                        // Oneshot modifier
                        if (event.pressed) {
                            if (tap_count == 0) {
                                debug("MODS_TAP: Oneshot: add_mods\n");
                                add_mods(mods);
                            }
                            else if (tap_count == 1) {
                                debug("MODS_TAP: Oneshot: start\n");
                                oneshot_start(mods, event.time);
                            }
                            else if (tap_count == TAPPING_TOGGLE) {
                                debug("MODS_TAP: Oneshot: toggle\n");
                                oneshot_toggle();
                            }
                            else {
                                debug("MODS_TAP: Oneshot: cancel&add_mods\n");
                                // double tap cancels oneshot and works as normal modifier.
                                oneshot_cancel();
                                add_mods(mods);
                            }
                        } else {
                            if (tap_count == 0) {
                                debug("MODS_TAP: Oneshot: cancel/del_mods\n");
                                // cancel oneshot by holding.
                                oneshot_cancel();
                                del_mods(mods);
                            }
                            else if (tap_count == 1) {
                                debug("MODS_TAP: Oneshot: del_mods\n");
                                // retain Oneshot
                                del_mods(mods);
                            }
                            else {
                                debug("MODS_TAP: Oneshot: del_mods\n");
                                // cancel Mods
                                del_mods(mods);
                            }
                        }
                        break;
                    default:
                        if (event.pressed) {
                            if (tap_count > 0) {
                                if (waiting_buffer_has_anykey_pressed()) {
                                    debug("MODS_TAP: Tap: Cancel: add_mods\n");
                                    // ad hoc: set 0 to cancel tap
                                    record->tap_count = 0;
                                    add_mods(mods);
                                } else {
                                    debug("MODS_TAP: Tap: register_code\n");
                                    register_code(action.key.code);
                                }
                            } else {
                                debug("MODS_TAP: No tap: add_mods\n");
                                add_mods(mods);
                            }
                        } else {
                            if (tap_count > 0) {
                                debug("MODS_TAP: Tap: unregister_code\n");
                                unregister_code(action.key.code);
                            } else {
                                debug("MODS_TAP: No tap: add_mods\n");
                                del_mods(mods);
                            }
                        }
                        break;
                }
            }
            break;

        /* other HID usage */
        case ACT_USAGE:
#ifdef EXTRAKEY_ENABLE
            switch (action.usage.page) {
                case PAGE_SYSTEM:
                    if (event.pressed) {
                        host_system_send(action.usage.code);
                    } else {
                        host_system_send(0);
                    }
                    break;
                case PAGE_CONSUMER:
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
        case ACT_LAYER:
            switch (action.layer.code) {
                case LAYER_MOMENTARY:  /* momentary */
                    if (event.pressed) {
                        layer_switch(action.layer.val);
                    }
                    else {
                        // NOTE: This is needed by legacy keymap support
                        layer_switch(default_layer);
                    }
                    break;
                case LAYER_ON_PRESS:
                    if (event.pressed) {
                        layer_switch(action.layer.val);
                    }
                    break;
                case LAYER_ON_RELEASE:
                    if (!event.pressed) {
                        layer_switch(action.layer.val);
                    }
                    break;
                case LAYER_DEFAULT:  /* default layer */
                    switch (action.layer.val) {
                        case DEFAULT_ON_BOTH:
                            layer_switch(default_layer);
                            break;
                        case DEFAULT_ON_PRESS:
                            if (event.pressed) {
                                layer_switch(default_layer);
                            }
                            break;
                        case DEFAULT_ON_RELEASE:
                            if (!event.pressed) {
                                layer_switch(default_layer);
                            }
                            break;
                    }
                    break;
                case LAYER_TAP_TOGGLE:  /* switch on hold and toggle on several taps */
                    if (event.pressed) {
                        if (tap_count < TAPPING_TOGGLE) {
                            layer_switch(action.layer.val);
                        }
                    } else {
                        if (tap_count >= TAPPING_TOGGLE) {
                            debug("LAYER_PRESSED: tap toggle.\n");
                            layer_switch(action.layer.val);
                        }
                    }
                    break;
                case LAYER_CHANGE_DEFAULT:  /* change default layer */
                    if (event.pressed) {
                        default_layer = action.layer.val;
                        layer_switch(default_layer);
                    }
                    break;
                default:    /* switch layer on hold and key on tap*/
                    if (event.pressed) {
                       if (tap_count > 0) {
                            debug("LAYER_PRESSED: Tap: register_code\n");
                            register_code(action.layer.code);
                       } else {
                            debug("LAYER_PRESSED: No tap: layer_switch\n");
                            layer_switch(action.layer.val);
                       }
                    } else {
                        if (tap_count > 0) {
                            debug("LAYER_PRESSED: Tap: unregister_code\n");
                            unregister_code(action.layer.code);
                        } else {
                            //debug("LAYER_PRESSED: No tap: NO ACTION\n");
                            // NOTE: This is needed by legacy keymap support
                            debug("LAYER_PRESSED: No tap: return to default layer\n");
                            layer_switch(default_layer);
                        }
                    }
                    break;
            }
            break;
        case ACT_LAYER_BIT:
            switch (action.layer.code) {
                case LAYER_MOMENTARY:  /* momentary */
                    if (event.pressed) {
                        layer_switch(current_layer ^ action.layer.val);
                    } else {
                        layer_switch(current_layer ^ action.layer.val);
                    }
                    break;
                case LAYER_ON_PRESS:
                    if (event.pressed) {
                        layer_switch(current_layer ^ action.layer.val);
                    }
                    break;
                case LAYER_ON_RELEASE:
                    if (!event.pressed) {
                        layer_switch(current_layer ^ action.layer.val);
                    }
                    break;
                case LAYER_TAP_TOGGLE:  /* switch on hold and toggle on several taps */
                    if (event.pressed) {
                        if (tap_count < TAPPING_TOGGLE) {
                            debug("LAYER_BIT: tap toggle(press).\n");
                            layer_switch(current_layer ^ action.layer.val);
                        }
                    } else {
                        if (tap_count <= TAPPING_TOGGLE) {
                            debug("LAYER_BIT: tap toggle(release).\n");
                            layer_switch(current_layer ^ action.layer.val);
                        }
                    }
                    break;
                case 0xFF:
                    // change default layer
                    if (event.pressed) {
                        default_layer = current_layer ^ action.layer.val;
                        layer_switch(default_layer);
                    } else {
                        default_layer = current_layer ^ action.layer.val;
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
                            layer_switch(current_layer ^ action.layer.val);
                        }
                    } else {
                        if (IS_TAPPING_KEY(event.key) && tap_count > 0) {
                            debug("LAYER_BIT: Tap: unregister_code\n");
                            unregister_code(action.layer.code);
                        } else {
                            debug("LAYER_BIT: No tap: layer_switch(bit off)\n");
                            layer_switch(current_layer ^ action.layer.val);
                        }
                    }
                    break;
            }
            break;

        /* Extentions */
        case ACT_MACRO:
            // TODO
            break;
        case ACT_COMMAND:
            break;
        case ACT_FUNCTION:
            action_function(record, action.func.id, action.func.opt);
            break;
        default:
            break;
    }
}

/* Tapping
 *
 * Rule: Tap key is typed(pressed and released) within TAPPING_TERM.
 *       (without interfering by typing other key)
 */
/* return true when key event is processed or consumed. */
static bool process_tapping(keyrecord_t *keyp)
{
    keyevent_t event = keyp->event;

    // if tapping
    if (IS_TAPPING_PRESSED()) {
        if (WITHIN_TAPPING_TERM(event)) {
            if (tapping_key.tap_count == 0) {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    // first tap!
                    debug("Tapping: First tap(0->1).\n");
                    tapping_key.tap_count = 1;
                    debug_tapping_key();
                    process_action(&tapping_key);

                    // enqueue
                    keyp->tap_count = tapping_key.tap_count;
                    return false;
                }
#if TAPPING_TERM >= 500
                /* This can prevent from typing some tap keys in a row at a time. */
                else if (!event.pressed && waiting_buffer_typed(event)) {
                    // other key typed. not tap.
                    debug("Tapping: End. No tap. Interfered by typing key\n");
                    process_action(&tapping_key);
                    tapping_key = (keyrecord_t){};
                    debug_tapping_key();

                    // enqueue
                    return false;
                }
#endif
                else {
                    // other key events shall be enq'd till tapping state settles.
                    return false;
                }
            }
            // tap_count > 0
            else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    debug("Tapping: Tap release("); debug_dec(tapping_key.tap_count); debug(")\n");
                    keyp->tap_count = tapping_key.tap_count;
                    process_action(keyp);
                    tapping_key = *keyp;
                    debug_tapping_key();
                    return true;
                }
                else if (is_tap_key(keyp->event.key) && event.pressed) {
                    if (tapping_key.tap_count > 1) {
                        debug("Tapping: Start new tap with releasing last tap(>1).\n");
                        // unregister key
                        process_action(&(keyrecord_t){
                                .tap_count = tapping_key.tap_count,
                                .event.key = tapping_key.event.key,
                                .event.time = event.time,
                                .event.pressed = false
                        });
                    } else {
                        debug("Tapping: Start while last tap(1).\n");
                    }
                    tapping_key = *keyp;
                    waiting_buffer_scan_tap();
                    debug_tapping_key();
                    return true;
                }
                else {
                    if (!IS_NOEVENT(keyp->event)) {
                        debug("Tapping: key event while last tap(>0).\n");
                    }
                    process_action(keyp);
                    return true;
                }
            }
        }
        // after TAPPING_TERM
        else {
            if (tapping_key.tap_count == 0) {
                debug("Tapping: End. Timeout. Not tap(0): ");
                debug_event(event); debug("\n");
                process_action(&tapping_key);
                tapping_key = (keyrecord_t){};
                debug_tapping_key();
                return false;
            }  else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    debug("Tapping: End. last timeout tap release(>0).");
                    keyp->tap_count = tapping_key.tap_count;
                    process_action(keyp);
                    tapping_key = (keyrecord_t){};
                    return true;
                }
                else if (is_tap_key(keyp->event.key) && event.pressed) {
                    if (tapping_key.tap_count > 1) {
                        debug("Tapping: Start new tap with releasing last timeout tap(>1).\n");
                        // unregister key
                        process_action(&(keyrecord_t){
                                .tap_count = tapping_key.tap_count,
                                .event.key = tapping_key.event.key,
                                .event.time = event.time,
                                .event.pressed = false
                        });
                    } else {
                        debug("Tapping: Start while last timeout tap(1).\n");
                    }
                    tapping_key = *keyp;
                    waiting_buffer_scan_tap();
                    debug_tapping_key();
                    return true;
                }
                else {
                    if (!IS_NOEVENT(keyp->event)) {
                        debug("Tapping: key event while last timeout tap(>0).\n");
                    }
                    process_action(keyp);
                    return true;
                }
            }
        }
    } else if (IS_TAPPING_RELEASED()) {
        if (WITHIN_TAPPING_TERM(event)) {
            if (tapping_key.tap_count > 0 && IS_TAPPING_KEY(event.key) && event.pressed) {
                // sequential tap.
                keyp->tap_count = tapping_key.tap_count + 1;
                debug("Tapping: Tap press("); debug_dec(keyp->tap_count); debug(")\n");
                process_action(keyp);
                tapping_key = *keyp;
                debug_tapping_key();
                return true;
            } else if (event.pressed && is_tap_key(event.key)) {
                // Sequential tap can be interfered with other tap key.
                debug("Tapping: Start with interfering other tap.\n");
                tapping_key = *keyp;
                waiting_buffer_scan_tap();
                debug_tapping_key();
                return true;
            } else {
                if (!IS_NOEVENT(keyp->event)) debug("Tapping: other key just after tap.\n");
                process_action(keyp);
                return true;
            }
        } else {
            // timeout. no sequential tap.
            debug("Tapping: End(Timeout after releasing last tap): ");
            debug_event(event); debug("\n");
            tapping_key = (keyrecord_t){};
            debug_tapping_key();
            return false;
        }
    }
    // not tapping satate
    else {
        if (event.pressed && is_tap_key(event.key)) {
            debug("Tapping: Start(Press tap key).\n");
            tapping_key = *keyp;
            waiting_buffer_scan_tap();
            debug_tapping_key();
            return true;
        } else {
            process_action(keyp);
            return true;
        }
    }
}

/* scan buffer for tapping */
static void waiting_buffer_scan_tap(void)
{
    // tapping already is settled
    if (tapping_key.tap_count > 0) return;
    // invalid state: tapping_key released && tap_count == 0
    if (!tapping_key.event.pressed) return;

    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (IS_TAPPING_KEY(waiting_buffer[i].event.key) &&
                !waiting_buffer[i].event.pressed &&
                WITHIN_TAPPING_TERM(waiting_buffer[i].event)) {
            tapping_key.tap_count = 1;
            waiting_buffer[i].tap_count = 1;
            process_action(&tapping_key);

            debug("waiting_buffer_scan_tap: found at ["); debug_dec(i); debug("]\n");
            debug_waiting_buffer();
            return;
        }
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
        if (command_proc(code)) return;

        if (oneshot_state.mods && oneshot_state.ready && !oneshot_state.disabled) {
            uint8_t tmp_mods = host_get_mods();
            host_add_mods(oneshot_state.mods);
            host_add_key(code);
            host_send_keyboard_report();

            host_set_mods(tmp_mods);
            oneshot_state.ready = false;
        } else {
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
        // NOTE: update mods with full scan of matrix? if modifier changes between layers
    }
}

bool is_tap_key(key_t key)
{
    action_t action = get_action(key);

    switch (action.kind.id) {
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            return true;
        case ACT_LAYER:
        case ACT_LAYER_BIT:
            switch (action.layer.code) {
                case LAYER_MOMENTARY:
                case LAYER_ON_PRESS:
                case LAYER_ON_RELEASE:
                case LAYER_DEFAULT:
                    return false;
                case LAYER_TAP_TOGGLE:
                default:    /* tap key */
                    return true;
            }
            return false;
        case ACT_FUNCTION:
            if (action.func.opt & FUNC_TAP) { return true; }
            return false;
    }
    return false;
}


/*
 * debug print
 */
static void debug_event(keyevent_t event)
{
    debug_hex16((event.key.row<<8) | event.key.col);
    if (event.pressed) debug("d("); else debug("u(");
    debug_dec(event.time); debug(")");
}
static void debug_record(keyrecord_t record)
{
    debug_event(record.event); debug(":"); debug_dec(record.tap_count);
}
static void debug_action(action_t action)
{
    switch (action.kind.id) {
        case ACT_LMODS:             debug("ACT_LMODS");             break;
        case ACT_RMODS:             debug("ACT_RMODS");             break;
        case ACT_LMODS_TAP:         debug("ACT_LMODS_TAP");         break;
        case ACT_RMODS_TAP:         debug("ACT_RMODS_TAP");         break;
        case ACT_USAGE:             debug("ACT_USAGE");             break;
        case ACT_MOUSEKEY:          debug("ACT_MOUSEKEY");          break;
        case ACT_LAYER:             debug("ACT_LAYER");     break;
        case ACT_LAYER_BIT:         debug("ACT_LAYER_BIT");         break;
        case ACT_MACRO:             debug("ACT_MACRO");             break;
        case ACT_COMMAND:           debug("ACT_COMMAND");           break;
        case ACT_FUNCTION:          debug("ACT_FUNCTION");          break;
        default:                    debug("UNKNOWN");               break;
    }
    debug("[");
    debug_hex4(action.kind.param>>8);
    debug(":");
    debug_hex8(action.kind.param & 0xff);
    debug("]");
}
static void debug_tapping_key(void)
{
    debug("TAPPING_KEY="); debug_record(tapping_key); debug("\n");
}
static void debug_waiting_buffer(void)
{
    debug("{ ");
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        debug("["); debug_dec(i); debug("]="); debug_record(waiting_buffer[i]); debug(" ");
    }
    debug("}\n");
}
