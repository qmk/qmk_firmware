/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
#include "keyboard.h"
#include "matrix.h"
#include "keymap.h"
#include "host.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif


#define Kdebug(s)       do { if (debug_keyboard) debug(s); } while(0)
#define Kdebug_P(s)     do { if (debug_keyboard) debug_P(s); } while(0)
#define Kdebug_hex(s)   do { if (debug_keyboard) debug_hex(s); } while(0)

#define LAYER_DELAY     250

typedef enum keykind {
    NONE,
    FN_DOWN, FN_UP,
    FNK_DOWN, FNK_UP,
    KEY_DOWN, KEY_UP,
    MOD_DOWN, MOD_UP,
} keykind_t;

typedef enum { IDLE, DELAYING, WAITING, PRESSING } kbdstate_t;


#ifdef KEYMAP_DEFAULT_LAYER
uint8_t default_layer = KEYMAP_DEFAULT_LAYER;
uint8_t current_layer = KEYMAP_DEFAULT_LAYER;
#else
uint8_t default_layer = 0;
uint8_t current_layer = 0;
#endif

/* keyboard internal states */
static kbdstate_t kbdstate = IDLE;
static uint8_t fn_state_bits = 0;
static keyrecord_t delayed_fn;
static keyrecord_t waiting_key;


static const char *state_str(kbdstate_t state)
{
    if (state == IDLE)      return PSTR("IDLE");
    if (state == DELAYING)  return PSTR("DELAYING");
    if (state == WAITING)   return PSTR("WAITING");
    if (state == PRESSING)  return PSTR("PRESSING");
    return PSTR("UNKNOWN");
}

static inline keykind_t get_keykind(uint8_t code, bool pressed)
{
    if IS_KEY(code)         return (pressed ? KEY_DOWN : KEY_UP);
    if IS_MOD(code)         return (pressed ? MOD_DOWN : MOD_UP);
    if IS_FN(code) {
        if (keymap_fn_keycode(FN_INDEX(code)))
            return (pressed ? FNK_DOWN : FNK_UP);
        else
            return (pressed ? FN_DOWN : FN_UP);
    }
    if IS_MOUSEKEY(code)    return (pressed ? KEY_DOWN : KEY_UP);
    if IS_SYSTEM(code)      return (pressed ? KEY_DOWN : KEY_UP);
    if IS_CONSUMER(code)    return (pressed ? KEY_DOWN : KEY_UP);
    return  NONE;
}

static void clear_keyboard(void)
{
    host_clear_keys();
    host_clear_mods();
    host_send_keyboard_report();

    host_system_send(0);
    host_consumer_send(0);

#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
    mousekey_send();
#endif
}

static void clear_keyboard_but_mods(void)
{
    host_clear_keys();
    host_send_keyboard_report();

    host_system_send(0);
    host_consumer_send(0);

#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
    mousekey_send();
#endif
}

static bool anykey_sent_to_host(void)
{
    return (host_has_anykey() || host_mouse_in_use() ||
            host_last_sysytem_report() || host_last_consumer_report());
}

static void layer_switch_on(uint8_t code)
{
    if (!IS_FN(code)) return;
    fn_state_bits |= FN_BIT(code);
    uint8_t new_layer = (fn_state_bits ? keymap_fn_layer(biton(fn_state_bits)) : default_layer);
    if (current_layer != new_layer) {
        Kdebug("Layer Switch(on): "); Kdebug_hex(current_layer);
        Kdebug(" -> "); Kdebug_hex(new_layer); Kdebug("\n");

        clear_keyboard_but_mods();
        current_layer = new_layer;
    }
}

static bool layer_switch_off(uint8_t code)
{
    if (!IS_FN(code)) return false;
    fn_state_bits &= ~FN_BIT(code);
    uint8_t new_layer = (fn_state_bits ? keymap_fn_layer(biton(fn_state_bits)) : default_layer);
    if (current_layer != new_layer) {
        Kdebug("Layer Switch(off): "); Kdebug_hex(current_layer);
        Kdebug(" -> "); Kdebug_hex(new_layer); Kdebug("\n");

        clear_keyboard_but_mods();
        current_layer = new_layer;
        return true;
    }
    return false;
}

