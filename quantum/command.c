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
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "keycode.h"
#include "host.h"
#include "keymap.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "keyboard.h"
#include "bootloader.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "sleep_led.h"
#include "led.h"
#include "command.h"
#include "quantum.h"
#include "version.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#if defined(MOUSEKEY_ENABLE)
#    include "mousekey.h"
#endif

#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif /* AUDIO_ENABLE */

static bool command_common(uint8_t code);
static void command_common_help(void);
static void print_version(void);
static void print_status(void);
static bool command_console(uint8_t code);
static void command_console_help(void);
#if defined(MOUSEKEY_ENABLE)
static bool mousekey_console(uint8_t code);
#endif

static void switch_default_layer(uint8_t layer);

command_state_t command_state = ONESHOT;

bool command_proc(uint8_t code) {
    switch (command_state) {
        case ONESHOT:
            if (!IS_COMMAND()) return false;
            return (command_extra(code) || command_common(code));
            break;
        case CONSOLE:
            if (IS_COMMAND())
                return (command_extra(code) || command_common(code));
            else
                return (command_console_extra(code) || command_console(code));
            break;
#if defined(MOUSEKEY_ENABLE)
        case MOUSEKEY:
            mousekey_console(code);
            break;
#endif
        default:
            command_state = ONESHOT;
            return false;
    }
    return true;
}

/* TODO: Refactoring is needed. */
/* This allows to define extra commands. return false when not processed. */
bool command_extra(uint8_t code) __attribute__((weak));
bool command_extra(uint8_t code) {
    (void)code;
    return false;
}

bool command_console_extra(uint8_t code) __attribute__((weak));
bool command_console_extra(uint8_t code) {
    (void)code;
    return false;
}

/***********************************************************
 * Command common
 ***********************************************************/

static void command_common_help(void) {
    print(/* clang-format off */
        "\n\t- Magic -\n"

        STR(MAGIC_KEY_DEBUG) ":	Debug Message Toggle\n"
        STR(MAGIC_KEY_DEBUG_MATRIX) ":	Matrix Debug Mode Toggle"
            " - Show keypresses in matrix grid\n"
        STR(MAGIC_KEY_DEBUG_KBD) ":	Keyboard Debug Toggle"
            " - Show keypress report\n"
        STR(MAGIC_KEY_DEBUG_MOUSE) ":	Debug Mouse Toggle\n"
        STR(MAGIC_KEY_VERSION) ":	Version\n"
        STR(MAGIC_KEY_STATUS) ":	Status\n"
        STR(MAGIC_KEY_CONSOLE) ":	Activate Console Mode\n"

#if MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM
        STR(MAGIC_KEY_LAYER0) ":	Switch to Layer 0\n"
        STR(MAGIC_KEY_LAYER1) ":	Switch to Layer 1\n"
        STR(MAGIC_KEY_LAYER2) ":	Switch to Layer 2\n"
        STR(MAGIC_KEY_LAYER3) ":	Switch to Layer 3\n"
        STR(MAGIC_KEY_LAYER4) ":	Switch to Layer 4\n"
        STR(MAGIC_KEY_LAYER5) ":	Switch to Layer 5\n"
        STR(MAGIC_KEY_LAYER6) ":	Switch to Layer 6\n"
        STR(MAGIC_KEY_LAYER7) ":	Switch to Layer 7\n"
        STR(MAGIC_KEY_LAYER8) ":	Switch to Layer 8\n"
        STR(MAGIC_KEY_LAYER9) ":	Switch to Layer 9\n"
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS
        "F1-F10:	Switch to Layer 0-9 (F10 = L0)\n"
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS
        "0-9:	Switch to Layer 0-9\n"
#endif

        STR(MAGIC_KEY_LAYER0_ALT) ":	Switch to Layer 0 (alternate)\n"

        STR(MAGIC_KEY_BOOTLOADER) ":	Jump to Bootloader\n"
        STR(MAGIC_KEY_BOOTLOADER_ALT) ":	Jump to Bootloader (alternate)\n"

#ifdef KEYBOARD_LOCK_ENABLE
        STR(MAGIC_KEY_LOCK) ":	Lock Keyboard\n"
#endif

        STR(MAGIC_KEY_EEPROM) ":	Print EEPROM Settings\n"
        STR(MAGIC_KEY_EEPROM_CLEAR) ":	Clear EEPROM\n"

#ifdef NKRO_ENABLE
        STR(MAGIC_KEY_NKRO) ":	NKRO Toggle\n"
#endif

#ifdef SLEEP_LED_ENABLE
        STR(MAGIC_KEY_SLEEP_LED) ":	Sleep LED Test\n"
#endif
    ); /* clang-format on */
}

