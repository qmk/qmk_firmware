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
#if !defined(__CDCPROLIFIC_H__)
#define __CDCPROLIFIC_H__

#include "cdcacm.h"

//#define PL2303_COMPAT // Uncomment it if you have compatibility problems

#define PL_VID                                  0x067B
#define CHECK_PID(pid)                          ( pid != 0x2303 && pid != 0x0609 )

//#define PL_PID                                0x0609

#define PROLIFIC_REV_H                          0x0202
#define PROLIFIC_REV_X                          0x0300
#define PROLIFIC_REV_HX_CHIP_D                  0x0400
#define PROLIFIC_REV_1                          0x0001

#define kXOnChar                                '\x11'
#define kXOffChar                               '\x13'

#define SPECIAL_SHIFT                           (5)
#define SPECIAL_MASK                            ((1<<SPECIAL_SHIFT) - 1)
#define STATE_ALL                               ( PD_RS232_S_MASK | PD_S_MASK )
#define FLOW_RX_AUTO                            ( PD_RS232_A_RFR | PD_RS232_A_DTR | PD_RS232_A_RXO )
#define FLOW_TX_AUTO                            ( PD_RS232_A_CTS | PD_RS232_A_DSR | PD_RS232_A_TXO | PD_RS232_A_DCD )
#define CAN_BE_AUTO                             ( FLOW_RX_AUTO | FLOW_TX_AUTO )
#define CAN_NOTIFY                              ( PD_RS232_N_MASK )
#define EXTERNAL_MASK                           ( PD_S_MASK | (PD_RS232_S_MASK & ~PD_RS232_S_LOOP) )
#define INTERNAL_DELAY                          ( PD_RS232_S_LOOP )
#define DEFAULT_AUTO                            ( PD_RS232_A_DTR | PD_RS232_A_RFR | PD_RS232_A_CTS | PD_RS232_A_DSR )
#define DEFAULT_NOTIFY                          0x00
#define DEFAULT_STATE                           ( PD_S_TX_ENABLE | PD_S_RX_ENABLE | PD_RS232_A_TXO | PD_RS232_A_RXO )

#define CONTINUE_SEND                           1
#define PAUSE_SEND                              2

#define kRxAutoFlow                             ((UInt32)( PD_RS232_A_RFR | PD_RS232_A_DTR | PD_RS232_A_RXO ))
#define kTxAutoFlow                             ((UInt32)( PD_RS232_A_CTS | PD_RS232_A_DSR | PD_RS232_A_TXO | PD_RS232_A_DCD ))
#define kControl_StateMask                      ((UInt32)( PD_RS232_S_CTS | PD_RS232_S_DSR | PD_RS232_S_CAR | PD_RS232_S_RI  ))
#define kRxQueueState                           ((UInt32)( PD_S_RXQ_EMPTY | PD_S_RXQ_LOW_WATER | PD_S_RXQ_HIGH_WATER | PD_S_RXQ_FULL ))
#define kTxQueueState                           ((UInt32)( PD_S_TXQ_EMPTY | PD_S_TXQ_LOW_WATER | PD_S_TXQ_HIGH_WATER | PD_S_TXQ_FULL ))

#define kCONTROL_DTR                            0x01
#define kCONTROL_RTS                            0x02

#define kStateTransientMask                     0x74
#define kBreakError                             0x04
#define kFrameError                             0x10
#define kParityError                            0x20
#define kOverrunError                           0x40

#define kCTS                                    0x80
#define kDSR                                    0x02
#define kRI                                     0x08
#define kDCD                                    0x01
#define kHandshakeInMask                        ((UInt32)( PD_RS232_S_CTS | PD_RS232_S_DSR | PD_RS232_S_CAR | PD_RS232_S_RI  ))

#define VENDOR_WRITE_REQUEST_TYPE               0x40
#define VENDOR_WRITE_REQUEST                    0x01

#define VENDOR_READ_REQUEST_TYPE                0xc0
#define VENDOR_READ_REQUEST                     0x01

// Device Configuration Registers (DCR0, DCR1, DCR2)
#define SET_DCR0                                0x00
#define GET_DCR0                                0x80
#define DCR0_INIT                               0x01
#define DCR0_INIT_H                             0x41
#define DCR0_INIT_X                             0x61

#define SET_DCR1                                0x01
#define GET_DCR1                                0x81
#define DCR1_INIT_H                             0x80
#define DCR1_INIT_X                             0x00

#define SET_DCR2                                0x02
#define GET_DCR2                                0x82
#define DCR2_INIT_H                             0x24
#define DCR2_INIT_X                             0x44

// On-chip Data Buffers:
#define RESET_DOWNSTREAM_DATA_PIPE              0x08
#define RESET_UPSTREAM_DATA_PIPE                0x09


#define PL_MAX_ENDPOINTS                        4

enum tXO_State {
        kXOnSent = -2,
        kXOffSent = -1,
        kXO_Idle = 0,
        kXOffNeeded = 1,
        kXOnNeeded = 2
};

enum pl2303_type {
        unknown,
        type_0, /* don't know the difference between type 0 and */
        type_1, /* type 1, until someone from prolific tells us... */
        rev_X,
        rev_HX, /* HX version of the pl2303 chip */
        rev_H
};


class PL2303 : public ACM {
        uint16_t wPLType; // Type of chip

public:
        PL2303(USB *pusb, CDCAsyncOper *pasync);

        // USBDeviceConfig implementation
        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        //virtual uint8_t Release();
        //virtual uint8_t Poll();
        //virtual uint8_t GetAddress() { return bAddress; };

        //// UsbConfigXtracter implementation
        //virtual void EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *ep);

#ifdef PL2303_COMPAT
private:
        /* Prolific proprietary requests */
        uint8_t vendorRead( uint8_t val_lo, uint8_t val_hi, uint16_t index, uint8_t* buf );
        uint8_t vendorWrite( uint8_t val_lo, uint8_t val_hi, uint8_t index );
#endif
};

#ifdef PL2303_COMPAT
/* vendor read request */
inline uint8_t PL2303::vendorRead( uint8_t val_lo, uint8_t val_hi, uint16_t index, uint8_t* buf )
{
        return( pUsb->ctrlReq(bAddress, 0, VENDOR_READ_REQUEST_TYPE, VENDOR_READ_REQUEST, val_lo, val_hi, index, 1, 1, buf, NULL ));
}

/* vendor write request */
inline uint8_t PL2303::vendorWrite( uint8_t val_lo, uint8_t val_hi, uint8_t index )
{
        return( pUsb->ctrlReq(bAddress, 0, VENDOR_WRITE_REQUEST_TYPE, VENDOR_WRITE_REQUEST, val_lo, val_hi, index, 0, 0, NULL, NULL ));
}
#endif

#endif // __CDCPROLIFIC_H__
