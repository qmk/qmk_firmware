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
* File Name    : usb1_host_drv_api.c
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
#include "usb1_host.h"
#include "dev_drv.h"


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
static void usb1_host_resetEP(USB_HOST_CFG_PIPETBL_t *tbl);


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb1_api_host_init
* Description  : Initializes USB module in the USB host mode.
*              : USB connection is executed when executing this function in
*              : the states that USB device isconnected to the USB port.
* Arguments    : uint8_t int_level  : USB Module interrupt level
*              : USBU16  mode       : USB_HOST_HIGH_SPEED
*                                   : USB_HOST_FULL_SPEED
*              : uint16_t clockmode : USB Clock mode
* Return Value : USB detach or attach
*              :  USB_HOST_ATTACH
*              :  USB_HOST_DETACH
*******************************************************************************/
uint16_t usb1_api_host_init (uint8_t int_level, uint16_t mode, uint16_t clockmode)
{
    uint16_t         connect;
    volatile uint8_t dummy_buf;

    CPG.STBCR7 &= 0xfc;                         /*The clock of USB0/1 modules is permitted */
    dummy_buf   = CPG.STBCR7;                   /* (Dummy read) */

    g_usb1_host_SupportUsbDeviceSpeed = mode;

    usb1_host_setting_interrupt(int_level);
    usb1_host_reset_module(clockmode);

    g_usb1_host_bchg_flag   = USB_HOST_NO;
    g_usb1_host_detach_flag = USB_HOST_NO;
    g_usb1_host_attach_flag = USB_HOST_NO;

    g_usb1_host_driver_state = USB_HOST_DRV_DETACHED;
    g_usb1_host_default_max_packet[USB_HOST_DEVICE_0] = 64;

    usb1_host_InitModule();

    connect = usb1_host_CheckAttach();

    if (connect == USB_HOST_ATTACH)
    {
        g_usb1_host_attach_flag = USB_HOST_YES;
    }
    else
    {
        usb1_host_UsbDetach2();
    }

    return connect;
}

#if(1) /* ohci_wrapp */
#else
/*******************************************************************************
* Function Name: usb1_api_host_enumeration
* Description  : Initializes USB module in the USB host mode.
*              : USB connection is executed when executing this function in
*              : the states that USB device isconnected to the USB port.
* Arguments    : uint16_t devadr : device address
* Return Value : DEVDRV_USBH_DETACH_ERR       : device detach
*              : DEVDRV_SUCCESS               : device enumeration success
*              : DEVDRV_ERROR                 : device enumeration error
*******************************************************************************/
int32_t usb1_api_host_enumeration (uint16_t devadr)
{
    int32_t  ret;
    uint16_t driver_sts;

    g_usb1_host_setUsbAddress = devadr;

    while (1)
    {
        driver_sts = usb1_api_host_GetUsbDeviceState();

        if (driver_sts == USB_HOST_DRV_DETACHED)
        {
            ret = DEVDRV_USBH_DETACH_ERR;
            break;
        }
        else if (driver_sts == USB_HOST_DRV_CONFIGURED)
        {
            ret = DEVDRV_SUCCESS;
            break;
        }
        else if (driver_sts == USB_HOST_DRV_STALL)
        {
            ret = DEVDRV_ERROR;
            break;
        }
        else if (driver_sts == USB_HOST_DRV_NORES)
        {
            ret = DEVDRV_ERROR;
            break;
        }
        else
        {
            /* Do Nothing */
        }
    }

    if (driver_sts == USB_HOST_DRV_NORES)
    {
        while (1)
        {
            driver_sts = usb1_api_host_GetUsbDeviceState();

            if (driver_sts == USB_HOST_DRV_DETACHED)
            {
                break;
            }
        }
    }

    return ret;
}

