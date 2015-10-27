/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2012 - 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : devdrv_usb_function_api.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB_FUNCTION_API_H
#define USB_FUNCTION_API_H


/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <MBRZA1H.h>
#include "r_typedefs.h"
#include "usb0_function_api.h"
#include "usb1_function_api.h"


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
Typedef definitions
*******************************************************************************/
typedef struct
{
    uint32_t fifo;
    uint32_t buffer;
    uint32_t bytes;
    uint32_t dir;
    uint32_t size;
} USB_FUNCTION_DMA_t;


/*******************************************************************************
Macro definitions
*******************************************************************************/
#define USBFCLOCK_X1_48MHZ                          (0x0000u)       /* USB_X1_48MHz */
#define USBFCLOCK_EXTAL_12MHZ                       (0x0004u)       /* EXTAL_12MHz  */

#define DEVDRV_USBF_ON                              (1)
#define DEVDRV_USBF_OFF                             (0)
#define DEVDRV_USBF_YES                             (1)
#define DEVDRV_USBF_NO                              (0)

#define DEVDRV_USBF_STALL                           (-2)

#define DEVDRV_USBF_WRITEEND                        (0)
#define DEVDRV_USBF_WRITESHRT                       (1)
#define DEVDRV_USBF_WRITING                         (2)
#define DEVDRV_USBF_WRITEDMA                        (3)

#define DEVDRV_USBF_FIFOERROR                       (0xffff)

#define DEVDRV_USBF_PIPE_IDLE                       (0x00)
#define DEVDRV_USBF_PIPE_WAIT                       (0x01)
#define DEVDRV_USBF_PIPE_DONE                       (0x02)
#define DEVDRV_USBF_PIPE_NORES                      (0x03)
#define DEVDRV_USBF_PIPE_STALL                      (0x04)

#define DEVDRV_USBF_PID_NAK                         (0x0000u)
#define DEVDRV_USBF_PID_BUF                         (0x0001u)
#define DEVDRV_USBF_PID_STALL                       (0x0002u)
#define DEVDRV_USBF_PID_STALL2                      (0x0003u)

#define USB_FUNCTION_NON_SPEED                      (0)
#define USB_FUNCTION_LOW_SPEED                      (1)
#define USB_FUNCTION_FULL_SPEED                     (2)
#define USB_FUNCTION_HIGH_SPEED                     (3)

#define USB_FUNCTION_READEND                        (0)
#define USB_FUNCTION_READSHRT                       (1)
#define USB_FUNCTION_READING                        (2)
#define USB_FUNCTION_READOVER                       (3)
#define USB_FUNCTION_READZERO                       (4)

#define USB_FUNCTION_MAX_PIPE_NO                    (15u)
#define USB_FUNCTION_PIPE0                          (0)
#define USB_FUNCTION_PIPE1                          (1)
#define USB_FUNCTION_PIPE2                          (2)
#define USB_FUNCTION_PIPE3                          (3)
#define USB_FUNCTION_PIPE4                          (4)
#define USB_FUNCTION_PIPE5                          (5)
#define USB_FUNCTION_PIPE6                          (6)
#define USB_FUNCTION_PIPE7                          (7)
#define USB_FUNCTION_PIPE8                          (8)
#define USB_FUNCTION_PIPE9                          (9)
#define USB_FUNCTION_PIPEA                          (10)
#define USB_FUNCTION_PIPEB                          (11)
#define USB_FUNCTION_PIPEC                          (12)
#define USB_FUNCTION_PIPED                          (13)
#define USB_FUNCTION_PIPEE                          (14)
#define USB_FUNCTION_PIPEF                          (15)

#define USB_FUNCTION_ISO                            (0xc000u)
#define USB_FUNCTION_INTERRUPT                      (0x8000u)
#define USB_FUNCTION_BULK                           (0x4000u)

