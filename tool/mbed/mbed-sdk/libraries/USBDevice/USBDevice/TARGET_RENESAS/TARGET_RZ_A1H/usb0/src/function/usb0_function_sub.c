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
* File Name    : usb0_function_sub.c
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
#if 0
extern const uint16_t *g_usb0_function_EndPntPtr[];
extern uint8_t         g_usb0_function_DeviceDescriptor[];
extern uint8_t        *g_usb0_function_ConfigurationPtr[];
#endif


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb0_function_ResetDCP
* Description  : Initializes the default control pipe(DCP).
* Outline      : Reset default control pipe
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_function_ResetDCP (void)
{
    USB200.DCPCFG  = 0;
#if 0
    USB200.DCPMAXP = g_usb0_function_DeviceDescriptor[7];
#else
    USB200.DCPMAXP = 64;
#endif

    USB200.CFIFOSEL  = (uint16_t)(USB_FUNCTION_BITMBW_8 | USB_FUNCTION_BITBYTE_LITTLE);
    USB200.D0FIFOSEL = (uint16_t)(USB_FUNCTION_BITMBW_8 | USB_FUNCTION_BITBYTE_LITTLE);
    USB200.D1FIFOSEL = (uint16_t)(USB_FUNCTION_BITMBW_8 | USB_FUNCTION_BITBYTE_LITTLE);
}

/*******************************************************************************
* Function Name: usb0_function_ResetEP
* Description  : Initializes the end point.
* Arguments    : uint16_t num          ; Configuration Number
* Return Value : none
*******************************************************************************/
#if 0
void usb0_function_ResetEP (uint16_t num)
{
    uint16_t   pipe;
    uint16_t   ep;
    uint16_t   index;
    uint16_t   buf;
    uint16_t * tbl;

    tbl = (uint16_t *)(g_usb0_function_EndPntPtr[num - 1]);

    for (ep = 1; ep <= USB_FUNCTION_MAX_EP_NO; ++ep)
    {
        if (g_usb0_function_EPTableIndex[ep] != USB_FUNCTION_EP_ERROR)
        {
            index = (uint16_t)(USB_FUNCTION_EPTABLE_LENGTH * g_usb0_function_EPTableIndex[ep]);
            pipe  = (uint16_t)(tbl[index + 0] & USB_FUNCTION_BITCURPIPE);

            g_usb0_function_PipeTbl[pipe] = (uint16_t)( ((tbl[index + 1] & USB_FUNCTION_DIRFIELD) << 3) |
                                                         ep                                             |
                                                         (tbl[index + 0] & USB_FUNCTION_FIFO_USE)          );

            if ((tbl[index + 1] & USB_FUNCTION_DIRFIELD) == USB_FUNCTION_DIR_P_OUT)
            {
                tbl[index + 1] |= USB_FUNCTION_SHTNAKON;
#ifdef  __USB_DMA_BFRE_ENABLE__
                /* this routine cannnot be perfomred if read operation is executed in buffer size */
                if (((tbl[index + 0] & USB_FUNCTION_FIFO_USE) == USB_FUNCTION_D0FIFO_DMA) ||
                    ((tbl[index + 0] & USB_FUNCTION_FIFO_USE) == USB_FUNCTION_D1FIFO_DMA))
                {
                    tbl[index + 1] |= USB_FUNCTION_BFREON;
                }
#endif
            }

            /* Interrupt Disable */
            buf  = USB200.BRDYENB;
            buf &= (uint16_t)~g_usb0_function_bit_set[pipe];
            USB200.BRDYENB = buf;
            buf  = USB200.NRDYENB;
            buf &= (uint16_t)~g_usb0_function_bit_set[pipe];
            USB200.NRDYENB = buf;
            buf  = USB200.BEMPENB;
            buf &= (uint16_t)~g_usb0_function_bit_set[pipe];
            USB200.BEMPENB = buf;

            usb0_function_set_pid_nak(pipe);

            /* CurrentPIPE Clear */
            if (RZA_IO_RegRead_16(&USB200.CFIFOSEL,
                                    USB_CFIFOSEL_CURPIPE_SHIFT,
                                    USB_CFIFOSEL_CURPIPE) == pipe)
            {
                RZA_IO_RegWrite_16(&USB200.CFIFOSEL,
                                    0,
                                    USB_CFIFOSEL_CURPIPE_SHIFT,
                                    USB_CFIFOSEL_CURPIPE);
            }

            if (RZA_IO_RegRead_16(&USB200.D0FIFOSEL,
                                    USB_DnFIFOSEL_CURPIPE_SHIFT,
                                    USB_DnFIFOSEL_CURPIPE) == pipe)
            {
                RZA_IO_RegWrite_16(&USB200.D0FIFOSEL,
                                    0,
                                    USB_DnFIFOSEL_CURPIPE_SHIFT,
                                    USB_DnFIFOSEL_CURPIPE);
            }

            if (RZA_IO_RegRead_16(&USB200.D1FIFOSEL,
                                    USB_DnFIFOSEL_CURPIPE_SHIFT,
                                    USB_DnFIFOSEL_CURPIPE) == pipe)
            {
                RZA_IO_RegWrite_16(&USB200.D1FIFOSEL,
                                    0,
                                    USB_DnFIFOSEL_CURPIPE_SHIFT,
                                    USB_DnFIFOSEL_CURPIPE);
            }

            /* PIPE Configuration */
            USB200.PIPESEL  = pipe;
            USB200.PIPECFG  = tbl[index + 1];
            USB200.PIPEBUF  = tbl[index + 2];
            USB200.PIPEMAXP = tbl[index + 3];
            USB200.PIPEPERI = tbl[index + 4];

            g_usb0_function_pipecfg[pipe]  = tbl[index + 1];
            g_usb0_function_pipebuf[pipe]  = tbl[index + 2];
            g_usb0_function_pipemaxp[pipe] = tbl[index + 3];
            g_usb0_function_pipeperi[pipe] = tbl[index + 4];

            /* Buffer Clear */
            usb0_function_set_sqclr(pipe);
            usb0_function_aclrm(pipe);

            /* init Global */
            g_usb0_function_pipe_status[pipe]  = DEVDRV_USBF_PIPE_IDLE;
            g_usb0_function_PipeDataSize[pipe] = 0;
        }
    }
}
#endif

