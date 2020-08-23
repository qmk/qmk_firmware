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
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <usbdrv/usbdrv.h>
#include <usbdrv/oddebug.h>
#include "vusb.h"
#include "keyboard.h"
#include "host.h"
#include "timer.h"
#include "uart.h"
#include "debug.h"
#include "suspend.h"
#include "wait.h"
#include "sendchar.h"

#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#endif

#define UART_BAUD_RATE 115200

#ifdef CONSOLE_ENABLE
void console_task(void);
#endif

#ifdef RAW_ENABLE
void raw_hid_task(void);
#endif

/* This is from main.c of USBaspLoader */
static void initForUsbConnectivity(void) {
    uint8_t i = 0;

    usbInit();
    /* enforce USB re-enumerate: */
    usbDeviceDisconnect(); /* do this while interrupts are disabled */
    while (--i) {          /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
}

static void usb_remote_wakeup(void) {
    cli();

    int8_t ddr_orig = USBDDR;
    USBOUT |= (1 << USBMINUS);
    USBDDR = ddr_orig | USBMASK;
    USBOUT ^= USBMASK;

    _delay_ms(25);

    USBOUT ^= USBMASK;
    USBDDR = ddr_orig;
    USBOUT &= ~(1 << USBMINUS);

    sei();
}

/** \brief Setup USB
 *
 * FIXME: Needs doc
 */
static void setup_usb(void) {
    // debug("initForUsbConnectivity()\n");
    initForUsbConnectivity();

    // for Console_Task
    print_set_sendchar(sendchar);
}

/** \brief Main
 *
 * FIXME: Needs doc
 */
int main(void) __attribute__((weak));
int main(void) {
    bool suspended = false;
#if USB_COUNT_SOF
    uint16_t last_timer = timer_read();
#endif

#ifdef CLKPR
    // avoid unintentional changes of clock frequency in devices that have a
    // clock prescaler
    CLKPR = 0x80, CLKPR = 0;
#endif
#ifndef NO_UART
    uart_init(UART_BAUD_RATE);
#endif
    keyboard_setup();

    host_set_driver(vusb_driver());
    setup_usb();
    sei();

    wait_ms(50);

    keyboard_init();
#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    debug("main loop\n");
    while (1) {
#if USB_COUNT_SOF
        if (usbSofCount != 0) {
            suspended   = false;
            usbSofCount = 0;
            last_timer  = timer_read();
#    ifdef SLEEP_LED_ENABLE
            sleep_led_disable();
#    endif
        } else {
            // Suspend when no SOF in 3ms-10ms(7.1.7.4 Suspending of USB1.1)
            if (timer_elapsed(last_timer) > 5) {
                suspended = true;
#    ifdef SLEEP_LED_ENABLE
                sleep_led_enable();
#    endif
                /*
                                uart_putchar('S');
                                _delay_ms(1);
                                cli();
                                set_sleep_mode(SLEEP_MODE_PWR_DOWN);
                                sleep_enable();
                                sleep_bod_disable();
                                sei();
                                sleep_cpu();
                                sleep_disable();
                                _delay_ms(10);
                                uart_putchar('W');
                */
            }
        }
#endif
        if (!suspended) {
            usbPoll();

            // TODO: configuration process is inconsistent. it sometime fails.
            // To prevent failing to configure NOT scan keyboard during configuration
            if (usbConfiguration && usbInterruptIsReady()) {
                keyboard_task();
            }
            vusb_transfer_keyboard();

#ifdef RAW_ENABLE
            usbPoll();

            if (usbConfiguration && usbInterruptIsReady3()) {
                raw_hid_task();
            }
#endif
#ifdef CONSOLE_ENABLE
            usbPoll();

            if (usbConfiguration && usbInterruptIsReady3()) {
                console_task();
            }
#endif
        } else if (suspend_wakeup_condition()) {
            usb_remote_wakeup();
        }
    }
}
