/* Name: usbdrv.h
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Christian Starkjohann
 * Creation Date: 2004-12-29
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: usbdrv.h 793 2010-07-15 15:58:11Z cs $
 */

#ifndef __usbdrv_h_included__
#define __usbdrv_h_included__
#include "usbconfig.h"
#include "usbportability.h"

/*
Hardware Prerequisites:
=======================
USB lines D+ and D- MUST be wired to the same I/O port. We recommend that D+
triggers the interrupt (best achieved by using INT0 for D+), but it is also
possible to trigger the interrupt from D-. If D- is used, interrupts are also
triggered by SOF packets. D- requires a pull-up of 1.5k to +3.5V (and the
device must be powered at 3.5V) to identify as low-speed USB device. A
pull-down or pull-up of 1M SHOULD be connected from D+ to +3.5V to prevent
interference when no USB master is connected. If you use Zener diodes to limit
the voltage on D+ and D-, you MUST use a pull-down resistor, not a pull-up.
We use D+ as interrupt source and not D- because it does not trigger on
keep-alive and RESET states. If you want to count keep-alive events with
USB_COUNT_SOF, you MUST use D- as an interrupt source.

As a compile time option, the 1.5k pull-up resistor on D- can be made
switchable to allow the device to disconnect at will. See the definition of
usbDeviceConnect() and usbDeviceDisconnect() further down in this file.

Please adapt the values in usbconfig.h according to your hardware!

The device MUST be clocked at exactly 12 MHz, 15 MHz, 16 MHz or 20 MHz
or at 12.8 MHz resp. 16.5 MHz +/- 1%. See usbconfig-prototype.h for details.


Limitations:
============
Robustness with respect to communication errors:
The driver assumes error-free communication. It DOES check for errors in
the PID, but does NOT check bit stuffing errors, SE0 in middle of a byte,
token CRC (5 bit) and data CRC (16 bit). CRC checks can not be performed due
to timing constraints: We must start sending a reply within 7 bit times.
Bit stuffing and misplaced SE0 would have to be checked in real-time, but CPU
performance does not permit that. The driver does not check Data0/Data1
toggling, but application software can implement the check.

Input characteristics:
Since no differential receiver circuit is used, electrical interference
robustness may suffer. The driver samples only one of the data lines with
an ordinary I/O pin's input characteristics. However, since this is only a
low speed USB implementation and the specification allows for 8 times the
bit rate over the same hardware, we should be on the safe side. Even the spec
requires detection of asymmetric states at high bit rate for SE0 detection.

Number of endpoints:
The driver supports the following endpoints:

- Endpoint 0, the default control endpoint.
- Any number of interrupt- or bulk-out endpoints. The data is sent to
  usbFunctionWriteOut() and USB_CFG_IMPLEMENT_FN_WRITEOUT must be defined
  to 1 to activate this feature. The endpoint number can be found in the
  global variable 'usbRxToken'.
- One default interrupt- or bulk-in endpoint. This endpoint is used for
  interrupt- or bulk-in transfers which are not handled by any other endpoint.
  You must define USB_CFG_HAVE_INTRIN_ENDPOINT in order to activate this
  feature and call usbSetInterrupt() to send interrupt/bulk data.
- One additional interrupt- or bulk-in endpoint. This was endpoint 3 in
  previous versions of this driver but can now be configured to any endpoint
  number. You must define USB_CFG_HAVE_INTRIN_ENDPOINT3 in order to activate
  this feature and call usbSetInterrupt3() to send interrupt/bulk data. The
  endpoint number can be set with USB_CFG_EP3_NUMBER.

Please note that the USB standard forbids bulk endpoints for low speed devices!
Most operating systems allow them anyway, but the AVR will spend 90% of the CPU
time in the USB interrupt polling for bulk data.

Maximum data payload:
Data payload of control in and out transfers may be up to 254 bytes. In order
to accept payload data of out transfers, you need to implement
'usbFunctionWrite()'.

USB Suspend Mode supply current:
The USB standard limits power consumption to 500uA when the bus is in suspend
mode. This is not a problem for self-powered devices since they don't need
bus power anyway. Bus-powered devices can achieve this only by putting the
CPU in sleep mode. The driver does not implement suspend handling by itself.
However, the application may implement activity monitoring and wakeup from
sleep. The host sends regular SE0 states on the bus to keep it active. These
SE0 states can be detected by using D- as the interrupt source. Define
USB_COUNT_SOF to 1 and use the global variable usbSofCount to check for bus
activity.

Operation without an USB master:
The driver behaves neutral without connection to an USB master if D- reads
as 1. To avoid spurious interrupts, we recommend a high impedance (e.g. 1M)
pull-down or pull-up resistor on D+ (interrupt). If Zener diodes are used,
use a pull-down. If D- becomes statically 0, the driver may block in the
interrupt routine.

Interrupt latency:
The application must ensure that the USB interrupt is not disabled for more
than 25 cycles (this is for 12 MHz, faster clocks allow longer latency).
This implies that all interrupt routines must either have the "ISR_NOBLOCK"
attribute set (see "avr/interrupt.h") or be written in assembler with "sei"
as the first instruction.

Maximum interrupt duration / CPU cycle consumption:
The driver handles all USB communication during the interrupt service
routine. The routine will not return before an entire USB message is received
and the reply is sent. This may be up to ca. 1200 cycles @ 12 MHz (= 100us) if
the host conforms to the standard. The driver will consume CPU cycles for all
USB messages, even if they address another (low-speed) device on the same bus.

*/