/*******************************************************************************
* Function Name: usb0_function_EpToPipe
* Description  : Returns the pipe which end point specified by the argument is
*              : allocated to.
* Arguments    : uint16_t ep       ; Direction + Endpoint Number
* Return Value : USB_FUNCTION_EP_ERROR         : Error
*              : Others           : Pipe Number
*******************************************************************************/
uint16_t usb0_function_EpToPipe (uint16_t ep)
{
    uint16_t pipe;

    for (pipe = 1; pipe <= USB_FUNCTION_MAX_PIPE_NO; pipe++)
    {
        if ((g_usb0_function_PipeTbl[pipe] & 0x00ff) == ep)
        {
            return pipe;
        }
    }

    return USB_FUNCTION_EP_ERROR;
}

/*******************************************************************************
* Function Name: usb0_function_InitEPTable
* Description  : Sets the end point by the Alternate setting value of the
*              : configuration number and the interface number specified by the
*              : argument.
* Arguments    : uint16_t Con_Num       ; Configuration Number
*              : uint16_t Int_Num       ; Interface Number
*              : uint16_t Alt_Num       ; Alternate Setting
* Return Value : none
*******************************************************************************/
#if 0
void usb0_function_InitEPTable (uint16_t Con_Num, uint16_t Int_Num, uint16_t Alt_Num)
{
    uint8_t  * ptr;
    uint16_t   point_interface;
    uint16_t   point_endpoint;
    uint16_t   length;
    uint16_t   start;
    uint16_t   numbers;
    uint16_t   endpoint;

    ptr = (uint8_t *)g_usb0_function_ConfigurationPtr[Con_Num - 1];
    point_interface = *ptr;
    length = (uint16_t)((uint16_t)*(ptr + 3) << 8 | (uint16_t)*(ptr + 2));
    ptr  += *ptr;
    start   = 0;
    numbers = 0;
    point_endpoint = 0;

    for (; point_interface < length;)
    {
        switch (*(ptr + 1))                                     /* Descriptor Type ? */
        {
            case USB_FUNCTION_DT_INTERFACE:                     /* Interface */
                if ((*(ptr + 2) == Int_Num) && (*(ptr + 3) == Alt_Num))
                {
                    numbers = *(ptr + 4);
                }
                else
                {
                    start  += *(ptr + 4);
                }
                point_interface += *ptr;
                ptr += *ptr;
            break;

            case USB_FUNCTION_DT_ENDPOINT:                      /* Endpoint */
                if (point_endpoint < numbers)
                {
                    endpoint = (uint16_t)(*(ptr + 2) & 0x0f);
                    g_usb0_function_EPTableIndex[endpoint] = (uint16_t)(start + point_endpoint);
                    ++point_endpoint;
                }
                point_interface += *ptr;
                ptr += *ptr;
            break;

            case USB_FUNCTION_DT_DEVICE:                        /* Device */
            case USB_FUNCTION_DT_CONFIGURATION:                 /* Configuration */
            case USB_FUNCTION_DT_STRING:                        /* String */
            default:                                            /* Class, Vendor, else */
                point_interface += *ptr;
                ptr += *ptr;
            break;
        }
    }
}
#endif

/*******************************************************************************
* Function Name: usb0_function_GetConfigNum
* Description  : Returns the number of configuration referring to the number of
*              : configuration described in the device descriptor.
* Arguments    : none
* Return Value : Number of possible configurations (bNumConfigurations).
*******************************************************************************/
#if 0
uint16_t usb0_function_GetConfigNum (void)
{
    return (uint16_t)g_usb0_function_DeviceDescriptor[17];
}
#endif

