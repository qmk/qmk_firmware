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
* File Name    : devdrv_usb_host_api.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB_HOST_API_H
#define USB_HOST_API_H

#include "r_typedefs.h"


/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/
#define USB_HOST_PORTNUM                            (2)

#define USB_HOST_ELT_INTERRUPT_LEVEL                (9)

#define USBHCLOCK_X1_48MHZ                          (0x0000u)       /* USB_X1_48MHz */
#define USBHCLOCK_EXTAL_12MHZ                       (0x0004u)       /* EXTAL_12MHz  */

#define USB_HOST_MAX_DEVICE                         (10)

#define USB_HOST_ON                                 (1)
#define USB_HOST_OFF                                (0)
#define USB_HOST_YES                                (1)
#define USB_HOST_NO                                 (0)

#define USB_HOST_NON_SPEED                          (0)
#define USB_HOST_LOW_SPEED                          (1)
#define USB_HOST_FULL_SPEED                         (2)
#define USB_HOST_HIGH_SPEED                         (3)

/* DEVDRV_SUCCESS(0) & DEVDRV_ERROR(-1) is dev_drv.h */
#define DEVDRV_USBH_STALL                           (-2)
#define DEVDRV_USBH_TIMEOUT                         (-3)
#define DEVDRV_USBH_NAK_TIMEOUT                     (-4)
#define DEVDRV_USBH_DETACH_ERR                      (-5)
#define DEVDRV_USBH_SETUP_ERR                       (-6)
#define DEVDRV_USBH_CTRL_COM_ERR                    (-7)
#define DEVDRV_USBH_COM_ERR                         (-8)
#define DEVDRV_USBH_DEV_ADDR_ERR                    (-9)

#define USB_HOST_ATTACH                             (1)
#define USB_HOST_DETACH                             (0)

#define USB_HOST_MAX_PIPE_NO                        (9u)
#define USB_HOST_PIPE0                              (0)
#define USB_HOST_PIPE1                              (1)
#define USB_HOST_PIPE2                              (2)
#define USB_HOST_PIPE3                              (3)
#define USB_HOST_PIPE4                              (4)
#define USB_HOST_PIPE5                              (5)
#define USB_HOST_PIPE6                              (6)
#define USB_HOST_PIPE7                              (7)
#define USB_HOST_PIPE8                              (8)
#define USB_HOST_PIPE9                              (9)

#define USB_HOST_ISO                                (0xc000u)
#define USB_HOST_INTERRUPT                          (0x8000u)
#define USB_HOST_BULK                               (0x4000u)

#define USB_HOST_PIPE_IDLE                          (0x00)
#define USB_HOST_PIPE_WAIT                          (0x01)
#define USB_HOST_PIPE_DONE                          (0x02)
#define USB_HOST_PIPE_NORES                         (0x03)
#define USB_HOST_PIPE_STALL                         (0x04)
#define USB_HOST_PIPE_ERROR                         (0x05)

#define USB_HOST_NONE                               (0x0000u)
#define USB_HOST_BFREFIELD                          (0x0400u)
#define USB_HOST_BFREON                             (0x0400u)
#define USB_HOST_BFREOFF                            (0x0000u)
#define USB_HOST_DBLBFIELD                          (0x0200u)
#define USB_HOST_DBLBON                             (0x0200u)
#define USB_HOST_DBLBOFF                            (0x0000u)
#define USB_HOST_CNTMDFIELD                         (0x0100u)
#define USB_HOST_CNTMDON                            (0x0100u)
#define USB_HOST_CNTMDOFF                           (0x0000u)
#define USB_HOST_SHTNAKON                           (0x0080u)
#define USB_HOST_SHTNAKOFF                          (0x0000u)
#define USB_HOST_DIRFIELD                           (0x0010u)
#define USB_HOST_DIR_H_OUT                          (0x0010u)
#define USB_HOST_DIR_H_IN                           (0x0000u)
#define USB_HOST_EPNUMFIELD                         (0x000fu)

#define USB_HOST_CUSE                               (0)
#define USB_HOST_D0USE                              (1)
#define USB_HOST_D0DMA                              (2)
#define USB_HOST_D1USE                              (3)
#define USB_HOST_D1DMA                              (4)

