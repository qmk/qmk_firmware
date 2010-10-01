#ifndef USB_MOUSE_H
#define  USB_MOUSE_H 1

#include <stdint.h>
#include "usb.h"


#define MOUSE_INTERFACE		1
#define MOUSE_ENDPOINT		2
#define MOUSE_SIZE		8
#define MOUSE_BUFFER		EP_DOUBLE_BUFFER

extern uint8_t mouse_buttons;
extern uint8_t mouse_protocol;


int8_t usb_mouse_buttons(uint8_t left, uint8_t middle, uint8_t right);
int8_t usb_mouse_move(int8_t x, int8_t y, int8_t wheel, int8_t hwheel);

#endif