/*******************************************************************************
* Function Name: usb0_function_GetInterfaceNum
* Description  : Returns the number of interface referring to the number of
*              : interface described in the configuration descriptor.
* Arguments    : uint16_t num       ; Configuration Number
* Return Value : Number of this interface (bNumInterfaces).
*******************************************************************************/
#if 0
uint16_t usb0_function_GetInterfaceNum (uint16_t num)
{
    return (uint16_t)(*(g_usb0_function_ConfigurationPtr[num - 1] + 4));
}
#endif

/*******************************************************************************
* Function Name: usb0_function_GetAltNum
* Description  : Returns the Alternate setting value of the configuration number
*              : and the interface number specified by the argument.
* Arguments    : uint16_t Con_Num       ; Configuration Number
*              : uint16_t Int_Num       ; Interface Number
* Return Value : Value used to select this alternate setting(bAlternateSetting).
*******************************************************************************/
#if 0
uint16_t usb0_function_GetAltNum (uint16_t Con_Num, uint16_t Int_Num)
{
    uint8_t  * ptr;
    uint16_t   point;
    uint16_t   alt_num = 0;
    uint16_t   length;

    ptr = (uint8_t *)(g_usb0_function_ConfigurationPtr[Con_Num - 1]);
    point = ptr[0];
    ptr  += ptr[0];                                 /* InterfaceDescriptor[0] */
    length  = (uint16_t)(*(g_usb0_function_ConfigurationPtr[Con_Num - 1] + 2));
    length |= (uint16_t)((uint16_t)(*(g_usb0_function_ConfigurationPtr[Con_Num - 1] + 3)) << 8);

    for (; point < length;)                                 /* Search Descriptor Table size */
    {
        switch (ptr[1])                                     /* Descriptor Type ? */
        {
            case USB_FUNCTION_DT_INTERFACE:                 /* Interface */
                if (Int_Num == ptr[2])
                {
                    alt_num = (uint16_t)ptr[3];             /* Alternate Number count */
                }
                point += ptr[0];
                ptr += ptr[0];
            break;

            case USB_FUNCTION_DT_DEVICE:                    /* Device */
            case USB_FUNCTION_DT_CONFIGURATION:             /* Configuration */
            case USB_FUNCTION_DT_STRING:                    /* String */
            case USB_FUNCTION_DT_ENDPOINT:                  /* Endpoint */
            default:                                        /* Class, Vendor, else */
                point += ptr[0];
                ptr   += ptr[0];
            break;
        }
    }
    return alt_num;
}
#endif

/*******************************************************************************
* Function Name: usb0_function_CheckRemoteWakeup
* Description  : Returns the result of the remote wake up function is supported
*              : or not referring to the configuration descriptor.
* Arguments    : none
* Return Value : DEVDRV_USBF_ON     :   Support Remote Wakeup
*              : DEVDRV_USBF_OFF    :   not Support Remote Wakeup
*******************************************************************************/
#if 0
uint16_t usb0_function_CheckRemoteWakeup (void)
{
    uint8_t atr;

    if (g_usb0_function_ConfigNum == 0)
    {
        return DEVDRV_USBF_OFF;
    }

    atr = *(g_usb0_function_ConfigurationPtr[g_usb0_function_ConfigNum - 1] + 7);

    if (atr & USB_FUNCTION_CF_RWUP)
    {
        return DEVDRV_USBF_ON;
    }

    return DEVDRV_USBF_OFF;
}
#endif

/*******************************************************************************
* Function Name: usb0_function_clear_alt
* Description  : Initializes the Alternate setting area.
* Arguments    : none
* Return Value : none
*******************************************************************************/
#if 0
void usb0_function_clear_alt (void)
{
    int i;

    for (i = 0; i < USB_FUNCTION_ALT_NO; ++i)
    {
        g_usb0_function_Alternate[i] = 0;                           /* Alternate */
    }
}
#endif

/*******************************************************************************
* Function Name: usb0_function_clear_pipe_tbl
* Description  : Initializes pipe definition table.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_function_clear_pipe_tbl (void)
{
    int pipe;

    for (pipe = 0; pipe < (USB_FUNCTION_MAX_PIPE_NO + 1); ++pipe)
    {
        g_usb0_function_PipeTbl[pipe] = 0;
    }
}

/*******************************************************************************
* Function Name: usb0_function_clear_ep_table_index
* Description  : Initializes the end point table index.
* Arguments    : none
* Return Value : none
*******************************************************************************/
#if 0
void usb0_function_clear_ep_table_index (void)
{
    int ep;

    for (ep = 0; ep <= USB_FUNCTION_MAX_EP_NO; ++ep)
    {
        g_usb0_function_EPTableIndex[ep] = USB_FUNCTION_EP_ERROR;
    }
}
#endif

/* End of File */
