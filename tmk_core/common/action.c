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
#include "keycode.h"
#include "keyboard.h"
#include "mousekey.h"
#include "command.h"
#include "led.h"
#include "backlight.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "action_macro.h"
#include "action_util.h"
#include "action.h"

#ifdef DEBUG_ACTION
#include "debug.h"
#else
#include "nodebug.h"
#endif


void action_exec(keyevent_t event)
{
    if (!IS_NOEVENT(event)) {
        dprint("\n---- action_exec: start -----\n");
        dprint("EVENT: "); debug_event(event); dprintln();
    }

#ifdef ONEHAND_ENABLE
    if (!IS_NOEVENT(event)) {
        process_hand_swap(&event);
    }
#endif

    keyrecord_t record = { .event = event };

#ifndef NO_ACTION_TAPPING
    action_tapping_process(record);
#else
    process_record(&record);
    if (!IS_NOEVENT(record.event)) {
        dprint("processed: "); debug_record(record); dprintln();
    }
#endif
}

#ifdef ONEHAND_ENABLE
bool swap_hands = false;

void process_hand_swap(keyevent_t *event) {
    static swap_state_row_t swap_state[MATRIX_ROWS];

    keypos_t pos = event->key;
    swap_state_row_t col_bit = (swap_state_row_t)1<<pos.col;
    bool do_swap = event->pressed ? swap_hands :
                                    swap_state[pos.row] & (col_bit);

    if (do_swap) {
        event->key = hand_swap_config[pos.row][pos.col];
        swap_state[pos.row] |= col_bit;
    } else {
        swap_state[pos.row] &= ~(col_bit);
    }
}
#endif

#if !defined(NO_ACTION_LAYER) && defined(PREVENT_STUCK_MODIFIERS)
bool disable_action_cache = false;

void process_record_nocache(keyrecord_t *record)
{
    disable_action_cache = true;
    process_record(record);
    disable_action_cache = false;
}
#else
void process_record_nocache(keyrecord_t *record)
{
    process_record(record);
}
#endif

__attribute__ ((weak))
bool process_record_quantum(keyrecord_t *record) {
    return true;
}

void process_record(keyrecord_t *record) 
{
    if (IS_NOEVENT(record->event)) { return; }

    if(!process_record_quantum(record))
        return;

    action_t action = store_or_get_action(record->event.pressed, record->event.key);
    dprint("ACTION: "); debug_action(action);
#ifndef NO_ACTION_LAYER
    dprint(" layer_state: "); layer_debug();
    dprint(" default_layer_state: "); default_layer_debug();
#endif
    dprintln();

    process_action(record, action);
}

void process_action(keyrecord_t *record, action_t action)
{
    bool do_release_oneshot = false;
    keyevent_t event = record->event;
#ifndef NO_ACTION_TAPPING
    uint8_t tap_count = record->tap.count;
#endif

#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    if (has_oneshot_layer_timed_out()) {
        dprintf("Oneshot layer: timeout\n");
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
#endif

    if (event.pressed) {
        // clear the potential weak mods left by previously pressed keys
        clear_weak_mods();
    }

#ifndef NO_ACTION_ONESHOT
    // notice we only clear the one shot layer if the pressed key is not a modifier.
    if (is_oneshot_layer_active() && event.pressed && !IS_MOD(action.key.code)) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        do_release_oneshot = !is_oneshot_layer_active();
    }
#endif

    switch (action.kind.id) {
        /* Key and Mods */
        case ACT_LMODS:
        case ACT_RMODS:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS) ?  action.key.mods :
                                                                action.key.mods<<4;
                if (event.pressed) {
                    if (mods) {
                        if (IS_MOD(action.key.code) || action.key.code == KC_NO) {
                            // e.g. LSFT(KC_LGUI): we don't want the LSFT to be weak as it would make it useless.
                            // This also makes LSFT(KC_LGUI) behave exactly the same as LGUI(KC_LSFT).
                            // Same applies for some keys like KC_MEH which are declared as MEH(KC_NO).
                            add_mods(mods);
                        } else {
                            add_weak_mods(mods);
                        }
                        send_keyboard_report();
                    }
                    register_code(action.key.code);
                } else {
                    unregister_code(action.key.code);
                    if (mods) {
                        if (IS_MOD(action.key.code) || action.key.code == KC_NO) {
                            del_mods(mods);
                        } else {
                            del_weak_mods(mods);
                        }
                        send_keyboard_report();
                    }
                }
            }
            break;
