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
* File Name    : usb1_host_dataio.c
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
static uint16_t g_usb1_host_mbw[(USB_HOST_MAX_PIPE_NO + 1)];

static void     usb1_host_start_receive_trns_c(uint16_t pipe, uint32_t size, uint8_t *data);
static void     usb1_host_start_receive_trns_d0(uint16_t pipe, uint32_t size, uint8_t *data);
static void     usb1_host_start_receive_trns_d1(uint16_t pipe, uint32_t size, uint8_t *data);
static void     usb1_host_start_receive_dma_d0(uint16_t pipe, uint32_t size, uint8_t *data);
static void     usb1_host_start_receive_dma_d1(uint16_t pipe, uint32_t size, uint8_t *data);
static uint16_t usb1_host_read_dma_d0(uint16_t pipe);
static uint16_t usb1_host_read_dma_d1(uint16_t pipe);
static uint16_t usb1_host_write_dma_d0(uint16_t pipe);
static uint16_t usb1_host_write_dma_d1(uint16_t pipe);

static void     usb1_host_read_c_fifo(uint16_t pipe, uint16_t count);
static void     usb1_host_write_c_fifo(uint16_t Pipe, uint16_t count);
static void     usb1_host_read_d0_fifo(uint16_t pipe, uint16_t count);
static void     usb1_host_write_d0_fifo(uint16_t pipe, uint16_t count);
static void     usb1_host_read_d1_fifo(uint16_t pipe, uint16_t count);
static void     usb1_host_write_d1_fifo(uint16_t pipe, uint16_t count);

static void     usb1_host_clear_transaction_counter(uint16_t pipe);
static void     usb1_host_set_transaction_counter(uint16_t pipe, uint32_t count);

static uint32_t usb1_host_com_get_dmasize(uint32_t trncount, uint32_t dtptr);

static uint16_t usb1_host_set_dfacc_d0(uint16_t mbw, uint32_t count);
static uint16_t usb1_host_set_dfacc_d1(uint16_t mbw, uint32_t count);


/*******************************************************************************
* Function Name: usb1_host_start_send_transfer
* Description  : Starts the USB data communication using pipe specified by the argument.
* Arguments    : uint16_t  pipe    ; Pipe Number
*              : uint32_t size     ; Data Size
*              : uint8_t  *data    ; Data data Address
* Return Value : USB_HOST_WRITEEND          ; Write end
*              : USB_HOST_WRITESHRT         ; short data
*              : USB_HOST_WRITING           ; Continue of data write
*              : USB_HOST_WRITEDMA          ; Write DMA
*              : USB_HOST_FIFOERROR         ; FIFO status
*******************************************************************************/
uint16_t usb1_host_start_send_transfer (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t status;
    uint16_t usefifo;
    uint16_t mbw;

    g_usb1_host_data_count[pipe]   = size;
    g_usb1_host_data_pointer[pipe] = (uint8_t *)data;
    g_usb1_host_pipe_status[pipe]  = USB_HOST_PIPE_WAIT;

    usb1_host_clear_bemp_sts(pipe);
    usb1_host_clear_brdy_sts(pipe);
    usb1_host_clear_nrdy_sts(pipe);

    mbw = usb1_host_get_mbw(size, (uint32_t)data);

    usefifo = (uint16_t)(g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE);

    switch (usefifo)
    {
        case USB_HOST_D0FIFO_USE:
        case USB_HOST_D0FIFO_DMA:
            usefifo = USB_HOST_D0USE;
        break;

        case USB_HOST_D1FIFO_USE:
        case USB_HOST_D1FIFO_DMA:
            usefifo = USB_HOST_D1USE;
        break;

        default:
            usefifo = USB_HOST_CUSE;
        break;
    };

    usb1_host_set_curpipe(USB_HOST_PIPE0, usefifo, USB_HOST_NO, mbw);

    usb1_host_clear_transaction_counter(pipe);

#if(1) /* ohci_wrapp */
#else
    usb1_host_aclrm(pipe);
#endif

    status = usb1_host_write_buffer(pipe);

    if (status != USB_HOST_FIFOERROR)
    {
        usb1_host_set_pid_buf(pipe);
    }

    return status;
}

/*******************************************************************************
* Function Name: usb1_host_write_buffer
* Description  : Writes data in the buffer allocated in the pipe specified by
*              : the argument. The FIFO for using is set in the pipe definition table.
* Arguments    : uint16_t pipe      ; Pipe Number
* Return Value : USB_HOST_WRITEEND          ; Write end
*              : USB_HOST_WRITESHRT         ; short data
*              : USB_HOST_WRITING           ; Continue of data write
*              : USB_HOST_WRITEDMA          ; Write DMA
*              : USB_HOST_FIFOERROR         ; FIFO status
*******************************************************************************/
uint16_t usb1_host_write_buffer (uint16_t pipe)
{
    uint16_t status;
    uint16_t usefifo;

    g_usb1_host_PipeIgnore[pipe] = 0;
    usefifo = (uint16_t)(g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE);

    switch (usefifo)
    {
        case USB_HOST_D0FIFO_USE:
            status = usb1_host_write_buffer_d0(pipe);
        break;

        case USB_HOST_D1FIFO_USE:
            status = usb1_host_write_buffer_d1(pipe);
        break;

        case USB_HOST_D0FIFO_DMA:
            status = usb1_host_write_dma_d0(pipe);
        break;

        case USB_HOST_D1FIFO_DMA:
            status = usb1_host_write_dma_d1(pipe);
        break;

        default:
            status = usb1_host_write_buffer_c(pipe);
        break;
    };

    switch (status)
    {
        case USB_HOST_WRITING:                      /* Continue of data write */
            usb1_host_enable_nrdy_int(pipe);        /* Error (NORES or STALL) */
            usb1_host_enable_brdy_int(pipe);        /* Enable Ready Interrupt */
        break;

        case USB_HOST_WRITEEND:                     /* End of data write */
        case USB_HOST_WRITESHRT:                    /* End of data write */
            usb1_host_disable_brdy_int(pipe);       /* Disable Ready Interrupt */

            usb1_host_clear_nrdy_sts(pipe);
            usb1_host_enable_nrdy_int(pipe);        /* Error (NORES or STALL) */

            /* for last transfer */
            usb1_host_enable_bemp_int(pipe);        /* Enable Empty Interrupt */
        break;

        case USB_HOST_WRITEDMA:                     /* DMA write */
            usb1_host_clear_nrdy_sts(pipe);
            usb1_host_enable_nrdy_int(pipe);        /* Error (NORES or STALL) */
        break;

        case USB_HOST_FIFOERROR:                    /* FIFO access status */
        default:
            usb1_host_disable_brdy_int(pipe);       /* Disable Ready Interrupt */
            usb1_host_disable_bemp_int(pipe);       /* Disable Empty Interrupt */
            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_ERROR;
        break;
    }

    return status;                                  /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_write_buffer_c
* Description  : Writes data in the buffer allocated in the pipe specified in
*              : the argument. Writes data by CPU transfer using CFIFO.
* Arguments    : uint16_t pipe      ; Pipe Number
* Return Value : USB_HOST_WRITEEND          ; Write end
*              : USB_HOST_WRITESHRT         ; short data
*              : USB_HOST_WRITING           ; Continue of data write
*              : USB_HOST_WRITEDMA          ; Write DMA
*              : USB_HOST_FIFOERROR         ; FIFO status
*******************************************************************************/
uint16_t usb1_host_write_buffer_c (uint16_t pipe)
{
    uint32_t count;
    uint16_t size;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);

    if (pipe == USB_HOST_PIPE0)
    {
        buffer = usb1_host_change_fifo_port(pipe, USB_HOST_CUSE, USB_HOST_CFIFO_WRITE, mbw);
    }
    else
    {
        buffer = usb1_host_change_fifo_port(pipe, USB_HOST_CUSE, USB_HOST_NO, mbw);
    }

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    size = usb1_host_get_buf_size(pipe);                    /* Data buffer size */
    mxps = usb1_host_get_mxps(pipe);                        /* Max Packet Size */

    if (g_usb1_host_data_count[pipe] <= (uint32_t)size)
    {
        status = USB_HOST_WRITEEND;                         /* write continues */
        count  = g_usb1_host_data_count[pipe];

        if (count == 0)
        {
            status = USB_HOST_WRITESHRT;                    /* Null Packet is end of write */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_WRITESHRT;                    /* Short Packet is end of write */
        }
    }
    else
    {
        status = USB_HOST_WRITING;                          /* write continues */
        count  = (uint32_t)size;
    }

    usb1_host_write_c_fifo(pipe, (uint16_t)count);

    if (g_usb1_host_data_count[pipe] < (uint32_t)size)
    {
        g_usb1_host_data_count[pipe] = 0;

        if (RZA_IO_RegRead_16(&USB201.CFIFOCTR,
                                USB_CFIFOCTR_BVAL_SHIFT,
                                USB_CFIFOCTR_BVAL) == 0)
        {
            USB201.CFIFOCTR = USB_HOST_BITBVAL;             /* Short Packet */
        }
    }
    else
    {
        g_usb1_host_data_count[pipe] -= count;
    }

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_write_buffer_d0
* Description  : Writes data in the buffer allocated in the pipe specified in the argument.
*              : Writes data by CPU transfer using D0FIFO.
* Arguments    : uint16_t pipe      ; Pipe Number
* Return Value : USB_HOST_WRITEEND          ; Write end
*              : USB_HOST_WRITESHRT         ; short data
*              : USB_HOST_WRITING           ; Continue of data write
*              : USB_HOST_WRITEDMA          ; Write DMA
*              : USB_HOST_FIFOERROR         ; FIFO status
*******************************************************************************/
uint16_t usb1_host_write_buffer_d0 (uint16_t pipe)
{
    uint32_t count;
    uint16_t size;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;

    mbw    = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);
    buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D0USE, USB_HOST_NO, mbw);

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    size = usb1_host_get_buf_size(pipe);                    /* Data buffer size */
    mxps = usb1_host_get_mxps(pipe);                        /* Max Packet Size */

    if (g_usb1_host_data_count[pipe] <= (uint32_t)size)
    {
        status = USB_HOST_WRITEEND;                         /* write continues */
        count = g_usb1_host_data_count[pipe];

        if (count == 0)
        {
            status = USB_HOST_WRITESHRT;                    /* Null Packet is end of write */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_WRITESHRT;                    /* Short Packet is end of write */
        }
    }
    else
    {
        status = USB_HOST_WRITING;                          /* write continues */
        count  = (uint32_t)size;
    }

    usb1_host_write_d0_fifo(pipe, (uint16_t)count);

    if (g_usb1_host_data_count[pipe] < (uint32_t)size)
    {
        g_usb1_host_data_count[pipe] = 0;

        if (RZA_IO_RegRead_16(&USB201.D0FIFOCTR,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL) == 0)
        {
            USB201.D0FIFOCTR = USB_HOST_BITBVAL;            /* Short Packet */
        }
    }
    else
    {
        g_usb1_host_data_count[pipe] -= count;
    }

    return status;                                  /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_write_buffer_d1