static void print_version(void) {
    xprintf("%s", /* clang-format off */
        "\n\t- Version -\n"
        "VID: " STR(VENDOR_ID) "(" STR(MANUFACTURER) ") "
        "PID: " STR(PRODUCT_ID) "(" STR(PRODUCT) ") "
        "VER: " STR(DEVICE_VER) "\n"
        "BUILD:  (" __DATE__ ")\n"
#ifndef SKIP_VERSION
#    ifdef PROTOCOL_CHIBIOS
        "CHIBIOS: " STR(CHIBIOS_VERSION)
            ", CONTRIB: " STR(CHIBIOS_CONTRIB_VERSION) "\n"
#    endif
#endif

    /* build options */
        "OPTIONS:"

#ifdef PROTOCOL_LUFA
        " LUFA"
#endif
#ifdef PROTOCOL_VUSB
        " VUSB"
#endif
#ifdef BOOTMAGIC_ENABLE
        " BOOTMAGIC"
#endif
#ifdef MOUSEKEY_ENABLE
        " MOUSEKEY"
#endif
#ifdef EXTRAKEY_ENABLE
        " EXTRAKEY"
#endif
#ifdef CONSOLE_ENABLE
        " CONSOLE"
#endif
#ifdef COMMAND_ENABLE
        " COMMAND"
#endif
#ifdef NKRO_ENABLE
        " NKRO"
#endif
#ifdef LTO_ENABLE
        " LTO"
#endif

        " " STR(BOOTLOADER_SIZE) "\n"

        "GCC: " STR(__GNUC__)
            "." STR(__GNUC_MINOR__)
            "." STR(__GNUC_PATCHLEVEL__)
#if defined(__AVR__)
        " AVR-LIBC: " __AVR_LIBC_VERSION_STRING__
        " AVR_ARCH: avr" STR(__AVR_ARCH__)
#endif
        "\n"
    ); /* clang-format on */
}

static void print_status(void) {
    xprintf(/* clang-format off */
        "\n\t- Status -\n"

        "host_keyboard_leds(): %02X\n"
#ifndef PROTOCOL_VUSB
        "keyboard_protocol: %02X\n"
        "keyboard_idle: %02X\n"
#endif
#ifdef NKRO_ENABLE
        "keymap_config.nkro: %02X\n"
#endif
        "timer_read32(): %08lX\n"

        , host_keyboard_leds()
#ifndef PROTOCOL_VUSB
        /* these aren't set on the V-USB protocol, so we just ignore them for now */
        , keyboard_protocol
        , keyboard_idle
#endif
#ifdef NKRO_ENABLE
        , keymap_config.nkro
#endif
        , timer_read32()

    ); /* clang-format on */
}