#define USB_FUNCTION_NONE                           (0x0000u)
#define USB_FUNCTON_BFREFIELD                       (0x0400u)
#define USB_FUNCTION_BFREON                         (0x0400u)
#define USB_FUNCTION_BFREOFF                        (0x0000u)
#define USB_FUNCTION_DBLBFIELD                      (0x0200u)
#define USB_FUNCTION_DBLBON                         (0x0200u)
#define USB_FUNCTION_DBLBOFF                        (0x0000u)
#define USB_FUNCTION_CNTMDFIELD                     (0x0100u)
#define USB_FUNCTION_CNTMDON                        (0x0100u)
#define USB_FUNCTION_CNTMDOFF                       (0x0000u)
#define USB_FUNCTION_SHTNAKON                       (0x0080u)
#define USB_FUNCTION_SHTNAKOFF                      (0x0000u)
#define USB_FUNCTION_DIRFIELD                       (0x0010u)
#define USB_FUNCTION_DIR_P_OUT                      (0x0000u)
#define USB_FUNCTION_DIR_P_IN                       (0x0010u)
#define USB_FUNCTION_EPNUMFIELD                     (0x000fu)
#define USB_FUNCTION_MAX_EP_NO                      (15u)
#define USB_FUNCTION_EP0                            (0u)
#define USB_FUNCTION_EP1                            (1u)
#define USB_FUNCTION_EP2                            (2u)
#define USB_FUNCTION_EP3                            (3u)
#define USB_FUNCTION_EP4                            (4u)
#define USB_FUNCTION_EP5                            (5u)
#define USB_FUNCTION_EP6                            (6u)
#define USB_FUNCTION_EP7                            (7u)
#define USB_FUNCTION_EP8                            (8u)
#define USB_FUNCTION_EP9                            (9u)
#define USB_FUNCTION_EP10                           (10u)
#define USB_FUNCTION_EP11                           (11u)
#define USB_FUNCTION_EP12                           (12u)
#define USB_FUNCTION_EP13                           (13u)
#define USB_FUNCTION_EP14                           (14u)
#define USB_FUNCTION_EP15                           (15u)

#define USB_FUNCTION_EPTABLE_LENGTH                 (5u)

#define USB_FUNCTION_CUSE                           (0)
#define USB_FUNCTION_D0USE                          (1)
#define USB_FUNCTION_D0DMA                          (2)
#define USB_FUNCTION_D1USE                          (3)
#define USB_FUNCTION_D1DMA                          (4)

#define USB_FUNCTION_CFIFO_USE                      (0x0000)
#define USB_FUNCTION_D0FIFO_USE                     (0x1000)
#define USB_FUNCTION_D1FIFO_USE                     (0x2000)
#define USB_FUNCTION_D0FIFO_DMA                     (0x5000)
#define USB_FUNCTION_D1FIFO_DMA                     (0x6000)

#define USB_FUNCTION_BUF2FIFO                       (0)
#define USB_FUNCTION_FIFO2BUF                       (1)

#define USB_FUNCTION_DVST_POWERED                   (0x0001)
#define USB_FUNCTION_DVST_DEFAULT                   (0x0002)
#define USB_FUNCTION_DVST_ADDRESS                   (0x0003)
#define USB_FUNCTION_DVST_CONFIGURED                (0x0004)
#define USB_FUNCTION_DVST_SUSPEND                   (0x0005)
#define USB_FUNCTION_DVST_CONFIGURED_SUSPEND        (0x0006)

#define USB_FUNCTION_FUNCTION_TEST_SELECT           (0xff00u)
#define USB_FUNCTION_FUNCTION_TEST_J                (0x0100u)
#define USB_FUNCTION_FUNCTION_TEST_K                (0x0200u)
#define USB_FUNCTION_FUNCTION_TEST_SE0_NAK          (0x0300u)
#define USB_FUNCTION_FUNCTION_TEST_PACKET           (0x0400u)
#define USB_FUNCTION_FUNCTION_TEST_FORCE_ENABLE     (0x0500u)
#define USB_FUNCTION_FUNCTION_TEST_STSelectors      (0x0600u)
#define USB_FUNCTION_FUNCTION_TEST_Reserved         (0x4000u)
#define USB_FUNCTION_FUNCTION_TEST_VSTModes         (0xc000u)

#define USB_FUNCTION_DT_TYPE                        (0xff00u)
#define USB_FUNCTION_DT_INDEX                       (0xff)
#define USB_FUNCTION_DT_DEVICE                      (0x01)
#define USB_FUNCTION_DT_CONFIGURATION               (0x02)
#define USB_FUNCTION_DT_STRING                      (0x03)
#define USB_FUNCTION_DT_INTERFACE                   (0x04)
#define USB_FUNCTION_DT_ENDPOINT                    (0x05)
#define USB_FUNCTION_DT_DEVICE_QUALIFIER            (0x06)
#define USB_FUNCTION_DT_OTHER_SPEED_CONFIGURATION   (0x07)
#define USB_FUNCTION_DT_INTERFACE_POWER             (0x08)

#define USB_FUNCTION_CF_RESERVED                    (0x80)
#define USB_FUNCTION_CF_SELF                        (0x40)
#define USB_FUNCTION_CF_RWUP                        (0x20)
#define USB_FUNCTION_CF_NORWUP                      (0x00)
#define USB_FUNCTION_EP_ERROR                       (0xff)

