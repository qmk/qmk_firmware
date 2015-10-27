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
* File Name    : usb0_host_lib.c
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
#if(1) /* ohci_wrapp */
#include "MBRZA1H.h"            /* INTC Driver Header   */
#else
#include "devdrv_intc.h"        /* INTC Driver Header   */
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


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb0_host_enable_brdy_int
* Description  : Enables BRDY interrupt in the pipe spceified by the argument.
*              : Disables BEMP/NRDY/BRDY interrupts in all pipes before enabling
*              : BRDY. Enables BRDY interrupt in the pipe specified by the argument
*              : in the disabled status. After enabling BRDY, recover all
*              : BEMP/NRDY/BRDY disabled/enabled status.
* Arguments    : uint16_t pipe           ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_enable_brdy_int (uint16_t pipe)
{
    /* enable brdy interrupt */
    USB200.BRDYENB |= (uint16_t)g_usb0_host_bit_set[pipe];
}

/*******************************************************************************
* Function Name: usb0_host_disable_brdy_int
* Description  : Disables BRDY interrupt in the pipe spceified by the argument.
*              : Disables BEMP/NRDY/BRDY interrupts in all pipes before disabling
*              : BRDY. Enables BRDY interrupt in the pipe specified by the argument
*              : in the disabled status. After disabling BRDY, recover all
*              : BEMP/NRDY/BRDY disabled/enabled status.
* Arguments    : uint16_t pipe        ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_disable_brdy_int (uint16_t pipe)
{
    /* disable brdy interrupt */
    USB200.BRDYENB &= (uint16_t)~(g_usb0_host_bit_set[pipe]);
}

/*******************************************************************************
* Function Name: usb0_host_clear_brdy_sts
* Description  : Clear BRDY interrupt status in the pipe spceified by the argument.
* Arguments    : uint16_t pipe        ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_clear_brdy_sts (uint16_t pipe)
{
    /* clear brdy status */
    USB200.BRDYSTS = (uint16_t)~(g_usb0_host_bit_set[pipe]);
}

/*******************************************************************************
* Function Name: usb0_host_enable_bemp_int
* Description  : Enables BEMP interrupt in the pipe spceified by the argument.
*              : Disables BEMP/NRDY/BRDY interrupts in all pipes before enabling
*              : BEMP. Enables BEMP interrupt in the pipe specified by the argument
*              : in the disabled status. After enabling BEMP, recover all
*              : BEMP/NRDY/BRDY disabled/enabled status.
* Arguments    : uint16_t pipe           ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_enable_bemp_int (uint16_t pipe)
{
    /* enable bemp interrupt */
    USB200.BEMPENB |= (uint16_t)g_usb0_host_bit_set[pipe];
}

/*******************************************************************************
* Function Name: usb0_host_disable_bemp_int
* Description  : Disables BEMP interrupt in the pipe spceified by the argument.
*              : Disables BEMP/NRDY/BRDY interrupts in all pipes before disabling
*              : BEMP. Enables BEMP interrupt in the pipe specified by the argument
*              : in the disabled status. After enabling BEMP, recover all
*              : BEMP/NRDY/BRDY disabled/enabled status.
* Arguments    : uint16_t pipe           ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_disable_bemp_int (uint16_t pipe)
{
    /* disable bemp interrupt */
    USB200.BEMPENB &= (uint16_t)~(g_usb0_host_bit_set[pipe]);
}

/*******************************************************************************
* Function Name: usb0_host_clear_bemp_sts
* Description  : Clear BEMP interrupt status in the pipe spceified by the argument.
* Arguments    : uint16_t pipe        ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_clear_bemp_sts (uint16_t pipe)
{
    /* clear bemp status */
    USB200.BEMPSTS = (uint16_t)~(g_usb0_host_bit_set[pipe]);
}

/*******************************************************************************
* Function Name: usb0_host_enable_nrdy_int
* Description  : Enables NRDY interrupt in the pipe spceified by the argument.
*              : Disables BEMP/NRDY/BRDY interrupts in all pipes before enabling
*              : NRDY. Enables NRDY interrupt in the pipe specified by the argument
*              : in the disabled status. After enabling NRDY, recover all
*              : BEMP/NRDY/BRDY disabled/enabled status.
* Arguments    : uint16_t pipe             ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_enable_nrdy_int (uint16_t pipe)
{
    /* enable nrdy interrupt */
    USB200.NRDYENB |= (uint16_t)g_usb0_host_bit_set[pipe];
}

/*******************************************************************************
* Function Name: usb0_host_disable_nrdy_int
* Description  : Disables NRDY interrupt in the pipe spceified by the argument.
*              : Disables BEMP/NRDY/BRDY interrupts in all pipes before disabling
*              : NRDY. Disables NRDY interrupt in the pipe specified by the argument
*              : in the disabled status. After disabling NRDY, recover all
*              : BEMP/NRDY/BRDY disabled/enabled status.
* Arguments    : uint16_t pipe            ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_disable_nrdy_int (uint16_t pipe)
{
    /* disable nrdy interrupt */
    USB200.NRDYENB &= (uint16_t)~(g_usb0_host_bit_set[pipe]);
}

