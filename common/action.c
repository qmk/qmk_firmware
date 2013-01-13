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

#define Kdebug(s)       do { if (debug_keyboard) debug(s); } while(0)
#define Kdebug_P(s)     do { if (debug_keyboard) debug_P(s); } while(0)
#define Kdebug_hex(s)   do { if (debug_keyboard) debug_hex(s); } while(0)


/*
 *
 * Event/State|IDLE          PRESSING      DELAYING[f]      WAITING[f,k]         
 * -----------+------------------------------------------------------------------
 * Fn  Down   |(L+)          -*1           WAITING(Sk)      IDLE(Rf,Ps)*7        
 *     Up     |(L-)          IDLE(L-)*8    IDLE(L-)*8       IDLE(L-)*8           
 * Fnk Down   |DELAYING(Sf)* (Rf)          WAITING(Sk)      IDLE(Rf,Ps,Rf)       
 *     Up     |(L-)          IDLE(L-/Uf)*8 IDLE(Rf,Uf/L-)*3 IDLE(Rf,Ps,Uf/L-)*3  
 * Key Down   |PRESSING(Rk)  (Rk)          WAITING(Sk)      IDLE(Rf,Ps,Rk)       
 *     Up     |(Uk)          IDLE(Uk)*4    (Uk)             IDLE(L+,Ps,Pk)/(Uk)*a
 *            |
 * Delay      |-             -             IDLE(L+)         IDLE(L+,Ps)          
 * Magic Key  |COMMAND*5
 *
 * *1: ignore Fn if other key is down.
 * *2: register Fnk if any key is pressing
 * *3: register/unregister delayed Fnk and move to IDLE if code == delayed Fnk, else *8
 * *4: if no keys registered to host
 * *5: unregister all keys
 * *6: only if no keys down
 * *7: ignore Fn because Fnk key and stored key are down.
 * *8: move to IDLE if layer switch(off) occurs, else stay at current state
 * *9: repeat key if pressing Fnk twice quickly(move to PRESSING)
 * *a: layer switch and process waiting key and code if code == wainting key, else unregister key
 *
 * States:
 *      IDLE: No key is down except modifiers
 *      DELAYING: delay layer switch after pressing Fn with alt keycode
 *      WAITING: key is pressed during DELAYING
 *
 * Events:
 *      Fn: Fn key without alternative keycode
 *      Fnk: Fn key with alternative keycode
 *      -: ignore
 *      Delay: layer switch delay term is elapsed
 *
 * Actions:
 *      Rk: register key
 *      Uk: unregister key
 *      Rf: register Fn(alt keycode)
 *      Uf: unregister Fn(alt keycode)
 *      Rs: register stored key
 *      Us: unregister stored key
 *      Sk: Store key(waiting Key)
 *      Sf: Store Fn(delayed Fn)
 *      Ps: Process stored key
 *      Ps: Process key
 *      Is: Interpret stored keys in current layer
 *      L+: Switch to new layer(*unregister* all keys but modifiers)
 *      L-: Switch back to last layer(*unregister* all keys but modifiers)
 *      Ld: Switch back to default layer(*unregister* all keys but modifiers)
 */


typedef enum { IDLE, DELAYING, WAITING, PRESSING } kbdstate_t;
#define NEXT(state)     do { \
    Kdebug("NEXT: "); Kdebug_P(state_str(kbdstate)); \
    kbdstate = state; \
    Kdebug(" -> "); Kdebug_P(state_str(kbdstate)); Kdebug("\n"); \
} while (0)


static kbdstate_t kbdstate = IDLE;
static uint8_t fn_state_bits = 0;

static const char *state_str(kbdstate_t state)
{
    if (state == IDLE)      return PSTR("IDLE");
    if (state == DELAYING)  return PSTR("DELAYING");
    if (state == WAITING)   return PSTR("WAITING");
    if (state == PRESSING)  return PSTR("PRESSING");
    return PSTR("UNKNOWN");
}
static bool anykey_sent_to_host(void)
{
    return (host_has_anykey() || host_mouse_in_use() ||
            host_last_sysytem_report() || host_last_consumer_report());
}


static void register_code(uint8_t code);
static void unregister_code(uint8_t code);
static void register_mods(uint8_t mods);
static void unregister_mods(uint8_t mods);
static void clear_keyboard(void);
static void clear_keyboard_but_mods(void);
static void layer_switch(uint8_t new_layer);


/* tap */
#define TAP_TIME    200
#define LAYER_DELAY 200
static keyevent_t last_event = {};
static uint16_t last_event_time = 0;
static uint8_t tap_count = 0;

