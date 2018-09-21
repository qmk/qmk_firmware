/* Name: usbconfig.h
 * Project: AVR USB driver
 * Author: Christian Starkjohann
 * Creation Date: 2007-03-13
 * Tabsize: 4
 * Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt)
 * This Revision: $Id$
 */

#ifndef __usbconfig_h_included__
#define __usbconfig_h_included__

/*
General Description:
This file contains the configuration options for the USB driver.

Please note that the usbdrv contains a usbconfig-prototype.h file now. We
recommend that you use that file as a template because it will always list
the newest features and options.
*/

/* Fetch the hardware configuration from bootloaderconfig.h so that we have a
 * single file where hardware settings are stored.
 * Do not edit the functional settings below.
 */
#include "bootloaderconfig.h"

#define USB_PUBLIC static
/* Use the define above if you #include usbdrv.c instead of linking against it.
 * This technique saves a couple of bytes in flash memory.
 */

/* --------------------------- Functional Range ---------------------------- */

#define USB_CFG_HAVE_INTRIN_ENDPOINT    1
/* Define this to 1 if you want to compile a version with two endpoints: The
 * default control endpoint 0 and an interrupt-in endpoint 1.
 */
#define USB_CFG_HAVE_INTRIN_ENDPOINT3   0
/* Define this to 1 if you want to compile a version with three endpoints: The
 * default control endpoint 0, an interrupt-in endpoint 1 and an interrupt-in
 * endpoint 3. You must also enable endpoint 1 above.
 */
#define USB_CFG_SUPPRESS_INTR_CODE      1
/* Define this to 1 if you want to declare interrupt-in endpoints, but don't
 * want to send any data over them. If this macro is defined to 1, functions
 * usbSetInterrupt() and usbSetInterrupt3() are omitted. This is useful if
 * you need the interrupt-in endpoints in order to comply to an interface
 * (e.g. HID), but never want to send any data. This option saves a couple
 * of bytes in flash memory and the transmit buffers in RAM.
 */
#define USB_CFG_IMPLEMENT_HALT          0
/* Define this to 1 if you also want to implement the ENDPOINT_HALT feature
 * for endpoint 1 (interrupt endpoint). Although you may not need this feature,
 * it is required by the standard. We have made it a config option because it
 * bloats the code considerably.
 */
#define USB_CFG_INTR_POLL_INTERVAL      200
/* If you compile a version with endpoint 1 (interrupt-in), this is the poll
 * interval. The value is in milliseconds and must not be less than 10 ms for
 * low speed devices.
 */
#define USB_CFG_IS_SELF_POWERED         0
/* Define this to 1 if the device has its own power supply. Set it to 0 if the
 * device is powered from the USB bus.
 */
#define USB_CFG_MAX_BUS_POWER           100
/* Set this variable to the maximum USB bus power consumption of your device.
 * The value is in milliamperes. [It will be divided by two since USB
 * communicates power requirements in units of 2 mA.]
 */
#define USB_CFG_IMPLEMENT_FN_WRITE      1
/* Set this to 1 if you want usbFunctionWrite() to be called for control-out
 * transfers. Set it to 0 if you don't need it and want to save a couple of
 * bytes.
 */
#define USB_CFG_IMPLEMENT_FN_READ       0
/* Set this to 1 if you need to send control replies which are generated
 * "on the fly" when usbFunctionRead() is called. If you only want to send
 * data from a static buffer, set it to 0 and return the data from
 * usbFunctionSetup(). This saves a couple of bytes.
 */
#define USB_CFG_IMPLEMENT_FN_WRITEOUT   0
/* Define this to 1 if you want to use interrupt-out (or bulk out) endpoint 1.
 * You must implement the function usbFunctionWriteOut() which receives all
 * interrupt/bulk data sent to endpoint 1.
 */
#define USB_CFG_HAVE_FLOWCONTROL        0
/* Define this to 1 if you want flowcontrol over USB data. See the definition
 * of the macros usbDisableAllRequests() and usbEnableAllRequests() in
 * usbdrv.h.
 */
#define TIMER0_PRESCALING           64 /* must match the configuration for TIMER0 in main */
#define TOLERATED_DEVIATION_PPT     5  /* max clock deviation before we tune in 1/10 % */
/* derived constants: */
#define EXPECTED_TIMER0_INCREMENT   ((F_CPU / (1000 * TIMER0_PRESCALING)) & 0xff)
#define TOLERATED_DEVIATION         (TOLERATED_DEVIATION_PPT * F_CPU / (1000000 * TIMER0_PRESCALING))
#ifdef __ASSEMBLER__
macro tuneOsccal
    push    YH                              ;[0]
    clr     YH                              ;[2]
    in      YL, TCNT0                       ;[3]
    out     TCNT0, YH                       ;[4]
    subi    YL, EXPECTED_TIMER0_INCREMENT   ;[5]
