#ifndef USB_EXTRA_H
#define  USB_EXTRA_H 1
/*
 * Enhanced keyboard features for Windows:
 * Audio control and System control
 *
 * http://www.microsoft.com/whdc/archive/w2kbd.mspx
 */

#include <stdint.h>
#include "usb.h"


#define EXTRA_INTERFACE		3
#define EXTRA_ENDPOINT		4
#define EXTRA_SIZE		8
#define EXTRA_BUFFER		EP_DOUBLE_BUFFER


int8_t usb_extra_consumer_send(uint16_t bits);
int8_t usb_extra_system_send(uint16_t bits);

#endif