/* layer */
uint8_t default_layer = 0;
uint8_t current_layer = 0;
keyrecord_t delaying_layer = {};

keyrecord_t waiting_key = {};

// TODO: ring buffer: waiting_keys[]
/*
#define WAITING_KEYS_BUFFER 3
static keyrecord_t waiting_keys[WAITING_KEYS_BUFFER] = {};
static uint8_t waiting_keys_head = 0;
static uint8_t waiting_keys_tail = 0;
static void waiting_key_queue(keyevent_t event)
{
}
static void waiting_key_dequeue(keyevent_t event)
{
}
*/

static void process(keyevent_t event, action_t action)
{
    //action_t action = keymap_get_action(current_layer, event.key.row, event.key.col);

    debug("action: "); debug_hex16(action.code); debug("\n");
    debug("kind.id: "); debug_hex(action.kind.id); debug("\n");
    debug("kind.param: "); debug_hex16(action.kind.param); debug("\n");
    debug("key.code: "); debug_hex(action.key.code); debug("\n");
    debug("key.mods: "); debug_hex(action.key.mods); debug("\n");

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
                    debug("tap: "); debug_hex(tap_count); debug("\n");
                    if (event.pressed) {
                        if (tap_count == 0) {
                            if (host_has_anykey()) {
                                register_code(action.layer.code);
                            } else {
                                delaying_layer = (keyrecord_t){
                                    .event = event,
                                    .action = action,
                                    .mods = host_get_mods()
                                };
                            }
                        } else if (tap_count > 0) {
                            register_code(action.layer.code);
                        }
                    } else {
                        // tap key
                        if (KEYEQ(event.key, delaying_layer.event.key) &&
                                timer_elapsed(delaying_layer.event.time) < TAP_TIME) {
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
                    debug("tap: "); debug_hex(tap_count); debug("\n");
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
    /* count tap when key is up */
    if (KEYEQ(event.key, last_event.key) && timer_elapsed(last_event_time) < TAP_TIME) {
        if (!event.pressed) tap_count++;
    } else {
        tap_count = 0;
    }

    /* When delaying layer switch */
    if (delaying_layer.action.code) {
        /* Layer switch when delay time elapses or waiting key is released */
        if ((timer_elapsed(delaying_layer.event.time) > LAYER_DELAY) ||
            (!event.pressed && KEYEQ(event.key, waiting_key.event.key))) {
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
            if (waiting_key.event.time) {
                uint8_t tmp_mods = host_get_mods();
                host_set_mods(waiting_key.mods);
                process(waiting_key.event, keymap_get_action(current_layer,
                                                             waiting_key.event.key.row,
                                                             waiting_key.event.key.col));
                host_set_mods(tmp_mods);
                waiting_key = (keyrecord_t){};
            }
        }
        /* when delaying layer key is released within delay term */
        else if (!event.pressed && KEYEQ(event.key, delaying_layer.event.key)) {
            /* tap key down */
            uint8_t tmp_mods = host_get_mods();
            host_set_mods(delaying_layer.mods);
            register_code(delaying_layer.action.layer.code);
            delaying_layer = (keyrecord_t){};

            /* process waiting keys */
            if (waiting_key.event.time) {
                host_set_mods(waiting_key.mods);
                process(waiting_key.event, waiting_key.action);
                waiting_key = (keyrecord_t){};
            }
            host_set_mods(tmp_mods);
        }
    }

    action_t action = keymap_get_action(current_layer, event.key.row, event.key.col);

    /* postpone key-down events while delaying layer */
    if (delaying_layer.action.code) {
        if (event.pressed) {
            // TODO: waiting_keys[]
            waiting_key = (keyrecord_t){
                .event = event,
                .action = action,
                .mods = host_get_mods()
            };
        } else {
            process(event, action);
        }
    } else {
        process(event, action);
    }

    /* last event */
    last_event = event;
    last_event_time = timer_read();
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

static void register_mods(uint8_t mods)
{
    if (!mods) return;
    host_add_mods(mods);
    host_send_keyboard_report();
}

static void unregister_mods(uint8_t mods)
{
    if (!mods) return;
    host_del_mods(mods);
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

static void layer_switch(uint8_t new_layer)
{
    if (current_layer != new_layer) {
        Kdebug("Layer Switch: "); Kdebug_hex(current_layer);
        Kdebug(" -> "); Kdebug_hex(new_layer); Kdebug("\n");

        current_layer = new_layer;
        clear_keyboard_but_mods(); // To avoid stuck keys
        // TODO: update mods with full scan of matrix? if modifier changes between layers
    }
}