/*******************************************************************************
* Function Name: usb1_api_host_detach
* Description  : USB detach routine
* Arguments    : none
* Return Value : USB_HOST_DETACH : USB detach
*              : USB_HOST_ATTACH : USB attach
*              : DEVDRV_ERROR    : error
*******************************************************************************/
int32_t usb1_api_host_detach (void)
{
    int32_t  ret;
    uint16_t driver_sts;

    while (1)
    {
        driver_sts = usb1_api_host_GetUsbDeviceState();

        if (driver_sts == USB_HOST_DRV_DETACHED)
        {
            ret = USB_HOST_DETACH;
            break;
        }
        else if (driver_sts == USB_HOST_DRV_CONFIGURED)
        {
            ret = USB_HOST_ATTACH;
            break;
        }
        else if (driver_sts == USB_HOST_DRV_STALL)
        {
            ret = DEVDRV_ERROR;
            break;
        }
        else if (driver_sts == USB_HOST_DRV_NORES)
        {
            ret = DEVDRV_ERROR;
            break;
        }
        else
        {
            /* Do Nothing */
        }
    }

    if (driver_sts == USB_HOST_DRV_NORES)
    {
        while (1)
        {
            driver_sts = usb1_api_host_GetUsbDeviceState();

            if (driver_sts == USB_HOST_DRV_DETACHED)
            {
                break;
            }
        }
    }

    return ret;
}

/*******************************************************************************
* Function Name: usb1_api_host_data_in
* Description  : Executes USB transfer as data-in in the argument specified pipe.
* Arguments    : uint16_t devadr       ; device address
*              : uint16_t Pipe         ; Pipe Number
*              : uint32_t Size         ; Data Size
*              : uint8_t  *data_buf    ; Data data_buf Address
* Return Value : DEVDRV_SUCCESS       ; success
*              : DEVDRV_ERROR         ; error
*******************************************************************************/
int32_t usb1_api_host_data_in (uint16_t devadr, uint16_t Pipe, uint32_t Size, uint8_t * data_buf)
{
    int32_t ret;

    if (Pipe == USB_HOST_PIPE0)
    {
        return DEVDRV_ERROR;
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipemaxp[Pipe], USB_PIPEMAXP_DEVSEL_SHIFT, USB_PIPEMAXP_DEVSEL) != devadr)
    {
        return DEVDRV_ERROR;
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[Pipe], USB_PIPECFG_DIR_SHIFT, USB_PIPECFG_DIR) == 1)
    {
        return DEVDRV_ERROR;
    }

    if (g_usb1_host_pipe_status[Pipe] == USB_HOST_PIPE_IDLE)
    {
        usb1_host_start_receive_transfer(Pipe, Size, data_buf);
    }
    else
    {
        return DEVDRV_ERROR;                /* Now pipe is busy */
    }

    /* waiting for completing routine           */
    do
    {
        if (g_usb1_host_detach_flag == USB_HOST_YES)
        {
            break;
        }

        if ((g_usb1_host_pipe_status[Pipe] != USB_HOST_PIPE_IDLE) && (g_usb1_host_pipe_status[Pipe] != USB_HOST_PIPE_WAIT))
        {
            break;
        }

    } while (1);

    if (g_usb1_host_detach_flag == USB_HOST_YES)
    {
        return DEVDRV_USBH_DETACH_ERR;
    }

    switch (g_usb1_host_pipe_status[Pipe])
    {
        case USB_HOST_PIPE_DONE:
            ret = DEVDRV_SUCCESS;
        break;

        case USB_HOST_PIPE_STALL:
            ret = DEVDRV_USBH_STALL;
        break;

        case USB_HOST_PIPE_NORES:
            ret = DEVDRV_USBH_COM_ERR;
        break;

        default:
            ret = DEVDRV_ERROR;
        break;
    }

    usb1_host_stop_transfer(Pipe);

    g_usb1_host_pipe_status[Pipe] = USB_HOST_PIPE_IDLE;

    return ret;
}

