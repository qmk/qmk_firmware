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
* File Name    : usb0_function_global.c
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Device(s)    : RZ/A1H
* Tool-Chain   :
* OS           : None
* H/W Platform :
* Description  : RZ/A1H R7S72100 USB Sample Program
* Operation    :
* Limitations  :
*******************************************************************************/


/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "usb0_function.h"


/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


/*******************************************************************************
Private global variables and functions
*******************************************************************************/
const uint16_t g_usb0_function_bit_set[16] =
{
    0x0001, 0x0002, 0x0004, 0x0008,
    0x0010, 0x0020, 0x0040, 0x0080,
    0x0100, 0x0200, 0x0400, 0x0800,
    0x1000, 0x2000, 0x4000, 0x8000
};

uint32_t g_usb0_function_data_count[USB_FUNCTION_MAX_PIPE_NO + 1];
uint8_t  * g_usb0_function_data_pointer[USB_FUNCTION_MAX_PIPE_NO + 1];

uint16_t g_usb0_function_PipeIgnore[USB_FUNCTION_MAX_PIPE_NO + 1];
uint16_t g_usb0_function_PipeTbl[USB_FUNCTION_MAX_PIPE_NO + 1];
uint16_t g_usb0_function_pipe_status[USB_FUNCTION_MAX_PIPE_NO + 1];
uint32_t g_usb0_function_PipeDataSize[USB_FUNCTION_MAX_PIPE_NO + 1];

USB_FUNCTION_DMA_t g_usb0_function_DmaInfo[2];
uint16_t g_usb0_function_DmaPipe[2];
uint16_t g_usb0_function_DmaBval[2];
uint16_t g_usb0_function_DmaStatus[2];

uint16_t g_usb0_function_CtrZeroLengthFlag;

//uint16_t g_usb0_function_ConfigNum;
//uint16_t g_usb0_function_Alternate[USB_FUNCTION_ALT_NO];
//uint16_t g_usb0_function_RemoteWakeupFlag;
uint16_t g_usb0_function_TestModeFlag;
uint16_t g_usb0_function_TestModeSelectors;

//uint16_t g_usb0_function_ReqType;
//uint16_t g_usb0_function_ReqTypeType;
//uint16_t g_usb0_function_ReqTypeRecip;
//uint16_t g_usb0_function_ReqRequest;
//uint16_t g_usb0_function_ReqValue;
//uint16_t g_usb0_function_ReqIndex;
//uint16_t g_usb0_function_ReqLength;

//uint16_t g_usb0_function_EPTableIndex[USB_FUNCTION_MAX_EP_NO + 1];

uint16_t g_usb0_function_pipecfg[USB_FUNCTION_MAX_PIPE_NO + 1];
uint16_t g_usb0_function_pipebuf[USB_FUNCTION_MAX_PIPE_NO + 1];
uint16_t g_usb0_function_pipemaxp[USB_FUNCTION_MAX_PIPE_NO + 1];
uint16_t g_usb0_function_pipeperi[USB_FUNCTION_MAX_PIPE_NO + 1];


/*******************************************************************************
* Function Name: usb0_function_init_status
* Description  : Initialization USB Sample Driver Variable.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_function_init_status (void)
{
    uint16_t pipe;

    //g_usb0_function_ConfigNum         = 0;
    //g_usb0_function_RemoteWakeupFlag  = DEVDRV_USBF_OFF;
    g_usb0_function_TestModeFlag      = DEVDRV_USBF_OFF;
    g_usb0_function_CtrZeroLengthFlag = 0;

#if 0
    usb0_function_clear_alt();
#endif

    for (pipe = 0; pipe < (USB_FUNCTION_MAX_PIPE_NO + 1); ++pipe)
    {
        g_usb0_function_pipe_status[pipe]  = DEVDRV_USBF_PIPE_IDLE;
        g_usb0_function_PipeDataSize[pipe] = 0;
        g_usb0_function_data_count[pipe]   = 0;

        /* pipe configuration in usb0_function_ResetEP() */
        g_usb0_function_pipecfg[pipe]  = 0;
        g_usb0_function_pipebuf[pipe]  = 0;
        g_usb0_function_pipemaxp[pipe] = 0;
        g_usb0_function_pipeperi[pipe] = 0;
    }
}

/* End of File */
