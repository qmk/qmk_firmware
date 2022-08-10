
#include "quantum.h"
#include "bluetooth.h"
#include "indicator.h"
#include "lpm.h"
#if defined(PROTOCOL_CHIBIOS)
#    include <usb_main.h>
#endif
#include "transport.h"

#ifndef REINIT_LED_DRIVER
#    define REINIT_LED_DRIVER 1
#endif

#ifdef NKRO_ENABLE
typedef struct {
    bool usb : 1;
    bool bluetooth : 1;
} nkro_t;
#endif

#if defined(PROTOCOL_CHIBIOS)
extern host_driver_t chibios_driver;
#endif
extern host_driver_t   bluetooth_driver;
extern keymap_config_t keymap_config;

static transport_t transport = TRANSPORT_USB;

#ifdef NKRO_ENABLE
nkro_t nkro = {false, false};
#endif

static void transport_changed(transport_t new_transport);

__attribute__((weak)) void bt_transport_enable(bool enable) {
    if (enable) {
        if (host_get_driver() != &bluetooth_driver) {
            host_set_driver(&bluetooth_driver);
            
            /* Disconnect and reconnect to sync the bluetooth state 
             * TODO: query bluetooth state to sync
             */
            bluetooth_disconnect();
            bluetooth_connect();
            // TODO: Clear USB report
        }
    } else {
        indicator_stop();

        if (bluetooth_get_state() == BLUETOOTH_CONNECTED) {
            report_keyboard_t empty_report = {0};
            bluetooth_driver.send_keyboard(&empty_report);
        }
    }
}

/* There is no dedicated pin for USB power on chip such as STM32L432, but USB power 
 * can be connected and disconnected via registers. 
 * Overwrite these two functions if such chip is used. */
__attribute__((weak)) void usb_power_connect(void) {}
__attribute__((weak)) void usb_power_disconnect(void) {}

__attribute__((weak)) void usb_transport_enable(bool enable) {
    if (enable) {
        if (host_get_driver() != &chibios_driver) {

#if !defined(KEEP_USB_CONNECTION_IN_BLUETOOTH_MODE)
            usb_power_connect();
            usb_start(&USBD1);
#endif
            host_set_driver(&chibios_driver);
        }
    } else {
        if (USB_DRIVER.state == USB_ACTIVE) {
            report_keyboard_t empty_report = {0};
            chibios_driver.send_keyboard(&empty_report);
        }

#if !defined(KEEP_USB_CONNECTION_IN_BLUETOOTH_MODE)
        usbStop(&USBD1);
        usbDisconnectBus(&USBD1);
        usb_power_disconnect();
#endif
    }
}

void set_transport(transport_t new_transport) {
    if (transport != new_transport) {
        transport = new_transport;

        clear_keyboard();

        switch (transport) {
            case TRANSPORT_USB:
                usb_transport_enable(true);
                bt_transport_enable(false);
                lpm_timer_stop();
#ifdef NKRO_ENABLE
#    if defined(BLUETOOTH_NKRO_ENABLE)
                nkro.bluetooth = keymap_config.nkro;
#    endif
                keymap_config.nkro = nkro.usb;
#endif
                break;

            case TRANSPORT_BLUETOOTH:
                bt_transport_enable(true);
                usb_transport_enable(false);
                lpm_timer_reset();
#if defined(NKRO_ENABLE)
                nkro.usb = keymap_config.nkro;
#    if defined(BLUETOOTH_NKRO_ENABLE)
                keymap_config.nkro = nkro.bluetooth;
#    else
                keymap_config.nkro = FALSE;
#    endif
#endif
                break;
            default:
                break;
        }

        transport_changed(transport);
    }
}

transport_t get_transport(void) {
    return transport;
}

/* Changing transport may cause bronw-out reset of led driver
 * withoug MCU reset, which lead backlight to not work,
 * reinit the led driver workgound this issue */
static void reinit_led_drvier(void) {
    /* Wait circuit to discharge for a while */
    systime_t start = chVTGetSystemTime();
    while (chTimeI2MS(chVTTimeElapsedSinceX(start)) < 100) {};

#ifdef LED_MATRIX_ENABLE
    led_matrix_init();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init();
#endif
}

void transport_changed(transport_t new_transport) {
#if (REINIT_LED_DRIVER)
    reinit_led_drvier();
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_DISABLE_TIMEOUT)
#    if (RGB_DISABLE_TIMEOUT > 0)
    rgb_matrix_disable_timeout_set(RGB_DISABLE_TIME_INFINITE);
    rgb_matrix_disable_time_reset();
#    endif
#endif
#if defined(LED_MATRIX_ENABLE) && defined(LED_DISABLE_TIMEOUT)
#    if (LED_DISABLE_TIMEOUT > 0)
    led_matrix_disable_timeout_set(LED_DISABLE_TIME_INFINITE);
    led_matrix_disable_time_reset();
#    endif
#endif
}

void usb_remote_wakeup(void) {
    if (USB_DRIVER.state == USB_SUSPENDED) {
        while (USB_DRIVER.state == USB_SUSPENDED) {
            /* Do this in the suspended state */
            suspend_power_down();  // on AVR this deep sleeps for 15ms
            /* Remote wakeup */
            if (suspend_wakeup_condition()) {
                usbWakeupHost(&USB_DRIVER);
                usb_wakeup(&USB_DRIVER);
            }
        }
        /* Woken up */
        // variables has been already cleared by the wakeup hook
        send_keyboard_report();
    }
}
