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
#include "led.h"
#include "sendchar.h"
#include "debug.h"
#ifdef SLEEP_LED_ENABLE
#include "sleep_led.h"
#endif
#include "suspend.h"


/* -------------------------
 *   TMK host driver defs
 * -------------------------
 */

host_driver_t chibios_driver = {
  keyboard_leds,
  send_keyboard,
  send_mouse,
  send_system,
  send_consumer
};

/* Main thread
 */
int main(void) {
  /* ChibiOS/RT init */
  halInit();
  chSysInit();

  palSetPad(GPIOC, GPIOC_LED_BLUE);
  chThdSleepMilliseconds(400);
  palClearPad(GPIOC, GPIOC_LED_BLUE);

  /* Init USB */
  init_usb_driver(&USB_DRIVER);

  /* init printf */
  init_printf(NULL,sendchar_pf);

  /* Wait until the USB is active */
  while(USB_DRIVER.state != USB_ACTIVE)
    chThdSleepMilliseconds(50);

  print("USB configured.\n");

  /* init TMK modules */
  keyboard_init();
  host_set_driver(&chibios_driver);

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

  print("Keyboard start.\n");

  /* Main loop */
  while(true) {
    /* TODO: check for suspended event */

    keyboard_task();
    chThdSleepMilliseconds(5);
  }
}
