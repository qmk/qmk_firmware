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
* File Name    : usb1_function_api.c
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
#include "usb1_function.h"
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


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: usb1_api_function_init
* Description  : Initializes the USB module in the USB function mode.
* Arguments    : uint8_t  int_level ; interruput level
*              : uint16_t mode      : Speed modes
*              :                    :  USB_FUCNTION_HIGH_SPEED: High-speed device
*              :                    :  USB_FUCNTION_FULL_SPEED: Full-speed device
*              : uint16_t clockmode ; 48MHz ; USBFCLOCK_X1_48MHZ
*              :                    ; 12MHz ; USBFCLOCK_EXTAL_12MHZ
* Return Value : none
*******************************************************************************/
#if 0
void usb1_api_function_init (uint8_t int_level, uint16_t mode, uint16_t clockmode)
{
    volatile uint8_t dummy_buf;

    CPG.STBCR7  &= 0xfc;                        /*The clock of USB0/1 modules is permitted  */
    dummy_buf   = CPG.STBCR7;                   /* (Dummy read)                             */

    usb1_function_setting_interrupt(int_level);

    usb1_function_reset_module(clockmode);      /* reset USB module with setting tranciever */
                                                /* and HSE=1                                */

    usb1_function_init_status();                /* clear variables                          */

    usb1_function_InitModule(mode);             /* select USB Function and Interrupt Enable */
                                                /* Detect USB Device to attach or detach    */
}
#endif

/*******************************************************************************
* Function Name: usb1_api_function_IsConfigured
* Description  : Checks if the USB device is configured to return the result as
*              : the return value.
* Arguments    : none
* Return Value : DEVDRV_USBF_YES  : Configured & Configured Suspend
*              : DEVDRV_USBF_NO   : not Configured
*******************************************************************************/
uint16_t usb1_api_function_IsConfigured (void)
{
    uint16_t dvst;

    dvst = usb1_function_GetDeviceState();

    if ((dvst == USB_FUNCTION_DVST_CONFIGURED) ||
        (dvst == USB_FUNCTION_DVST_CONFIGURED_SUSPEND))
    {
        return DEVDRV_USBF_YES;
    }

    return DEVDRV_USBF_NO;
}

/*******************************************************************************
* Function Name: usb1_function_GetDeviceState
* Description  : Returns the state of USB device.
* Arguments    : none
* Return Value : Device States
*******************************************************************************/
uint16_t usb1_function_GetDeviceState (void)
{
    uint16_t dvsq;
    uint16_t dvst;

    dvsq = USB201.INTSTS0;
    switch (dvsq & USB_FUNCTION_BITDVSQ)
    {
        case USB_FUNCTION_DS_POWR:                      /* Power state *//* power-on */
            dvst = USB_FUNCTION_DVST_POWERED;
        break;

        case USB_FUNCTION_DS_DFLT:                      /* Default state *//* bus-reset */
            dvst = USB_FUNCTION_DVST_DEFAULT;
        break;

        case USB_FUNCTION_DS_ADDS:                      /* Address state */
            dvst = USB_FUNCTION_DVST_ADDRESS;
        break;

        case USB_FUNCTION_DS_CNFG:                      /* Configured state */
            dvst = USB_FUNCTION_DVST_CONFIGURED;
        break;

        case USB_FUNCTION_DS_SPD_CNFG:                  /* Configured Suspend state */
            dvst = USB_FUNCTION_DVST_CONFIGURED_SUSPEND;
        break;

        case USB_FUNCTION_DS_SPD_POWR:                  /* Power      Suspend state */
        case USB_FUNCTION_DS_SPD_DFLT:                  /* Default    Suspend state */
        case USB_FUNCTION_DS_SPD_ADDR:                  /* Address    Suspend state */
            dvst = USB_FUNCTION_DVST_SUSPEND;
        break;

        default:                                        /* error */
            dvst = USB_FUNCTION_DVST_SUSPEND;
        break;
    }

    return dvst;
}

