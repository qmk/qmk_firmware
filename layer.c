#include "keymap_skel.h"
#include "host.h"
#include "debug.h"
#include "timer.h"
#include "layer.h"

/*
 * Parameters:
 *     ENTER_DELAY         |=======|
 *     SEND_FN_TERM        |================|
 *
 * Fn key processing cases:
 * 1. release Fn after SEND_FN_TERM.
 *     Layer sw         ___________|~~~~~~~~~~~|___
 *     Fn press         ___|~~~~~~~~~~~~~~~~~~~|___
 *     Fn send          ___________________________
 *
 * 2. release Fn during SEND_FN_TERM.(not layer used)
 *     Layer sw         ___________|~~~~~~|________
 *     Fn press         ___|~~~~~~~~~~~~~~|________
 *     Fn key send      __________________|~|______
 *     other key press  ___________________________
 *     other key send   ___________________________
 *
 * 3. release Fn during SEND_FN_TERM.(layer used)
 *     Layer sw         ___________|~~~~~~|________
 *     Fn press         ___|~~~~~~~~~~~~~~|________
 *     Fn key send      ___________________________
 *     Fn send          ___________________________
 *     other key press  _____________|~~|__________
 *     other key send   _____________|~~|__________
 *
 * 4. press other key during ENTER_DELAY.
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
#define LAYER_ENTER_DELAY 10

// LAYER_SEND_FN_TERM: send keycode if release key in this term
#define LAYER_SEND_FN_TERM 40


uint8_t default_layer = 0;
uint8_t current_layer = 0;

static bool layer_used = false;
static uint8_t new_layer(uint8_t fn_bits);


uint8_t layer_get_keycode(uint8_t row, uint8_t col)
{
    uint8_t code = keymap_get_keycode(current_layer, row, col);
    // normal key or mouse key
    if ((IS_KEY(code) || IS_MOUSEKEY(code))) {
        layer_used = true;
    }
    return code;
}

// bit substract b from a
#define BIT_SUBT(a, b) (a&(a^b))
void layer_switching(uint8_t fn_bits)
{
    // layer switching
    static uint8_t last_fn = 0;
    static uint8_t last_mods = 0;
    static uint16_t last_timer = 0; 
    static uint8_t sent_fn = 0;

    if (fn_bits == last_fn) { // Fn state is not changed
        if (fn_bits == 0) {
            // do nothing
        } else {
            if (timer_elapsed(last_timer) > LAYER_ENTER_DELAY) {
                uint8_t _layer_to_switch = new_layer(BIT_SUBT(fn_bits, sent_fn));
                if (current_layer != _layer_to_switch) { // not switch layer yet
                    debug("Fn case: 1,2,3(LAYER_ENTER_DELAY passed)\n");
                    debug("Switch Layer: "); debug_hex(current_layer);
                    current_layer = _layer_to_switch;
                    layer_used = false;
                    debug(" -> "); debug_hex(current_layer); debug("\n");
                }
            } else {
                if (host_has_anykey()) { // other keys is pressed
                    uint8_t _fn_to_send = BIT_SUBT(fn_bits, sent_fn);
                    if (_fn_to_send) {
                        debug("Fn case: 4(send Fn before other key pressed)\n");
                        // send only Fn key first
                        host_swap_keyboard_report();
                        host_clear_keyboard_report();
                        host_add_code(keymap_fn_keycode(_fn_to_send));   // TODO: do all Fn keys
                        host_set_mods(last_mods);
                        host_send_keyboard_report();
                        host_swap_keyboard_report();
                        sent_fn |= _fn_to_send;
                    }
                }
            }
            // add Fn keys to send
            //host_add_code(keymap_fn_keycode(fn_bits&sent_fn));  // TODO: do all Fn keys
        }
    } else { // Fn state is changed(edge)
        uint8_t fn_changed = 0;

        debug("fn_bits: "); debug_bin(fn_bits); debug("\n");
        debug("sent_fn: "); debug_bin(sent_fn); debug("\n");
        debug("last_fn: "); debug_bin(last_fn); debug("\n");
        debug("last_mods: "); debug_hex(last_mods); debug("\n");
        debug("last_timer: "); debug_hex16(last_timer); debug("\n");

        // pressed Fn
        if ((fn_changed = BIT_SUBT(fn_bits, last_fn))) {
        debug("fn_changed: "); debug_bin(fn_changed); debug("\n");
            if (host_has_anykey()) {
                debug("Fn case: 5(pressed Fn with other key)\n");
                sent_fn |= fn_changed;
            } else if (fn_changed & sent_fn) { // pressed same Fn in a row
                if (timer_elapsed(last_timer) > LAYER_ENTER_DELAY) {
                    debug("Fn case: 6(repate2)\n");
                    // time passed: not repeate
                    sent_fn &= ~fn_changed;
                } else {
                    debug("Fn case: 6(repate)\n");
                }
            }
        }
        // released Fn
        if ((fn_changed = BIT_SUBT(last_fn, fn_bits))) {
        debug("fn_changed: "); debug_bin(fn_changed); debug("\n");
            if (timer_elapsed(last_timer) < LAYER_SEND_FN_TERM) {
                //if (!layer_used && BIT_SUBT(fn_changed, sent_fn)) {  // layer not used && Fn not sent
                if (BIT_SUBT(fn_changed, sent_fn)) {  // layer not used && Fn not sent
                    debug("Fn case: 2(send Fn one shot: released Fn during LAYER_SEND_FN_TERM)\n");
                    // send only Fn key first
                    host_swap_keyboard_report();
                    host_clear_keyboard_report();
                    host_add_code(keymap_fn_keycode(fn_changed));   // TODO: do all Fn keys
                    host_set_mods(last_mods);
                    host_send_keyboard_report();
                    host_swap_keyboard_report();
                    sent_fn |= fn_changed;
                }
            }
            debug("Switch Layer(released Fn): "); debug_hex(current_layer);
            current_layer = new_layer(BIT_SUBT(fn_bits, sent_fn));
            layer_used = false;
            debug(" -> "); debug_hex(current_layer); debug("\n");
        }

        last_fn = fn_bits;
        last_mods = keyboard_report->mods;
        last_timer = timer_read();
    }
    // send Fn keys
    for (uint8_t i = 0; i < 8; i++) {
        if ((sent_fn & fn_bits) & (1<<i)) {
            host_add_code(keymap_fn_keycode(1<<i));
        }
    }
}

inline
static uint8_t new_layer(uint8_t fn_bits)
{
    return (fn_bits ? keymap_fn_layer(fn_bits) : default_layer);
}
