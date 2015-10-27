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
* File Name    : usb1_host_dma.c
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
/* #include "usb1_host_dmacdrv.h" */


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
static void usb1_host_dmaint(uint16_t fifo);
static void usb1_host_dmaint_buf2fifo(uint16_t pipe);
static void usb1_host_dmaint_fifo2buf(uint16_t pipe);


/*******************************************************************************
* Function Name: usb1_host_dma_stop_d0
* Description  : D0FIFO DMA stop
* Arguments    : uint16_t pipe     : pipe number
*              : uint32_t remain   : transfer byte
* Return Value : none
*******************************************************************************/
void usb1_host_dma_stop_d0 (uint16_t pipe, uint32_t remain)
{
    uint16_t dtln;
    uint16_t dfacc;
    uint16_t buffer;
    uint16_t sds_b = 1;

    dfacc = RZA_IO_RegRead_16(&USB201.D0FBCFG,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
    if (dfacc == 2)
    {
        sds_b = 32;
    }
    else if (dfacc == 1)
    {
        sds_b = 16;
    }
    else
    {
        if (g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size == 2)
        {
            sds_b = 4;
        }
        else if (g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size == 1)
        {
            sds_b = 2;
        }
        else
        {
            sds_b = 1;
        }
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
    {
        if (g_usb1_host_pipe_status[pipe] != USB_HOST_PIPE_DONE)
        {
            buffer = USB201.D0FIFOCTR;
            dtln   = (buffer & USB_HOST_BITDTLN);

            if ((dtln % sds_b) != 0)
            {
                remain += (sds_b - (dtln % sds_b));
            }
            g_usb1_host_PipeDataSize[pipe] = (g_usb1_host_data_count[pipe] - remain);
            g_usb1_host_data_count[pipe]   = remain;
        }
    }

    RZA_IO_RegWrite_16(&USB201.D0FIFOSEL,
                        0,
                        USB_DnFIFOSEL_DREQE_SHIFT,
                        USB_DnFIFOSEL_DREQE);
}

/*******************************************************************************
* Function Name: usb1_host_dma_stop_d1
* Description  : D1FIFO DMA stop
* Arguments    : uint16_t pipe     : pipe number
*              : uint32_t remain   : transfer byte
* Return Value : none
*******************************************************************************/
void usb1_host_dma_stop_d1 (uint16_t pipe, uint32_t remain)
{
    uint16_t dtln;
    uint16_t dfacc;
    uint16_t buffer;
    uint16_t sds_b = 1;

    dfacc = RZA_IO_RegRead_16(&USB201.D1FBCFG,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
    if (dfacc == 2)
    {
        sds_b = 32;
    }
    else if (dfacc == 1)
    {
        sds_b = 16;
    }
    else
    {
        if (g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size == 2)
        {
            sds_b = 4;
        }
        else if (g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size == 1)
        {
            sds_b = 2;
        }
        else
        {
            sds_b = 1;
        }
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
    {
        if (g_usb1_host_pipe_status[pipe] != USB_HOST_PIPE_DONE)
        {
            buffer = USB201.D1FIFOCTR;
            dtln = (buffer & USB_HOST_BITDTLN);

            if ((dtln % sds_b) != 0)
            {
                remain += (sds_b - (dtln % sds_b));
            }
            g_usb1_host_PipeDataSize[pipe] = (g_usb1_host_data_count[pipe] - remain);
            g_usb1_host_data_count[pipe]   = remain;
        }
    }

    RZA_IO_RegWrite_16(&USB201.D1FIFOSEL,
                        0,
                        USB_DnFIFOSEL_DREQE_SHIFT,
                        USB_DnFIFOSEL_DREQE);
}

/*******************************************************************************
* Function Name: usb1_host_dma_interrupt_d0fifo
* Description  : This function is DMA interrupt handler entry.
*              : Execute usb1_host_dmaint() after disabling DMA interrupt in this function.
*              : Disable DMA interrupt to DMAC executed when USB_HOST_D0FIFO_DMA is
*              : specified by dma->fifo.
*              : Register this function as DMA complete interrupt.
* Arguments    : uint32_t int_sense ; Interrupts detection mode
*              :                    ;  INTC_LEVEL_SENSITIVE : Level sense
*              :                    ;  INTC_EDGE_TRIGGER : Edge trigger
* Return Value : none
*******************************************************************************/
void usb1_host_dma_interrupt_d0fifo (uint32_t int_sense)
{
    usb1_host_dmaint(USB_HOST_D0FIFO);
    g_usb1_host_DmaStatus[USB_HOST_D0FIFO] = USB_HOST_DMA_READY;
}

/*******************************************************************************
* Function Name: usb1_host_dma_interrupt_d1fifo
* Description  : This function is DMA interrupt handler entry.
*              : Execute usb0_host_dmaint() after disabling DMA interrupt in this function.
*              : Disable DMA interrupt to DMAC executed when USB_HOST_D1FIFO_DMA is
*              : specified by dma->fifo.
*              : Register this function as DMA complete interrupt.
* Arguments    : uint32_t int_sense ; Interrupts detection mode
*              :                    ;  INTC_LEVEL_SENSITIVE : Level sense
*              :                    ;  INTC_EDGE_TRIGGER : Edge trigger
* Return Value : none
*******************************************************************************/
void usb1_host_dma_interrupt_d1fifo (uint32_t int_sense)
{
    usb1_host_dmaint(USB_HOST_D1FIFO);
    g_usb1_host_DmaStatus[USB_HOST_D1FIFO] = USB_HOST_DMA_READY;
}

/*******************************************************************************
* Function Name: usb1_host_dmaint
* Description  : This function is DMA transfer end interrupt
* Arguments    : uint16_t fifo  ; fifo number
*              :                ;  USB_HOST_D0FIFO
*              :                ;  USB_HOST_D1FIFO
* Return Value : none
*******************************************************************************/
static void usb1_host_dmaint (uint16_t fifo)
{
    uint16_t pipe;

    pipe = g_usb1_host_DmaPipe[fifo];

    if (g_usb1_host_DmaInfo[fifo].dir == USB_HOST_BUF2FIFO)
    {
        usb1_host_dmaint_buf2fifo(pipe);
    }
    else
    {
        usb1_host_dmaint_fifo2buf(pipe);
    }
}

/*******************************************************************************
* Function Name: usb1_host_dmaint_fifo2buf
* Description  : Executes read completion from FIFO by DMAC.
* Arguments    : uint16_t pipe       : pipe number
* Return Value : none
*******************************************************************************/
static void usb1_host_dmaint_fifo2buf (uint16_t pipe)
{
    uint32_t remain;
    uint16_t useport;

    if (g_usb1_host_pipe_status[pipe] != USB_HOST_PIPE_DONE)
    {
        useport = (uint16_t)(g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE);

        if (useport == USB_HOST_D0FIFO_DMA)
        {
            remain = Userdef_USB_usb1_host_stop_dma0();
            usb1_host_dma_stop_d0(pipe, remain);

            if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
            {
                if (g_usb1_host_DmaStatus[USB_HOST_D0FIFO] == USB_HOST_DMA_BUSYEND)
                {
                    USB201.D0FIFOCTR = USB_HOST_BITBCLR;
                    g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_DONE;
                }
                else
                {
                    usb1_host_enable_brdy_int(pipe);
                }
            }
        }
        else
        {
            remain = Userdef_USB_usb1_host_stop_dma1();
            usb1_host_dma_stop_d1(pipe, remain);

            if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
            {
                if (g_usb1_host_DmaStatus[USB_HOST_D1FIFO] == USB_HOST_DMA_BUSYEND)
                {
                    USB201.D1FIFOCTR = USB_HOST_BITBCLR;
                    g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_DONE;
                }
                else
                {
                    usb1_host_enable_brdy_int(pipe);
                }
            }
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_dmaint_buf2fifo
* Description  : Executes write completion in FIFO by DMAC.
* Arguments    : uint16_t pipe     : pipe number
* Return Value : none
*******************************************************************************/
static void usb1_host_dmaint_buf2fifo (uint16_t pipe)
{
    uint16_t useport;
    uint32_t remain;

    useport = (uint16_t)(g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE);

    if (useport == USB_HOST_D0FIFO_DMA)
    {
        remain = Userdef_USB_usb1_host_stop_dma0();
        usb1_host_dma_stop_d0(pipe, remain);

        if (g_usb1_host_DmaBval[USB_HOST_D0FIFO] != 0)
        {
            RZA_IO_RegWrite_16(&USB201.D0FIFOCTR,
                                1,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL);
        }
    }
    else
    {
        remain = Userdef_USB_usb1_host_stop_dma1();
        usb1_host_dma_stop_d1(pipe, remain);

        if (g_usb1_host_DmaBval[USB_HOST_D1FIFO] != 0)
        {
            RZA_IO_RegWrite_16(&USB201.D1FIFOCTR,
                                1,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL);
        }
    }

    usb1_host_enable_bemp_int(pipe);
}

/* End of File */