* Description  : Writes data in the buffer allocated in the pipe specified in the argument.
*              : Writes data by CPU transfer using D1FIFO.
* Arguments    : uint16_t pipe      ; Pipe Number
* Return Value : USB_HOST_WRITEEND          ; Write end
*              : USB_HOST_WRITESHRT         ; short data
*              : USB_HOST_WRITING           ; Continue of data write
*              : USB_HOST_WRITEDMA          ; Write DMA
*              : USB_HOST_FIFOERROR         ; FIFO status
*******************************************************************************/
uint16_t usb1_host_write_buffer_d1 (uint16_t pipe)
{
    uint32_t count;
    uint16_t size;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);
    buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D1USE, USB_HOST_NO, mbw);

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    size = usb1_host_get_buf_size(pipe);                    /* Data buffer size */
    mxps = usb1_host_get_mxps(pipe);                        /* Max Packet Size */

    if (g_usb1_host_data_count[pipe] <= (uint32_t)size)
    {
        status = USB_HOST_WRITEEND;                         /* write continues */
        count  = g_usb1_host_data_count[pipe];

        if (count == 0)
        {
            status = USB_HOST_WRITESHRT;                    /* Null Packet is end of write */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_WRITESHRT;                    /* Short Packet is end of write */
        }
    }
    else
    {
        status = USB_HOST_WRITING;                          /* write continues */
        count  = (uint32_t)size;
    }

    usb1_host_write_d1_fifo(pipe, (uint16_t)count);

    if (g_usb1_host_data_count[pipe] < (uint32_t)size)
    {
        g_usb1_host_data_count[pipe] = 0;

        if (RZA_IO_RegRead_16(&USB201.D1FIFOCTR,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL) == 0)
        {
            USB201.D1FIFOCTR = USB_HOST_BITBVAL;            /* Short Packet */
        }
    }
    else
    {
        g_usb1_host_data_count[pipe] -= count;
    }

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_write_dma_d0
* Description  : Writes data in the buffer allocated in the pipe specified in the argument.
*              : Writes data by DMA transfer using D0FIFO.
*              : The DMA-ch for using is specified by Userdef_USB_usb1_host_start_dma().
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_WRITEEND          : Write end
*              : USB_HOST_WRITESHRT         : short data
*              : USB_HOST_WRITING           : Continue of data write
*              : USB_HOST_WRITEDMA          : Write DMA
*              : USB_HOST_FIFOERROR         : FIFO status
*******************************************************************************/
static uint16_t usb1_host_write_dma_d0 (uint16_t pipe)
{
    uint32_t count;
    uint16_t size;
    uint16_t buffer;
    uint16_t status;
    uint16_t mbw;
    uint16_t dfacc = 0;

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);
    buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D0DMA, USB_HOST_NO, mbw);

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    size  = usb1_host_get_buf_size(pipe);                   /* Data buffer size */
    count = g_usb1_host_data_count[pipe];

    if (count != 0)
    {
        g_usb1_host_DmaPipe[USB_HOST_D0FIFO] = pipe;

        if ((count % size) != 0)
        {
            g_usb1_host_DmaBval[USB_HOST_D0FIFO] = 1;
        }
        else
        {
            g_usb1_host_DmaBval[USB_HOST_D0FIFO] = 0;
        }

        dfacc = usb1_host_set_dfacc_d0(mbw, count);

        if (mbw == USB_HOST_BITMBW_32)
        {
            g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size = 2;  /* 32bit transfer */
        }
        else if (mbw == USB_HOST_BITMBW_16)
        {
            g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size = 1;  /* 16bit transfer */
        }
        else
        {
            g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size = 0;  /* 8bit transfer */
        }

        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].fifo   = USB_HOST_D0FIFO_DMA;
        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].dir    = USB_HOST_BUF2FIFO;
        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].buffer = (uint32_t)g_usb1_host_data_pointer[pipe];
        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].bytes  = count;

        Userdef_USB_usb1_host_start_dma(&g_usb1_host_DmaInfo[USB_HOST_D0FIFO], dfacc);

        usb1_host_set_curpipe2(pipe, USB_HOST_D0DMA, USB_HOST_NO, mbw, dfacc);

        RZA_IO_RegWrite_16(&USB201.D0FIFOSEL,
                            1,
                            USB_DnFIFOSEL_DREQE_SHIFT,
                            USB_DnFIFOSEL_DREQE);

        g_usb1_host_data_count[pipe]    = 0;
        g_usb1_host_data_pointer[pipe] += count;

        status = USB_HOST_WRITEDMA;                         /* DMA write  */
    }
    else
    {
        if (RZA_IO_RegRead_16(&USB201.D0FIFOCTR,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL) == 0)
        {
            RZA_IO_RegWrite_16(&USB201.D0FIFOCTR,
                                1,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL);        /* Short Packet */
        }
        status = USB_HOST_WRITESHRT;                        /* Short Packet is end of write */
    }

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_write_dma_d1
* Description  : Writes data in the buffer allocated in the pipe specified in the argument.
*              : Writes data by DMA transfer using D1FIFO.
*              : The DMA-ch for using is specified by Userdef_USB_usb1_host_start_dma().
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_WRITEEND          : Write end
*              : USB_HOST_WRITESHRT         : short data
*              : USB_HOST_WRITING           : Continue of data write
*              : USB_HOST_WRITEDMA          : Write DMA
*              : USB_HOST_FIFOERROR         : FIFO status
*******************************************************************************/
static uint16_t usb1_host_write_dma_d1 (uint16_t pipe)
{
    uint32_t count;
    uint16_t size;
    uint16_t buffer;
    uint16_t status;
    uint16_t mbw;
    uint16_t dfacc = 0;

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);
    buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D1DMA, USB_HOST_NO, mbw);

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    size  = usb1_host_get_buf_size(pipe);                   /* Data buffer size */
    count = g_usb1_host_data_count[pipe];

    if (count != 0)
    {
        g_usb1_host_DmaPipe[USB_HOST_D1FIFO] = pipe;

        if ((count % size) != 0)
        {
            g_usb1_host_DmaBval[USB_HOST_D1FIFO] = 1;
        }
        else
        {
            g_usb1_host_DmaBval[USB_HOST_D1FIFO] = 0;
        }

        dfacc = usb1_host_set_dfacc_d1(mbw, count);

        if (mbw == USB_HOST_BITMBW_32)
        {
            g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size = 2;  /* 32bit transfer */
        }
        else if (mbw == USB_HOST_BITMBW_16)
        {
            g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size = 1;  /* 16bit transfer */
        }
        else
        {
            g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size = 0;  /* 8bit transfer */
        }

        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].fifo   = USB_HOST_D1FIFO_DMA;
        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].dir    = USB_HOST_BUF2FIFO;
        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].buffer = (uint32_t)g_usb1_host_data_pointer[pipe];
        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].bytes  = count;

        Userdef_USB_usb1_host_start_dma(&g_usb1_host_DmaInfo[USB_HOST_D1FIFO], dfacc);

        usb1_host_set_curpipe2(pipe, USB_HOST_D1DMA, USB_HOST_NO, mbw , dfacc);

        RZA_IO_RegWrite_16(&USB201.D1FIFOSEL,
                            1,
                            USB_DnFIFOSEL_DREQE_SHIFT,
                            USB_DnFIFOSEL_DREQE);

        g_usb1_host_data_count[pipe]    = 0;
        g_usb1_host_data_pointer[pipe] += count;

        status = USB_HOST_WRITEDMA;                         /* DMA write */
    }
    else
    {
        if (RZA_IO_RegRead_16(&USB201.D1FIFOCTR,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL) == 0)
        {
            RZA_IO_RegWrite_16(&USB201.D1FIFOCTR,
                                1,
                                USB_DnFIFOCTR_BVAL_SHIFT,
                                USB_DnFIFOCTR_BVAL);        /* Short Packet */
        }
        status = USB_HOST_WRITESHRT;                        /* Short Packet is end of write */
    }

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_start_receive_transfer
* Description  : Starts USB data reception using the pipe specified in the argument.
*              : The FIFO for using is set in the pipe definition table.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint32_t  size     ; Data Size
*              : uint8_t  *data     ; Data Address
* Return Value : none
*******************************************************************************/
void usb1_host_start_receive_transfer (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t usefifo;

    usb1_host_clear_bemp_sts(pipe);
    usb1_host_clear_brdy_sts(pipe);
    usb1_host_clear_nrdy_sts(pipe);

    usefifo = (uint16_t)(g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE);

    switch (usefifo)
    {
        case USB_HOST_D0FIFO_USE:
            usb1_host_start_receive_trns_d0(pipe, size, data);
        break;

        case USB_HOST_D1FIFO_USE:
            usb1_host_start_receive_trns_d1(pipe, size, data);
        break;

        case USB_HOST_D0FIFO_DMA:
            usb1_host_start_receive_dma_d0(pipe, size, data);
        break;

        case USB_HOST_D1FIFO_DMA:
            usb1_host_start_receive_dma_d1(pipe, size, data);
        break;

        default:
            usb1_host_start_receive_trns_c(pipe, size, data);
        break;
    }
}

