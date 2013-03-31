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
#include "debug.h"
#include "led.h"
#include "layer_switch.h"
#include "action_tapping.h"
#include "action_oneshot.h"
#include "action_macro.h"
#include "action.h"


void action_exec(keyevent_t event)
{
    if (!IS_NOEVENT(event)) {
        debug("\n---- action_exec: start -----\n");
        debug("EVENT: "); debug_event(event); debug("\n");
    }

    keyrecord_t record = { .event = event };

#ifndef NO_ACTION_TAPPING
    action_tapping_process(record);
#else
    process_action(&record);
    if (!IS_NOEVENT(record.event)) {
        debug("processed: "); debug_record(record); debug("\n");
    }
#endif
}

void process_action(keyrecord_t *record)
{
    keyevent_t event = record->event;
    uint8_t tap_count = record->tap.count;

    if (IS_NOEVENT(event)) { return; }

    action_t action = layer_switch_get_action(event.key);
    debug("ACTION: "); debug_action(action);
    debug(" keymaps: "); keymap_debug();
    debug(" default_layer: "); debug_dec(default_layer); debug("\n");

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
#ifndef NO_ACTION_TAPPING
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS_TAP) ?  action.key.mods :
                                                                    action.key.mods<<4;
                switch (action.layer.code) {
    #ifndef NO_ACTION_ONESHOT
                    case 0x00:
                        // Oneshot modifier
                        if (event.pressed) {
                            if (tap_count == 0) {
                                debug("MODS_TAP: Oneshot: add_mods\n");
                                add_mods(mods);
                            }
                            else if (tap_count == 1) {
                                debug("MODS_TAP: Oneshot: start\n");
                                oneshot_start(mods);
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
                                // cancel oneshot on hold
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
    #endif
                    default:
                        if (event.pressed) {
                            if (tap_count > 0) {
                                if (record->tap.interrupted) {
                                    debug("MODS_TAP: Tap: Cancel: add_mods\n");
                                    // ad hoc: set 0 to cancel tap
                                    record->tap.count = 0;
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
        case ACT_LAYER1:
            switch (action.layer.code) {
                /* Keymap clear */
                case OP_RESET:
                    switch (action.layer.val & 0x03) {
                        case 0:
                            // NOTE: reserved
                            keymap_clear();
                            break;
                        case ON_PRESS:
                            if (event.pressed) {
                                keymap_clear();
                            }
                            break;
                        case ON_RELEASE:
                            if (!event.pressed) {
                                keymap_clear();
                            }
                            break;
                        case ON_BOTH:
                            keymap_clear();
                            break;
                        /* NOTE: 4-7 rserved */
                    }
                    break;
                /* Keymap Reset default layer */
                case (OP_RESET | ON_PRESS):
                    if (event.pressed) {
                        default_layer_set(action.layer.val);
                    }
                    break;
                case (OP_RESET | ON_RELEASE):
                    if (!event.pressed) {
                        default_layer_set(action.layer.val);
                    }
                    break;
                case (OP_RESET | ON_BOTH):
                    default_layer_set(action.layer.val);
                    break;

                /* Keymap Bit invert */
                case OP_INV:
                    /* with tap toggle */
                    if (event.pressed) {
                        if (tap_count < TAPPING_TOGGLE) {
                            debug("KEYMAP_INV: tap toggle(press).\n");
                            keymap_invert(action.layer.val);
                        }
                    } else {
                        if (tap_count <= TAPPING_TOGGLE) {
                            debug("KEYMAP_INV: tap toggle(release).\n");
                            keymap_invert(action.layer.val);
                        }
                    }
                    break;
                case (OP_INV | ON_PRESS):
                    if (event.pressed) {
                        keymap_invert(action.layer.val);
                    }
                    break;
                case (OP_INV | ON_RELEASE):
                    if (!event.pressed) {
                        keymap_invert(action.layer.val);
                    }
                    break;
                case (OP_INV | ON_BOTH):
                    keymap_invert(action.layer.val);
                    break;

                /* Keymap Bit on */
                case OP_ON:
                    if (event.pressed) {
                        keymap_on(action.layer.val);
                    } else {
                        keymap_off(action.layer.val);
                    }
                    break;
                case (OP_ON | ON_PRESS):
                    if (event.pressed) {
                        keymap_on(action.layer.val);
                    }
                    break;
                case (OP_ON | ON_RELEASE):
                    if (!event.pressed) {
                        keymap_on(action.layer.val);
                    }
                    break;
                case (OP_ON | ON_BOTH):
                    keymap_on(action.layer.val);
                    break;

                /* Keymap Bit off */
                case OP_OFF:
                    if (event.pressed) {
                        keymap_off(action.layer.val);
                    } else {
                        keymap_on(action.layer.val);
                    }
                    break;
                case (OP_OFF | ON_PRESS):
                    if (event.pressed) {
                        keymap_off(action.layer.val);
                    }
                    break;
                case (OP_OFF | ON_RELEASE):
                    if (!event.pressed) {
                        keymap_off(action.layer.val);
                    }
                    break;
                case (OP_OFF | ON_BOTH):
                    keymap_off(action.layer.val);
                    break;

                /* Keymap Bit set */
                case OP_SET:
                    if (event.pressed) {
                        keymap_set(action.layer.val);
                    } else {
                        keymap_clear();
                    }
                    break;
                case (OP_SET | ON_PRESS):
                    if (event.pressed) {
                        keymap_set(action.layer.val);
                    }
                    break;
                case (OP_SET | ON_RELEASE):
                    if (!event.pressed) {
                        keymap_set(action.layer.val);
                    }
                    break;
                case (OP_SET | ON_BOTH):
                    keymap_set(action.layer.val);
                    break;

                /* Keymap Bit invert with tap key */
                default:
                    if (event.pressed) {
                        if (tap_count > 0) {
                            debug("KEYMAP_TAP_KEY: Tap: register_code\n");
                            register_code(action.layer.code);
                        } else {
                            debug("KEYMAP_TAP_KEY: No tap: On on press\n");
                            keymap_on(action.layer.val);
                        }
                    } else {
                        if (tap_count > 0) {
                            debug("KEYMAP_TAP_KEY: Tap: unregister_code\n");
                            unregister_code(action.layer.code);
                        } else {
                            debug("KEYMAP_TAP_KEY: No tap: Off on release\n");
                            keymap_off(action.layer.val);
                        }
                    }
                    break;
            }
            break;
#endif
        /* Extentions */
#ifndef NO_ACTION_MACRO
        case ACT_MACRO:
            action_macro_play(action_get_macro(record, action.func.id, action.func.opt));
            break;
#endif
        case ACT_COMMAND:
            break;
#ifndef NO_ACTION_FUNCTION
        case ACT_FUNCTION:
            action_function(record, action.func.id, action.func.opt);
            break;
#endif
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
#ifdef CAPSLOCK_LOCKING_ENABLE
    else if (KC_LOCKING_CAPS == code) {
#ifdef CAPSLOCK_LOCKING_RESYNC_ENABLE
        // Resync: ignore if caps lock already is on
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) return;
#endif
        host_add_key(KC_CAPSLOCK);
        host_send_keyboard_report();
        host_del_key(KC_CAPSLOCK);
        host_send_keyboard_report();
    }
#endif
    else if IS_KEY(code) {
        // TODO: should push command_proc out of this block?
        if (command_proc(code)) return;

#ifndef NO_ACTION_ONESHOT
        if (oneshot_state.mods && !oneshot_state.disabled) {
            uint8_t tmp_mods = host_get_mods();
            host_add_mods(oneshot_state.mods);

            host_add_key(code);
            host_send_keyboard_report();

            host_set_mods(tmp_mods);
            oneshot_cancel();
        } else 
#endif
        {
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
    if (code == KC_NO) {
        return;
    }
#ifdef CAPSLOCK_LOCKING_ENABLE
    else if (KC_LOCKING_CAPS == code) {
#ifdef CAPSLOCK_LOCKING_RESYNC_ENABLE
        // Resync: ignore if caps lock already is off
        if (!(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) return;
#endif
        host_add_key(KC_CAPSLOCK);
        host_send_keyboard_report();
        host_del_key(KC_CAPSLOCK);
        host_send_keyboard_report();
    }
#endif
    else if IS_KEY(code) {
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

bool is_tap_key(key_t key)
{
    action_t action = layer_switch_get_action(key);

    switch (action.kind.id) {
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            return true;
        case ACT_LAYER:
            switch (action.layer.code) {
                case 0x04 ... 0xEF:    /* tap key */
                case OP_INV:
                    return true;
                default:
                    return false;
            }
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
    debug_hex16((event.key.row<<8) | event.key.col);
    if (event.pressed) debug("d("); else debug("u(");
    debug_dec(event.time); debug(")");
}

void debug_record(keyrecord_t record)
{
    debug_event(record.event);
#ifndef NO_ACTION_TAPPING
    debug(":"); debug_dec(record.tap.count);
    if (record.tap.interrupted) debug("-");
#endif
}

void debug_action(action_t action)
{
    switch (action.kind.id) {
        case ACT_LMODS:             debug("ACT_LMODS");             break;
        case ACT_RMODS:             debug("ACT_RMODS");             break;
        case ACT_LMODS_TAP:         debug("ACT_LMODS_TAP");         break;
        case ACT_RMODS_TAP:         debug("ACT_RMODS_TAP");         break;
        case ACT_USAGE:             debug("ACT_USAGE");             break;
        case ACT_MOUSEKEY:          debug("ACT_MOUSEKEY");          break;
        case ACT_LAYER:             debug("ACT_LAYER");             break;
        case ACT_LAYER_BITOP:       debug("ACT_LAYER_BITOP");       break;
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
