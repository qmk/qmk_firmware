/*
 * (c) 2015 flabberast <s3+flabbergast@sdfeu.org>
 *
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */

#include "ch.h"
#include "hal.h"

#include "usb_main.h"

#include "host.h"
#include "debug.h"
#include "suspend.h"
#ifdef SLEEP_LED_ENABLE
#include "sleep_led.h"
#include "led.h"
#endif

/* ---------------------------------------------------------
 *       Global interface variables and declarations
 * ---------------------------------------------------------
 */

uint8_t keyboard_idle __attribute__((aligned(2))) = 0;
uint8_t keyboard_protocol __attribute__((aligned(2))) = 1;
uint16_t keyboard_led_stats __attribute__((aligned(2))) = 0;
volatile uint16_t keyboard_idle_count = 0;
static virtual_timer_t keyboard_idle_timer;
static void keyboard_idle_timer_cb(void *arg);
#ifdef NKRO_ENABLE
extern bool keyboard_nkro;
#endif /* NKRO_ENABLE */

report_keyboard_t keyboard_report_sent = {{0}};
#ifdef MOUSE_ENABLE
report_mouse_t mouse_report_blank = {0};
#endif /* MOUSE_ENABLE */
#ifdef EXTRAKEY_ENABLE
uint8_t extra_report_blank[3] = {0};
#endif /* EXTRAKEY_ENABLE */

#ifdef CONSOLE_ENABLE
/* The emission buffers queue */
output_buffers_queue_t console_buf_queue;
static uint8_t console_queue_buffer[BQ_BUFFER_SIZE(CONSOLE_QUEUE_CAPACITY, CONSOLE_EPSIZE)];

static virtual_timer_t console_flush_timer;
void console_queue_onotify(io_buffers_queue_t *bqp);
static void console_flush_cb(void *arg);
#endif /* CONSOLE_ENABLE */

/* ---------------------------------------------------------
 *            Descriptors and USB driver objects
 * ---------------------------------------------------------
 */

/* HID specific constants */
#define USB_DESCRIPTOR_HID 0x21
#define USB_DESCRIPTOR_HID_REPORT 0x22
#define HID_GET_REPORT 0x01
#define HID_GET_IDLE 0x02
#define HID_GET_PROTOCOL 0x03
#define HID_SET_REPORT 0x09
#define HID_SET_IDLE 0x0A
#define HID_SET_PROTOCOL 0x0B

/* USB Device Descriptor */
static const uint8_t usb_device_descriptor_data[] = {
  USB_DESC_DEVICE(0x0200,      // bcdUSB (1.1)
                  0,           // bDeviceClass (defined in later in interface)
                  0,           // bDeviceSubClass
                  0,           // bDeviceProtocol
                  64,          // bMaxPacketSize (64 bytes) (the driver didn't work with 32)
                  VENDOR_ID,   // idVendor
                  PRODUCT_ID,  // idProduct
                  DEVICE_VER,      // bcdDevice
                  1,           // iManufacturer
                  2,           // iProduct
                  3,           // iSerialNumber
                  1)           // bNumConfigurations
};

/* Device Descriptor wrapper */
static const USBDescriptor usb_device_descriptor = {
  sizeof usb_device_descriptor_data,
  usb_device_descriptor_data
};

/*
 * HID Report Descriptor
 *
 * See "Device Class Definition for Human Interface Devices (HID)"
 * (http://www.usb.org/developers/hidpage/HID1_11.pdf) for the
 * detailed descrition of all the fields
 */

/* Keyboard Protocol 1, HID 1.11 spec, Appendix B, page 59-60 */
static const uint8_t keyboard_hid_report_desc_data[] = {
  0x05, 0x01,                // Usage Page (Generic Desktop),
  0x09, 0x06,                // Usage (Keyboard),
  0xA1, 0x01,                // Collection (Application),
  0x75, 0x01,                //   Report Size (1),
  0x95, 0x08,                //   Report Count (8),
  0x05, 0x07,                //   Usage Page (Key Codes),
  0x19, 0xE0,                //   Usage Minimum (224),
  0x29, 0xE7,                //   Usage Maximum (231),
  0x15, 0x00,                //   Logical Minimum (0),
  0x25, 0x01,                //   Logical Maximum (1),
  0x81, 0x02,                //   Input (Data, Variable, Absolute), ;Modifier byte
  0x95, 0x01,                //   Report Count (1),
  0x75, 0x08,                //   Report Size (8),
  0x81, 0x03,                //   Input (Constant),                 ;Reserved byte
  0x95, 0x05,                //   Report Count (5),
  0x75, 0x01,                //   Report Size (1),
  0x05, 0x08,                //   Usage Page (LEDs),
  0x19, 0x01,                //   Usage Minimum (1),
  0x29, 0x05,                //   Usage Maximum (5),
  0x91, 0x02,                //   Output (Data, Variable, Absolute), ;LED report
  0x95, 0x01,                //   Report Count (1),
  0x75, 0x03,                //   Report Size (3),
  0x91, 0x03,                //   Output (Constant),                 ;LED report padding
  0x95, KBD_REPORT_KEYS,          //   Report Count (),
  0x75, 0x08,                //   Report Size (8),
  0x15, 0x00,                //   Logical Minimum (0),
  0x25, 0xFF,                //   Logical Maximum(255),
  0x05, 0x07,                //   Usage Page (Key Codes),
  0x19, 0x00,                //   Usage Minimum (0),
  0x29, 0xFF,                //   Usage Maximum (255),
  0x81, 0x00,                //   Input (Data, Array),
  0xc0                       // End Collection
};
/* wrapper */
static const USBDescriptor keyboard_hid_report_descriptor = {
  sizeof keyboard_hid_report_desc_data,
  keyboard_hid_report_desc_data
};

#ifdef NKRO_ENABLE
static const uint8_t nkro_hid_report_desc_data[] = {
  0x05, 0x01,                           // Usage Page (Generic Desktop),
  0x09, 0x06,                           // Usage (Keyboard),
  0xA1, 0x01,                           // Collection (Application),
  // bitmap of modifiers
  0x75, 0x01,                           //   Report Size (1),
  0x95, 0x08,                           //   Report Count (8),
  0x05, 0x07,                           //   Usage Page (Key Codes),
  0x19, 0xE0,                           //   Usage Minimum (224),
  0x29, 0xE7,                           //   Usage Maximum (231),
  0x15, 0x00,                           //   Logical Minimum (0),
  0x25, 0x01,                           //   Logical Maximum (1),
  0x81, 0x02,                           //   Input (Data, Variable, Absolute), ;Modifier byte
  // LED output report
  0x95, 0x05,                           //   Report Count (5),
  0x75, 0x01,                           //   Report Size (1),
  0x05, 0x08,                           //   Usage Page (LEDs),
  0x19, 0x01,                           //   Usage Minimum (1),
  0x29, 0x05,                           //   Usage Maximum (5),
  0x91, 0x02,                           //   Output (Data, Variable, Absolute),
  0x95, 0x01,                           //   Report Count (1),
  0x75, 0x03,                           //   Report Size (3),
  0x91, 0x03,                           //   Output (Constant),
  // bitmap of keys
  0x95, NKRO_REPORT_KEYS * 8,           //   Report Count (),
  0x75, 0x01,                           //   Report Size (1),
  0x15, 0x00,                           //   Logical Minimum (0),
  0x25, 0x01,                           //   Logical Maximum(1),
  0x05, 0x07,                           //   Usage Page (Key Codes),
  0x19, 0x00,                           //   Usage Minimum (0),
  0x29, NKRO_REPORT_KEYS * 8 - 1,       //   Usage Maximum (),
  0x81, 0x02,                           //   Input (Data, Variable, Absolute),
  0xc0                                  // End Collection
};
/* wrapper */
static const USBDescriptor nkro_hid_report_descriptor = {
  sizeof nkro_hid_report_desc_data,
  nkro_hid_report_desc_data
};
#endif /* NKRO_ENABLE */

