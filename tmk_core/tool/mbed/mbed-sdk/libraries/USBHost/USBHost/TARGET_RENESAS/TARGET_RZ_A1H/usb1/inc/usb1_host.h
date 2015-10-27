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
* File Name    : usb1_host.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB1_HOST_H
#define USB1_HOST_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "devdrv_usb_host_api.h"
#include "usb_host.h"

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
extern const uint16_t   g_usb1_host_bit_set[];
extern uint32_t         g_usb1_host_data_count[USB_HOST_MAX_PIPE_NO + 1];
extern uint8_t          *g_usb1_host_data_pointer[USB_HOST_MAX_PIPE_NO + 1];

extern uint16_t         g_usb1_host_PipeIgnore[];
extern uint16_t         g_usb1_host_PipeTbl[];
extern uint16_t         g_usb1_host_pipe_status[];
extern uint32_t         g_usb1_host_PipeDataSize[];

extern USB_HOST_DMA_t   g_usb1_host_DmaInfo[];
extern uint16_t         g_usb1_host_DmaPipe[];
extern uint16_t         g_usb1_host_DmaBval[];
extern uint16_t         g_usb1_host_DmaStatus[];

extern uint16_t         g_usb1_host_driver_state;
extern uint16_t         g_usb1_host_ConfigNum;
extern uint16_t         g_usb1_host_CmdStage;
extern uint16_t         g_usb1_host_bchg_flag;
extern uint16_t         g_usb1_host_detach_flag;
extern uint16_t         g_usb1_host_attach_flag;

extern uint16_t         g_usb1_host_UsbAddress;
extern uint16_t         g_usb1_host_setUsbAddress;
extern uint16_t         g_usb1_host_default_max_packet[USB_HOST_MAX_DEVICE + 1];
extern uint16_t         g_usb1_host_UsbDeviceSpeed;
extern uint16_t         g_usb1_host_SupportUsbDeviceSpeed;

extern uint16_t         g_usb1_host_SavReq;
extern uint16_t         g_usb1_host_SavVal;
extern uint16_t         g_usb1_host_SavIndx;
extern uint16_t         g_usb1_host_SavLen;

extern uint16_t  g_usb1_host_pipecfg[USB_HOST_MAX_PIPE_NO + 1];
extern uint16_t  g_usb1_host_pipebuf[USB_HOST_MAX_PIPE_NO + 1];
extern uint16_t  g_usb1_host_pipemaxp[USB_HOST_MAX_PIPE_NO + 1];
extern uint16_t  g_usb1_host_pipeperi[USB_HOST_MAX_PIPE_NO + 1];

/*******************************************************************************
Functions Prototypes
*******************************************************************************/
/* ==== common ==== */
void        usb1_host_dma_stop_d0(uint16_t pipe, uint32_t remain);
void        usb1_host_dma_stop_d1(uint16_t pipe, uint32_t remain);
uint16_t    usb1_host_is_hispeed(void);
uint16_t    usb1_host_is_hispeed_enable(void);
uint16_t    usb1_host_start_send_transfer(uint16_t pipe, uint32_t size, uint8_t *data);
uint16_t    usb1_host_write_buffer(uint16_t pipe);
uint16_t    usb1_host_write_buffer_c(uint16_t pipe);
uint16_t    usb1_host_write_buffer_d0(uint16_t pipe);
uint16_t    usb1_host_write_buffer_d1(uint16_t pipe);
void        usb1_host_start_receive_transfer(uint16_t pipe, uint32_t size, uint8_t *data);
uint16_t    usb1_host_read_buffer(uint16_t pipe);
uint16_t    usb1_host_read_buffer_c(uint16_t pipe);
uint16_t    usb1_host_read_buffer_d0(uint16_t pipe);
uint16_t    usb1_host_read_buffer_d1(uint16_t pipe);
uint16_t    usb1_host_change_fifo_port(uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw);
void        usb1_host_set_curpipe(uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw);
void        usb1_host_set_curpipe2(uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw, uint16_t dfacc);
uint16_t    usb1_host_get_mbw(uint32_t trncount, uint32_t dtptr);
uint16_t    usb1_host_read_dma(uint16_t pipe);
void        usb1_host_stop_transfer(uint16_t pipe);
void        usb1_host_brdy_int(uint16_t status, uint16_t int_enb);
void        usb1_host_nrdy_int(uint16_t status, uint16_t int_enb);
void        usb1_host_bemp_int(uint16_t status, uint16_t int_enb);
void        usb1_host_setting_interrupt(uint8_t level);
void        usb1_host_reset_module(uint16_t clockmode);
uint16_t    usb1_host_get_buf_size(uint16_t pipe);
uint16_t    usb1_host_get_mxps(uint16_t pipe);
void        usb1_host_enable_brdy_int(uint16_t pipe);
void        usb1_host_disable_brdy_int(uint16_t pipe);
void        usb1_host_clear_brdy_sts(uint16_t pipe);
void        usb1_host_enable_bemp_int(uint16_t pipe);
void        usb1_host_disable_bemp_int(uint16_t pipe);
void        usb1_host_clear_bemp_sts(uint16_t pipe);
void        usb1_host_enable_nrdy_int(uint16_t pipe);
void        usb1_host_disable_nrdy_int(uint16_t pipe);
void        usb1_host_clear_nrdy_sts(uint16_t pipe);
void        usb1_host_set_pid_buf(uint16_t pipe);
void        usb1_host_set_pid_nak(uint16_t pipe);
void        usb1_host_set_pid_stall(uint16_t pipe);
void        usb1_host_clear_pid_stall(uint16_t pipe);
uint16_t    usb1_host_get_pid(uint16_t pipe);
void        usb1_host_set_sqclr(uint16_t pipe);
void        usb1_host_set_sqset(uint16_t pipe);
void        usb1_host_set_csclr(uint16_t pipe);
void        usb1_host_aclrm(uint16_t pipe);
void        usb1_host_set_aclrm(uint16_t pipe);
void        usb1_host_clr_aclrm(uint16_t pipe);
uint16_t    usb1_host_get_sqmon(uint16_t pipe);
uint16_t    usb1_host_get_inbuf(uint16_t pipe);

/* ==== host ==== */
void        usb1_host_init_pipe_status(void);
int32_t     usb1_host_CtrlTransStart(uint16_t devadr, uint16_t Req, uint16_t Val, uint16_t Indx, uint16_t Len, uint8_t *Buf);
void        usb1_host_SetupStage(uint16_t Req, uint16_t Val, uint16_t Indx, uint16_t Len);
void        usb1_host_CtrlReadStart(uint32_t Bsize, uint8_t *Table);
uint16_t    usb1_host_CtrlWriteStart(uint32_t Bsize, uint8_t *Table);
void        usb1_host_StatusStage(void);
void        usb1_host_get_devadd(uint16_t addr, uint16_t *devadd);
void        usb1_host_set_devadd(uint16_t addr, uint16_t *devadd);
void        usb1_host_InitModule(void);
uint16_t    usb1_host_CheckAttach(void);
void        usb1_host_UsbDetach(void);
void        usb1_host_UsbDetach2(void);
void        usb1_host_UsbAttach(void);
uint16_t    usb1_host_UsbBusReset(void);
int32_t     usb1_host_UsbResume(void);
int32_t     usb1_host_UsbSuspend(void);
void        usb1_host_Enable_DetachINT(void);
void        usb1_host_Disable_DetachINT(void);
void        usb1_host_UsbStateManager(void);


#endif /* USB1_HOST_H */

/* End of File */
