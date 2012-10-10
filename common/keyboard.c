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
#ifdef EXTRAKEY_ENABLE
#include <util/delay.h>
#endif


#define LAYER_DELAY     250

typedef enum keykind {
    NONE,
    FN_DOWN, FN_UP,
    FNK_DOWN, FNK_UP,
    KEY_DOWN, KEY_UP,
    MOD_DOWN, MOD_UP,
} keykind_t;

typedef enum { IDLE, DELAYING, WAITING, PRESSING } kbdstate_t;


uint8_t current_layer = 0;
uint8_t default_layer = 0;

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

static void layer_switch_on(uint8_t code)
{
    if (!IS_FN(code)) return;
    fn_state_bits |= FN_BIT(code);
    if (current_layer != keymap_fn_layer(FN_INDEX(code))) {
        clear_keyboard_but_mods();

        debug("Layer Switch(on): "); debug_hex(current_layer);
        current_layer = keymap_fn_layer(FN_INDEX(code));
        debug(" -> "); debug_hex(current_layer); debug("\n");
    }
}

static void layer_switch_off(uint8_t code)
{
    if (!IS_FN(code)) return;
    fn_state_bits &= ~FN_BIT(code);
    if (current_layer != keymap_fn_layer(biton(fn_state_bits))) {
        clear_keyboard_but_mods();

        debug("Layer Switch(off): "); debug_hex(current_layer);
        current_layer = keymap_fn_layer(biton(fn_state_bits));
        debug(" -> "); debug_hex(current_layer); debug("\n");
    }
}

// whether any key except modifier is down or not
static inline bool is_anykey_down(void)
{
    for (int r = 0; r < MATRIX_ROWS; r++) {
        matrix_row_t matrix_row = matrix_get_row(r);
        for (int c = 0; c < MATRIX_COLS; c++) {
            if (matrix_row && (1<<c)) {
                if (IS_KEY(keymap_get_keycode(current_layer, r, c))) {
                    return true;
                }
            }
        }
    }
    return false;
}

