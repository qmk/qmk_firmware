#include <hal.h>

void restart_usb_driver(USBDriver *usbp) {
    // Do nothing. Restarting the USB driver on the Teensy 3.6 breaks it,
    // resulting in a keyboard which can wake up a PC from Suspend-to-RAM, but
    // does not actually produce any keypresses until you un-plug and re-plug.
}
