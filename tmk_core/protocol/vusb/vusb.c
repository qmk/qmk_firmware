/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <stdint.h>
#include "usbdrv.h"
#include "usbconfig.h"
#include "host.h"
#include "report.h"
#include "print.h"
#include "debug.h"
#include "host_driver.h"
#include "vusb.h"
#include "bootloader.h"
#include <util/delay.h>

static uint8_t vusb_keyboard_leds = 0;
static uint8_t vusb_idle_rate     = 0;

/* Keyboard report send buffer */
#define KBUF_SIZE 16
static report_keyboard_t kbuf[KBUF_SIZE];
static uint8_t           kbuf_head = 0;
static uint8_t           kbuf_tail = 0;

typedef struct {
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keycode[6];
} keyboard_report_t;

static keyboard_report_t keyboard_report;  // sent to PC

#define VUSB_TRANSFER_KEYBOARD_MAX_TRIES 10

/* transfer keyboard report from buffer */
void vusb_transfer_keyboard(void) {
    for (int i = 0; i < VUSB_TRANSFER_KEYBOARD_MAX_TRIES; i++) {
        if (usbInterruptIsReady()) {
            if (kbuf_head != kbuf_tail) {
                usbSetInterrupt((void *)&kbuf[kbuf_tail], sizeof(report_keyboard_t));
                kbuf_tail = (kbuf_tail + 1) % KBUF_SIZE;
                if (debug_keyboard) {
                    print("V-USB: kbuf[");
                    pdec(kbuf_tail);
                    print("->");
                    pdec(kbuf_head);
                    print("](");
                    phex((kbuf_head < kbuf_tail) ? (KBUF_SIZE - kbuf_tail + kbuf_head) : (kbuf_head - kbuf_tail));
                    print(")\n");
                }
            }
            break;
        }
        usbPoll();
        _delay_ms(1);
    }
}

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);

static host_driver_t driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};

host_driver_t *vusb_driver(void) { return &driver; }

static uint8_t keyboard_leds(void) { return vusb_keyboard_leds; }

static void send_keyboard(report_keyboard_t *report) {
    uint8_t next = (kbuf_head + 1) % KBUF_SIZE;
    if (next != kbuf_tail) {
        kbuf[kbuf_head] = *report;
        kbuf_head       = next;
    } else {
        debug("kbuf: full\n");
    }

    // NOTE: send key strokes of Macro
    usbPoll();
    vusb_transfer_keyboard();
}

typedef struct {
    uint8_t        report_id;
    report_mouse_t report;
} __attribute__((packed)) vusb_mouse_report_t;

static void send_mouse(report_mouse_t *report) {
    vusb_mouse_report_t r = {.report_id = REPORT_ID_MOUSE, .report = *report};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&r, sizeof(vusb_mouse_report_t));
    }
}

static void send_extra(uint8_t report_id, uint16_t data) {
    static uint8_t  last_id   = 0;
    static uint16_t last_data = 0;
    if ((report_id == last_id) && (data == last_data)) return;
    last_id   = report_id;
    last_data = data;

    report_extra_t report = {.report_id = report_id, .usage = data};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&report, sizeof(report));
    }
}

static void send_system(uint16_t data) { send_extra(REPORT_ID_SYSTEM, data); }

static void send_consumer(uint16_t data) { send_extra(REPORT_ID_CONSUMER, data); }

/*------------------------------------------------------------------*
 * Request from host                                                *
 *------------------------------------------------------------------*/
static struct {
    uint16_t len;
    enum { NONE, BOOTLOADER, SET_LED } kind;
} last_req;

usbMsgLen_t usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data;

    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) { /* class request type */
        if (rq->bRequest == USBRQ_HID_GET_REPORT) {
            debug("GET_REPORT:");
            /* we only have one report type, so don't look at wValue */
            usbMsgPtr = (void *)&keyboard_report;
            return sizeof(keyboard_report);
        } else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
            debug("GET_IDLE: ");
            // debug_hex(vusb_idle_rate);
            usbMsgPtr = &vusb_idle_rate;
            return 1;
        } else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
            vusb_idle_rate = rq->wValue.bytes[1];
            debug("SET_IDLE: ");
            debug_hex(vusb_idle_rate);
        } else if (rq->bRequest == USBRQ_HID_SET_REPORT) {
            debug("SET_REPORT: ");
            // Report Type: 0x02(Out)/ReportID: 0x00(none) && Interface: 0(keyboard)
            if (rq->wValue.word == 0x0200 && rq->wIndex.word == 0) {
                debug("SET_LED: ");
                last_req.kind = SET_LED;
                last_req.len  = rq->wLength.word;
#ifdef BOOTLOADER_SIZE
            } else if (rq->wValue.word == 0x0301) {
                last_req.kind = BOOTLOADER;
                last_req.len  = rq->wLength.word;
#endif
            }
            return USB_NO_MSG;  // to get data in usbFunctionWrite
        } else {
            debug("UNKNOWN:");
        }
    } else {
        debug("VENDOR:");
        /* no vendor specific requests implemented */
    }
    debug("\n");
    return 0; /* default for not implemented requests: return no data back to host */
}

