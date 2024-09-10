// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "module.h"
#include "usb_main.h"
#include "transport.h"

#ifndef USB_POWER_DOWN_DELAY
#    define USB_POWER_DOWN_DELAY 3000
#endif

extern host_driver_t chibios_driver;
extern host_driver_t wireless_driver;

static transport_t transport = TRANSPORT_USB;

void wls_transport_enable(bool enable) __attribute__((weak));
void wls_transport_enable(bool enable) {

    if (enable) {
        if (host_get_driver() != &wireless_driver) {
            host_set_driver(&wireless_driver);
            keyboard_protocol = true; // default with true
        }
    } else {
        if (*md_getp_state() == MD_STATE_CONNECTED) {
            wireless_driver.send_keyboard(NULL);
            wireless_driver.send_nkro(NULL);
        }
    }
}

/* Control USB device connection and disconnection by
 * controlling the power supply of the USB DP pull-up resistor.
 * Overwrite these two functions. */
void usb_power_connect(void) __attribute__((weak));
void usb_power_connect(void) {}

void usb_power_disconnect(void) __attribute__((weak));
void usb_power_disconnect(void) {}

void usb_transport_enable(bool enable) __attribute__((weak));
void usb_transport_enable(bool enable) {

    if (enable) {
        if (host_get_driver() != &chibios_driver) {
            extern bool last_suspend_state;

            /* This flag is not set to 1 with probability after usb restart */
            last_suspend_state = true;
#if !defined(KEEP_USB_CONNECTION_IN_WIRELESS_MODE)
            usb_power_connect();
            restart_usb_driver(&USBD1);
#endif
            host_set_driver(&chibios_driver);
        }
    } else {
        if (USB_DRIVER.state == USB_ACTIVE) {
            chibios_driver.send_keyboard(NULL);
            chibios_driver.send_nkro(NULL);
        }

#if !defined(KEEP_USB_CONNECTION_IN_WIRELESS_MODE)
        usbStop(&USBD1);
        usbDisconnectBus(&USBD1);
        usb_power_disconnect();
#endif
    }
}

void set_transport(transport_t new_transport) {

    if (transport != new_transport) {
        transport = new_transport;

        switch (transport) {
            case TRANSPORT_USB: {
                usb_transport_enable(true);
                wls_transport_enable(false);
            } break;
            case TRANSPORT_WLS: {
                wls_transport_enable(true);
                usb_transport_enable(false);
            } break;
            default:
                break;
        }
    }
}

transport_t get_transport(void) {

    return transport;
}

void usb_remote_wakeup(void) {

#ifdef USB_REMOTE_USE_QMK
    if (USB_DRIVER.state == USB_SUSPENDED) {
        dprintln("suspending keyboard");
        while (USB_DRIVER.state == USB_SUSPENDED) {
            /* Do this in the suspended state */
            suspend_power_down(); // on AVR this deep sleeps for 15ms
            /* Remote wakeup */
            if ((USB_DRIVER.status & 2U) && suspend_wakeup_condition()) {
                usbWakeupHost(&USB_DRIVER);
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
        /* Woken up */
    }
#else
    static uint32_t suspend_timer = 0x00;

    if ((USB_DRIVER.state == USB_SUSPENDED)) {
        if (!suspend_timer) suspend_timer = sync_timer_read32();
        if (sync_timer_elapsed32(suspend_timer) >= USB_POWER_DOWN_DELAY) {
            suspend_timer = 0x00;
            suspend_power_down();
        }
    } else {
        suspend_timer = 0x00;
    }
#endif
}

#ifndef USB_REMOTE_USE_QMK
void usb_remote_host(void) {

    if (USB_DRIVER.state == USB_SUSPENDED) {
        if ((USB_DRIVER.status & 2U) && suspend_wakeup_condition()) {
            usbWakeupHost(&USB_DRIVER);
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
#    if !defined(USB_REMOTE_USE_QMK) && USB_POWER_DOWN_DELAY
        suspend_wakeup_init();
#    endif
    }
}

bool process_action_kb(keyrecord_t *record) {

    (void)record;
    if (get_transport() == TRANSPORT_USB){
        usb_remote_host();
    }

    return true;
}
#endif