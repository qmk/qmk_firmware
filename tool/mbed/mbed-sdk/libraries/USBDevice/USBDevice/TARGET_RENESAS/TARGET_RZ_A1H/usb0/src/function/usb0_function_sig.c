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
* File Name    : usb0_function_sig.c
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
static void usb0_function_EnableINTModule(void);


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb0_function_InitModule
* Description  : Initializes the USB module in the USB function mode.
* Arguments    : uint16_t mode  ; USB_FUNCTION_HIGH_SPEED ; Hi-Speed Mode
*              :                ; other                   ; Full-speed Mode
* Return Value : none
*******************************************************************************/
void usb0_function_InitModule (uint16_t mode)
{
    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        0,
                        USB_SYSCFG_DCFM_SHIFT,
                        USB_SYSCFG_DCFM);           /* USB function */

    /* USB module operation enabled     */
    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        1,
                        USB_SYSCFG_USBE_SHIFT,
                        USB_SYSCFG_USBE);

    if (mode == USB_FUNCTION_HIGH_SPEED)
    {
        RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                            1,
                            USB_SYSCFG_HSE_SHIFT,
                            USB_SYSCFG_HSE);        /* Hi-Speed Mode */
    }
    else
    {
        RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                            0,
                            USB_SYSCFG_HSE_SHIFT,
                            USB_SYSCFG_HSE);
    }

    /* for power-on                     */
    if (usb0_function_CheckVBUStaus() == DEVDRV_USBF_ON)
    {
        usb0_function_EnableINTModule();            /* Interrupt Enable         */
        usb0_function_USB_FUNCTION_Attach();        /* pull-up D+ and open D-   */
    }
    else
    {
        usb0_function_USB_FUNCTION_Detach();        /* USB Detach               */
                                                    /* with Interrupt Enable    */
    }
}

/*******************************************************************************
* Function Name: usb0_function_CheckVBUStaus
* Description  : Checks the USB-VBUS state to returns the connection state to
*              : the USB host.
* Arguments    : none
* Return Value : DEVDRV_USBF_ON     :   VBUS ON
*              : DEVDRV_USBF_OFF    :   VBUS OFF
*******************************************************************************/
uint16_t usb0_function_CheckVBUStaus (void)
{
    uint16_t buf1;
    uint16_t buf2;
    uint16_t buf3;

    /* monitor VBUS pins */
    do
    {
        buf1 = RZA_IO_RegRead_16(&USB200.INTSTS0,
                                USB_INTSTS0_VBSTS_SHIFT,
                                USB_INTSTS0_VBSTS);
        Userdef_USB_usb0_function_delay_10us(1);
        buf2 = RZA_IO_RegRead_16(&USB200.INTSTS0,
                                USB_INTSTS0_VBSTS_SHIFT,
                                USB_INTSTS0_VBSTS);
        Userdef_USB_usb0_function_delay_10us(1);
        buf3 = RZA_IO_RegRead_16(&USB200.INTSTS0,
                                USB_INTSTS0_VBSTS_SHIFT,
                                USB_INTSTS0_VBSTS);
    } while ((buf1 != buf2) || (buf2 != buf3));

    if (buf1 == DEVDRV_USBF_OFF)
    {
        return DEVDRV_USBF_OFF;         /* detach */
    }

    return DEVDRV_USBF_ON;              /* attach */
}

/*******************************************************************************
* Function Name: usb0_function_USB_FUNCTION_Attach
* Description  : Connects to the USB host controller.
*              : This function pulls up D+.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_function_USB_FUNCTION_Attach (void)
{
    Userdef_USB_usb0_function_attach();

    Userdef_USB_usb0_function_delay_xms(10);

    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        1,
                        USB_SYSCFG_DPRPU_SHIFT,
                        USB_SYSCFG_DPRPU);      /* Pull-up D+ and open D- */
}