/*******************************************************************************
* Function Name: usb1_api_host_data_out
* Description  : Executes USB transfer as data-out in the argument specified pipe.
* Arguments    : uint16_t devadr       ; device address
*              : uint16_t Pipe         ; Pipe Number
*              : uint32_t Size         ; Data Size
*              : uint8_t  *data_buf    ; Data data_buf Address
* Return Value : DEVDRV_SUCCESS       ; success
*              : DEVDRV_ERROR         ; error
*******************************************************************************/
int32_t usb1_api_host_data_out (uint16_t devadr, uint16_t Pipe, uint32_t Size, uint8_t * data_buf)
{
    int32_t ret;

    if (Pipe == USB_HOST_PIPE0)
    {
        return DEVDRV_ERROR;
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipemaxp[Pipe], USB_PIPEMAXP_DEVSEL_SHIFT, USB_PIPEMAXP_DEVSEL) != devadr)
    {
        return DEVDRV_ERROR;
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[Pipe], USB_PIPECFG_DIR_SHIFT, USB_PIPECFG_DIR) == 0)
    {
        return DEVDRV_ERROR;
    }

    if (g_usb1_host_pipe_status[Pipe] == USB_HOST_PIPE_IDLE)
    {
        usb1_host_start_send_transfer(Pipe, Size, data_buf);
    }
    else
    {
        return DEVDRV_ERROR;              /* Now pipe is busy */
    }

    /* waiting for completing routine           */
    do
    {
        if (g_usb1_host_detach_flag == USB_HOST_YES)
        {
            break;
        }

        if ((g_usb1_host_pipe_status[Pipe] != USB_HOST_PIPE_IDLE) && (g_usb1_host_pipe_status[Pipe] != USB_HOST_PIPE_WAIT))
        {
            break;
        }

    } while (1);

    if (g_usb1_host_detach_flag == USB_HOST_YES)
    {
        return DEVDRV_USBH_DETACH_ERR;
    }

    switch (g_usb1_host_pipe_status[Pipe])
    {
        case USB_HOST_PIPE_DONE:
            ret = DEVDRV_SUCCESS;
        break;

        case USB_HOST_PIPE_STALL:
            ret = DEVDRV_USBH_STALL;
        break;

        case USB_HOST_PIPE_NORES:
            ret = DEVDRV_USBH_COM_ERR;
        break;

        default:
            ret = DEVDRV_ERROR;
        break;
    }

    usb1_host_stop_transfer(Pipe);

    g_usb1_host_pipe_status[Pipe] = USB_HOST_PIPE_IDLE;

    return ret;
}

/*******************************************************************************
* Function Name: usb1_api_host_control_transfer
* Description  : Executes USB control transfer.
* Arguments    : uint16_t devadr       ; device address
*              : uint16_t Req          ; bmRequestType & bRequest
*              : uint16_t Val          ; wValue
*              : uint16_t Indx         ; wIndex
*              : uint16_t Len          ; wLength
*              : uint8_t  *buf         ; Buffer
* Return Value : DEVDRV_SUCCESS           ; success
*              : DEVDRV_USBH_DETACH_ERR   ; device detach
*              : DEVDRV_USBH_CTRL_COM_ERR ; device no response
*              : DEVDRV_USBH_STALL        ; STALL
*              : DEVDRV_ERROR             ; error
*******************************************************************************/
int32_t usb1_api_host_control_transfer (uint16_t devadr, uint16_t Req, uint16_t Val, uint16_t Indx,
                                                     uint16_t Len, uint8_t * Buf)
{
    int32_t  ret;

    do
    {
        ret = usb1_host_CtrlTransStart(devadr, Req, Val, Indx, Len, Buf);

        if (ret == DEVDRV_SUCCESS)
        {
            if (g_usb1_host_detach_flag == USB_HOST_YES)
            {
                break;
            }

            if ((g_usb1_host_pipe_status[USB_HOST_PIPE0] != USB_HOST_PIPE_IDLE)
                && (g_usb1_host_pipe_status[USB_HOST_PIPE0] != USB_HOST_PIPE_WAIT))
            {
                break;
            }
        }
        else
        {
            return DEVDRV_ERROR;
        }
    } while (1);

    if (g_usb1_host_detach_flag == USB_HOST_YES)
    {
        return DEVDRV_USBH_DETACH_ERR;
    }

    switch (g_usb1_host_pipe_status[USB_HOST_PIPE0])
    {
        case USB_HOST_PIPE_DONE:
            ret = DEVDRV_SUCCESS;
        break;

        case USB_HOST_PIPE_STALL:
            ret = DEVDRV_USBH_STALL;
        break;

        case USB_HOST_PIPE_NORES:
            ret = DEVDRV_USBH_CTRL_COM_ERR;
        break;

        default:
            ret = DEVDRV_ERROR;
        break;
    }

    g_usb1_host_pipe_status[USB_HOST_PIPE0] = USB_HOST_PIPE_IDLE;

    return ret;
}

