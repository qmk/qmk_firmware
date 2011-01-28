/* Name: main.c
 * Project: hid-mouse, a very simple HID example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-07
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: main.c 790 2010-05-30 21:00:26Z cs $
 */

/*
This example should run on most AVRs with only little changes. No special
hardware resources except INT0 are used. You may have to change usbconfig.h for
different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
at least be connected to INT0 as well.

We use VID/PID 0x046D/0xC00E which is taken from a Logitech mouse. Don't
publish any hardware using these IDs! This is for demonstration only!
*/

#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"
#include "usart_print.h"        /* This is also an example for using debug macros */
#include "ps2.h"
#include "usb_keycodes.h"
#include "matrix_skel.h"
#include "keymap_skel.h"
#include "layer.h"
#include "print.h"
#include "debug.h"
#include "sendchar.h"
#include "keyboard.h"
#include "timer.h"

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */






int main(void)
{
uchar   i;

print_enable = true;
debug_enable = true;
timer_init();
matrix_init();

    wdt_enable(WDTO_1S);
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */
    /* RESET status: all port bits are inputs without pull-up.
     * That's the way we need D+ and D-. Therefore we don't need any
     * additional hardware initialization.
     */
    odDebugInit();
    DBG1(0x00, 0, 0);       /* debug output: main starts */
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    i = 0;
    while(--i){             /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();

    uint8_t fn_bits = 0;
    while (1) {                /* main event loop */
        DBG1(0x02, 0, 0);   /* debug output: main loop iterates */
        wdt_reset();
        usbPoll();

/*
static uint8_t code = 0;
code = ps2_host_recv();
if (code) {
    odDebug(0x05, &code, 1);
}
*/
        matrix_scan();
        if (matrix_is_modified()) {
            //matrix_print();   // too heavy on USART
            fn_bits = 0;
            report_swap();
            report_clear();
            for (int row = 0; row < matrix_rows(); row++) {
                for (int col = 0; col < matrix_cols(); col++) {
                    if (!matrix_is_on(row, col)) continue;

                    uint8_t code = layer_get_keycode(row, col);
                    if (code == KB_NO) {
                        // do nothing
                    }
                    else if (IS_MOD(code)) {
                        report_add_mod(MOD_BIT(code));
                    }
                    else if (IS_KEY(code)) {
                        report_add_key(code);
                    }
                    else if (IS_FN(code)) {
                        fn_bits |= FN_BIT(code);
                    }
                    else {
                        debug("ignore keycode: "); debug_hex(code); debug("\n");
                    }
                }
            }
        }
        layer_switching(fn_bits);
        if (matrix_is_modified()) {
            report_send();
        }
    }
}
