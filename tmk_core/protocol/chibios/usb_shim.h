#pragma once

void usbStartTransmitIGuard(USBDriver *usbp, usbep_t ep, const uint8_t *buf, size_t n);
