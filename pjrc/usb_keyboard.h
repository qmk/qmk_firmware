#ifndef USB_KEYBOARD_H
#define  USB_KEYBOARD_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb.h"
#include "host.h"


extern uint8_t usb_keyboard_protocol;
extern uint8_t usb_keyboard_idle_config;
extern uint8_t usb_keyboard_idle_count;
extern volatile uint8_t usb_keyboard_leds;


int8_t usb_keyboard_send_report(report_keyboard_t *report);
void usb_keyboard_print_report(report_keyboard_t *report);

#endif