/* ------------------------------------------------------------------------- */
/* --------------------------- Module Interface ---------------------------- */
/* ------------------------------------------------------------------------- */

#define USBDRV_VERSION  20100715
/* This define uniquely identifies a driver version. It is a decimal number
 * constructed from the driver's release date in the form YYYYMMDD. If the
 * driver's behavior or interface changes, you can use this constant to
 * distinguish versions. If it is not defined, the driver's release date is
 * older than 2006-01-25.
 */


#ifndef USB_PUBLIC
#define USB_PUBLIC
#endif
/* USB_PUBLIC is used as declaration attribute for all functions exported by
 * the USB driver. The default is no attribute (see above). You may define it
 * to static either in usbconfig.h or from the command line if you include
 * usbdrv.c instead of linking against it. Including the C module of the driver
 * directly in your code saves a couple of bytes in flash memory.
 */

#ifndef __ASSEMBLER__
#ifndef uchar
#define uchar   unsigned char
#endif
#ifndef schar
#define schar   signed char
#endif
/* shortcuts for well defined 8 bit integer types */

#if USB_CFG_LONG_TRANSFERS  /* if more than 254 bytes transfer size required */
#   define usbMsgLen_t unsigned
#else
#   define usbMsgLen_t uchar
#endif
/* usbMsgLen_t is the data type used for transfer lengths. By default, it is
 * defined to uchar, allowing a maximum of 254 bytes (255 is reserved for
 * USB_NO_MSG below). If the usbconfig.h defines USB_CFG_LONG_TRANSFERS to 1,
 * a 16 bit data type is used, allowing up to 16384 bytes (the rest is used
 * for flags in the descriptor configuration).
 */
#define USB_NO_MSG  ((usbMsgLen_t)-1)   /* constant meaning "no message" */

struct usbRequest;  /* forward declaration */

USB_PUBLIC void usbInit(void);
/* This function must be called before interrupts are enabled and the main
 * loop is entered. We exepct that the PORT and DDR bits for D+ and D- have
 * not been changed from their default status (which is 0). If you have changed
 * them, set both back to 0 (configure them as input with no internal pull-up).
 */
USB_PUBLIC void usbPoll(void);
/* This function must be called at regular intervals from the main loop.
 * Maximum delay between calls is somewhat less than 50ms (USB timeout for
 * accepting a Setup message). Otherwise the device will not be recognized.
 * Please note that debug outputs through the UART take ~ 0.5ms per byte
 * at 19200 bps.
 */
extern uchar *usbMsgPtr;
/* This variable may be used to pass transmit data to the driver from the
 * implementation of usbFunctionWrite(). It is also used internally by the
 * driver for standard control requests.
 */