/*******************************************************************************
* Function Name: usb1_api_host_set_endpoint
* Description  : Sets end point on the information specified in the argument.
* Arguments    : uint16_t                devadr           ; device address
*              : uint8_t                *configdescriptor ; device configration descriptor
*              : USB_HOST_CFG_PIPETBL_t *user_table       ; pipe table
* Return Value : DEVDRV_SUCCESS       ; success
*              : DEVDRV_ERROR         ; error
*******************************************************************************/
int32_t usb1_api_host_set_endpoint (uint16_t devadr, USB_HOST_CFG_PIPETBL_t * user_table, uint8_t * configdescriptor)
{
    uint16_t                ret;
    uint32_t                end_point;
    uint32_t                offset;
    uint32_t                totalLength;
    USB_HOST_CFG_PIPETBL_t * pipe_table;

    /*  End Point Search */
    end_point   = 0;
    offset      = configdescriptor[0];
    totalLength = (uint16_t)(configdescriptor[2] + ((uint16_t)configdescriptor[3] << 8));

    do
    {
        if (configdescriptor[offset + 1] == USB_HOST_ENDPOINT_DESC)
        {
            pipe_table = &user_table[end_point];

            if (pipe_table->pipe_number == 0xffff)
            {
                break;
            }

            ret = usb1_api_host_SetEndpointTable(devadr, pipe_table, (uint8_t *)&configdescriptor[offset]);

            if ((ret != USB_HOST_PIPE_IN) && (ret != USB_HOST_PIPE_OUT))
            {
                return DEVDRV_ERROR;
            }

            ++end_point;
        }

        /* Next End Point Search */
        offset += configdescriptor[offset];

    } while (offset < totalLength);

    return DEVDRV_SUCCESS;
}

/*******************************************************************************
* Function Name: usb1_api_host_clear_endpoint
* Description  : Clears the pipe definition table specified in the argument.
* Arguments    : uint16_t pipe_sel                  : Pipe Number
*              : USB_HOST_CFG_PIPETBL_t *user_table : pipe table
* Return Value : DEVDRV_SUCCESS       ; success
*              : DEVDRV_ERROR         ; error
*******************************************************************************/
int32_t usb1_api_host_clear_endpoint (USB_HOST_CFG_PIPETBL_t * user_table)
{
    uint16_t pipe;

    for (pipe = USB_HOST_PIPE0; pipe <= USB_HOST_MAX_PIPE_NO; ++pipe)
    {
        if (user_table->pipe_number == 0xffff)
        {
            break;
        }
        user_table->pipe_cfg         &= (USB_HOST_DBLBFIELD | USB_HOST_CNTMDFIELD);
        user_table->pipe_max_pktsize  = 0;
        user_table->pipe_cycle        = 0;

        user_table++;
    }

    return DEVDRV_SUCCESS;
}

