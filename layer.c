#include "keymap_skel.h"
#include "usb_keyboard.h"
#include "debug.h"
#include "timer.h"
#include "layer.h"

/*
 * LAYER_ENTER_DELAY: prevent from moving new layer
 *                     press                release
 * Fn key sate     ____|~~~~~~~~~~~~~~~~~~~|_______________
 * 
 * enter_delay         |======|
 *                              new layer
 * Layer sw        ___________|~~~~~~~~~~~~|_______________
 */ 
#define LAYER_ENTER_DELAY 10

/*
 * LAYER_SEND_FN_TERM: send keycode if release key in this term
 *                     press          release(send)
 * Fn key state    ____|~~~~~~~~~~~~~|_______________
 *                     press         |       release(not send)
 * Fn key state    ____|~~~~~~~~~~~~~|~~~~~~|__________
 *                                   |      |
 * send_fn_term        |=============o==|   x
 */
#define LAYER_SEND_FN_TERM 30


static uint8_t current_layer = 0;
static bool layer_used = false;


uint8_t layer_get_keycode(uint8_t row, uint8_t col)
{
    uint8_t code = keymap_get_keycode(current_layer, row, col);
    // normal key or mouse key
    if ((IS_KEY(code) || IS_MOUSE(code)))
        layer_used = true;
    return code;
}

void layer_switching(uint8_t fn_bits)
{
    // layer switching
    static uint8_t last_bits = 0;
    static uint8_t last_mod = 0;
    static uint16_t last_timer = 0; 

    //uint16_t now_timer;

    if (fn_bits == last_bits) {
        // switch layer when specific time elapsed
        if (current_layer != keymap_fn_layer(fn_bits) &&
                timer_elapsed(last_timer) > LAYER_ENTER_DELAY) {
            current_layer = keymap_fn_layer(fn_bits);
            debug("time_elapsed: "); debug_hex16(timer_elapsed(last_timer)); debug("\n"); 
            debug("switch layer: "); debug_hex(current_layer); debug("\n");
        }
    } else if (fn_bits == 0) {
        // send key when Fn key is released without using the layer and within specific time
        if ((!layer_used || current_layer != keymap_fn_layer(last_bits)) &&
                timer_elapsed(last_timer) < LAYER_SEND_FN_TERM) {
            uint8_t code = keymap_fn_keycode(last_bits);
            if (code != KB_NO) {
                if (IS_MOD(code)) {
                    keyboard_modifier_keys = last_mod | MOD_BIT(code);
                } else {
                    keyboard_keys[0] = code;
                    keyboard_modifier_keys = last_mod;
                }
                usb_keyboard_send();
                usb_keyboard_print();
                usb_keyboard_clear();
            }
        }
        last_bits = 0;
        last_mod = 0;
        layer_used = false;
        current_layer = 0; // default layer
    } else if ((fn_bits & (fn_bits - 1)) == 0) {
        // switch layer when just one Fn Key is pressed
        if (!usb_keyboard_has_key()) {
            last_bits = fn_bits;
            last_mod = keyboard_modifier_keys;
            last_timer = timer_read();
            debug("last_bits: "); debug_bin(last_bits); debug("\n");
            debug("last_mod: "); debug_hex(last_mod); debug("\n");
            debug("last_timer: "); debug_hex16(last_timer); debug("\n");
        }
    }
}