/*******************************************************************************
* Function Name: usb1_host_start_receive_trns_c
* Description  : Reads data from the buffer allocated in the pipe specified in the argument.
*              : Reads data by CPU transfer using CFIFO.
*              : When storing data in the buffer allocated in the pipe specified in the
*              : argument, BRDY interrupt is generated to read data
*              : in the interrupt.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint32_t  size     ; Data Size
*              : uint8_t  *data     ; Data Address
* Return Value : none
*******************************************************************************/
static void usb1_host_start_receive_trns_c (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t mbw;

    usb1_host_set_pid_nak(pipe);
    g_usb1_host_data_count[pipe]   = size;
    g_usb1_host_data_pointer[pipe] = (uint8_t *)data;
    g_usb1_host_PipeIgnore[pipe]   = 0;

    g_usb1_host_PipeDataSize[pipe] = size;
    g_usb1_host_pipe_status[pipe]  = USB_HOST_PIPE_WAIT;

    mbw = usb1_host_get_mbw(size, (uint32_t)data);
    usb1_host_set_curpipe(USB_HOST_PIPE0, USB_HOST_CUSE, USB_HOST_CFIFO_READ, mbw);
    USB201.CFIFOCTR = USB_HOST_BITBCLR;

    usb1_host_set_transaction_counter(pipe, size);

#if(1) /* ohci_wrapp */
#else
    usb1_host_aclrm(pipe);
#endif

    usb1_host_enable_nrdy_int(pipe);
    usb1_host_enable_brdy_int(pipe);

    usb1_host_set_pid_buf(pipe);
}

/*******************************************************************************
* Function Name: usb1_host_start_receive_trns_d0
* Description  : Reads data from the buffer allocated in the pipe specified in the argument.
*              : Reads data by CPU transfer using D0FIFO.
*              : This function does not read data from the buffer.
*              : When storing data in the buffer allocated in the pipe specified
*              : in the argument, BRDY interrupt is generated to read data in the
*              : interrupt.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint32_t  size     ; Data Size
*              : uint8_t  *data     ; Data Address
* Return Value : none
*******************************************************************************/
static void usb1_host_start_receive_trns_d0 (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t mbw;

    usb1_host_set_pid_nak(pipe);
    g_usb1_host_data_count[pipe]   = size;
    g_usb1_host_data_pointer[pipe] = (uint8_t *)data;
    g_usb1_host_PipeIgnore[pipe]   = 0;

    g_usb1_host_PipeDataSize[pipe] = size;
    g_usb1_host_pipe_status[pipe]  = USB_HOST_PIPE_WAIT;

    mbw = usb1_host_get_mbw(size, (uint32_t)data);
    usb1_host_set_curpipe(USB_HOST_PIPE0, USB_HOST_D0USE, USB_HOST_NO, mbw);

    usb1_host_set_transaction_counter(pipe, size);

#if(1) /* ohci_wrapp */
#else
    usb1_host_aclrm(pipe);
#endif

    usb1_host_enable_nrdy_int(pipe);
    usb1_host_enable_brdy_int(pipe);

    usb1_host_set_pid_buf(pipe);
}

/*******************************************************************************
* Function Name: usb1_host_start_receive_trns_d1
* Description  : Reads data from the buffer allocated in the pipe specified in the argument.
*              : Reads data by CPU transfer using D1FIFO.
*              : This function does not read data from the buffer.
*              : When storing data in the buffer allocated in the pipe specified
*              : in the argument, BRDY interrupt is generated to read data.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint32_t  size     ; Data Size
*              : uint8_t  *data     ; Data Address
* Return Value : none
*******************************************************************************/
static void usb1_host_start_receive_trns_d1 (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t mbw;

    usb1_host_set_pid_nak(pipe);
    g_usb1_host_data_count[pipe]   = size;
    g_usb1_host_data_pointer[pipe] = (uint8_t *)data;
    g_usb1_host_PipeIgnore[pipe]   = 0;

    g_usb1_host_PipeDataSize[pipe] = size;
    g_usb1_host_pipe_status[pipe]  = USB_HOST_PIPE_WAIT;

    mbw = usb1_host_get_mbw(size, (uint32_t)data);
    usb1_host_set_curpipe(USB_HOST_PIPE0, USB_HOST_D1USE, USB_HOST_NO, mbw);

    usb1_host_set_transaction_counter(pipe, size);

#if(1) /* ohci_wrapp */
#else
    usb1_host_aclrm(pipe);
#endif

    usb1_host_enable_nrdy_int(pipe);
    usb1_host_enable_brdy_int(pipe);

    usb1_host_set_pid_buf(pipe);
}

/*******************************************************************************
* Function Name: usb1_host_start_receive_dma_d0
* Description  : Reads data from the buffer allocated in the pipe specified in the argument.
*              : Reads data by DMA transfer using D0FIFO.
*              : This function does not read data from the buffer.
*              : When storing data in the buffer allocated in the pipe specified
*              : in the argument, delivered read request to DMAC to read data from
*              : the buffer by DMAC.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint32_t  size     ; Data Size
*              : uint8_t  *data     ; Data Address
* Return Value : none
*******************************************************************************/
static void usb1_host_start_receive_dma_d0 (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t mbw;

    usb1_host_set_pid_nak(pipe);
    g_usb1_host_data_count[pipe]   = size;
    g_usb1_host_data_pointer[pipe] = (uint8_t *)data;
    g_usb1_host_PipeIgnore[pipe]   = 0;

    g_usb1_host_PipeDataSize[pipe] = 0;
    g_usb1_host_pipe_status[pipe]  = USB_HOST_PIPE_WAIT;

    mbw = usb1_host_get_mbw(size, (uint32_t)data);
    usb1_host_set_curpipe(USB_HOST_PIPE0, USB_HOST_D0USE, USB_HOST_NO, mbw);

    usb1_host_set_transaction_counter(pipe, size);

#if(1) /* ohci_wrapp */
#else
    usb1_host_aclrm(pipe);
#endif

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
    {
        usb1_host_read_dma(pipe);

        usb1_host_enable_nrdy_int(pipe);
        usb1_host_enable_brdy_int(pipe);
    }
    else
    {
        usb1_host_enable_nrdy_int(pipe);
        usb1_host_enable_brdy_int(pipe);
    }

    usb1_host_set_pid_buf(pipe);
}

/*******************************************************************************
* Function Name: usb1_host_start_receive_dma_d1
* Description  : Read data from the buffer allocated in the pipe specified in the argument.
*              : Reads data by DMA transfer using D0FIFO.
*              : This function does not read data from the buffer.
*              : When storing data in the buffer allocated in the pipe specified
*              : in the argument, delivered read request to DMAC to read data from
*              : the buffer by DMAC.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint32_t  size     ; Data Size
*              : uint8_t  *data     ; Data Address
* Return Value : none
*******************************************************************************/
static void usb1_host_start_receive_dma_d1 (uint16_t pipe, uint32_t size, uint8_t * data)
{
    uint16_t mbw;

    usb1_host_set_pid_nak(pipe);
    g_usb1_host_data_count[pipe]   = size;
    g_usb1_host_data_pointer[pipe] = (uint8_t *)data;
    g_usb1_host_PipeIgnore[pipe]   = 0;

    g_usb1_host_PipeDataSize[pipe] = 0;
    g_usb1_host_pipe_status[pipe]  = USB_HOST_PIPE_WAIT;

    mbw = usb1_host_get_mbw(size, (uint32_t)data);
    usb1_host_set_curpipe(USB_HOST_PIPE0, USB_HOST_D1USE, USB_HOST_NO, mbw);

    usb1_host_set_transaction_counter(pipe, size);

#if(1) /* ohci_wrapp */
#else
    usb1_host_aclrm(pipe);
#endif

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
    {
        usb1_host_read_dma(pipe);

        usb1_host_enable_nrdy_int(pipe);
        usb1_host_enable_brdy_int(pipe);
    }
    else
    {
        usb1_host_enable_nrdy_int(pipe);
        usb1_host_enable_brdy_int(pipe);
    }

    usb1_host_set_pid_buf(pipe);
}