/*******************************************************************************
* Function Name: usb0_host_clear_nrdy_sts
* Description  : Clear NRDY interrupt status in the pipe spceified by the argument.
* Arguments    : uint16_t pipe        ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_clear_nrdy_sts (uint16_t pipe)
{
    /* clear nrdy status */
    USB200.NRDYSTS = (uint16_t)~(g_usb0_host_bit_set[pipe]);
}

/*******************************************************************************
* Function Name: usb0_host_is_hispeed
* Description  : Returns the result of USB reset hand shake (RHST) as
*              : return value.
* Arguments    : none
* Return Value : USB_HOST_HIGH_SPEED  ; Hi-Speed
*              : USB_HOST_FULL_SPEED  ; Full-Speed
*              : USB_HOST_LOW_SPEED   ; Low-Speed
*              : USB_HOST_NON_SPEED   ; error
*******************************************************************************/
uint16_t usb0_host_is_hispeed (void)
{
    uint16_t rhst;
    uint16_t speed;

    rhst = RZA_IO_RegRead_16(&USB200.DVSTCTR0,
                                USB_DVSTCTR0_RHST_SHIFT,
                                USB_DVSTCTR0_RHST);
    if (rhst == USB_HOST_HSMODE)
    {
        speed = USB_HOST_HIGH_SPEED;
    }
    else if (rhst == USB_HOST_FSMODE)
    {
        speed = USB_HOST_FULL_SPEED;
    }
    else if (rhst == USB_HOST_LSMODE)
    {
        speed = USB_HOST_LOW_SPEED;
    }
    else
    {
        speed = USB_HOST_NON_SPEED;
    }

    return speed;
}

/*******************************************************************************
* Function Name: usb0_host_is_hispeed_enable
* Description  : Returns the USB High-Speed connection enabled status as
*              : return value.
* Arguments    : none
* Return Value : USB_HOST_YES : Hi-Speed Enable
*              : USB_HOST_NO  : Hi-Speed Disable
*******************************************************************************/
uint16_t usb0_host_is_hispeed_enable (void)
{
    uint16_t ret;

    ret = USB_HOST_NO;

    if (RZA_IO_RegRead_16(&USB200.SYSCFG0,
                                USB_SYSCFG_HSE_SHIFT,
                                USB_SYSCFG_HSE) == 1)
    {
        ret = USB_HOST_YES;
    }

    return ret;
}

