/* Name: usbdrv.c
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Christian Starkjohann
 * Creation Date: 2004-12-29
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: usbdrv.c 791 2010-07-15 15:56:13Z cs $
 */

#include "usbportability.h"
#include "usbdrv.h"
#include "oddebug.h"

/*
General Description:
This module implements the C-part of the USB driver. See usbdrv.h for a
documentation of the entire driver.
*/

/* ------------------------------------------------------------------------- */

/* raw USB registers / interface to assembler code: */
uchar usbRxBuf[2*USB_BUFSIZE];  /* raw RX buffer: PID, 8 bytes data, 2 bytes CRC */
uchar       usbInputBufOffset;  /* offset in usbRxBuf used for low level receiving */
uchar       usbDeviceAddr;      /* assigned during enumeration, defaults to 0 */
uchar       usbNewDeviceAddr;   /* device ID which should be set after status phase */
uchar       usbConfiguration;   /* currently selected configuration. Administered by driver, but not used */
volatile schar usbRxLen;        /* = 0; number of bytes in usbRxBuf; 0 means free, -1 for flow control */
uchar       usbCurrentTok;      /* last token received or endpoint number for last OUT token if != 0 */
uchar       usbRxToken;         /* token for data we received; or endpont number for last OUT */
volatile uchar usbTxLen = USBPID_NAK;   /* number of bytes to transmit with next IN token or handshake token */
uchar       usbTxBuf[USB_BUFSIZE];/* data to transmit with next IN, free if usbTxLen contains handshake token */
#if USB_COUNT_SOF
volatile uchar  usbSofCount;    /* incremented by assembler module every SOF */
#endif
#if USB_CFG_HAVE_INTRIN_ENDPOINT && !USB_CFG_SUPPRESS_INTR_CODE
usbTxStatus_t  usbTxStatus1;
#   if USB_CFG_HAVE_INTRIN_ENDPOINT3
usbTxStatus_t  usbTxStatus3;
#   endif
#endif
#if USB_CFG_CHECK_DATA_TOGGLING
uchar       usbCurrentDataToken;/* when we check data toggling to ignore duplicate packets */
#endif

/* USB status registers / not shared with asm code */
uchar               *usbMsgPtr;     /* data to transmit next -- ROM or RAM address */
static usbMsgLen_t  usbMsgLen = USB_NO_MSG; /* remaining number of bytes */
static uchar        usbMsgFlags;    /* flag values see below */

#define USB_FLG_MSGPTR_IS_ROM   (1<<6)
#define USB_FLG_USE_USER_RW     (1<<7)

/*
optimizing hints:
- do not post/pre inc/dec integer values in operations
- assign value of USB_READ_FLASH() to register variables and don't use side effects in arg
- use narrow scope for variables which should be in X/Y/Z register
- assign char sized expressions to variables to force 8 bit arithmetics
*/

/* -------------------------- String Descriptors --------------------------- */

#if USB_CFG_DESCR_PROPS_STRINGS == 0

#if USB_CFG_DESCR_PROPS_STRING_0 == 0
#undef USB_CFG_DESCR_PROPS_STRING_0
#define USB_CFG_DESCR_PROPS_STRING_0    sizeof(usbDescriptorString0)
const PROGMEM char usbDescriptorString0[] = { /* language descriptor */
    4,          /* sizeof(usbDescriptorString0): length of descriptor in bytes */
    3,          /* descriptor type */
    0x09, 0x04, /* language index (0x0409 = US-English) */
};
#endif

#if USB_CFG_DESCR_PROPS_STRING_VENDOR == 0 && USB_CFG_VENDOR_NAME_LEN
#undef USB_CFG_DESCR_PROPS_STRING_VENDOR
#define USB_CFG_DESCR_PROPS_STRING_VENDOR   sizeof(usbDescriptorStringVendor)
const PROGMEM int  usbDescriptorStringVendor[] = {
    USB_STRING_DESCRIPTOR_HEADER(USB_CFG_VENDOR_NAME_LEN),
    USB_CFG_VENDOR_NAME
};
#endif

