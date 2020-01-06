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

#include "ch.h"
#include "hal.h"

#include "usb_main.h"

/* TMK includes */
#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "led.h"
#include "sendchar.h"
#include "debug.h"
#include "printf.h"
#include "rgblight_reconfig.h"

#if (defined(RGB_MIDI) || defined(RGBLIGHT_ANIMATIONS)) && defined(RGBLIGHT_ENABLE)
#    include "rgblight.h"
#endif
#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#endif
#ifdef SERIAL_LINK_ENABLE
#    include "serial_link/system/serial_link.h"
#endif
#ifdef VISUALIZER_ENABLE
#    include "visualizer/visualizer.h"
#endif
#ifdef MIDI_ENABLE
#    include "qmk_midi.h"
#endif
#ifdef STM32_EEPROM_ENABLE
#    include "eeprom_stm32.h"
#endif
#include "suspend.h"
#include "wait.h"

/* -------------------------
 *   TMK host driver defs
 * -------------------------
 */

/* declarations */
uint8_t keyboard_leds(void);
void    send_keyboard(report_keyboard_t *report);
void    send_mouse(report_mouse_t *report);
void    send_system(uint16_t data);
void    send_consumer(uint16_t data);

/* host struct */
host_driver_t chibios_driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};

#ifdef VIRTSER_ENABLE
void virtser_task(void);
#endif

#ifdef RAW_ENABLE
void raw_hid_task(void);
#endif

#ifdef CONSOLE_ENABLE
void console_task(void);
#endif

#ifdef WEBUSB_ENABLE
void webusb_task(void);
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

/* Main thread
 */
int main(void) {
    /* ChibiOS/RT init */
    halInit();
    chSysInit();

#ifdef STM32_EEPROM_ENABLE
    EEPROM_Init();
#endif

    // TESTING
    // chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    keyboard_setup();

    /* Init USB */
    init_usb_driver(&USB_DRIVER);

    /* init printf */
    init_printf(NULL, sendchar_pf);

#ifdef MIDI_ENABLE
    setup_midi();
#endif

#ifdef SERIAL_LINK_ENABLE
    init_serial_link();
#endif

#ifdef VISUALIZER_ENABLE
    visualizer_init();
#endif

    host_driver_t *driver = NULL;

    /* Wait until the USB or serial link is active */
    while (true) {
#if defined(WAIT_FOR_USB) || defined(SERIAL_LINK_ENABLE)
        if (USB_DRIVER.state == USB_ACTIVE) {
            driver = &chibios_driver;
            break;
        }
#else
        driver = &chibios_driver;
        break;
#endif
#ifdef SERIAL_LINK_ENABLE
        if (is_serial_link_connected()) {
            driver = get_serial_link_driver();
            break;
        }
        serial_link_update();
#endif
        wait_ms(50);
    }

    /* Do need to wait here!
     * Otherwise the next print might start a transfer on console EP
     * before the USB is completely ready, which sometimes causes
     * HardFaults.
     */
    wait_ms(50);

    print("USB configured.\n");

    /* init TMK modules */
    keyboard_init();
    host_set_driver(driver);

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    print("Keyboard start.\n");

    /* Main loop */
    while (true) {
#if !defined(NO_USB_STARTUP_CHECK)
        if (USB_DRIVER.state == USB_SUSPENDED) {
            print("[s]");
#    ifdef VISUALIZER_ENABLE
            visualizer_suspend();
#    endif
            while (USB_DRIVER.state == USB_SUSPENDED) {
                /* Do this in the suspended state */
#    ifdef SERIAL_LINK_ENABLE
                serial_link_update();
#    endif
                suspend_power_down();  // on AVR this deep sleeps for 15ms
                /* Remote wakeup */
                if (suspend_wakeup_condition()) {
                    usbWakeupHost(&USB_DRIVER);
                }
            }
            /* Woken up */
            // variables has been already cleared by the wakeup hook
            send_keyboard_report();
#    ifdef MOUSEKEY_ENABLE
            mousekey_send();
#    endif /* MOUSEKEY_ENABLE */

#    ifdef VISUALIZER_ENABLE
            visualizer_resume();
#    endif
        }
#endif

        keyboard_task();
#ifdef CONSOLE_ENABLE
        console_task();
#endif
#ifdef VIRTSER_ENABLE
        virtser_task();
#endif
#ifdef RAW_ENABLE
        raw_hid_task();
#endif
#ifdef WEBUSB_ENABLE
        webusb_task();
#endif

#if defined(RGBLIGHT_ANIMATIONS) && defined(RGBLIGHT_ENABLE)
        rgblight_task();
#endif
    }
}
