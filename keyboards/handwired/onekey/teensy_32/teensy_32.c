#include QMK_KEYBOARD_H

void restart_usb_driver(USBDriver *usbp) {
    // Do nothing. Restarting the USB driver on these boards breaks it.
}

#define WDOG_TMROUTL *(volatile uint16_t *)0x40052012

void early_hardware_init_pre(void) {
    // This is a dirty hack and should only be used as a temporary fix until this
    // is upstreamed.
    while (WDOG_TMROUTL < 2)
        ;  // Must wait for WDOG timer if already running, before jumping
}