USB_PUBLIC usbMsgLen_t usbFunctionSetup(uchar data[8]);
/* This function is called when the driver receives a SETUP transaction from
 * the host which is not answered by the driver itself (in practice: class and
 * vendor requests). All control transfers start with a SETUP transaction where
 * the host communicates the parameters of the following (optional) data
 * transfer. The SETUP data is available in the 'data' parameter which can
 * (and should) be casted to 'usbRequest_t *' for a more user-friendly access
 * to parameters.
 *
 * If the SETUP indicates a control-in transfer, you should provide the
 * requested data to the driver. There are two ways to transfer this data:
 * (1) Set the global pointer 'usbMsgPtr' to the base of the static RAM data
 * block and return the length of the data in 'usbFunctionSetup()'. The driver
 * will handle the rest. Or (2) return USB_NO_MSG in 'usbFunctionSetup()'. The
 * driver will then call 'usbFunctionRead()' when data is needed. See the
 * documentation for usbFunctionRead() for details.
 *
 * If the SETUP indicates a control-out transfer, the only way to receive the
 * data from the host is through the 'usbFunctionWrite()' call. If you
 * implement this function, you must return USB_NO_MSG in 'usbFunctionSetup()'
 * to indicate that 'usbFunctionWrite()' should be used. See the documentation
 * of this function for more information. If you just want to ignore the data
 * sent by the host, return 0 in 'usbFunctionSetup()'.
 *
 * Note that calls to the functions usbFunctionRead() and usbFunctionWrite()
 * are only done if enabled by the configuration in usbconfig.h.
 */
USB_PUBLIC usbMsgLen_t usbFunctionDescriptor(struct usbRequest *rq);
/* You need to implement this function ONLY if you provide USB descriptors at
 * runtime (which is an expert feature). It is very similar to
 * usbFunctionSetup() above, but it is called only to request USB descriptor
 * data. See the documentation of usbFunctionSetup() above for more info.
 */
#if USB_CFG_HAVE_INTRIN_ENDPOINT
USB_PUBLIC void usbSetInterrupt(uchar *data, uchar len);
/* This function sets the message which will be sent during the next interrupt
 * IN transfer. The message is copied to an internal buffer and must not exceed
 * a length of 8 bytes. The message may be 0 bytes long just to indicate the
 * interrupt status to the host.
 * If you need to transfer more bytes, use a control read after the interrupt.
 */
#define usbInterruptIsReady()   (usbTxLen1 & 0x10)
/* This macro indicates whether the last interrupt message has already been
 * sent. If you set a new interrupt message before the old was sent, the
 * message already buffered will be lost.
 */
#if USB_CFG_HAVE_INTRIN_ENDPOINT3
USB_PUBLIC void usbSetInterrupt3(uchar *data, uchar len);
#define usbInterruptIsReady3()   (usbTxLen3 & 0x10)
/* Same as above for endpoint 3 */
#endif
#endif /* USB_CFG_HAVE_INTRIN_ENDPOINT */
#if USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH    /* simplified interface for backward compatibility */
#define usbHidReportDescriptor  usbDescriptorHidReport
/* should be declared as: PROGMEM char usbHidReportDescriptor[]; */
/* If you implement an HID device, you need to provide a report descriptor.
 * The HID report descriptor syntax is a bit complex. If you understand how
 * report descriptors are constructed, we recommend that you use the HID
 * Descriptor Tool from usb.org, see http://www.usb.org/developers/hidpage/.
 * Otherwise you should probably start with a working example.
 */
#endif  /* USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH */
#if USB_CFG_IMPLEMENT_FN_WRITE
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len);
/* This function is called by the driver to provide a control transfer's
 * payload data (control-out). It is called in chunks of up to 8 bytes. The
 * total count provided in the current control transfer can be obtained from
 * the 'length' property in the setup data. If an error occurred during
 * processing, return 0xff (== -1). The driver will answer the entire transfer
 * with a STALL token in this case. If you have received the entire payload
 * successfully, return 1. If you expect more data, return 0. If you don't
 * know whether the host will send more data (you should know, the total is
 * provided in the usbFunctionSetup() call!), return 1.
 * NOTE: If you return 0xff for STALL, 'usbFunctionWrite()' may still be called
 * for the remaining data. You must continue to return 0xff for STALL in these
 * calls.
 * In order to get usbFunctionWrite() called, define USB_CFG_IMPLEMENT_FN_WRITE
 * to 1 in usbconfig.h and return 0xff in usbFunctionSetup()..
 */
