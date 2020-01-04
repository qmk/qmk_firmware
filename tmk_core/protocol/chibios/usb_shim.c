#include <stddef.h>
#include "hal.h"
#include "usb_driver.h"

void usbStartTransmitIGuard(USBDriver *usbp, usbep_t ep, const uint8_t *buf, size_t n) {
  if (usbp->epc[ep] != NULL) {
    usbStartTransmitI(usbp, ep, buf, n);
  }
}

void usbStartReceiveIGuard(USBDriver *usbp, usbep_t ep, uint8_t *buf, size_t n) {
  if (usbp->epc[ep] != NULL) {
      usbStartReceiveI(usbp, ep, buf, n);
  }
}
