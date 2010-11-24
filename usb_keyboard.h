#ifndef USB_KEYBOARD_H
#define  USB_KEYBOARD_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb.h"


#define KEYBOARD_INTERFACE	0
#define KEYBOARD_ENDPOINT	1
#define KEYBOARD_INTERFACE2	4
#define KEYBOARD_ENDPOINT2	5
#define KEYBOARD_SIZE		8
#define KEYBOARD_BUFFER		EP_DOUBLE_BUFFER

#define BIT_LCTRL   (1<<0)
#define BIT_LSHIFT  (1<<1)
#define BIT_LALT    (1<<2)
#define BIT_LGUI    (1<<3)
#define BIT_RCTRL   (1<<4)
#define BIT_RSHIFT  (1<<5)
#define BIT_RALT    (1<<6)
#define BIT_RGUI    (1<<7)
#define BIT_LCTL BIT_LCTRL
#define BIT_RCTL BIT_RCTRL
#define BIT_LSFT BIT_LSHIFT
#define BIT_RSFT BIT_RSHIFT

#define KEYBOARD_REPORT_MAX	12
typedef struct report {
    uint8_t keys[KEYBOARD_REPORT_MAX];
    uint8_t mods;
    bool is_sent;
} usb_keyboard_report_t;


#define usb_keyboard_keys usb_keyboard_report->keys
#define usb_keyboard_mods usb_keyboard_report->mods
#define usb_keyboard_keys_prev usb_keyboard_report_prev->keys
#define usb_keyboard_mods_prev usb_keyboard_report_prev->mods


extern usb_keyboard_report_t *usb_keyboard_report;
extern usb_keyboard_report_t *usb_keyboard_report_prev;
extern uint8_t usb_keyboard_protocol;
extern uint8_t usb_keyboard_idle_config;
extern uint8_t usb_keyboard_idle_count;
extern volatile uint8_t usb_keyboard_leds;


int8_t usb_keyboard_press(uint8_t key, uint8_t modifier);
int8_t usb_keyboard_send(void);
int8_t usb_keyboard_send_report(usb_keyboard_report_t *report);

void usb_keyboard_swap_report(void);

void usb_keyboard_clear_report(void);
void usb_keyboard_clear_keys(void);
void usb_keyboard_clear_mods(void);

void usb_keyboard_set_keys(uint8_t keys[6]);
void usb_keyboard_set_mods(uint8_t mods);

void usb_keyboard_add_code(uint8_t code);
void usb_keyboard_add_key(uint8_t code);
void usb_keyboard_add_mod(uint8_t code);

void usb_keyboard_del_code(uint8_t code);
void usb_keyboard_del_key(uint8_t code);
void usb_keyboard_del_mod(uint8_t code);

bool usb_keyboard_is_sent(void);
bool usb_keyboard_has_key(void);
bool usb_keyboard_has_mod(void);

void usb_keyboard_print_report(usb_keyboard_report_t *report);

#endif