#endif /* USB_CFG_IMPLEMENT_FN_WRITE */
#if USB_CFG_IMPLEMENT_FN_READ
USB_PUBLIC uchar usbFunctionRead(uchar *data, uchar len);
/* This function is called by the driver to ask the application for a control
 * transfer's payload data (control-in). It is called in chunks of up to 8
 * bytes each. You should copy the data to the location given by 'data' and
 * return the actual number of bytes copied. If you return less than requested,
 * the control-in transfer is terminated. If you return 0xff, the driver aborts
 * the transfer with a STALL token.
 * In order to get usbFunctionRead() called, define USB_CFG_IMPLEMENT_FN_READ
 * to 1 in usbconfig.h and return 0xff in usbFunctionSetup()..
 */
#endif /* USB_CFG_IMPLEMENT_FN_READ */

extern uchar usbRxToken;    /* may be used in usbFunctionWriteOut() below */
#if USB_CFG_IMPLEMENT_FN_WRITEOUT
USB_PUBLIC void usbFunctionWriteOut(uchar *data, uchar len);
/* This function is called by the driver when data is received on an interrupt-
 * or bulk-out endpoint. The endpoint number can be found in the global
 * variable usbRxToken. You must define USB_CFG_IMPLEMENT_FN_WRITEOUT to 1 in
 * usbconfig.h to get this function called.
 */
#endif /* USB_CFG_IMPLEMENT_FN_WRITEOUT */
#ifdef USB_CFG_PULLUP_IOPORTNAME
#define usbDeviceConnect()      ((USB_PULLUP_DDR |= (1<<USB_CFG_PULLUP_BIT)), \
                                  (USB_PULLUP_OUT |= (1<<USB_CFG_PULLUP_BIT)))
#define usbDeviceDisconnect()   ((USB_PULLUP_DDR &= ~(1<<USB_CFG_PULLUP_BIT)), \
                                  (USB_PULLUP_OUT &= ~(1<<USB_CFG_PULLUP_BIT)))
#else /* USB_CFG_PULLUP_IOPORTNAME */
#define usbDeviceConnect()      (USBDDR &= ~(1<<USBMINUS))
#define usbDeviceDisconnect()   (USBDDR |= (1<<USBMINUS))
#endif /* USB_CFG_PULLUP_IOPORTNAME */
/* The macros usbDeviceConnect() and usbDeviceDisconnect() (intended to look
 * like a function) connect resp. disconnect the device from the host's USB.
 * If the constants USB_CFG_PULLUP_IOPORT and USB_CFG_PULLUP_BIT are defined
 * in usbconfig.h, a disconnect consists of removing the pull-up resisitor
 * from D-, otherwise the disconnect is done by brute-force pulling D- to GND.
 * This does not conform to the spec, but it works.
 * Please note that the USB interrupt must be disabled while the device is
 * in disconnected state, or the interrupt handler will hang! You can either
 * turn off the USB interrupt selectively with
 *     USB_INTR_ENABLE &= ~(1 << USB_INTR_ENABLE_BIT)
 * or use cli() to disable interrupts globally.
 */
extern unsigned usbCrc16(unsigned data, uchar len);
#define usbCrc16(data, len) usbCrc16((unsigned)(data), len)
/* This function calculates the binary complement of the data CRC used in
 * USB data packets. The value is used to build raw transmit packets.
 * You may want to use this function for data checksums or to verify received
 * data. We enforce 16 bit calling conventions for compatibility with IAR's
 * tiny memory model.
 */
extern unsigned usbCrc16Append(unsigned data, uchar len);
#define usbCrc16Append(data, len)    usbCrc16Append((unsigned)(data), len)
/* This function is equivalent to usbCrc16() above, except that it appends
 * the 2 bytes CRC (lowbyte first) in the 'data' buffer after reading 'len'
 * bytes.
 */
#if USB_CFG_HAVE_MEASURE_FRAME_LENGTH
extern unsigned usbMeasureFrameLength(void);
/* This function MUST be called IMMEDIATELY AFTER USB reset and measures 1/7 of
 * the number of CPU cycles during one USB frame minus one low speed bit
 * length. In other words: return value = 1499 * (F_CPU / 10.5 MHz)
 * Since this is a busy wait, you MUST disable all interrupts with cli() before
 * calling this function.
 * This can be used to calibrate the AVR's RC oscillator.
 */