#if USB_CFG_DESCR_PROPS_STRING_PRODUCT == 0 && USB_CFG_DEVICE_NAME_LEN
#undef USB_CFG_DESCR_PROPS_STRING_PRODUCT
#define USB_CFG_DESCR_PROPS_STRING_PRODUCT   sizeof(usbDescriptorStringDevice)
const PROGMEM int  usbDescriptorStringDevice[] = {
    USB_STRING_DESCRIPTOR_HEADER(USB_CFG_DEVICE_NAME_LEN),
    USB_CFG_DEVICE_NAME
};
#endif

#if USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER == 0 && USB_CFG_SERIAL_NUMBER_LEN
#undef USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER
#define USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER    sizeof(usbDescriptorStringSerialNumber)
PROGMEM int usbDescriptorStringSerialNumber[] = {
    USB_STRING_DESCRIPTOR_HEADER(USB_CFG_SERIAL_NUMBER_LEN),
    USB_CFG_SERIAL_NUMBER
};
#endif

#endif  /* USB_CFG_DESCR_PROPS_STRINGS == 0 */

/* --------------------------- Device Descriptor --------------------------- */

#if USB_CFG_DESCR_PROPS_DEVICE == 0
#undef USB_CFG_DESCR_PROPS_DEVICE
#define USB_CFG_DESCR_PROPS_DEVICE  sizeof(usbDescriptorDevice)
const PROGMEM char usbDescriptorDevice[] = {    /* USB device descriptor */
    18,         /* sizeof(usbDescriptorDevice): length of descriptor in bytes */
    USBDESCR_DEVICE,        /* descriptor type */
    0x10, 0x01,             /* USB version supported */
    USB_CFG_DEVICE_CLASS,
    USB_CFG_DEVICE_SUBCLASS,
    0,                      /* protocol */
    8,                      /* max packet size */
    /* the following two casts affect the first byte of the constant only, but
     * that's sufficient to avoid a warning with the default values.
     */
    (char)USB_CFG_VENDOR_ID,/* 2 bytes */
    (char)USB_CFG_DEVICE_ID,/* 2 bytes */
    USB_CFG_DEVICE_VERSION, /* 2 bytes */
    USB_CFG_DESCR_PROPS_STRING_VENDOR != 0 ? 1 : 0,         /* manufacturer string index */
    USB_CFG_DESCR_PROPS_STRING_PRODUCT != 0 ? 2 : 0,        /* product string index */
    USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER != 0 ? 3 : 0,  /* serial number string index */
    1,          /* number of configurations */
};
#endif

/* ----------------------- Configuration Descriptor ------------------------ */

#if USB_CFG_DESCR_PROPS_HID_REPORT != 0 && USB_CFG_DESCR_PROPS_HID == 0
#undef USB_CFG_DESCR_PROPS_HID
#define USB_CFG_DESCR_PROPS_HID     9   /* length of HID descriptor in config descriptor below */
#endif