static void register_code(uint8_t code)
{
    if IS_KEY(code) {
        host_add_key(code);
        host_send_keyboard_report();
    }
    else if IS_MOD(code) {
        host_add_mod_bit(MOD_BIT(code));
        host_send_keyboard_report();
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
 * Event/State|IDLE             DELAYING[f]     WAITING[f,k]        PRESSING
 * -----------+------------------------------------------------------------------
 * Fn  Down   |IDLE(L+)         WAITING(Sk)     WAITING(Sk)         -
 *     Up     |IDLE(L-)         IDLE(L-)        IDLE(L-)            IDLE(L-)
 * Fnk Down   |DELAYING(Sf)     WAITING(Sk)     WAINTING(Sk)        PRESSING(Rf)
 *     Up     |IDLE(L-)         IDLE(Rf,Uf)     IDLE(Rf,Ps,Uf)*3    PRESSING(Uf)
 * Key Down   |PRESSING(Rk)     WAITING(Sk)     WAITING(Sk)         PRESSING(Rk)
 *     Up     |IDLE(Uk)         DELAYING(Uk)    IDLE(L+,Ps,Uk)      IDLE(Uk)*4
 * Delay      |-                IDLE(L+)        IDLE(L+,Ps)         -
 *            |
 * No key Down|IDLE(Ld)         IDLE(Ld)        IDLE(Ld)            IDLE(Ld)
 *
 * *2: register Fnk if any key is pressing
 * *3: when Fnk == Stored Fnk, if not ignore.
 * *4: when no registered key any more
 *
 * States:
 *      IDLE:
 *      DELAYING: delay layer switch after pressing Fn with alt keycode
 *      WAITING: key is pressed during DELAYING
 *
 * Events:
 *      Fn: Fn key without alternative keycode
 *      Fnk: Fn key with alternative keycode
 *      -: ignore
 *
 * Actions:
 *      Rk: register key
 *      Uk: unregister key
 *      Rf: register stored Fn(alt keycode)
 *      Uf: unregister stored Fn(alt keycode)
 *      Rs: register stored key
 *      Us: unregister stored key
 *      Sk: store key
 *      Sf: store Fn
 *      Ps: play stored key(Interpret stored key and transit state)
 *      L+: Switch to new layer(*unregister* all keys but modifiers)
 *      L-: Switch back to last layer(*unregister* all keys but modifiers)
 *      Ld: Switch back to default layer(*unregister* all keys but modifiers)
 */
#define NEXT(state)     do { \
    debug("NEXT: "); print_P(state_str(kbdstate)); \
    kbdstate = state; \
    debug(" -> "); print_P(state_str(kbdstate)); debug("\n"); \
} while (0)

static inline void process_key(keyevent_t event)
{
    uint8_t code = keymap_get_keycode(current_layer, event.key.row, event.key.col);
    keykind_t kind = get_keykind(code, event.pressed);

    uint8_t tmp_mods;

    debug("state: "); print_P(state_str(kbdstate));
    debug(" kind: "); debug_hex(kind);
    debug(" code: "); debug_hex(code);
    if (event.pressed) { debug("d"); } else { debug("u"); }
    debug("\n");

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
                        register_code(keymap_fn_keycode(FN_INDEX(code)));
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
                    layer_switch_off(code);
                    NEXT(IDLE);
                    break;
                case FNK_DOWN:
                    register_code(keymap_fn_keycode(FN_INDEX(code)));
                    break;
                case FNK_UP:
                    // can't know whether layer switched or not
                    layer_switch_off(code);
                    unregister_code(keymap_fn_keycode(FN_INDEX(code)));
                    break;
                case KEY_DOWN:
                case MOD_DOWN:
                    register_code(code);
                    break;
                case KEY_UP:
                case MOD_UP:
                    unregister_code(code);
                    // TODO: no key registered? mousekey, mediakey, systemkey
                    if (!host_has_anykey())
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
                    layer_switch_off(code);
                    NEXT(IDLE);
                    break;
                case FNK_UP:
                    if (code == delayed_fn.code) {
                        // type Fn with alt keycode
                        // restore the mod status at the time of pressing Fn key
                        tmp_mods = keyboard_report->mods;
                        host_set_mods(delayed_fn.mods);
                        register_code(keymap_fn_keycode(FN_INDEX(delayed_fn.code)));
                        unregister_code(keymap_fn_keycode(FN_INDEX(delayed_fn.code)));
                        host_set_mods(tmp_mods);
                        NEXT(IDLE);
                    } else {
                        layer_switch_off(code);
                        NEXT(IDLE);
                    }
                    break;
                case KEY_UP:
                    unregister_code(code);
                    NEXT(IDLE);
                    break;
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
                    register_code(keymap_fn_keycode(FN_INDEX(delayed_fn.code)));
                    host_set_mods(waiting_key.mods);
                    register_code(waiting_key.code);
                    host_set_mods(tmp_mods);
                    register_code(code);
                    NEXT(IDLE);
                    break;
                case MOD_DOWN:
                    register_code(code);
                    break;
                case FN_UP:
                    layer_switch_off(code);
                    NEXT(IDLE);
                    break;
                case FNK_UP:
                    if (code == delayed_fn.code) {
                        // alt down, key down, alt up
                        tmp_mods = keyboard_report->mods;
                        host_set_mods(delayed_fn.mods);
                        register_code(keymap_fn_keycode(FN_INDEX(delayed_fn.code)));
                        host_set_mods(waiting_key.mods);
                        register_code(waiting_key.code);
                        unregister_code(keymap_fn_keycode(FN_INDEX(delayed_fn.code)));
                        host_set_mods(tmp_mods);
                        NEXT(IDLE);
                    } else {
                        layer_switch_off(code);
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
    if (command_proc()) {
        debug("COMMAND\n");
        // TODO: COMMAND state?
        clear_keyboard();
        return;
    }

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
            debug("FAIL SAFE: clear all keys.\n");
            clear_keyboard();
        }
    }
    
    return;
}

void keyboard_set_leds(uint8_t leds)
{
    led_set(leds);
}
