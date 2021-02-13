#include <hal.h>
#include "usb_util.h"

bool usb_active_connection(void) { return usbGetDriverStateI(&USBD1) == USB_ACTIVE; }

void usb_disable(void) { usbStop(&USBD1); }