#if USB_CFG_DESCR_PROPS_CONFIGURATION == 0
#undef USB_CFG_DESCR_PROPS_CONFIGURATION
#define USB_CFG_DESCR_PROPS_CONFIGURATION   sizeof(usbDescriptorConfiguration)
PROGMEM char usbDescriptorConfiguration[] = {    /* USB configuration descriptor */
    9,          /* sizeof(usbDescriptorConfiguration): length of descriptor in bytes */
    USBDESCR_CONFIG,    /* descriptor type */
    18 + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT3 +
                (USB_CFG_DESCR_PROPS_HID & 0xff), 0,
                /* total length of data returned (including inlined descriptors) */
    1,          /* number of interfaces in this configuration */
    1,          /* index of this configuration */
    0,          /* configuration name string index */
#if USB_CFG_IS_SELF_POWERED
    (1 << 7) | USBATTR_SELFPOWER,       /* attributes */
#else
    (1 << 7),                           /* attributes */
#endif
    USB_CFG_MAX_BUS_POWER/2,            /* max USB current in 2mA units */
/* interface descriptor follows inline: */
    9,          /* sizeof(usbDescrInterface): length of descriptor in bytes */
    USBDESCR_INTERFACE, /* descriptor type */
    0,          /* index of this interface */
    0,          /* alternate setting for this interface */
    USB_CFG_HAVE_INTRIN_ENDPOINT + USB_CFG_HAVE_INTRIN_ENDPOINT3, /* endpoints excl 0: number of endpoint descriptors to follow */
    USB_CFG_INTERFACE_CLASS,
    USB_CFG_INTERFACE_SUBCLASS,
    USB_CFG_INTERFACE_PROTOCOL,
    0,          /* string index for interface */
#if (USB_CFG_DESCR_PROPS_HID & 0xff)    /* HID descriptor */
    9,          /* sizeof(usbDescrHID): length of descriptor in bytes */
    USBDESCR_HID,   /* descriptor type: HID */
    0x01, 0x01, /* BCD representation of HID version */
    0x00,       /* target country code */
    0x01,       /* number of HID Report (or other HID class) Descriptor infos to follow */
    0x22,       /* descriptor type: report */
    USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH, 0,  /* total length of report descriptor */
#endif
#if USB_CFG_HAVE_INTRIN_ENDPOINT    /* endpoint descriptor for endpoint 1 */
    7,          /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,  /* descriptor type = endpoint */
    (char)0x81, /* IN endpoint number 1 */
    0x03,       /* attrib: Interrupt endpoint */
    8, 0,       /* maximum packet size */
    USB_CFG_INTR_POLL_INTERVAL, /* in ms */
#endif
#if USB_CFG_HAVE_INTRIN_ENDPOINT3   /* endpoint descriptor for endpoint 3 */
    7,          /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,  /* descriptor type = endpoint */
    (char)(0x80 | USB_CFG_EP3_NUMBER), /* IN endpoint number 3 */
    0x03,       /* attrib: Interrupt endpoint */
    8, 0,       /* maximum packet size */
    USB_CFG_INTR_POLL_INTERVAL, /* in ms */
#endif
};
#endif

/* ------------------------------------------------------------------------- */

static inline void  usbResetDataToggling(void)
{
#if USB_CFG_HAVE_INTRIN_ENDPOINT && !USB_CFG_SUPPRESS_INTR_CODE
    USB_SET_DATATOKEN1(USB_INITIAL_DATATOKEN);  /* reset data toggling for interrupt endpoint */
#   if USB_CFG_HAVE_INTRIN_ENDPOINT3
    USB_SET_DATATOKEN3(USB_INITIAL_DATATOKEN);  /* reset data toggling for interrupt endpoint */
#   endif
#endif
}

static inline void  usbResetStall(void)
{
#if USB_CFG_IMPLEMENT_HALT && USB_CFG_HAVE_INTRIN_ENDPOINT
        usbTxLen1 = USBPID_NAK;
#if USB_CFG_HAVE_INTRIN_ENDPOINT3
        usbTxLen3 = USBPID_NAK;
#endif
#endif
}

/* ------------------------------------------------------------------------- */

#if !USB_CFG_SUPPRESS_INTR_CODE
#if USB_CFG_HAVE_INTRIN_ENDPOINT
static void usbGenericSetInterrupt(uchar *data, uchar len, usbTxStatus_t *txStatus)
{
uchar   *p;
char    i;

#if USB_CFG_IMPLEMENT_HALT
    if(usbTxLen1 == USBPID_STALL)
        return;
#endif
    if(txStatus->len & 0x10){   /* packet buffer was empty */
        txStatus->buffer[0] ^= USBPID_DATA0 ^ USBPID_DATA1; /* toggle token */
    }else{
        txStatus->len = USBPID_NAK; /* avoid sending outdated (overwritten) interrupt data */
    }
    p = txStatus->buffer + 1;
    i = len;
    do{                         /* if len == 0, we still copy 1 byte, but that's no problem */
        *p++ = *data++;
    }while(--i > 0);            /* loop control at the end is 2 bytes shorter than at beginning */
    usbCrc16Append(&txStatus->buffer[1], len);
    txStatus->len = len + 4;    /* len must be given including sync byte */
    DBG2(0x21 + (((int)txStatus >> 3) & 3), txStatus->buffer, len + 3);
}

USB_PUBLIC void usbSetInterrupt(uchar *data, uchar len)
{
    usbGenericSetInterrupt(data, len, &usbTxStatus1);
}
#endif

