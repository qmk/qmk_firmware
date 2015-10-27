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
* File Name    : usb0_host_api.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB0_HOST_API_H
#define USB0_HOST_API_H


/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Variable Externs
*******************************************************************************/


/*******************************************************************************
Functions Prototypes
*******************************************************************************/
void        usb0_host_interrupt(uint32_t int_sense);
void        usb0_host_dma_interrupt_d0fifo(uint32_t int_sense);
void        usb0_host_dma_interrupt_d1fifo(uint32_t int_sense);

uint16_t    usb0_api_host_init(uint8_t int_level, uint16_t mode, uint16_t clockmode);
int32_t     usb0_api_host_enumeration(uint16_t devadr);
int32_t     usb0_api_host_detach(void);
int32_t     usb0_api_host_data_in(uint16_t devadr, uint16_t Pipe, uint32_t Size, uint8_t *data_buf);
int32_t     usb0_api_host_data_out(uint16_t devadr, uint16_t Pipe, uint32_t Size, uint8_t *data_buf);
int32_t     usb0_api_host_control_transfer(uint16_t devadr, uint16_t Req, uint16_t Val, uint16_t Indx, uint16_t Len, uint8_t *Buf);
int32_t     usb0_api_host_set_endpoint(uint16_t devadr, USB_HOST_CFG_PIPETBL_t *user_table, uint8_t *configdescriptor);
int32_t     usb0_api_host_clear_endpoint(USB_HOST_CFG_PIPETBL_t *user_table);
int32_t     usb0_api_host_clear_endpoint_pipe(uint16_t pipe_sel, USB_HOST_CFG_PIPETBL_t *user_table);
uint16_t    usb0_api_host_SetEndpointTable(uint16_t devadr, USB_HOST_CFG_PIPETBL_t *user_table, uint8_t* Table);
int32_t     usb0_api_host_data_count(uint16_t pipe, uint32_t *data_count);

int32_t     usb0_api_host_GetDeviceDescriptor(uint16_t devadr, uint16_t size, uint8_t *buf);
int32_t     usb0_api_host_GetConfigDescriptor(uint16_t devadr, uint16_t size, uint8_t *buf);
int32_t     usb0_api_host_SetConfig(uint16_t devadr, uint16_t confignum);
int32_t     usb0_api_host_SetInterface(uint16_t devadr, uint16_t interface_alt, uint16_t interface_index);
int32_t     usb0_api_host_ClearStall(uint16_t devadr, uint16_t ep_dir);
uint16_t    usb0_api_host_GetUsbDeviceState(void);

void        usb0_api_host_elt_4_4(void);
void        usb0_api_host_elt_4_5(void);
void        usb0_api_host_elt_4_6(void);
void        usb0_api_host_elt_4_7(void);
void        usb0_api_host_elt_4_8(void);
void        usb0_api_host_elt_4_9(void);
void        usb0_api_host_elt_get_desc(void);

void        usb0_host_EL_ModeInit(void);
void        usb0_host_EL_SetUACT(void);
void        usb0_host_EL_ClearUACT(void);
void        usb0_host_EL_SetTESTMODE(uint16_t mode);
void        usb0_host_EL_ClearNRDYSTS(uint16_t pipe);
uint16_t    usb0_host_EL_GetINTSTS1(void);
void        usb0_host_EL_UsbBusReset(void);
void        usb0_host_EL_UsbAttach(void);
void        usb0_host_EL_SetupStage(uint16_t Req, uint16_t Val, uint16_t Indx, uint16_t Len);
void        usb0_host_EL_StatusStage(void);
void        usb0_host_EL_CtrlReadStart(uint32_t Bsize, uint8_t *Table);
int32_t     usb0_host_EL_UsbSuspend(void);
int32_t     usb0_host_EL_UsbResume(void);

#if 0   /* prototype in devdrv_usb_host_api.h */
uint16_t    Userdef_USB_usb0_host_d0fifo_dmaintid(void);
uint16_t    Userdef_USB_usb0_host_d1fifo_dmaintid(void);
void        Userdef_USB_usb0_host_attach(void);
void        Userdef_USB_usb0_host_detach(void);
void        Userdef_USB_usb0_host_delay_1ms(void);
void        Userdef_USB_usb0_host_delay_xms(uint32_t msec);
void        Userdef_USB_usb0_host_delay_10us(uint32_t usec);
void        Userdef_USB_usb0_host_delay_500ns(void);
void        Userdef_USB_usb0_host_start_dma(USB_HOST_DMA_t *dma, uint16_t dfacc);
uint32_t    Userdef_USB_usb0_host_stop_dma0(void);
uint32_t    Userdef_USB_usb0_host_stop_dma1(void);
#endif

#endif /* USB0_HOST_API_H */

/* End of File */