#define USB_HOST_CFIFO_USE                          (0x0000)
#define USB_HOST_D0FIFO_USE                         (0x1000)
#define USB_HOST_D1FIFO_USE                         (0x2000)
#define USB_HOST_D0FIFO_DMA                         (0x5000)
#define USB_HOST_D1FIFO_DMA                         (0x6000)

#define USB_HOST_BUF2FIFO                           (0)
#define USB_HOST_FIFO2BUF                           (1)

#define USB_HOST_DRV_DETACHED                       (0x0000)
#define USB_HOST_DRV_ATTACHED                       (0x0001)
#define USB_HOST_DRV_GET_DEVICE_DESC_64             (0x0002)
#define USB_HOST_DRV_POWERED                        (0x0003)
#define USB_HOST_DRV_DEFAULT                        (0x0004)
#define USB_HOST_DRV_SET_ADDRESS                    (0x0005)
#define USB_HOST_DRV_ADDRESSED                      (0x0006)
#define USB_HOST_DRV_GET_DEVICE_DESC_18             (0x0007)
#define USB_HOST_DRV_GET_CONGIG_DESC_9              (0x0008)
#define USB_HOST_DRV_GET_CONGIG_DESC                (0x0009)
#define USB_HOST_DRV_SET_CONFIG                     (0x000a)
#define USB_HOST_DRV_CONFIGURED                     (0x000b)
#define USB_HOST_DRV_SUSPEND                        (0x1000)
#define USB_HOST_DRV_NORES                          (0x0100)
#define USB_HOST_DRV_STALL                          (0x0200)

#define USB_HOST_TESTMODE_FORCE                     (0x000du)
#define USB_HOST_TESTMODE_TESTPACKET                (0x000cu)
#define USB_HOST_TESTMODE_SE0_NAK                   (0x000bu)
#define USB_HOST_TESTMODE_K                         (0x000au)
#define USB_HOST_TESTMODE_J                         (0x0009u)
#define USB_HOST_TESTMODE_NORMAL                    (0x0000u)

#define USB_HOST_DT_DEVICE                          (0x01)
#define USB_HOST_DT_CONFIGURATION                   (0x02)
#define USB_HOST_DT_STRING                          (0x03)
#define USB_HOST_DT_INTERFACE                       (0x04)
#define USB_HOST_DT_ENDPOINT                        (0x05)
#define USB_HOST_DT_DEVICE_QUALIFIER                (0x06)
#define USB_HOST_DT_OTHER_SPEED_CONFIGURATION       (0x07)
#define USB_HOST_DT_INTERFACE_POWER                 (0x08)

#define USB_HOST_IF_CLS_NOT                         (0x00)
#define USB_HOST_IF_CLS_AUDIO                       (0x01)
#define USB_HOST_IF_CLS_CDC_CTRL                    (0x02)
#define USB_HOST_IF_CLS_HID                         (0x03)
#define USB_HOST_IF_CLS_PHYSICAL                    (0x05)
#define USB_HOST_IF_CLS_IMAGE                       (0x06)
#define USB_HOST_IF_CLS_PRINTER                     (0x07)
#define USB_HOST_IF_CLS_MASS                        (0x08)
#define USB_HOST_IF_CLS_HUB                         (0x09)
#define USB_HOST_IF_CLS_CDC_DATA                    (0x0a)
#define USB_HOST_IF_CLS_CRAD                        (0x0b)
#define USB_HOST_IF_CLS_CONTENT                     (0x0d)
#define USB_HOST_IF_CLS_VIDEO                       (0x0e)
#define USB_HOST_IF_CLS_DIAG                        (0xdc)
#define USB_HOST_IF_CLS_WIRELESS                    (0xe0)
#define USB_HOST_IF_CLS_APL                         (0xfe)
#define USB_HOST_IF_CLS_VENDOR                      (0xff)
#define USB_HOST_IF_CLS_HELE                        (0xaa)

#define USB_HOST_EP_DIR_MASK                        (0x80)
#define USB_HOST_EP_OUT                             (0x00)
#define USB_HOST_EP_IN                              (0x80)
#define USB_HOST_EP_TYPE                            (0x03)
#define USB_HOST_EP_CNTRL                           (0x00)
#define USB_HOST_EP_ISO                             (0x01)
#define USB_HOST_EP_BULK                            (0x02)
#define USB_HOST_EP_INT                             (0x03)
#define USB_HOST_EP_NUM_MASK                        (0x0f)

