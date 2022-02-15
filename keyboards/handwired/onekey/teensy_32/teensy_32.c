#include QMK_KEYBOARD_H

void restart_usb_driver(USBDriver *usbp) {
    // Do nothing. Restarting the USB driver on these boards breaks it.
}