/*******************************************************************************
* Function Name: usb0_host_set_pid_buf
* Description  : Enables communicaqtion in the pipe specified by the argument
*              : (BUF).
* Arguments    : uint16_t pipe             ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_set_pid_buf (uint16_t pipe)
{
    uint16_t pid;

    pid = usb0_host_get_pid(pipe);

    if (pid == USB_HOST_PID_STALL2)
    {
        usb0_host_set_pid_nak(pipe);
    }

    switch (pipe)
    {
        case USB_HOST_PIPE0:
            RZA_IO_RegWrite_16(&USB200.DCPCTR,
                                USB_HOST_PID_BUF,
                                USB_DCPCTR_PID_SHIFT,
                                USB_DCPCTR_PID);
        break;

        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE6:
            RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_6_8_PID_SHIFT,
                                USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE7:
            RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_6_8_PID_SHIFT,
                                USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE8:
            RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_6_8_PID_SHIFT,
                                USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                USB_HOST_PID_BUF,
                                USB_PIPEnCTR_9_PID_SHIFT,
                                USB_PIPEnCTR_9_PID);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb0_host_set_pid_nak
* Description  : Disables communication (NAK) in the pipe specified by the argument.
*              : When the pipe status was enabling communication (BUF) before
*              : executing before executing this function, waits in the software
*              : until the pipe becomes ready after setting disabled.
* Arguments    : uint16_t pipe            ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_set_pid_nak (uint16_t pipe)
{
    uint16_t pid;
    uint16_t pbusy;
    uint32_t loop;

    pid = usb0_host_get_pid(pipe);

    if (pid == USB_HOST_PID_STALL2)
    {
        usb0_host_set_pid_stall(pipe);
    }

    switch (pipe)
    {
        case USB_HOST_PIPE0:
            RZA_IO_RegWrite_16(&USB200.DCPCTR,
                                USB_HOST_PID_NAK,
                                USB_DCPCTR_PID_SHIFT,
                                USB_DCPCTR_PID);
        break;

        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_1_5_PID_SHIFT,
                                USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE6:
            RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_6_8_PID_SHIFT,
                                USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE7:
            RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_6_8_PID_SHIFT,
                                USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE8:
            RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_6_8_PID_SHIFT,
                                USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                USB_HOST_PID_NAK,
                                USB_PIPEnCTR_9_PID_SHIFT,
                                USB_PIPEnCTR_9_PID);
        break;

        default:
        break;
    }

    if (pid == USB_HOST_PID_BUF)
    {
        for (loop = 0; loop < 200; loop++)
        {
            switch (pipe)
            {
                case USB_HOST_PIPE0:
                    pbusy = RZA_IO_RegRead_16(&USB200.DCPCTR,
                                                USB_DCPCTR_PBUSY_SHIFT,
                                                USB_DCPCTR_PBUSY);
                break;

                case USB_HOST_PIPE1:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE1CTR,
                                                USB_PIPEnCTR_1_5_PBUSY_SHIFT,
                                                USB_PIPEnCTR_1_5_PBUSY);
                break;

                case USB_HOST_PIPE2:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE2CTR,
                                                USB_PIPEnCTR_1_5_PBUSY_SHIFT,
                                                USB_PIPEnCTR_1_5_PBUSY);
                break;

                case USB_HOST_PIPE3:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE3CTR,
                                                USB_PIPEnCTR_1_5_PBUSY_SHIFT,
                                                USB_PIPEnCTR_1_5_PBUSY);
                break;

                case USB_HOST_PIPE4:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE4CTR,
                                                USB_PIPEnCTR_1_5_PBUSY_SHIFT,
                                                USB_PIPEnCTR_1_5_PBUSY);
                break;

                case USB_HOST_PIPE5:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE5CTR,
                                                USB_PIPEnCTR_1_5_PBUSY_SHIFT,
                                                USB_PIPEnCTR_1_5_PBUSY);
                break;

                case USB_HOST_PIPE6:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE6CTR,
                                                USB_PIPEnCTR_6_8_PBUSY_SHIFT,
                                                USB_PIPEnCTR_6_8_PBUSY);
                break;

                case USB_HOST_PIPE7:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE7CTR,
                                                USB_PIPEnCTR_6_8_PBUSY_SHIFT,
                                                USB_PIPEnCTR_6_8_PBUSY);
                break;

                case USB_HOST_PIPE8:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE8CTR,
                                                USB_PIPEnCTR_6_8_PBUSY_SHIFT,
                                                USB_PIPEnCTR_6_8_PBUSY);
                break;

                case USB_HOST_PIPE9:
                    pbusy = RZA_IO_RegRead_16(&USB200.PIPE9CTR,
                                                USB_PIPEnCTR_9_PBUSY_SHIFT,
                                                USB_PIPEnCTR_9_PBUSY);
                break;

                default:
                    pbusy = 1;
                break;
            }

            if (pbusy == 0)
            {
                break;
            }

            Userdef_USB_usb0_host_delay_500ns();
        }
    }
}

/*******************************************************************************
* Function Name: usb0_host_set_pid_stall
* Description  : Disables communication (STALL) in the pipe specified by the
*              : argument.
* Arguments    : uint16_t pipe            ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_set_pid_stall (uint16_t pipe)
{
    uint16_t pid;

    pid = usb0_host_get_pid(pipe);

    if (pid == USB_HOST_PID_BUF)
    {
        switch (pipe)
        {
            case USB_HOST_PIPE0:
                RZA_IO_RegWrite_16(&USB200.DCPCTR,
                                    USB_HOST_PID_STALL2,
                                    USB_DCPCTR_PID_SHIFT,
                                    USB_DCPCTR_PID);
            break;

            case USB_HOST_PIPE1:
                RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE2:
                RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE3:
                RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE4:
                RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE5:
                RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE6:
                RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
            break;

            case USB_HOST_PIPE7:
                RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
            break;

            case USB_HOST_PIPE8:
                RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
            break;

            case USB_HOST_PIPE9:
                RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                    USB_HOST_PID_STALL2,
                                    USB_PIPEnCTR_9_PID_SHIFT,
                                    USB_PIPEnCTR_9_PID);
            break;

            default:
            break;
        }
    }
    else
    {
        switch (pipe)
        {
            case USB_HOST_PIPE0:
                RZA_IO_RegWrite_16(&USB200.DCPCTR,
                                    USB_HOST_PID_STALL,
                                    USB_DCPCTR_PID_SHIFT,
                                    USB_DCPCTR_PID);
            break;

            case USB_HOST_PIPE1:
                RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE2:
                RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE3:
                RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE4:
                RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE5:
                RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
            break;

            case USB_HOST_PIPE6:
                RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
            break;

            case USB_HOST_PIPE7:
                RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
            break;

            case USB_HOST_PIPE8:
                RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
            break;

            case USB_HOST_PIPE9:
                RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                    USB_HOST_PID_STALL,
                                    USB_PIPEnCTR_9_PID_SHIFT,
                                    USB_PIPEnCTR_9_PID);
            break;

            default:
            break;
        }
    }
}

/*******************************************************************************
* Function Name: usb0_host_clear_pid_stall
* Description  : Disables communication (NAK) in the pipe specified by the argument.
* Arguments    : uint16_t pipe            ; pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_clear_pid_stall (uint16_t pipe)
{
    usb0_host_set_pid_nak(pipe);
}

/*******************************************************************************
* Function Name: usb0_host_get_pid
* Description  : Returns the pipe state specified by the argument.
* Arguments    : uint16_t pipe          ; Pipe Number
* Return Value : PID
*******************************************************************************/
uint16_t usb0_host_get_pid (uint16_t pipe)
{
    uint16_t pid;

    switch (pipe)
    {
        case USB_HOST_PIPE0:
            pid = RZA_IO_RegRead_16(&USB200.DCPCTR,
                                    USB_DCPCTR_PID_SHIFT,
                                    USB_DCPCTR_PID);
        break;

        case USB_HOST_PIPE1:
            pid = RZA_IO_RegRead_16(&USB200.PIPE1CTR,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE2:
            pid = RZA_IO_RegRead_16(&USB200.PIPE2CTR,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE3:
            pid = RZA_IO_RegRead_16(&USB200.PIPE3CTR,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE4:
            pid = RZA_IO_RegRead_16(&USB200.PIPE4CTR,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE5:
            pid = RZA_IO_RegRead_16(&USB200.PIPE5CTR,
                                    USB_PIPEnCTR_1_5_PID_SHIFT,
                                    USB_PIPEnCTR_1_5_PID);
        break;

        case USB_HOST_PIPE6:
            pid = RZA_IO_RegRead_16(&USB200.PIPE6CTR,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE7:
            pid = RZA_IO_RegRead_16(&USB200.PIPE7CTR,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE8:
            pid = RZA_IO_RegRead_16(&USB200.PIPE8CTR,
                                    USB_PIPEnCTR_6_8_PID_SHIFT,
                                    USB_PIPEnCTR_6_8_PID);
        break;

        case USB_HOST_PIPE9:
            pid = RZA_IO_RegRead_16(&USB200.PIPE9CTR,
                                    USB_PIPEnCTR_9_PID_SHIFT,
                                    USB_PIPEnCTR_9_PID);
        break;

        default:
            pid = 0;
        break;
    }

    return pid;
}

/*******************************************************************************
* Function Name: usb0_host_set_csclr
* Description  : CSPLIT status clear setting of sprit transaction in specified
*              : pipe is performed.
*              : When SQSET bit or SQCLR bit, and SQSET bit or SQCLR bit
*              : in DCPCTR register are continuously changed (when the sequence
*              : toggle bit of data PID is continuously changed over two or more pipes),
*              : the access cycle with 120 ns and more than 5 cycle bus clock is necessary.
*              : Do not set both SQCLR bit and SQSET bit to 1 at the same time.
*              : In addition, both bits should be operated after PID is set to NAK.
*              : However, when it is set to the isochronous transfer as the transfer type
*              : (TYPE=11), writing in SQSET bit is disabled.
* Arguments    : uint16_t pipe     ; Pipe number
* Return Value : none
*******************************************************************************/
void usb0_host_set_csclr (uint16_t pipe)
{
    switch (pipe)
    {
        case USB_HOST_PIPE0:
            RZA_IO_RegWrite_16(&USB200.DCPCTR,
                                1,
                                USB_DCPCTR_CSCLR_SHIFT,
                                USB_DCPCTR_CSCLR);
        break;

        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                1,
                                USB_PIPEnCTR_1_5_CSCLR_SHIFT,
                                USB_PIPEnCTR_1_5_CSCLR);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                1,
                                USB_PIPEnCTR_1_5_CSCLR_SHIFT,
                                USB_PIPEnCTR_1_5_CSCLR);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                1,
                                USB_PIPEnCTR_1_5_CSCLR_SHIFT,
                                USB_PIPEnCTR_1_5_CSCLR);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                1,
                                USB_PIPEnCTR_1_5_CSCLR_SHIFT,
                                USB_PIPEnCTR_1_5_CSCLR);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                1,
                                USB_PIPEnCTR_1_5_CSCLR_SHIFT,
                                USB_PIPEnCTR_1_5_CSCLR);
        break;

        case USB_HOST_PIPE6:
            RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                1,
                                USB_PIPEnCTR_6_8_CSCLR_SHIFT,
                                USB_PIPEnCTR_6_8_CSCLR);
        break;

        case USB_HOST_PIPE7:
            RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                1,
                                USB_PIPEnCTR_6_8_CSCLR_SHIFT,
                                USB_PIPEnCTR_6_8_CSCLR);
        break;

        case USB_HOST_PIPE8:
            RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                1,
                                USB_PIPEnCTR_6_8_CSCLR_SHIFT,
                                USB_PIPEnCTR_6_8_CSCLR);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                1,
                                USB_PIPEnCTR_9_CSCLR_SHIFT,
                                USB_PIPEnCTR_9_CSCLR);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb0_host_set_sqclr