#ifdef MOUSE_ENABLE
/* Mouse Protocol 1, HID 1.11 spec, Appendix B, page 59-60, with wheel extension
 * http://www.microchip.com/forums/tm.aspx?high=&m=391435&mpage=1#391521
 * http://www.keil.com/forum/15671/
 * http://www.microsoft.com/whdc/device/input/wheel.mspx */
static const uint8_t mouse_hid_report_desc_data[] = {
  /* mouse */
  0x05, 0x01,                      // USAGE_PAGE (Generic Desktop)
  0x09, 0x02,                      // USAGE (Mouse)
  0xa1, 0x01,                      // COLLECTION (Application)
  //0x85, REPORT_ID_MOUSE,         //   REPORT_ID (1)
  0x09, 0x01,                      //   USAGE (Pointer)
  0xa1, 0x00,                      //   COLLECTION (Physical)
                                   // ----------------------------  Buttons
  0x05, 0x09,                      //     USAGE_PAGE (Button)
  0x19, 0x01,                      //     USAGE_MINIMUM (Button 1)
  0x29, 0x05,                      //     USAGE_MAXIMUM (Button 5)
  0x15, 0x00,                      //     LOGICAL_MINIMUM (0)
  0x25, 0x01,                      //     LOGICAL_MAXIMUM (1)
  0x75, 0x01,                      //     REPORT_SIZE (1)
  0x95, 0x05,                      //     REPORT_COUNT (5)
  0x81, 0x02,                      //     INPUT (Data,Var,Abs)
  0x75, 0x03,                      //     REPORT_SIZE (3)
  0x95, 0x01,                      //     REPORT_COUNT (1)
  0x81, 0x03,                      //     INPUT (Cnst,Var,Abs)
                                   // ----------------------------  X,Y position
  0x05, 0x01,                      //     USAGE_PAGE (Generic Desktop)
  0x09, 0x30,                      //     USAGE (X)
  0x09, 0x31,                      //     USAGE (Y)
  0x15, 0x81,                      //     LOGICAL_MINIMUM (-127)
  0x25, 0x7f,                      //     LOGICAL_MAXIMUM (127)
  0x75, 0x08,                      //     REPORT_SIZE (8)
  0x95, 0x02,                      //     REPORT_COUNT (2)
  0x81, 0x06,                      //     INPUT (Data,Var,Rel)
                                   // ----------------------------  Vertical wheel
  0x09, 0x38,                      //     USAGE (Wheel)
  0x15, 0x81,                      //     LOGICAL_MINIMUM (-127)
  0x25, 0x7f,                      //     LOGICAL_MAXIMUM (127)
  0x35, 0x00,                      //     PHYSICAL_MINIMUM (0)        - reset physical
  0x45, 0x00,                      //     PHYSICAL_MAXIMUM (0)
  0x75, 0x08,                      //     REPORT_SIZE (8)
  0x95, 0x01,                      //     REPORT_COUNT (1)
  0x81, 0x06,                      //     INPUT (Data,Var,Rel)
                                   // ----------------------------  Horizontal wheel
  0x05, 0x0c,                      //     USAGE_PAGE (Consumer Devices)
  0x0a, 0x38, 0x02,                //     USAGE (AC Pan)
  0x15, 0x81,                      //     LOGICAL_MINIMUM (-127)
  0x25, 0x7f,                      //     LOGICAL_MAXIMUM (127)
  0x75, 0x08,                      //     REPORT_SIZE (8)
  0x95, 0x01,                      //     REPORT_COUNT (1)
  0x81, 0x06,                      //     INPUT (Data,Var,Rel)
  0xc0,                            //   END_COLLECTION
  0xc0,                            // END_COLLECTION
};
/* wrapper */
static const USBDescriptor mouse_hid_report_descriptor = {
  sizeof mouse_hid_report_desc_data,
  mouse_hid_report_desc_data
};
#endif /* MOUSE_ENABLE */

#ifdef CONSOLE_ENABLE
static const uint8_t console_hid_report_desc_data[] = {
  0x06, 0x31, 0xFF, // Usage Page 0xFF31 (vendor defined)
  0x09, 0x74,       // Usage 0x74
  0xA1, 0x53,       // Collection 0x53
  0x75, 0x08,       // report size = 8 bits
  0x15, 0x00,       // logical minimum = 0
  0x26, 0xFF, 0x00, // logical maximum = 255
  0x95, CONSOLE_EPSIZE, // report count
  0x09, 0x75,       // usage
  0x81, 0x02,       // Input (array)
  0xC0              // end collection
};
/* wrapper */
static const USBDescriptor console_hid_report_descriptor = {
  sizeof console_hid_report_desc_data,
  console_hid_report_desc_data
};
#endif /* CONSOLE_ENABLE */

#ifdef EXTRAKEY_ENABLE
/* audio controls & system controls
 * http://www.microsoft.com/whdc/archive/w2kbd.mspx */
static const uint8_t extra_hid_report_desc_data[] = {
  /* system control */
  0x05, 0x01,                      // USAGE_PAGE (Generic Desktop)
  0x09, 0x80,                      // USAGE (System Control)
  0xa1, 0x01,                      // COLLECTION (Application)
  0x85, REPORT_ID_SYSTEM,          //   REPORT_ID (2)
  0x15, 0x01,                      //   LOGICAL_MINIMUM (0x1)
  0x25, 0xb7,                      //   LOGICAL_MAXIMUM (0xb7)
  0x19, 0x01,                      //   USAGE_MINIMUM (0x1)
  0x29, 0xb7,                      //   USAGE_MAXIMUM (0xb7)
  0x75, 0x10,                      //   REPORT_SIZE (16)
  0x95, 0x01,                      //   REPORT_COUNT (1)
  0x81, 0x00,                      //   INPUT (Data,Array,Abs)
  0xc0,                            // END_COLLECTION
  /* consumer */
  0x05, 0x0c,                      // USAGE_PAGE (Consumer Devices)
  0x09, 0x01,                      // USAGE (Consumer Control)
  0xa1, 0x01,                      // COLLECTION (Application)
  0x85, REPORT_ID_CONSUMER,        //   REPORT_ID (3)
  0x15, 0x01,                      //   LOGICAL_MINIMUM (0x1)
  0x26, 0x9c, 0x02,                //   LOGICAL_MAXIMUM (0x29c)
  0x19, 0x01,                      //   USAGE_MINIMUM (0x1)
  0x2a, 0x9c, 0x02,                //   USAGE_MAXIMUM (0x29c)
  0x75, 0x10,                      //   REPORT_SIZE (16)
  0x95, 0x01,                      //   REPORT_COUNT (1)
  0x81, 0x00,                      //   INPUT (Data,Array,Abs)
  0xc0,                            // END_COLLECTION
};
/* wrapper */
static const USBDescriptor extra_hid_report_descriptor = {
  sizeof extra_hid_report_desc_data,
  extra_hid_report_desc_data
};
#endif /* EXTRAKEY_ENABLE */