#if USB_CFG_HAVE_INTRIN_ENDPOINT3
USB_PUBLIC void usbSetInterrupt3(uchar *data, uchar len)
{
    usbGenericSetInterrupt(data, len, &usbTxStatus3);
}
#endif
#endif /* USB_CFG_SUPPRESS_INTR_CODE */

/* ------------------ utilities for code following below ------------------- */

/* Use defines for the switch statement so that we can choose between an
 * if()else if() and a switch/case based implementation. switch() is more
 * efficient for a LARGE set of sequential choices, if() is better in all other
 * cases.
 */
#if USB_CFG_USE_SWITCH_STATEMENT
#   define SWITCH_START(cmd)       switch(cmd){{
#   define SWITCH_CASE(value)      }break; case (value):{
#   define SWITCH_CASE2(v1,v2)     }break; case (v1): case(v2):{
#   define SWITCH_CASE3(v1,v2,v3)  }break; case (v1): case(v2): case(v3):{
#   define SWITCH_DEFAULT          }break; default:{
#   define SWITCH_END              }}
#else
#   define SWITCH_START(cmd)       {uchar _cmd = cmd; if(0){
#   define SWITCH_CASE(value)      }else if(_cmd == (value)){
#   define SWITCH_CASE2(v1,v2)     }else if(_cmd == (v1) || _cmd == (v2)){
#   define SWITCH_CASE3(v1,v2,v3)  }else if(_cmd == (v1) || _cmd == (v2) || (_cmd == v3)){
#   define SWITCH_DEFAULT          }else{
#   define SWITCH_END              }}
#endif

#ifndef USB_RX_USER_HOOK
#define USB_RX_USER_HOOK(data, len)
#endif
#ifndef USB_SET_ADDRESS_HOOK
#define USB_SET_ADDRESS_HOOK()
#endif

/* ------------------------------------------------------------------------- */

/* We use if() instead of #if in the macro below because #if can't be used
 * in macros and the compiler optimizes constant conditions anyway.
 * This may cause problems with undefined symbols if compiled without
 * optimizing!
 */
#define GET_DESCRIPTOR(cfgProp, staticName)         \
    if(cfgProp){                                    \
        if((cfgProp) & USB_PROP_IS_RAM)             \
            flags = 0;                              \
        if((cfgProp) & USB_PROP_IS_DYNAMIC){        \
            len = usbFunctionDescriptor(rq);        \
        }else{                                      \
            len = USB_PROP_LENGTH(cfgProp);         \
            usbMsgPtr = (uchar *)(staticName);      \
        }                                           \
    }

/* usbDriverDescriptor() is similar to usbFunctionDescriptor(), but used
 * internally for all types of descriptors.
 */
static inline usbMsgLen_t usbDriverDescriptor(usbRequest_t *rq)
{
usbMsgLen_t len = 0;
uchar       flags = USB_FLG_MSGPTR_IS_ROM;

    SWITCH_START(rq->wValue.bytes[1])
    SWITCH_CASE(USBDESCR_DEVICE)    /* 1 */
        GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_DEVICE, usbDescriptorDevice)
    SWITCH_CASE(USBDESCR_CONFIG)    /* 2 */
        GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_CONFIGURATION, usbDescriptorConfiguration)
    SWITCH_CASE(USBDESCR_STRING)    /* 3 */
#if USB_CFG_DESCR_PROPS_STRINGS & USB_PROP_IS_DYNAMIC
        if(USB_CFG_DESCR_PROPS_STRINGS & USB_PROP_IS_RAM)
            flags = 0;
        len = usbFunctionDescriptor(rq);
#else   /* USB_CFG_DESCR_PROPS_STRINGS & USB_PROP_IS_DYNAMIC */
        SWITCH_START(rq->wValue.bytes[0])
        SWITCH_CASE(0)
            GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_STRING_0, usbDescriptorString0)
        SWITCH_CASE(1)
            GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_STRING_VENDOR, usbDescriptorStringVendor)
        SWITCH_CASE(2)
            GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_STRING_PRODUCT, usbDescriptorStringDevice)
        SWITCH_CASE(3)
            GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER, usbDescriptorStringSerialNumber)
        SWITCH_DEFAULT
            if(USB_CFG_DESCR_PROPS_UNKNOWN & USB_PROP_IS_DYNAMIC){
                len = usbFunctionDescriptor(rq);
            }
        SWITCH_END
