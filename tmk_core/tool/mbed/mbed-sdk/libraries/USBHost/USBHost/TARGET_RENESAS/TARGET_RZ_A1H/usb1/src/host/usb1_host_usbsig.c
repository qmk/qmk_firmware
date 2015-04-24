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
* File Name    : usb1_host_usbsig.c
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
static void usb1_host_EnableINT_Module(void);
static void usb1_host_Enable_AttachINT(void);
static void usb1_host_Disable_AttachINT(void);
static void usb1_host_Disable_BchgINT(void);


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb1_host_InitModule
* Description  : Initializes the USB module in USB host module.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_InitModule (void)
{
    uint16_t buf1;
    uint16_t buf2;
    uint16_t buf3;

    usb1_host_init_pipe_status();

    RZA_IO_RegWrite_16(&USB201.SYSCFG0,
                        1,
                        USB_SYSCFG_DCFM_SHIFT,
                        USB_SYSCFG_DCFM);       /* HOST mode */
    RZA_IO_RegWrite_16(&USB201.SYSCFG0,
                        1,
                        USB_SYSCFG_DRPD_SHIFT,
                        USB_SYSCFG_DRPD);       /* PORT0 D+, D- setting */

    do
    {
        buf1 = RZA_IO_RegRead_16(&USB201.SYSSTS0,
                                USB_SYSSTS0_LNST_SHIFT,
                                USB_SYSSTS0_LNST);
        Userdef_USB_usb1_host_delay_xms(50);
        buf2 = RZA_IO_RegRead_16(&USB201.SYSSTS0,
                                USB_SYSSTS0_LNST_SHIFT,
                                USB_SYSSTS0_LNST);
        Userdef_USB_usb1_host_delay_xms(50);
        buf3 = RZA_IO_RegRead_16(&USB201.SYSSTS0,
                                USB_SYSSTS0_LNST_SHIFT,
                                USB_SYSSTS0_LNST);

    } while ((buf1 != buf2) || (buf1 != buf3));

    RZA_IO_RegWrite_16(&USB201.SYSCFG0,
                        1,
                        USB_SYSCFG_USBE_SHIFT,
                        USB_SYSCFG_USBE);

    USB201.CFIFOSEL  = (uint16_t)(USB_HOST_BITRCNT | USB_HOST_BITMBW_8 | USB_HOST_BITBYTE_LITTLE);
    USB201.D0FIFOSEL = (uint16_t)(                   USB_HOST_BITMBW_8 | USB_HOST_BITBYTE_LITTLE);
    USB201.D1FIFOSEL = (uint16_t)(                   USB_HOST_BITMBW_8 | USB_HOST_BITBYTE_LITTLE);
}