/*******************************************************************************
* Function Name: usb1_api_host_clear_endpoint_pipe
* Description  : Clears the pipe definition table specified in the argument.
* Arguments    : USB_HOST_CFG_PIPETBL_t *user_table : pipe table
* Return Value : DEVDRV_SUCCESS       ; success
*              : DEVDRV_ERROR         ; error
*******************************************************************************/
int32_t usb1_api_host_clear_endpoint_pipe (uint16_t pipe_sel, USB_HOST_CFG_PIPETBL_t * user_table)
{
    uint16_t pipe;

    for (pipe = USB_HOST_PIPE0; pipe <= USB_HOST_MAX_PIPE_NO; ++pipe)
    {
        if (user_table->pipe_number == 0xffff)
        {
            break;
        }

        if (user_table->pipe_number == pipe_sel)
        {
            user_table->pipe_cfg         &= (USB_HOST_DBLBFIELD | USB_HOST_CNTMDFIELD);
            user_table->pipe_max_pktsize  = 0;
            user_table->pipe_cycle        = 0;
            break;
        }

        user_table++;
    }

    return DEVDRV_SUCCESS;
}
#endif

/*******************************************************************************
* Function Name: usb1_api_host_SetEndpointTable
* Description  : Sets the end point on the information specified by the argument.
* Arguments    : uint16_t devadr                    : device address
*              : USB_HOST_CFG_PIPETBL_t *user_table : pipe table
*              : uint8_t                *Table      : Endpoint descriptor
* Return Value : USB_HOST_DIR_H_IN           ; IN endpoint
*              : USB_HOST_DIR_H_OUT          ; OUT endpoint
*              : USB_END_POINT_ERROR         ; error
*******************************************************************************/
uint16_t usb1_api_host_SetEndpointTable (uint16_t devadr, USB_HOST_CFG_PIPETBL_t * user_table, uint8_t * Table)
{
    uint16_t PipeCfg;
    uint16_t PipeMaxp;
    uint16_t pipe_number;
    uint16_t ret;
    uint16_t ret_flag = 0;                                  // avoid warning.

    pipe_number = user_table->pipe_number;

    if (Table[1] != USB_HOST_ENDPOINT_DESC)
    {
        return USB_END_POINT_ERROR;
    }

    switch (Table[3] & USB_HOST_EP_TYPE)
    {
        case USB_HOST_EP_CNTRL:
            ret_flag = USB_END_POINT_ERROR;
        break;

        case USB_HOST_EP_ISO:
            if ((pipe_number != USB_HOST_PIPE1) && (pipe_number != USB_HOST_PIPE2))
            {
                return USB_END_POINT_ERROR;
            }

            PipeCfg = USB_HOST_ISO;
        break;

        case USB_HOST_EP_BULK:
            if ((pipe_number < USB_HOST_PIPE1) || (pipe_number > USB_HOST_PIPE5))
            {
                return USB_END_POINT_ERROR;
            }

            PipeCfg = USB_HOST_BULK;
        break;

        case USB_HOST_EP_INT:
            if ((pipe_number < USB_HOST_PIPE6) || (pipe_number > USB_HOST_PIPE9))
            {
                return USB_END_POINT_ERROR;
            }

            PipeCfg = USB_HOST_INTERRUPT;
        break;

        default:
            ret_flag = USB_END_POINT_ERROR;
        break;
    }

    if (ret_flag == USB_END_POINT_ERROR)
    {
        return ret_flag;
    }

    /* Set pipe configuration table */
    if ((Table[2] & USB_HOST_EP_DIR_MASK) == USB_HOST_EP_IN)        /* IN(receive) */
    {
        if (PipeCfg == USB_HOST_ISO)
        {
            /* Transfer Type is ISO*/
            PipeCfg |= USB_HOST_DIR_H_IN;

            switch (user_table->fifo_port)
            {
                case USB_HOST_CUSE:
                case USB_HOST_D0USE:
                case USB_HOST_D1USE:
                case USB_HOST_D0DMA:
                case USB_HOST_D1DMA:
                    PipeCfg |= (uint16_t)(user_table->pipe_cfg & USB_HOST_DBLBFIELD);
                break;

                default:
                    ret_flag = USB_END_POINT_ERROR;
                break;
            }

            if (ret_flag == USB_END_POINT_ERROR)
            {
                return ret_flag;
            }
        }
        else
        {
            /* Transfer Type is BULK or INT */
            PipeCfg |= (USB_HOST_SHTNAKON | USB_HOST_DIR_H_IN);             /* Compulsory SHTNAK */

            switch (user_table->fifo_port)
            {
                case USB_HOST_CUSE:
                case USB_HOST_D0USE:
                case USB_HOST_D1USE:
                    PipeCfg |= (uint16_t)(user_table->pipe_cfg & (USB_HOST_DBLBFIELD | USB_HOST_CNTMDFIELD));
                break;

                case USB_HOST_D0DMA:
                case USB_HOST_D1DMA:
                    PipeCfg |= (uint16_t)(user_table->pipe_cfg & (USB_HOST_DBLBFIELD | USB_HOST_CNTMDFIELD));
#ifdef  __USB_DMA_BFRE_ENABLE__
                    /* this routine cannnot be perfomred if read operation is executed in buffer size */
                    PipeCfg |= USB_HOST_BFREON;
#endif
                break;

                default:
                    ret_flag = USB_END_POINT_ERROR;
                break;
            }

            if (ret_flag == USB_END_POINT_ERROR)
            {
                return ret_flag;
            }
        }
        ret = USB_HOST_PIPE_IN;
    }
    else                                                            /* OUT(send)    */
    {
        if (PipeCfg == USB_HOST_ISO)
        {
            /* Transfer Type is ISO*/
            PipeCfg |= (uint16_t)(user_table->pipe_cfg & USB_HOST_DBLBFIELD);
        }
        else
        {
            /* Transfer Type is BULK or INT */
            PipeCfg |= (uint16_t)(user_table->pipe_cfg & (USB_HOST_DBLBFIELD | USB_HOST_CNTMDFIELD));
        }
        PipeCfg |= USB_HOST_DIR_H_OUT;
        ret = USB_HOST_PIPE_OUT;
    }

    switch (user_table->fifo_port)
    {
        case USB_HOST_CUSE:
            g_usb1_host_PipeTbl[pipe_number] = (uint16_t)USB_HOST_CFIFO_USE;
        break;

        case USB_HOST_D0USE:
            g_usb1_host_PipeTbl[pipe_number] = (uint16_t)USB_HOST_D0FIFO_USE;
        break;

        case USB_HOST_D1USE:
            g_usb1_host_PipeTbl[pipe_number] = (uint16_t)USB_HOST_D1FIFO_USE;
        break;

        case USB_HOST_D0DMA:
            g_usb1_host_PipeTbl[pipe_number] = (uint16_t)USB_HOST_D0FIFO_DMA;
        break;

        case USB_HOST_D1DMA:
            g_usb1_host_PipeTbl[pipe_number] = (uint16_t)USB_HOST_D1FIFO_DMA;
        break;

        default:
            ret_flag = USB_END_POINT_ERROR;
        break;
    }

    if (ret_flag == USB_END_POINT_ERROR)
    {
        return ret_flag;
    }

    /* Endpoint number set              */
    PipeCfg  |= (uint16_t)(Table[2] & USB_HOST_EP_NUM_MASK);
    g_usb1_host_PipeTbl[pipe_number] |= (uint16_t)(Table[2] & USB_HOST_EP_NUM_MASK);

    /* Max packet size set              */
    PipeMaxp  = (uint16_t)((uint16_t)Table[4] | (uint16_t)((uint16_t)Table[5] << 8));

    if (PipeMaxp == 0u)
    {
        return USB_END_POINT_ERROR;
    }

    /* Set device address               */
    PipeMaxp |= (uint16_t)(devadr << 12);

    user_table->pipe_cfg         = PipeCfg;
    user_table->pipe_max_pktsize = PipeMaxp;

    usb1_host_resetEP(user_table);

    return ret;
}