#endif  /* USB_CFG_DESCR_PROPS_STRINGS & USB_PROP_IS_DYNAMIC */
#if USB_CFG_DESCR_PROPS_HID_REPORT  /* only support HID descriptors if enabled */
    SWITCH_CASE(USBDESCR_HID)       /* 0x21 */
        GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_HID, usbDescriptorConfiguration + 18)
    SWITCH_CASE(USBDESCR_HID_REPORT)/* 0x22 */
        GET_DESCRIPTOR(USB_CFG_DESCR_PROPS_HID_REPORT, usbDescriptorHidReport)
#endif
    SWITCH_DEFAULT
        if(USB_CFG_DESCR_PROPS_UNKNOWN & USB_PROP_IS_DYNAMIC){
            len = usbFunctionDescriptor(rq);
        }
    SWITCH_END
    usbMsgFlags = flags;
    return len;
}

/* ------------------------------------------------------------------------- */

/* usbDriverSetup() is similar to usbFunctionSetup(), but it's used for
 * standard requests instead of class and custom requests.
 */
static inline usbMsgLen_t usbDriverSetup(usbRequest_t *rq)
{
uchar   len  = 0, *dataPtr = usbTxBuf + 9;  /* there are 2 bytes free space at the end of the buffer */
uchar   value = rq->wValue.bytes[0];
#if USB_CFG_IMPLEMENT_HALT
uchar   index = rq->wIndex.bytes[0];
#endif

    dataPtr[0] = 0; /* default reply common to USBRQ_GET_STATUS and USBRQ_GET_INTERFACE */
    SWITCH_START(rq->bRequest)
    SWITCH_CASE(USBRQ_GET_STATUS)           /* 0 */
        uchar recipient = rq->bmRequestType & USBRQ_RCPT_MASK;  /* assign arith ops to variables to enforce byte size */
        if(USB_CFG_IS_SELF_POWERED && recipient == USBRQ_RCPT_DEVICE)
            dataPtr[0] =  USB_CFG_IS_SELF_POWERED;
#if USB_CFG_IMPLEMENT_HALT
        if(recipient == USBRQ_RCPT_ENDPOINT && index == 0x81)   /* request status for endpoint 1 */
            dataPtr[0] = usbTxLen1 == USBPID_STALL;
#endif
        dataPtr[1] = 0;
        len = 2;
#if USB_CFG_IMPLEMENT_HALT
    SWITCH_CASE2(USBRQ_CLEAR_FEATURE, USBRQ_SET_FEATURE)    /* 1, 3 */
        if(value == 0 && index == 0x81){    /* feature 0 == HALT for endpoint == 1 */
            usbTxLen1 = rq->bRequest == USBRQ_CLEAR_FEATURE ? USBPID_NAK : USBPID_STALL;
            usbResetDataToggling();
        }
#endif
    SWITCH_CASE(USBRQ_SET_ADDRESS)          /* 5 */
        usbNewDeviceAddr = value;
        USB_SET_ADDRESS_HOOK();
    SWITCH_CASE(USBRQ_GET_DESCRIPTOR)       /* 6 */
        len = usbDriverDescriptor(rq);
        goto skipMsgPtrAssignment;
    SWITCH_CASE(USBRQ_GET_CONFIGURATION)    /* 8 */
        dataPtr = &usbConfiguration;  /* send current configuration value */
        len = 1;
    SWITCH_CASE(USBRQ_SET_CONFIGURATION)    /* 9 */
        usbConfiguration = value;
        usbResetStall();
    SWITCH_CASE(USBRQ_GET_INTERFACE)        /* 10 */
        len = 1;
#if USB_CFG_HAVE_INTRIN_ENDPOINT && !USB_CFG_SUPPRESS_INTR_CODE
    SWITCH_CASE(USBRQ_SET_INTERFACE)        /* 11 */
        usbResetDataToggling();
        usbResetStall();
#endif
    SWITCH_DEFAULT                          /* 7=SET_DESCRIPTOR, 12=SYNC_FRAME */
        /* Should we add an optional hook here? */
    SWITCH_END
    usbMsgPtr = dataPtr;
skipMsgPtrAssignment:
    return len;
}