static void register_code(uint8_t code)
{
    if IS_KEY(code) {
        if (!command_proc(code)) {
            host_add_key(code);
            host_send_keyboard_report();
        }
    }
    else if IS_MOD(code) {
        host_add_mod_bit(MOD_BIT(code));
        host_send_keyboard_report();
    }
    else if IS_FN(code) {
        if (!command_proc(keymap_fn_keycode(FN_INDEX(code)))) {
            host_add_key(keymap_fn_keycode(FN_INDEX(code)));
            host_send_keyboard_report();
        }
    }
    else if IS_MOUSEKEY(code) {
#ifdef MOUSEKEY_ENABLE
        mousekey_on(code);
        mousekey_send();
#endif
    }
    else if IS_CONSUMER(code) {
        uint16_t usage = 0;
        switch (code) {
            case KC_AUDIO_MUTE:
                usage = AUDIO_MUTE;
                break;
            case KC_AUDIO_VOL_UP:
                usage = AUDIO_VOL_UP;
                break;
            case KC_AUDIO_VOL_DOWN:
                usage = AUDIO_VOL_DOWN;
                break;
            case KC_MEDIA_NEXT_TRACK:
                usage = TRANSPORT_NEXT_TRACK;
                break;
            case KC_MEDIA_PREV_TRACK:
                usage = TRANSPORT_PREV_TRACK;
                break;
            case KC_MEDIA_STOP:
                usage = TRANSPORT_STOP;
                break;
            case KC_MEDIA_PLAY_PAUSE:
                usage = TRANSPORT_PLAY_PAUSE;
                break;
            case KC_MEDIA_SELECT:
                usage = AL_CC_CONFIG;
                break;
            case KC_MAIL:
                usage = AL_EMAIL;
                break;
            case KC_CALCULATOR:
                usage = AL_CALCULATOR;
                break;
            case KC_MY_COMPUTER:
                usage = AL_LOCAL_BROWSER;
                break;
            case KC_WWW_SEARCH:
                usage = AC_SEARCH;
                break;
            case KC_WWW_HOME:
                usage = AC_HOME;
                break;
            case KC_WWW_BACK:
                usage = AC_BACK;
                break;
            case KC_WWW_FORWARD:
                usage = AC_FORWARD;
                break;
            case KC_WWW_STOP:
                usage = AC_STOP;
                break;
            case KC_WWW_REFRESH:
                usage = AC_REFRESH;
                break;
            case KC_WWW_FAVORITES:
                usage = AC_BOOKMARKS;
                break;
        }
        host_consumer_send(usage);
    }
    else if IS_SYSTEM(code) {
        uint16_t usage = 0;
        switch (code) {
            case KC_SYSTEM_POWER:
                usage = SYSTEM_POWER_DOWN;
                break;
            case KC_SYSTEM_SLEEP:
                usage = SYSTEM_SLEEP;
                break;
            case KC_SYSTEM_WAKE:
                usage = SYSTEM_WAKE_UP;
                break;
        }
        host_system_send(usage);
    }

}

static void unregister_code(uint8_t code)
{
    if IS_KEY(code) {
        host_del_key(code);
        host_send_keyboard_report();
    }
    else if IS_MOD(code) {
        host_del_mod_bit(MOD_BIT(code));
        host_send_keyboard_report();
    }
    else if IS_FN(code) {
        host_del_key(keymap_fn_keycode(FN_INDEX(code)));
        host_send_keyboard_report();
    }
    else if IS_MOUSEKEY(code) {
#ifdef MOUSEKEY_ENABLE
        mousekey_off(code);
        mousekey_send();
#endif
    }
    else if IS_CONSUMER(code) {
        host_consumer_send(0x0000);
    }
    else if IS_SYSTEM(code) {
        host_system_send(0x0000);
    }
}

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
#define NEXT(state)     do { \
    Kdebug("NEXT: "); Kdebug_P(state_str(kbdstate)); \
    kbdstate = state; \
    Kdebug(" -> "); Kdebug_P(state_str(kbdstate)); Kdebug("\n"); \
} while (0)

