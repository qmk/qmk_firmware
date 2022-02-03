/* Copyright (C) 2015 Andrew J. Kroll
   and
   Circuits At Home, LTD. All rights reserved.

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
#if !defined(__CDC_XR21B1411_H__)
#define __CDC_XR21B1411_H__

#include "cdcacm.h"

#define XR_REG_CUSTOM_DRIVER                    (0x020DU) // DRIVER SELECT
#define XR_REG_CUSTOM_DRIVER_ACTIVE             (0x0001U) // 0: CDC 1: CUSTOM

#define XR_REG_ACM_FLOW_CTL                     (0x0216U) // FLOW CONTROL REGISTER CDCACM MODE
#define XR_REG_FLOW_CTL                         (0x0C06U) // FLOW CONTROL REGISTER CUSTOM MODE
#define XR_REG_FLOW_CTL_HALF_DPLX               (0x0008U) // 0:FULL DUPLEX 1:HALF DUPLEX
#define XR_REG_FLOW_CTL_MODE_MASK               (0x0007U) // MODE BITMASK
#define XR_REG_FLOW_CTL_NONE                    (0x0000U) // NO FLOW CONTROL
#define XR_REG_FLOW_CTL_HW                      (0x0001U) // HARDWARE FLOW CONTROL
#define XR_REG_FLOW_CTL_SW                      (0x0002U) // SOFTWARE FLOW CONTROL
#define XR_REG_FLOW_CTL_MMMRX                   (0x0003U) // MULTIDROP RX UPON ADDRESS MATCH
#define XR_REG_FLOW_CTL_MMMRXTX                 (0x0004U) // MULTIDROP RX/TX UPON ADDRESS MATCH

#define XR_REG_ACM_GPIO_MODE                    (0x0217U) // GPIO MODE REGISTER IN CDCACM MODE
#define XR_REG_GPIO_MODE                        (0x0C0CU) // GPIO MODE REGISTER IN CUSTOM MODE
#define XR_REG_GPIO_MODE_GPIO                   (0x0000U) // ALL GPIO PINS ACM PROGRAMMABLE
#define XR_REG_GPIO_MODE_FC_RTSCTS              (0x0001U) // AUTO RTSCTS HW FC (GPIO 4/5)
#define XR_REG_GPIO_MODE_FC_DTRDSR              (0x0002U) // AUTO DTRDSR HW FC (GPIO 2/3)
#define XR_REG_GPIO_MODE_ATE                    (0x0003U) // AUTO TRANSCEIVER ENABLE DURING TX (GPIO 5)
#define XR_REG_GPIO_MODE_ATE_ADDRESS            (0x0004U) // AUTO TRANSCEIVER ENABLE ON ADDRESS MATCH (GPIO 5)

#define XR_REG_ACM_GPIO_DIR                     (0x0218U) // GPIO DIRECTION REGISTER CDCACM MODE, 0:IN 1:OUT
#define XR_REG_GPIO_DIR                         (0x0C0DU) // GPIO DIRECTION REGISTER CUSTOM MODE, 0:IN 1:OUT

#define XR_REG_ACM_GPIO_INT                     (0x0219U) // GPIO PIN CHANGE INTERRUPT ENABLE CDCACM MODE, 0: ENABLED 1: DISABLED
#define XR_REG_GPIO_INT                         (0x0C11U) // GPIO PIN CHANGE INTERRUPT ENABLE CUSTOM MODE, 0: ENABLED 1: DISABLED
#define XR_REG_GPIO_MASK                        (0x001FU) // GPIO REGISTERS BITMASK

#define XR_REG_UART_ENABLE                      (0x0C00U) // UART I/O ENABLE REGISTER
#define XR_REG_UART_ENABLE_RX                   (0x0002U) // 0:DISABLED 1:ENABLED
#define XR_REG_UART_ENABLE_TX                   (0x0001U) // 0:DISABLED 1:ENABLED

#define XR_REG_ERROR_STATUS                     (0x0C09U) // ERROR STATUS REGISTER
#define XR_REG_ERROR_STATUS_MASK                (0x00F8U) // ERROR STATUS BITMASK
#define XR_REG_ERROR_STATUS_ERROR               (0x0078U) // ERROR STATUS ERROR BITMASK
#define XR_REG_ERROR_STATUS_BREAK               (0x0008U) // BREAK ERROR HAS BEEN DETECTED
#define XR_REG_ERROR_STATUS_FRAME               (0x0010U) // FRAMING ERROR HAS BEEN DETECTED
#define XR_REG_ERROR_STATUS_PARITY              (0x0020U) // PARITY ERROR HAS BEEN DETECTED
#define XR_REG_ERROR_STATUS_OVERRUN             (0x0040U) // RX OVERRUN ERROR HAS BEEN DETECTED
#define XR_REG_ERROR_STATUS_BREAK_STATUS        (0x0080U) // BREAK CONDITION IS CURRENTLY BEING DETECTED

#define XR_REG_TX_BREAK                         (0x0C0AU) // TRANSMIT BREAK. 0X0001-0XFFE TIME IN MS, 0X0000 STOP, 0X0FFF BREAK ON

#define XR_REG_XCVR_EN_DELAY                    (0x0C0BU) // TURN-ARROUND DELAY IN BIT-TIMES 0X0000-0X000F

#define XR_REG_GPIO_SET                         (0x0C0EU) // 1:SET GPIO PIN

#define XR_REG_GPIO_CLR                         (0x0C0FU) // 1:CLEAR GPIO PIN

#define XR_REG_GPIO_STATUS                      (0x0C10U) // READ GPIO PINS

#define XR_REG_CUSTOMISED_INT                   (0x0C12U) // 0:STANDARD 1:CUSTOM SEE DATA SHEET

#define XR_REG_PIN_PULLUP_ENABLE                (0x0C14U) // 0:DISABLE 1:ENABLE, BITS 0-5:GPIO, 6:RX 7:TX

#define XR_REG_PIN_PULLDOWN_ENABLE              (0x0C15U) // 0:DISABLE 1:ENABLE, BITS 0-5:GPIO, 6:RX 7:TX

#define XR_REG_LOOPBACK                         (0x0C16U) // 0:DISABLE 1:ENABLE, SEE DATA SHEET

#define XR_REG_RX_FIFO_LATENCY                  (0x0CC2U) // FIFO LATENCY REGISTER
#define XR_REG_RX_FIFO_LATENCY_ENABLE           (0x0001U) //

#define XR_REG_WIDE_MODE                        (0x0D02U)
#define XR_REG_WIDE_MODE_ENABLE                 (0x0001U)

#define XR_REG_XON_CHAR                         (0x0C07U)
#define XR_REG_XOFF_CHAR                        (0x0C08U)

#define XR_REG_TX_FIFO_RESET                    (0x0C80U) // 1: RESET, SELF-CLEARING
#define XR_REG_TX_FIFO_COUNT                    (0x0C81U) // READ-ONLY
#define XR_REG_RX_FIFO_RESET                    (0x0CC0U) // 1: RESET, SELF-CLEARING
#define XR_REG_RX_FIFO_COUNT                    (0x0CC1U) // READ-ONLY

#define XR_WRITE_REQUEST_TYPE                   (0x40U)

#define XR_READ_REQUEST_TYPE                    (0xC0U)

#define XR_MAX_ENDPOINTS                        4

class XR21B1411 : public ACM {
protected:

public:
        XR21B1411(USB *pusb, CDCAsyncOper *pasync);

        /**
         * Used by the USB core to check what this driver support.
         * @param  vid The device's VID.
         * @param  pid The device's PID.
         * @return     Returns true if the device's VID and PID matches this driver.
         */
        virtual bool VIDPIDOK(uint16_t vid, uint16_t pid) {
                return (((vid == 0x2890U) && (pid == 0x0201U)) || ((vid == 0x04e2U) && (pid == 0x1411U)));
        };

        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);

        virtual tty_features enhanced_features(void) {
                tty_features rv;
                rv.enhanced = true;
                rv.autoflow_RTS = true;
                rv.autoflow_DSR = true;
                rv.autoflow_XON = true;
                rv.half_duplex = true;
                rv.wide = true;
                return rv;
        };

        uint8_t read_register(uint16_t reg, uint16_t *val) {
                return (pUsb->ctrlReq(bAddress, 0, XR_READ_REQUEST_TYPE, 1, 0, 0, reg, 2, 2, (uint8_t *)val, NULL));
        }

        uint8_t write_register(uint16_t reg, uint16_t val) {
                return (pUsb->ctrlReq(bAddress, 0, XR_WRITE_REQUEST_TYPE, 0, BGRAB0(val), BGRAB1(val), reg, 0, 0, NULL, NULL));
        }


        ////////////////////////////////////////////////////////////////////////
        // The following methods set the CDC-ACM defaults.
        ////////////////////////////////////////////////////////////////////////

        virtual void autoflowRTS(bool s) {
                uint16_t val;
                uint8_t rval;
                rval = read_register(XR_REG_ACM_FLOW_CTL, &val);
                if(!rval) {
                        if(s) {
                                val &= XR_REG_FLOW_CTL_HALF_DPLX;
                                val |= XR_REG_FLOW_CTL_HW;
                        } else {
                                val &= XR_REG_FLOW_CTL_HALF_DPLX;
                        }
                        rval = write_register(XR_REG_ACM_FLOW_CTL, val);
                        if(!rval) {
                                rval = write_register(XR_REG_ACM_GPIO_MODE, XR_REG_GPIO_MODE_GPIO);
                                if(!rval) {
                                        // ACM commands apply the new settings.
                                        LINE_CODING LCT;
                                        rval = GetLineCoding(&LCT);
                                        if(!rval) {
                                                rval = SetLineCoding(&LCT);
                                                if(!rval) {
                                                        _enhanced_status.autoflow_XON = false;
                                                        _enhanced_status.autoflow_DSR = false;
                                                        _enhanced_status.autoflow_RTS = s;
                                                }
                                        }
                                }
                        }
                }
        };

        virtual void autoflowDSR(bool s) {
                uint16_t val;
                uint8_t rval;
                rval = read_register(XR_REG_ACM_FLOW_CTL, &val);
                if(!rval) {
                        if(s) {
                                val &= XR_REG_FLOW_CTL_HALF_DPLX;
                                val |= XR_REG_FLOW_CTL_HW;
                        } else {
                                val &= XR_REG_FLOW_CTL_HALF_DPLX;
                        }
                        rval = write_register(XR_REG_ACM_FLOW_CTL, val);
                        if(!rval) {
                                if(s) {
                                        rval = write_register(XR_REG_ACM_GPIO_MODE, XR_REG_GPIO_MODE_FC_DTRDSR);
                                } else {
                                        rval = write_register(XR_REG_ACM_GPIO_MODE, XR_REG_GPIO_MODE_GPIO);
                                }
                                if(!rval) {
                                        // ACM commands apply the new settings.
                                        LINE_CODING LCT;
                                        rval = GetLineCoding(&LCT);
                                        if(!rval) {
                                                rval = SetLineCoding(&LCT);
                                                if(!rval) {
                                                        _enhanced_status.autoflow_XON = false;
                                                        _enhanced_status.autoflow_RTS = false;
                                                        _enhanced_status.autoflow_DSR = s;
                                                }
                                        }
                                }
                        }
                }
        };

        virtual void autoflowXON(bool s) {
                // NOTE: hardware defaults to the normal XON/XOFF
                uint16_t val;
                uint8_t rval;
                rval = read_register(XR_REG_ACM_FLOW_CTL, &val);
                if(!rval) {
                        if(s) {
                                val &= XR_REG_FLOW_CTL_HALF_DPLX;
                                val |= XR_REG_FLOW_CTL_SW;
                        } else {
                                val &= XR_REG_FLOW_CTL_HALF_DPLX;
                        }
                        rval = write_register(XR_REG_ACM_FLOW_CTL, val);
                        if(!rval) {
                                rval = write_register(XR_REG_ACM_GPIO_MODE, XR_REG_GPIO_MODE_GPIO);
                                if(!rval) {
                                        // ACM commands apply the new settings.
                                        LINE_CODING LCT;
                                        rval = GetLineCoding(&LCT);
                                        if(!rval) {
                                                rval = SetLineCoding(&LCT);
                                                if(!rval) {
                                                        _enhanced_status.autoflow_RTS = false;
                                                        _enhanced_status.autoflow_DSR = false;
                                                        _enhanced_status.autoflow_XON = s;
                                                }
                                        }
                                }
                        }
                }
        };

        virtual void half_duplex(bool s) {
                uint16_t val;
                uint8_t rval;
                rval = read_register(XR_REG_ACM_FLOW_CTL, &val);
                if(!rval) {
                        if(s) {
                                val |= XR_REG_FLOW_CTL_HALF_DPLX;
                        } else {
                                val &= XR_REG_FLOW_CTL_MODE_MASK;
                        }
                        rval = write_register(XR_REG_ACM_FLOW_CTL, val);
                        if(!rval) {
                                // ACM commands apply the new settings.
                                LINE_CODING LCT;
                                rval = GetLineCoding(&LCT);
                                if(!rval) {
                                        rval = SetLineCoding(&LCT);
                                        if(!rval) {
                                                _enhanced_status.half_duplex = s;
                                        }
                                }
                        }
                }
        };



};

#endif // __CDCPROLIFIC_H__