#if !defined(NO_PRINT) && !defined(USER_PRINT)
static void print_eeconfig(void) {
    xprintf("eeconfig:\ndefault_layer: %u\n", eeconfig_read_default_layer());

    debug_config_t dc;
    dc.raw = eeconfig_read_debug();
    xprintf(/* clang-format off */

        "debug_config.raw: %02X\n"
        ".enable: %u\n"
        ".matrix: %u\n"
        ".keyboard: %u\n"
        ".mouse: %u\n"

        , dc.raw
        , dc.enable
        , dc.matrix
        , dc.keyboard
        , dc.mouse
    ); /* clang-format on */

    keymap_config_t kc;
    kc.raw = eeconfig_read_keymap();
    xprintf(/* clang-format off */

        "keymap_config.raw: %02X\n"
        ".swap_control_capslock: %u\n"
        ".capslock_to_control: %u\n"
        ".swap_lctl_lgui: %u\n"
        ".swap_rctl_rgui: %u\n"
        ".swap_lalt_lgui: %u\n"
        ".swap_ralt_rgui: %u\n"
        ".no_gui: %u\n"
        ".swap_grave_esc: %u\n"
        ".swap_backslash_backspace: %u\n"
        ".nkro: %u\n"
        ".swap_escape_capslock: %u\n"

        , kc.raw
        , kc.swap_control_capslock
        , kc.capslock_to_control
        , kc.swap_lctl_lgui
        , kc.swap_rctl_rgui
        , kc.swap_lalt_lgui
        , kc.swap_ralt_rgui
        , kc.no_gui
        , kc.swap_grave_esc
        , kc.swap_backslash_backspace
        , kc.nkro
        , kc.swap_escape_capslock
    ); /* clang-format on */

#    ifdef BACKLIGHT_ENABLE

    backlight_config_t bc;
    bc.raw = eeconfig_read_backlight();
    xprintf(/* clang-format off */
        "backlight_config"

        ".raw: %02X\n"
        ".enable: %u\n"
        ".level: %u\n"

        , bc.raw
        , bc.enable
        , bc.level

    ); /* clang-format on */

#    endif /* BACKLIGHT_ENABLE */
}
#endif /* !NO_PRINT && !USER_PRINT */

static bool command_common(uint8_t code) {
#ifdef KEYBOARD_LOCK_ENABLE
    static host_driver_t *host_driver = 0;
#endif

    switch (code) {
#ifdef SLEEP_LED_ENABLE

        // test breathing sleep LED
        case MAGIC_KC(MAGIC_KEY_SLEEP_LED):
            print("Sleep LED Test\n");
            sleep_led_toggle();
            led_set(host_keyboard_leds());
            break;
#endif

        // print stored eeprom config
        case MAGIC_KC(MAGIC_KEY_EEPROM):
#if !defined(NO_PRINT) && !defined(USER_PRINT)
            print_eeconfig();
#endif /* !NO_PRINT && !USER_PRINT */
            break;

        // clear eeprom
        case MAGIC_KC(MAGIC_KEY_EEPROM_CLEAR):
            print("Clearing EEPROM\n");
            eeconfig_init();
            break;

#ifdef KEYBOARD_LOCK_ENABLE

        // lock/unlock keyboard
        case MAGIC_KC(MAGIC_KEY_LOCK):
            if (host_get_driver()) {
                host_driver = host_get_driver();
                clear_keyboard();
                host_set_driver(0);
                print("Locked.\n");
            } else {
                host_set_driver(host_driver);
                print("Unlocked.\n");
            }
            break;
#endif

        // print help
        case MAGIC_KC(MAGIC_KEY_HELP):
        case MAGIC_KC(MAGIC_KEY_HELP_ALT):
            command_common_help();
            break;

        // activate console
        case MAGIC_KC(MAGIC_KEY_CONSOLE):
            debug_matrix   = false;
            debug_keyboard = false;
            debug_mouse    = false;
            debug_enable   = false;
            command_console_help();
            print("C> ");
            command_state = CONSOLE;
            break;

        // jump to bootloader
        case MAGIC_KC(MAGIC_KEY_BOOTLOADER):
        case MAGIC_KC(MAGIC_KEY_BOOTLOADER_ALT):
            print("\n\nJumping to bootloader... ");
            reset_keyboard();
            break;

        // debug toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG):
            debug_enable = !debug_enable;
            if (debug_enable) {
                print("\ndebug: on\n");
            } else {
                print("\ndebug: off\n");
                debug_matrix   = false;
                debug_keyboard = false;
                debug_mouse    = false;
            }
            break;

        // debug matrix toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_MATRIX):
            debug_matrix = !debug_matrix;
            if (debug_matrix) {
                print("\nmatrix: on\n");
                debug_enable = true;
            } else {
                print("\nmatrix: off\n");
            }
            break;

        // debug keyboard toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_KBD):
            debug_keyboard = !debug_keyboard;
            if (debug_keyboard) {
                print("\nkeyboard: on\n");
                debug_enable = true;
            } else {
                print("\nkeyboard: off\n");
            }
            break;

        // debug mouse toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_MOUSE):
            debug_mouse = !debug_mouse;
            if (debug_mouse) {
                print("\nmouse: on\n");
                debug_enable = true;
            } else {
                print("\nmouse: off\n");
            }
            break;

        // print version
        case MAGIC_KC(MAGIC_KEY_VERSION):
            print_version();
            break;

        // print status
        case MAGIC_KC(MAGIC_KEY_STATUS):
            print_status();
            break;

#ifdef NKRO_ENABLE

        // NKRO toggle
        case MAGIC_KC(MAGIC_KEY_NKRO):
            clear_keyboard(); // clear to prevent stuck keys
            keymap_config.nkro = !keymap_config.nkro;
            if (keymap_config.nkro) {
                print("NKRO: on\n");
            } else {
                print("NKRO: off\n");
            }
            break;
#endif

            // switch layers

        case MAGIC_KC(MAGIC_KEY_LAYER0_ALT):
            switch_default_layer(0);
            break;

#if MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM

        case MAGIC_KC(MAGIC_KEY_LAYER0):
            switch_default_layer(0);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER1):
            switch_default_layer(1);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER2):
            switch_default_layer(2);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER3):
            switch_default_layer(3);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER4):
            switch_default_layer(4);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER5):
            switch_default_layer(5);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER6):
            switch_default_layer(6);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER7):
            switch_default_layer(7);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER8):
            switch_default_layer(8);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER9):
            switch_default_layer(9);
            break;
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS

        case KC_F1 ... KC_F9:
            switch_default_layer((code - KC_F1) + 1);
            break;
        case KC_F10:
            switch_default_layer(0);
            break;
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS

        case KC_1 ... KC_9:
            switch_default_layer((code - KC_1) + 1);
            break;
        case KC_0:
            switch_default_layer(0);
            break;
