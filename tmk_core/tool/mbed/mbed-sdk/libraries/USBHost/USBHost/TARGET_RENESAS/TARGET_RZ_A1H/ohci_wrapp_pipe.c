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
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "devdrv_usb_host_api.h"


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


/********************************************************************************************************/
/* Endpoint Configuration Data Format                                                                   */
/********************************************************************************************************/
/*  LINE1: Pipe Window Select Register                                                                  */
/*      CPU Access PIPE                 : PIPE1 to PIPE9                        [ ### SET ### ]         */
/*  LINE2: Pipe Configuration Register                                                                  */
/*      Transfer Type                   : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*      Buffer Ready interrupt          : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*      Double Buffer Mode              : USB_HOST_CNT_ON / USB_HOST_CNT_OFF    [ ### SET ### ]         */
/*      Continuous Transmit:            : USB_HOST_CNT_ON / USB_HOST_CNT_OFF    [ ### SET ### ]         */
/*      Short NAK                       : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*      Transfer Direction              : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*      Endpoint Number                 : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*  LINE3: Pipe Buffer Configuration Register                                                           */
/*      Buffer Size                     : (uint16_t)((uint16_t)(((x) / 64) - 1) << 10)                  */
/*                                                                              [ ### SET ### ]         */
/*      Buffer Top Number               : (uint16_t)(x)                         [ ### SET ### ]         */
/*  LINE4: Pipe Maxpacket Size Register                                                                 */
/*      Max Packet Size                 : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*  LINE5: Pipe Cycle Configuration Register (0x6C)                                                     */
/*      ISO Buffer Flush Mode           : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*      ISO Interval Value              : USB_HOST_NONE                         [ USB_HOST_NONE    ]    */
/*  LINE6: use FIFO port                                                                                */
/*                                      : USB_HOST_CUSE                         [ ### SET ### ]         */
/*                                      : USB_HOST_D0USE / USB_HOST_D1USE                               */
/*                                      : USB_HOST_D0DMA    / USB_HOST_D0DMA                            */
/*  LINE7: use FIFO port Endian         : USB_HOST_FIFO_BIG / USB_HOST_FIFO_LITTLE [ #SET# ]            */
/********************************************************************************************************/

/* Device Address 1 */
USB_HOST_CFG_PIPETBL_t     usb_host_blk_ep_tbl1[ ] =
{
    {
        USB_HOST_PIPE3,
        /* TYPE       / BFRE           / DBLB            / CNTMD            / SHTNAK        / DIR           / EPNUM */
        USB_HOST_NONE | USB_HOST_NONE  | USB_HOST_DBLBON | USB_HOST_CNTMDON | USB_HOST_NONE | USB_HOST_NONE | USB_HOST_NONE,
        (uint16_t)((uint16_t)(((1024) / 64) - 1) << 10) | (uint16_t)(8),
        USB_HOST_NONE,
        USB_HOST_NONE,
        USB_HOST_D0USE
    },

    {
        /* Pipe end */
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF
    }
};

USB_HOST_CFG_PIPETBL_t     usb_host_int_ep_tbl1[ ] =
{
    {
        USB_HOST_PIPE6,
        /* TYPE       / BFRE           / DBLB            / CNTMD            / SHTNAK        / DIR           / EPNUM */
        USB_HOST_NONE | USB_HOST_NONE  | USB_HOST_DBLBON | USB_HOST_CNTMDON | USB_HOST_NONE | USB_HOST_NONE | USB_HOST_NONE,
        (uint16_t)((uint16_t)(((64) / 64) - 1) << 10) | (uint16_t)(40),
        USB_HOST_NONE,
        USB_HOST_NONE,
        USB_HOST_D1USE
    },

    {
        USB_HOST_PIPE7,
        /* TYPE       / BFRE           / DBLB            / CNTMD            / SHTNAK        / DIR           / EPNUM */
        USB_HOST_NONE | USB_HOST_NONE  | USB_HOST_DBLBON | USB_HOST_CNTMDON | USB_HOST_NONE | USB_HOST_NONE | USB_HOST_NONE,
        (uint16_t)((uint16_t)(((64) / 64) - 1) << 10) | (uint16_t)(41),
        USB_HOST_NONE,
        USB_HOST_NONE,
        USB_HOST_D1USE
    },

    {
        USB_HOST_PIPE8,
        /* TYPE       / BFRE           / DBLB            / CNTMD            / SHTNAK        / DIR           / EPNUM */
        USB_HOST_NONE | USB_HOST_NONE  | USB_HOST_DBLBON | USB_HOST_CNTMDON | USB_HOST_NONE | USB_HOST_NONE | USB_HOST_NONE,
        (uint16_t)((uint16_t)(((64) / 64) - 1) << 10) | (uint16_t)(42),
        USB_HOST_NONE,
        USB_HOST_NONE,
        USB_HOST_D1USE
    },

    {
        USB_HOST_PIPE9,
        /* TYPE       / BFRE           / DBLB            / CNTMD            / SHTNAK        / DIR           / EPNUM */
        USB_HOST_NONE | USB_HOST_NONE  | USB_HOST_DBLBON | USB_HOST_CNTMDON | USB_HOST_NONE | USB_HOST_NONE | USB_HOST_NONE,
        (uint16_t)((uint16_t)(((64) / 64) - 1) << 10) | (uint16_t)(43),
        USB_HOST_NONE,
        USB_HOST_NONE,
        USB_HOST_D1USE
    },

    {
        /* Pipe end */
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF
    }
};

USB_HOST_CFG_PIPETBL_t     usb_host_iso_ep_tbl1[ ] =
{
    {
        USB_HOST_PIPE1,
        /* TYPE       / BFRE           / DBLB            / CNTMD            / SHTNAK        / DIR           / EPNUM */
        USB_HOST_NONE | USB_HOST_NONE  | USB_HOST_DBLBON | USB_HOST_CNTMDON | USB_HOST_NONE | USB_HOST_NONE | USB_HOST_NONE,
        (uint16_t)((uint16_t)(((1024) / 64) - 1) << 10) | (uint16_t)(44),
        USB_HOST_NONE,
        USB_HOST_NONE,
        USB_HOST_D1USE
    },

    {
        USB_HOST_PIPE2,
        /* TYPE       / BFRE           / DBLB            / CNTMD            / SHTNAK        / DIR           / EPNUM */
        USB_HOST_NONE | USB_HOST_NONE  | USB_HOST_DBLBON | USB_HOST_CNTMDON | USB_HOST_NONE | USB_HOST_NONE | USB_HOST_NONE,
        (uint16_t)((uint16_t)(((1024) / 64) - 1) << 10) | (uint16_t)(60),
        USB_HOST_NONE,
        USB_HOST_NONE,
        USB_HOST_D1USE
    },

    {
        /* Pipe end */
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF,
        0xFFFF
    }
};


/* End of File */