/*******************************************************************************
* Function Name: usb1_host_read_buffer
* Description  : Reads data from the buffer allocated in the pipe specified
*              : in the argument.
*              : Uses FIF0 set in the pipe definition table.
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_READEND          ; Read end
*              : USB_HOST_READSHRT         ; short data
*              : USB_HOST_READING          ; Continue of data read
*              : USB_HOST_READOVER         ; buffer over
*              : USB_HOST_FIFOERROR        ; FIFO status
*******************************************************************************/
uint16_t usb1_host_read_buffer (uint16_t pipe)
{
    uint16_t status;

    g_usb1_host_PipeIgnore[pipe] = 0;

    if ((g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE) == USB_HOST_D0FIFO_USE)
    {
        status = usb1_host_read_buffer_d0(pipe);
    }
    else if ((g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE) == USB_HOST_D1FIFO_USE)
    {
        status = usb1_host_read_buffer_d1(pipe);
    }
    else
    {
        status = usb1_host_read_buffer_c(pipe);
    }

    switch (status)
    {
        case USB_HOST_READING:                                  /* Continue of data read */
        break;

        case USB_HOST_READEND:                                  /* End of data read */
        case USB_HOST_READSHRT:                                 /* End of data read */
            usb1_host_disable_brdy_int(pipe);
            g_usb1_host_PipeDataSize[pipe] -= g_usb1_host_data_count[pipe];
            g_usb1_host_pipe_status[pipe]   = USB_HOST_PIPE_DONE;
        break;

        case USB_HOST_READOVER:                                 /* buffer over */
            if ((g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE) == USB_HOST_D0FIFO_USE)
            {
                USB201.D0FIFOCTR = USB_HOST_BITBCLR;                /* Clear BCLR */
            }
            else if ((g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE) == USB_HOST_D1FIFO_USE)
            {
                USB201.D1FIFOCTR = USB_HOST_BITBCLR;                /* Clear BCLR */
            }
            else
            {
                USB201.CFIFOCTR = USB_HOST_BITBCLR;                 /* Clear BCLR */
            }
            usb1_host_disable_brdy_int(pipe);                       /* Disable Ready Interrupt */
#if(1) /* ohci_wrapp */
            g_usb1_host_pipe_status[pipe]   = USB_HOST_PIPE_DONE;
#else
            g_usb1_host_pipe_status[pipe]   = USB_HOST_PIPE_ERROR;
#endif
            g_usb1_host_PipeDataSize[pipe] -= g_usb1_host_data_count[pipe];
        break;

        case USB_HOST_FIFOERROR:                                    /* FIFO access status */
        default:
            usb1_host_disable_brdy_int(pipe);                       /* Disable Ready Interrupt */
            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_ERROR;
        break;
    }

    return status;                                      /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_read_buffer_c
* Description  : Reads data from the buffer allocated in the pipe specified in the argument.
*              : Reads data by CPU transfer using CFIFO.
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_READEND          ; Read end
*              : USB_HOST_READSHRT         ; short data
*              : USB_HOST_READING          ; Continue of data read
*              : USB_HOST_READOVER         ; buffer over
*              : USB_HOST_FIFOERROR        ; FIFO status
*******************************************************************************/
uint16_t usb1_host_read_buffer_c (uint16_t pipe)
{
    uint32_t count;
    uint32_t dtln;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;

    mbw    = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);
    buffer = usb1_host_change_fifo_port(pipe, USB_HOST_CUSE, USB_HOST_NO, mbw);

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    dtln = (uint32_t)(buffer & USB_HOST_BITDTLN);
    mxps = usb1_host_get_mxps(pipe);                        /* Max Packet Size */

    if (g_usb1_host_data_count[pipe] < dtln)                /* Buffer Over ? */
    {
        status = USB_HOST_READOVER;
        usb1_host_set_pid_nak(pipe);                        /* Set NAK */
        count = g_usb1_host_data_count[pipe];
    }
    else if (g_usb1_host_data_count[pipe] == dtln)          /* just Receive Size */
    {
        status = USB_HOST_READEND;
        usb1_host_set_pid_nak(pipe);                        /* Set NAK */
        count = dtln;

        if (count == 0)
        {
            status = USB_HOST_READSHRT;                     /* Null Packet receive */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_READSHRT;                     /* Short Packet receive */
        }
    }
    else                                                    /* continue Receive data */
    {
        status = USB_HOST_READING;
        count  = dtln;

        if (count == 0)
        {
            status = USB_HOST_READSHRT;                     /* Null Packet receive */
            usb1_host_set_pid_nak(pipe);                    /* Set NAK */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_READSHRT;                     /* Short Packet receive */
            usb1_host_set_pid_nak(pipe);                    /* Set NAK */
        }
    }

    if (count == 0)                                         /* 0 length packet */
    {
        USB201.CFIFOCTR = USB_HOST_BITBCLR;                 /* Clear BCLR */
    }
    else
    {
        usb1_host_read_c_fifo(pipe, (uint16_t)count);
    }

    g_usb1_host_data_count[pipe] -= count;

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_read_buffer_d0
* Description  : Reads data from the buffer allocated in the pipe specified in
*              : the argument.
*              : Reads data by CPU transfer using D0FIFO.
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_READEND          ; Read end
*              : USB_HOST_READSHRT         ; short data
*              : USB_HOST_READING          ; Continue of data read
*              : USB_HOST_READOVER         ; buffer over
*              : USB_HOST_FIFOERROR        ; FIFO status
*******************************************************************************/
uint16_t usb1_host_read_buffer_d0 (uint16_t pipe)
{
    uint32_t count;
    uint32_t dtln;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;
    uint16_t pipebuf_size;

    mbw    = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);
    buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D0USE, USB_HOST_NO, mbw);

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    dtln = (uint32_t)(buffer & USB_HOST_BITDTLN);
    mxps = usb1_host_get_mxps(pipe);                        /* Max Packet Size */

    if (g_usb1_host_data_count[pipe] < dtln)                /* Buffer Over ? */
    {
        status = USB_HOST_READOVER;
        usb1_host_set_pid_nak(pipe);                        /* Set NAK */
        count = g_usb1_host_data_count[pipe];
    }
    else if (g_usb1_host_data_count[pipe] == dtln)      /* just Receive Size */
    {
        status = USB_HOST_READEND;
        usb1_host_set_pid_nak(pipe);                        /* Set NAK */
        count = dtln;

        if (count == 0)
        {
            status = USB_HOST_READSHRT;                     /* Null Packet receive */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_READSHRT;                     /* Short Packet receive */
        }
    }
    else                                                    /* continue Receive data */
    {
        status = USB_HOST_READING;
        count  = dtln;

        if (count == 0)
        {
            status = USB_HOST_READSHRT;                     /* Null Packet receive */
            usb1_host_set_pid_nak(pipe);                    /* Set NAK */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_READSHRT;                     /* Short Packet receive */
            usb1_host_set_pid_nak(pipe);                    /* Set NAK */
        }
        else
        {
            pipebuf_size = usb1_host_get_buf_size(pipe);    /* Data buffer size */

            if (count != pipebuf_size)
            {
                status = USB_HOST_READSHRT;                 /* Short Packet receive */
                usb1_host_set_pid_nak(pipe);                /* Set NAK */
            }
        }
    }

    if (count == 0)                                         /* 0 length packet */
    {
        USB201.D0FIFOCTR = USB_HOST_BITBCLR;                /* Clear BCLR */
    }
    else
    {
        usb1_host_read_d0_fifo(pipe, (uint16_t)count);
    }

    g_usb1_host_data_count[pipe] -= count;

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_read_buffer_d1
* Description  : Reads data from the buffer allocated in the pipe specified
*              : in the argument.
*              : Reads data by CPU transfer using D1FIFO.
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_READEND          ; Read end
*              : USB_HOST_READSHRT         ; short data
*              : USB_HOST_READING          ; Continue of data read
*              : USB_HOST_READOVER         ; buffer over
*              : USB_HOST_FIFOERROR        ; FIFO status
*******************************************************************************/
uint16_t usb1_host_read_buffer_d1 (uint16_t pipe)
{
    uint32_t count;
    uint32_t dtln;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;
    uint16_t pipebuf_size;

    mbw    = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);
    buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D1USE, USB_HOST_NO, mbw);

    if (buffer == USB_HOST_FIFOERROR)                       /* FIFO access status */
    {
        return USB_HOST_FIFOERROR;
    }

    dtln = (uint32_t)(buffer & USB_HOST_BITDTLN);
    mxps = usb1_host_get_mxps(pipe);                        /* Max Packet Size */

    if (g_usb1_host_data_count[pipe] < dtln)                /* Buffer Over ? */
    {
        status = USB_HOST_READOVER;
        usb1_host_set_pid_nak(pipe);                        /* Set NAK */
        count = g_usb1_host_data_count[pipe];
    }
    else if (g_usb1_host_data_count[pipe] == dtln)      /* just Receive Size */
    {
        status = USB_HOST_READEND;
        usb1_host_set_pid_nak(pipe);                        /* Set NAK */
        count = dtln;

        if (count == 0)
        {
            status = USB_HOST_READSHRT;                     /* Null Packet receive */
        }

        if ((count % mxps) !=0)
        {
            status = USB_HOST_READSHRT;                     /* Short Packet receive */
        }
    }
    else                                                    /* continue Receive data */
    {
        status = USB_HOST_READING;
        count  = dtln;

        if (count == 0)
        {
            status = USB_HOST_READSHRT;                     /* Null Packet receive */
            usb1_host_set_pid_nak(pipe);                    /* Set NAK */
        }

        if ((count % mxps) != 0)
        {
            status = USB_HOST_READSHRT;                     /* Short Packet receive */
            usb1_host_set_pid_nak(pipe);                    /* Set NAK */
        }
        else
        {
            pipebuf_size = usb1_host_get_buf_size(pipe);    /* Data buffer size */
            if (count != pipebuf_size)
            {
                status = USB_HOST_READSHRT;                 /* Short Packet receive */
                usb1_host_set_pid_nak(pipe);                /* Set NAK */
            }
        }
    }

    if (count == 0)                                         /* 0 length packet */
    {
        USB201.D1FIFOCTR = USB_HOST_BITBCLR;                /* Clear BCLR */
    }
    else
    {
        usb1_host_read_d1_fifo(pipe, (uint16_t)count);
    }

    g_usb1_host_data_count[pipe] -= count;

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_read_dma
* Description  : Reads data from the buffer allocated in the pipe specified
*              : in the argument.
*              : Reads data by DMA transfer using D0FIFO or D1FIFO.
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_READEND          ; Read end
*              : USB_HOST_READSHRT         ; short data
*              : USB_HOST_READZERO         ; zero data
*              : USB_HOST_READING          ; Continue of data read
*              : USB_HOST_READOVER         ; buffer over
*              : USB_HOST_FIFOERROR        ; FIFO status
*******************************************************************************/
uint16_t usb1_host_read_dma (uint16_t pipe)
{
    uint16_t status;

    g_usb1_host_PipeIgnore[pipe] = 0;

    if ((g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE) == USB_HOST_D0FIFO_DMA)
    {
        status = usb1_host_read_dma_d0(pipe);
    }
    else
    {
        status = usb1_host_read_dma_d1(pipe);
    }

    switch (status)
    {
        case USB_HOST_READING:                                      /* Continue of data read */
        break;

        case USB_HOST_READZERO:                                     /* End of data read */
            usb1_host_disable_brdy_int(pipe);
            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_DONE;
        break;

        case USB_HOST_READEND:                                      /* End of data read */
        case USB_HOST_READSHRT:                                     /* End of data read */
            usb1_host_disable_brdy_int(pipe);

            if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
            {
                g_usb1_host_PipeDataSize[pipe] -= g_usb1_host_data_count[pipe];
            }
        break;

        case USB_HOST_READOVER:                                     /* buffer over */
            usb1_host_disable_brdy_int(pipe);                       /* Disable Ready Interrupt */

            if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
            {
                g_usb1_host_PipeDataSize[pipe] -= g_usb1_host_data_count[pipe];
            }
#if(1) /* ohci_wrapp */
            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_DONE;
#else
            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_ERROR;
#endif
        break;

        case USB_HOST_FIFOERROR:                                    /* FIFO access status */
        default:
            usb1_host_disable_brdy_int(pipe);                       /* Disable Ready Interrupt */
            g_usb1_host_pipe_status[pipe] = USB_HOST_PIPE_ERROR;
        break;
    }

    return status;                                                  /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_read_dma_d0
* Description  : Writes data in the buffer allocated in the pipe specified
*              : in the argument.
*              : Reads data by DMA transfer using D0FIFO.
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_READEND          ; Read end
*              : USB_HOST_READSHRT         ; short data
*              : USB_HOST_READZERO         ; zero data
*              : USB_HOST_READING          ; Continue of data read
*              : USB_HOST_READOVER         ; buffer over
*              : USB_HOST_FIFOERROR        ; FIFO status
*******************************************************************************/
static uint16_t usb1_host_read_dma_d0 (uint16_t pipe)
{
    uint32_t count;
    uint32_t dtln;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;
    uint16_t dfacc = 0;
    uint16_t pipebuf_size;

    g_usb1_host_DmaStatus[USB_HOST_D0FIFO] = USB_HOST_DMA_READY;

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
    {
        count  = g_usb1_host_data_count[pipe];
        status = USB_HOST_READING;
    }
    else
    {
        buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D0DMA, USB_HOST_NO, mbw);

        if (buffer == USB_HOST_FIFOERROR)                   /* FIFO access status */
        {
            return USB_HOST_FIFOERROR;
        }

        dtln = (uint32_t)(buffer & USB_HOST_BITDTLN);
        mxps = usb1_host_get_mxps(pipe);                    /* Max Packet Size */

        if (g_usb1_host_data_count[pipe] < dtln)            /* Buffer Over ? */
        {
            status = USB_HOST_READOVER;
            count  = g_usb1_host_data_count[pipe];
        }
        else if (g_usb1_host_data_count[pipe] == dtln)  /* just Receive Size */
        {
            status = USB_HOST_READEND;
            count  = dtln;

            if (count == 0)
            {
                status = USB_HOST_READSHRT;                 /* Null Packet receive */
            }

            if ((count % mxps) != 0)
            {
                status = USB_HOST_READSHRT;                 /* Short Packet receive */
            }
        }
        else                                                /* continue Receive data */
        {
            status = USB_HOST_READING;
            count  = dtln;

            if (count == 0)
            {
                status = USB_HOST_READSHRT;                 /* Null Packet receive */
            }

            if ((count % mxps) != 0)
            {
                status = USB_HOST_READSHRT;                 /* Short Packet receive */
            }
            else
            {
                pipebuf_size = usb1_host_get_buf_size(pipe);    /* Data buffer size */

                if (count != pipebuf_size)
                {
                    status = USB_HOST_READSHRT;             /* Short Packet receive */
                }
            }
        }
    }

    if (count == 0)                                         /* 0 length packet */
    {
        if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
        {
            USB201.D0FIFOCTR = USB_HOST_BITBCLR;            /* Clear BCLR */
            status = USB_HOST_READZERO;                     /* Null Packet receive */
        }
        else
        {
            usb1_host_set_curpipe(pipe, USB_HOST_D0DMA, USB_HOST_NO, mbw);
                                                            /* transaction counter No set */
                                                            /* FRDY = 1, DTLN = 0 -> BRDY */
        }
    }
    else
    {
        dfacc = usb1_host_set_dfacc_d0(mbw, count);

        if (mbw == USB_HOST_BITMBW_32)
        {
            g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size = 2;  /* 32bit transfer */
        }
        else if (mbw == USB_HOST_BITMBW_16)
        {
            g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size = 1;  /* 16bit transfer */
        }
        else
        {
            g_usb1_host_DmaInfo[USB_HOST_D0FIFO].size = 0;  /* 8bit transfer */
        }

        g_usb1_host_DmaPipe[USB_HOST_D0FIFO] = pipe;        /* not use in read operation */
        g_usb1_host_DmaBval[USB_HOST_D0FIFO] = 0;           /* not use in read operation */

        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].fifo   = USB_HOST_D0FIFO_DMA;
        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].dir    = USB_HOST_FIFO2BUF;
        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].buffer = (uint32_t)g_usb1_host_data_pointer[pipe];
        g_usb1_host_DmaInfo[USB_HOST_D0FIFO].bytes  = count;

        if (status == USB_HOST_READING)
        {
            g_usb1_host_DmaStatus[USB_HOST_D0FIFO] = USB_HOST_DMA_BUSY;
        }
        else
        {
            g_usb1_host_DmaStatus[USB_HOST_D0FIFO] = USB_HOST_DMA_BUSYEND;
        }

        Userdef_USB_usb1_host_start_dma(&g_usb1_host_DmaInfo[USB_HOST_D0FIFO], dfacc);

        usb1_host_set_curpipe2(pipe, USB_HOST_D0DMA, USB_HOST_NO, mbw , dfacc);

        RZA_IO_RegWrite_16(&USB201.D0FIFOSEL,
                            1,
                            USB_DnFIFOSEL_DREQE_SHIFT,
                            USB_DnFIFOSEL_DREQE);
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
    {
        g_usb1_host_data_count[pipe]   -= count;
        g_usb1_host_data_pointer[pipe] += count;
        g_usb1_host_PipeDataSize[pipe] += count;
    }

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_read_dma_d1
* Description  : Reads data from the buffer allocated in the pipe specified in
*              : the argument.
*              : Reads data by DMA transfer using D1FIFO.
* Arguments    : uint16_t pipe     ; Pipe Number
* Return Value : USB_HOST_READEND          ; Read end
*              : USB_HOST_READSHRT         ; short data
*              : USB_HOST_READZERO         ; zero data
*              : USB_HOST_READING          ; Continue of data read
*              : USB_HOST_READOVER         ; buffer over
*              : USB_HOST_FIFOERROR        ; FIFO status
*******************************************************************************/
static uint16_t usb1_host_read_dma_d1 (uint16_t pipe)
{
    uint32_t count;
    uint32_t dtln;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t status;
    uint16_t mbw;
    uint16_t dfacc = 0;
    uint16_t pipebuf_size;

    g_usb1_host_DmaStatus[USB_HOST_D1FIFO] = USB_HOST_DMA_READY;

    mbw = usb1_host_get_mbw(g_usb1_host_data_count[pipe], (uint32_t)g_usb1_host_data_pointer[pipe]);

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 1)
    {
        count  = g_usb1_host_data_count[pipe];
        status = USB_HOST_READING;
    }
    else
    {
        buffer = usb1_host_change_fifo_port(pipe, USB_HOST_D1DMA, USB_HOST_NO, mbw);

        if (buffer == USB_HOST_FIFOERROR)                   /* FIFO access status */
        {
            return USB_HOST_FIFOERROR;
        }

        dtln = (uint32_t)(buffer & USB_HOST_BITDTLN);
        mxps = usb1_host_get_mxps(pipe);                    /* Max Packet Size */

        if (g_usb1_host_data_count[pipe] < dtln)            /* Buffer Over ? */
        {
            status = USB_HOST_READOVER;
            count  = g_usb1_host_data_count[pipe];
        }
        else if (g_usb1_host_data_count[pipe] == dtln)  /* just Receive Size */
        {
            status = USB_HOST_READEND;
            count  = dtln;

            if (count == 0)
            {
                status = USB_HOST_READSHRT;                 /* Null Packet receive */
            }

            if ((count % mxps) != 0)
            {
                status = USB_HOST_READSHRT;                 /* Short Packet receive */
            }
        }
        else                                                /* continue Receive data */
        {
            status = USB_HOST_READING;
            count  = dtln;

            if (count == 0)
            {
                status = USB_HOST_READSHRT;                 /* Null Packet receive */
            }

            if ((count % mxps) != 0)
            {
                status = USB_HOST_READSHRT;                 /* Short Packet receive */
            }
            else
            {
                pipebuf_size = usb1_host_get_buf_size(pipe);    /* Data buffer size */

                if (count != pipebuf_size)
                {
                    status = USB_HOST_READSHRT;             /* Short Packet receive */
                }
            }
        }
    }

    if (count == 0)                                         /* 0 length packet */
    {
        if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
        {
            USB201.D1FIFOCTR = USB_HOST_BITBCLR;            /* Clear BCLR */
            status = USB_HOST_READZERO;                     /* Null Packet receive */
        }
        else
        {
            usb1_host_set_curpipe(pipe, USB_HOST_D1DMA, USB_HOST_NO, mbw);
                                                            /* transaction counter No set */
                                                            /* FRDY = 1, DTLN = 0 -> BRDY */
        }
    }
    else
    {
        dfacc = usb1_host_set_dfacc_d1(mbw, count);

        if (mbw == USB_HOST_BITMBW_32)
        {
            g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size = 2;  /* 32bit transfer */
        }
        else if (mbw == USB_HOST_BITMBW_16)
        {
            g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size = 1;  /* 16bit transfer */
        }
        else
        {
            g_usb1_host_DmaInfo[USB_HOST_D1FIFO].size = 0;  /* 8bit transfer */
        }

        g_usb1_host_DmaPipe[USB_HOST_D1FIFO] = pipe;        /* not use in read operation */
        g_usb1_host_DmaBval[USB_HOST_D1FIFO] = 0;           /* not use in read operation */

        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].fifo   = USB_HOST_D1FIFO_DMA;
        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].dir    = USB_HOST_FIFO2BUF;
        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].buffer = (uint32_t)g_usb1_host_data_pointer[pipe];
        g_usb1_host_DmaInfo[USB_HOST_D1FIFO].bytes  = count;

        if (status == USB_HOST_READING)
        {
            g_usb1_host_DmaStatus[USB_HOST_D1FIFO] = USB_HOST_DMA_BUSY;
        }
        else
        {
            g_usb1_host_DmaStatus[USB_HOST_D1FIFO] = USB_HOST_DMA_BUSYEND;
        }

        Userdef_USB_usb1_host_start_dma(&g_usb1_host_DmaInfo[USB_HOST_D1FIFO], dfacc);

        usb1_host_set_curpipe2(pipe, USB_HOST_D1DMA, USB_HOST_NO, mbw , dfacc);

        RZA_IO_RegWrite_16(&USB201.D1FIFOSEL,
                            1,
                            USB_DnFIFOSEL_DREQE_SHIFT,
                            USB_DnFIFOSEL_DREQE);
    }

    if (RZA_IO_RegRead_16(&g_usb1_host_pipecfg[pipe], USB_PIPECFG_BFRE_SHIFT, USB_PIPECFG_BFRE) == 0)
    {
        g_usb1_host_data_count[pipe]   -= count;
        g_usb1_host_data_pointer[pipe] += count;
        g_usb1_host_PipeDataSize[pipe] += count;
    }

    return status;                                          /* End or Err or Continue */
}

