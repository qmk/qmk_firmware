#include <usbdrv/usbdrv.h>
#include "usb_util.h"

bool usb_active_connection(void) {
    usbPoll();
    return usbConfiguration;
}

void usb_disable(void) { usbDeviceDisconnect(); }