#define USB_FUNCTION_EP_OUT                         (0x00)
#define USB_FUNCTION_EP_IN                          (0x80)
#define USB_FUNCTION_EP_CNTRL                       (0x00)
#define USB_FUNCTION_EP_ISO                         (0x01)
#define USB_FUNCTION_EP_BULK                        (0x02)
#define USB_FUNCTION_EP_INT                         (0x03)

#define USB_FUNCTION_STANDARD_REQUEST               (0x0000u)
#define USB_FUNCTION_CLASS_REQUEST                  (0x0020u)
#define USB_FUNCTION_VENDOR_REQUEST                 (0x0040u)
#define USB_FUNCTION_DEVICE_REQUEST                 (0x0000u)
#define USB_FUNCTION_INTERFACE_REQUEST              (0x0001u)
#define USB_FUNCTION_ENDPOINT_REQUEST               (0x0002u)

#define USB_FUNCTION_GETSTATUS_BUSPOWERD            (0x0000u)
#define USB_FUNCTION_GETSTATUS_SELFPOWERD           (0x0001u)
#define USB_FUNCTION_GETSTATUS_REMOTEWAKEUP         (0x0002u)
#define USB_FUNCTION_GETSTATUS_NOTHALT              (0x0000u)
#define USB_FUNCTION_GETSTATUS_HALT                 (0x0001u)

#define USB_FUNCTION_FEATURE_ENDPOINT_HALT          (0x0000u)
#define USB_FUNCTION_FEATURE_REMOTE_WAKEUP          (0x0001u)
#define USB_FUNCTION_FEATURE_TEST_MODE              (0x0002u)

#define USB_FUNCTION_bRequest                       (0xff00u)       /* b15-8:bRequest */
#define USB_FUNCTION_bmRequestType                  (0x00ffu)       /* b7-0: bmRequestType */
#define USB_FUNCTION_bmRequestTypeDir               (0x0080u)       /* b7  : Data transfer direction */
#define USB_FUNCTION_bmRequestTypeType              (0x0060u)       /* b6-5: Type */
#define USB_FUNCTION_bmRequestTypeRecip             (0x001fu)       /* b4-0: Recipient */


/*******************************************************************************
Variable Externs
*******************************************************************************/


/*******************************************************************************
Functions Prototypes
*******************************************************************************/
#if 0
void     R_USB_api_function_init(uint16_t root, uint8_t int_level, uint16_t mode, uint16_t clockmode);
uint16_t R_USB_api_function_IsConfigured(uint16_t root);
uint16_t R_USB_api_function_CtrlReadStart(uint16_t root, uint32_t size, uint8_t *data);
void     R_USB_api_function_CtrlWriteStart(uint16_t root, uint32_t size, uint8_t *data);
uint16_t R_USB_api_function_start_send_transfer(uint16_t root, uint16_t pipe, uint32_t size, uint8_t *data);
uint16_t R_USB_api_function_check_pipe_status(uint16_t root, uint16_t pipe, uint32_t *size);
void     R_USB_api_function_clear_pipe_status(uint16_t root, uint16_t pipe);
void     R_USB_api_function_start_receive_transfer(uint16_t root, uint16_t pipe, uint32_t size, uint8_t *data);
void     R_USB_api_function_set_pid_buf(uint16_t root, uint16_t pipe);
void     R_USB_api_function_set_pid_nak(uint16_t root, uint16_t pipe);
void     R_USB_api_function_set_pid_stall(uint16_t root, uint16_t pipe);
void     R_USB_api_function_clear_pid_stall(uint16_t root, uint16_t pipe);
uint16_t R_USB_api_function_get_pid(uint16_t root, uint16_t pipe);
int32_t  R_USB_api_function_check_stall(uint16_t root, uint16_t pipe);
void     R_USB_api_function_set_sqclr(uint16_t root, uint16_t pipe);
void     R_USB_api_function_set_sqset(uint16_t root, uint16_t pipe);
void     R_USB_api_function_set_csclr(uint16_t root, uint16_t pipe);
void     R_USB_api_function_set_curpipe(uint16_t root, uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw);
void     R_USB_api_function_clear_brdy_sts(uint16_t root, uint16_t pipe);
void     R_USB_api_function_clear_bemp_sts(uint16_t root, uint16_t pipe);
void     R_USB_api_function_clear_nrdy_sts(uint16_t root, uint16_t pipe);
void     R_USB_api_function_enable_brdy_int(uint16_t root, uint16_t pipe);
void     R_USB_api_function_disable_brdy_int(uint16_t root, uint16_t pipe);
void     R_USB_api_function_enable_bemp_int(uint16_t root, uint16_t pipe);
void     R_USB_api_function_disable_bemp_int(uint16_t root, uint16_t pipe);
void     R_USB_api_function_enable_nrdy_int(uint16_t root, uint16_t pipe);
void     R_USB_api_function_disable_nrdy_int(uint16_t root, uint16_t pipe);
void     R_USB_api_function_stop_transfer(uint16_t root, uint16_t pipe);
#endif