#ifndef NO_ACTION_TAPPING
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS_TAP) ?  action.key.mods :
                                                                    action.key.mods<<4;
                switch (action.layer_tap.code) {
    #ifndef NO_ACTION_ONESHOT
                    case MODS_ONESHOT:
                        // Oneshot modifier
                        if (event.pressed) {
                            if (tap_count == 0) {
                                dprint("MODS_TAP: Oneshot: 0\n");
                                register_mods(mods);
                            } else if (tap_count == 1) {
                                dprint("MODS_TAP: Oneshot: start\n");
                                set_oneshot_mods(mods);
                    #if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE > 1
                            } else if (tap_count == ONESHOT_TAP_TOGGLE) {
                                dprint("MODS_TAP: Toggling oneshot");
                                clear_oneshot_mods();
                                set_oneshot_locked_mods(mods);
                                register_mods(mods);
                    #endif
                            } else {
                                register_mods(mods);
                            }
                        } else {
                            if (tap_count == 0) {
                                clear_oneshot_mods();
                                unregister_mods(mods);
                            } else if (tap_count == 1) {
                                // Retain Oneshot mods
                    #if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE > 1
                                if (mods & get_mods()) {
                                    clear_oneshot_locked_mods();
                                    clear_oneshot_mods();
                                    unregister_mods(mods);
                                }
                            } else if (tap_count == ONESHOT_TAP_TOGGLE) {
                                // Toggle Oneshot Layer
                    #endif
                            } else {
                                clear_oneshot_mods();
                                unregister_mods(mods);
                            }
                        }
                        break;
    #endif
                    case MODS_TAP_TOGGLE:
                        if (event.pressed) {
                            if (tap_count <= TAPPING_TOGGLE) {
                                register_mods(mods);
                            }
                        } else {
                            if (tap_count < TAPPING_TOGGLE) {
                                unregister_mods(mods);
                            }
                        }
                        break;
                    default:
                        if (event.pressed) {
                            if (tap_count > 0) {
#ifndef IGNORE_MOD_TAP_INTERRUPT
                                if (record->tap.interrupted) {
                                    dprint("mods_tap: tap: cancel: add_mods\n");
                                    // ad hoc: set 0 to cancel tap
                                    record->tap.count = 0;
                                    register_mods(mods);
                                } else
#endif
                                {
                                    dprint("MODS_TAP: Tap: register_code\n");
                                    register_code(action.key.code);
                                }
                            } else {
                                dprint("MODS_TAP: No tap: add_mods\n");
                                register_mods(mods);
                            }
                        } else {
                            if (tap_count > 0) {
                                dprint("MODS_TAP: Tap: unregister_code\n");
                                unregister_code(action.key.code);
                            } else {
                                dprint("MODS_TAP: No tap: add_mods\n");
                                unregister_mods(mods);
                            }
                        }
                        break;
                }
            }
            break;
#endif
#ifdef EXTRAKEY_ENABLE
        /* other HID usage */
        case ACT_USAGE:
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
            break;
#endif
#ifdef MOUSEKEY_ENABLE
        /* Mouse key */
        case ACT_MOUSEKEY:
            if (event.pressed) {
                mousekey_on(action.key.code);
                mousekey_send();
            } else {
                mousekey_off(action.key.code);
                mousekey_send();
            }
            break;
