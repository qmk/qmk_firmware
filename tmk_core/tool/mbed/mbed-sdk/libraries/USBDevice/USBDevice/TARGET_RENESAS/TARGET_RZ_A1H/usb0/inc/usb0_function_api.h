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
* File Name    : usb0_function_api.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB0_FUNCTION_API_H
#define USB0_FUNCTION_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/


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
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
void     usb0_api_function_init(uint8_t int_level, uint16_t mode, uint16_t clockmode);
uint16_t usb0_api_function_IsConfigured(void);
uint16_t usb0_function_GetDeviceState(void);
uint16_t usb0_api_function_CtrlReadStart(uint32_t size, uint8_t *data);
void     usb0_api_function_CtrlWriteStart(uint32_t size, uint8_t *data);
uint16_t usb0_api_function_start_send_transfer(uint16_t pipe, uint32_t size, uint8_t *data);
uint16_t usb0_api_function_check_pipe_status(uint16_t pipe, uint32_t *size);
void     usb0_api_function_clear_pipe_status(uint16_t pipe);
void     usb0_api_function_start_receive_transfer(uint16_t pipe, uint32_t size, uint8_t *data);
void     usb0_api_function_set_pid_buf(uint16_t pipe);
void     usb0_api_function_set_pid_nak(uint16_t pipe);
void     usb0_api_function_set_pid_stall(uint16_t pipe);
void     usb0_api_function_clear_pid_stall(uint16_t pipe);
uint16_t usb0_api_function_get_pid(uint16_t pipe);
int32_t  usb0_api_function_check_stall(uint16_t pipe);
void     usb0_api_function_set_sqclr(uint16_t pipe);
void     usb0_api_function_set_sqset(uint16_t pipe);
void     usb0_api_function_set_csclr(uint16_t pipe);
void     usb0_api_function_set_curpipe(uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw);
void     usb0_api_function_clear_brdy_sts(uint16_t pipe);
void     usb0_api_function_clear_bemp_sts(uint16_t pipe);
void     usb0_api_function_clear_nrdy_sts(uint16_t pipe);

void     usb0_function_ClearFeature(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_SetFeature(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_SetAddress(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_SetDescriptor(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_SetConfiguration(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_SetInterface(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_SynchFrame(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_GetStatus(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_GetDescriptor(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_GetConfiguration(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_GetInterface(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Resrv_0(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Resrv_123(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Resrv_4(uint16_t type, uint16_t value, uint16_t index, uint16_t length);
void     usb0_function_Resrv_5(uint16_t type, uint16_t value, uint16_t index, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* USB0_FUNCTION_API_H */

/* End of File */
