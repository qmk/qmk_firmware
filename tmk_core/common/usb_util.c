#include "usb_utils.h"
#include "wait.h"

__attribute__ ((weak)) bool usb_active_connection(void) { return true; }
__attribute__ ((weak)) void usb_disable(void) {}
__attribute__ ((weak)) bool usb_vbus_state(void) {
#ifdef USB_VBUS_PIN
    setPinInput(USB_VBUS_PIN);
    wait_us(5);
    return readPin(USB_VBUS_PIN);
#else
    return true;
#endif
}