#endif
#ifndef NO_ACTION_LAYER
        case ACT_LAYER:
            if (action.layer_bitop.on == 0) {
                /* Default Layer Bitwise Operation */
                if (!event.pressed) {
                    uint8_t shift = action.layer_bitop.part*4;
                    uint32_t bits = ((uint32_t)action.layer_bitop.bits)<<shift;
                    uint32_t mask = (action.layer_bitop.xbit) ? ~(((uint32_t)0xf)<<shift) : 0;
                    switch (action.layer_bitop.op) {
                        case OP_BIT_AND: default_layer_and(bits | mask); break;
                        case OP_BIT_OR:  default_layer_or(bits | mask);  break;
                        case OP_BIT_XOR: default_layer_xor(bits | mask); break;
                        case OP_BIT_SET: default_layer_and(mask); default_layer_or(bits); break;
                    }
                }
            } else {
                /* Layer Bitwise Operation */
                if (event.pressed ? (action.layer_bitop.on & ON_PRESS) :
                                    (action.layer_bitop.on & ON_RELEASE)) {
                    uint8_t shift = action.layer_bitop.part*4;
                    uint32_t bits = ((uint32_t)action.layer_bitop.bits)<<shift;
                    uint32_t mask = (action.layer_bitop.xbit) ? ~(((uint32_t)0xf)<<shift) : 0;
                    switch (action.layer_bitop.op) {
                        case OP_BIT_AND: layer_and(bits | mask); break;
                        case OP_BIT_OR:  layer_or(bits | mask);  break;
                        case OP_BIT_XOR: layer_xor(bits | mask); break;
                        case OP_BIT_SET: layer_and(mask); layer_or(bits); break;
                    }
                }
            }
            break;
    #ifndef NO_ACTION_TAPPING
        case ACT_LAYER_TAP:
        case ACT_LAYER_TAP_EXT:
            switch (action.layer_tap.code) {
                case 0xe0 ... 0xef:
                    /* layer On/Off with modifiers(left only) */
                    if (event.pressed) {
                        layer_on(action.layer_tap.val);
                        register_mods(action.layer_tap.code & 0x0f);
                    } else {
                        layer_off(action.layer_tap.val);
                        unregister_mods(action.layer_tap.code & 0x0f);
                    }
                    break;
                case OP_TAP_TOGGLE:
                    /* tap toggle */
                    if (event.pressed) {
                        if (tap_count < TAPPING_TOGGLE) {
                            layer_invert(action.layer_tap.val);
                        }
                    } else {
                        if (tap_count <= TAPPING_TOGGLE) {
                            layer_invert(action.layer_tap.val);
                        }
                    }
                    break;
                case OP_ON_OFF:
                    event.pressed ? layer_on(action.layer_tap.val) :
                                    layer_off(action.layer_tap.val);
                    break;
                case OP_OFF_ON:
                    event.pressed ? layer_off(action.layer_tap.val) :
                                    layer_on(action.layer_tap.val);
                    break;
                case OP_SET_CLEAR:
                    event.pressed ? layer_move(action.layer_tap.val) :
                                    layer_clear();
                    break;
            #ifndef NO_ACTION_ONESHOT
                case OP_ONESHOT:
                    // Oneshot modifier
                #if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE > 1
                    do_release_oneshot = false;
                    if (event.pressed) {
                        del_mods(get_oneshot_locked_mods());
                        if (get_oneshot_layer_state() == ONESHOT_TOGGLED) {
                            reset_oneshot_layer();
                            layer_off(action.layer_tap.val);
                            break;
                        } else if (tap_count < ONESHOT_TAP_TOGGLE) {
                            layer_on(action.layer_tap.val);
                            set_oneshot_layer(action.layer_tap.val, ONESHOT_START);
                        }
                    } else {
                        add_mods(get_oneshot_locked_mods());
                        if (tap_count >= ONESHOT_TAP_TOGGLE) {
                            reset_oneshot_layer();
                            clear_oneshot_locked_mods();
                            set_oneshot_layer(action.layer_tap.val, ONESHOT_TOGGLED);
                        } else {
                            clear_oneshot_layer_state(ONESHOT_PRESSED);
                        }
                    }
                #else
                    if (event.pressed) {
                        layer_on(action.layer_tap.val);
                        set_oneshot_layer(action.layer_tap.val, ONESHOT_START);
                    } else {
                        clear_oneshot_layer_state(ONESHOT_PRESSED);
                        if (tap_count > 1) {
                            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                        }
                    }
                #endif
                    break;
            #endif
                default:
                    /* tap key */
                    if (event.pressed) {
                        if (tap_count > 0) {
                            dprint("KEYMAP_TAP_KEY: Tap: register_code\n");
                            register_code(action.layer_tap.code);
                        } else {
                            dprint("KEYMAP_TAP_KEY: No tap: On on press\n");
                            layer_on(action.layer_tap.val);
                        }
                    } else {
                        if (tap_count > 0) {
                            dprint("KEYMAP_TAP_KEY: Tap: unregister_code\n");
                            unregister_code(action.layer_tap.code);
                        } else {
                            dprint("KEYMAP_TAP_KEY: No tap: Off on release\n");
                            layer_off(action.layer_tap.val);
                        }
                    }
                    break;
            }
            break;
    #endif
#endif
        /* Extentions */
#ifndef NO_ACTION_MACRO
        case ACT_MACRO:
            action_macro_play(action_get_macro(record, action.func.id, action.func.opt));
            break;