#ifdef USB0_FUNCTION_API_H
void     usb0_function_interrupt(uint32_t int_sense);
void     usb0_function_dma_interrupt_d0fifo(uint32_t int_sense);
void     usb0_function_dma_interrupt_d1fifo(uint32_t int_sense);

void     usb0_function_Class0(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Class1(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Class2(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Class3(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Class4(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Class5(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Vendor0(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Vendor1(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Vendor2(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Vendor3(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Vendor4(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Vendor5(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_ResetDescriptor(uint16_t mode);

IRQn_Type Userdef_USB_usb0_function_d0fifo_dmaintid(void);
IRQn_Type Userdef_USB_usb0_function_d1fifo_dmaintid(void);
void     Userdef_USB_usb0_function_attach(void);
void     Userdef_USB_usb0_function_detach(void);
void     Userdef_USB_usb0_function_delay_1ms(void);
void     Userdef_USB_usb0_function_delay_xms(uint32_t msec);
void     Userdef_USB_usb0_function_delay_10us(uint32_t usec);
void     Userdef_USB_usb0_function_delay_500ns(void);
void     Userdef_USB_usb0_function_start_dma(USB_FUNCTION_DMA_t *dma, uint16_t dfacc);
uint32_t Userdef_USB_usb0_function_stop_dma0(void);
uint32_t Userdef_USB_usb0_function_stop_dma1(void);

void     usb0_function_stop_transfer(uint16_t pipe);
void     usb0_function_enable_brdy_int(uint16_t pipe);
void     usb0_function_disable_brdy_int(uint16_t pipe);
void     usb0_function_enable_bemp_int(uint16_t pipe);
void     usb0_function_disable_bemp_int(uint16_t pipe);
void     usb0_function_enable_nrdy_int(uint16_t pipe);
void     usb0_function_disable_nrdy_int(uint16_t pipe);
#endif

#ifdef  USB1_FUNCTION_API_H
void     usb1_function_interrupt(uint32_t int_sense);
void     usb1_function_dma_interrupt_d0fifo(uint32_t int_sense);
void     usb1_function_dma_interrupt_d1fifo(uint32_t int_sense);

void     usb1_function_Class0(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Class1(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Class2(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Class3(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Class4(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Class5(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Vendor0(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Vendor1(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Vendor2(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Vendor3(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Vendor4(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_Vendor5(uint16_t type, uint16_t req, uint16_t value, uint16_t index, uint16_t length);
void     usb1_function_ResetDescriptor(uint16_t mode);

uint16_t Userdef_USB_usb1_function_d0fifo_dmaintid(void);
uint16_t Userdef_USB_usb1_function_d1fifo_dmaintid(void);
void     Userdef_USB_usb1_function_attach(void);
void     Userdef_USB_usb1_function_detach(void);
void     Userdef_USB_usb1_function_delay_1ms(void);
void     Userdef_USB_usb1_function_delay_xms(uint32_t msec);
void     Userdef_USB_usb1_function_delay_10us(uint32_t usec);
void     Userdef_USB_usb1_function_delay_500ns(void);
void     Userdef_USB_usb1_function_start_dma(USB_FUNCTION_DMA_t *dma, uint16_t dfacc);
uint32_t Userdef_USB_usb1_function_stop_dma0(void);
uint32_t Userdef_USB_usb1_function_stop_dma1(void);

void     usb1_function_stop_transfer(uint16_t pipe);
void     usb1_function_enable_brdy_int(uint16_t pipe);
void     usb1_function_disable_brdy_int(uint16_t pipe);
void     usb1_function_enable_bemp_int(uint16_t pipe);
void     usb1_function_disable_bemp_int(uint16_t pipe);
void     usb1_function_enable_nrdy_int(uint16_t pipe);
void     usb1_function_disable_nrdy_int(uint16_t pipe);
#endif

#ifdef __cplusplus
}
#endif


#endif /* USB_FUNCTION_API_H */

/* End of File */