* Description  : Sets the sequence bit of the pipe specified by the argument to
*              : DATA0.
* Arguments    : uint16_t pipe              ; Pipe Number
* Return Value : none
*******************************************************************************/
void usb0_host_set_sqclr (uint16_t pipe)
{
    switch (pipe)
    {
        case USB_HOST_PIPE0:
            RZA_IO_RegWrite_16(&USB200.DCPCTR,
                                1,
                                USB_DCPCTR_SQCLR_SHIFT,
                                USB_DCPCTR_SQCLR);
        break;

        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQCLR_SHIFT,
                                USB_PIPEnCTR_1_5_SQCLR);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQCLR_SHIFT,
                                USB_PIPEnCTR_1_5_SQCLR);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQCLR_SHIFT,
                                USB_PIPEnCTR_1_5_SQCLR);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQCLR_SHIFT,
                                USB_PIPEnCTR_1_5_SQCLR);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQCLR_SHIFT,
                                USB_PIPEnCTR_1_5_SQCLR);
        break;

        case USB_HOST_PIPE6:
            RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                1,
                                USB_PIPEnCTR_6_8_SQCLR_SHIFT,
                                USB_PIPEnCTR_6_8_SQCLR);
        break;

        case USB_HOST_PIPE7:
            RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                1,
                                USB_PIPEnCTR_6_8_SQCLR_SHIFT,
                                USB_PIPEnCTR_6_8_SQCLR);
        break;

        case USB_HOST_PIPE8:
            RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                1,
                                USB_PIPEnCTR_6_8_SQCLR_SHIFT,
                                USB_PIPEnCTR_6_8_SQCLR);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                1,
                                USB_PIPEnCTR_9_SQCLR_SHIFT,
                                USB_PIPEnCTR_9_SQCLR);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb0_host_set_sqset
