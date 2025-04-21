/*
 * (c) 2015 flabberast <s3+flabbergast@sdfeu.org>
 *
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */

#include <ch.h>
#include <hal.h>

#include "usb_main.h"

/* TMK includes */
#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "action_util.h"
#include "usb_device_state.h"
#include "mousekey.h"
#include "led.h"
#include "sendchar.h"
#include "debug.h"
#include "print.h"

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
// Change this to be TRUE once we've migrated keyboards to the new init system
// Remember to change docs/platformdev_chibios_earlyinit.md as well.
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP FALSE
#endif

#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#endif
#ifdef MIDI_ENABLE
#    include "qmk_midi.h"
#endif
#include "suspend.h"
#include "wait.h"

#define USB_GETSTATUS_REMOTE_WAKEUP_ENABLED (2U)

#ifdef WAIT_FOR_USB
// TODO: Remove backwards compatibility with old define
#    define USB_WAIT_FOR_ENUMERATION
#endif

/* -------------------------
 *   TMK host driver defs
 * -------------------------
 */

/* declarations */
extern void send_keyboard(report_keyboard_t *report);
extern void send_nkro(report_nkro_t *report);
extern void send_mouse(report_mouse_t *report);
extern void send_extra(report_extra_t *report);
#ifdef JOYSTICK_ENABLE
extern void send_joystick(report_joystick_t *report);
#endif // JOYSTICK_ENABLE
#ifdef DIGITIZER_ENABLE
extern void send_digitizer(report_digitizer_t *report);
#endif // DIGITIZER_ENABLE
#ifdef PROGRAMMABLE_BUTTON_ENABLE
extern void send_programmable_button(report_programmable_button_t *report);
#endif // PROGRAMMABLE_BUTTON_ENABLE
#ifdef CONSOLE_ENABLE
extern int8_t send_console(uint8_t c);
#endif // CONSOLE_ENABLE
#ifdef VIRTSER_ENABLE
extern void send_virtser(uint8_t c);
#endif // VIRTSER_ENABLE
#ifdef RAW_ENABLE
extern void send_raw_hid(uint8_t *data, uint8_t length);
#endif // RAW_ENABLE

/* host struct */
host_driver_t chibios_driver = {
    .has_init_executed = false,
    .init              = NULL,
    .connect           = NULL,
    .disconnect        = NULL,
    .is_connected      = NULL,
    .keyboard_leds     = usb_device_state_get_leds,
    .send_keyboard     = send_keyboard,
    .send_nkro         = send_nkro,
    .send_mouse        = send_mouse,
    .send_extra        = send_extra,
#ifdef JOYSTICK_ENABLE
    .send_joystick = send_joystick,
#endif // JOYSTICK_ENABLE
#ifdef DIGITIZER_ENABLE
    .send_digitizer = send_digitizer,
#endif // DIGITIZER_ENABLE
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    .send_programmable_button = send_programmable_button,
#endif // PROGRAMMABLE_BUTTON_ENABLE
#ifdef CONSOLE_ENABLE
    .send_console = send_console,
#endif // CONSOLE_ENABLE
#ifdef VIRTSER_ENABLE
    .send_virtser = send_virtser,
#endif // VIRTSER_ENABLE
#ifdef RAW_ENABLE
    .send_raw_hid = send_raw_hid,
#endif // RAW_ENABLE
};

host_driver_t *host_usb_driver(void) {
    return &chibios_driver;
}

#ifdef VIRTSER_ENABLE
void virtser_task(void);
#endif

/* TESTING
 * Amber LED blinker thread, times are in milliseconds.
 */
/* set this variable to non-zero anywhere to blink once */
// static THD_WORKING_AREA(waThread1, 128);
// static THD_FUNCTION(Thread1, arg) {

//   (void)arg;
//   chRegSetThreadName("blinker");
//   while (true) {
//     systime_t time;

//     time = USB_DRIVER.state == USB_ACTIVE ? 250 : 500;
//     palClearLine(LINE_CAPS_LOCK);
//     chSysPolledDelayX(MS2RTC(STM32_HCLK, time));
//     palSetLine(LINE_CAPS_LOCK);
//     chSysPolledDelayX(MS2RTC(STM32_HCLK, time));
//   }
// }

/* Early initialisation
 */
__attribute__((weak)) void early_hardware_init_pre(void) {
#if EARLY_INIT_PERFORM_BOOTLOADER_JUMP
    void enter_bootloader_mode_if_requested(void);
    enter_bootloader_mode_if_requested();
#endif // EARLY_INIT_PERFORM_BOOTLOADER_JUMP
}

__attribute__((weak)) void early_hardware_init_post(void) {}

__attribute__((weak)) void board_init(void) {}

// This overrides what's normally in ChibiOS board definitions
void __early_init(void) {
    early_hardware_init_pre();

    // This is the renamed equivalent of __early_init in the board.c file
    void __chibios_override___early_init(void);
    __chibios_override___early_init();

    early_hardware_init_post();
}

// This overrides what's normally in ChibiOS board definitions
void boardInit(void) {
    // This is the renamed equivalent of boardInit in the board.c file
    void __chibios_override_boardInit(void);
    __chibios_override_boardInit();

    board_init();
}

void protocol_setup(void) {
    usb_device_state_init();

    // TESTING
    // chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
}

void protocol_pre_init(void) {
    /* Init USB */
    usb_event_queue_init();
    init_usb_driver(&USB_DRIVER);

#ifdef MIDI_ENABLE
    setup_midi();
#endif

    /* Wait until USB is active */
#if defined(USB_WAIT_FOR_ENUMERATION)
    while (true) {
        if (USB_DRIVER.state == USB_ACTIVE) {
            break;
        }
        wait_ms(50);
    }
#endif

    /* Do need to wait here!
     * Otherwise the next print might start a transfer on console EP
     * before the USB is completely ready, which sometimes causes
     * HardFaults.
     */
    wait_ms(50);

    print("USB configured.\n");
}

void protocol_post_init(void) {
    host_set_driver(host_usb_driver());
}

void protocol_pre_task(void) {
    usb_event_queue_task();

#if !defined(NO_USB_STARTUP_CHECK)
    if (USB_DRIVER.state == USB_SUSPENDED) {
        dprintln("suspending keyboard");
        while (USB_DRIVER.state == USB_SUSPENDED) {
            /* Do this in the suspended state */
            suspend_power_down(); // on AVR this deep sleeps for 15ms
            /* Remote wakeup */
            if (suspend_wakeup_condition() && (USB_DRIVER.status & USB_GETSTATUS_REMOTE_WAKEUP_ENABLED)) {
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
#endif
}

void protocol_post_task(void) {
#ifdef VIRTSER_ENABLE
    virtser_task();
#endif
    usb_idle_task();
}