uchar usbFunctionWrite(uchar *data, uchar len) {
    if (last_req.len == 0) {
        return -1;
    }
    switch (last_req.kind) {
        case SET_LED:
            debug("SET_LED: ");
            debug_hex(data[0]);
            debug("\n");
            vusb_keyboard_leds = data[0];
            last_req.len       = 0;
            return 1;
            break;
        case BOOTLOADER:
            usbDeviceDisconnect();
            bootloader_jump();
            return 1;
            break;
        case NONE:
        default:
            return -1;
            break;
    }
    return 1;
}

/*------------------------------------------------------------------*
 * Descriptors                                                      *
 *------------------------------------------------------------------*/

/*
 * Report Descriptor for keyboard
 *
 * from an example in HID spec appendix
 */
const PROGMEM uchar keyboard_hid_report[] = {
    0x05, 0x01,        // Usage Page (Generic Desktop),
    0x09, 0x06,        // Usage (Keyboard),
    0xA1, 0x01,        // Collection (Application),
    0x75, 0x01,        //   Report Size (1),
    0x95, 0x08,        //   Report Count (8),
    0x05, 0x07,        //   Usage Page (Key Codes),
    0x19, 0xE0,        //   Usage Minimum (224),
    0x29, 0xE7,        //   Usage Maximum (231),
    0x15, 0x00,        //   Logical Minimum (0),
    0x25, 0x01,        //   Logical Maximum (1),
    0x81, 0x02,        //   Input (Data, Variable, Absolute), ;Modifier byte
    0x95, 0x01,        //   Report Count (1),
    0x75, 0x08,        //   Report Size (8),
    0x81, 0x03,        //   Input (Constant),                 ;Reserved byte
    0x95, 0x05,        //   Report Count (5),
    0x75, 0x01,        //   Report Size (1),
    0x05, 0x08,        //   Usage Page (LEDs),
    0x19, 0x01,        //   Usage Minimum (1),
    0x29, 0x05,        //   Usage Maximum (5),
    0x91, 0x02,        //   Output (Data, Variable, Absolute), ;LED report
    0x95, 0x01,        //   Report Count (1),
    0x75, 0x03,        //   Report Size (3),
    0x91, 0x03,        //   Output (Constant),                 ;LED report padding
    0x95, 0x06,        //   Report Count (6),
    0x75, 0x08,        //   Report Size (8),
    0x15, 0x00,        //   Logical Minimum (0),
    0x26, 0xFF, 0x00,  //   Logical Maximum(255),
    0x05, 0x07,        //   Usage Page (Key Codes),
    0x19, 0x00,        //   Usage Minimum (0),
    0x29, 0xFF,        //   Usage Maximum (255),
    0x81, 0x00,        //   Input (Data, Array),
    0xc0               // End Collection
};

/*
 * Report Descriptor for mouse
 *
 * Mouse Protocol 1, HID 1.11 spec, Appendix B, page 59-60, with wheel extension
 * http://www.microchip.com/forums/tm.aspx?high=&m=391435&mpage=1#391521
 * http://www.keil.com/forum/15671/
 * http://www.microsoft.com/whdc/device/input/wheel.mspx
 */