/*******************************************************************************
* Function Name: usb0_function_USB_FUNCTION_Detach
* Description  : Disconnects from the USB host controller.
*              : This function opens D+/D-.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_function_USB_FUNCTION_Detach (void)
{
    uint16_t pipe;

    Userdef_USB_usb0_function_detach();

    for (pipe = 0; pipe < (USB_FUNCTION_MAX_PIPE_NO + 1); ++pipe)
    {
        if (g_usb0_function_pipe_status[pipe] != DEVDRV_USBF_PIPE_IDLE)
        {
            usb0_function_stop_transfer(pipe);
        }
    }

    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        0,
                        USB_SYSCFG_DPRPU_SHIFT,
                        USB_SYSCFG_DPRPU);                  /* open D+ and D- */

    /* Detach Recovery */
    Userdef_USB_usb0_function_delay_500ns();                /* need 1us=500ns * 2 wait */
    Userdef_USB_usb0_function_delay_500ns();

    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        1,
                        USB_SYSCFG_DCFM_SHIFT,
                        USB_SYSCFG_DCFM);
    Userdef_USB_usb0_function_delay_500ns();                /* need 100ns wait but 500ns S/W wait */

    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        0,
                        USB_SYSCFG_DCFM_SHIFT,
                        USB_SYSCFG_DCFM);

    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        0,
                        USB_SYSCFG_USBE_SHIFT,
                        USB_SYSCFG_USBE);       /* soft reset module */
    Userdef_USB_usb0_function_delay_500ns();

    RZA_IO_RegWrite_16(&USB200.SYSCFG0,
                        1,
                        USB_SYSCFG_USBE_SHIFT,
                        USB_SYSCFG_USBE);

    usb0_function_EnableINTModule();            /* Interrupt Enable */
}

/*******************************************************************************
* Function Name: usb0_function_USB_FUNCTION_BusReset
* Description  : This function is executed when the USB device is transitioned
*              : to POWERD_STATE. Sets the device descriptor according to the
*              : connection speed determined by the USB reset hand shake.
* Arguments    : none
* Return Value : none
*******************************************************************************/
#if 0	/*The USBHAL in mbed does not need this function*/
void usb0_function_USB_FUNCTION_BusReset (void)
{
    usb0_function_init_status();                                    /* memory clear */

    if (usb0_function_is_hispeed() == USB_FUNCTION_HIGH_SPEED)
    {
        usb0_function_ResetDescriptor(USB_FUNCTION_HIGH_SPEED);     /* Device Descriptor reset */
    }
    else
    {
        usb0_function_ResetDescriptor(USB_FUNCTION_FULL_SPEED);     /* Device Descriptor reset */
    }

    usb0_function_ResetDCP();                                       /* Default Control PIPE reset */
}
#endif

/*******************************************************************************
* Function Name: usb0_function_USB_FUNCTION_Resume
* Description  : This function is executed when the USB device detects a resume
*              : signal.
*              : The USB sample driver does not operate for this function.
* Arguments    : none
* Return Value : none
*******************************************************************************/
#if 0	/*The USBHAL in mbed does not need this function*/
void usb0_function_USB_FUNCTION_Resume (void)
{
    /* NOP */
}
#endif

/*******************************************************************************
* Function Name: usb0_function_USB_FUNCTION_Suspend
* Description  : This function is executed when the USB device detects a suspend
*              : signal.
*              : The USB sample driver does not operate for this function.
* Arguments    : none
* Return Value : none
*******************************************************************************/
#if 0	/*The USBHAL in mbed does not need this function*/
void usb0_function_USB_FUNCTION_Suspend (void)
{
    /* NOP */
}
#endif

/*******************************************************************************
* Function Name: usb0_function_USB_FUNCTION_TestMode
* Description  : This function is executed when the USB device is transitioned U
*              : to TEST_MODE by the USB standard request.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb0_function_USB_FUNCTION_TestMode (void)
{
    switch (g_usb0_function_TestModeSelectors & USB_FUNCTION_FUNCTION_TEST_SELECT)
    {
        case USB_FUNCTION_FUNCTION_TEST_J:
        case USB_FUNCTION_FUNCTION_TEST_K:
        case USB_FUNCTION_FUNCTION_TEST_SE0_NAK:
        case USB_FUNCTION_FUNCTION_TEST_PACKET:
            RZA_IO_RegWrite_16(&USB200.TESTMODE,
                                (g_usb0_function_TestModeSelectors >> 8),
                                USB_TESTMODE_UTST_SHIFT,
                                USB_TESTMODE_UTST);
        break;

        case USB_FUNCTION_FUNCTION_TEST_FORCE_ENABLE:
        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb0_function_EnableINTModule
* Description  : Enables USB interrupt.
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void usb0_function_EnableINTModule (void)
{
    uint16_t buf;

    buf  = USB200.INTENB0;
    buf |= (USB_FUNCTION_BITVBSE | USB_FUNCTION_BITDVSE | USB_FUNCTION_BITCTRE |
             USB_FUNCTION_BITBEMPE | USB_FUNCTION_BITNRDYE | USB_FUNCTION_BITBRDYE);
    USB200.INTENB0 = buf;

    usb0_function_enable_bemp_int(USB_FUNCTION_PIPE0);
}

/* End of File */
