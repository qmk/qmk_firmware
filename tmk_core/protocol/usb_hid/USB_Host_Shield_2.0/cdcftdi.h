/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */
#if !defined(__CDCFTDI_H__)
#define __CDCFTDI_H__

#include "Usb.h"

#define bmREQ_FTDI_OUT  0x40
#define bmREQ_FTDI_IN   0xc0

//#define bmREQ_FTDI_OUT                USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE
//#define bmREQ_FTDI_IN         USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE

#define FTDI_VID                        0x0403  // FTDI VID
#define FTDI_PID                        0x6001  // FTDI PID

#define FT232AM                         0x0200
#define FT232BM                         0x0400
#define FT2232                          0x0500
#define FT232R                          0x0600

// Commands
#define FTDI_SIO_RESET                  0 /* Reset the port */
#define FTDI_SIO_MODEM_CTRL             1 /* Set the modem control register */
#define FTDI_SIO_SET_FLOW_CTRL          2 /* Set flow control register */
#define FTDI_SIO_SET_BAUD_RATE          3 /* Set baud rate */
#define FTDI_SIO_SET_DATA               4 /* Set the data characteristics of the port */
#define FTDI_SIO_GET_MODEM_STATUS       5 /* Retrieve current value of modem status register */
#define FTDI_SIO_SET_EVENT_CHAR         6 /* Set the event character */
#define FTDI_SIO_SET_ERROR_CHAR         7 /* Set the error character */

#define FTDI_SIO_RESET_SIO              0
#define FTDI_SIO_RESET_PURGE_RX         1
#define FTDI_SIO_RESET_PURGE_TX         2

#define FTDI_SIO_SET_DATA_PARITY_NONE   (0x0 << 8 )
#define FTDI_SIO_SET_DATA_PARITY_ODD    (0x1 << 8 )
#define FTDI_SIO_SET_DATA_PARITY_EVEN   (0x2 << 8 )
#define FTDI_SIO_SET_DATA_PARITY_MARK   (0x3 << 8 )
#define FTDI_SIO_SET_DATA_PARITY_SPACE  (0x4 << 8 )
#define FTDI_SIO_SET_DATA_STOP_BITS_1   (0x0 << 11)
#define FTDI_SIO_SET_DATA_STOP_BITS_15  (0x1 << 11)
#define FTDI_SIO_SET_DATA_STOP_BITS_2   (0x2 << 11)
#define FTDI_SIO_SET_BREAK              (0x1 << 14)

#define FTDI_SIO_SET_DTR_MASK           0x1
#define FTDI_SIO_SET_DTR_HIGH           ( 1 | ( FTDI_SIO_SET_DTR_MASK  << 8))
#define FTDI_SIO_SET_DTR_LOW            ( 0 | ( FTDI_SIO_SET_DTR_MASK  << 8))
#define FTDI_SIO_SET_RTS_MASK           0x2
#define FTDI_SIO_SET_RTS_HIGH           ( 2 | ( FTDI_SIO_SET_RTS_MASK << 8 ))
#define FTDI_SIO_SET_RTS_LOW            ( 0 | ( FTDI_SIO_SET_RTS_MASK << 8 ))

#define FTDI_SIO_DISABLE_FLOW_CTRL      0x0
#define FTDI_SIO_RTS_CTS_HS             (0x1 << 8)
#define FTDI_SIO_DTR_DSR_HS             (0x2 << 8)
#define FTDI_SIO_XON_XOFF_HS            (0x4 << 8)

#define FTDI_SIO_CTS_MASK               0x10
#define FTDI_SIO_DSR_MASK               0x20
#define FTDI_SIO_RI_MASK                0x40
#define FTDI_SIO_RLSD_MASK              0x80

class FTDI;

class FTDIAsyncOper {
public:

        virtual uint8_t OnInit(FTDI *pftdi) {
                return 0;
        };

        virtual uint8_t OnRelease(FTDI *pftdi) {
                return 0;
        };
};


// Only single port chips are currently supported by the library,
//              so only three endpoints are allocated.
#define FTDI_MAX_ENDPOINTS              3

class FTDI : public USBDeviceConfig, public UsbConfigXtracter {
        static const uint8_t epDataInIndex; // DataIn endpoint index
        static const uint8_t epDataOutIndex; // DataOUT endpoint index
        static const uint8_t epInterruptInIndex; // InterruptIN  endpoint index

        FTDIAsyncOper *pAsync;
        USB *pUsb;
        uint8_t bAddress;
        uint8_t bConfNum; // configuration number
        uint8_t bNumIface; // number of interfaces in the configuration
        uint8_t bNumEP; // total number of EP in the configuration
        uint32_t qNextPollTime; // next poll time
        bool bPollEnable; // poll enable flag
        uint16_t wFTDIType; // Type of FTDI chip

        EpInfo epInfo[FTDI_MAX_ENDPOINTS];

        void PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr);

public:
        FTDI(USB *pusb, FTDIAsyncOper *pasync);

        uint8_t SetBaudRate(uint32_t baud);
        uint8_t SetModemControl(uint16_t control);
        uint8_t SetFlowControl(uint8_t protocol, uint8_t xon = 0x11, uint8_t xoff = 0x13);
        uint8_t SetData(uint16_t databm);

        // Methods for recieving and sending data
        uint8_t RcvData(uint16_t *bytes_rcvd, uint8_t *dataptr);
        uint8_t SndData(uint16_t nbytes, uint8_t *dataptr);

        // USBDeviceConfig implementation
        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        uint8_t Release();
        uint8_t Poll();

        virtual uint8_t GetAddress() {
                return bAddress;
        };

        // UsbConfigXtracter implementation
        void EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *ep);

        virtual bool VIDPIDOK(uint16_t vid, uint16_t pid) {
                return (vid == FTDI_VID && pid == FTDI_PID);
        }

};

#endif // __CDCFTDI_H__
