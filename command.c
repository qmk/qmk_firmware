#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "usb_keycodes.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "layer.h"
#include "matrix.h"
#include "command.h"

#ifdef HOST_PJRC
#   include "jump_bootloader.h"
#   include "usb_keyboard.h"
#   ifdef USB_EXTRA_ENABLE
#       include "usb_extra.h"
#   endif
#endif


static void help(void);
static void switch_layer(uint8_t layer);


uint8_t command_proc(void)
{
    if (!IS_COMMAND())
        return 0;

    uint8_t processed = 1;
    bool last_print_enable = print_enable;
    print_enable = true;
    switch (host_get_first_key()) {
        case KB_H:
            help();
            break;
        case KB_B:
#ifdef HOST_PJRC
            host_clear_keyboard_report();
            host_send_keyboard_report();
            print("jump to bootloader...\n");
            _delay_ms(1000);
            jump_bootloader(); // not return
#endif
            break;
        case KB_D:
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
        case KB_X: // debug matrix toggle
            debug_matrix = !debug_matrix;
            if (debug_matrix)
                print("debug matrix enabled.\n");
            else
                print("debug matrix disabled.\n");
            break;
        case KB_K: // debug keyboard toggle
            debug_keyboard = !debug_keyboard;
            if (debug_keyboard)
                print("debug keyboard enabled.\n");
            else
                print("debug keyboard disabled.\n");
            break;
        case KB_M: // debug mouse toggle
            debug_mouse = !debug_mouse;
            if (debug_mouse)
                print("debug mouse enabled.\n");
            else
                print("debug mouse disabled.\n");
            break;
        case KB_V: // print version & information
            print(STR(DESCRIPTION) "\n");
            break;
        case KB_T: // print timer
            print("timer: "); phex16(timer_count); print("\n");
            break;
        case KB_P: // print toggle
            if (last_print_enable) {
                print("print disabled.\n");
                last_print_enable = false;
            } else {
                last_print_enable = true;
                print("print enabled.\n");
            }
            break;
        case KB_S:
#ifdef HOST_PJRC
            print("UDCON: "); phex(UDCON); print("\n");
            print("UDIEN: "); phex(UDIEN); print("\n");
            print("UDINT: "); phex(UDINT); print("\n");
            print("usb_keyboard_leds:"); phex(usb_keyboard_leds); print("\n");
            print("usb_keyboard_protocol: "); phex(usb_keyboard_protocol); print("\n");
            print("usb_keyboard_idle_config:"); phex(usb_keyboard_idle_config); print("\n");
            print("usb_keyboard_idle_count:"); phex(usb_keyboard_idle_count); print("\n");
#endif
            break;
#ifdef USB_NKRO_ENABLE
        case KB_N:
            // send empty report before change
            host_clear_keyboard_report();
            host_send_keyboard_report();
            keyboard_nkro = !keyboard_nkro;
            if (keyboard_nkro)
                print("USB_NKRO: enabled\n");
            else
                print("USB_NKRO: disabled\n");
            break;
#endif
#ifdef USB_EXTRA_ENABLE
        case KB_ESC:
#ifdef HOST_PJRC
            if (suspend && remote_wakeup) {
                usb_remote_wakeup();
            } else {
                host_system_send(SYSTEM_POWER_DOWN);
            }
#else
            host_system_send(SYSTEM_POWER_DOWN);
#endif
            break;
#endif
        case KB_BSPC:
            matrix_init();
            print("clear matrix\n");
            break;
        case KB_0:
            switch_layer(0);
            break;
        case KB_1:
            switch_layer(1);
            break;
        case KB_2:
            switch_layer(2);
            break;
        case KB_3:
            switch_layer(3);
            break;
        case KB_4:
            switch_layer(4);
            break;
        default:
            processed = 0;
    }
    if (processed)
        _delay_ms(500);
    print_enable = last_print_enable;
    return processed;
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
#ifdef USB_NKRO_ENABLE
    print("n: toggle USB_NKRO\n");
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
