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
* File Name    : usb0_host_global.c
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
#include "usb0_host.h"


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
const uint16_t g_usb0_host_bit_set[16] =
{
    0x0001, 0x0002, 0x0004, 0x0008,
    0x0010, 0x0020, 0x0040, 0x0080,
    0x0100, 0x0200, 0x0400, 0x0800,
    0x1000, 0x2000, 0x4000, 0x8000
};

uint32_t  g_usb0_host_data_count[USB_HOST_MAX_PIPE_NO + 1];
uint8_t * g_usb0_host_data_pointer[USB_HOST_MAX_PIPE_NO + 1];

uint16_t  g_usb0_host_PipeIgnore[USB_HOST_MAX_PIPE_NO + 1];
uint16_t  g_usb0_host_PipeTbl[USB_HOST_MAX_PIPE_NO + 1];
uint16_t  g_usb0_host_pipe_status[USB_HOST_MAX_PIPE_NO + 1];
uint32_t  g_usb0_host_PipeDataSize[USB_HOST_MAX_PIPE_NO + 1];

USB_HOST_DMA_t g_usb0_host_DmaInfo[2];

uint16_t  g_usb0_host_DmaPipe[2];
uint16_t  g_usb0_host_DmaBval[2];
uint16_t  g_usb0_host_DmaStatus[2];

uint16_t  g_usb0_host_driver_state;
uint16_t  g_usb0_host_ConfigNum;
uint16_t  g_usb0_host_CmdStage;
uint16_t  g_usb0_host_bchg_flag;
uint16_t  g_usb0_host_detach_flag;
uint16_t  g_usb0_host_attach_flag;

uint16_t  g_usb0_host_UsbAddress;
uint16_t  g_usb0_host_setUsbAddress;
uint16_t  g_usb0_host_default_max_packet[USB_HOST_MAX_DEVICE + 1];
uint16_t  g_usb0_host_UsbDeviceSpeed;
uint16_t  g_usb0_host_SupportUsbDeviceSpeed;

uint16_t  g_usb0_host_SavReq;
uint16_t  g_usb0_host_SavVal;
uint16_t  g_usb0_host_SavIndx;
uint16_t  g_usb0_host_SavLen;

uint16_t  g_usb0_host_pipecfg[USB_HOST_MAX_PIPE_NO + 1];
uint16_t  g_usb0_host_pipebuf[USB_HOST_MAX_PIPE_NO + 1];
uint16_t  g_usb0_host_pipemaxp[USB_HOST_MAX_PIPE_NO + 1];
uint16_t  g_usb0_host_pipeperi[USB_HOST_MAX_PIPE_NO + 1];


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb0_host_init_pipe_status
* Description  : Initialize pipe status.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_host_init_pipe_status (void)
{
    uint16_t loop;

    g_usb0_host_ConfigNum = 0;

    for (loop = 0; loop < (USB_HOST_MAX_PIPE_NO + 1); ++loop)
    {
        g_usb0_host_pipe_status[loop]   = USB_HOST_PIPE_IDLE;
        g_usb0_host_PipeDataSize[loop]  = 0;

        /* pipe configuration in usb0_host_resetEP() */
        g_usb0_host_pipecfg[loop]  = 0;
        g_usb0_host_pipebuf[loop]  = 0;
        g_usb0_host_pipemaxp[loop] = 0;
        g_usb0_host_pipeperi[loop] = 0;
    }
}

/* End of File */