* Description  : Sets the sequence bit of the pipe specified by the argument to
*              : DATA1.
* Arguments    : uint16_t pipe   ; Pipe number
* Return Value : none
*******************************************************************************/
void usb0_host_set_sqset (uint16_t pipe)
{
    switch (pipe)
    {
        case USB_HOST_PIPE0:
            RZA_IO_RegWrite_16(&USB200.DCPCTR,
                                1,
                                USB_DCPCTR_SQSET_SHIFT,
                                USB_DCPCTR_SQSET);
        break;

        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQSET_SHIFT,
                                USB_PIPEnCTR_1_5_SQSET);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQSET_SHIFT,
                                USB_PIPEnCTR_1_5_SQSET);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQSET_SHIFT,
                                USB_PIPEnCTR_1_5_SQSET);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQSET_SHIFT,
                                USB_PIPEnCTR_1_5_SQSET);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                1,
                                USB_PIPEnCTR_1_5_SQSET_SHIFT,
                                USB_PIPEnCTR_1_5_SQSET);
        break;

        case USB_HOST_PIPE6:
            RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                1,
                                USB_PIPEnCTR_6_8_SQSET_SHIFT,
                                USB_PIPEnCTR_6_8_SQSET);
        break;

        case USB_HOST_PIPE7:
            RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                1,
                                USB_PIPEnCTR_6_8_SQSET_SHIFT,
                                USB_PIPEnCTR_6_8_SQSET);
        break;

        case USB_HOST_PIPE8:
            RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                1,
                                USB_PIPEnCTR_6_8_SQSET_SHIFT,
                                USB_PIPEnCTR_6_8_SQSET);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                1,
                                USB_PIPEnCTR_9_SQSET_SHIFT,
                                USB_PIPEnCTR_9_SQSET);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb0_host_get_sqmon
* Description  : Toggle bit of specified pipe is obtained
* Arguments    : uint16_t pipe   ; Pipe number
* Return Value : sqmon
*******************************************************************************/
uint16_t usb0_host_get_sqmon (uint16_t pipe)
{
    uint16_t sqmon;

    switch (pipe)
    {
        case USB_HOST_PIPE0:
            sqmon = RZA_IO_RegRead_16(&USB200.DCPCTR,
                                        USB_DCPCTR_SQMON_SHIFT,
                                        USB_DCPCTR_SQMON);
        break;

        case USB_HOST_PIPE1:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE1CTR,
                                        USB_PIPEnCTR_1_5_SQMON_SHIFT,
                                        USB_PIPEnCTR_1_5_SQMON);
        break;

        case USB_HOST_PIPE2:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE2CTR,
                                        USB_PIPEnCTR_1_5_SQMON_SHIFT,
                                        USB_PIPEnCTR_1_5_SQMON);
        break;

        case USB_HOST_PIPE3:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE3CTR,
                                        USB_PIPEnCTR_1_5_SQMON_SHIFT,
                                        USB_PIPEnCTR_1_5_SQMON);
        break;

        case USB_HOST_PIPE4:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE4CTR,
                                        USB_PIPEnCTR_1_5_SQMON_SHIFT,
                                        USB_PIPEnCTR_1_5_SQMON);
        break;

        case USB_HOST_PIPE5:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE5CTR,
                                        USB_PIPEnCTR_1_5_SQMON_SHIFT,
                                        USB_PIPEnCTR_1_5_SQMON);
        break;

        case USB_HOST_PIPE6:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE6CTR,
                                        USB_PIPEnCTR_6_8_SQMON_SHIFT,
                                        USB_PIPEnCTR_6_8_SQMON);
        break;

        case USB_HOST_PIPE7:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE7CTR,
                                        USB_PIPEnCTR_6_8_SQMON_SHIFT,
                                        USB_PIPEnCTR_6_8_SQMON);
        break;

        case USB_HOST_PIPE8:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE8CTR,
                                        USB_PIPEnCTR_6_8_SQMON_SHIFT,
                                        USB_PIPEnCTR_6_8_SQMON);
        break;

        case USB_HOST_PIPE9:
            sqmon = RZA_IO_RegRead_16(&USB200.PIPE9CTR,
                                        USB_PIPEnCTR_9_SQMON_SHIFT,
                                        USB_PIPEnCTR_9_SQMON);
        break;

        default:
            sqmon = 0;
        break;
    }

    return sqmon;
}

