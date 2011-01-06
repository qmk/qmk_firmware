#include "keymap_skel.h"
#include "usb_keyboard.h"
#include "debug.h"
#include "timer.h"
#include "layer.h"

/*
 * Parameters:
 *     enter_delay         |=======|
 *     send_fn_term        |================|
 *
 * Fn key processing cases:
 * 1. release Fn after send_fn_term.
 *     Layer sw         ___________|~~~~~~~~~~~|___
 *     Fn press         ___|~~~~~~~~~~~~~~~~~~~|___
 *     Fn send          ___________________________
 *
 * 2. release Fn in send_fn_term.(not layer used)
 *     Layer sw         ___________|~~~~~~|________
 *     Fn press         ___|~~~~~~~~~~~~~~|________
 *     Fn key send      __________________|~|______
 *     other key press  ___________________________
 *     other key send   ___________________________
 *
 * 3. release Fn in send_fn_term.(layer used)
 *     Layer sw         ___________|~~~~~~|________
 *     Fn press         ___|~~~~~~~~~~~~~~|________
 *     Fn key send      ___________________________
 *     Fn send          ___________________________
 *     other key press  _____________|~~|__________
 *     other key send   _____________|~~|__________
 *
 * 4. press other key in ENTER_DELAY.
 *     Layer sw         ___________________________
 *     Fn key press     ___|~~~~~~~~~|_____________
 *     Fn key send      ______|~~~~~~|_____________
 *     other key press  ______|~~~|________________
 *     other key send   _______|~~|________________
 *
 * 5. press Fn while press other key.
 *     Layer sw         ___________________________
 *     Fn key press     ___|~~~~~~~~~|_____________
 *     Fn key send      ___|~~~~~~~~~|_____________
 *     other key press  ~~~~~~~|___________________
 *     other key send   ~~~~~~~|___________________
 *
 * 6. press Fn twice quickly and keep holding down.(repeat)
 *     Layer sw         ___________________________
 *     Fn key press     ___|~|____|~~~~~~~~~~~~~~~~
 *     Fn key send      _____|~|__|~~~~~~~~~~~~~~~~
 */

// LAYER_ENTER_DELAY: prevent from moving new layer
#define LAYER_ENTER_DELAY 8

// LAYER_SEND_FN_TERM: send keycode if release key in this term
#define LAYER_SEND_FN_TERM 40


static uint8_t current_layer = 0;
static bool layer_used = false;


uint8_t layer_get_keycode(uint8_t row, uint8_t col)
{
    uint8_t code = keymap_get_keycode(current_layer, row, col);
    // normal key or mouse key
    if ((IS_KEY(code) || IS_MOUSEKEY(code))) {
        layer_used = true;
    }
    return code;
}

void layer_switching(uint8_t fn_bits)
{
    // layer switching
    static uint8_t new_layer = 0;
    static uint8_t last_fn = 0;
    static uint8_t last_mods = 0;
    static uint16_t last_timer = 0; 
    static uint8_t sent_fn = 0;

    if (fn_bits == last_fn) { // Fn key is not changed
        if (current_layer != new_layer) {
            // not switch layer yet
            if (timer_elapsed(last_timer) > LAYER_ENTER_DELAY) {
                debug("Fn case: 1,2,3(switch layer)\n");
                // case: 1,2,3
                current_layer = new_layer;
                debug("timer_elapsed: "); debug_hex16(timer_elapsed(last_timer)); debug("\n"); 
                debug("switch layer: "); debug_hex(current_layer); debug("\n");
            } else if (usb_keyboard_has_key()) {
                debug("Fn case: 4(send Fn first, then add Fn to report)\n");
                // case: 4
                // send only Fn key first
                usb_keyboard_swap_report();
                usb_keyboard_clear_report();
                usb_keyboard_add_code(keymap_fn_keycode(last_fn));
                usb_keyboard_set_mods(last_mods);
                usb_keyboard_send();
                usb_keyboard_swap_report();
                // add Fn key to send with other keys
                usb_keyboard_add_code(keymap_fn_keycode(last_fn));

                new_layer = 0;
                sent_fn = last_fn;
           }
        } else {
            if (fn_bits && new_layer == 0) {
                // case: 4,5,6
                usb_keyboard_add_code(keymap_fn_keycode(last_fn));
                sent_fn = last_fn;
            }
        }
    } else { // Fn key is changed
        if (fn_bits == 0) { // Fn key is released(falling edge)
            if (!layer_used && timer_elapsed(last_timer) < LAYER_SEND_FN_TERM) {
                debug("Fn case: 2(send Fn)\n");
                // case: 2
                usb_keyboard_swap_report();
                usb_keyboard_clear_report();
                usb_keyboard_add_code(keymap_fn_keycode(last_fn));
                usb_keyboard_set_mods(last_mods);
                usb_keyboard_send();
                usb_keyboard_swap_report();
                sent_fn = last_fn;
            }
            debug("Fn case: 1,2,3,4,5,6(return to default layer)\n");
            new_layer = 0;
            current_layer = 0;
        } else { // Fn Key is pressed(rising edge)
            if (usb_keyboard_has_key() ||
                    (fn_bits == sent_fn &&timer_elapsed(last_timer) < LAYER_ENTER_DELAY)) {
                debug("Fn case: 5,6(add Fn to repeat)\n");
                usb_keyboard_add_code(keymap_fn_keycode(fn_bits));
                sent_fn = fn_bits;
            } else {
                debug("Fn case: 1,2,3,4(ready for switching layer)\n");
                // ready for switching layer(case: 1,2,3,4)
                new_layer = keymap_fn_layer(fn_bits);
                sent_fn = 0;
            }
        }
        layer_used = false;
        last_fn = fn_bits;
        last_mods = usb_keyboard_mods;
        last_timer = timer_read();
        debug("new_layer: "); debug_hex(new_layer); debug("\n");
        debug("last_fn: "); debug_bin(last_fn); debug("\n");
        debug("last_mods: "); debug_hex(last_mods); debug("\n");
        debug("last_timer: "); debug_hex16(last_timer); debug("\n");
    }
}