/*
 * Configuration Descriptor tree for a HID device
 *
 * The HID Specifications version 1.11 require the following order:
 * - Configuration Descriptor
 * - Interface Descriptor
 * - HID Descriptor
 * - Endpoints Descriptors
 */
#define KBD_HID_DESC_NUM                0
#define KBD_HID_DESC_OFFSET             (9 + (9 + 9 + 7) * KBD_HID_DESC_NUM + 9)

#ifdef MOUSE_ENABLE
#   define MOUSE_HID_DESC_NUM           (KBD_HID_DESC_NUM + 1)
#   define MOUSE_HID_DESC_OFFSET        (9 + (9 + 9 + 7) * MOUSE_HID_DESC_NUM + 9)
#else /* MOUSE_ENABLE */
#   define MOUSE_HID_DESC_NUM           (KBD_HID_DESC_NUM + 0)
#endif /* MOUSE_ENABLE */

#ifdef CONSOLE_ENABLE
#define CONSOLE_HID_DESC_NUM            (MOUSE_HID_DESC_NUM + 1)
#define CONSOLE_HID_DESC_OFFSET         (9 + (9 + 9 + 7) * CONSOLE_HID_DESC_NUM + 9)
#else /* CONSOLE_ENABLE */
#   define CONSOLE_HID_DESC_NUM         (MOUSE_HID_DESC_NUM + 0)
#endif /* CONSOLE_ENABLE */

#ifdef EXTRAKEY_ENABLE
#   define EXTRA_HID_DESC_NUM           (CONSOLE_HID_DESC_NUM + 1)
#   define EXTRA_HID_DESC_OFFSET        (9 + (9 + 9 + 7) * EXTRA_HID_DESC_NUM + 9)
#else /* EXTRAKEY_ENABLE */
#   define EXTRA_HID_DESC_NUM           (CONSOLE_HID_DESC_NUM + 0)
#endif /* EXTRAKEY_ENABLE */

#ifdef NKRO_ENABLE
#   define NKRO_HID_DESC_NUM            (EXTRA_HID_DESC_NUM + 1)
#   define NKRO_HID_DESC_OFFSET         (9 + (9 + 9 + 7) * EXTRA_HID_DESC_NUM + 9)
#else /* NKRO_ENABLE */
#   define NKRO_HID_DESC_NUM            (EXTRA_HID_DESC_NUM + 0)
#endif /* NKRO_ENABLE */

#define NUM_INTERFACES                  (NKRO_HID_DESC_NUM + 1)
#define CONFIG1_DESC_SIZE               (9 + (9 + 9 + 7) * NUM_INTERFACES)

static const uint8_t hid_configuration_descriptor_data[] = {
  /* Configuration Descriptor (9 bytes) USB spec 9.6.3, page 264-266, Table 9-10 */
  USB_DESC_CONFIGURATION(CONFIG1_DESC_SIZE, // wTotalLength
                         NUM_INTERFACES,    // bNumInterfaces
                         1,    // bConfigurationValue
                         0,    // iConfiguration
                         0xA0, // bmAttributes (RESERVED|REMOTEWAKEUP)
                         50),  // bMaxPower (50mA)

  /* Interface Descriptor (9 bytes) USB spec 9.6.5, page 267-269, Table 9-12 */
  USB_DESC_INTERFACE(KBD_INTERFACE,        // bInterfaceNumber
                     0,        // bAlternateSetting
                     1,        // bNumEndpoints
                     0x03,     // bInterfaceClass: HID
                     0x01,     // bInterfaceSubClass: Boot
                     0x01,     // bInterfaceProtocol: Keyboard
                     0),       // iInterface

  /* HID descriptor (9 bytes) HID 1.11 spec, section 6.2.1 */
  USB_DESC_BYTE(9),            // bLength
  USB_DESC_BYTE(0x21),         // bDescriptorType (HID class)
  USB_DESC_BCD(0x0111),        // bcdHID: HID version 1.11
  USB_DESC_BYTE(0),            // bCountryCode
  USB_DESC_BYTE(1),            // bNumDescriptors
  USB_DESC_BYTE(0x22),         // bDescriptorType (report desc)
  USB_DESC_WORD(sizeof(keyboard_hid_report_desc_data)), // wDescriptorLength

  /* Endpoint Descriptor (7 bytes) USB spec 9.6.6, page 269-271, Table 9-13 */
  USB_DESC_ENDPOINT(KBD_ENDPOINT | 0x80,  // bEndpointAddress
                    0x03,      // bmAttributes (Interrupt)
                    KBD_EPSIZE,// wMaxPacketSize
                    10),       // bInterval

  #ifdef MOUSE_ENABLE
  /* Interface Descriptor (9 bytes) USB spec 9.6.5, page 267-269, Table 9-12 */
  USB_DESC_INTERFACE(MOUSE_INTERFACE,   // bInterfaceNumber
                     0,        // bAlternateSetting
                     1,        // bNumEndpoints
                     0x03,     // bInterfaceClass (0x03 = HID)
                     // ThinkPad T23 BIOS doesn't work with boot mouse.
                     0x00,     // bInterfaceSubClass (0x01 = Boot)
                     0x00,     // bInterfaceProtocol (0x02 = Mouse)
                     /*
                        0x01,      // bInterfaceSubClass (0x01 = Boot)
                        0x02,      // bInterfaceProtocol (0x02 = Mouse)
                      */
                     0),        // iInterface

  /* HID descriptor (9 bytes) HID 1.11 spec, section 6.2.1 */
  USB_DESC_BYTE(9),            // bLength
  USB_DESC_BYTE(0x21),         // bDescriptorType (HID class)
  USB_DESC_BCD(0x0111),        // bcdHID: HID version 1.11
  USB_DESC_BYTE(0),            // bCountryCode
  USB_DESC_BYTE(1),            // bNumDescriptors
  USB_DESC_BYTE(0x22),         // bDescriptorType (report desc)
  USB_DESC_WORD(sizeof(mouse_hid_report_desc_data)), // wDescriptorLength

  /* Endpoint Descriptor (7 bytes) USB spec 9.6.6, page 269-271, Table 9-13 */
  USB_DESC_ENDPOINT(MOUSE_ENDPOINT | 0x80,  // bEndpointAddress
                    0x03,      // bmAttributes (Interrupt)
                    MOUSE_EPSIZE,  // wMaxPacketSize
                    1),        // bInterval
  #endif /* MOUSE_ENABLE */

  #ifdef CONSOLE_ENABLE
  /* Interface Descriptor (9 bytes) USB spec 9.6.5, page 267-269, Table 9-12 */
  USB_DESC_INTERFACE(CONSOLE_INTERFACE, // bInterfaceNumber
                     0,        // bAlternateSetting
                     1,        // bNumEndpoints
                     0x03,     // bInterfaceClass: HID
                     0x00,     // bInterfaceSubClass: None
                     0x00,     // bInterfaceProtocol: None
                     0),       // iInterface

  /* HID descriptor (9 bytes) HID 1.11 spec, section 6.2.1 */
  USB_DESC_BYTE(9),            // bLength
  USB_DESC_BYTE(0x21),         // bDescriptorType (HID class)
  USB_DESC_BCD(0x0111),        // bcdHID: HID version 1.11
  USB_DESC_BYTE(0),            // bCountryCode
  USB_DESC_BYTE(1),            // bNumDescriptors
  USB_DESC_BYTE(0x22),         // bDescriptorType (report desc)
  USB_DESC_WORD(sizeof(console_hid_report_desc_data)), // wDescriptorLength

  /* Endpoint Descriptor (7 bytes) USB spec 9.6.6, page 269-271, Table 9-13 */
  USB_DESC_ENDPOINT(CONSOLE_ENDPOINT | 0x80,  // bEndpointAddress
                    0x03,      // bmAttributes (Interrupt)
                    CONSOLE_EPSIZE, // wMaxPacketSize
                    1),        // bInterval
  #endif /* CONSOLE_ENABLE */

  #ifdef EXTRAKEY_ENABLE
  /* Interface Descriptor (9 bytes) USB spec 9.6.5, page 267-269, Table 9-12 */
  USB_DESC_INTERFACE(EXTRA_INTERFACE, // bInterfaceNumber
                     0,        // bAlternateSetting
                     1,        // bNumEndpoints
                     0x03,     // bInterfaceClass: HID
                     0x00,     // bInterfaceSubClass: None
                     0x00,     // bInterfaceProtocol: None
                     0),       // iInterface

  /* HID descriptor (9 bytes) HID 1.11 spec, section 6.2.1 */
  USB_DESC_BYTE(9),            // bLength
  USB_DESC_BYTE(0x21),         // bDescriptorType (HID class)
  USB_DESC_BCD(0x0111),        // bcdHID: HID version 1.11
  USB_DESC_BYTE(0),            // bCountryCode
  USB_DESC_BYTE(1),            // bNumDescriptors
  USB_DESC_BYTE(0x22),         // bDescriptorType (report desc)
  USB_DESC_WORD(sizeof(extra_hid_report_desc_data)), // wDescriptorLength

  /* Endpoint Descriptor (7 bytes) USB spec 9.6.6, page 269-271, Table 9-13 */
  USB_DESC_ENDPOINT(EXTRA_ENDPOINT | 0x80,  // bEndpointAddress
                    0x03,      // bmAttributes (Interrupt)
                    EXTRA_EPSIZE, // wMaxPacketSize
                    10),       // bInterval
  #endif /* EXTRAKEY_ENABLE */

  #ifdef NKRO_ENABLE
  /* Interface Descriptor (9 bytes) USB spec 9.6.5, page 267-269, Table 9-12 */
  USB_DESC_INTERFACE(NKRO_INTERFACE, // bInterfaceNumber
                     0,        // bAlternateSetting
                     1,        // bNumEndpoints
                     0x03,     // bInterfaceClass: HID
                     0x00,     // bInterfaceSubClass: None
                     0x00,     // bInterfaceProtocol: None
                     0),       // iInterface

  /* HID descriptor (9 bytes) HID 1.11 spec, section 6.2.1 */
  USB_DESC_BYTE(9),            // bLength
  USB_DESC_BYTE(0x21),         // bDescriptorType (HID class)
  USB_DESC_BCD(0x0111),        // bcdHID: HID version 1.11
  USB_DESC_BYTE(0),            // bCountryCode
  USB_DESC_BYTE(1),            // bNumDescriptors
  USB_DESC_BYTE(0x22),         // bDescriptorType (report desc)
  USB_DESC_WORD(sizeof(nkro_hid_report_desc_data)), // wDescriptorLength

  /* Endpoint Descriptor (7 bytes) USB spec 9.6.6, page 269-271, Table 9-13 */
  USB_DESC_ENDPOINT(NKRO_ENDPOINT | 0x80,  // bEndpointAddress
                    0x03,      // bmAttributes (Interrupt)
                    NKRO_EPSIZE, // wMaxPacketSize
                    1),       // bInterval
  #endif /* NKRO_ENABLE */
};