/*******************************************************************************
* Function Name: usb1_host_resetEP
* Description  : Sets the end point on the information specified by the argument.
* Arguments    : USB_HOST_CFG_PIPETBL_t *tbl : pipe table
* Return Value : none
*******************************************************************************/
static void usb1_host_resetEP (USB_HOST_CFG_PIPETBL_t * tbl)
{

    uint16_t pipe;

    /* Host pipe */
    /* The pipe number of pipe definition table is obtained */
    pipe = (uint16_t)(tbl->pipe_number & USB_HOST_BITCURPIPE);  /* Pipe Number */

    /* FIFO port access pipe is set to initial value */
    /* The connection with FIFO should be cut before setting the pipe */
    if (RZA_IO_RegRead_16(&USB201.CFIFOSEL,
                            USB_CFIFOSEL_CURPIPE_SHIFT,
                            USB_CFIFOSEL_CURPIPE) == pipe)
    {
        usb1_host_change_fifo_port(USB_HOST_PIPE0, USB_HOST_CUSE, USB_HOST_NO, USB_HOST_BITMBW_16);
    }

    if (RZA_IO_RegRead_16(&USB201.D0FIFOSEL,
                            USB_DnFIFOSEL_CURPIPE_SHIFT,
                            USB_DnFIFOSEL_CURPIPE) == pipe)
    {
        usb1_host_change_fifo_port(USB_HOST_PIPE0, USB_HOST_D0USE, USB_HOST_NO, USB_HOST_BITMBW_16);
    }

    if (RZA_IO_RegRead_16(&USB201.D1FIFOSEL,
                            USB_DnFIFOSEL_CURPIPE_SHIFT,
                            USB_DnFIFOSEL_CURPIPE) == pipe)
    {
        usb1_host_change_fifo_port(USB_HOST_PIPE0, USB_HOST_D1USE, USB_HOST_NO, USB_HOST_BITMBW_16);
    }

    /* Interrupt of pipe set is disabled */
    usb1_host_disable_brdy_int(pipe);
    usb1_host_disable_nrdy_int(pipe);
    usb1_host_disable_bemp_int(pipe);

    /* Pipe to set is set to NAK */
    usb1_host_set_pid_nak(pipe);

    /* Pipe is set */
    USB201.PIPESEL  = pipe;

    USB201.PIPECFG  = tbl->pipe_cfg;
    USB201.PIPEBUF  = tbl->pipe_buf;
    USB201.PIPEMAXP = tbl->pipe_max_pktsize;
    USB201.PIPEPERI = tbl->pipe_cycle;

    g_usb1_host_pipecfg[pipe]  = tbl->pipe_cfg;
    g_usb1_host_pipebuf[pipe]  = tbl->pipe_buf;
    g_usb1_host_pipemaxp[pipe] = tbl->pipe_max_pktsize;
    g_usb1_host_pipeperi[pipe] = tbl->pipe_cycle;

    /* Sequence bit clear */
    usb1_host_set_sqclr(pipe);

    usb1_host_aclrm(pipe);
    usb1_host_set_csclr(pipe);

    /* Pipe window selection is set to unused */
    USB201.PIPESEL = USB_HOST_PIPE0;

}

#if(1) /* ohci_wrapp */
#else
/*******************************************************************************
* Function Name: usb1_api_host_data_count
* Description  : Get g_usb0_host_data_count[pipe]
* Arguments    : uint16_t pipe        ; Pipe Number
*              : uint32_t *data_count ; return g_usb0_data_count[pipe]
* Return Value : DEVDRV_SUCCESS    ; success
*              : DEVDRV_ERROR      ; error
*******************************************************************************/
int32_t usb1_api_host_data_count (uint16_t pipe, uint32_t * data_count)
{
    if (pipe > USB_HOST_MAX_PIPE_NO)
    {
        return DEVDRV_ERROR;
    }

    *data_count = g_usb1_host_PipeDataSize[pipe];

    return DEVDRV_SUCCESS;
}
#endif

/* End of File */