static inline void process_key(keyevent_t event)
{
    uint8_t code = keymap_get_keycode(current_layer, event.key.row, event.key.col);
    keykind_t kind = get_keykind(code, event.pressed);

    uint8_t tmp_mods;

    Kdebug("state: "); Kdebug_P(state_str(kbdstate));
    Kdebug(" kind: "); Kdebug_hex(kind);
    Kdebug(" code: "); Kdebug_hex(code);
    if (event.pressed) { Kdebug("d"); } else { Kdebug("u"); }
    Kdebug("\n");

    switch (kbdstate) {
        case IDLE:
            switch (kind) {
                case FN_DOWN:
                    layer_switch_on(code);
                    break;
                case FN_UP:
                    layer_switch_off(code);
                    break;
                case FNK_DOWN:
                    // repeat Fn alt key when press Fn key down, up then down again quickly
                    if (KEYEQ(delayed_fn.event.key, event.key) &&
                            timer_elapsed(delayed_fn.time) < LAYER_DELAY) {
                        register_code(code);
                        NEXT(PRESSING);
                    } else {
                        delayed_fn = (keyrecord_t) {
                            .event = event,
                            .code = code,
                            .mods = keyboard_report->mods,
                            .time = timer_read()
                        };
                        NEXT(DELAYING);
                    }
                    break;
                case FNK_UP:
                    layer_switch_off(code);
                    break;
                case KEY_DOWN:
                    register_code(code);
                    NEXT(PRESSING);
                    break;
                case MOD_DOWN:
                    register_code(code);
                    break;
                case KEY_UP:
                case MOD_UP:
                    unregister_code(code);
                    break;
                default:
                    break;
            }
            break;
        case PRESSING:
            switch (kind) {
                case FN_DOWN:
                    // ignored when any key is pressed
                    break;
                case FN_UP:
                    if (layer_switch_off(code))
                        NEXT(IDLE);
                    break;
                case FNK_DOWN:
                    register_code(code);
                    break;
                case FNK_UP:
                    if (layer_switch_off(code)) {
                        NEXT(IDLE);
                    } else {
                        unregister_code(code);
                        if (!anykey_sent_to_host())
                            NEXT(IDLE);
                    }
                    break;
                case KEY_DOWN:
                case MOD_DOWN:
                    register_code(code);
                    break;
                case KEY_UP:
                case MOD_UP:
                    unregister_code(code);
                    if (!anykey_sent_to_host())
                        NEXT(IDLE);
                    break;
                default:
                    break;
            }
            break;
        case DELAYING:
            switch (kind) {
                case FN_DOWN:
                case FNK_DOWN:
                case KEY_DOWN:
                    waiting_key = (keyrecord_t) {
                        .event = event,
                        .code = code,
                        .mods = keyboard_report->mods,
                        .time = timer_read()
                    };
                    NEXT(WAITING);
                    break;
                case MOD_DOWN:
                    register_code(code);
                    break;
                case FN_UP:
                    if (layer_switch_off(code))
                        NEXT(IDLE);
                    break;
                case FNK_UP:
                    if (code == delayed_fn.code) {
                        // type Fn with alt keycode
                        // restore the mod status at the time of pressing Fn key
                        tmp_mods = keyboard_report->mods;
                        host_set_mods(delayed_fn.mods);
                        register_code(delayed_fn.code);
                        unregister_code(delayed_fn.code);
                        host_set_mods(tmp_mods);
                        NEXT(IDLE);
                    } else {
                        if (layer_switch_off(code))
                            NEXT(IDLE);
                    }
                    break;
                case KEY_UP:
                case MOD_UP:
                    unregister_code(code);
                    break;
                default:
                    break;
            }
            break;
        case WAITING:
            switch (kind) {
                case FN_DOWN:
                case FNK_DOWN:
                case KEY_DOWN:
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
                case MOD_DOWN:
                    register_code(code);
                    break;
                case FN_UP:
                    if (layer_switch_off(code))
                        NEXT(IDLE);
                    break;
                case FNK_UP:
                    if (code == delayed_fn.code) {
                        // alt down, key down, alt up
                        tmp_mods = keyboard_report->mods;
                        host_set_mods(delayed_fn.mods);
                        register_code(delayed_fn.code);
                        host_set_mods(waiting_key.mods);
                        register_code(waiting_key.code);
                        unregister_code(delayed_fn.code);
                        host_set_mods(tmp_mods);
                        NEXT(IDLE);
                    } else {
                        if (layer_switch_off(code))
                            NEXT(IDLE);
                    }
                    break;
                case KEY_UP:
                    if (code == waiting_key.code) {
                        layer_switch_on(delayed_fn.code);
                        NEXT(IDLE);
                        // process waiting_key
                        tmp_mods = keyboard_report->mods;
                        host_set_mods(waiting_key.mods);
                        process_key(waiting_key.event);
                        host_set_mods(tmp_mods);
                        process_key(event);
                    } else {
                        unregister_code(code);
                    }
                    break;
                case MOD_UP:
                    unregister_code(code);
                    break;
                default:
                    break;
            }
            break;
    }
}

void keyboard_init(void)
{
    debug_keyboard = true;

    timer_init();
    matrix_init();
#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_init();
#endif
}

void keyboard_task(void)
{
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;

    matrix_scan();
    for (int r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = matrix_get_row(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
            if (debug_matrix) matrix_print();

            for (int c = 0; c < MATRIX_COLS; c++) {
                if (matrix_change & (1<<c)) {
                    process_key((keyevent_t){
                        .key = (key_t){ .row = r, .col = c },
                        .pressed = (matrix_row & (1<<c))
                    });
                    // record a processed key
                    matrix_prev[r] ^= (1<<c);
                    // process a key per task call
                    goto MATRIX_LOOP_END;
                }
            }
        }
    }
    MATRIX_LOOP_END:

    // layer switch when delay term elapses
    if (kbdstate == DELAYING || kbdstate == WAITING) {
        if (timer_elapsed(delayed_fn.time) > LAYER_DELAY) {
            if (kbdstate == DELAYING) {
                layer_switch_on(delayed_fn.code);
                NEXT(IDLE);
            }
            if (kbdstate == WAITING) {
                layer_switch_on(delayed_fn.code);
                NEXT(IDLE);
                uint8_t tmp_mods = keyboard_report->mods;
                host_set_mods(waiting_key.mods);
                process_key(waiting_key.event);
                host_set_mods(tmp_mods);
            }
        }
    }

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

    // FAIL SAFE: clear all key if no key down
    if (matrix_change) {
        matrix_row_t is_matrix_on = 0;
        for (int r = 0; r < MATRIX_ROWS; r++) {
            is_matrix_on |= matrix_get_row(r);
        }
        if (!is_matrix_on) {
            Kdebug("FAIL SAFE: clear all keys(default layer).\n");
            clear_keyboard();
            current_layer = default_layer;
        }
    }

    return;
}

void keyboard_set_leds(uint8_t leds)
{
    led_set(leds);
}