/* Configuration Descriptor wrapper */
static const USBDescriptor hid_configuration_descriptor = {
  sizeof hid_configuration_descriptor_data,
  hid_configuration_descriptor_data
};

/* wrappers */
#define HID_DESCRIPTOR_SIZE 9
static const USBDescriptor keyboard_hid_descriptor = {
  HID_DESCRIPTOR_SIZE,
  &hid_configuration_descriptor_data[KBD_HID_DESC_OFFSET]
};
#ifdef MOUSE_ENABLE
static const USBDescriptor mouse_hid_descriptor = {
  HID_DESCRIPTOR_SIZE,
  &hid_configuration_descriptor_data[MOUSE_HID_DESC_OFFSET]
};
#endif /* MOUSE_ENABLE */
#ifdef CONSOLE_ENABLE
static const USBDescriptor console_hid_descriptor = {
  HID_DESCRIPTOR_SIZE,
  &hid_configuration_descriptor_data[CONSOLE_HID_DESC_OFFSET]
};
#endif /* CONSOLE_ENABLE */
#ifdef EXTRAKEY_ENABLE
static const USBDescriptor extra_hid_descriptor = {
  HID_DESCRIPTOR_SIZE,
  &hid_configuration_descriptor_data[EXTRA_HID_DESC_OFFSET]
};
#endif /* EXTRAKEY_ENABLE */
#ifdef NKRO_ENABLE
static const USBDescriptor nkro_hid_descriptor = {
  HID_DESCRIPTOR_SIZE,
  &hid_configuration_descriptor_data[NKRO_HID_DESC_OFFSET]
};
#endif /* NKRO_ENABLE */


/* U.S. English language identifier */
static const uint8_t usb_string_langid[] = {
  USB_DESC_BYTE(4),                        // bLength
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING),    // bDescriptorType
  USB_DESC_WORD(0x0409)                    // wLANGID (U.S. English)
};

/* ugly ugly hack */
#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

/* Vendor string = manufacturer */
static const uint8_t usb_string_vendor[] = {
  USB_DESC_BYTE(PP_NARG(USBSTR_MANUFACTURER)+2),                       // bLength
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING),    // bDescriptorType
  USBSTR_MANUFACTURER
};

/* Device Description string = product */
static const uint8_t usb_string_description[] = {
  USB_DESC_BYTE(PP_NARG(USBSTR_PRODUCT)+2),           // bLength
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING),    // bDescriptorType
  USBSTR_PRODUCT
};

/* Serial Number string (will be filled by the function init_usb_serial_string) */
static uint8_t usb_string_serial[] = {
  USB_DESC_BYTE(22),                       // bLength
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING),    // bDescriptorType
  '0', 0, 'x', 0, 'D', 0, 'E', 0, 'A', 0, 'D', 0, 'B', 0, 'E', 0, 'E', 0, 'F', 0
};

/* Strings wrappers array */
static const USBDescriptor usb_strings[] = {
  { sizeof usb_string_langid, usb_string_langid }
  ,
  { sizeof usb_string_vendor, usb_string_vendor }
  ,
  { sizeof usb_string_description, usb_string_description }
  ,
  { sizeof usb_string_serial, usb_string_serial }
};

/*
 * Handles the GET_DESCRIPTOR callback
 *
 * Returns the proper descriptor
 */