/*******************************************************************************
* Function Name: usb1_host_change_fifo_port
* Description  : Allocates FIF0 specified by the argument in the pipe assigned
*              : by the argument. After allocating FIF0, waits in the software
*              : till the corresponding pipe becomes ready.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t fifosel   ; Select FIFO
*              : uint16_t isel      ; FIFO Access Direction
*              : uint16_t mbw       ; FIFO Port Access Bit Width
* Return Value : USB_HOST_FIFOERROR         ; Error
*              : Others            ; CFIFOCTR/D0FIFOCTR/D1FIFOCTR Register Value
*******************************************************************************/
uint16_t usb1_host_change_fifo_port (uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw)
{
    uint16_t          buffer;
    uint32_t          loop;
    volatile uint32_t loop2;

    usb1_host_set_curpipe(pipe, fifosel, isel, mbw);

    for (loop = 0; loop < 4; loop++)
    {
        switch (fifosel)
        {
            case USB_HOST_CUSE:
                buffer = USB201.CFIFOCTR;
            break;

            case USB_HOST_D0USE:
            case USB_HOST_D0DMA:
                buffer = USB201.D0FIFOCTR;
            break;

            case USB_HOST_D1USE:
            case USB_HOST_D1DMA:
                buffer = USB201.D1FIFOCTR;
            break;

            default:
                buffer = 0;
            break;
        }

        if ((buffer & USB_HOST_BITFRDY) == USB_HOST_BITFRDY)
        {
            return buffer;
        }

        loop2 = 25;

        while (loop2-- > 0)
        {
            /* wait */
        }
    }

    return USB_HOST_FIFOERROR;
}