/*******************************************************************************
* Function Name: usb0_host_aclrm
* Description  : The buffer of specified pipe is initialized
* Arguments    : uint16_t pipe    : Pipe
* Return Value : none
*******************************************************************************/
void usb0_host_aclrm (uint16_t pipe)
{
    usb0_host_set_aclrm(pipe);
    usb0_host_clr_aclrm(pipe);
}

/*******************************************************************************
* Function Name: usb0_host_set_aclrm
* Description  : The auto buffer clear mode of specified pipe is enabled
* Arguments    : uint16_t pipe    : Pipe
* Return Value : none
*******************************************************************************/
void usb0_host_set_aclrm (uint16_t pipe)
{
    switch (pipe)
    {
        case USB_HOST_PIPE0:
        break;

        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                1,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                1,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                1,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                1,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                1,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE6:
            RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                1,
                                USB_PIPEnCTR_6_8_ACLRM_SHIFT,
                                USB_PIPEnCTR_6_8_ACLRM);
        break;

        case USB_HOST_PIPE7:
            RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                1,
                                USB_PIPEnCTR_6_8_ACLRM_SHIFT,
                                USB_PIPEnCTR_6_8_ACLRM);
        break;

        case USB_HOST_PIPE8:
            RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                1,
                                USB_PIPEnCTR_6_8_ACLRM_SHIFT,
                                USB_PIPEnCTR_6_8_ACLRM);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                1,
                                USB_PIPEnCTR_9_ACLRM_SHIFT,
                                USB_PIPEnCTR_9_ACLRM);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb0_host_clr_aclrm
* Description  : The auto buffer clear mode of specified pipe is enabled
* Arguments    : uint16_t pipe    : Pipe
* Return Value : none
*******************************************************************************/
void usb0_host_clr_aclrm (uint16_t pipe)
{
    switch (pipe)
    {
        case USB_HOST_PIPE0:
        break;

        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB200.PIPE1CTR,
                                0,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB200.PIPE2CTR,
                                0,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB200.PIPE3CTR,
                                0,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB200.PIPE4CTR,
                                0,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB200.PIPE5CTR,
                                0,
                                USB_PIPEnCTR_1_5_ACLRM_SHIFT,
                                USB_PIPEnCTR_1_5_ACLRM);
        break;

        case USB_HOST_PIPE6:
            RZA_IO_RegWrite_16(&USB200.PIPE6CTR,
                                0,
                                USB_PIPEnCTR_6_8_ACLRM_SHIFT,
                                USB_PIPEnCTR_6_8_ACLRM);
        break;

        case USB_HOST_PIPE7:
            RZA_IO_RegWrite_16(&USB200.PIPE7CTR,
                                0,
                                USB_PIPEnCTR_6_8_ACLRM_SHIFT,
                                USB_PIPEnCTR_6_8_ACLRM);
        break;

        case USB_HOST_PIPE8:
            RZA_IO_RegWrite_16(&USB200.PIPE8CTR,
                                0,
                                USB_PIPEnCTR_6_8_ACLRM_SHIFT,
                                USB_PIPEnCTR_6_8_ACLRM);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB200.PIPE9CTR,
                                0,
                                USB_PIPEnCTR_9_ACLRM_SHIFT,
                                USB_PIPEnCTR_9_ACLRM);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb0_host_get_inbuf
