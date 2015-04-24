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
* File Name    : usb0_function_controlrw.c
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


/*******************************************************************************
* Function Name: usb0_api_function_CtrlReadStart
* Description  : Executes the USB control read transfer.
*              : USB host controller <- USB device
* Arguments    : uint16_t size     ; Data Size
*              : uint8_t  *data    ; Data Address
* Return Value : DEVDRV_USBF_WRITEEND          ; End of data write
*              : DEVDRV_USBF_WRITESHRT         ; End of short data write
*              : DEVDRV_USBF_WRITING           ; Continue of data write
*              : DEVDRV_USBF_FIFOERROR         ; FIFO access error
*******************************************************************************/
uint16_t usb0_api_function_CtrlReadStart (uint32_t size, uint8_t * data)
{
    uint16_t status;
    uint16_t mbw;

    usb0_function_set_pid_nak(USB_FUNCTION_PIPE0);

    g_usb0_function_data_count[USB_FUNCTION_PIPE0]   = size;
    g_usb0_function_data_pointer[USB_FUNCTION_PIPE0] = data;

    mbw = usb0_function_get_mbw(g_usb0_function_data_count[USB_FUNCTION_PIPE0],
                                 (uint32_t)g_usb0_function_data_pointer[USB_FUNCTION_PIPE0]);
    usb0_function_set_curpipe(USB_FUNCTION_PIPE0, USB_FUNCTION_CUSE, USB_FUNCTION_CFIFO_WRITE, mbw);
    USB200.CFIFOCTR = USB_FUNCTION_BITBCLR;

    status = usb0_function_write_buffer_c(USB_FUNCTION_PIPE0);

    /* Peripheral Control sequence */
    switch (status)
    {
        case DEVDRV_USBF_WRITESHRT:                                     /* End of data write */
        case DEVDRV_USBF_WRITEEND:                                      /* End of data write (not null) */
        case DEVDRV_USBF_WRITING:                                       /* Continue of data write */
            usb0_function_enable_bemp_int(USB_FUNCTION_PIPE0);          /* Enable Empty Interrupt */
            usb0_function_set_pid_buf(USB_FUNCTION_PIPE0);              /* Set BUF */
        break;

        case DEVDRV_USBF_FIFOERROR:                                     /* FIFO access error */
        break;

        default:
        break;
    }

    return status;                                                      /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb0_api_function_CtrlWriteStart
* Description  : Executes the USB control write transfer.
*              : USB host controller -> USB device
* Arguments    : uint16_t  size         ; Data Size
*              : uint8_t  *data         ; Data Address
* Return Value : none
*******************************************************************************/
void usb0_api_function_CtrlWriteStart (uint32_t size, uint8_t * data)
{
    uint16_t mbw;

    usb0_function_set_pid_nak(USB_FUNCTION_PIPE0);

    g_usb0_function_data_count[USB_FUNCTION_PIPE0]   = size;
    g_usb0_function_data_pointer[USB_FUNCTION_PIPE0] = data;

    mbw = usb0_function_get_mbw(g_usb0_function_data_count[USB_FUNCTION_PIPE0],
                                (uint32_t)g_usb0_function_data_pointer[USB_FUNCTION_PIPE0]);
    usb0_function_set_curpipe(USB_FUNCTION_PIPE0, USB_FUNCTION_CUSE, USB_FUNCTION_CFIFO_WRITE, mbw);
    USB200.CFIFOCTR = USB_FUNCTION_BITBCLR;

    usb0_function_enable_brdy_int(USB_FUNCTION_PIPE0);
    usb0_function_set_pid_buf(USB_FUNCTION_PIPE0);
}

/* End of File */