#endif

        default:
            print("?");
            return false;
    }
    return true;
}

/***********************************************************
 * Command console
 ***********************************************************/
static void command_console_help(void) {
    print("\n\t- Console -\n"
          "ESC/q:	quit\n"
#ifdef MOUSEKEY_ENABLE
          "m:	mousekey\n"
#endif
    );
}

static bool command_console(uint8_t code) {
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            command_console_help();
            print("C> ");
            return true;
        case KC_Q:
        case KC_ESC:
            command_state = ONESHOT;
            return false;
#if defined(MOUSEKEY_ENABLE)
        case KC_M:
            command_state = MOUSEKEY;
            mousekey_console(KC_SLASH /* ? */);
            return true;
#endif
        default:
            print("?");
            return false;
    }
}

/***********************************************************
 * Mousekey console
 ***********************************************************/

#if defined(MOUSEKEY_ENABLE)

#    if !defined(NO_PRINT) && !defined(USER_PRINT)
static void mousekey_param_print(void) {
    xprintf(/* clang-format off */

#ifndef MK_3_SPEED
        "1:	delay(*10ms): %u\n"
        "2:	interval(ms): %u\n"
        "3:	max_speed: %u\n"
        "4:	time_to_max: %u\n"
        "5:	wheel_max_speed: %u\n"
        "6:	wheel_time_to_max: %u\n"

        , mk_delay
        , mk_interval
        , mk_max_speed
        , mk_time_to_max
        , mk_wheel_max_speed
        , mk_wheel_time_to_max
#else
        "no knobs sorry\n"
#endif

    ); /* clang-format on */
}
#    endif /* !NO_PRINT && !USER_PRINT */