static const USBDescriptor *usb_get_descriptor_cb(USBDriver *usbp, uint8_t dtype, uint8_t dindex, uint16_t lang) {
  (void)usbp;
  (void)lang;
  switch(dtype) {
  /* Generic descriptors */
  case USB_DESCRIPTOR_DEVICE:   /* Device Descriptor */
    return &usb_device_descriptor;

  case USB_DESCRIPTOR_CONFIGURATION:    /* Configuration Descriptor */
    return &hid_configuration_descriptor;

  case USB_DESCRIPTOR_STRING:   /* Strings */
    if(dindex < 4)
      return &usb_strings[dindex];
    break;

  /* HID specific descriptors */
  case USB_DESCRIPTOR_HID:      /* HID Descriptors */
    switch(lang) {    /* yea, poor label, it's actually wIndex from the setup packet */
    case KBD_INTERFACE:
      return &keyboard_hid_descriptor;

#ifdef MOUSE_ENABLE
    case MOUSE_INTERFACE:
      return &mouse_hid_descriptor;
#endif /* MOUSE_ENABLE */
#ifdef CONSOLE_ENABLE
    case CONSOLE_INTERFACE:
      return &console_hid_descriptor;
#endif /* CONSOLE_ENABLE */
#ifdef EXTRAKEY_ENABLE
    case EXTRA_INTERFACE:
      return &extra_hid_descriptor;
#endif /* EXTRAKEY_ENABLE */
#ifdef NKRO_ENABLE
    case NKRO_INTERFACE:
      return &nkro_hid_descriptor;
#endif /* NKRO_ENABLE */
    }

  case USB_DESCRIPTOR_HID_REPORT:       /* HID Report Descriptor */
    switch(lang) {
    case KBD_INTERFACE:
      return &keyboard_hid_report_descriptor;

#ifdef MOUSE_ENABLE
    case MOUSE_INTERFACE:
      return &mouse_hid_report_descriptor;
#endif /* MOUSE_ENABLE */
#ifdef CONSOLE_ENABLE
    case CONSOLE_INTERFACE:
      return &console_hid_report_descriptor;
#endif /* CONSOLE_ENABLE */
#ifdef EXTRAKEY_ENABLE
    case EXTRA_INTERFACE:
      return &extra_hid_report_descriptor;
#endif /* EXTRAKEY_ENABLE */
#ifdef NKRO_ENABLE
    case NKRO_INTERFACE:
      return &nkro_hid_report_descriptor;
#endif /* NKRO_ENABLE */
    }
  }
  return NULL;
}

/* keyboard endpoint state structure */
static USBInEndpointState kbd_ep_state;
/* keyboard endpoint initialization structure (IN) */
static const USBEndpointConfig kbd_ep_config = {
  USB_EP_MODE_TYPE_INTR,        /* Interrupt EP */
  NULL,                         /* SETUP packet notification callback */
  kbd_in_cb,                    /* IN notification callback */
  NULL,                         /* OUT notification callback */
  KBD_EPSIZE,                   /* IN maximum packet size */
  0,                            /* OUT maximum packet size */
  &kbd_ep_state,                /* IN Endpoint state */
  NULL,                         /* OUT endpoint state */
  2,                            /* IN multiplier */
  NULL                          /* SETUP buffer (not a SETUP endpoint) */
};

#ifdef MOUSE_ENABLE
/* mouse endpoint state structure */
static USBInEndpointState mouse_ep_state;

/* mouse endpoint initialization structure (IN) */
static const USBEndpointConfig mouse_ep_config = {
  USB_EP_MODE_TYPE_INTR,        /* Interrupt EP */
  NULL,                         /* SETUP packet notification callback */
  mouse_in_cb,                  /* IN notification callback */
  NULL,                         /* OUT notification callback */
  MOUSE_EPSIZE,                 /* IN maximum packet size */
  0,                            /* OUT maximum packet size */
  &mouse_ep_state,              /* IN Endpoint state */
  NULL,                         /* OUT endpoint state */
  2,                            /* IN multiplier */
  NULL                          /* SETUP buffer (not a SETUP endpoint) */
};
#endif /* MOUSE_ENABLE */

#ifdef CONSOLE_ENABLE
/* console endpoint state structure */
static USBInEndpointState console_ep_state;

/* console endpoint initialization structure (IN) */
static const USBEndpointConfig console_ep_config = {
  USB_EP_MODE_TYPE_INTR,        /* Interrupt EP */
  NULL,                         /* SETUP packet notification callback */
  console_in_cb,                /* IN notification callback */
  NULL,                         /* OUT notification callback */
  CONSOLE_EPSIZE,               /* IN maximum packet size */
  0,                            /* OUT maximum packet size */
  &console_ep_state,            /* IN Endpoint state */
  NULL,                         /* OUT endpoint state */
  2,                            /* IN multiplier */
  NULL                          /* SETUP buffer (not a SETUP endpoint) */
};
#endif /* CONSOLE_ENABLE */

#ifdef EXTRAKEY_ENABLE
/* extrakey endpoint state structure */
static USBInEndpointState extra_ep_state;

/* extrakey endpoint initialization structure (IN) */
static const USBEndpointConfig extra_ep_config = {
  USB_EP_MODE_TYPE_INTR,        /* Interrupt EP */
  NULL,                         /* SETUP packet notification callback */
  extra_in_cb,                  /* IN notification callback */
  NULL,                         /* OUT notification callback */
  EXTRA_EPSIZE,                 /* IN maximum packet size */
  0,                            /* OUT maximum packet size */
  &extra_ep_state,              /* IN Endpoint state */
  NULL,                         /* OUT endpoint state */
  2,                            /* IN multiplier */
  NULL                          /* SETUP buffer (not a SETUP endpoint) */
};
#endif /* EXTRAKEY_ENABLE */

#ifdef NKRO_ENABLE
/* nkro endpoint state structure */
static USBInEndpointState nkro_ep_state;

/* nkro endpoint initialization structure (IN) */
static const USBEndpointConfig nkro_ep_config = {
  USB_EP_MODE_TYPE_INTR,        /* Interrupt EP */
  NULL,                         /* SETUP packet notification callback */
  nkro_in_cb,                   /* IN notification callback */
  NULL,                         /* OUT notification callback */
  NKRO_EPSIZE,                  /* IN maximum packet size */
  0,                            /* OUT maximum packet size */
  &nkro_ep_state,               /* IN Endpoint state */
  NULL,                         /* OUT endpoint state */
  2,                            /* IN multiplier */
  NULL                          /* SETUP buffer (not a SETUP endpoint) */
};
#endif /* NKRO_ENABLE */

/* ---------------------------------------------------------
 *                  USB driver functions
 * ---------------------------------------------------------
 */

/* Handles the USB driver global events
 * TODO: maybe disable some things when connection is lost? */
