#include "host.h"
#include "timer.h"
//#include "keymap.h"
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
static keyrecord_t delayed_fn = {};
static keyrecord_t waiting_key = {};

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



/*
static void layer_switch_on(uint8_t code);
static void layer_switch_off(uint8_t code);
static void key_action(uint8_t code, keyevent_t event);
static void key_pressed(uint8_t code, keyevent_t event);
static void key_released(uint8_t code, keyevent_t event);
static void mod_pressed(uint8_t code, keyevent_t event);
static void mod_released(uint8_t code, keyevent_t event);
*/

static void register_code(uint8_t code);
static void unregister_code(uint8_t code);
static void register_mods(uint8_t mods);
static void unregister_mods(uint8_t mods);
static void clear_keyboard(void);
static void clear_keyboard_but_mods(void);
static void layer_switch(uint8_t new_layer);


/* tap */
#define TAP_TIME    200
static keyevent_t last_event = {};
static uint16_t last_event_time = 0;
static uint8_t tap_count = 0;

/* layer */
uint8_t default_layer = 0;
uint8_t current_layer = 0;
uint8_t waiting_layer = 0;


void action_exec(action_t action, keyevent_t event)
{
    /* count tap when key is up */
    if (KEYEQ(event.key, last_event.key) && timer_elapsed(last_event_time) < TAP_TIME) {
        if (!event.pressed) tap_count++;
    } else {
        tap_count = 0;
    }

    debug("action: "); debug_hex16(action.code); debug("\n");
    debug("kind.id: "); debug_hex(action.kind.id); debug("\n");
    debug("kind.param: "); debug_hex16(action.kind.param); debug("\n");
    debug("key.code: "); debug_hex(action.key.code); debug("\n");
    debug("key.mods: "); debug_hex(action.key.mods); debug("\n");

    switch (action.kind.id) {
        case ACT_LMODS:
            if (event.pressed) {
                register_mods(action.key.mods);
                register_code(action.key.code);
            } else {
                unregister_code(action.key.code);
                unregister_mods(action.key.mods);
            }
            break;
        case ACT_RMODS:
            if (event.pressed) {
                register_mods(action.key.mods<<4);
                register_code(action.key.code);
            } else {
                unregister_code(action.key.code);
                unregister_mods(action.key.mods<<4);
            }
            break;
        case ACT_LAYER:
            switch (action.layer_key.code) {
                case 0x00:  // Momentary switch
                    // TODO: history of layer switch
                    if (event.pressed) {
                        layer_switch(action.layer_key.layer);
                    } else {
                        layer_switch(default_layer);
                    }
                    break;
                case 0x01:  // Oneshot switch
                    // TODO:
                    break;
                case 0x02:  // reserved
                case 0x03:  // reserved
                    break;
                case 0xF0 ... 0xF7: // Tap to enable/disable
                case 0xF8 ... 0xFF: // Tap to toggle layer
                    // TODO:
                    break;
                default:    // with keycode for tap
                    debug("tap: "); debug_hex(tap_count); debug("\n");
                    // TODO: layer switch
                    // TODO: in case tap is interrupted by other key

                    
                    if (event.pressed) {
                        // when any key down
                        if (host_has_anykey()) {
                            if (tap_count == 0)
                            register_code(action.layer_key.code);
                        } else {
                        }

                        if (tap_count == 0) {
                            if (host_has_anykey()) {
                                register_code(action.layer_key.code);
                            } else {
                                waiting_layer = action.layer_key.layer;
                            }
                        }
                        // register key when press after a tap
                        if (tap_count > 0) {
                            register_code(action.layer_key.code);
                        }
                    } else {
                        // type key after tap
                        if (tap_count == 1) {
                            register_code(action.layer_key.code);
                        }
                        unregister_code(action.layer_key.code);
                    }
                    break;
            }
            break;
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
        case ACT_LMOD_TAP:
        case ACT_RMOD_TAP:
        case ACT_MACRO:
        case ACT_COMMAND:
        case ACT_FUNCTION:
        default:
            break;
    }

    /* last event */
    last_event = event;
    last_event_time = timer_read();
}


#if 0
/* Key Action */
inline
static void key_action(uint8_t code, keyevent_t event)
{
    if (event.pressed)
        key_pressed(code, event);
    else
        key_released(code, event);
}

void fn_action(uint8_t code, keyevent_t event)
{
}

/* Key */
inline static void key_pressed(uint8_t code, keyevent_t event)
{
    uint8_t tmp_mods;
    switch (kbdstate) {
        case IDLE:
            register_code(code);
            NEXT(PRESSING);
            break;
        case PRESSING:
            register_code(code);
            break;
        case DELAYING:
            waiting_key = (keyrecord_t) {
                .event = event,
                .code = code,
                .mods = keyboard_report->mods,
                .time = timer_read()
            };
            NEXT(WAITING);
            break;
        case WAITING:
            // play back key stroke
            tmp_mods = keyboard_report->mods;
            host_set_mods(delayed_fn.mods);
            register_code(delayed_fn.code);
            host_set_mods(waiting_key.mods);
            register_code(waiting_key.code);
            host_set_mods(tmp_mods);
            register_code(code);
            NEXT(IDLE);
            break;
    }
}
inline static void key_released(uint8_t code, keyevent_t event)
{
    uint8_t tmp_mods;
    switch (kbdstate) {
        case IDLE:
            unregister_code(code);
            break;
        case PRESSING:
            unregister_code(code);
            if (!anykey_sent_to_host())
                NEXT(IDLE);
            break;
        case DELAYING:
            unregister_code(code);
            break;
        case WAITING:
            if (code == waiting_key.code) {
                layer_switch_on(delayed_fn.code);
                NEXT(IDLE);
                // process waiting_key
                tmp_mods = keyboard_report->mods;
                host_set_mods(waiting_key.mods);
                keymap_process_event(waiting_key.event);
                host_set_mods(tmp_mods);
                keymap_process_event(event);
            } else {
                unregister_code(code);
            }
            break;
    }
}

/* layer switch momentary */
inline static void layerkey_pressed(uint8_t code, keyevent_t event)
{
    uint8_t tmp_mods;
    switch (kbdstate) {
        case IDLE:
            layer_switch_on(code);
            break;
        case PRESSING:
            // ignore
            break;
        case DELAYING:
            waiting_key = (keyrecord_t) {
                .event = event,
                .code = code,
                .mods = keyboard_report->mods,
                .time = timer_read()
            };
            NEXT(WAITING);
            break;
        case WAITING:
            tmp_mods = keyboard_report->mods;
            host_set_mods(delayed_fn.mods);
            register_code(delayed_fn.code);
            host_set_mods(waiting_key.mods);
            register_code(waiting_key.code);
            host_set_mods(tmp_mods);
            if (kind == FN_DOWN) {
                // ignore Fn
            } else if (kind == FNK_DOWN) {
                register_code(code);
            } else if (kind == KEY_DOWN) {
                register_code(code);
            }
            NEXT(IDLE);
            break;
    }
}
inline static void layerkey_released(uint8_t code, keyevent_t event)
{
    switch (kbdstate) {
        case IDLE:
            layer_switch_off(code);
            break;
        case PRESSING:
        case DELAYING:
        case WAITING:
            if (layer_switch_off(code))
                NEXT(IDLE);
            break;
    }
}
#endif


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
    }
}
