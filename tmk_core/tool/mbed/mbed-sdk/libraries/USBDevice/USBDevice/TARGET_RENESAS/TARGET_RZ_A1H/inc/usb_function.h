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
* File Name    : usb_function.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB_FUNCTION_H
#define USB_FUNCTION_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_typedefs.h"
#include "iodefine.h"
#include "rza_io_regrw.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define USB_FUNCTION_ALT_NO         (255)
#define USB_FUNCTION_ALT_SET        (0xff)

#define USB_FUNCTION_BITUPLLE       (0x0002u)
#define USB_FUNCTION_BITUCKSEL      (0x0004u)
#define USB_FUNCTION_BITBWAIT       (0x003fu)

#define USB_FUNCTION_BUSWAIT_02     (0x0000u)
#define USB_FUNCTION_BUSWAIT_03     (0x0001u)
#define USB_FUNCTION_BUSWAIT_04     (0x0002u)
#define USB_FUNCTION_BUSWAIT_05     (0x0003u)
#define USB_FUNCTION_BUSWAIT_06     (0x0004u)
#define USB_FUNCTION_BUSWAIT_07     (0x0005u)
#define USB_FUNCTION_BUSWAIT_08     (0x0006u)
#define USB_FUNCTION_BUSWAIT_09     (0x0007u)
#define USB_FUNCTION_BUSWAIT_10     (0x0008u)
#define USB_FUNCTION_BUSWAIT_11     (0x0009u)
#define USB_FUNCTION_BUSWAIT_12     (0x000au)
#define USB_FUNCTION_BUSWAIT_13     (0x000bu)
#define USB_FUNCTION_BUSWAIT_14     (0x000cu)
#define USB_FUNCTION_BUSWAIT_15     (0x000du)
#define USB_FUNCTION_BUSWAIT_16     (0x000eu)
#define USB_FUNCTION_BUSWAIT_17     (0x000fu)

#define USB_FUNCTION_BITRESUME      (0x0020u)
#define USB_FUNCTION_BITUACT        (0x0010u)
#define USB_FUNCTION_HSPROC         (0x0004u)
#define USB_FUNCTION_HSMODE         (0x0003u)
#define USB_FUNCTION_FSMODE         (0x0002u)
#define USB_FUNCTION_LSMODE         (0x0001u)
#define USB_FUNCTION_UNDECID        (0x0000u)

#define USB_FUNCTION_BITRCNT        (0x8000u)
#define USB_FUNCTION_BITDREQE       (0x1000u)
#define USB_FUNCTION_BITMBW         (0x0c00u)
#define USB_FUNCTION_BITMBW_8       (0x0000u)
#define USB_FUNCTION_BITMBW_16      (0x0400u)
#define USB_FUNCTION_BITMBW_32      (0x0800u)
#define USB_FUNCTION_BITBYTE_LITTLE (0x0000u)
#define USB_FUNCTION_BITBYTE_BIG    (0x0100u)
#define USB_FUNCTION_BITISEL        (0x0020u)
#define USB_FUNCTION_BITCURPIPE     (0x000fu)

#define USB_FUNCTION_CFIFO_READ     (0x0000u)
#define USB_FUNCTION_CFIFO_WRITE    (0x0020u)

#define USB_FUNCTION_BITBVAL        (0x8000u)
#define USB_FUNCTION_BITBCLR        (0x4000u)
#define USB_FUNCTION_BITFRDY        (0x2000u)
#define USB_FUNCTION_BITDTLN        (0x0fffu)

#define USB_FUNCTION_BITVBSE        (0x8000u)
#define USB_FUNCTION_BITRSME        (0x4000u)
#define USB_FUNCTION_BITSOFE        (0x2000u)
#define USB_FUNCTION_BITDVSE        (0x1000u)
#define USB_FUNCTION_BITCTRE        (0x0800u)
#define USB_FUNCTION_BITVBINT       (0x8000u)
#define USB_FUNCTION_BITRESM        (0x4000u)
#define USB_FUNCTION_BITSOFR        (0x2000u)
#define USB_FUNCTION_BITDVST        (0x1000u)
#define USB_FUNCTION_BITCTRT        (0x0800u)

#define USB_FUNCTION_BITBEMPE       (0x0400u)
#define USB_FUNCTION_BITNRDYE       (0x0200u)
#define USB_FUNCTION_BITBRDYE       (0x0100u)
#define USB_FUNCTION_BITBEMP        (0x0400u)
#define USB_FUNCTION_BITNRDY        (0x0200u)
#define USB_FUNCTION_BITBRDY        (0x0100u)

#define USB_FUNCTION_BITDVSQ        (0x0070u)
#define USB_FUNCTION_BITDVSQS       (0x0030u)
#define USB_FUNCTION_DS_SPD_CNFG    (0x0070u)
#define USB_FUNCTION_DS_SPD_ADDR    (0x0060u)
#define USB_FUNCTION_DS_SPD_DFLT    (0x0050u)
#define USB_FUNCTION_DS_SPD_POWR    (0x0040u)
#define USB_FUNCTION_DS_CNFG        (0x0030u)
#define USB_FUNCTION_DS_ADDS        (0x0020u)
#define USB_FUNCTION_DS_DFLT        (0x0010u)
#define USB_FUNCTION_DS_POWR        (0x0000u)
#define USB_FUNCTION_BITVALID       (0x0008u)
#define USB_FUNCTION_BITCTSQ        (0x0007u)
#define USB_FUNCTION_CS_SQER        (0x0006u)
#define USB_FUNCTION_CS_WRND        (0x0005u)
#define USB_FUNCTION_CS_WRSS        (0x0004u)
#define USB_FUNCTION_CS_WRDS        (0x0003u)
#define USB_FUNCTION_CS_RDSS        (0x0002u)
#define USB_FUNCTION_CS_RDDS        (0x0001u)
#define USB_FUNCTION_CS_IDST        (0x0000u)

#define USB_FUNCTION_PIPExBUF       (64u)

#define USB_FUNCTION_D0FIFO         (0)
#define USB_FUNCTION_D1FIFO         (1)
#define USB_FUNCTION_DMA_READY      (0)
#define USB_FUNCTION_DMA_BUSY       (1)
#define USB_FUNCTION_DMA_BUSYEND    (2)

#define USB_FUNCTION_FIFO_USE       (0x7000)

#endif /* USB_FUNCTION_FUNCTION_H */

/* End of File */