#if OSCCAL > 0x3f
    lds     YH, OSCCAL                      ;[6]
#else
    in      YH, OSCCAL                      ;[6]
#endif
    cpi     YL, TOLERATED_DEVIATION + 1     ;[7]
    brmi    notTooHigh                      ;[8]
    subi    YH, 1                           ;[9] clock rate was too high
    rjmp    osctuneDone                     ;[10]
notTooHigh:
    cpi     YL, -TOLERATED_DEVIATION        ;[10]
    brpl    osctuneDone                     ;[11] not too low
    inc     YH                              ;[12] clock rate was too low
osctuneDone:
#if OSCCAL > 0x3f
    sts     OSCCAL, YH                      ;[12-13] store tuned value
#else
    out     OSCCAL, YH                      ;[12-13] store tuned value
#endif
tuningOverflow:
    pop     YH                              ;[14]
    endm                                    ;[16] max number of cycles
#endif
#if F_CPU == 12800000
#   define USB_SOF_HOOK        tuneOsccal
#endif
/* This macro (if defined) is executed in the assembler module when a
 * Start Of Frame condition is detected. It is recommended to define it to
 * the name of an assembler macro which is defined here as well so that more
 * than one assembler instruction can be used. The macro may use the register
 * YL and modify SREG. If it lasts longer than a couple of cycles, USB messages
 * immediately after an SOF pulse may be lost and must be retried by the host.
 * What can you do with this hook? Since the SOF signal occurs exactly every
 * 1 ms (unless the host is in sleep mode), you can use it to tune OSCCAL in
 * designs running on the internal RC oscillator.
 * Please note that Start Of Frame detection works only if D- is wired to the
 * interrupt, not D+. THIS IS DIFFERENT THAN MOST EXAMPLES!
 */

/* -------------------------- Device Description --------------------------- */

#define  USB_CFG_VENDOR_ID       0xc0, 0x16
/* USB vendor ID for the device, low byte first. If you have registered your
 * own Vendor ID, define it here. Otherwise you use obdev's free shared
 * VID/PID pair. Be sure to read USBID-License.txt for rules!
 */
#define  USB_CFG_DEVICE_ID       0xdf, 0x05
/* This is the ID of the product, low byte first. It is interpreted in the
 * scope of the vendor ID. If you have registered your own VID with usb.org
 * or if you have licensed a PID from somebody else, define it here. Otherwise
 * you use obdev's free shared VID/PID pair. Be sure to read the rules in
 * USBID-License.txt!
 */
#define USB_CFG_DEVICE_VERSION  0x00, 0x01
/* Version number of the device: Minor number first, then major number.
 */
#define USB_CFG_VENDOR_NAME     'o', 'b', 'd', 'e', 'v', '.', 'a', 't'
#define USB_CFG_VENDOR_NAME_LEN 8
/* These two values define the vendor name returned by the USB device. The name
 * must be given as a list of characters under single quotes. The characters
 * are interpreted as Unicode (UTF-16) entities.
 * If you don't want a vendor name string, undefine these macros.
 * ALWAYS define a vendor name containing your Internet domain name if you use
 * obdev's free shared VID/PID pair. See the file USBID-License.txt for
 * details.
 */
#define USB_CFG_DEVICE_NAME     'H', 'I', 'D', 'B', 'o', 'o', 't'
#define USB_CFG_DEVICE_NAME_LEN 7
/* Same as above for the device name. If you don't want a device name, undefine
 * the macros. See the file USBID-License.txt before you assign a name if you
 * use a shared VID/PID.
 */
/*#define USB_CFG_SERIAL_NUMBER   'N', 'o', 'n', 'e' */
/*#define USB_CFG_SERIAL_NUMBER_LEN   0 */
/* Same as above for the serial number. If you don't want a serial number,
 * undefine the macros.
 * It may be useful to provide the serial number through other means than at
 * compile time. See the section about descriptor properties below for how
 * to fine tune control over USB descriptors such as the string descriptor
 * for the serial number.
 */
#define USB_CFG_DEVICE_CLASS        0
#define USB_CFG_DEVICE_SUBCLASS     0
/* See USB specification if you want to conform to an existing device class.
 */
