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
* File Name    : usb0_function_userdef.c
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
#include <stdio.h>
#include "r_typedefs.h"
#include "iodefine.h"
#include "devdrv_usb_function_api.h"
#include "usb0_function_dmacdrv.h"  /* common DMAC driver for USB */


/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/
#define DUMMY_ACCESS OSTM0CNT

/* #define CACHE_WRITEBACK */


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
extern int32_t io_cwb(unsigned long start, unsigned long end);


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
static void usb0_function_enable_dmac0(uint32_t src, uint32_t dst, uint32_t count,
                                       uint32_t size, uint32_t dir, uint32_t fifo, uint16_t dfacc);
static void usb0_function_enable_dmac1(uint32_t src, uint32_t dst, uint32_t count,
                                       uint32_t size, uint32_t dir, uint32_t fifo, uint16_t dfacc);
static void Userdef_USB_usb0_function_delay_10us_2(void);


/*******************************************************************************
Private global variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_d0fifo_dmaintid
* Description  : get D0FIFO DMA Interrupt ID
* Arguments    : none
* Return Value : D0FIFO DMA Interrupt ID
*******************************************************************************/
IRQn_Type Userdef_USB_usb0_function_d0fifo_dmaintid (void)
{
#if 0
    return DMAINT1_IRQn;
#else
    return 0xFFFF;
#endif
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_d1fifo_dmaintid
* Description  : get D1FIFO DMA Interrupt ID
* Arguments    : none
* Return Value : D1FIFO DMA Interrupt ID
*******************************************************************************/
IRQn_Type Userdef_USB_usb0_function_d1fifo_dmaintid (void)
{
#if 0
    return DMAINT1_IRQn;
#else
    return 0xFFFF;
#endif
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_attach
* Description  : Wait for the software of 1ms.
*              : Alter this function according to the user's system.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void Userdef_USB_usb0_function_attach (void)
{
    printf("\n");
    printf("channel 0 attach device\n");
    printf("\n");
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_detach
* Description  : Wait for the software of 1ms.
*              : Alter this function according to the user's system.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void Userdef_USB_usb0_function_detach (void)
{
    printf("\n");
    printf("channel 0 detach device\n");
    printf("\n");
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_delay_1ms
* Description  : Wait for the software of 1ms.
*              : Alter this function according to the user's system.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void Userdef_USB_usb0_function_delay_1ms (void)
{
    volatile int i;
    volatile unsigned long tmp;

    /*
     * Wait 1ms (Please change for your MCU).
     */
    for (i = 0; i < 1440; ++i)
    {
        tmp = DUMMY_ACCESS;
    }
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_delay_xms
* Description  : Wait for the software in the period of time specified by the
*              : argument.
*              : Alter this function according to the user's system.
* Arguments    : uint32_t msec ; Wait Time (msec)
* Return Value : none
*******************************************************************************/
void Userdef_USB_usb0_function_delay_xms (uint32_t msec)
{
    volatile unsigned short i;

    for (i = 0; i < msec; ++i)
    {
        Userdef_USB_usb0_function_delay_1ms();
    }
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_delay_10us
* Description  : Waits for software for the period specified by the argument.
*              : Alter this function according to the user's system.
* Arguments    : uint32_t usec ; Wait Time(x 10usec)
* Return Value : none
*******************************************************************************/
void Userdef_USB_usb0_function_delay_10us (uint32_t usec)
{
    volatile int i;

    /* Wait 10us (Please change for your MCU) */
    for (i = 0; i < usec; ++i)
    {
        Userdef_USB_usb0_function_delay_10us_2();
    }
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_delay_10us_2
* Description  : Waits for software for the period specified by the argument.
*              : Alter this function according to the user's system.
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void Userdef_USB_usb0_function_delay_10us_2 (void)
{
    volatile int i;
    volatile unsigned long tmp;

    /* Wait 1us (Please change for your MCU) */
    for (i = 0; i < 14; ++i)
    {
        tmp = DUMMY_ACCESS;
    }
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_delay_500ns
* Description  : Wait for software for 500ns.
*              : Alter this function according to the user's system.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void Userdef_USB_usb0_function_delay_500ns (void)
{
    volatile int i;
    volatile unsigned long tmp;

    /* Wait 500ns (Please change for your MCU) */
    /* Wait 500ns I clock 266MHz */
    tmp = DUMMY_ACCESS;
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_start_dma
* Description  : Enables DMA transfer on the information specified by the argument.
*              : Set DMAC register by this function to enable DMA transfer.
*              : After executing this function, USB module is set to start DMA
*              : transfer. DMA transfer should not wait for DMA transfer complete.
* Arguments    : USB_FUNCTION_DMA_t *dma   : DMA parameter
*              :  typedef struct{
*              :      uint32_t fifo;    FIFO for using
*              :      uint32_t buffer;  Start address of transfer source/destination
*              :      uint32_t bytes;   Transfer size(Byte)
*              :      uint32_t dir;     Transfer direction(0:Buffer->FIFO, 1:FIFO->Buffer)
*              :      uint32_t size;    DMA transfer size
*              :   } USB_FUNCTION_DMA_t;
*              : uint16_t dfacc ; 0 : cycle steal mode
*              :                  1 : 16byte continuous mode
*              :                  2 : 32byte continuous mode
* Return Value : none
*******************************************************************************/
void Userdef_USB_usb0_function_start_dma (USB_FUNCTION_DMA_t * dma, uint16_t dfacc)
{
    uint32_t trncount;
    uint32_t src;
    uint32_t dst;
    uint32_t size;
    uint32_t dir;
#ifdef CACHE_WRITEBACK
    uint32_t ptr;
#endif

    trncount = dma->bytes;
    dir      = dma->dir;

    if (dir == USB_FUNCTION_FIFO2BUF)
    {
        /* DxFIFO determination */
        dst = dma->buffer;
#ifndef __USB_FUNCTION_DF_ACC_ENABLE__
        if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
        {
            src = (uint32_t)(&USB200.D0FIFO.UINT32);
        }
        else
        {
            src = (uint32_t)(&USB200.D1FIFO.UINT32);
        }
        size = dma->size;

        if (size == 0)
        {
            src += 3;       /* byte access  */
        }
        else if (size == 1)
        {
            src += 2;       /* short access */
        }
        else
        {
            /* Do Nothing */
        }
#else
        size = dma->size;

        if (size == 2)
        {
            /* 32bit access */
            if (dfacc == 2)
            {
                /* 32byte access */
                if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
                {
                    src = (uint32_t)(&USB200.D0FIFOB0);
                }
                else
                {
                    src = (uint32_t)(&USB200.D1FIFOB0);
                }
            }
            else if (dfacc == 1)
            {
                /* 16byte access */
                if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
                {
                    src = (uint32_t)(&USB200.D0FIFOB0);
                }
                else
                {
                    src = (uint32_t)(&USB200.D1FIFOB0);
                }
            }
            else
            {
                /* normal access */
                if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
                {
                    src = (uint32_t)(&USB200.D0FIFO.UINT32);
                }
                else
                {
                    src = (uint32_t)(&USB200.D1FIFO.UINT32);
                }
            }
        }
        else if (size == 1)
        {
            /* 16bit access */
            dfacc = 0;      /* force normal access */

            if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
            {
                src = (uint32_t)(&USB200.D0FIFO.UINT32);
            }
            else
            {
                src = (uint32_t)(&USB200.D1FIFO.UINT32);
            }
            src += 2;       /* short access */
        }
        else
        {
            /* 8bit access */
            dfacc = 0;      /* force normal access */

            if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
            {
                src = (uint32_t)(&USB200.D0FIFO.UINT32);
            }
            else
            {
                src = (uint32_t)(&USB200.D1FIFO.UINT32);
            }
            src += 3;       /* byte access */
        }
#endif
    }
    else
    {
        /* DxFIFO determination */
        src = dma->buffer;
#ifndef __USB_FUNCTION_DF_ACC_ENABLE__
        if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
        {
            dst = (uint32_t)(&USB200.D0FIFO.UINT32);
        }
        else
        {
            dst = (uint32_t)(&USB200.D1FIFO.UINT32);
        }
        size = dma->size;

        if (size == 0)
        {
            dst += 3;       /* byte access  */
        }
        else if (size == 1)
        {
            dst += 2;       /* short access */
        }
        else
        {
            /* Do Nothing */
        }
#else
        size = dma->size;

        if (size == 2)
        {
            /* 32bit access */
            if (dfacc == 2)
            {
                /* 32byte access */
                if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
                {
                    dst = (uint32_t)(&USB200.D0FIFOB0);
                }
                else
                {
                    dst = (uint32_t)(&USB200.D1FIFOB0);
                }
            }
            else if (dfacc == 1)
            {
                /* 16byte access */
                if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
                {
                    dst = (uint32_t)(&USB200.D0FIFOB0);
                }
                else
                {
                    dst = (uint32_t)(&USB200.D1FIFOB0);
                }
            }
            else
            {
                /* normal access */
                if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
                {
                    dst = (uint32_t)(&USB200.D0FIFO.UINT32);
                }
                else
                {
                    dst = (uint32_t)(&USB200.D1FIFO.UINT32);
                }
            }
        }
        else if (size == 1)
        {
            /* 16bit access */
            dfacc = 0;      /* force normal access */
            if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
            {
                dst = (uint32_t)(&USB200.D0FIFO.UINT32);
            }
            else
            {
                dst = (uint32_t)(&USB200.D1FIFO.UINT32);
            }
            dst += 2;       /* short access */
        }
        else
        {
            /* 8bit access */
            dfacc = 0;      /* force normal access */

            if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
            {
                dst = (uint32_t)(&USB200.D0FIFO.UINT32);
            }
            else
            {
                dst = (uint32_t)(&USB200.D1FIFO.UINT32);
            }
            dst += 3;       /* byte access  */
        }
#endif
    }

#ifdef CACHE_WRITEBACK
    ptr = (uint32_t)dma->buffer;

    if ((ptr & 0x20000000ul) == 0)
    {
        io_cwb((uint32_t)ptr, (uint32_t)(ptr) + trncount);
    }
#endif

    if (dma->fifo == USB_FUNCTION_D0FIFO_DMA)
    {
        usb0_function_enable_dmac0(src, dst, trncount, size, dir, dma->fifo, dfacc);
    }
    else
    {
        usb0_function_enable_dmac1(src, dst, trncount, size, dir, dma->fifo, dfacc);
    }
}

/*******************************************************************************
* Function Name: usb0_function_enable_dmac0
* Description  : Enables DMA transfer on the information specified by the argument.
* Arguments    : uint32_t src   : src address
*              : uint32_t dst   : dst address
*              : uint32_t count : transfer byte
*              : uint32_t size  : transfer size
*              : uint32_t dir   : direction
*              : uint32_t fifo  : FIFO(D0FIFO or D1FIFO)
*              : uint16_t dfacc : 0 : normal access
*              :                : 1 : 16byte access
*              :                : 2 : 32byte access
* Return Value : none
*******************************************************************************/
static void usb0_function_enable_dmac0 (uint32_t src, uint32_t dst, uint32_t count,
                                        uint32_t size, uint32_t dir, uint32_t fifo, uint16_t dfacc)
{
    dmac_transinfo_t trans_info;
    uint32_t         request_factor = 0;
    int32_t          ret;

    /* ==== Variable setting for DMAC initialization ==== */
    trans_info.src_addr = (uint32_t)src;                /* Start address of transfer source      */
    trans_info.dst_addr = (uint32_t)dst;                /* Start address of transfer destination */
    trans_info.count    = (uint32_t)count;              /* Total byte count to be transferred    */
#ifndef __USB_FUNCTION_DF_ACC_ENABLE__
    if (size == 0)
    {
        trans_info.src_size = DMAC_TRANS_SIZE_8;        /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_8;        /* Transfer destination transfer size */
    }
    else if (size == 1)
    {
        trans_info.src_size = DMAC_TRANS_SIZE_16;       /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_16;       /* Transfer destination transfer size */
    }
    else if (size == 2)
    {
        trans_info.src_size = DMAC_TRANS_SIZE_32;       /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_32;       /* Transfer destination transfer size */
    }
    else
    {
        printf("size error!!\n");
    }
#else
    if (dfacc == 2)
    {
        /* 32byte access */
        trans_info.src_size = DMAC_TRANS_SIZE_256;      /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_256;      /* Transfer destination transfer size */
    }
    else if (dfacc == 1)
    {
        /* 16byte access */
        trans_info.src_size = DMAC_TRANS_SIZE_128;      /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_128;      /* Transfer destination transfer size */
    }
    else
    {
        /* normal access */
        if (size == 0)
        {
            trans_info.src_size = DMAC_TRANS_SIZE_8;    /* Transfer source transfer size      */
            trans_info.dst_size = DMAC_TRANS_SIZE_8;    /* Transfer destination transfer size */
        }
        else if (size == 1)
        {
            trans_info.src_size = DMAC_TRANS_SIZE_16;   /* Transfer source transfer size      */
            trans_info.dst_size = DMAC_TRANS_SIZE_16;   /* Transfer destination transfer size */
        }
        else if (size == 2)
        {
            trans_info.src_size = DMAC_TRANS_SIZE_32;   /* Transfer source transfer size      */
            trans_info.dst_size = DMAC_TRANS_SIZE_32;   /* Transfer destination transfer size */
        }
        else
        {
            printf("size error!!\n");
        }
    }
#endif

    if (dir == USB_FUNCTION_FIFO2BUF)
    {
        request_factor =DMAC_REQ_USB0_DMA0_RX;          /* USB_0 channel 0 receive FIFO full               */
        trans_info.saddr_dir = DMAC_TRANS_ADR_NO_INC;   /* Count direction of transfer source address      */
        trans_info.daddr_dir = DMAC_TRANS_ADR_INC;      /* Count direction of transfer destination address */
    }
    else if (dir == USB_FUNCTION_BUF2FIFO)
    {
        request_factor =DMAC_REQ_USB0_DMA0_TX;          /* USB_0 channel 0 receive FIFO empty              */
        trans_info.saddr_dir = DMAC_TRANS_ADR_INC;      /* Count direction of transfer source address      */
        trans_info.daddr_dir = DMAC_TRANS_ADR_NO_INC;   /* Count direction of transfer destination address */
    }
    else
    {
        /* Do Nothing */
    }

    /* ==== DMAC initialization ==== */
    usb0_function_DMAC1_PeriReqInit((const dmac_transinfo_t *)&trans_info,
                                    DMAC_MODE_REGISTER,
                                    DMAC_SAMPLE_SINGLE,
                                    request_factor,
                                    0);     /* Don't care DMAC_REQ_REQD is setting in
                                            usb0_function_DMAC1_PeriReqInit() */

    /* ==== DMAC startup ==== */
    ret = usb0_function_DMAC1_Open(DMAC_REQ_MODE_PERI);
    if (ret != 0)
    {
        printf("DMAC1 Open error!!\n");
    }

    return;
}

/*******************************************************************************
* Function Name: usb0_function_enable_dmac1
* Description  : Enables DMA transfer on the information specified by the argument.
* Arguments    : uint32_t src   : src address
*              : uint32_t dst   : dst address
*              : uint32_t count : transfer byte
*              : uint32_t size  : transfer size
*              : uint32_t dir   : direction
*              : uint32_t fifo  : FIFO(D0FIFO or D1FIFO)
*              : uint16_t dfacc : 0 : normal access
*              :                : 1 : 16byte access
*              :                : 2 : 32byte access
* Return Value : none
*******************************************************************************/
static void usb0_function_enable_dmac1 (uint32_t src, uint32_t dst, uint32_t count,
                                        uint32_t size, uint32_t dir, uint32_t fifo, uint16_t dfacc)
{
    dmac_transinfo_t trans_info;
    uint32_t         request_factor = 0;
    int32_t          ret;

    /* ==== Variable setting for DMAC initialization ==== */
    trans_info.src_addr = (uint32_t)src;                /* Start address of transfer source      */
    trans_info.dst_addr = (uint32_t)dst;                /* Start address of transfer destination */
    trans_info.count    = (uint32_t)count;              /* Total byte count to be transferred    */
#ifndef __USB_FUNCTION_DF_ACC_ENABLE__
    if (size == 0)
    {
        trans_info.src_size = DMAC_TRANS_SIZE_8;        /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_8;        /* Transfer destination transfer size */
    }
    else if (size == 1)
    {
        trans_info.src_size = DMAC_TRANS_SIZE_16;       /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_16;       /* Transfer destination transfer size */
    }
    else if (size == 2)
    {
        trans_info.src_size = DMAC_TRANS_SIZE_32;       /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_32;       /* Transfer destination transfer size */
    }
    else
    {
        printf("size error!!\n");
    }
#else
    if (dfacc == 2)
    {
        /* 32byte access */
        trans_info.src_size = DMAC_TRANS_SIZE_256;      /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_256;      /* Transfer destination transfer size */
    }
    else if (dfacc == 1)
    {
        /* 16byte access */
        trans_info.src_size = DMAC_TRANS_SIZE_128;      /* Transfer source transfer size      */
        trans_info.dst_size = DMAC_TRANS_SIZE_128;      /* Transfer destination transfer size */
    }
    else
    {
        /* normal access */
        if (size == 0)
        {
            trans_info.src_size = DMAC_TRANS_SIZE_8;    /* Transfer source transfer size      */
            trans_info.dst_size = DMAC_TRANS_SIZE_8;    /* Transfer destination transfer size */
        }
        else if (size == 1)
        {
            trans_info.src_size = DMAC_TRANS_SIZE_16;   /* Transfer source transfer size      */
            trans_info.dst_size = DMAC_TRANS_SIZE_16;   /* Transfer destination transfer size */
        }
        else if (size == 2)
        {
            trans_info.src_size = DMAC_TRANS_SIZE_32;   /* Transfer source transfer size      */
            trans_info.dst_size = DMAC_TRANS_SIZE_32;   /* Transfer destination transfer size */
        }
        else
        {
            printf("size error!!\n");
        }
    }
#endif

    if (dir == USB_FUNCTION_FIFO2BUF)
    {
        request_factor =DMAC_REQ_USB0_DMA1_RX;          /* USB_0 channel 0 receive FIFO full               */
        trans_info.saddr_dir = DMAC_TRANS_ADR_NO_INC;   /* Count direction of transfer source address      */
        trans_info.daddr_dir = DMAC_TRANS_ADR_INC;      /* Count direction of transfer destination address */
    }
    else if (dir == USB_FUNCTION_BUF2FIFO)
    {
        request_factor =DMAC_REQ_USB0_DMA1_TX;          /* USB_0 channel 0 receive FIFO empty              */
        trans_info.saddr_dir = DMAC_TRANS_ADR_INC;      /* Count direction of transfer source address      */
        trans_info.daddr_dir = DMAC_TRANS_ADR_NO_INC;   /* Count direction of transfer destination address */
    }
    else
    {
        /* Do Nothing */
    }

    /* ==== DMAC initialization ==== */
    usb0_function_DMAC2_PeriReqInit((const dmac_transinfo_t *)&trans_info,
                                    DMAC_MODE_REGISTER,
                                    DMAC_SAMPLE_SINGLE,
                                    request_factor,
                                    0);     /* Don't care DMAC_REQ_REQD is setting in
                                            usb0_function_DMAC1_PeriReqInit() */

    /* ==== DMAC startup ==== */
    ret = usb0_function_DMAC2_Open(DMAC_REQ_MODE_PERI);
    if (ret != 0)
    {
        printf("DMAC2 Open error!!\n");
    }

    return;
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_stop_dma0
* Description  : Disables DMA transfer.
*              : This function should be executed to DMAC executed at the time
*              : of specification of D0_FIF0_DMA in dma->fifo.
* Arguments    : none
* Return Value : uint32_t return Transfer Counter register(DMATCRn) value
*              : regarding to the bus width.
*******************************************************************************/
uint32_t Userdef_USB_usb0_function_stop_dma0 (void)
{
    uint32_t remain;

    /* ==== DMAC release ==== */
    usb0_function_DMAC1_Close(&remain);

    return remain;
}

/*******************************************************************************
* Function Name: Userdef_USB_usb0_function_stop_dma1
* Description  : Disables DMA transfer.
*              : This function should be executed to DMAC executed at the time
*              : of specification of D1_FIF0_DMA in dma->fifo.
* Arguments    : none
* Return Value : uint32_t return Transfer Counter register(DMATCRn) value
*              : regarding to the bus width.
*******************************************************************************/
uint32_t Userdef_USB_usb0_function_stop_dma1 (void)
{
    uint32_t remain;

    /* ==== DMAC release ==== */
    usb0_function_DMAC2_Close(&remain);

    return remain;
}

/* End of File */