#define USB_HOST_PIPE_IN                            (0)
#define USB_HOST_PIPE_OUT                           (1)

#define USB_END_POINT_ERROR                         (0xffff)

#define USB_HOST_REQ_GET_STATUS                     (0x0000)
#define USB_HOST_REQ_CLEAR_FEATURE                  (0x0100)
#define USB_HOST_REQ_RESERVED2                      (0x0200)
#define USB_HOST_REQ_SET_FEATURE                    (0x0300)
#define USB_HOST_REQ_RESERVED4                      (0x0400)
#define USB_HOST_REQ_SET_ADDRESS                    (0x0500)
#define USB_HOST_REQ_GET_DESCRIPTOR                 (0x0600)
#define USB_HOST_REQ_SET_DESCRIPTOR                 (0x0700)
#define USB_HOST_REQ_GET_CONFIGURATION              (0x0800)
#define USB_HOST_REQ_SET_CONFIGURATION              (0x0900)
#define USB_HOST_REQ_GET_INTERFACE                  (0x0a00)
#define USB_HOST_REQ_SET_INTERFACE                  (0x0b00)
#define USB_HOST_REQ_SYNCH_FRAME                    (0x0c00)

#define USB_HOST_REQTYPE_HOST_TO_DEVICE             (0x0000)
#define USB_HOST_REQTYPE_DEVICE_TO_HOST             (0x0080)
#define USB_HOST_REQTYPE_STANDARD                   (0x0020)
#define USB_HOST_REQTYPE_CLASS                      (0x0040)
#define USB_HOST_REQTYPE_VENDOR                     (0x0060)
#define USB_HOST_REQTYPE_DEVICE                     (0x0000)
#define USB_HOST_REQTYPE_INTERFACE                  (0x0001)
#define USB_HOST_REQTYPE_ENDPOINT                   (0x0002)
#define USB_HOST_REQTYPE_OTHER                      (0x0003)

#define USB_HOST_DESCTYPE_DEVICE                    (0x0100)
#define USB_HOST_DESCTYPE_CONFIGURATION             (0x0200)
#define USB_HOST_DESCTYPE_STRING                    (0x0300)
#define USB_HOST_DESCTYPE_INTERFACE                 (0x0400)
#define USB_HOST_DESCTYPE_ENDPOINT                  (0x0500)
#define USB_HOST_DESCTYPE_DEVICE_QUALIFIER          (0x0600)
#define USB_HOST_DESCTYPE_OTHER_SPEED_CONFIGURATION (0x0700)
#define USB_HOST_DESCTYPE_INTERFACE_POWER           (0x0800)


/*******************************************************************************
Variable Externs
*******************************************************************************/
typedef struct
{
    uint16_t    pipe_number;
    uint16_t    pipe_cfg;
    uint16_t    pipe_buf;
    uint16_t    pipe_max_pktsize;
    uint16_t    pipe_cycle;
    uint16_t    fifo_port;
} USB_HOST_CFG_PIPETBL_t;

typedef struct
{
    uint32_t    fifo;
    uint32_t    buffer;
    uint32_t    bytes;
    uint32_t    dir;
    uint32_t    size;
} USB_HOST_DMA_t;


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
uint16_t R_USB_api_host_init(uint16_t root, uint8_t int_level, uint16_t mode, uint16_t clockmode);
int32_t R_USB_api_host_enumeration(uint16_t root, uint16_t devadr);
int32_t R_USB_api_host_detach(uint16_t root);
int32_t R_USB_api_host_data_in(uint16_t root, uint16_t devadr, uint16_t Pipe, uint32_t Size, uint8_t *data_buf);
int32_t R_USB_api_host_data_in2(uint16_t root, uint16_t devadr, uint16_t Pipe, uint32_t Size, uint8_t *data_buf, uint32_t *bytes);
int32_t R_USB_api_host_data_out(uint16_t root, uint16_t devadr, uint16_t Pipe, uint32_t Size, uint8_t *data_buf);
int32_t R_USB_api_host_control_transfer(uint16_t root, uint16_t devadr, uint16_t Req, uint16_t Val, uint16_t Indx, uint16_t Len, uint8_t *Buf);
int32_t R_USB_api_host_set_endpoint(uint16_t root, uint16_t devadr, USB_HOST_CFG_PIPETBL_t *user_table, uint8_t *configdescriptor);
int32_t R_USB_api_host_clear_endpoint(uint16_t root, USB_HOST_CFG_PIPETBL_t *user_table);
int32_t R_USB_api_host_clear_endpoint_pipe(uint16_t root, uint16_t pipe_sel, USB_HOST_CFG_PIPETBL_t *user_table);
uint16_t R_USB_api_host_SetEndpointTable(uint16_t root, uint16_t devadr, USB_HOST_CFG_PIPETBL_t *user_table, uint8_t* Table);