#define USB_CFG_INTERFACE_CLASS     3   /* HID */
#define USB_CFG_INTERFACE_SUBCLASS  0
#define USB_CFG_INTERFACE_PROTOCOL  0
/* See USB specification if you want to conform to an existing device class or
 * protocol.
 */
#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH    33  /* total length of report descriptor */
/* Define this to the length of the HID report descriptor, if you implement
 * an HID device. Otherwise don't define it or define it to 0.
 */

/* ------------------- Fine Control over USB Descriptors ------------------- */
/* If you don't want to use the driver's default USB descriptors, you can
 * provide our own. These can be provided as (1) fixed length static data in
 * flash memory, (2) fixed length static data in RAM or (3) dynamically at
 * runtime in the function usbFunctionDescriptor(). See usbdrv.h for more
 * information about this function.
 * Descriptor handling is configured through the descriptor's properties. If
 * no properties are defined or if they are 0, the default descriptor is used.
 * Possible properties are:
 *   + USB_PROP_IS_DYNAMIC: The data for the descriptor should be fetched
 *     at runtime via usbFunctionDescriptor().
 *   + USB_PROP_IS_RAM: The data returned by usbFunctionDescriptor() or found
 *     in static memory is in RAM, not in flash memory.
 *   + USB_PROP_LENGTH(len): If the data is in static memory (RAM or flash),
 *     the driver must know the descriptor's length. The descriptor itself is
 *     found at the address of a well known identifier (see below).
 * List of static descriptor names (must be declared PROGMEM if in flash):
 *   char usbDescriptorDevice[];
 *   char usbDescriptorConfiguration[];
 *   char usbDescriptorHidReport[];
 *   char usbDescriptorString0[];
 *   int usbDescriptorStringVendor[];
 *   int usbDescriptorStringDevice[];
 *   int usbDescriptorStringSerialNumber[];
 * Other descriptors can't be provided statically, they must be provided
 * dynamically at runtime.
 *
 * Descriptor properties are or-ed or added together, e.g.:
 * #define USB_CFG_DESCR_PROPS_DEVICE   (USB_PROP_IS_RAM | USB_PROP_LENGTH(18))
 *
 * The following descriptors are defined:
 *   USB_CFG_DESCR_PROPS_DEVICE
 *   USB_CFG_DESCR_PROPS_CONFIGURATION
 *   USB_CFG_DESCR_PROPS_STRINGS
 *   USB_CFG_DESCR_PROPS_STRING_0
 *   USB_CFG_DESCR_PROPS_STRING_VENDOR
 *   USB_CFG_DESCR_PROPS_STRING_PRODUCT
 *   USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER
 *   USB_CFG_DESCR_PROPS_HID
 *   USB_CFG_DESCR_PROPS_HID_REPORT
 *   USB_CFG_DESCR_PROPS_UNKNOWN (for all descriptors not handled by the driver)
 *
 */

#define USB_CFG_DESCR_PROPS_DEVICE                  0
#define USB_CFG_DESCR_PROPS_CONFIGURATION           0
#define USB_CFG_DESCR_PROPS_STRINGS                 0
#define USB_CFG_DESCR_PROPS_STRING_0                0
#define USB_CFG_DESCR_PROPS_STRING_VENDOR           0
#define USB_CFG_DESCR_PROPS_STRING_PRODUCT          0
#define USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER    0
#define USB_CFG_DESCR_PROPS_HID                     0
#define USB_CFG_DESCR_PROPS_HID_REPORT              0
#define USB_CFG_DESCR_PROPS_UNKNOWN                 0

#define usbMsgPtr_t unsigned short  /* Use scalar type in order to save a couple of bytes */

/* ----------------------- Optional MCU Description ------------------------ */

/* The following configurations have working defaults in usbdrv.h. You
 * usually don't need to set them explicitly. Only if you want to run
 * the driver on a device which is not yet supported or with a compiler
 * which is not fully supported (such as IAR C) or if you use a differnt
 * interrupt than INT0, you may have to define some of these.
 */
/* #define USB_INTR_CFG            MCUCR */
/* #define USB_INTR_CFG_SET        ((1 << ISC00) | (1 << ISC01)) */
/* #define USB_INTR_CFG_CLR        0 */
/* #define USB_INTR_ENABLE         GIMSK */
/* #define USB_INTR_ENABLE_BIT     INT0 */
/* #define USB_INTR_PENDING        GIFR */
/* #define USB_INTR_PENDING_BIT    INTF0 */

#endif /* __usbconfig_h_included__ */
