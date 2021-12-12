#pragma once

#include "usb/usbus.h"

#define NEXT_INTERFACE __COUNTER__

enum usb_interfaces {

    KEYBOARD_INTERFACE = NEXT_INTERFACE,

// It is important that the Raw HID interface is at a constant
// interface number, to support Linux/OSX platforms and chrome.hid
// If Raw HID is enabled, let it be always 1.
#ifdef RAW_ENABLE
    RAW_INTERFACE = NEXT_INTERFACE,
#endif

    SHARED_INTERFACE = NEXT_INTERFACE,

#ifdef CONSOLE_ENABLE
    CONSOLE_INTERFACE = NEXT_INTERFACE,
#endif

    TOTAL_INTERFACES = NEXT_INTERFACE
};

#define CONSOLE_EPSIZE 32
#define RAW_EPSIZE 32

extern usbus_t g_usbus;

typedef struct comp_hid_device_conf {
    uint8_t        id;
    const uint8_t *report_desc;      /**< report descriptor reference */
    size_t         report_desc_size; /**< report descriptor size */
    size_t         ep_size;
    uint8_t        interval;
} comp_hid_device_conf_t;

void usbdrv_init(comp_hid_device_conf_t *config, size_t len);
void usbdrv_write(uint8_t index, const void *buffer, size_t len);

uint8_t usbdrv_keyboard_leds(void);
