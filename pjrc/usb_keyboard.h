#ifndef USB_KEYBOARD_H
#define  USB_KEYBOARD_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb.h"


#define KBD_INTERFACE		0
#define KBD_ENDPOINT		1
#define KBD_SIZE		8
#define KBD_BUFFER		EP_DOUBLE_BUFFER
#define KBD_REPORT_KEYS		(KBD_SIZE - 2)

// secondary keyboard
#ifdef USB_NKRO_ENABLE
#define KBD2_INTERFACE		4
#define KBD2_ENDPOINT		5
#define KBD2_SIZE		16
#define KBD2_BUFFER		EP_DOUBLE_BUFFER
#define KBD2_REPORT_KEYS	(KBD2_SIZE - 1)
#endif

#if defined(KBD2_REPORT_KEYS) && KBD2_REPORT_KEYS > KBD_REPORT_KEYS
#define KEYS_MAX KBD2_REPORT_KEYS
#else
#define KEYS_MAX KBD_REPORT_KEYS
#endif


typedef struct report {
    uint8_t keys[KEYS_MAX];
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
extern bool usb_keyboard_nkro;


int8_t usb_keyboard_send(void);
int8_t usb_keyboard_send_report(usb_keyboard_report_t *report);

void usb_keyboard_swap_report(void);

void usb_keyboard_clear_report(void);
void usb_keyboard_clear_keys(void);
void usb_keyboard_clear_mods(void);

void usb_keyboard_set_keys(uint8_t *keys);
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

uint8_t usb_keyboard_get_key(void);

void usb_keyboard_print_report(usb_keyboard_report_t *report);

#endif
