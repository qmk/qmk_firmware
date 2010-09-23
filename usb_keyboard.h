#ifndef USB_KEYBOARD_H
#define  USB_KEYBOARD_H 1

#include <stdint.h>
#include "usb_device.h"


#define KEYBOARD_INTERFACE	0
#define KEYBOARD_ENDPOINT	3
#define KEYBOARD_SIZE		8
#define KEYBOARD_BUFFER		EP_DOUBLE_BUFFER


extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern uint8_t keyboard_protocol;
extern uint8_t keyboard_idle_config;
extern uint8_t keyboard_idle_count;
extern volatile uint8_t keyboard_leds;


int8_t usb_keyboard_press(uint8_t key, uint8_t modifier);
int8_t usb_keyboard_send(void);

#endif