const PROGMEM uchar mouse_hid_report[] = {
    /* mouse */
    0x05, 0x01,             // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,             // USAGE (Mouse)
    0xa1, 0x01,             // COLLECTION (Application)
    0x85, REPORT_ID_MOUSE,  //   REPORT_ID (1)
    0x09, 0x01,             //   USAGE (Pointer)
    0xa1, 0x00,             //   COLLECTION (Physical)
                            // ----------------------------  Buttons
    0x05, 0x09,             //     USAGE_PAGE (Button)
    0x19, 0x01,             //     USAGE_MINIMUM (Button 1)
    0x29, 0x05,             //     USAGE_MAXIMUM (Button 5)
    0x15, 0x00,             //     LOGICAL_MINIMUM (0)
    0x25, 0x01,             //     LOGICAL_MAXIMUM (1)
    0x75, 0x01,             //     REPORT_SIZE (1)
    0x95, 0x05,             //     REPORT_COUNT (5)
    0x81, 0x02,             //     INPUT (Data,Var,Abs)
    0x75, 0x03,             //     REPORT_SIZE (3)
    0x95, 0x01,             //     REPORT_COUNT (1)
    0x81, 0x03,             //     INPUT (Cnst,Var,Abs)
                            // ----------------------------  X,Y position
    0x05, 0x01,             //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,             //     USAGE (X)
    0x09, 0x31,             //     USAGE (Y)
    0x15, 0x81,             //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,             //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,             //     REPORT_SIZE (8)
    0x95, 0x02,             //     REPORT_COUNT (2)
    0x81, 0x06,             //     INPUT (Data,Var,Rel)
                            // ----------------------------  Vertical wheel
    0x09, 0x38,             //     USAGE (Wheel)
    0x15, 0x81,             //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,             //     LOGICAL_MAXIMUM (127)
    0x35, 0x00,             //     PHYSICAL_MINIMUM (0)        - reset physical
    0x45, 0x00,             //     PHYSICAL_MAXIMUM (0)
    0x75, 0x08,             //     REPORT_SIZE (8)
    0x95, 0x01,             //     REPORT_COUNT (1)
    0x81, 0x06,             //     INPUT (Data,Var,Rel)
                            // ----------------------------  Horizontal wheel
    0x05, 0x0c,             //     USAGE_PAGE (Consumer Devices)
    0x0a, 0x38, 0x02,       //     USAGE (AC Pan)
    0x15, 0x81,             //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,             //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,             //     REPORT_SIZE (8)
    0x95, 0x01,             //     REPORT_COUNT (1)
    0x81, 0x06,             //     INPUT (Data,Var,Rel)
    0xc0,                   //   END_COLLECTION
    0xc0,                   // END_COLLECTION
    /* system control */
    0x05, 0x01,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x80,              // USAGE (System Control)
    0xa1, 0x01,              // COLLECTION (Application)
    0x85, REPORT_ID_SYSTEM,  //   REPORT_ID (2)
    0x15, 0x01,              //   LOGICAL_MINIMUM (0x1)
    0x26, 0xb7, 0x00,        //   LOGICAL_MAXIMUM (0xb7)
    0x19, 0x01,              //   USAGE_MINIMUM (0x1)
    0x29, 0xb7,              //   USAGE_MAXIMUM (0xb7)
    0x75, 0x10,              //   REPORT_SIZE (16)
    0x95, 0x01,              //   REPORT_COUNT (1)
    0x81, 0x00,              //   INPUT (Data,Array,Abs)
    0xc0,                    // END_COLLECTION
    /* consumer */
    0x05, 0x0c,                // USAGE_PAGE (Consumer Devices)
    0x09, 0x01,                // USAGE (Consumer Control)
    0xa1, 0x01,                // COLLECTION (Application)
    0x85, REPORT_ID_CONSUMER,  //   REPORT_ID (3)
    0x15, 0x01,                //   LOGICAL_MINIMUM (0x1)
    0x26, 0x9c, 0x02,          //   LOGICAL_MAXIMUM (0x29c)
    0x19, 0x01,                //   USAGE_MINIMUM (0x1)
    0x2a, 0x9c, 0x02,          //   USAGE_MAXIMUM (0x29c)
    0x75, 0x10,                //   REPORT_SIZE (16)
    0x95, 0x01,                //   REPORT_COUNT (1)
    0x81, 0x00,                //   INPUT (Data,Array,Abs)
    0xc0,                      // END_COLLECTION
};

#ifndef USB_MAX_POWER_CONSUMPTION
#    define USB_MAX_POWER_CONSUMPTION 500
#endif

// TODO: change this to 10ms to match LUFA
#ifndef USB_POLLING_INTERVAL_MS
#    define USB_POLLING_INTERVAL_MS 1
#endif

/*
 * Descriptor for compite device: Keyboard + Mouse
 *
 * contains: device, interface, HID and endpoint descriptors
 */