* Description  : Returns INBUFM of the pipe specified by the argument.
* Arguments    : uint16_t pipe             ; Pipe Number
* Return Value : inbuf
*******************************************************************************/
uint16_t usb0_host_get_inbuf (uint16_t pipe)
{
    uint16_t inbuf;

    switch (pipe)
    {
        case USB_HOST_PIPE0:
            inbuf = 0;
        break;

        case USB_HOST_PIPE1:
            inbuf = RZA_IO_RegRead_16(&USB200.PIPE1CTR,
                                    USB_PIPEnCTR_1_5_INBUFM_SHIFT,
                                    USB_PIPEnCTR_1_5_INBUFM);
        break;

        case USB_HOST_PIPE2:
            inbuf = RZA_IO_RegRead_16(&USB200.PIPE2CTR,
                                    USB_PIPEnCTR_1_5_INBUFM_SHIFT,
                                    USB_PIPEnCTR_1_5_INBUFM);
        break;

        case USB_HOST_PIPE3:
            inbuf = RZA_IO_RegRead_16(&USB200.PIPE3CTR,
                                    USB_PIPEnCTR_1_5_INBUFM_SHIFT,
                                    USB_PIPEnCTR_1_5_INBUFM);
        break;

        case USB_HOST_PIPE4:
            inbuf = RZA_IO_RegRead_16(&USB200.PIPE4CTR,
                                    USB_PIPEnCTR_1_5_INBUFM_SHIFT,
                                    USB_PIPEnCTR_1_5_INBUFM);
        break;

        case USB_HOST_PIPE5:
            inbuf = RZA_IO_RegRead_16(&USB200.PIPE5CTR,
                                    USB_PIPEnCTR_1_5_INBUFM_SHIFT,
                                    USB_PIPEnCTR_1_5_INBUFM);
        break;

        case USB_HOST_PIPE6:
            inbuf = 0;
        break;

        case USB_HOST_PIPE7:
            inbuf = 0;
        break;

        case USB_HOST_PIPE8:
            inbuf = 0;
        break;

        case USB_HOST_PIPE9:
            inbuf = RZA_IO_RegRead_16(&USB200.PIPE9CTR,
                                    USB_PIPEnCTR_9_INBUFM_SHIFT,
                                    USB_PIPEnCTR_9_INBUFM);
        break;

        default:
            inbuf = 0;
        break;
    }

    return inbuf;
}

/*******************************************************************************
* Function Name: usb0_host_setting_interrupt
* Description  : Sets the USB module interrupt level.
* Arguments    : uint8_t level ; interrupt level
* Return Value : none
*******************************************************************************/
void usb0_host_setting_interrupt (uint8_t level)
{
#if(1) /* ohci_wrapp */
    IRQn_Type d0fifo_dmaintid;
    IRQn_Type d1fifo_dmaintid;

    InterruptHandlerRegister(USBI0_IRQn, usb0_host_interrupt);
    GIC_SetPriority(USBI0_IRQn, level);
    GIC_EnableIRQ(USBI0_IRQn);

    d0fifo_dmaintid = (IRQn_Type)Userdef_USB_usb0_host_d0fifo_dmaintid();

    if (d0fifo_dmaintid != 0xFFFF)
    {
        InterruptHandlerRegister(d0fifo_dmaintid, usb0_host_dma_interrupt_d0fifo);
        GIC_SetPriority(d0fifo_dmaintid, level);
        GIC_EnableIRQ(d0fifo_dmaintid);
    }

    d1fifo_dmaintid = (IRQn_Type)Userdef_USB_usb0_host_d1fifo_dmaintid();

    if (d1fifo_dmaintid != 0xFFFF)
    {
        InterruptHandlerRegister(d1fifo_dmaintid, usb0_host_dma_interrupt_d1fifo);
        GIC_SetPriority(d1fifo_dmaintid, level);
        GIC_EnableIRQ(d1fifo_dmaintid);
    }
#else
    uint16_t d0fifo_dmaintid;
    uint16_t d1fifo_dmaintid;

    R_INTC_RegistIntFunc(INTC_ID_USBI0, usb0_host_interrupt);
    R_INTC_SetPriority(INTC_ID_USBI0, level);
    R_INTC_Enable(INTC_ID_USBI0);

    d0fifo_dmaintid = Userdef_USB_usb0_host_d0fifo_dmaintid();

    if (d0fifo_dmaintid != 0xFFFF)
    {
        R_INTC_RegistIntFunc(d0fifo_dmaintid, usb0_host_dma_interrupt_d0fifo);
        R_INTC_SetPriority(d0fifo_dmaintid, level);
        R_INTC_Enable(d0fifo_dmaintid);
    }

    d1fifo_dmaintid = Userdef_USB_usb0_host_d1fifo_dmaintid();

    if (d1fifo_dmaintid != 0xFFFF)
    {
        R_INTC_RegistIntFunc(d1fifo_dmaintid, usb0_host_dma_interrupt_d1fifo);
        R_INTC_SetPriority(d1fifo_dmaintid, level);
        R_INTC_Enable(d1fifo_dmaintid);
    }
#endif
}

