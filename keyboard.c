#include "keyboard.h"
#include "host.h"
#include "layer.h"
#include "matrix_skel.h"
#include "led.h"
#include "usb_keycodes.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif


static uint8_t last_led = 0;


void keyboard_init(void)
{
    timer_init();
    matrix_init();
#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_init();
#endif
}

void keyboard_proc(void)
{
    uint8_t fn_bits = 0;

    matrix_scan();

    if (matrix_is_modified()) {
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

    host_swap_keyboard_report();
    host_clear_keyboard_report();
    for (int row = 0; row < matrix_rows(); row++) {
        for (int col = 0; col < matrix_cols(); col++) {
            if (!matrix_is_on(row, col)) continue;

            uint8_t code = layer_get_keycode(row, col);
            if (code == KB_NO) {
                // do nothing
            } else if (IS_MOD(code)) {
                host_add_mod_bit(MOD_BIT(code));
            } else if (IS_FN(code)) {
                fn_bits |= FN_BIT(code);
            }
#ifdef USB_EXTRA_ENABLE
/* TODO: use new API
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
*/
#endif
            else if (IS_KEY(code)) {
                host_add_key(code);
            }
#ifdef MOUSEKEY_ENABLE
            else if (IS_MOUSEKEY(code)) {
                mousekey_decode(code);
            }
#endif
            else {
                debug("ignore keycode: "); debug_hex(code); debug("\n");
            }
        }
    }

    layer_switching(fn_bits);

    if (command_proc()) {
        // not send report
        return;
    }

    if (matrix_is_modified()) {
        host_send_keyboard_report();
#ifdef DEBUG_LED
        // LED flash for debug
        DEBUG_LED_CONFIG;
        DEBUG_LED_OFF;
#endif
    }

#ifdef MOUSEKEY_ENABLE
    mousekey_send();
#endif

#ifdef PS2_MOUSE_ENABLE
    // TODO: should comform new API
    if (ps2_mouse_read() == 0)
        ps2_mouse_usb_send();
#endif

    if (last_led != host_keyboard_led()) {
        led_set(host_keyboard_led());
        last_led = host_keyboard_led();
    }
}
