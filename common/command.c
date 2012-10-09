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
#include <util/delay.h>
#include "keycode.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "keyboard.h"
#include "matrix.h"
#include "bootloader.h"
#include "command.h"

#ifdef HOST_PJRC
#   include "usb_keyboard.h"
#   ifdef EXTRAKEY_ENABLE
#       include "usb_extra.h"
#   endif
#endif

#ifdef HOST_VUSB
#   include "usbdrv.h"
#endif


static uint8_t command_common(void);
static void help(void);
static void switch_layer(uint8_t layer);

static bool last_print_enable;

uint8_t command_proc(void)
{
    uint8_t processed = 0;
    last_print_enable = print_enable;

    if (!IS_COMMAND())
        return 0;

    print_enable = true;
    if (command_extra() || command_common()) {
        processed = 1;
        _delay_ms(500);
    }
    print_enable = last_print_enable;
    return processed;
}

/* This allows to define extra commands. return 0 when not processed. */
uint8_t command_extra(void) __attribute__ ((weak));
uint8_t command_extra(void)
{
    return 0;
}


static uint8_t command_common(void)
{
    switch (host_get_first_key()) {
        case KC_H:
            help();
            break;
        case KC_B:
            print("jump to bootloader... ");
            _delay_ms(1000);
            bootloader_jump(); // not return
            print("not supported.\n");
            break;
        case KC_D:
            debug_enable = !debug_enable;
            if (debug_enable) {
                last_print_enable = true;
                print("debug enabled.\n");
                debug_matrix = true;
                debug_keyboard = true;
                debug_mouse = true;
            } else {
                print("debug disabled.\n");
                last_print_enable = false;
                debug_matrix = false;
                debug_keyboard = false;
                debug_mouse = false;
            }
            break;
        case KC_X: // debug matrix toggle
            debug_matrix = !debug_matrix;
            if (debug_matrix)
                print("debug matrix enabled.\n");
            else
                print("debug matrix disabled.\n");
            break;
        case KC_K: // debug keyboard toggle
            debug_keyboard = !debug_keyboard;
            if (debug_keyboard)
                print("debug keyboard enabled.\n");
            else
                print("debug keyboard disabled.\n");
            break;
        case KC_M: // debug mouse toggle
            debug_mouse = !debug_mouse;
            if (debug_mouse)
                print("debug mouse enabled.\n");
            else
                print("debug mouse disabled.\n");
            break;
        case KC_V: // print version & information
            print(STR(DESCRIPTION) "\n");
            break;
        case KC_T: // print timer
            print("timer: "); phex16(timer_count); print("\n");
            break;
        case KC_P: // print toggle
            if (last_print_enable) {
                print("print disabled.\n");
                last_print_enable = false;
            } else {
                last_print_enable = true;
                print("print enabled.\n");
            }
            break;
        case KC_S:
            print("host_keyboard_leds:"); phex(host_keyboard_leds()); print("\n");
#ifdef HOST_PJRC
            print("UDCON: "); phex(UDCON); print("\n");
            print("UDIEN: "); phex(UDIEN); print("\n");
            print("UDINT: "); phex(UDINT); print("\n");
            print("usb_keyboard_leds:"); phex(usb_keyboard_leds); print("\n");
            print("usb_keyboard_protocol: "); phex(usb_keyboard_protocol); print("\n");
            print("usb_keyboard_idle_config:"); phex(usb_keyboard_idle_config); print("\n");
            print("usb_keyboard_idle_count:"); phex(usb_keyboard_idle_count); print("\n");
#endif

#ifdef HOST_VUSB
#   if USB_COUNT_SOF
            print("usbSofCount: "); phex(usbSofCount); print("\n");
#   endif
#endif
            break;
#ifdef NKRO_ENABLE
        case KC_N:
            keyboard_nkro = !keyboard_nkro;
            if (keyboard_nkro)
                print("NKRO: enabled\n");
            else
                print("NKRO: disabled\n");
            break;
#endif
#ifdef EXTRAKEY_ENABLE
        case KC_ESC:
#ifdef HOST_PJRC
            if (suspend && remote_wakeup) {
                usb_remote_wakeup();
            } else {
                host_system_send(SYSTEM_POWER_DOWN);
                host_system_send(0);
                _delay_ms(500);
            }
#else
            host_system_send(SYSTEM_POWER_DOWN);
            host_system_send(0);
            _delay_ms(500);
#endif
            break;
#endif
        case KC_BSPC:
            matrix_init();
            print("clear matrix\n");
            break;
        case KC_0:
            switch_layer(0);
            break;
        case KC_1:
            switch_layer(1);
            break;
        case KC_2:
            switch_layer(2);
            break;
        case KC_3:
            switch_layer(3);
            break;
        case KC_4:
            switch_layer(4);
            break;
        default:
            return 0;
    }
    return 1;
}

static void help(void)
{
    print("b: jump to bootloader\n");
    print("d: toggle debug enable\n");
    print("x: toggle matrix debug\n");
    print("k: toggle keyboard debug\n");
    print("m: toggle mouse debug\n");
    print("p: toggle print enable\n");
    print("v: print version\n");
    print("t: print timer count\n");
    print("s: print status\n");
#ifdef NKRO_ENABLE
    print("n: toggle NKRO\n");
#endif
    print("Backspace: clear matrix\n");
    print("ESC: power down/wake up\n");
    print("0: switch to Layer0 \n");
    print("1: switch to Layer1 \n");
    print("2: switch to Layer2 \n");
    print("3: switch to Layer3 \n");
    print("4: switch to Layer4 \n");
}

static void switch_layer(uint8_t layer)
{
    print("current_layer: "); phex(current_layer); print("\n");
    print("default_layer: "); phex(default_layer); print("\n");
    current_layer = layer;
    default_layer = layer;
    print("switch to Layer: "); phex(layer); print("\n");
}
