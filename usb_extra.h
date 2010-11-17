#ifndef USB_EXTRA_H
#define  USB_EXTRA_H 1

#include <stdint.h>
#include "usb.h"


#define EXTRA_INTERFACE		3
#define EXTRA_ENDPOINT		4
#define EXTRA_SIZE		2
#define EXTRA_BUFFER		EP_DOUBLE_BUFFER

#define AUDIO_VOL_UP		(1<<0)
#define AUDIO_VOL_DOWN		(1<<1)
#define AUDIO_MUTE		(1<<2)


int8_t usb_extra_send(uint8_t bits);

#endif