/*******************************************************************************
* Function Name: usb1_api_function_start_receive_transfer
* Description  : Starts USB data reception using the pipe specified in the argument.
*              : The FIFO for using is set in the pipe definition table.
* Arguments    : uint16_t pipe      ; Pipe Number
*              : uint32_t size      ; Data Size
*              : uint8_t *data      ; Data data Address
* Return Value : none
*******************************************************************************/
void usb1_api_function_start_receive_transfer (uint16_t pipe, uint32_t size, uint8_t * data)
{
    usb1_function_start_receive_transfer(pipe, size, data);
}

/*******************************************************************************
* Function Name: usb1_api_function_start_send_transfer
* Description  : Starts the USB data communication using pipe specified by the argument.
* Arguments    : uint16_t pipe     ; Pipe Number
*              : uint32_t size     ; Data Size
*              : uint8_t *data     ; Data data Address
* Return Value : DEVDRV_USBF_WRITEEND           ; Write end
*              : DEVDRV_USBF_WRITESHRT          ; short data
*              : DEVDRV_USBF_WRITING            ; Continue of data write
*              : DEVDRV_USBF_WRITEDMA           ; Write DMA
*              : DEVDRV_USBF_FIFOERROR          ; FIFO status
*******************************************************************************/
uint16_t usb1_api_function_start_send_transfer (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t status;

    status = usb1_function_start_send_transfer(pipe, size, data);

    return status;
}

/*******************************************************************************
* Function Name: usb1_api_function_check_pipe_status
* Description  : Starts USB data reception using the pipe specified in the argument.
*              : The FIFO for using is set in the pipe definition table.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint32_t *size     ; Data Size
* Return Value : Pipe Status
*******************************************************************************/
uint16_t usb1_api_function_check_pipe_status (uint16_t pipe, uint32_t * size)
{
    if (g_usb1_function_pipe_status[pipe] == DEVDRV_USBF_PIPE_DONE)
    {
        *size = g_usb1_function_PipeDataSize[pipe];
        g_usb1_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_IDLE;

        return DEVDRV_USBF_PIPE_DONE;
    }
    else if (g_usb1_function_pipe_status[pipe] == DEVDRV_USBF_PIPE_NORES)
    {
        *size = 0;
        g_usb1_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_IDLE;

        return DEVDRV_USBF_PIPE_NORES;
    }
    else if (g_usb1_function_pipe_status[pipe] == DEVDRV_USBF_PIPE_STALL)
    {
        *size = 0;
        g_usb1_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_IDLE;

        return DEVDRV_USBF_PIPE_STALL;
    }
    else if (g_usb1_function_pipe_status[pipe] == DEVDRV_USBF_FIFOERROR)
    {
        *size = 0;
        g_usb1_function_pipe_status[pipe] = DEVDRV_USBF_PIPE_IDLE;

        return DEVDRV_USBF_FIFOERROR;
    }
    else
    {
        /* Do Nothing */
    }

    return g_usb1_function_pipe_status[pipe];
}

/*******************************************************************************
* Function Name: usb1_api_function_clear_pipe_status
* Description  : Starts USB data reception using the pipe specified in the argument.
*              : The FIFO for using is set in the pipe definition table.
* Arguments    : uint16_t  pipe     ; Pipe Number
* Return Value : Pipe Status
*******************************************************************************/
void usb1_api_function_clear_pipe_status (uint16_t pipe)
{
    g_usb1_function_pipe_status[pipe]  = DEVDRV_USBF_PIPE_IDLE;
    g_usb1_function_PipeDataSize[pipe] = 0;
}

