// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef NO_USB_STARTUP_CHECK

#    include <ch.h>
#    include <hal.h>

#    include "usb_main.h"

/* TMK includes */
#    include "action_util.h"
#    include "mousekey.h"
#    include "print.h"

#    include "suspend.h"
#    include "wait.h"

#    include "quantum.h"
#    include "common/bt_task.h"

// void restart_usb_driver(USBDriver *usbp) {}

void housekeeping_task_bt(void) {
    if (dev_info.devs == DEVS_USB) {
        if ((USB_DRIVER.state == USB_SUSPENDED) && (USB_DRIVER.saved_state == USB_ACTIVE)) {
            print("[s]");
            while (USB_DRIVER.state == USB_SUSPENDED) {
                // if (readPin(MM_CABLE_PIN)) break;
                /* Do this in the suspended state */
                suspend_power_down(); // on AVR this deep sleeps for 15ms
                /* Remote wakeup */
                if (suspend_wakeup_condition()) {
                    usbWakeupHost(&USB_DRIVER);
                    restart_usb_driver(&USB_DRIVER);
                }
            }
            /* Woken up */
            // variables has been already cleared by the wakeup hook
            send_keyboard_report();
#    ifdef MOUSEKEY_ENABLE
            mousekey_send();
#    endif /* MOUSEKEY_ENABLE */
        }
    }
}
#endif