#endif
#ifdef BACKLIGHT_ENABLE
        case ACT_BACKLIGHT:
            if (!event.pressed) {
                switch (action.backlight.opt) {
                    case BACKLIGHT_INCREASE:
                        backlight_increase();
                        break;
                    case BACKLIGHT_DECREASE:
                        backlight_decrease();
                        break;
                    case BACKLIGHT_TOGGLE:
                        backlight_toggle();
                        break;
                    case BACKLIGHT_STEP:
                        backlight_step();
                        break;
                    case BACKLIGHT_LEVEL:
                        backlight_level(action.backlight.level);
                        break;
                }
            }
            break;
#endif
        case ACT_COMMAND:
            break;
#ifdef ONEHAND_ENABLE
        case ACT_SWAP_HANDS:
            switch (action.swap.code) {
                case OP_SH_TOGGLE:
                    if (event.pressed) {
                        swap_hands = !swap_hands;
                    }
                    break;
                case OP_SH_ON_OFF:
                    swap_hands = event.pressed;
                    break;
                case OP_SH_OFF_ON:
                    swap_hands = !event.pressed;
                    break;
                case OP_SH_ON:
                    if (!event.pressed) {
                        swap_hands = true;
                    }
                    break;
                case OP_SH_OFF:
                    if (!event.pressed) {
                        swap_hands = false;
                    }
                    break;
    #ifndef NO_ACTION_TAPPING
                case OP_SH_TAP_TOGGLE:
                    /* tap toggle */
                    if (tap_count > 0) {
                        if (!event.pressed) {
                            swap_hands = !swap_hands;
                        }
                    } else {
                        swap_hands = event.pressed;
                    }
                    break;
                default:
                    if (tap_count > 0) {
                        if (event.pressed) {
                            register_code(action.swap.code);
                        } else {
                            unregister_code(action.swap.code);
                        }
                    } else {
                        swap_hands = event.pressed;
                    }
    #endif
            }
#endif
#ifndef NO_ACTION_FUNCTION
        case ACT_FUNCTION:
            action_function(record, action.func.id, action.func.opt);
            break;
#endif
        default:
            break;
    }

#ifndef NO_ACTION_ONESHOT
    /* Because we switch layers after a oneshot event, we need to release the
     * key before we leave the layer or no key up event will be generated.
     */
    if (do_release_oneshot && !(get_oneshot_layer_state() & ONESHOT_PRESSED )   ) {
        record->event.pressed = false;
        layer_on(get_oneshot_layer());
        process_record(record);
        layer_off(get_oneshot_layer());
    }
#endif
}




/*
 * Utilities for actions.
 */
void register_code(uint8_t code)
{
    if (code == KC_NO) {
        return;
    }

#ifdef LOCKING_SUPPORT_ENABLE
    else if (KC_LOCKING_CAPS == code) {
#ifdef LOCKING_RESYNC_ENABLE
        // Resync: ignore if caps lock already is on
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) return;
#endif
        add_key(KC_CAPSLOCK);
        send_keyboard_report();
        del_key(KC_CAPSLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_NUM == code) {
#ifdef LOCKING_RESYNC_ENABLE
        if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) return;
#endif
        add_key(KC_NUMLOCK);
        send_keyboard_report();
        del_key(KC_NUMLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_SCROLL == code) {
#ifdef LOCKING_RESYNC_ENABLE
        if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) return;
#endif
        add_key(KC_SCROLLLOCK);
        send_keyboard_report();
        del_key(KC_SCROLLLOCK);
        send_keyboard_report();
    }
#endif

    else if IS_KEY(code) {
        // TODO: should push command_proc out of this block?
        if (command_proc(code)) return;

#ifndef NO_ACTION_ONESHOT
/* TODO: remove
        if (oneshot_state.mods && !oneshot_state.disabled) {
            uint8_t tmp_mods = get_mods();
            add_mods(oneshot_state.mods);

            add_key(code);
            send_keyboard_report();

            set_mods(tmp_mods);
            send_keyboard_report();
            oneshot_cancel();
        } else
*/
#endif
        {
            add_key(code);
            send_keyboard_report();
        }
    }
    else if IS_MOD(code) {
        add_mods(MOD_BIT(code));
        send_keyboard_report();
    }
    else if IS_SYSTEM(code) {
        host_system_send(KEYCODE2SYSTEM(code));
    }
    else if IS_CONSUMER(code) {
        host_consumer_send(KEYCODE2CONSUMER(code));
    }
}

