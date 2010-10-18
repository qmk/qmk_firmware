// TODO: clean unused headers
#include <stdbool.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "print.h"
#include "matrix.h"
#include "keymap.h"
#include "jump_bootloader.h"

#include "key_process.h"


// for Teensy/Teensy++ 2.0
#define LED_CONFIG    (DDRD |= (1<<6))
#define LED_ON        (PORTD |= (1<<6))
#define LED_OFF       (PORTD &= ~(1<<6))

#define MOUSE_MOVE_UNIT 10
#define MOUSE_DELAY_MS 200
#define MOUSE_DELAY_ACC 5



static void print_matrix(void);
static void print_keys(void);
static void print_mouse(int8_t mouse_x, int8_t mouse_y, int8_t wheel_v, int8_t wheel_h);

void proc_matrix(void) {
    static int mouse_repeat = 0;

    bool modified = false;
    bool has_ghost = false;
    int layer = 0;
    int key_index = 0;
    uint8_t mouse_btn = 0;
    int8_t mouse_x = 0;
    int8_t mouse_y = 0;
    int8_t mouse_wheel = 0;
    int8_t mouse_hwheel = 0;

        matrix_scan();
        modified = matrix_is_modified();
        has_ghost = matrix_has_ghost();
        layer = get_layer();

        // print matrix state for debug
        if (modified) {
            print_matrix();

            // LED flash for debug
            LED_CONFIG;
            LED_ON;
        }

        keyboard_modifier_keys = 0;
        for (int i = 0; i < 6; i++) keyboard_keys[i] = KB_NO;
        key_index = 0;
        mouse_btn = 0;
        mouse_x = 0;
        mouse_y = 0;
        mouse_wheel = 0;
        mouse_hwheel = 0;

        // convert matrix state to HID report
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int col = 0; col < MATRIX_COLS; col++) {
                if (matrix[row] & 1<<col) continue;

                uint8_t code = get_keycode(layer, row, col);
                if (code == KB_NO) {
                    continue;
                } else if (KB_LCTRL <= code && code <= KB_RGUI) {
                    // modifier keys(0xE0-0xE7)
                    keyboard_modifier_keys |= 1<<(code & 0x07);
                } else if (code >= MS_UP) {
                    // mouse
                    if (code == MS_UP)    mouse_y -= MOUSE_MOVE_UNIT + (mouse_repeat < 50 ? mouse_repeat/5 : 10);
                    if (code == MS_DOWN)  mouse_y += MOUSE_MOVE_UNIT + (mouse_repeat < 50 ? mouse_repeat/5 : 10);
                    if (code == MS_LEFT)  mouse_x -= MOUSE_MOVE_UNIT + (mouse_repeat < 50 ? mouse_repeat/5 : 10);
                    if (code == MS_RIGHT) mouse_x += MOUSE_MOVE_UNIT + (mouse_repeat < 50 ? mouse_repeat/5 : 10);
                    if (code == MS_BTN1)  mouse_btn |= 1<<0;
                    if (code == MS_BTN2)  mouse_btn |= 1<<1;
                    if (code == MS_BTN3)  mouse_btn |= 1<<2;
                    if (code == MS_BTN4)  mouse_btn |= 1<<3;
                    if (code == MS_BTN5)  mouse_btn |= 1<<4;
                    if (code == MS_WH_UP)  mouse_wheel += 1;
                    if (code == MS_WH_DOWN)  mouse_wheel -= 1;
                    if (code == MS_WH_LEFT)  mouse_hwheel -= 1;
                    if (code == MS_WH_RIGHT) mouse_hwheel += 1;
                } else {
                    // normal keys
                    if (key_index < 6)
                        keyboard_keys[key_index] = code;
                    key_index++;
                }
            }
        }

        if (!has_ghost)  {
            // when 4 left modifier keys down
            if (keyboard_modifier_keys == (MOD_LCTRL | MOD_LSHIFT | MOD_LALT | MOD_LGUI)) {
                // cancel all keys
                keyboard_modifier_keys = 0;
                for (int i = 0; i < 6; i++) keyboard_keys[i] = KB_NO;
                usb_keyboard_send();

                print("jump to bootloader...\n");
                _delay_ms(100);
                jump_bootloader(); // not return
            }

            if (mouse_x || mouse_y || mouse_wheel || mouse_hwheel || mouse_btn != mouse_buttons) {
                mouse_buttons = mouse_btn;
                usb_mouse_move(mouse_x, mouse_y, mouse_wheel, mouse_hwheel);
                print_mouse(mouse_x, mouse_y, mouse_wheel, mouse_hwheel);
                key_sent = true;

                // acceleration
                _delay_ms(MOUSE_DELAY_MS >> (mouse_repeat < MOUSE_DELAY_ACC ? mouse_repeat : MOUSE_DELAY_ACC));
                mouse_repeat++;
            } else {
                mouse_repeat = 0;
            }


            // send keys to host
            if (modified) {
                if (key_index > 6) {
                    //Rollover
                }
                usb_keyboard_send();
                if (keyboard_keys[0])
                    key_sent = true;

                print_keys();
                // LED flash for debug
                LED_CONFIG;
                LED_OFF;
            }
        }
}

static void print_matrix(void) {
    print("\nr/c 01234567\n");
    for (int row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse(matrix[row]);
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
        print("\n");
    }
}

static void print_keys(void) {
    print("\nkeys: ");
    for (int i = 0; i < 6; i++) { phex(keyboard_keys[i]); print(" "); }
    print("\n");
    print("mods: "); phex(keyboard_modifier_keys); print("\n");
}

static void print_mouse(int8_t mouse_x, int8_t mouse_y, int8_t wheel_v, int8_t wheel_h) {
    print("\nmouse_x y v h: ");
    phex(mouse_x); print(" ");
    phex(mouse_y); print(" ");
    phex(wheel_v); print(" ");
    phex(wheel_h); print("\n");
    print("buttons: "); phex(mouse_buttons); print("\n");
}