/*******************************************************************************
* Function Name: usb1_host_set_curpipe
* Description  : Allocates FIF0 specified by the argument in the pipe assigned
*              : by the argument.
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t fifosel   ; Select FIFO
*              : uint16_t isel      ; FIFO Access Direction
*              : uint16_t mbw       ; FIFO Port Access Bit Width
* Return Value : none
*******************************************************************************/
void usb1_host_set_curpipe (uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw)
{
    uint16_t          buffer;
    uint32_t          loop;
    volatile uint32_t loop2;

    g_usb1_host_mbw[pipe] = mbw;

    switch (fifosel)
    {
        case USB_HOST_CUSE:
            buffer  = USB201.CFIFOSEL;
            buffer &= (uint16_t)~(USB_HOST_BITISEL | USB_HOST_BITCURPIPE);
            buffer |= (uint16_t)(~isel & USB_HOST_BITISEL);
            USB201.CFIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.CFIFOSEL & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE))
                        == (buffer & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE)))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }

            buffer &= (uint16_t)~(USB_HOST_BITISEL | USB_HOST_BITCURPIPE | USB_HOST_BITMBW);
            buffer |= (uint16_t)(isel | pipe | mbw);
            USB201.CFIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.CFIFOSEL & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE))
                        == (buffer & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE)))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }
        break;

        case USB_HOST_D0DMA:
        case USB_HOST_D0USE:
            buffer  = USB201.D0FIFOSEL;
            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE);
            USB201.D0FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D0FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }
            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE | USB_HOST_BITMBW);
            buffer |= (uint16_t)(pipe | mbw);
            USB201.D0FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D0FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }
        break;

        case USB_HOST_D1DMA:
        case USB_HOST_D1USE:
            buffer  = USB201.D1FIFOSEL;
            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE);
            USB201.D1FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D1FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }

            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE | USB_HOST_BITMBW);
            buffer |= (uint16_t)(pipe | mbw);
            USB201.D1FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D1FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }
        break;

        default:
        break;
    }

    /* Cautions !!!
     * Depending on the external bus speed of CPU, you may need to wait for 450ns here.
     * For details, please look at the data sheet.   */
    loop2 = 100;

    while (loop2-- > 0)
    {
        /* wait */
    }
}

/*******************************************************************************
* Function Name: usb1_host_set_curpipe2
* Description  : Allocates FIF0 specified by the argument in the pipe assigned
*              : by the argument.(DFACC)
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t fifosel   ; Select FIFO
*              : uint16_t isel      ; FIFO Access Direction
*              : uint16_t mbw       ; FIFO Port Access Bit Width
*              : uint16_t dfacc     ; DFACC Access mode
* Return Value : none
*******************************************************************************/
void usb1_host_set_curpipe2 (uint16_t pipe, uint16_t fifosel, uint16_t isel, uint16_t mbw, uint16_t dfacc)
{
    uint16_t buffer;
    uint32_t loop;
#ifdef  __USB_HOST_DF_ACC_ENABLE__
    uint32_t dummy;
#endif
    volatile uint32_t loop2;

    g_usb1_host_mbw[pipe] = mbw;

    switch (fifosel)
    {
        case USB_HOST_CUSE:
            buffer  = USB201.CFIFOSEL;
            buffer &= (uint16_t)~(USB_HOST_BITISEL | USB_HOST_BITCURPIPE);
            buffer |= (uint16_t)(~isel & USB_HOST_BITISEL);
            USB201.CFIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.CFIFOSEL & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE))
                        == (buffer & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE)))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }

            buffer &= (uint16_t)~(USB_HOST_BITISEL | USB_HOST_BITCURPIPE | USB_HOST_BITMBW);
            buffer |= (uint16_t)(isel | pipe | mbw);
            USB201.CFIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.CFIFOSEL & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE))
                        == (buffer & (USB_HOST_BITISEL | USB_HOST_BITCURPIPE)))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }
        break;

        case USB_HOST_D0DMA:
        case USB_HOST_D0USE:
            buffer  = USB201.D0FIFOSEL;
#ifdef  __USB_HOST_DF_ACC_ENABLE__
            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE | USB_HOST_BITMBW);

            if (dfacc != 0)
            {
                buffer |= (uint16_t)(USB_HOST_BITMBW_32);
            }
#else
            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE);
#endif
            USB201.D0FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D0FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }

#ifdef  __USB_HOST_DF_ACC_ENABLE__
            if (dfacc != 0)
            {
                dummy = USB201.D0FIFO.UINT32;
            }
#endif

            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE | USB_HOST_BITMBW);
            buffer |= (uint16_t)(pipe | mbw);
            USB201.D0FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D0FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }
        break;

        case USB_HOST_D1DMA:
        case USB_HOST_D1USE:
            buffer  = USB201.D1FIFOSEL;
#ifdef  __USB_HOST_DF_ACC_ENABLE__
            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE | USB_HOST_BITMBW);

            if (dfacc != 0)
            {
                buffer |= (uint16_t)(USB_HOST_BITMBW_32);
            }
#else
            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE);
#endif
            USB201.D1FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D1FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }

#ifdef  __USB_HOST_DF_ACC_ENABLE__
            if (dfacc != 0)
            {
                dummy = USB201.D1FIFO.UINT32;
                loop = dummy;                   // avoid warning.
            }
#endif

            buffer &= (uint16_t)~(USB_HOST_BITCURPIPE | USB_HOST_BITMBW);
            buffer |= (uint16_t)(pipe | mbw);
            USB201.D1FIFOSEL = buffer;

            for (loop = 0; loop < 4; loop++)
            {
                if ((USB201.D1FIFOSEL & USB_HOST_BITCURPIPE) == (buffer & USB_HOST_BITCURPIPE))
                {
                    break;
                }

                loop2 = 100;
                while (loop2-- > 0)
                {
                    /* wait */
                }
            }
        break;

        default:
        break;
    }

    /* Cautions !!!
     * Depending on the external bus speed of CPU, you may need to wait for 450ns here.
     * For details, please look at the data sheet.   */
    loop2 = 100;
    while (loop2-- > 0)
    {
        /* wait */
    }
}