void unregister_code(uint8_t code)
{
    if (code == KC_NO) {
        return;
    }

#ifdef LOCKING_SUPPORT_ENABLE
    else if (KC_LOCKING_CAPS == code) {
#ifdef LOCKING_RESYNC_ENABLE
        // Resync: ignore if caps lock already is off
        if (!(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) return;
#endif
        add_key(KC_CAPSLOCK);
        send_keyboard_report();
        del_key(KC_CAPSLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_NUM == code) {
#ifdef LOCKING_RESYNC_ENABLE
        if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) return;
#endif
        add_key(KC_NUMLOCK);
        send_keyboard_report();
        del_key(KC_NUMLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_SCROLL == code) {
#ifdef LOCKING_RESYNC_ENABLE
        if (!(host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK))) return;
#endif
        add_key(KC_SCROLLLOCK);
        send_keyboard_report();
        del_key(KC_SCROLLLOCK);
        send_keyboard_report();
    }
#endif

    else if IS_KEY(code) {
        del_key(code);
        send_keyboard_report();
    }
    else if IS_MOD(code) {
        del_mods(MOD_BIT(code));
        send_keyboard_report();
    }
    else if IS_SYSTEM(code) {
        host_system_send(0);
    }
    else if IS_CONSUMER(code) {
        host_consumer_send(0);
    }
}

void register_mods(uint8_t mods)
{
    if (mods) {
        add_mods(mods);
        send_keyboard_report();
    }
}

void unregister_mods(uint8_t mods)
{
    if (mods) {
        del_mods(mods);
        send_keyboard_report();
    }
}

void clear_keyboard(void)
{
    clear_mods();
    clear_keyboard_but_mods();
}

void clear_keyboard_but_mods(void)
{
    clear_weak_mods();
    clear_macro_mods();
    clear_keys();
    send_keyboard_report();
#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
    mousekey_send();
#endif
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif
}

bool is_tap_key(keypos_t key)
{
    action_t action = layer_switch_get_action(key);

    switch (action.kind.id) {
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
        case ACT_LAYER_TAP:
        case ACT_LAYER_TAP_EXT:
            switch (action.layer_tap.code) {
                case 0x00 ... 0xdf:
                case OP_TAP_TOGGLE:
                case OP_ONESHOT:
                    return true;
            }
            return false;
        case ACT_SWAP_HANDS:
            switch (action.swap.code) {
                case 0x00 ... 0xdf:
                case OP_SH_TAP_TOGGLE:
                    return true;
            }
            return false;
        case ACT_MACRO:
        case ACT_FUNCTION:
            if (action.func.opt & FUNC_TAP) { return true; }
            return false;
    }
    return false;
}


/*
 * debug print
 */
void debug_event(keyevent_t event)
{
    dprintf("%04X%c(%u)", (event.key.row<<8 | event.key.col), (event.pressed ? 'd' : 'u'), event.time);
}

void debug_record(keyrecord_t record)
{
    debug_event(record.event);
#ifndef NO_ACTION_TAPPING
    dprintf(":%u%c", record.tap.count, (record.tap.interrupted ? '-' : ' '));
#endif
}

void debug_action(action_t action)
{
    switch (action.kind.id) {
        case ACT_LMODS:             dprint("ACT_LMODS");             break;
        case ACT_RMODS:             dprint("ACT_RMODS");             break;
        case ACT_LMODS_TAP:         dprint("ACT_LMODS_TAP");         break;
        case ACT_RMODS_TAP:         dprint("ACT_RMODS_TAP");         break;
        case ACT_USAGE:             dprint("ACT_USAGE");             break;
        case ACT_MOUSEKEY:          dprint("ACT_MOUSEKEY");          break;
        case ACT_LAYER:             dprint("ACT_LAYER");             break;
        case ACT_LAYER_TAP:         dprint("ACT_LAYER_TAP");         break;
        case ACT_LAYER_TAP_EXT:     dprint("ACT_LAYER_TAP_EXT");     break;
        case ACT_MACRO:             dprint("ACT_MACRO");             break;
        case ACT_COMMAND:           dprint("ACT_COMMAND");           break;
        case ACT_FUNCTION:          dprint("ACT_FUNCTION");          break;
        case ACT_SWAP_HANDS:        dprint("ACT_SWAP_HANDS");        break;
        default:                    dprint("UNKNOWN");               break;
    }
    dprintf("[%X:%02X]", action.kind.param>>8, action.kind.param&0xff);
}