#endif
extern uchar    usbConfiguration;
/* This value contains the current configuration set by the host. The driver
 * allows setting and querying of this variable with the USB SET_CONFIGURATION
 * and GET_CONFIGURATION requests, but does not use it otherwise.
 * You may want to reflect the "configured" status with a LED on the device or
 * switch on high power parts of the circuit only if the device is configured.
 */
#if USB_COUNT_SOF
extern volatile uchar   usbSofCount;
/* This variable is incremented on every SOF packet. It is only available if
 * the macro USB_COUNT_SOF is defined to a value != 0.
 */
#endif
#if USB_CFG_CHECK_DATA_TOGGLING
extern uchar    usbCurrentDataToken;
/* This variable can be checked in usbFunctionWrite() and usbFunctionWriteOut()
 * to ignore duplicate packets.
 */
#endif

#define USB_STRING_DESCRIPTOR_HEADER(stringLength) ((2*(stringLength)+2) | (3<<8))
/* This macro builds a descriptor header for a string descriptor given the
 * string's length. See usbdrv.c for an example how to use it.
 */
#if USB_CFG_HAVE_FLOWCONTROL
extern volatile schar   usbRxLen;
#define usbDisableAllRequests()     usbRxLen = -1
/* Must be called from usbFunctionWrite(). This macro disables all data input
 * from the USB interface. Requests from the host are answered with a NAK
 * while they are disabled.
 */
#define usbEnableAllRequests()      usbRxLen = 0
/* May only be called if requests are disabled. This macro enables input from
 * the USB interface after it has been disabled with usbDisableAllRequests().
 */
#define usbAllRequestsAreDisabled() (usbRxLen < 0)
/* Use this macro to find out whether requests are disabled. It may be needed
 * to ensure that usbEnableAllRequests() is never called when requests are
 * enabled.
 */
#endif

#define USB_SET_DATATOKEN1(token)   usbTxBuf1[0] = token
#define USB_SET_DATATOKEN3(token)   usbTxBuf3[0] = token
/* These two macros can be used by application software to reset data toggling
 * for interrupt-in endpoints 1 and 3. Since the token is toggled BEFORE
 * sending data, you must set the opposite value of the token which should come
 * first.
 */

#endif  /* __ASSEMBLER__ */


/* ------------------------------------------------------------------------- */
/* ----------------- Definitions for Descriptor Properties ----------------- */
/* ------------------------------------------------------------------------- */
/* This is advanced stuff. See usbconfig-prototype.h for more information
 * about the various methods to define USB descriptors. If you do nothing,
 * the default descriptors will be used.
 */
#define USB_PROP_IS_DYNAMIC     (1 << 14)
/* If this property is set for a descriptor, usbFunctionDescriptor() will be
 * used to obtain the particular descriptor. Data directly returned via
 * usbMsgPtr are FLASH data by default, combine (OR) with USB_PROP_IS_RAM to
 * return RAM data.
 */
#define USB_PROP_IS_RAM         (1 << 15)
/* If this property is set for a descriptor, the data is read from RAM
 * memory instead of Flash. The property is used for all methods to provide
 * external descriptors.
 */
#define USB_PROP_LENGTH(len)    ((len) & 0x3fff)
/* If a static external descriptor is used, this is the total length of the
 * descriptor in bytes.
 */

/* all descriptors which may have properties: */
#ifndef USB_CFG_DESCR_PROPS_DEVICE
#define USB_CFG_DESCR_PROPS_DEVICE                  0
#endif
#ifndef USB_CFG_DESCR_PROPS_CONFIGURATION
#define USB_CFG_DESCR_PROPS_CONFIGURATION           0
#endif
#ifndef USB_CFG_DESCR_PROPS_STRINGS
#define USB_CFG_DESCR_PROPS_STRINGS                 0
#endif
#ifndef USB_CFG_DESCR_PROPS_STRING_0
#define USB_CFG_DESCR_PROPS_STRING_0                0
#endif
#ifndef USB_CFG_DESCR_PROPS_STRING_VENDOR
#define USB_CFG_DESCR_PROPS_STRING_VENDOR           0
#endif
#ifndef USB_CFG_DESCR_PROPS_STRING_PRODUCT
#define USB_CFG_DESCR_PROPS_STRING_PRODUCT          0
#endif
#ifndef USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER
#define USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER    0
#endif
#ifndef USB_CFG_DESCR_PROPS_HID
#define USB_CFG_DESCR_PROPS_HID                     0
#endif
#if !(USB_CFG_DESCR_PROPS_HID_REPORT)
#   undef USB_CFG_DESCR_PROPS_HID_REPORT
#   if USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH /* do some backward compatibility tricks */
#       define USB_CFG_DESCR_PROPS_HID_REPORT       USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH
#   else
#       define USB_CFG_DESCR_PROPS_HID_REPORT       0
#   endif
#endif
#ifndef USB_CFG_DESCR_PROPS_UNKNOWN
#define USB_CFG_DESCR_PROPS_UNKNOWN                 0
#endif