/*******************************************************************************
* Function Name: usb0_host_reset_module
* Description  : Initializes the USB module.
*              : Enables providing clock to the USB module.
*              : Sets USB bus wait register.
* Arguments    : uint16_t clockmode ; 48MHz ; USBHCLOCK_X1_48MHZ
*              :                    ; 12MHz ; USBHCLOCK_EXTAL_12MHZ
* Return Value : none
*******************************************************************************/
void usb0_host_reset_module (uint16_t clockmode)
{
    if (RZA_IO_RegRead_16(&USB200.SYSCFG0,
                                USB_SYSCFG_UPLLE_SHIFT,
                                USB_SYSCFG_UPLLE) == 1)
    {
        if ((USB200.SYSCFG0 & USB_HOST_BITUCKSEL) != clockmode)
        {
            RZA_IO_RegWrite_16(&USB200.SUSPMODE,
                                0,
                                USB_SUSPMODE_SUSPM_SHIFT,
                                USB_SUSPMODE_SUSPM);
            USB200.SYSCFG0 = 0;
            USB200.SYSCFG0 = (USB_HOST_BITUPLLE | clockmode);
            Userdef_USB_usb0_host_delay_xms(1);
            RZA_IO_RegWrite_16(&USB200.SUSPMODE,
                                1,
                                USB_SUSPMODE_SUSPM_SHIFT,
                                USB_SUSPMODE_SUSPM);
        }
        else
        {
            RZA_IO_RegWrite_16(&USB200.SUSPMODE,
                                0,
                                USB_SUSPMODE_SUSPM_SHIFT,
                                USB_SUSPMODE_SUSPM);
            Userdef_USB_usb0_host_delay_xms(1);
            RZA_IO_RegWrite_16(&USB200.SUSPMODE,
                                1,
                                USB_SUSPMODE_SUSPM_SHIFT,
                                USB_SUSPMODE_SUSPM);
        }
    }
    else
    {
        RZA_IO_RegWrite_16(&USB200.SUSPMODE,
                            0,
                            USB_SUSPMODE_SUSPM_SHIFT,
                            USB_SUSPMODE_SUSPM);
        USB200.SYSCFG0 = 0;
        USB200.SYSCFG0 = (USB_HOST_BITUPLLE | clockmode);
        Userdef_USB_usb0_host_delay_xms(1);
        RZA_IO_RegWrite_16(&USB200.SUSPMODE,
                            1,
                            USB_SUSPMODE_SUSPM_SHIFT,
                            USB_SUSPMODE_SUSPM);
    }

    USB200.BUSWAIT = (uint16_t)(USB_HOST_BUSWAIT_05 & USB_HOST_BITBWAIT);
}

/*******************************************************************************
* Function Name: usb0_host_get_buf_size
* Description  : Obtains pipe buffer size specified by the argument and
*              : maximum packet size of the USB device in use.
*              : When USB_HOST_PIPE0 is specified by the argument, obtains the maximum
*              : packet size of the USB device using the corresponding pipe.
*              : For the case that USB_HOST_PIPE0 is not assigned by the argument, when the
*              : corresponding pipe is in continuous transfer mode,
*              : obtains the buffer size allocated in the corresponcing pipe,
*              : when incontinuous transfer, obtains maximum packet size.
* Arguments    : uint16_t ; pipe Number
* Return Value : Maximum packet size or buffer size
*******************************************************************************/
uint16_t usb0_host_get_buf_size (uint16_t pipe)
{
    uint16_t size;
    uint16_t bufsize;

    if (pipe == USB_HOST_PIPE0)
    {
        size = RZA_IO_RegRead_16(&USB200.DCPMAXP,
                                USB_DCPMAXP_MXPS_SHIFT,
                                USB_DCPMAXP_MXPS);
    }
    else
    {
        if (RZA_IO_RegRead_16(&g_usb0_host_pipecfg[pipe], USB_PIPECFG_CNTMD_SHIFT, USB_PIPECFG_CNTMD) == 1)
        {
            bufsize = RZA_IO_RegRead_16(&g_usb0_host_pipebuf[pipe], USB_PIPEBUF_BUFSIZE_SHIFT, USB_PIPEBUF_BUFSIZE);
            size    = (uint16_t)((bufsize + 1) * USB_HOST_PIPExBUF);
        }
        else
        {
            size = RZA_IO_RegRead_16(&g_usb0_host_pipemaxp[pipe], USB_PIPEMAXP_MXPS_SHIFT, USB_PIPEMAXP_MXPS);
        }
    }
    return size;
}

/*******************************************************************************
* Function Name: usb0_host_get_mxps
* Description  : Obtains maximum packet size of the USB device using the pipe
*              : specified by the argument.
* Arguments    : uint16_t ; Pipe Number
* Return Value : Max Packet Size
*******************************************************************************/
uint16_t usb0_host_get_mxps (uint16_t pipe)
{
    uint16_t size;

    if (pipe == USB_HOST_PIPE0)
    {
        size = RZA_IO_RegRead_16(&USB200.DCPMAXP,
                                USB_DCPMAXP_MXPS_SHIFT,
                                USB_DCPMAXP_MXPS);
    }
    else
    {
        size = RZA_IO_RegRead_16(&g_usb0_host_pipemaxp[pipe], USB_PIPEMAXP_MXPS_SHIFT, USB_PIPEMAXP_MXPS);
    }

    return size;
}

/* End of File */
