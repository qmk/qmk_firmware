#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "util.h"
#include "jump_bootloader.h"
#include "usb_keyboard.h"
#include "usb_keycodes.h"
#include "usb.h"
#include "layer.h"
#include "matrix_skel.h"
#include "keymap_skel.h"
#include "key_process.h"
#ifdef MOUSEKEY_ENABLE
#   include "mousekey.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#   include "ps2_mouse.h"
#endif
#ifdef USB_EXTRA_ENABLE
#   include "usb_extra.h"
#endif
#ifdef USB_MOUSE_ENABLE
#   include "usb_mouse.h"
#endif


// TODO: refactoring
void proc_matrix(void) {
    bool modified = false;
    uint8_t fn_bits = 0;

    matrix_scan();
    modified = matrix_is_modified();
    
    if (modified) {
        if (debug_matrix) matrix_print();
#ifdef DEBUG_LED
        // LED flash for debug
        DEBUG_LED_CONFIG;
        DEBUG_LED_ON;
#endif
    }

    if (matrix_has_ghost()) {
        // should send error?
        debug("matrix has ghost!!\n");
        return;
    }

    usb_keyboard_swap_report();
    usb_keyboard_clear_report();
    for (int row = 0; row < matrix_rows(); row++) {
        for (int col = 0; col < matrix_cols(); col++) {
            if (!matrix_is_on(row, col)) continue;

            uint8_t code = layer_get_keycode(row, col);
            if (code == KB_NO) {
                // do nothing
            } else if (IS_MOD(code)) {
                usb_keyboard_add_mod(code);
            } else if (IS_FN(code)) {
                fn_bits |= FN_BIT(code);
            }
#ifdef MOUSEKEY_ENABLE
            else if (IS_MOUSEKEY(code)) {
                mousekey_decode(code);
            }
#endif
#ifdef USB_EXTRA_ENABLE
            // audio control & system control
            else if (code == KB_MUTE) {
                usb_extra_audio_send(AUDIO_MUTE);
                usb_extra_audio_send(0);
                _delay_ms(500);
            } else if (code == KB_VOLU) {
                usb_extra_audio_send(AUDIO_VOL_UP);
                usb_extra_audio_send(0);
                _delay_ms(200);
            } else if (code == KB_VOLD) {
                usb_extra_audio_send(AUDIO_VOL_DOWN);
                usb_extra_audio_send(0);
                _delay_ms(200);
            } else if (code == KB_PWR) {
                if (suspend && remote_wakeup) {
                    usb_remote_wakeup();
                } else {
                    usb_extra_system_send(SYSTEM_POWER_DOWN);
                }
                _delay_ms(1000);
            }
#endif
            // normal key
            else if (IS_KEY(code)) {
                usb_keyboard_add_key(code);
            } else {
                debug("ignore keycode: "); debug_hex(code); debug("\n");
            }
        }
    }

    if (modified) {
#ifdef DEBUG_LED
        // LED flash for debug
        DEBUG_LED_CONFIG;
        DEBUG_LED_OFF;
#endif
    }

    layer_switching(fn_bits);

    // TODO: clean code
    // special mode for control, develop and debug
    if (keymap_is_special_mode(fn_bits)) {
        switch (usb_keyboard_get_key()) {
            case KB_H: // help
                print_enable = true;
                print("b: jump to bootloader\n");
                print("d: toggle debug enable\n");
                print("x: toggle matrix debug\n");
                print("k: toggle keyboard debug\n");
                print("m: toggle mouse debug\n");
                print("p: toggle print enable\n");
                print("v: print version\n");
                print("t: print timer count\n");
                print("s: print status\n");
                print("`: toggle protcol(boot/report)\n");
#ifdef USB_NKRO_ENABLE
                print("n: toggle USB_NKRO\n");
#endif
                print("ESC: power down/wake up\n");
#ifdef PS2_MOUSE_ENABLE
                print("1: ps2_mouse_init \n");
                print("2: ps2_mouse_read \n");
                print("3: ps2_mouse: on/off toggle \n");
#endif
                _delay_ms(500);
                print_enable = false;
                break;
#ifdef PS2_MOUSE_ENABLE
            case KB_1:
                usb_keyboard_clear_report();
                usb_keyboard_send();
                print_enable = true;
                print("ps2_mouse_init...\n");
                _delay_ms(500);
                ps2_mouse_init();
                break;
            case KB_2:
                usb_keyboard_clear_report();
                usb_keyboard_send();
                print_enable = true;
                print("ps2_mouse_read[btn x y]: ");
                _delay_ms(100);
                ps2_mouse_read();
                phex(ps2_mouse_btn); print(" ");
                phex(ps2_mouse_x); print(" ");
                phex(ps2_mouse_y); print("\n");
                print("ps2_mouse_error_count: "); phex(ps2_mouse_error_count); print("\n");
                break;
            case KB_3:
                ps2_mouse_enable = !ps2_mouse_enable;
                print("ps2_mouse: ");
                if (ps2_mouse_enable)
                    print("on");
                else
                    print("off");
                print("\n");
                _delay_ms(500);
                break;
#endif
            case KB_B: // bootloader
                usb_keyboard_clear_report();
                usb_keyboard_send();
                print_enable = true;
                print("jump to bootloader...\n");
                _delay_ms(1000);
                jump_bootloader(); // not return
                break;
            case KB_D: // debug all toggle
                usb_keyboard_clear_report();
                usb_keyboard_send();
                debug_enable = !debug_enable;
                if (debug_enable) {
                    print_enable = true;
                    print("debug enabled.\n");
                    debug_matrix = true;
                    debug_keyboard = true;
                    debug_mouse = true;
                } else {
                    print("debug disabled.\n");
                    print_enable = false;
                    debug_matrix = false;
                    debug_keyboard = false;
                    debug_mouse = false;
                }
                _delay_ms(1000);
                break;
            case KB_X: // debug matrix toggle
                usb_keyboard_clear_report();
                usb_keyboard_send();
                debug_matrix = !debug_matrix;
                if (debug_matrix)
                    print("debug matrix enabled.\n");
                else
                    print("debug matrix disabled.\n");
                _delay_ms(1000);
                break;
            case KB_K: // debug keyboard toggle
                usb_keyboard_clear_report();
                usb_keyboard_send();
                debug_keyboard = !debug_keyboard;
                if (debug_keyboard)
                    print("debug keyboard enabled.\n");
                else
                    print("debug keyboard disabled.\n");
                _delay_ms(1000);
                break;
            case KB_M: // debug mouse toggle
                usb_keyboard_clear_report();
                usb_keyboard_send();
                debug_mouse = !debug_mouse;
                if (debug_mouse)
                    print("debug mouse enabled.\n");
                else
                    print("debug mouse disabled.\n");
                _delay_ms(1000);
                break;
            case KB_V: // print version & information
                usb_keyboard_clear_report();
                usb_keyboard_send();
                print_enable = true;
                print(STR(DESCRIPTION) "\n");
                _delay_ms(1000);
                break;
            case KB_T: // print timer
                usb_keyboard_clear_report();
                usb_keyboard_send();
                print_enable = true;
                print("timer: "); phex16(timer_count); print("\n");
                _delay_ms(500);
                break;
            case KB_P: // print toggle
                usb_keyboard_clear_report();
                usb_keyboard_send();
                if (print_enable) {
                    print("print disabled.\n");
                    print_enable = false;
                } else {
                    print_enable = true;
                    print("print enabled.\n");
                }
                _delay_ms(1000);
                break;
            case KB_S:
                usb_keyboard_clear_report();
                usb_keyboard_send();
                print("UDCON: "); phex(UDCON); print("\n");
                print("UDIEN: "); phex(UDIEN); print("\n");
                print("UDINT: "); phex(UDINT); print("\n");
                print("usb_keyboard_leds:"); phex(usb_keyboard_leds); print("\n");
                print("usb_keyboard_protocol:"); phex(usb_keyboard_protocol); print("\n");
                print("usb_keyboard_idle_config:"); phex(usb_keyboard_idle_config); print("\n");
                print("usb_keyboard_idle_count:"); phex(usb_keyboard_idle_count); print("\n");
#ifdef USB_MOUSE_ENABLE
                print("usb_mouse_protocol:"); phex(usb_mouse_protocol); print("\n");
#endif
                if (usb_keyboard_nkro) print("USB_NKRO: enabled\n"); else print("USB_NKRO: disabled\n");
                _delay_ms(500);
                break;
            case KB_GRV:
                usb_keyboard_clear_report();
                usb_keyboard_send();
                usb_keyboard_protocol = !usb_keyboard_protocol;
                print("keyboard protcol: ");
                if (usb_keyboard_protocol) print("report"); else print("boot");
                print("\n");

#ifdef USB_MOUSE_ENABLE
                usb_mouse_protocol = !usb_mouse_protocol;
                print("mouse protcol: ");
                if (usb_mouse_protocol) print("report"); else print("boot");
                print("\n");
#endif
                _delay_ms(1000);
                break;
#ifdef USB_NKRO_ENABLE
            case KB_N:
                usb_keyboard_clear_report();
                usb_keyboard_send();
                usb_keyboard_nkro = !usb_keyboard_nkro;
                if (usb_keyboard_nkro) print("USB_NKRO: enabled\n"); else print("USB_NKRO: disabled\n");
                _delay_ms(1000);
                break;
#endif
#ifdef USB_EXTRA_ENABLE
            case KB_ESC:
                usb_keyboard_clear_report();
                usb_keyboard_send();
                if (suspend && remote_wakeup) {
                    usb_remote_wakeup();
                } else {
                    usb_extra_system_send(SYSTEM_POWER_DOWN);
                }
                _delay_ms(1000);
                break;
#endif
        }
    }


    if (modified) {
        usb_keyboard_send();
    }

#ifdef MOUSEKEY_ENABLE
    mousekey_usb_send();
#endif

#ifdef PS2_MOUSE_ENABLE
    if (ps2_mouse_read() == 0)
        ps2_mouse_usb_send();
#endif
}