/* ------------------ forward declaration of descriptors ------------------- */
/* If you use external static descriptors, they must be stored in global
 * arrays as declared below:
 */
#ifndef __ASSEMBLER__
extern
#if !(USB_CFG_DESCR_PROPS_DEVICE & USB_PROP_IS_RAM)
PROGMEM
#endif
const char usbDescriptorDevice[];

extern
#if !(USB_CFG_DESCR_PROPS_CONFIGURATION & USB_PROP_IS_RAM)
PROGMEM
#endif
const char usbDescriptorConfiguration[];

extern
#if !(USB_CFG_DESCR_PROPS_HID_REPORT & USB_PROP_IS_RAM)
PROGMEM
#endif
const char usbDescriptorHidReport[];

extern
#if !(USB_CFG_DESCR_PROPS_STRING_0 & USB_PROP_IS_RAM)
PROGMEM
#endif
const char usbDescriptorString0[];

extern
#if !(USB_CFG_DESCR_PROPS_STRING_VENDOR & USB_PROP_IS_RAM)
PROGMEM
#endif
const int usbDescriptorStringVendor[];

extern
#if !(USB_CFG_DESCR_PROPS_STRING_PRODUCT & USB_PROP_IS_RAM)
PROGMEM
#endif
const int usbDescriptorStringDevice[];

extern
#if !(USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER & USB_PROP_IS_RAM)
PROGMEM
#endif
const int usbDescriptorStringSerialNumber[];

#endif /* __ASSEMBLER__ */

/* ------------------------------------------------------------------------- */
/* ------------------------ General Purpose Macros ------------------------- */
/* ------------------------------------------------------------------------- */

#define USB_CONCAT(a, b)            a ## b
#define USB_CONCAT_EXPANDED(a, b)   USB_CONCAT(a, b)

#define USB_OUTPORT(name)           USB_CONCAT(PORT, name)
#define USB_INPORT(name)            USB_CONCAT(PIN, name)
#define USB_DDRPORT(name)           USB_CONCAT(DDR, name)
/* The double-define trick above lets us concatenate strings which are
 * defined by macros.
 */

/* ------------------------------------------------------------------------- */
/* ------------------------- Constant definitions -------------------------- */
/* ------------------------------------------------------------------------- */

#if !defined __ASSEMBLER__ && (!defined USB_CFG_VENDOR_ID || !defined USB_CFG_DEVICE_ID)
#warning "You should define USB_CFG_VENDOR_ID and USB_CFG_DEVICE_ID in usbconfig.h"
/* If the user has not defined IDs, we default to obdev's free IDs.
 * See USB-IDs-for-free.txt for details.
 */
#endif

/* make sure we have a VID and PID defined, byte order is lowbyte, highbyte */
#ifndef USB_CFG_VENDOR_ID
#   define  USB_CFG_VENDOR_ID   0xc0, 0x16  /* = 0x16c0 = 5824 = voti.nl */
#endif

#ifndef USB_CFG_DEVICE_ID
#   if USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH
#       define USB_CFG_DEVICE_ID    0xdf, 0x05  /* = 0x5df = 1503, shared PID for HIDs */
#   elif USB_CFG_INTERFACE_CLASS == 2
#       define USB_CFG_DEVICE_ID    0xe1, 0x05  /* = 0x5e1 = 1505, shared PID for CDC Modems */
#   else
#       define USB_CFG_DEVICE_ID    0xdc, 0x05  /* = 0x5dc = 1500, obdev's free PID */
#   endif
#endif

