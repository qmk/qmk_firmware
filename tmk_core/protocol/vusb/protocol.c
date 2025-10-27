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

#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

#include <usbdrv/usbdrv.h>

#include "vusb.h"

#include "keyboard.h"
#include "host.h"
#include "timer.h"
#include "debug.h"
#include "suspend.h"
#include "wait.h"
#include "sendchar.h"

/* This is from main.c of USBaspLoader */
static void initForUsbConnectivity(void) {
    uint8_t i = 0;

    usbInit();
    /* enforce USB re-enumerate: */
    usbDeviceDisconnect(); /* do this while interrupts are disabled */
    while (--i) {          /* fake USB disconnect for > 250 ms */
        wdt_reset();
        wait_ms(1);
    }
    usbDeviceConnect();
}

static inline void vusb_send_remote_wakeup(void) {
    cli();

    uint8_t ddr_orig = USBDDR;
    USBOUT |= (1 << USBMINUS);
    USBDDR = ddr_orig | USBMASK;
    USBOUT ^= USBMASK;

    wait_ms(25);

    USBOUT ^= USBMASK;
    USBDDR = ddr_orig;
    USBOUT &= ~(1 << USBMINUS);

    sei();
}

bool vusb_suspended = false;

/** \brief Setup USB
 *
 * FIXME: Needs doc
 */
static void setup_usb(void) {
    initForUsbConnectivity();
}

uint16_t sof_timer = 0;

void protocol_setup(void) {
#if USB_COUNT_SOF
    sof_timer = timer_read();
#endif

#ifdef CLKPR
    // avoid unintentional changes of clock frequency in devices that have a
    // clock prescaler
    clock_prescale_set(clock_div_1);
#endif
}

void protocol_pre_init(void) {
    setup_usb();
    sei();
}

void protocol_post_init(void) {
    host_set_driver(vusb_driver());
    wait_ms(50);
}

static inline bool should_do_suspend(void) {
#if USB_COUNT_SOF
    if (usbSofCount != 0) {
        usbSofCount    = 0;
        sof_timer      = timer_read();
        vusb_suspended = false;
    } else {
        // Suspend when no SOF in 3ms-10ms(7.1.7.4 Suspending of USB1.1)
        if (!vusb_suspended && timer_elapsed(sof_timer) > 5) {
            vusb_suspended = true;
        }
    }
#endif
    return vusb_suspended;
}

void protocol_pre_task(void) {
#if !defined(NO_USB_STARTUP_CHECK)
    if (should_do_suspend()) {
        dprintln("suspending keyboard");
        while (should_do_suspend()) {
            suspend_power_down();
            if (suspend_wakeup_condition()) {
                vusb_send_remote_wakeup();

#    if USB_SUSPEND_WAKEUP_DELAY > 0
                // Some hubs, kvm switches, and monitors do
                // weird things, with USB device state bouncing
                // around wildly on wakeup, yielding race
                // conditions that can corrupt the keyboard state.
                //
                // Pause for a while to let things settle...
                wait_ms(USB_SUSPEND_WAKEUP_DELAY);
#    endif
            }
        }
        suspend_wakeup_init();
    }
#endif
}

void protocol_keyboard_task(void) {
    usbPoll();

    // TODO: configuration process is inconsistent. it sometime fails.
    // To prevent failing to configure NOT scan keyboard during configuration
    if (usbConfiguration && usbInterruptIsReady()) {
        keyboard_task();
    }
}

void protocol_post_task(void) {
    // do nothing
}