#    if !defined(NO_PRINT) && !defined(USER_PRINT)
static void mousekey_console_help(void) {
    mousekey_param_print();
    xprintf(/* clang-format off */
        "p:	print values\n"
        "d:	set defaults\n"
        "up:	+1\n"
        "dn:	-1\n"
        "lt:	+10\n"
        "rt:	-10\n"
        "ESC/q:	quit\n"

#ifndef MK_3_SPEED
        "\n"
        "speed = delta * max_speed * (repeat / time_to_max)\n"
        "where delta: cursor=%d, wheel=%d\n"
        "See http://en.wikipedia.org/wiki/Mouse_keys\n"
        , MOUSEKEY_MOVE_DELTA, MOUSEKEY_WHEEL_DELTA
#endif

    ); /* clang-format on */
}
#    endif /* !NO_PRINT && !USER_PRINT */

/* Only used by `quantum/command.c` / `command_proc()`. To avoid
 * any doubt: we return `false` to return to the main console,
 * which differs from the `bool` that `command_proc()` returns. */
bool mousekey_console(uint8_t code) {
    static uint8_t  param = 0;
    static uint8_t *pp    = NULL;
    static char *   desc  = NULL;

#    if defined(NO_PRINT) || defined(USER_PRINT) /* -Wunused-parameter */
    (void)desc;
#    endif

    int8_t change = 0;

    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
#    if !defined(NO_PRINT) && !defined(USER_PRINT)
            print("\n\t- Mousekey -\n");
            mousekey_console_help();
#    endif
            break;

        case KC_Q:
        case KC_ESC:
            print("q\n");
            if (!param) return false;
            param = 0;
            pp    = NULL;
            desc  = NULL;
            break;

        case KC_P:
#    if !defined(NO_PRINT) && !defined(USER_PRINT)
            print("\n\t- Values -\n");
            mousekey_param_print();
#    endif
            break;

        case KC_1 ... KC_0: /* KC_0 gives param = 10 */
            param = 1 + code - KC_1;
            switch (param) { /* clang-format off */
#               define PARAM(n, v) case n: pp = &(v); desc = #v; break

#ifndef MK_3_SPEED
                PARAM(1, mk_delay);
                PARAM(2, mk_interval);
                PARAM(3, mk_max_speed);
                PARAM(4, mk_time_to_max);
                PARAM(5, mk_wheel_max_speed);
                PARAM(6, mk_wheel_time_to_max);
#endif /* MK_3_SPEED */

#               undef PARAM
                default:
                    param = 0;
                    print("?\n");
                    break;
            } /* clang-format on */
            if (param) xprintf("%u\n", param);
            break;

            /* clang-format off */
        case KC_UP:    change =  +1; break;
        case KC_DOWN:  change =  -1; break;
        case KC_LEFT:  change = -10; break;
        case KC_RIGHT: change = +10; break;
            /* clang-format on */

        case KC_D:

#    ifndef MK_3_SPEED
            mk_delay             = MOUSEKEY_DELAY / 10;
            mk_interval          = MOUSEKEY_INTERVAL;
            mk_max_speed         = MOUSEKEY_MAX_SPEED;
            mk_time_to_max       = MOUSEKEY_TIME_TO_MAX;
            mk_wheel_max_speed   = MOUSEKEY_WHEEL_MAX_SPEED;
            mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
#    endif /* MK_3_SPEED */

            print("defaults\n");
            break;

        default:
            print("?\n");
            break;
    }

    if (change) {
        if (pp) {
            int16_t val = *pp + change;
            if (val > (int16_t)UINT8_MAX)
                *pp = UINT8_MAX;
            else if (val < 0)
                *pp = 0;
            else
                *pp = (uint8_t)val;
            xprintf("= %u\n", *pp);
        } else {
            print("?\n");
        }
    }

    if (param) {
        xprintf("M%u:%s> ", param, desc ? desc : "???");
    } else {
        print("M> ");
    }
    return true;
}

#endif /* MOUSEKEY_ENABLE */

/***********************************************************
 * Utilities
 ***********************************************************/

static void switch_default_layer(uint8_t layer) {
    xprintf("L%d\n", layer);
    default_layer_set((layer_state_t)1 << layer);
    clear_keyboard();
}