/* Derive Output, Input and DataDirection ports from port names */
#ifndef USB_CFG_IOPORTNAME
#error "You must define USB_CFG_IOPORTNAME in usbconfig.h, see usbconfig-prototype.h"
#endif

#define USBOUT          USB_OUTPORT(USB_CFG_IOPORTNAME)
#define USB_PULLUP_OUT  USB_OUTPORT(USB_CFG_PULLUP_IOPORTNAME)
#define USBIN           USB_INPORT(USB_CFG_IOPORTNAME)
#define USBDDR          USB_DDRPORT(USB_CFG_IOPORTNAME)
#define USB_PULLUP_DDR  USB_DDRPORT(USB_CFG_PULLUP_IOPORTNAME)

#define USBMINUS    USB_CFG_DMINUS_BIT
#define USBPLUS     USB_CFG_DPLUS_BIT
#define USBIDLE     (1<<USB_CFG_DMINUS_BIT) /* value representing J state */
#define USBMASK     ((1<<USB_CFG_DPLUS_BIT) | (1<<USB_CFG_DMINUS_BIT))  /* mask for USB I/O bits */

/* defines for backward compatibility with older driver versions: */
#define USB_CFG_IOPORT          USB_OUTPORT(USB_CFG_IOPORTNAME)
#ifdef USB_CFG_PULLUP_IOPORTNAME
#define USB_CFG_PULLUP_IOPORT   USB_OUTPORT(USB_CFG_PULLUP_IOPORTNAME)
#endif

#ifndef USB_CFG_EP3_NUMBER  /* if not defined in usbconfig.h */
#define USB_CFG_EP3_NUMBER  3
#endif

#ifndef USB_CFG_HAVE_INTRIN_ENDPOINT3
#define USB_CFG_HAVE_INTRIN_ENDPOINT3   0
#endif

#define USB_BUFSIZE     11  /* PID, 8 bytes data, 2 bytes CRC */

/* ----- Try to find registers and bits responsible for ext interrupt 0 ----- */

#ifndef USB_INTR_CFG    /* allow user to override our default */
#   if defined  EICRA
#       define USB_INTR_CFG EICRA
#   else
#       define USB_INTR_CFG MCUCR
#   endif
#endif
#ifndef USB_INTR_CFG_SET    /* allow user to override our default */
#   if defined(USB_COUNT_SOF) || defined(USB_SOF_HOOK)
#       define USB_INTR_CFG_SET (1 << ISC01)                    /* cfg for falling edge */
        /* If any SOF logic is used, the interrupt must be wired to D- where
         * we better trigger on falling edge
         */
#   else
#       define USB_INTR_CFG_SET ((1 << ISC00) | (1 << ISC01))   /* cfg for rising edge */
#   endif
#endif
#ifndef USB_INTR_CFG_CLR    /* allow user to override our default */
#   define USB_INTR_CFG_CLR 0    /* no bits to clear */
#endif

#ifndef USB_INTR_ENABLE     /* allow user to override our default */
#   if defined GIMSK
#       define USB_INTR_ENABLE  GIMSK
#   elif defined EIMSK
#       define USB_INTR_ENABLE  EIMSK
#   else
#       define USB_INTR_ENABLE  GICR
#   endif
#endif
#ifndef USB_INTR_ENABLE_BIT /* allow user to override our default */
#   define USB_INTR_ENABLE_BIT  INT0
#endif

#ifndef USB_INTR_PENDING    /* allow user to override our default */
#   if defined  EIFR
#       define USB_INTR_PENDING EIFR
#   else
#       define USB_INTR_PENDING GIFR
#   endif
#endif
#ifndef USB_INTR_PENDING_BIT    /* allow user to override our default */
#   define USB_INTR_PENDING_BIT INTF0
#endif

/*
The defines above don't work for the following chips
at90c8534: no ISC0?, no PORTB, can't find a data sheet
at86rf401: no PORTB, no MCUCR etc, low clock rate
atmega103: no ISC0? (maybe omission in header, can't find data sheet)
atmega603: not defined in avr-libc
at43usb320, at43usb355, at76c711: have USB anyway
at94k: is different...

at90s1200, attiny11, attiny12, attiny15, attiny28: these have no RAM
*/

