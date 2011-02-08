#ifndef USB_MOUSE_H
#define  USB_MOUSE_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb.h"


#define MOUSE_INTERFACE		1
#define MOUSE_ENDPOINT		2
#define MOUSE_SIZE		8
#define MOUSE_BUFFER		EP_DOUBLE_BUFFER

#define MOUSE_BTN1 (1<<0)
#define MOUSE_BTN2 (1<<1)
#define MOUSE_BTN3 (1<<2)
#define MOUSE_BTN4 (1<<3)
#define MOUSE_BTN5 (1<<4)


extern uint8_t usb_mouse_protocol;


int8_t usb_mouse_send(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons);
void usb_mouse_print(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons);

#endif