/*******************************************************************************
* Function Name: usb1_host_write_c_fifo
* Description  : Writes data in CFIFO.
*              : Writes data by BYTE/WORD/LONG according to access size
*              : to the pipe specified by the arguments.
*              : Before executing this function, allocating CFIF0 in the specified pipe
*              : should be completed.
*              : Before executing this function, access size to the specified pipe
*              : should be fixed and set in g_usb1_host_mbw[].
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t count     ; Data Size(Byte)
* Return Value : none
*******************************************************************************/
static void usb1_host_write_c_fifo (uint16_t pipe, uint16_t count)
{
    uint16_t even;

    if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_8)
    {
        for (even = count; even; --even)
        {
            USB201.CFIFO.UINT8[HH] = *g_usb1_host_data_pointer[pipe];
            g_usb1_host_data_pointer[pipe] += 1;
        }
    }
    else if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_16)
    {
        for (even = (uint16_t)(count / 2); even; --even)
        {
            USB201.CFIFO.UINT16[H] = *((uint16_t *)g_usb1_host_data_pointer[pipe]);
            g_usb1_host_data_pointer[pipe] += 2;
        }
    }
    else
    {
        for (even = (uint16_t)(count / 4); even; --even)
        {
            USB201.CFIFO.UINT32 = *((uint32_t *)g_usb1_host_data_pointer[pipe]);
            g_usb1_host_data_pointer[pipe] += 4;
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_read_c_fifo
* Description  : Reads data from CFIFO.
*              : Reads data by BYTE/WORD/LONG according to access size
*              : to the pipe specified by the arguments.
*              : Before executing this function, allocating CFIF0 in the specified pipe
*              : should be completed.
*              : Before executing this function, access size to the specified pipe
*              : should be fixed and set in g_usb0_host_mbw[].
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t count     ; Data Size(Byte)
* Return Value : none
*******************************************************************************/
static void usb1_host_read_c_fifo (uint16_t pipe, uint16_t count)
{
    uint16_t even;

    if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_8)
    {
        for (even = count; even; --even)
        {
            *g_usb1_host_data_pointer[pipe] = USB201.CFIFO.UINT8[HH];
            g_usb1_host_data_pointer[pipe] += 1;
        }
    }
    else if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_16)
    {
        for (even = (uint16_t)((count + 1) / 2); even; --even)
        {
            *((uint16_t *)g_usb1_host_data_pointer[pipe]) = USB201.CFIFO.UINT16[H];
            g_usb1_host_data_pointer[pipe] += 2;
        }
    }
    else
    {
        for (even = (uint16_t)((count + 3) / 4); even; --even)
        {
            *((uint32_t *)g_usb1_host_data_pointer[pipe]) = USB201.CFIFO.UINT32;
            g_usb1_host_data_pointer[pipe] += 4;
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_write_d0_fifo
* Description  : Writes data in D0FIFO.
*              : Writes data by BYTE/WORD/LONG according to access size
*              : to the pipe specified by the arguments.
*              : Before executing this function, allocating CFIF0 in the specified pipe
*              : should be completed.
*              : Before executing this function, access size to the specified pipe
*              : should be fixed and set in g_usb0_host_mbw[].
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t count     ; Data Size(Byte)
* Return Value : none
*******************************************************************************/
static void usb1_host_write_d0_fifo (uint16_t pipe, uint16_t count)
{
    uint16_t even;

    if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_8)
    {
        for (even = count; even; --even)
        {
            USB201.D0FIFO.UINT8[HH] = *g_usb1_host_data_pointer[pipe];
            g_usb1_host_data_pointer[pipe] += 1;
        }
    }
    else if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_16)
    {
        for (even = (uint16_t)(count / 2); even; --even)
        {
            USB201.D0FIFO.UINT16[H] = *((uint16_t *)g_usb1_host_data_pointer[pipe]);
            g_usb1_host_data_pointer[pipe] += 2;
        }
    }
    else
    {
        for (even = (uint16_t)(count / 4); even; --even)
        {
            USB201.D0FIFO.UINT32 = *((uint32_t *)g_usb1_host_data_pointer[pipe]);
            g_usb1_host_data_pointer[pipe] += 4;
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_read_d0_fifo
* Description  : Reads data from D0FIFO.
*              : Reads data by BYTE/WORD/LONG according to access size
*              : to the pipe specified by the arguments.
*              : Before executing this function, allocating DOFIF0 in the specified pipe
*              : should be completed.
*              : Before executing this function, access size to the specified pipe
*              : should be fixed and set in g_usb0_host_mbw[].
* Arguments    : uint16_t  Pipe     ; Pipe Number
*              : uint16_t count     ; Data Size(Byte)
* Return Value : none
*******************************************************************************/
static void usb1_host_read_d0_fifo (uint16_t pipe, uint16_t count)
{
    uint16_t even;

    if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_8)
    {
        for (even = count; even; --even)
        {
            *g_usb1_host_data_pointer[pipe] = USB201.D0FIFO.UINT8[HH];
            g_usb1_host_data_pointer[pipe] += 1;
        }
    }
    else if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_16)
    {
        for (even = (uint16_t)((count + 1) / 2); even; --even)
        {
            *((uint16_t *)g_usb1_host_data_pointer[pipe]) = USB201.D0FIFO.UINT16[H];
            g_usb1_host_data_pointer[pipe] += 2;
        }
    }
    else
    {
        for (even = (uint16_t)((count + 3) / 4); even; --even)
        {
            *((uint32_t *)g_usb1_host_data_pointer[pipe]) = USB201.D0FIFO.UINT32;
            g_usb1_host_data_pointer[pipe] += 4;
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_write_d1_fifo
* Description  : Writes data in D1FIFO.
*              : Writes data by BYTE/WORD/LONG according to access size
*              : to the pipe specified by the arguments.
*              : Before executing this function, allocating D1FIF0 in the specified pipe
*              : should be completed.
*              : Before executing this function, access size to the specified pipe
*              : should be fixed and set in g_usb1_host_mbw[].
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t count     ; Data Size(Byte)
* Return Value : none
*******************************************************************************/
static void usb1_host_write_d1_fifo (uint16_t pipe, uint16_t count)
{
    uint16_t even;

    if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_8)
    {
        for (even = count; even; --even)
        {
            USB201.D1FIFO.UINT8[HH] = *g_usb1_host_data_pointer[pipe];
            g_usb1_host_data_pointer[pipe] += 1;
        }
    }
    else if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_16)
    {
        for (even = (uint16_t)(count / 2); even; --even)
        {
            USB201.D1FIFO.UINT16[H] = *((uint16_t *)g_usb1_host_data_pointer[pipe]);
            g_usb1_host_data_pointer[pipe] += 2;
        }
    }
    else
    {
        for (even = (uint16_t)(count / 4); even; --even)
        {
            USB201.D1FIFO.UINT32 = *((uint32_t *)g_usb1_host_data_pointer[pipe]);
            g_usb1_host_data_pointer[pipe] += 4;
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_read_d1_fifo
* Description  : Reads data from D1FIFO.
*              : Reads data by BYTE/WORD/LONG according to access size
*              : to the pipe specified by the arguments.
*              : Before executing this function, allocating D1FIF0 in the specified pipe
*              : should be completed.
*              : Before executing this function, access size to the specified pipe
*              : should be fixed and set in g_usb1_host_mbw[].
* Arguments    : uint16_t  pipe     ; Pipe Number
*              : uint16_t count     ; Data Size(Byte)
* Return Value : none
*******************************************************************************/
static void usb1_host_read_d1_fifo (uint16_t pipe, uint16_t count)
{
    uint16_t even;

    if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_8)
    {
        for (even = count; even; --even)
        {
            *g_usb1_host_data_pointer[pipe] = USB201.D1FIFO.UINT8[HH];
            g_usb1_host_data_pointer[pipe] += 1;
        }
    }
    else if (g_usb1_host_mbw[pipe] == USB_HOST_BITMBW_16)
    {
        for (even = (uint16_t)((count + 1) / 2); even; --even)
        {
            *((uint16_t *)g_usb1_host_data_pointer[pipe]) = USB201.D1FIFO.UINT16[H];
            g_usb1_host_data_pointer[pipe] += 2;
        }
    }
    else
    {
        for (even = (uint16_t)((count + 3) / 4); even; --even)
        {
            *((uint32_t *)g_usb1_host_data_pointer[pipe]) = USB201.D1FIFO.UINT32;
            g_usb1_host_data_pointer[pipe] += 4;
        }
    }
}

/*******************************************************************************
* Function Name: usb1_host_com_get_dmasize
* Description  : Calculates access width of DMA transfer by the argument to
                 return as the Return Value.
* Arguments    : uint32_t trncount   : transfer byte
*              : uint32_t dtptr      : transfer data pointer
* Return Value : DMA transfer size    : 0   8bit
*              :                      : 1  16bit
*              :                      : 2  32bit
*******************************************************************************/
static uint32_t usb1_host_com_get_dmasize (uint32_t trncount, uint32_t dtptr)
{
    uint32_t size;

    if (((trncount & 0x0001) != 0) || ((dtptr & 0x00000001) != 0))
    {
        /*  When transfer byte count is odd         */
        /* or transfer data area is 8-bit alignment */
        size = 0;           /* 8bit */
    }
    else if (((trncount & 0x0003) != 0) || ((dtptr & 0x00000003) != 0))
    {
        /* When the transfer byte count is multiples of 2 */
        /* or the transfer data area is 16-bit alignment */
        size = 1;           /* 16bit */
    }
    else
    {
        /* When the transfer byte count is multiples of 4 */
        /* or the transfer data area is 32-bit alignment */
        size = 2;           /* 32bit */
    }

    return size;
}

/*******************************************************************************
* Function Name: usb1_host_get_mbw
* Description  : Calculates access width of DMA to return the value set in MBW.
* Arguments    : uint32_t trncount   : transfer byte
*              : uint32_t dtptr      : transfer data pointer
* Return Value : FIFO transfer size   : USB_HOST_BITMBW_8    8bit
*              :                      : USB_HOST_BITMBW_16  16bit
*              :                      : USB_HOST_BITMBW_32  32bit
*******************************************************************************/
uint16_t usb1_host_get_mbw (uint32_t trncount, uint32_t dtptr)
{
    uint32_t size;
    uint16_t mbw;

    size = usb1_host_com_get_dmasize(trncount, dtptr);

    if (size == 0)
    {
        /* 8bit */
        mbw = USB_HOST_BITMBW_8;
    }
    else if (size == 1)
    {
        /* 16bit */
        mbw = USB_HOST_BITMBW_16;
    }
    else
    {
        /* 32bit */
        mbw = USB_HOST_BITMBW_32;
    }

    return mbw;
}

/*******************************************************************************
* Function Name: usb1_host_set_transaction_counter
* Description  : Sets transaction counter by the argument(PIPEnTRN).
*              : Clears transaction before setting to enable transaction counter setting.
* Arguments    : uint16_t pipe     ; Pipe number
*              : uint32_t bsize    : Data transfer size
* Return Value : none
*******************************************************************************/
static void usb1_host_set_transaction_counter (uint16_t pipe, uint32_t bsize)
{
    uint16_t mxps;
    uint16_t cnt;

    if (bsize == 0)
    {
        return;
    }

    mxps = usb1_host_get_mxps(pipe);            /* Max Packet Size */

    if ((bsize % mxps) == 0)
    {
        cnt = (uint16_t)(bsize / mxps);
    }
    else
    {
        cnt = (uint16_t)((bsize / mxps) + 1);
    }

    switch (pipe)
    {
        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB201.PIPE1TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
            USB201.PIPE1TRN             = cnt;
            RZA_IO_RegWrite_16(&USB201.PIPE1TRE,
                                1,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB201.PIPE2TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
            USB201.PIPE2TRN             = cnt;
            RZA_IO_RegWrite_16(&USB201.PIPE2TRE,
                                1,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB201.PIPE3TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
            USB201.PIPE3TRN             = cnt;
            RZA_IO_RegWrite_16(&USB201.PIPE3TRE,
                                1,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB201.PIPE4TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
            USB201.PIPE4TRN             = cnt;
            RZA_IO_RegWrite_16(&USB201.PIPE4TRE,
                                1,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB201.PIPE5TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
            USB201.PIPE5TRN             = cnt;
            RZA_IO_RegWrite_16(&USB201.PIPE5TRE,
                                1,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB201.PIPE9TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
            USB201.PIPE9TRN             = cnt;
            RZA_IO_RegWrite_16(&USB201.PIPE9TRE,
                                1,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb1_host_clear_transaction_counter
* Description  : Clears the transaction counter by the argument.
*              : After executing this function, the transaction counter is invalid.
* Arguments    : uint16_t pipe     ; Pipe number
* Return Value : none
*******************************************************************************/
void usb1_host_clear_transaction_counter (uint16_t pipe)
{
    switch (pipe)
    {
        case USB_HOST_PIPE1:
            RZA_IO_RegWrite_16(&USB201.PIPE1TRE,
                                0,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
            RZA_IO_RegWrite_16(&USB201.PIPE1TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
        break;

        case USB_HOST_PIPE2:
            RZA_IO_RegWrite_16(&USB201.PIPE2TRE,
                                0,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
            RZA_IO_RegWrite_16(&USB201.PIPE2TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
        break;

        case USB_HOST_PIPE3:
            RZA_IO_RegWrite_16(&USB201.PIPE3TRE,
                                0,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
            RZA_IO_RegWrite_16(&USB201.PIPE3TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
        break;

        case USB_HOST_PIPE4:
            RZA_IO_RegWrite_16(&USB201.PIPE4TRE,
                                0,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
            RZA_IO_RegWrite_16(&USB201.PIPE4TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
        break;

        case USB_HOST_PIPE5:
            RZA_IO_RegWrite_16(&USB201.PIPE5TRE,
                                0,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
            RZA_IO_RegWrite_16(&USB201.PIPE5TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
        break;

        case USB_HOST_PIPE9:
            RZA_IO_RegWrite_16(&USB201.PIPE9TRE,
                                0,
                                USB_PIPEnTRE_TRENB_SHIFT,
                                USB_PIPEnTRE_TRENB);
            RZA_IO_RegWrite_16(&USB201.PIPE9TRE,
                                1,
                                USB_PIPEnTRE_TRCLR_SHIFT,
                                USB_PIPEnTRE_TRCLR);
        break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: usb1_host_stop_transfer
* Description  : Stops the USB transfer in the pipe specified by the argument.
*              : After stopping the USB transfer, clears the buffer allocated in
*              : the pipe.
*              : After executing this function, allocation in FIF0 becomes USB_HOST_PIPE0;
*              : invalid. After executing this function, BRDY/NRDY/BEMP interrupt
*              : in the corresponding pipe becomes invalid. Sequence bit is also
*              : cleared.
* Arguments    : uint16_t  pipe     ; Pipe Number
* Return Value : none
*******************************************************************************/
void usb1_host_stop_transfer (uint16_t pipe)
{
    uint16_t usefifo;
    uint32_t remain;

    usb1_host_set_pid_nak(pipe);

    usefifo = (uint16_t)(g_usb1_host_PipeTbl[pipe] & USB_HOST_FIFO_USE);

    switch (usefifo)
    {
        case USB_HOST_D0FIFO_USE:
            usb1_host_clear_transaction_counter(pipe);
            USB201.D0FIFOCTR = USB_HOST_BITBCLR;        /* Buffer Clear */
        break;

        case USB_HOST_D1FIFO_USE:
            usb1_host_clear_transaction_counter(pipe);
            USB201.D1FIFOCTR = USB_HOST_BITBCLR;        /* Buffer Clear */
        break;

        case USB_HOST_D0FIFO_DMA:
            remain = Userdef_USB_usb1_host_stop_dma0();
            usb1_host_dma_stop_d0(pipe, remain);
            usb1_host_clear_transaction_counter(pipe);
            USB201.D0FIFOCTR = USB_HOST_BITBCLR;        /* Buffer Clear */
        break;

        case USB_HOST_D1FIFO_DMA:
            remain = Userdef_USB_usb1_host_stop_dma1();
            usb1_host_dma_stop_d1(pipe, remain);
            usb1_host_clear_transaction_counter(pipe);
            USB201.D1FIFOCTR = USB_HOST_BITBCLR;        /* Buffer Clear */
        break;

        default:
            usb1_host_clear_transaction_counter(pipe);
            USB201.CFIFOCTR =  USB_HOST_BITBCLR;        /* Buffer Clear */
        break;
    }

    /* Interrupt of pipe set is disabled */
    usb1_host_disable_brdy_int(pipe);
    usb1_host_disable_nrdy_int(pipe);
    usb1_host_disable_bemp_int(pipe);

#if(1) /* ohci_wrapp */
#else
    usb1_host_aclrm(pipe);
#endif
    usb1_host_set_csclr(pipe);
}

/*******************************************************************************
* Function Name: usb1_host_set_dfacc_d0
* Description  : Sets the DFACC setting value in D0FIFO using the transfer size.
* Arguments    : uint16_t mbw     ; MBW
*              : uint16_t count   ; data count
* Return Value : DFACC Access mode
*******************************************************************************/
static uint16_t usb1_host_set_dfacc_d0 (uint16_t mbw, uint32_t count)
{
    uint16_t dfacc = 0;

#ifndef __USB_HOST_DF_ACC_ENABLE__
    RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                        0,
                        USB_DnFBCFG_DFACC_SHIFT,
                        USB_DnFBCFG_DFACC);
    RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                        0,
                        USB_DnFBCFG_TENDE_SHIFT,
                        USB_DnFBCFG_TENDE);
    dfacc = 0;
#else
    if (mbw == USB_HOST_BITMBW_32)
    {
        if ((count % 32) == 0)
        {
            /* 32byte transfer */
            RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                                2,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
            RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                                0,
                                USB_DnFBCFG_TENDE_SHIFT,
                                USB_DnFBCFG_TENDE);
            dfacc = 2;
        }
        else if ((count % 16) == 0)
        {
            /* 16byte transfer */
            RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                                1,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
            RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                                0,
                                USB_DnFBCFG_TENDE_SHIFT,
                                USB_DnFBCFG_TENDE);
            dfacc = 1;
        }
        else
        {
            RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                                0,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
            RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                                0,
                                USB_DnFBCFG_TENDE_SHIFT,
                                USB_DnFBCFG_TENDE);
            dfacc = 0;
        }
    }
    else if (mbw == USB_HOST_BITMBW_16)
    {
        RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                            0,
                            USB_DnFBCFG_DFACC_SHIFT,
                            USB_DnFBCFG_DFACC);
        RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                            0,
                            USB_DnFBCFG_TENDE_SHIFT,
                            USB_DnFBCFG_TENDE);
        dfacc = 0;
    }
    else
    {
        RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                            0,
                            USB_DnFBCFG_DFACC_SHIFT,
                            USB_DnFBCFG_DFACC);
        RZA_IO_RegWrite_16(&USB201.D0FBCFG,
                            0,
                            USB_DnFBCFG_TENDE_SHIFT,
                            USB_DnFBCFG_TENDE);
        dfacc = 0;
    }
#endif

    return dfacc;
}

/*******************************************************************************
* Function Name: usb1_host_set_dfacc_d1
* Description  : Sets the DFACC setting value in D0FIFO using the transfer size.
* Arguments    : uint16_t mbw     ; MBW
*              : uint16_t count   ; data count
* Return Value : DFACC Access mode
*******************************************************************************/
static uint16_t usb1_host_set_dfacc_d1 (uint16_t mbw, uint32_t count)
{
    uint16_t dfacc = 0;

#ifndef __USB_HOST_DF_ACC_ENABLE__
    RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                        0,
                        USB_DnFBCFG_DFACC_SHIFT,
                        USB_DnFBCFG_DFACC);
    RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                        0,
                        USB_DnFBCFG_TENDE_SHIFT,
                        USB_DnFBCFG_TENDE);
    dfacc = 0;
#else
    if (mbw == USB_HOST_BITMBW_32)
    {
        if ((count % 32) == 0)
        {
            /* 32byte transfer */
            RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                                2,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
            RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                                0,
                                USB_DnFBCFG_TENDE_SHIFT,
                                USB_DnFBCFG_TENDE);
            dfacc = 2;
        }
        else if ((count % 16) == 0)
        {
            /* 16byte transfer */
            RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                                1,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
            RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                                0,
                                USB_DnFBCFG_TENDE_SHIFT,
                                USB_DnFBCFG_TENDE);
            dfacc = 1;
        }
        else
        {
            RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                                0,
                                USB_DnFBCFG_DFACC_SHIFT,
                                USB_DnFBCFG_DFACC);
            RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                                0,
                                USB_DnFBCFG_TENDE_SHIFT,
                                USB_DnFBCFG_TENDE);
            dfacc = 0;
        }
    }
    else if (mbw == USB_HOST_BITMBW_16)
    {
        RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                            0,
                            USB_DnFBCFG_DFACC_SHIFT,
                            USB_DnFBCFG_DFACC);
        RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                            0,
                            USB_DnFBCFG_TENDE_SHIFT,
                            USB_DnFBCFG_TENDE);
        dfacc = 0;
    }
    else
    {
        RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                            0,
                            USB_DnFBCFG_DFACC_SHIFT,
                            USB_DnFBCFG_DFACC);
        RZA_IO_RegWrite_16(&USB201.D1FBCFG,
                            0,
                            USB_DnFBCFG_TENDE_SHIFT,
                            USB_DnFBCFG_TENDE);
        dfacc = 0;
    }
#endif

    return dfacc;
}

/* End of File */