/* ------------------------------------------------------------------------- */
/* ----------------- USB Specification Constants and Types ----------------- */
/* ------------------------------------------------------------------------- */

/* USB Token values */
#define USBPID_SETUP    0x2d
#define USBPID_OUT      0xe1
#define USBPID_IN       0x69
#define USBPID_DATA0    0xc3
#define USBPID_DATA1    0x4b

#define USBPID_ACK      0xd2
#define USBPID_NAK      0x5a
#define USBPID_STALL    0x1e

#ifndef USB_INITIAL_DATATOKEN
#define USB_INITIAL_DATATOKEN   USBPID_DATA1
#endif

#ifndef __ASSEMBLER__

typedef struct usbTxStatus{
    volatile uchar   len;
    uchar   buffer[USB_BUFSIZE];
}usbTxStatus_t;

extern usbTxStatus_t   usbTxStatus1, usbTxStatus3;
#define usbTxLen1   usbTxStatus1.len
#define usbTxBuf1   usbTxStatus1.buffer
#define usbTxLen3   usbTxStatus3.len
#define usbTxBuf3   usbTxStatus3.buffer


typedef union usbWord{
    unsigned    word;
    uchar       bytes[2];
}usbWord_t;

typedef struct usbRequest{
    uchar       bmRequestType;
    uchar       bRequest;
    usbWord_t   wValue;
    usbWord_t   wIndex;
    usbWord_t   wLength;
}usbRequest_t;
/* This structure matches the 8 byte setup request */
#endif

/* bmRequestType field in USB setup:
 * d t t r r r r r, where
 * d ..... direction: 0=host->device, 1=device->host
 * t ..... type: 0=standard, 1=class, 2=vendor, 3=reserved
 * r ..... recipient: 0=device, 1=interface, 2=endpoint, 3=other
 */

/* USB setup recipient values */
#define USBRQ_RCPT_MASK         0x1f
#define USBRQ_RCPT_DEVICE       0
#define USBRQ_RCPT_INTERFACE    1
#define USBRQ_RCPT_ENDPOINT     2

/* USB request type values */
#define USBRQ_TYPE_MASK         0x60
#define USBRQ_TYPE_STANDARD     (0<<5)
#define USBRQ_TYPE_CLASS        (1<<5)
#define USBRQ_TYPE_VENDOR       (2<<5)

/* USB direction values: */
#define USBRQ_DIR_MASK              0x80
#define USBRQ_DIR_HOST_TO_DEVICE    (0<<7)
#define USBRQ_DIR_DEVICE_TO_HOST    (1<<7)

/* USB Standard Requests */
#define USBRQ_GET_STATUS        0
#define USBRQ_CLEAR_FEATURE     1
#define USBRQ_SET_FEATURE       3
#define USBRQ_SET_ADDRESS       5
#define USBRQ_GET_DESCRIPTOR    6
#define USBRQ_SET_DESCRIPTOR    7
#define USBRQ_GET_CONFIGURATION 8
#define USBRQ_SET_CONFIGURATION 9
#define USBRQ_GET_INTERFACE     10
#define USBRQ_SET_INTERFACE     11
#define USBRQ_SYNCH_FRAME       12

/* USB descriptor constants */
#define USBDESCR_DEVICE         1
#define USBDESCR_CONFIG         2
#define USBDESCR_STRING         3
#define USBDESCR_INTERFACE      4
#define USBDESCR_ENDPOINT       5
#define USBDESCR_HID            0x21
#define USBDESCR_HID_REPORT     0x22
#define USBDESCR_HID_PHYS       0x23

//#define USBATTR_BUSPOWER        0x80  // USB 1.1 does not define this value any more
#define USBATTR_SELFPOWER       0x40
#define USBATTR_REMOTEWAKE      0x20

/* USB HID Requests */
#define USBRQ_HID_GET_REPORT    0x01
#define USBRQ_HID_GET_IDLE      0x02
#define USBRQ_HID_GET_PROTOCOL  0x03
#define USBRQ_HID_SET_REPORT    0x09
#define USBRQ_HID_SET_IDLE      0x0a
#define USBRQ_HID_SET_PROTOCOL  0x0b

/* ------------------------------------------------------------------------- */

#endif /* __usbdrv_h_included__ */