/* ------------------------------------------------------------------------- */

/* usbProcessRx() is called for every message received by the interrupt
 * routine. It distinguishes between SETUP and DATA packets and processes
 * them accordingly.
 */
static inline void usbProcessRx(uchar *data, uchar len)
{
usbRequest_t    *rq = (void *)data;

/* usbRxToken can be:
 * 0x2d 00101101 (USBPID_SETUP for setup data)
 * 0xe1 11100001 (USBPID_OUT: data phase of setup transfer)
 * 0...0x0f for OUT on endpoint X
 */
    DBG2(0x10 + (usbRxToken & 0xf), data, len + 2); /* SETUP=1d, SETUP-DATA=11, OUTx=1x */
    USB_RX_USER_HOOK(data, len)
#if USB_CFG_IMPLEMENT_FN_WRITEOUT
    if(usbRxToken < 0x10){  /* OUT to endpoint != 0: endpoint number in usbRxToken */
        usbFunctionWriteOut(data, len);
        return;
    }
#endif
    if(usbRxToken == (uchar)USBPID_SETUP){
        if(len != 8)    /* Setup size must be always 8 bytes. Ignore otherwise. */
            return;
        usbMsgLen_t replyLen;
        usbTxBuf[0] = USBPID_DATA0;         /* initialize data toggling */
        usbTxLen = USBPID_NAK;              /* abort pending transmit */
        usbMsgFlags = 0;
        uchar type = rq->bmRequestType & USBRQ_TYPE_MASK;
        if(type != USBRQ_TYPE_STANDARD){    /* standard requests are handled by driver */
            replyLen = usbFunctionSetup(data);
        }else{
            replyLen = usbDriverSetup(rq);
        }
#if USB_CFG_IMPLEMENT_FN_READ || USB_CFG_IMPLEMENT_FN_WRITE
        if(replyLen == USB_NO_MSG){         /* use user-supplied read/write function */
            /* do some conditioning on replyLen, but on IN transfers only */
            if((rq->bmRequestType & USBRQ_DIR_MASK) != USBRQ_DIR_HOST_TO_DEVICE){
                if(sizeof(replyLen) < sizeof(rq->wLength.word)){ /* help compiler with optimizing */
                    replyLen = rq->wLength.bytes[0];
                }else{
                    replyLen = rq->wLength.word;
                }
            }
            usbMsgFlags = USB_FLG_USE_USER_RW;
        }else   /* The 'else' prevents that we limit a replyLen of USB_NO_MSG to the maximum transfer len. */
#endif
        if(sizeof(replyLen) < sizeof(rq->wLength.word)){ /* help compiler with optimizing */
            if(!rq->wLength.bytes[1] && replyLen > rq->wLength.bytes[0])    /* limit length to max */
                replyLen = rq->wLength.bytes[0];
        }else{
            if(replyLen > rq->wLength.word)     /* limit length to max */
                replyLen = rq->wLength.word;
        }
        usbMsgLen = replyLen;
    }else{  /* usbRxToken must be USBPID_OUT, which means data phase of setup (control-out) */
#if USB_CFG_IMPLEMENT_FN_WRITE
        if(usbMsgFlags & USB_FLG_USE_USER_RW){
            uchar rval = usbFunctionWrite(data, len);
            if(rval == 0xff){   /* an error occurred */
                usbTxLen = USBPID_STALL;
            }else if(rval != 0){    /* This was the final package */
                usbMsgLen = 0;  /* answer with a zero-sized data packet */
            }
        }
#endif
    }
}

/* ------------------------------------------------------------------------- */

/* This function is similar to usbFunctionRead(), but it's also called for
 * data handled automatically by the driver (e.g. descriptor reads).
 */
static uchar usbDeviceRead(uchar *data, uchar len)
{
    if(len > 0){    /* don't bother app with 0 sized reads */
#if USB_CFG_IMPLEMENT_FN_READ
        if(usbMsgFlags & USB_FLG_USE_USER_RW){
            len = usbFunctionRead(data, len);
        }else
#endif
        {
            uchar i = len, *r = usbMsgPtr;
            if(usbMsgFlags & USB_FLG_MSGPTR_IS_ROM){    /* ROM data */
                do{
                    uchar c = USB_READ_FLASH(r);    /* assign to char size variable to enforce byte ops */
                    *data++ = c;
                    r++;
                }while(--i);
            }else{  /* RAM data */
                do{
                    *data++ = *r++;
                }while(--i);
            }
            usbMsgPtr = r;
        }
    }
    return len;
}

