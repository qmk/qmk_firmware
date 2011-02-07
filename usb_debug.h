#ifndef USB_DEBUG_H
#define  USB_DEBUG_H 1

#include <stdint.h>
#include "usb.h"


#define DEBUG_INTERFACE		2
#define DEBUG_TX_ENDPOINT	3
#define DEBUG_TX_SIZE		32
#define DEBUG_TX_BUFFER		EP_DOUBLE_BUFFER


extern volatile uint8_t debug_flush_timer;


void usb_debug_flush_output(void);	// immediately transmit any buffered output

#endif
