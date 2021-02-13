#include <LUFA/Drivers/USB/USB.h>
#include "usb_util.h"
#include "wait.h"

bool usb_active_connection(void) { return USB_Device_IsAddressSet(); }

void usb_disable(void) {
    USB_Disable();
    USB_DeviceState = DEVICE_STATE_Unattached;
}

#if defined(OTGPADE)
bool usb_vbus_state(void) {
    USB_OTGPAD_On();  // enables VBUS pad
    wait_us(5);

    return USB_VBUS_GetStatus();  // checks state of VBUS
}
#endif