/* ------------------------------------------------------------------------- */

/* usbBuildTxBlock() is called when we have data to transmit and the
 * interrupt routine's transmit buffer is empty.
 */
static inline void usbBuildTxBlock(void)
{
usbMsgLen_t wantLen;
uchar       len;

    wantLen = usbMsgLen;
    if(wantLen > 8)
        wantLen = 8;
    usbMsgLen -= wantLen;
    usbTxBuf[0] ^= USBPID_DATA0 ^ USBPID_DATA1; /* DATA toggling */
    len = usbDeviceRead(usbTxBuf + 1, wantLen);
    if(len <= 8){           /* valid data packet */
        usbCrc16Append(&usbTxBuf[1], len);
        len += 4;           /* length including sync byte */
        if(len < 12)        /* a partial package identifies end of message */
            usbMsgLen = USB_NO_MSG;
    }else{
        len = USBPID_STALL;   /* stall the endpoint */
        usbMsgLen = USB_NO_MSG;
    }
    usbTxLen = len;
    DBG2(0x20, usbTxBuf, len-1);
}

/* ------------------------------------------------------------------------- */

static inline void usbHandleResetHook(uchar notResetState)
{
#ifdef USB_RESET_HOOK
static uchar    wasReset;
uchar           isReset = !notResetState;

    if(wasReset != isReset){
        USB_RESET_HOOK(isReset);
        wasReset = isReset;
    }
#endif
}

/* ------------------------------------------------------------------------- */

USB_PUBLIC void usbPoll(void)
{
schar   len;
uchar   i;

    len = usbRxLen - 3;
    if(len >= 0){
/* We could check CRC16 here -- but ACK has already been sent anyway. If you
 * need data integrity checks with this driver, check the CRC in your app
 * code and report errors back to the host. Since the ACK was already sent,
 * retries must be handled on application level.
 * unsigned crc = usbCrc16(buffer + 1, usbRxLen - 3);
 */
        usbProcessRx(usbRxBuf + USB_BUFSIZE + 1 - usbInputBufOffset, len);
#if USB_CFG_HAVE_FLOWCONTROL
        if(usbRxLen > 0)    /* only mark as available if not inactivated */
            usbRxLen = 0;
#else
        usbRxLen = 0;       /* mark rx buffer as available */
#endif
    }
    if(usbTxLen & 0x10){    /* transmit system idle */
        if(usbMsgLen != USB_NO_MSG){    /* transmit data pending? */
            usbBuildTxBlock();
        }
    }
    for(i = 20; i > 0; i--){
        uchar usbLineStatus = USBIN & USBMASK;
        if(usbLineStatus != 0)  /* SE0 has ended */
            goto isNotReset;
    }
    /* RESET condition, called multiple times during reset */
    usbNewDeviceAddr = 0;
    usbDeviceAddr = 0;
    usbResetStall();
    DBG1(0xff, 0, 0);
isNotReset:
    usbHandleResetHook(i);
}

/* ------------------------------------------------------------------------- */

USB_PUBLIC void usbInit(void)
{
#if USB_INTR_CFG_SET != 0
    USB_INTR_CFG |= USB_INTR_CFG_SET;
#endif
#if USB_INTR_CFG_CLR != 0
    USB_INTR_CFG &= ~(USB_INTR_CFG_CLR);
#endif
    USB_INTR_ENABLE |= (1 << USB_INTR_ENABLE_BIT);
    usbResetDataToggling();
#if USB_CFG_HAVE_INTRIN_ENDPOINT && !USB_CFG_SUPPRESS_INTR_CODE
    usbTxLen1 = USBPID_NAK;
#if USB_CFG_HAVE_INTRIN_ENDPOINT3
    usbTxLen3 = USBPID_NAK;
#endif
#endif
}

/* ------------------------------------------------------------------------- */
