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
* File Name    : usb1_function.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB1_FUNCTION_H
#define USB1_FUNCTION_H


/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "devdrv_usb_function_api.h"
#include "usb_function.h"


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
extern const uint16_t       g_usb1_function_bit_set[];
extern uint32_t             g_usb1_function_data_count[USB_FUNCTION_MAX_PIPE_NO + 1];
extern uint8_t              *g_usb1_function_data_pointer[USB_FUNCTION_MAX_PIPE_NO + 1];

extern uint16_t             g_usb1_function_PipeIgnore[];
extern uint16_t             g_usb1_function_PipeTbl[];
extern uint16_t             g_usb1_function_pipe_status[];
extern uint32_t             g_usb1_function_PipeDataSize[];

extern USB_FUNCTION_DMA_t   g_usb1_function_DmaInfo[];
extern uint16_t             g_usb1_function_DmaPipe[];
extern uint16_t             g_usb1_function_DmaBval[];
extern uint16_t             g_usb1_function_DmaStatus[];

extern uint16_t             g_usb1_function_CtrZeroLengthFlag;

extern uint16_t             g_usb1_function_ConfigNum;
extern uint16_t             g_usb1_function_Alternate[USB_FUNCTION_ALT_NO];
extern uint16_t             g_usb1_function_RemoteWakeupFlag;
extern uint16_t             g_usb1_function_TestModeFlag;
extern uint16_t             g_usb1_function_TestModeSelectors;

extern uint16_t             g_usb1_function_ReqType;
extern uint16_t             g_usb1_function_ReqTypeType;
extern uint16_t             g_usb1_function_ReqTypeRecip;
extern uint16_t             g_usb1_function_ReqRequest;
extern uint16_t             g_usb1_function_ReqValue;
extern uint16_t             g_usb1_function_ReqIndex;
extern uint16_t             g_usb1_function_ReqLength;

extern uint16_t             g_usb1_function_EPTableIndex[USB_FUNCTION_MAX_EP_NO + 1];

extern uint16_t             g_usb1_function_pipecfg[USB_FUNCTION_MAX_PIPE_NO + 1];
extern uint16_t             g_usb1_function_pipebuf[USB_FUNCTION_MAX_PIPE_NO + 1];
extern uint16_t             g_usb1_function_pipemaxp[USB_FUNCTION_MAX_PIPE_NO + 1];
extern uint16_t             g_usb1_function_pipeperi[USB_FUNCTION_MAX_PIPE_NO + 1];


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
/* ==== common ==== */
void     usb1_function_dma_stop_d0(uint16_t pipe, uint32_t remain);
void     usb1_function_dma_stop_d1(uint16_t pipe, uint32_t remain);
uint16_t usb1_function_is_hispeed(void);
uint16_t usb1_function_is_hispeed_enable(void);
uint16_t usb1_function_start_send_transfer(uint16_t pipe, uint32_t size, uint8_t *data);
uint16_t usb1_function_write_buffer(uint16_t pipe);
uint16_t usb1_function_write_buffer_c(uint16_t pipe);
uint16_t usb1_function_write_buffer_d0(uint16_t pipe);
uint16_t usb1_function_write_buffer_d1(uint16_t pipe);
void     usb1_function_start_receive_transfer(uint16_t pipe, uint32_t size, uint8_t *data);
uint16_t usb1_function_read_buffer(uint16_t pipe);
uint16_t usb1_function_read_buffer_c(uint16_t pipe);
uint16_t usb1_function_read_buffer_d0(uint16_t pipe);
uint16_t usb1_function_read_buffer_d1(uint16_t pipe);
uint16_t usb1_function_change_fifo_port(uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw);
void     usb1_function_set_curpipe(uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw);
void     usb1_function_set_curpipe2(uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw, uint16_t dfacc);
uint16_t usb1_function_get_mbw(uint32_t trncount, uint32_t dtptr);
uint16_t usb1_function_read_dma(uint16_t pipe);
void     usb1_function_brdy_int(uint16_t status, uint16_t int_enb);
void     usb1_function_nrdy_int(uint16_t status, uint16_t int_enb);
void     usb1_function_bemp_int(uint16_t status, uint16_t int_enb);
void     usb1_function_setting_interrupt(uint8_t level);
void     usb1_function_reset_module(uint16_t clockmode);
uint16_t usb1_function_get_buf_size(uint16_t pipe);
uint16_t usb1_function_get_mxps(uint16_t pipe);
void     usb1_function_clear_brdy_sts(uint16_t pipe);
void     usb1_function_clear_bemp_sts(uint16_t pipe);
void     usb1_function_clear_nrdy_sts(uint16_t pipe);
void     usb1_function_set_pid_buf(uint16_t pipe);
void     usb1_function_set_pid_nak(uint16_t pipe);
void     usb1_function_set_pid_stall(uint16_t pipe);
void     usb1_function_clear_pid_stall(uint16_t pipe);
uint16_t usb1_function_get_pid(uint16_t pipe);
void     usb1_function_set_sqclr(uint16_t pipe);
void     usb1_function_set_sqset(uint16_t pipe);
void     usb1_function_set_csclr(uint16_t pipe);
void     usb1_function_aclrm(uint16_t pipe);
void     usb1_function_set_aclrm(uint16_t pipe);
void     usb1_function_clr_aclrm(uint16_t pipe);
uint16_t usb1_function_get_sqmon(uint16_t pipe);
uint16_t usb1_function_get_inbuf(uint16_t pipe);

/* ==== function ==== */
void     usb1_function_init_status(void);
void     usb1_function_InitModule(uint16_t mode);
uint16_t usb1_function_CheckVBUStaus(void);
void     usb1_function_USB_FUNCTION_Attach(void);
void     usb1_function_USB_FUNCTION_Detach(void);
void     usb1_function_USB_FUNCTION_BusReset(void);
void     usb1_function_USB_FUNCTION_Resume(void);
void     usb1_function_USB_FUNCTION_Suspend(void);
void     usb1_function_USB_FUNCTION_TestMode(void);
void     usb1_function_ResetDCP(void);
void     usb1_function_ResetEP(uint16_t num);
uint16_t usb1_function_EpToPipe(uint16_t ep);
void     usb1_function_InitEPTable(uint16_t Con_Num, uint16_t Int_Num, uint16_t Alt_Num);
uint16_t usb1_function_GetConfigNum(void);
uint16_t usb1_function_GetAltNum(uint16_t Con_Num, uint16_t Int_Num);
uint16_t usb1_function_CheckRemoteWakeup(void);
void     usb1_function_clear_alt(void);
void     usb1_function_clear_pipe_tbl(void);
void     usb1_function_clear_ep_table_index(void);
uint16_t usb1_function_GetInterfaceNum(uint16_t num);

#ifdef __cplusplus
}
#endif


#endif /* USB1_FUNCTION_H */

/* End of File */