/*******************************************************************************
* Function Name: usb1_api_function_set_pid_buf
* Description  : Enables communicaqtion in the pipe specified by the argument
*              : (BUF).
* Arguments    : uint16_t pipe             ; pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_set_pid_buf (uint16_t pipe)
{
    usb1_function_set_pid_buf(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_set_pid_nak
* Description  : Disables communication (NAK) in the pipe specified by the argument.
*              : When the pipe status was enabling communication (BUF) before
*              : executing before executing this function, waits in the software
*              : until the pipe becomes ready after setting disabled.
* Arguments    : uint16_t pipe            ; pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_set_pid_nak (uint16_t pipe)
{
    usb1_function_set_pid_nak(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_set_pid_stall
* Description  : Disables communication (STALL) in the pipe specified by the
*              : argument.
* Arguments    : uint16_t pipe            ; pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_set_pid_stall (uint16_t pipe)
{
    usb1_function_set_pid_stall(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_clear_pid_stall
* Description  : Disables communication (NAK) in the pipe specified by the argument.
* Arguments    : uint16_t pipe            ; pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_clear_pid_stall (uint16_t pipe)
{
    usb1_function_clear_pid_stall(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_get_pid
* Description  : Returns the pipe state specified by the argument.
* Arguments    : uint16_t pipe          ; Pipe Number
* Return Value : PID
*******************************************************************************/
uint16_t usb1_api_function_get_pid (uint16_t pipe)
{
    uint16_t pid;

    pid = usb1_function_get_pid(pipe);

    return pid;
}

/*******************************************************************************
* Function Name: usb1_api_function_check_stall
* Description  :
* Arguments    : uint16_t pipe          ; Pipe Number
* Return Value : PID
*******************************************************************************/
int32_t usb1_api_function_check_stall (uint16_t pipe)
{
    uint16_t pid;

    pid = usb1_function_get_pid(pipe);

    if ((pid & DEVDRV_USBF_PID_STALL) == DEVDRV_USBF_PID_STALL)
    {
        return DEVDRV_USBF_STALL;
    }

    return DEVDRV_SUCCESS;
}

/*******************************************************************************
* Function Name: usb1_api_function_set_sqclr
* Description  : Sets the sequence bit of the pipe specified by the argument to
*              : DATA0.
* Arguments    : uint16_t pipe              ; Pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_set_sqclr (uint16_t pipe)
{
    usb1_function_set_sqclr(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_set_sqset
* Description  : Sets the sequence bit of the pipe specified by the argument to
*              : DATA1.
* Arguments    : uint16_t pipe   ; Pipe number
* Return Value : none
*******************************************************************************/
void usb1_api_function_set_sqset (uint16_t pipe)
{
    usb1_function_set_sqset(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_set_csclr
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
void usb1_api_function_set_csclr (uint16_t pipe)
{
    usb1_function_set_csclr(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_set_curpipe
* Description  : Allocates FIF0 specifed by the argument in the pipe assigned
*              : by the argument.
* Arguments    : uint16_t pipe      ; Pipe Number
*              : uint16_t fifosel   ; Select FIFO
*              : uint16_t isel      ; FIFO Access Direction
*              : uint16_t mbw       ; FIFO Port Access Bit Width
* Return Value : none
*******************************************************************************/
void usb1_api_function_set_curpipe (uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw)
{
    usb1_function_set_curpipe(pipe, fifosel, isel, mbw);
}

/*******************************************************************************
* Function Name: usb1_api_function_clear_brdy_sts
* Description  : Clear BRDY interrupt status in the pipe spceified by the argument.
* Arguments    : uint16_t pipe        ; pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_clear_brdy_sts (uint16_t pipe)
{
    usb1_function_clear_brdy_sts(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_clear_bemp_sts
* Description  : Clear BEMP interrupt status in the pipe spceified by the argument.
* Arguments    : uint16_t pipe        ; pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_clear_bemp_sts (uint16_t pipe)
{
    usb1_function_clear_bemp_sts(pipe);
}

/*******************************************************************************
* Function Name: usb1_api_function_clear_nrdy_sts
* Description  : Clear NRDY interrupt status in the pipe spceified by the argument.
* Arguments    : uint16_t pipe        ; pipe Number
* Return Value : none
*******************************************************************************/
void usb1_api_function_clear_nrdy_sts (uint16_t pipe)
{
    usb1_function_clear_nrdy_sts(pipe);
}

/* End of File */
