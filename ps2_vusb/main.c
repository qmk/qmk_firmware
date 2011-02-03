/* Name: main.c
 * Project: hid-mouse, a very simple HID example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-07
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: main.c 790 2010-05-30 21:00:26Z cs $
 */
#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <util/delay.h>     /* for _delay_ms() */
#include "usbdrv.h"
#include "usart_print.h"        /* This is also an example for using debug macros */
#include "usb_keycodes.h"
#include "matrix_skel.h"
#include "keymap_skel.h"
#include "mousekey.h"
#include "keyboard.h"
#include "layer.h"
#include "print.h"
#include "debug.h"
#include "sendchar.h"
#include "host.h"
#include "host_vusb.h"
#include "timer.h"


int main(void)
{
    wdt_enable(WDTO_1S);
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */

    /* RESET status: all port bits are inputs without pull-up.
     * That's the way we need D+ and D-. Therefore we don't need any
     * additional hardware initialization.
     */
    odDebugInit();
    usbInit();

    print_enable = true;
    //debug_enable = true;
    timer_init();
    matrix_init();

    /* enforce re-enumeration, do this while interrupts are disabled! */
    usbDeviceDisconnect();
    uint8_t i = 0;
    while(--i){             /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();

    uint8_t fn_bits = 0;
    while (1) {                /* main event loop */
        wdt_reset();
        usbPoll();
        host_vusb_keyboard_send();

        matrix_scan();
        fn_bits = 0;
        keyboard_swap_report();
        keyboard_clear_report();
        mousekey_clear_report();
        for (int row = 0; row < matrix_rows(); row++) {
            for (int col = 0; col < matrix_cols(); col++) {
                if (!matrix_is_on(row, col)) continue;

                uint8_t code = layer_get_keycode(row, col);
                if (code == KB_NO) {
                    // do nothing
                }
                else if (IS_MOD(code)) {
                    keyboard_add_mod(MOD_BIT(code));
                }
                else if (IS_KEY(code)) {
                    keyboard_add_key(code);
                }
                else if (IS_FN(code)) {
                    fn_bits |= FN_BIT(code);
                }
                else if (IS_MOUSEKEY(code)) {
                    mousekey_decode(code);
                }
                else {
                    debug("ignore keycode: "); debug_hex(code); debug("\n");
                }
            }
        }
        layer_switching(fn_bits);
        if (matrix_is_modified()) {
            keyboard_send();
        }
        mousekey_send();
    }
}