/*******************************************************************************
* Function Name: usb1_host_CheckAttach
* Description  : Returns the USB device connection state.
* Arguments    : none
* Return Value : uint16_t ; USB_HOST_ATTACH : Attached
*              :          ; USB_HOST_DETACH : not Attached
*******************************************************************************/
uint16_t usb1_host_CheckAttach (void)
{
    uint16_t buf1;
    uint16_t buf2;
    uint16_t buf3;
    uint16_t rhst;

    do
    {
        buf1 = RZA_IO_RegRead_16(&USB201.SYSSTS0,
                                USB_SYSSTS0_LNST_SHIFT,
                                USB_SYSSTS0_LNST);
        Userdef_USB_usb1_host_delay_xms(50);
        buf2 = RZA_IO_RegRead_16(&USB201.SYSSTS0,
                                USB_SYSSTS0_LNST_SHIFT,
                                USB_SYSSTS0_LNST);
        Userdef_USB_usb1_host_delay_xms(50);
        buf3 = RZA_IO_RegRead_16(&USB201.SYSSTS0,
                                USB_SYSSTS0_LNST_SHIFT,
                                USB_SYSSTS0_LNST);

    } while ((buf1 != buf2) || (buf1 != buf3));

    rhst = RZA_IO_RegRead_16(&USB201.DVSTCTR0,
                                USB_DVSTCTR0_RHST_SHIFT,
                                USB_DVSTCTR0_RHST);
    if (rhst == USB_HOST_UNDECID)
    {
        if (buf1 == USB_HOST_FS_JSTS)
        {
            if (g_usb1_host_SupportUsbDeviceSpeed == USB_HOST_HIGH_SPEED)
            {
                RZA_IO_RegWrite_16(&USB201.SYSCFG0,
                                    1,
                                    USB_SYSCFG_HSE_SHIFT,
                                    USB_SYSCFG_HSE);
            }
            else
            {
                RZA_IO_RegWrite_16(&USB201.SYSCFG0,
                                    0,
                                    USB_SYSCFG_HSE_SHIFT,
                                    USB_SYSCFG_HSE);
            }
            return USB_HOST_ATTACH;
        }
        else if (buf1 == USB_HOST_LS_JSTS)
        {
            /* Low Speed Device */
            RZA_IO_RegWrite_16(&USB201.SYSCFG0,
                                0,
                                USB_SYSCFG_HSE_SHIFT,
                                USB_SYSCFG_HSE);
            return USB_HOST_ATTACH;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else if ((rhst == USB_HOST_HSMODE) || (rhst == USB_HOST_FSMODE))
    {
        return USB_HOST_ATTACH;
    }
    else if (rhst == USB_HOST_LSMODE)
    {
        return USB_HOST_ATTACH;
    }
    else
    {
        /* Do Nothing */
    }

    return USB_HOST_DETACH;
}

/*******************************************************************************
* Function Name: usb1_host_UsbAttach
* Description  : Connects the USB device.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_UsbAttach (void)
{
    usb1_host_EnableINT_Module();
    usb1_host_Disable_BchgINT();
    usb1_host_Disable_AttachINT();
    usb1_host_Enable_DetachINT();
}

/*******************************************************************************
* Function Name: usb1_host_UsbDetach
* Description  : Disconnects the USB device.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_UsbDetach (void)
{
    uint16_t pipe;
    uint16_t devadr;

    g_usb1_host_driver_state = USB_HOST_DRV_DETACHED;

    /* Terminate all the pipes in which communications on port  */
    /* are currently carried out                                */
    for (pipe = 0; pipe < (USB_HOST_MAX_PIPE_NO + 1); ++pipe)
    {
        if (g_usb1_host_pipe_status[pipe] != USB_HOST_PIPE_IDLE)
        {
            if (pipe == USB_HOST_PIPE0)
            {
                devadr = RZA_IO_RegRead_16(&USB201.DCPMAXP,
                                            USB_DCPMAXP_DEVSEL_SHIFT,
                                            USB_DCPMAXP_DEVSEL);
            }
            else
            {
                devadr = RZA_IO_RegRead_16(&g_usb1_host_pipemaxp[pipe], USB_PIPEMAXP_DEVSEL_SHIFT, USB_PIPEMAXP_DEVSEL);
            }

            if (devadr == g_usb1_host_UsbAddress)
            {
                usb1_host_stop_transfer(pipe);
            }

            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_IDLE;
        }
    }

    g_usb1_host_ConfigNum  = 0;
    g_usb1_host_UsbAddress = 0;
    g_usb1_host_default_max_packet[USB_HOST_DEVICE_0] = 64;

    usb1_host_UsbDetach2();
}

/*******************************************************************************
* Function Name: usb1_host_UsbDetach2
* Description  : Disconnects the USB device.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_UsbDetach2 (void)
{
    usb1_host_Disable_DetachINT();
    usb1_host_Disable_BchgINT();
    usb1_host_Enable_AttachINT();
}

/*******************************************************************************
* Function Name: usb1_host_UsbBusReset
* Description  : Issues the USB bus reset signal.
* Arguments    : none
* Return Value : uint16_t               ; RHST
*******************************************************************************/
uint16_t usb1_host_UsbBusReset (void)
{
    uint16_t buffer;
    uint16_t loop;

    RZA_IO_RegWrite_16(&USB201.DVSTCTR0,
                        1,
                        USB_DVSTCTR0_USBRST_SHIFT,
                        USB_DVSTCTR0_USBRST);
    RZA_IO_RegWrite_16(&USB201.DVSTCTR0,
                        0,
                        USB_DVSTCTR0_UACT_SHIFT,
                        USB_DVSTCTR0_UACT);

    Userdef_USB_usb1_host_delay_xms(50);

    buffer  = USB201.DVSTCTR0;
    buffer &= (uint16_t)(~(USB_HOST_BITRST));
    buffer |= USB_HOST_BITUACT;
    USB201.DVSTCTR0 = buffer;

    Userdef_USB_usb1_host_delay_xms(20);

    for (loop = 0, buffer = USB_HOST_HSPROC;  loop < 3; ++loop)
    {
        buffer = RZA_IO_RegRead_16(&USB201.DVSTCTR0,
                                    USB_DVSTCTR0_RHST_SHIFT,
                                    USB_DVSTCTR0_RHST);
        if (buffer == USB_HOST_HSPROC)
        {
            Userdef_USB_usb1_host_delay_xms(10);
        }
        else
        {
            break;
        }
    }

    return buffer;
}

/*******************************************************************************
* Function Name: usb1_host_UsbResume
* Description  : Issues the USB resume signal.
* Arguments    : none
* Return Value : int32_t            ; DEVDRV_SUCCESS
*              :                    ; DEVDRV_ERROR
*******************************************************************************/
int32_t usb1_host_UsbResume (void)
{
    uint16_t buf;

    if ((g_usb1_host_driver_state & USB_HOST_DRV_SUSPEND) == 0)
    {
        /* not SUSPEND */
        return DEVDRV_ERROR;
    }

    RZA_IO_RegWrite_16(&USB201.INTENB1,
                        0,
                        USB_INTENB1_BCHGE_SHIFT,
                        USB_INTENB1_BCHGE);
    RZA_IO_RegWrite_16(&USB201.DVSTCTR0,
                        1,
                        USB_DVSTCTR0_RESUME_SHIFT,
                        USB_DVSTCTR0_RESUME);
    Userdef_USB_usb1_host_delay_xms(20);

    buf  = USB201.DVSTCTR0;
    buf &= (uint16_t)(~(USB_HOST_BITRESUME));
    buf |= USB_HOST_BITUACT;
    USB201.DVSTCTR0 = buf;

    g_usb1_host_driver_state &= (uint16_t)~USB_HOST_DRV_SUSPEND;

    return DEVDRV_SUCCESS;
}

/*******************************************************************************
* Function Name: usb1_host_UsbSuspend
* Description  : Issues the USB suspend signal.
* Arguments    : none
* Return Value : int32_t            ; DEVDRV_SUCCESS   :not SUSPEND
*              :                    ; DEVDRV_ERROR     :SUSPEND
*******************************************************************************/
int32_t usb1_host_UsbSuspend (void)
{
    uint16_t buf;

    if ((g_usb1_host_driver_state & USB_HOST_DRV_SUSPEND) != 0)
    {
        /* SUSPEND */
        return DEVDRV_ERROR;
    }

    RZA_IO_RegWrite_16(&USB201.DVSTCTR0,
                        0,
                        USB_DVSTCTR0_UACT_SHIFT,
                        USB_DVSTCTR0_UACT);

    Userdef_USB_usb1_host_delay_xms(5);

    buf = RZA_IO_RegRead_16(&USB201.SYSSTS0,
                                USB_SYSSTS0_LNST_SHIFT,
                                USB_SYSSTS0_LNST);
    if ((buf != USB_HOST_FS_JSTS) && (buf != USB_HOST_LS_JSTS))
    {
        usb1_host_UsbDetach();
    }
    else
    {
        g_usb1_host_driver_state |= USB_HOST_DRV_SUSPEND;
    }

    return DEVDRV_SUCCESS;
}

/*******************************************************************************
* Function Name: usb1_host_Enable_DetachINT
* Description  : Enables the USB disconnection interrupt.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_Enable_DetachINT (void)
{
    USB201.INTSTS1 = (uint16_t)(~(USB_HOST_BITDTCH));
    RZA_IO_RegWrite_16(&USB201.INTENB1,
                        1,
                        USB_INTENB1_DTCHE_SHIFT,
                        USB_INTENB1_DTCHE);
}

/*******************************************************************************
* Function Name: usb1_host_Disable_DetachINT
* Description  : Disables the USB disconnection interrupt.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_Disable_DetachINT (void)
{
    USB201.INTSTS1 = (uint16_t)(~(USB_HOST_BITDTCH));
    RZA_IO_RegWrite_16(&USB201.INTENB1,
                        0,
                        USB_INTENB1_DTCHE_SHIFT,
                        USB_INTENB1_DTCHE);
}

/*******************************************************************************
* Function Name: usb1_host_Enable_AttachINT
* Description  : Enables the USB connection detection interrupt.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_Enable_AttachINT (void)
{
    USB201.INTSTS1 = (uint16_t)(~(USB_HOST_BITATTCH));
    RZA_IO_RegWrite_16(&USB201.INTENB1,
                        1,
                        USB_INTENB1_ATTCHE_SHIFT,
                        USB_INTENB1_ATTCHE);
}

/*******************************************************************************
* Function Name: usb1_host_Disable_AttachINT
* Description  : Disables the USB connection detection interrupt.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_Disable_AttachINT (void)
{
    USB201.INTSTS1 = (uint16_t)(~(USB_HOST_BITATTCH));
    RZA_IO_RegWrite_16(&USB201.INTENB1,
                        0,
                        USB_INTENB1_ATTCHE_SHIFT,
                        USB_INTENB1_ATTCHE);
}

/*******************************************************************************
* Function Name: usb1_host_Disable_BchgINT
* Description  : Disables the USB bus change detection interrupt.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_Disable_BchgINT (void)
{
    USB201.INTSTS1 = (uint16_t)(~(USB_HOST_BITBCHG));
    RZA_IO_RegWrite_16(&USB201.INTENB1,
                        0,
                        USB_INTENB1_BCHGE_SHIFT,
                        USB_INTENB1_BCHGE);
}

/*******************************************************************************
* Function Name: usb1_host_set_devadd
* Description  : DEVADDn register is set by specified value
* Arguments    : uint16_t addr             : Device address
*              : uint16_t *devadd          : Set value
* Return Value : none
*******************************************************************************/
void usb1_host_set_devadd (uint16_t addr, uint16_t * devadd)
{
    uint16_t * ptr;
    uint16_t ret_flag = DEVDRV_FLAG_ON;                             // avoid warning.

    switch (addr)
    {
        case USB_HOST_DEVICE_0:
            ptr = (uint16_t *)&USB201.DEVADD0;
        break;

        case USB_HOST_DEVICE_1:
            ptr = (uint16_t *)&USB201.DEVADD1;
        break;

        case USB_HOST_DEVICE_2:
            ptr = (uint16_t *)&USB201.DEVADD2;
        break;

        case USB_HOST_DEVICE_3:
            ptr = (uint16_t *)&USB201.DEVADD3;
        break;

        case USB_HOST_DEVICE_4:
            ptr = (uint16_t *)&USB201.DEVADD4;
        break;

        case USB_HOST_DEVICE_5:
            ptr = (uint16_t *)&USB201.DEVADD5;
        break;

        case USB_HOST_DEVICE_6:
            ptr = (uint16_t *)&USB201.DEVADD6;
        break;

        case USB_HOST_DEVICE_7:
            ptr = (uint16_t *)&USB201.DEVADD7;
        break;

        case USB_HOST_DEVICE_8:
            ptr = (uint16_t *)&USB201.DEVADD8;
        break;

        case USB_HOST_DEVICE_9:
            ptr = (uint16_t *)&USB201.DEVADD9;
        break;

        case USB_HOST_DEVICE_10:
            ptr = (uint16_t *)&USB201.DEVADDA;
        break;

        default:
            ret_flag = DEVDRV_FLAG_OFF;
        break;
    }

    if (ret_flag == DEVDRV_FLAG_ON)
    {
        *ptr = (uint16_t)(*devadd & USB_HOST_DEVADD_MASK);
    }
}

/*******************************************************************************
* Function Name: usb1_host_get_devadd
* Description  : DEVADDn register is obtained
* Arguments    : uint16_t addr      : Device address
*              : uint16_t *devadd   : USB_HOST_DEVADD register value
* Return Value : none
*******************************************************************************/
void usb1_host_get_devadd (uint16_t addr, uint16_t * devadd)
{
    uint16_t * ptr;
    uint16_t ret_flag = DEVDRV_FLAG_ON;                             // avoid warning.

    switch (addr)
    {
        case USB_HOST_DEVICE_0:
            ptr = (uint16_t *)&USB201.DEVADD0;
        break;

        case USB_HOST_DEVICE_1:
            ptr = (uint16_t *)&USB201.DEVADD1;
        break;

        case USB_HOST_DEVICE_2:
            ptr = (uint16_t *)&USB201.DEVADD2;
        break;

        case USB_HOST_DEVICE_3:
            ptr = (uint16_t *)&USB201.DEVADD3;
        break;

        case USB_HOST_DEVICE_4:
            ptr = (uint16_t *)&USB201.DEVADD4;
        break;

        case USB_HOST_DEVICE_5:
            ptr = (uint16_t *)&USB201.DEVADD5;
        break;

        case USB_HOST_DEVICE_6:
            ptr = (uint16_t *)&USB201.DEVADD6;
        break;

        case USB_HOST_DEVICE_7:
            ptr = (uint16_t *)&USB201.DEVADD7;
        break;

        case USB_HOST_DEVICE_8:
            ptr = (uint16_t *)&USB201.DEVADD8;
        break;

        case USB_HOST_DEVICE_9:
            ptr = (uint16_t *)&USB201.DEVADD9;
        break;

        case USB_HOST_DEVICE_10:
            ptr = (uint16_t *)&USB201.DEVADDA;
        break;

        default:
            ret_flag = DEVDRV_FLAG_OFF;
        break;
    }

    if (ret_flag == DEVDRV_FLAG_ON)
    {
        *devadd = *ptr;
    }
}

/*******************************************************************************
* Function Name: usb1_host_EnableINT_Module
* Description  : Enables BEMP/NRDY/BRDY interrupt and SIGN/SACK interrupt.
*              : Enables NRDY/BEMP interrupt in the pipe0.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb1_host_EnableINT_Module (void)
{
    uint16_t buf;

    buf  = USB201.INTENB0;
    buf |= (USB_HOST_BITBEMPE | USB_HOST_BITNRDYE | USB_HOST_BITBRDYE);
    USB201.INTENB0 = buf;

    buf  = USB201.INTENB1;
    buf |= (USB_HOST_BITSIGNE | USB_HOST_BITSACKE);
    USB201.INTENB1 = buf;

    usb1_host_enable_nrdy_int(USB_HOST_PIPE0);
    usb1_host_enable_bemp_int(USB_HOST_PIPE0);
}

/* End of File */
