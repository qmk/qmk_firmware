#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "util.h"
#include "jump_bootloader.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "usb_extra.h"
#include "usb_keycodes.h"
#include "layer.h"
#include "matrix_skel.h"
#include "keymap_skel.h"
#include "controller.h"
#include "key_process.h"


#define MOUSE_MOVE_UNIT 10
#define MOUSE_MOVE_ACCEL (mouse_repeat < 50 ? mouse_repeat/5 : 10)

#ifndef MOUSE_DELAY_TIME
#   define MOUSE_DELAY_TIME 255
#endif
#define MOUSE_DELAY_MS (MOUSE_DELAY_TIME >> (mouse_repeat < 5 ? mouse_repeat : 4))


// TODO: refactoring
void proc_matrix(void) {
    static int mouse_repeat = 0;

    bool modified = false;
    //bool has_ghost = false;
    int key_index = 0;
    uint8_t mouse_btn = 0;
    int8_t mouse_x = 0;
    int8_t mouse_y = 0;
    int8_t mouse_vwheel = 0;
    int8_t mouse_hwheel = 0;
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

    usb_keyboard_clear_report();
    for (int row = 0; row < matrix_rows(); row++) {
        for (int col = 0; col < matrix_cols(); col++) {
            if (!matrix_is_on(row, col)) continue;

            uint8_t code = layer_get_keycode(row, col);
            if (code == KB_NO) {
                // do nothing
            } else if (IS_MOD(code)) {
                usb_keyboard_mods |= MOD_BIT(code);
            } else if (IS_MOUSE(code)) {
                // mouse
                if (code == MS_UP)
                    mouse_y -= MOUSE_MOVE_UNIT + MOUSE_MOVE_ACCEL;
                if (code == MS_DOWN)
                    mouse_y += MOUSE_MOVE_UNIT + MOUSE_MOVE_ACCEL;
                if (code == MS_LEFT)
                    mouse_x -= MOUSE_MOVE_UNIT + MOUSE_MOVE_ACCEL;
                if (code == MS_RIGHT)
                    mouse_x += MOUSE_MOVE_UNIT + MOUSE_MOVE_ACCEL;
                if (code == MS_BTN1) mouse_btn |= BIT_BTN1;
                if (code == MS_BTN2) mouse_btn |= BIT_BTN2;
                if (code == MS_BTN3) mouse_btn |= BIT_BTN3;
                if (code == MS_BTN4) mouse_btn |= BIT_BTN4;
                if (code == MS_BTN5) mouse_btn |= BIT_BTN5;
                if (code == MS_WH_UP)    mouse_vwheel  += 1;
                if (code == MS_WH_DOWN)  mouse_vwheel  -= 1;
                if (code == MS_WH_LEFT)  mouse_hwheel -= 1;
                if (code == MS_WH_RIGHT) mouse_hwheel += 1;
            } else if (IS_FN(code)) {
                fn_bits |= FN_BIT(code);
            } else if (code == KB_MUTE) {
                usb_extra_send(AUDIO_MUTE);
                usb_extra_send(0);
                _delay_ms(500);
            } else if (code == KB_VOLU) {
                usb_extra_send(AUDIO_VOL_UP);
                usb_extra_send(0);
                _delay_ms(100);
            } else if (code == KB_VOLD) {
                usb_extra_send(AUDIO_VOL_DOWN);
                usb_extra_send(0);
                _delay_ms(100);
            } else {
                // normal keys
                if (key_index < 6)
                    usb_keyboard_keys[key_index] = code;
                key_index++;
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

    // when 4 left modifier keys down
    if (keymap_is_special_mode(fn_bits)) {
        switch (usb_keyboard_keys[0]) {
            case KB_H: // help
                print_enable = true;
                print("b: jump to bootloader\n");
                print("d: debug print toggle\n");
                print("k: keyboard debug toggle\n");
                print("m: mouse debug toggle\n");
                print("x: matrix debug toggle\n");
                print("v: print version\n");
                print("t: print timer count\n");
                print("p: print enable toggle\n");
                _delay_ms(500);
                print_enable = false;
                break;
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
        }
    }


    // send mouse packet to host
    if (mouse_x || mouse_y || mouse_vwheel || mouse_hwheel || mouse_btn != mouse_buttons) {
        mouse_buttons = mouse_btn;
        if (mouse_x && mouse_y)
            usb_mouse_move(mouse_x*0.7, mouse_y*0.7, mouse_vwheel, mouse_hwheel);
        else
            usb_mouse_move(mouse_x, mouse_y, mouse_vwheel, mouse_hwheel);
        usb_mouse_print(mouse_x, mouse_y, mouse_vwheel, mouse_hwheel);

        // acceleration
        _delay_ms(MOUSE_DELAY_MS);
        mouse_repeat++;
    } else {
        mouse_repeat = 0;
    }


    // send key packet to host
    if (modified) {
        if (key_index > 6) {
            //Rollover
        }
        usb_keyboard_send();
    }
}