#if USB_CFG_DESCR_PROPS_CONFIGURATION
const PROGMEM char usbDescriptorConfiguration[] = {
    /* USB configuration descriptor */
    9,               /* sizeof(usbDescriptorConfiguration): length of descriptor in bytes */
    USBDESCR_CONFIG, /* descriptor type */
    9 + (9 + 9 + 7) + (9 + 9 + 7), 0,
    // 18 + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT3 + 9, 0,
    /* total length of data returned (including inlined descriptors) */
    2, /* number of interfaces in this configuration */
    1, /* index of this configuration */
    0, /* configuration name string index */
#    if USB_CFG_IS_SELF_POWERED
    (1 << 7) | USBATTR_SELFPOWER, /* attributes */
#    else
    (1 << 7), /* attributes */
#    endif
    USB_MAX_POWER_CONSUMPTION / 2, /* max USB current in 2mA units */

    /*
     * Keyboard interface
     */
    /* Interface descriptor */
    9,                                                                                  /* sizeof(usbDescrInterface): length of descriptor in bytes */
    USBDESCR_INTERFACE,                                                                 /* descriptor type */
    0,                                                                                  /* index of this interface */
    0,                                                                                  /* alternate setting for this interface */
    USB_CFG_HAVE_INTRIN_ENDPOINT,                                                       /* endpoints excl 0: number of endpoint descriptors to follow */
    USB_CFG_INTERFACE_CLASS, USB_CFG_INTERFACE_SUBCLASS, USB_CFG_INTERFACE_PROTOCOL, 0, /* string index for interface */
    /* HID descriptor */
    9,                              /* sizeof(usbDescrHID): length of descriptor in bytes */
    USBDESCR_HID,                   /* descriptor type: HID */
    0x01, 0x01,                     /* BCD representation of HID version */
    0x00,                           /* target country code */
    0x01,                           /* number of HID Report (or other HID class) Descriptor infos to follow */
    0x22,                           /* descriptor type: report */
    sizeof(keyboard_hid_report), 0, /* total length of report descriptor */
/* Endpoint descriptor */
#    if USB_CFG_HAVE_INTRIN_ENDPOINT /* endpoint descriptor for endpoint 1 */
    7,                               /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,               /* descriptor type = endpoint */
    (char)0x81,                      /* IN endpoint number 1 */
    0x03,                            /* attrib: Interrupt endpoint */
    8, 0,                            /* maximum packet size */
    USB_POLLING_INTERVAL_MS,         /* in ms */
#    endif

    /*
     * Mouse interface
     */
    /* Interface descriptor */
    9,                             /* sizeof(usbDescrInterface): length of descriptor in bytes */
    USBDESCR_INTERFACE,            /* descriptor type */
    1,                             /* index of this interface */
    0,                             /* alternate setting for this interface */
    USB_CFG_HAVE_INTRIN_ENDPOINT3, /* endpoints excl 0: number of endpoint descriptors to follow */
    0x03,                          /* CLASS: HID */
    0,                             /* SUBCLASS: none */
    0,                             /* PROTOCOL: none */
    0,                             /* string index for interface */
    /* HID descriptor */
    9,                                /* sizeof(usbDescrHID): length of descriptor in bytes */
    USBDESCR_HID,                     /* descriptor type: HID */
    0x01, 0x01,                       /* BCD representation of HID version */
    0x00,                             /* target country code */
    0x01,                             /* number of HID Report (or other HID class) Descriptor infos to follow */
    0x22,                             /* descriptor type: report */
    sizeof(mouse_hid_report), 0,      /* total length of report descriptor */
#    if USB_CFG_HAVE_INTRIN_ENDPOINT3 /* endpoint descriptor for endpoint 3 */
    /* Endpoint descriptor */
    7,                                 /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,                 /* descriptor type = endpoint */
    (char)(0x80 | USB_CFG_EP3_NUMBER), /* IN endpoint number 3 */
    0x03,                              /* attrib: Interrupt endpoint */
    8, 0,                              /* maximum packet size */
    USB_POLLING_INTERVAL_MS,           /* in ms */
#    endif
};
#endif

USB_PUBLIC usbMsgLen_t usbFunctionDescriptor(struct usbRequest *rq) {
    usbMsgLen_t len = 0;

    /*
        debug("usbFunctionDescriptor: ");
        debug_hex(rq->bmRequestType); debug(" ");
        debug_hex(rq->bRequest); debug(" ");
        debug_hex16(rq->wValue.word); debug(" ");
        debug_hex16(rq->wIndex.word); debug(" ");
        debug_hex16(rq->wLength.word); debug("\n");
    */
    switch (rq->wValue.bytes[1]) {
#if USB_CFG_DESCR_PROPS_CONFIGURATION
        case USBDESCR_CONFIG:
            usbMsgPtr = (unsigned char *)usbDescriptorConfiguration;
            len       = sizeof(usbDescriptorConfiguration);
            break;
#endif
        case USBDESCR_HID:
            switch (rq->wValue.bytes[0]) {
                case 0:
                    usbMsgPtr = (unsigned char *)(usbDescriptorConfiguration + 9 + 9);
                    len       = 9;
                    break;
                case 1:
                    usbMsgPtr = (unsigned char *)(usbDescriptorConfiguration + 9 + (9 + 9 + 7) + 9);
                    len       = 9;
                    break;
            }
            break;
        case USBDESCR_HID_REPORT:
            /* interface index */
            switch (rq->wIndex.word) {
                case 0:
                    usbMsgPtr = (unsigned char *)keyboard_hid_report;
                    len       = sizeof(keyboard_hid_report);
                    break;
                case 1:
                    usbMsgPtr = (unsigned char *)mouse_hid_report;
                    len       = sizeof(mouse_hid_report);
                    break;
            }
            break;
    }
    // debug("desc len: "); debug_hex(len); debug("\n");
    return len;
}