static void usb_event_cb(USBDriver *usbp, usbevent_t event) {
  switch(event) {
  case USB_EVENT_RESET:
    //TODO: from ISR! print("[R]");
    return;

  case USB_EVENT_ADDRESS:
    return;

  case USB_EVENT_CONFIGURED:
    osalSysLockFromISR();
    /* Enable the endpoints specified into the configuration. */
    usbInitEndpointI(usbp, KBD_ENDPOINT, &kbd_ep_config);
#ifdef MOUSE_ENABLE
    usbInitEndpointI(usbp, MOUSE_ENDPOINT, &mouse_ep_config);
#endif /* MOUSE_ENABLE */
#ifdef CONSOLE_ENABLE
    usbInitEndpointI(usbp, CONSOLE_ENDPOINT, &console_ep_config);
    /* don't need to start the flush timer, it starts from console_in_cb automatically */
#endif /* CONSOLE_ENABLE */
#ifdef EXTRAKEY_ENABLE
    usbInitEndpointI(usbp, EXTRA_ENDPOINT, &extra_ep_config);
#endif /* EXTRAKEY_ENABLE */
#ifdef NKRO_ENABLE
    usbInitEndpointI(usbp, NKRO_ENDPOINT, &nkro_ep_config);
#endif /* NKRO_ENABLE */
    osalSysUnlockFromISR();
    return;

  case USB_EVENT_SUSPEND:
    //TODO: from ISR! print("[S]");
#ifdef SLEEP_LED_ENABLE
    sleep_led_enable();
#endif /* SLEEP_LED_ENABLE */
    return;

  case USB_EVENT_WAKEUP:
    //TODO: from ISR! print("[W]");
    suspend_wakeup_init();
#ifdef SLEEP_LED_ENABLE
    sleep_led_disable();
    // NOTE: converters may not accept this
    led_set(host_keyboard_leds());
#endif /* SLEEP_LED_ENABLE */
    return;

  case USB_EVENT_STALLED:
    return;
  }
}

/* Function used locally in os/hal/src/usb.c for getting descriptors
 * need it here for HID descriptor */
static uint16_t get_hword(uint8_t *p) {
  uint16_t hw;

  hw = (uint16_t)*p++;
  hw |= (uint16_t)*p << 8U;
  return hw;
}

/*
 * Appendix G: HID Request Support Requirements
 *
 * The following table enumerates the requests that need to be supported by various types of HID class devices.
 * Device type     GetReport   SetReport   GetIdle     SetIdle     GetProtocol SetProtocol
 * ------------------------------------------------------------------------------------------
 * Boot Mouse      Required    Optional    Optional    Optional    Required    Required
 * Non-Boot Mouse  Required    Optional    Optional    Optional    Optional    Optional
 * Boot Keyboard   Required    Optional    Required    Required    Required    Required
 * Non-Boot Keybrd Required    Optional    Required    Required    Optional    Optional
 * Other Device    Required    Optional    Optional    Optional    Optional    Optional
 */

