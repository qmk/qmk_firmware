#ifndef USB_KEYBOARD_H
#define  USB_KEYBOARD_H 1

#include <stdint.h>
#include "usb.h"


#define KEYBOARD_INTERFACE	0
#define KEYBOARD_ENDPOINT	1
#define KEYBOARD_SIZE		8
#define KEYBOARD_BUFFER		EP_DOUBLE_BUFFER

// modifier bits
#define MOD_LCTRL   (1<<0)
#define MOD_LSHIFT  (1<<1)
#define MOD_LALT    (1<<2)
#define MOD_LGUI    (1<<3)
#define MOD_RCTRL   (1<<4)
#define MOD_RSHIFT  (1<<5)
#define MOD_RALT    (1<<6)
#define MOD_RGUI    (1<<7)


extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern uint8_t keyboard_protocol;
extern uint8_t keyboard_idle_config;
extern uint8_t keyboard_idle_count;
extern volatile uint8_t keyboard_leds;


int8_t usb_keyboard_press(uint8_t key, uint8_t modifier);
int8_t usb_keyboard_send(void);

#endif
