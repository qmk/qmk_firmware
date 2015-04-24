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
* File Name    : usb1_host_intrn.c
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
#if(1) /* ohci_wrapp */
#include "ohci_wrapp_RZ_A1_local.h"
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
* Function Name: usb1_host_brdy_int
* Description  : Executes BRDY interrupt(USB_HOST_PIPE1-9).
*              : According to the pipe that interrupt is generated in,
*              : reads/writes buffer allocated in the pipe.
*              : This function is executed in the BRDY interrupt handler.
*              : This function clears BRDY interrupt status and BEMP interrupt
*              : status.
* Arguments    : uint16_t status       ; BRDYSTS Register Value
*              : uint16_t int_enb      ; BRDYENB Register Value
* Return Value : none
*******************************************************************************/
void usb1_host_brdy_int (uint16_t status, uint16_t int_enb)
{
    uint32_t int_sense = 0;
    uint16_t pipe;
    uint16_t pipebit;

    for (pipe = USB_HOST_PIPE1; pipe <= USB_HOST_MAX_PIPE_NO; pipe++)
    {
        pipebit = g_usb1_host_bit_set[pipe];

        if ((status & pipebit) && (int_enb & pipebit))
        {
            USB201.BRDYSTS = (uint16_t)~pipebit;
            USB201.BEMPSTS = (uint16_t)~pipebit;

            if ((g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE) == USB_HOST_D0FIFO_DMA)
            {
                if (g_usb1_host_DmaStatus[USB_HOST_D0FIFO] != USB_HOST_DMA_READY)
                {
                    usb1_host_dma_interrupt_d0fifo(int_sense);
                }

                if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
                {
                    usb1_host_read_dma(pipe);
                    usb1_host_disable_brdy_int(pipe);
                }
                else
                {
                    USB201.D0FIFOCTR = USB_HOST_BITBCLR;
                    g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_DONE;
                }
            }
            else if ((g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE) == USB_HOST_D1FIFO_DMA)
            {
                if (g_usb1_host_DmaStatus[USB_HOST_D1FIFO] != USB_HOST_DMA_READY)
                {
                    usb1_host_dma_interrupt_d1fifo(int_sense);
                }

                if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
                {
                    usb1_host_read_dma(pipe);
                    usb1_host_disable_brdy_int(pipe);
                }
                else
                {
                    USB201.D1FIFOCTR = USB_HOST_BITBCLR;
                    g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_DONE;
                }
            }
            else
            {
                if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_DIR_SHIFT, USB_PIPECFG_DIR) == 0)
                {
                    usb1_host_read_buffer(pipe);
                }
                else
                {
                    usb1_host_write_buffer(pipe);
                }
            }
#if(1) /* ohci_wrapp */
            switch (g_usb1_host_pipe_status[pipe])
            {
                case USB_HOST_PIPE_DONE:
                    ohciwrapp_loc_TransEnd(pipe, TD_CC_NOERROR);
                break;
                case USB_HOST_PIPE_NORES:
                case USB_HOST_PIPE_STALL:
                case USB_HOST_PIPE_ERROR:
                    ohciwrapp_loc_TransEnd(pipe, TD_CC_STALL);
                break;
                default:
                    /* Do Nothing */
                break;
            }
#endif
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_nrdy_int
* Description  : Executes NRDY interrupt(USB_HOST_PIPE1-9).
*              : Checks NRDY interrupt cause by PID. When the cause if STALL,
*              : regards the pipe state as STALL and ends the processing.
*              : Then the cause is not STALL, increments the error count to
*              : communicate again. When the error count is 3, determines
*              : the pipe state as USB_HOST_PIPE_NORES and ends the processing.
*              : This function is executed in the NRDY interrupt handler.
*              : This function clears NRDY interrupt status.
* Arguments    : uint16_t status       ; NRDYSTS Register Value
*              : uint16_t int_enb      ; NRDYENB Register Value
* Return Value : none
*******************************************************************************/
void usb1_host_nrdy_int (uint16_t status, uint16_t int_enb)
{
    uint16_t pid;
    uint16_t pipe;
    uint16_t bitcheck;

    bitcheck = (uint16_t)(status & int_enb);

    USB201.NRDYSTS = (uint16_t)~status;

    for (pipe = USB_HOST_PIPE1; pipe <= USB_HOST_MAX_PIPE_NO; pipe++)
    {
        if ((bitcheck&g_usb1_host_bit_set[pipe]) == g_usb1_host_bit_set[pipe])
        {
            if (RZA_IO_RegRead_16(&USB201.SYSCFG0,
                                    USB_SYSCFG_DCFM_SHIFT,
                                    USB_SYSCFG_DCFM) == 1)
            {
                if (g_usb1_host_pipe_status[pipe] == USB_HOST_PIPE_WAIT)
                {
                    pid = usb1_host_get_pid(pipe);

                    if ((pid == USB_HOST_PID_STALL) || (pid == USB_HOST_PID_STALL2))
                    {
                        g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_STALL;
#if(1) /* ohci_wrapp */
                        ohciwrapp_loc_TransEnd(pipe, TD_CC_STALL);
#endif
                    }
                    else
                    {
#if(1) /* ohci_wrapp */
                        g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_NORES;
                        ohciwrapp_loc_TransEnd(pipe, TD_CC_DEVICENOTRESPONDING);
#else
                        g_usb1_host_PipeIgnore[pipe]++;

                        if (g_usb1_host_PipeIgnore[pipe] == 3)
                        {
                            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_NORES;
                        }
                        else
                        {
                            usb1_host_set_pid_buf(pipe);
                        }
#endif
                    }
                }
            }
            else
            {
                /* USB Function */
            }
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_bemp_int
* Description  : Executes BEMP interrupt(USB_HOST_PIPE1-9).
* Arguments    : uint16_t status       ; BEMPSTS Register Value
*              : uint16_t int_enb      ; BEMPENB Register Value
* Return Value : none
*******************************************************************************/
void usb1_host_bemp_int (uint16_t status, uint16_t int_enb)
{
    uint16_t pid;
    uint16_t pipe;
    uint16_t bitcheck;
    uint16_t inbuf;

    bitcheck = (uint16_t)(status & int_enb);

    USB201.BEMPSTS = (uint16_t)~status;

    for (pipe = USB_HOST_PIPE1; pipe <= USB_HOST_MAX_PIPE_NO; pipe++)
    {
        if ((bitcheck&g_usb1_host_bit_set[pipe]) == g_usb1_host_bit_set[pipe])
        {
            pid = usb1_host_get_pid(pipe);

            if ((pid == USB_HOST_PID_STALL) || (pid == USB_HOST_PID_STALL2))
            {
                g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_STALL;
#if(1) /* ohci_wrapp */
                ohciwrapp_loc_TransEnd(pipe, TD_CC_STALL);
#endif
            }
            else
            {
                inbuf = usb1_host_get_inbuf(pipe);

                if (inbuf == 0)
                {
                    usb1_host_disable_bemp_int(pipe);
                    usb1_host_set_pid_nak(pipe);
                    g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_DONE;
#if(1) /* ohci_wrapp */
                    ohciwrapp_loc_TransEnd(pipe, TD_CC_NOERROR);
#endif
                }
            }
        }
    }
}

/* End of File */