int32_t R_USB_api_host_GetDeviceDescriptor(uint16_t root, uint16_t devadr, uint16_t size, uint8_t *buf);
int32_t R_USB_api_host_GetConfigDescriptor(uint16_t root, uint16_t devadr, uint16_t size, uint8_t *buf);
int32_t R_USB_api_host_SetConfig(uint16_t root, uint16_t devadr, uint16_t confignum);
int32_t R_USB_api_host_SetInterface(uint16_t root, uint16_t devadr, uint16_t interface_alt, uint16_t interface_index);
int32_t R_USB_api_host_ClearStall(uint16_t root, uint16_t devadr, uint16_t ep_dir);
uint16_t R_USB_api_host_GetUsbDeviceState(uint16_t root);

void    R_USB_api_host_elt_clocksel(uint16_t clockmode);
void    R_USB_api_host_elt_4_4(uint16_t root);
void    R_USB_api_host_elt_4_5(uint16_t root);
void    R_USB_api_host_elt_4_6(uint16_t root);
void    R_USB_api_host_elt_4_7(uint16_t root);
void    R_USB_api_host_elt_4_8(uint16_t root);
void    R_USB_api_host_elt_4_9(uint16_t root);
void    R_USB_api_host_elt_get_desc(uint16_t root);


/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "usb0_host_api.h"
#include "usb1_host_api.h"


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
#ifdef USB0_HOST_API_H
uint16_t Userdef_USB_usb0_host_d0fifo_dmaintid(void);
uint16_t Userdef_USB_usb0_host_d1fifo_dmaintid(void);
void     Userdef_USB_usb0_host_attach(void);
void     Userdef_USB_usb0_host_detach(void);
void     Userdef_USB_usb0_host_delay_1ms(void);
void     Userdef_USB_usb0_host_delay_xms(uint32_t msec);
void     Userdef_USB_usb0_host_delay_10us(uint32_t usec);
void     Userdef_USB_usb0_host_delay_500ns(void);
void     Userdef_USB_usb0_host_start_dma(USB_HOST_DMA_t * dma, uint16_t dfacc);
uint32_t Userdef_USB_usb0_host_stop_dma0(void);
uint32_t Userdef_USB_usb0_host_stop_dma1(void);
void     Userdef_USB_usb0_host_notice(const char * format);
void     Userdef_USB_usb0_host_user_rdy(const char * format, uint16_t data);
#endif

#ifdef USB1_HOST_API_H
uint16_t Userdef_USB_usb1_host_d0fifo_dmaintid(void);
uint16_t Userdef_USB_usb1_host_d1fifo_dmaintid(void);
void     Userdef_USB_usb1_host_attach(void);
void     Userdef_USB_usb1_host_detach(void);
void     Userdef_USB_usb1_host_delay_1ms(void);
void     Userdef_USB_usb1_host_delay_xms(uint32_t msec);
void     Userdef_USB_usb1_host_delay_10us(uint32_t usec);
void     Userdef_USB_usb1_host_delay_500ns(void);
void     Userdef_USB_usb1_host_start_dma(USB_HOST_DMA_t * dma, uint16_t dfacc);
uint32_t Userdef_USB_usb1_host_stop_dma0(void);
uint32_t Userdef_USB_usb1_host_stop_dma1(void);
void     Userdef_USB_usb1_host_notice(const char * format);
void     Userdef_USB_usb1_host_user_rdy(const char * format, uint16_t data);
#endif

#endif /* USB_HOST_API_H */

/* End of File */