/* Callback for SETUP request on the endpoint 0 (control) */
static bool usb_request_hook_cb(USBDriver *usbp) {
  const USBDescriptor *dp;

  /* usbp->setup fields:
   *  0:   bmRequestType (bitmask)
   *  1:   bRequest
   *  2,3: (LSB,MSB) wValue
   *  4,5: (LSB,MSB) wIndex
   *  6,7: (LSB,MSB) wLength (number of bytes to transfer if there is a data phase) */

  /* Handle HID class specific requests */
  if(((usbp->setup[0] & USB_RTYPE_TYPE_MASK) == USB_RTYPE_TYPE_CLASS) &&
     ((usbp->setup[0] & USB_RTYPE_RECIPIENT_MASK) == USB_RTYPE_RECIPIENT_INTERFACE)) {
    switch(usbp->setup[0] & USB_RTYPE_DIR_MASK) {
    case USB_RTYPE_DIR_DEV2HOST:
      switch(usbp->setup[1]) {   /* bRequest */
      case HID_GET_REPORT:
        switch(usbp->setup[4]) {     /* LSB(wIndex) (check MSB==0?) */
        case KBD_INTERFACE:
#ifdef NKRO_ENABLE
        case NKRO_INTERFACE:
#endif /* NKRO_ENABLE */
          usbSetupTransfer(usbp, (uint8_t *)&keyboard_report_sent, sizeof(keyboard_report_sent), NULL);
          return TRUE;
          break;

#ifdef MOUSE_ENABLE
        case MOUSE_INTERFACE:
          usbSetupTransfer(usbp, (uint8_t *)&mouse_report_blank, sizeof(mouse_report_blank), NULL);
          return TRUE;
          break;
#endif /* MOUSE_ENABLE */

#ifdef CONSOLE_ENABLE
        case CONSOLE_INTERFACE:
          usbSetupTransfer(usbp, console_queue_buffer, CONSOLE_EPSIZE, NULL);
          return TRUE;
          break;
#endif /* CONSOLE_ENABLE */

#ifdef EXTRAKEY_ENABLE
        case EXTRA_INTERFACE:
          if(usbp->setup[3] == 1) { /* MSB(wValue) [Report Type] == 1 [Input Report] */
            switch(usbp->setup[2]) { /* LSB(wValue) [Report ID] */
              case REPORT_ID_SYSTEM:
                extra_report_blank[0] = REPORT_ID_SYSTEM;
                usbSetupTransfer(usbp, (uint8_t *)extra_report_blank, sizeof(extra_report_blank), NULL);
                return TRUE;
                break;
              case REPORT_ID_CONSUMER:
                extra_report_blank[0] = REPORT_ID_CONSUMER;
                usbSetupTransfer(usbp, (uint8_t *)extra_report_blank, sizeof(extra_report_blank), NULL);
                return TRUE;
                break;
              default:
                return FALSE;
            }
          } else {
            return FALSE;
          }
          break;
#endif /* EXTRAKEY_ENABLE */

        default:
          usbSetupTransfer(usbp, NULL, 0, NULL);
          return TRUE;
          break;
        }
        break;

      case HID_GET_PROTOCOL:
        if((usbp->setup[4] == KBD_INTERFACE) && (usbp->setup[5] == 0)) {   /* wIndex */
          usbSetupTransfer(usbp, &keyboard_protocol, 1, NULL);
          return TRUE;
        }
        break;

      case HID_GET_IDLE:
        usbSetupTransfer(usbp, &keyboard_idle, 1, NULL);
        return TRUE;
        break;
      }
      break;

    case USB_RTYPE_DIR_HOST2DEV:
      switch(usbp->setup[1]) {   /* bRequest */
      case HID_SET_REPORT:
        switch(usbp->setup[4]) {       /* LSB(wIndex) (check MSB==0 and wLength==1?) */
        case KBD_INTERFACE:
#ifdef NKRO_ENABLE
        case NKRO_INTERFACE:
#endif  /* NKRO_ENABLE */
        /* keyboard_led_stats = <read byte from next OUT report>
         * keyboard_led_stats needs be word (or dword), otherwise we get an exception on F0 */
          usbSetupTransfer(usbp, (uint8_t *)&keyboard_led_stats, 1, NULL);
          return TRUE;
          break;
        }
        break;

      case HID_SET_PROTOCOL:
        if((usbp->setup[4] == KBD_INTERFACE) && (usbp->setup[5] == 0)) {   /* wIndex */
          keyboard_protocol = ((usbp->setup[2]) != 0x00);   /* LSB(wValue) */
#ifdef NKRO_ENABLE
          keyboard_nkro = !!keyboard_protocol;
          if(!keyboard_nkro && keyboard_idle) {
#else /* NKRO_ENABLE */
          if(keyboard_idle) {
#endif /* NKRO_ENABLE */
          /* arm the idle timer if boot protocol & idle */
            osalSysLockFromISR();
            chVTSetI(&keyboard_idle_timer, 4*MS2ST(keyboard_idle), keyboard_idle_timer_cb, (void *)usbp);
            osalSysUnlockFromISR();
          }
        }
        usbSetupTransfer(usbp, NULL, 0, NULL);
        return TRUE;
        break;

      case HID_SET_IDLE:
        keyboard_idle = usbp->setup[3];     /* MSB(wValue) */
        /* arm the timer */
#ifdef NKRO_ENABLE
        if(!keyboard_nkro && keyboard_idle) {
#else /* NKRO_ENABLE */
        if(keyboard_idle) {
#endif /* NKRO_ENABLE */
          osalSysLockFromISR();
          chVTSetI(&keyboard_idle_timer, 4*MS2ST(keyboard_idle), keyboard_idle_timer_cb, (void *)usbp);
          osalSysUnlockFromISR();
        }
        usbSetupTransfer(usbp, NULL, 0, NULL);
        return TRUE;
        break;
      }
      break;
    }
  }

  /* Handle the Get_Descriptor Request for HID class (not handled by the default hook) */
  if((usbp->setup[0] == 0x81) && (usbp->setup[1] == USB_REQ_GET_DESCRIPTOR)) {
    dp = usbp->config->get_descriptor_cb(usbp, usbp->setup[3], usbp->setup[2], get_hword(&usbp->setup[4]));
    if(dp == NULL)
      return FALSE;
    usbSetupTransfer(usbp, (uint8_t *)dp->ud_string, dp->ud_size, NULL);
    return TRUE;
  }

  return FALSE;
}

/* Start-of-frame callback */
static void usb_sof_cb(USBDriver *usbp) {
  kbd_sof_cb(usbp);
}


/* USB driver configuration */
static const USBConfig usbcfg = {
  usb_event_cb,                 /* USB events callback */
  usb_get_descriptor_cb,        /* Device GET_DESCRIPTOR request callback */
  usb_request_hook_cb,          /* Requests hook callback */
  usb_sof_cb                    /* Start Of Frame callback */
};

/*
 * Initialize the USB driver
 */
void init_usb_driver(USBDriver *usbp) {
  /*
   * Activates the USB driver and then the USB bus pull-up on D+.
   * Note, a delay is inserted in order to not have to disconnect the cable
   * after a reset.
   */
  usbDisconnectBus(usbp);
  chThdSleepMilliseconds(1500);
  usbStart(usbp, &usbcfg);
  usbConnectBus(usbp);

  chVTObjectInit(&keyboard_idle_timer);
#ifdef CONSOLE_ENABLE
  obqObjectInit(&console_buf_queue, console_queue_buffer, CONSOLE_EPSIZE, CONSOLE_QUEUE_CAPACITY, console_queue_onotify, (void*)usbp);
  chVTObjectInit(&console_flush_timer);
#endif
}

/*
 * Send remote wakeup packet
 * Note: should not be called from ISR
 */
void send_remote_wakeup(USBDriver *usbp) {
  (void)usbp;
#if defined(K20x) || defined(KL2x)
#if KINETIS_USB_USE_USB0
  USB0->CTL |= USBx_CTL_RESUME;
  chThdSleepMilliseconds(15);
  USB0->CTL &= ~USBx_CTL_RESUME;
#endif /* KINETIS_USB_USE_USB0 */
#elif defined(STM32F0XX) || defined(STM32F1XX) /* K20x || KL2x */
  STM32_USB->CNTR |= CNTR_RESUME;
  chThdSleepMilliseconds(15);
  STM32_USB->CNTR &= ~CNTR_RESUME;
#else /* STM32F0XX || STM32F1XX */
#warning Sending remote wakeup packet not implemented for your platform.
#endif /* K20x || KL2x */
}

/* ---------------------------------------------------------
 *                  Keyboard functions
 * ---------------------------------------------------------
 */

/* keyboard IN callback hander (a kbd report has made it IN) */
void kbd_in_cb(USBDriver *usbp, usbep_t ep) {
  /* STUB */
  (void)usbp;
  (void)ep;
}

#ifdef NKRO_ENABLE
/* nkro IN callback hander (a nkro report has made it IN) */
void nkro_in_cb(USBDriver *usbp, usbep_t ep) {
  /* STUB */
  (void)usbp;
  (void)ep;
}
#endif /* NKRO_ENABLE */

/* start-of-frame handler
 * TODO: i guess it would be better to re-implement using timers,
 *  so that this is not going to have to be checked every 1ms */
void kbd_sof_cb(USBDriver *usbp) {
  (void)usbp;
}

/* Idle requests timer code
 * callback (called from ISR, unlocked state) */
static void keyboard_idle_timer_cb(void *arg) {
  USBDriver *usbp = (USBDriver *)arg;

  osalSysLockFromISR();

  /* check that the states of things are as they're supposed to */
  if(usbGetDriverStateI(usbp) != USB_ACTIVE) {
    /* do not rearm the timer, should be enabled on IDLE request */
    osalSysUnlockFromISR();
    return;
  }

#ifdef NKRO_ENABLE
  if(!keyboard_nkro && keyboard_idle) {
#else /* NKRO_ENABLE */
  if(keyboard_idle) {
#endif /* NKRO_ENABLE */
    /* TODO: are we sure we want the KBD_ENDPOINT? */
    if(!usbGetTransmitStatusI(usbp, KBD_ENDPOINT)) {
      usbStartTransmitI(usbp, KBD_ENDPOINT, (uint8_t *)&keyboard_report_sent, KBD_EPSIZE);
    }
    /* rearm the timer */
    chVTSetI(&keyboard_idle_timer, 4*MS2ST(keyboard_idle), keyboard_idle_timer_cb, (void *)usbp);
  }

  /* do not rearm the timer if the condition above fails
   * it should be enabled again on either IDLE or SET_PROTOCOL requests */
  osalSysUnlockFromISR();
}

/* LED status */
uint8_t keyboard_leds(void) {
  return (uint8_t)(keyboard_led_stats & 0xFF);
}

/* prepare and start sending a report IN
 * not callable from ISR or locked state */
void send_keyboard(report_keyboard_t *report) {
  osalSysLock();
  if(usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
    osalSysUnlock();
    return;
  }
  osalSysUnlock();

#ifdef NKRO_ENABLE
  if(keyboard_nkro) {  /* NKRO protocol */
    /* need to wait until the previous packet has made it through */
    /* can rewrite this using the synchronous API, then would wait
     * until *after* the packet has been transmitted. I think
     * this is more efficient */
    /* busy wait, should be short and not very common */
    osalSysLock();
    if(usbGetTransmitStatusI(&USB_DRIVER, NKRO_ENDPOINT)) {
      /* Need to either suspend, or loop and call unlock/lock during
       * every iteration - otherwise the system will remain locked,
       * no interrupts served, so USB not going through as well.
       * Note: for suspend, need USB_USE_WAIT == TRUE in halconf.h */
      osalThreadSuspendS(&(&USB_DRIVER)->epc[NKRO_ENDPOINT]->in_state->thread);
    }
    usbStartTransmitI(&USB_DRIVER, NKRO_ENDPOINT, (uint8_t *)report, sizeof(report_keyboard_t));
    osalSysUnlock();
  } else
#endif /* NKRO_ENABLE */
  { /* boot protocol */
    /* need to wait until the previous packet has made it through */
    /* busy wait, should be short and not very common */
    osalSysLock();
    if(usbGetTransmitStatusI(&USB_DRIVER, KBD_ENDPOINT)) {
      /* Need to either suspend, or loop and call unlock/lock during
       * every iteration - otherwise the system will remain locked,
       * no interrupts served, so USB not going through as well.
       * Note: for suspend, need USB_USE_WAIT == TRUE in halconf.h */
      osalThreadSuspendS(&(&USB_DRIVER)->epc[KBD_ENDPOINT]->in_state->thread);
    }
    usbStartTransmitI(&USB_DRIVER, KBD_ENDPOINT, (uint8_t *)report, KBD_EPSIZE);
    osalSysUnlock();
  }
  keyboard_report_sent = *report;
}

/* ---------------------------------------------------------
 *                     Mouse functions
 * ---------------------------------------------------------
 */

#ifdef MOUSE_ENABLE

/* mouse IN callback hander (a mouse report has made it IN) */
void mouse_in_cb(USBDriver *usbp, usbep_t ep) {
  (void)usbp;
  (void)ep;
}

void send_mouse(report_mouse_t *report) {
  osalSysLock();
  if(usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
    osalSysUnlock();
    return;
  }
  osalSysUnlock();

  /* TODO: LUFA manually waits for the endpoint to become ready
   * for about 10ms for mouse, kbd, system; 1ms for nkro
   * is this really needed?
   */

  osalSysLock();
  usbStartTransmitI(&USB_DRIVER, MOUSE_ENDPOINT, (uint8_t *)report, sizeof(report_mouse_t));
  osalSysUnlock();
}

#else /* MOUSE_ENABLE */
void send_mouse(report_mouse_t *report) {
  (void)report;
}
#endif /* MOUSE_ENABLE */

/* ---------------------------------------------------------
 *                   Extrakey functions
 * ---------------------------------------------------------
 */

#ifdef EXTRAKEY_ENABLE

/* extrakey IN callback hander */
void extra_in_cb(USBDriver *usbp, usbep_t ep) {
  /* STUB */
  (void)usbp;
  (void)ep;
}

static void send_extra_report(uint8_t report_id, uint16_t data) {
  osalSysLock();
  if(usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
    osalSysUnlock();
    return;
  }

  report_extra_t report = {
    .report_id = report_id,
    .usage = data
  };

  usbStartTransmitI(&USB_DRIVER, EXTRA_ENDPOINT, (uint8_t *)&report, sizeof(report_extra_t));
  osalSysUnlock();
}

void send_system(uint16_t data) {
  send_extra_report(REPORT_ID_SYSTEM, data);
}

void send_consumer(uint16_t data) {
  send_extra_report(REPORT_ID_CONSUMER, data);
}

#else /* EXTRAKEY_ENABLE */
void send_system(uint16_t data) {
  (void)data;
}
void send_consumer(uint16_t data) {
  (void)data;
}
#endif /* EXTRAKEY_ENABLE */

/* ---------------------------------------------------------
 *                   Console functions
 * ---------------------------------------------------------
 */

#ifdef CONSOLE_ENABLE

/* console IN callback hander */
void console_in_cb(USBDriver *usbp, usbep_t ep) {
  (void)ep; /* should have ep == CONSOLE_ENDPOINT, so use that to save time/space */
  uint8_t *buf;
  size_t n;

  osalSysLockFromISR();

  /* rearm the timer */
  chVTSetI(&console_flush_timer, MS2ST(CONSOLE_FLUSH_MS), console_flush_cb, (void *)usbp);

  /* Freeing the buffer just transmitted, if it was not a zero size packet.*/
  if (usbp->epc[CONSOLE_ENDPOINT]->in_state->txsize > 0U) {
    obqReleaseEmptyBufferI(&console_buf_queue);
  }

  /* Checking if there is a buffer ready for transmission.*/
  buf = obqGetFullBufferI(&console_buf_queue, &n);

  if (buf != NULL) {
    /* The endpoint cannot be busy, we are in the context of the callback,
       so it is safe to transmit without a check.*/
    /* Should have n == CONSOLE_EPSIZE; check it? */
    usbStartTransmitI(usbp, CONSOLE_ENDPOINT, buf, CONSOLE_EPSIZE);
  } else {
    /* Nothing to transmit.*/
  }

  osalSysUnlockFromISR();
}

/* Callback when data is inserted into the output queue
 * Called from a locked state */
void console_queue_onotify(io_buffers_queue_t *bqp) {
  size_t n;
  USBDriver *usbp = bqGetLinkX(bqp);

  if(usbGetDriverStateI(usbp) != USB_ACTIVE)
    return;

  /* Checking if there is already a transaction ongoing on the endpoint.*/
  if (!usbGetTransmitStatusI(usbp, CONSOLE_ENDPOINT)) {
    /* Trying to get a full buffer.*/
    uint8_t *buf = obqGetFullBufferI(&console_buf_queue, &n);
    if (buf != NULL) {
      /* Buffer found, starting a new transaction.*/
      /* Should have n == CONSOLE_EPSIZE; check this? */
      usbStartTransmitI(usbp, CONSOLE_ENDPOINT, buf, CONSOLE_EPSIZE);
    }
  }
}

/* Flush timer code
 * callback (called from ISR, unlocked state) */
static void console_flush_cb(void *arg) {
  USBDriver *usbp = (USBDriver *)arg;
  osalSysLockFromISR();

  /* check that the states of things are as they're supposed to */
  if(usbGetDriverStateI(usbp) != USB_ACTIVE) {
    /* rearm the timer */
    chVTSetI(&console_flush_timer, MS2ST(CONSOLE_FLUSH_MS), console_flush_cb, (void *)usbp);
    osalSysUnlockFromISR();
    return;
  }

  /* If there is already a transaction ongoing then another one cannot be
     started.*/
  if (usbGetTransmitStatusI(usbp, CONSOLE_ENDPOINT)) {
    /* rearm the timer */
    chVTSetI(&console_flush_timer, MS2ST(CONSOLE_FLUSH_MS), console_flush_cb, (void *)usbp);
    osalSysUnlockFromISR();
    return;
  }

  /* Checking if there only a buffer partially filled, if so then it is
     enforced in the queue and transmitted.*/
  if(obqTryFlushI(&console_buf_queue)) {
    size_t n,i;
    uint8_t *buf = obqGetFullBufferI(&console_buf_queue, &n);

    osalDbgAssert(buf != NULL, "queue is empty");

    /* zero the rest of the buffer (buf should point to allocated space) */
    for(i=n; i<CONSOLE_EPSIZE; i++)
      buf[i]=0;
    usbStartTransmitI(usbp, CONSOLE_ENDPOINT, buf, CONSOLE_EPSIZE);
  }

  /* rearm the timer */
  chVTSetI(&console_flush_timer, MS2ST(CONSOLE_FLUSH_MS), console_flush_cb, (void *)usbp);
  osalSysUnlockFromISR();
}


int8_t sendchar(uint8_t c) {
  osalSysLock();
  if(usbGetDriverStateI(&USB_DRIVER) != USB_ACTIVE) {
    osalSysUnlock();
    return 0;
  }
  osalSysUnlock();
  /* Timeout after 100us if the queue is full.
   * Increase this timeout if too much stuff is getting
   * dropped (i.e. the buffer is getting full too fast
   * for USB/HIDRAW to dequeue). Another possibility
   * for fixing this kind of thing is to increase
   * CONSOLE_QUEUE_CAPACITY. */
  return(obqPutTimeout(&console_buf_queue, c, US2ST(100)));
}

#else /* CONSOLE_ENABLE */
int8_t sendchar(uint8_t c) {
  (void)c;
  return 0;
}
#endif /* CONSOLE_ENABLE */

void sendchar_pf(void *p, char c) {
  (void)p;
  sendchar((uint8_t)c);
}
