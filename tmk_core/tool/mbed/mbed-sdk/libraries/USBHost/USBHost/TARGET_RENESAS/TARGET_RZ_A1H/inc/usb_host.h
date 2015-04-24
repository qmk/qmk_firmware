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
* File Name    : usb_host.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description  : RZ/A1H R7S72100 USB Sample Program
*******************************************************************************/
#ifndef USB_HOST_H
#define USB_HOST_H


/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_typedefs.h"
#include "iodefine.h"
#include "rza_io_regrw.h"


/*******************************************************************************
Typedef definitions
*******************************************************************************/


/*******************************************************************************
Macro definitions
*******************************************************************************/
#define USB_HOST_DEVICE_0               (0u)
#define USB_HOST_DEVICE_1               (1u)
#define USB_HOST_DEVICE_2               (2u)
#define USB_HOST_DEVICE_3               (3u)
#define USB_HOST_DEVICE_4               (4u)
#define USB_HOST_DEVICE_5               (5u)
#define USB_HOST_DEVICE_6               (6u)
#define USB_HOST_DEVICE_7               (7u)
#define USB_HOST_DEVICE_8               (8u)
#define USB_HOST_DEVICE_9               (9u)
#define USB_HOST_DEVICE_10              (10u)

#define USB_HOST_ENDPOINT_DESC          (0x05)

#define USB_HOST_BITUPLLE               (0x0002u)
#define USB_HOST_BITUCKSEL              (0x0004u)
#define USB_HOST_BITBWAIT               (0x003fu)

#define USB_HOST_BUSWAIT_02             (0x0000u)
#define USB_HOST_BUSWAIT_03             (0x0001u)
#define USB_HOST_BUSWAIT_04             (0x0002u)
#define USB_HOST_BUSWAIT_05             (0x0003u)
#define USB_HOST_BUSWAIT_06             (0x0004u)
#define USB_HOST_BUSWAIT_07             (0x0005u)
#define USB_HOST_BUSWAIT_08             (0x0006u)
#define USB_HOST_BUSWAIT_09             (0x0007u)
#define USB_HOST_BUSWAIT_10             (0x0008u)
#define USB_HOST_BUSWAIT_11             (0x0009u)
#define USB_HOST_BUSWAIT_12             (0x000au)
#define USB_HOST_BUSWAIT_13             (0x000bu)
#define USB_HOST_BUSWAIT_14             (0x000cu)
#define USB_HOST_BUSWAIT_15             (0x000du)
#define USB_HOST_BUSWAIT_16             (0x000eu)
#define USB_HOST_BUSWAIT_17             (0x000fu)

#define USB_HOST_FS_JSTS                (0x0001u)
#define USB_HOST_LS_JSTS                (0x0002u)

#define USB_HOST_BITRST                 (0x0040u)
#define USB_HOST_BITRESUME              (0x0020u)
#define USB_HOST_BITUACT                (0x0010u)
#define USB_HOST_HSPROC                 (0x0004u)
#define USB_HOST_HSMODE                 (0x0003u)
#define USB_HOST_FSMODE                 (0x0002u)
#define USB_HOST_LSMODE                 (0x0001u)
#define USB_HOST_UNDECID                (0x0000u)

#define USB_HOST_BITRCNT                (0x8000u)
#define USB_HOST_BITDREQE               (0x1000u)
#define USB_HOST_BITMBW                 (0x0c00u)
#define USB_HOST_BITMBW_8               (0x0000u)
#define USB_HOST_BITMBW_16              (0x0400u)
#define USB_HOST_BITMBW_32              (0x0800u)
#define USB_HOST_BITBYTE_LITTLE         (0x0000u)
#define USB_HOST_BITBYTE_BIG            (0x0100u)
#define USB_HOST_BITISEL                (0x0020u)
#define USB_HOST_BITCURPIPE             (0x000fu)

#define USB_HOST_CFIFO_READ             (0x0000u)
#define USB_HOST_CFIFO_WRITE            (0x0020u)

#define USB_HOST_BITBVAL                (0x8000u)
#define USB_HOST_BITBCLR                (0x4000u)
#define USB_HOST_BITFRDY                (0x2000u)
#define USB_HOST_BITDTLN                (0x0fffu)

#define USB_HOST_BITBEMPE               (0x0400u)
#define USB_HOST_BITNRDYE               (0x0200u)
#define USB_HOST_BITBRDYE               (0x0100u)
#define USB_HOST_BITBEMP                (0x0400u)
#define USB_HOST_BITNRDY                (0x0200u)
#define USB_HOST_BITBRDY                (0x0100u)

#define USB_HOST_BITBCHGE               (0x4000u)
#define USB_HOST_BITDTCHE               (0x1000u)
#define USB_HOST_BITATTCHE              (0x0800u)
#define USB_HOST_BITEOFERRE             (0x0040u)
#define USB_HOST_BITBCHG                (0x4000u)
#define USB_HOST_BITDTCH                (0x1000u)
#define USB_HOST_BITATTCH               (0x0800u)
#define USB_HOST_BITEOFERR              (0x0040u)

#define USB_HOST_BITSIGNE               (0x0020u)
#define USB_HOST_BITSACKE               (0x0010u)
#define USB_HOST_BITSIGN                (0x0020u)
#define USB_HOST_BITSACK                (0x0010u)

#define USB_HOST_BITSUREQ               (0x4000u)
#define USB_HOST_BITSQSET               (0x0080u)
#define USB_HOST_PID_STALL2             (0x0003u)
#define USB_HOST_PID_STALL              (0x0002u)
#define USB_HOST_PID_BUF                (0x0001u)
#define USB_HOST_PID_NAK                (0x0000u)

#define USB_HOST_PIPExBUF               (64u)

#define USB_HOST_D0FIFO                 (0)
#define USB_HOST_D1FIFO                 (1)
#define USB_HOST_DMA_READY              (0)
#define USB_HOST_DMA_BUSY               (1)
#define USB_HOST_DMA_BUSYEND            (2)

#define USB_HOST_FIFO_USE               (0x7000)

#define USB_HOST_FIFOERROR              (0xffff)
#define USB_HOST_WRITEEND               (0)
#define USB_HOST_WRITESHRT              (1)
#define USB_HOST_WRITING                (2)
#define USB_HOST_WRITEDMA               (3)
#define USB_HOST_READEND                (0)
#define USB_HOST_READSHRT               (1)
#define USB_HOST_READING                (2)
#define USB_HOST_READOVER               (3)
#define USB_HOST_READZERO               (4)

#define USB_HOST_CMD_IDLE               (0x0000)
#define USB_HOST_CMD_DOING              (0x0001)
#define USB_HOST_CMD_DONE               (0x0002)
#define USB_HOST_CMD_NORES              (0x0003)
#define USB_HOST_CMD_STALL              (0x0004)
#define USB_HOST_CMD_FIELD              (0x000f)

#if 0
#define USB_HOST_CHG_CMDFIELD( r, v )   do { r &= ( ~USB_HOST_CMD_FIELD );  \
                                         r |= v;                } while(0)
#endif

#define USB_HOST_MODE_WRITE             (0x0100)
#define USB_HOST_MODE_READ              (0x0200)
#define USB_HOST_MODE_NO_DATA           (0x0300)
#define USB_HOST_MODE_FIELD             (0x0f00)

#define USB_HOST_STAGE_SETUP            (0x0010)
#define USB_HOST_STAGE_DATA             (0x0020)
#define USB_HOST_STAGE_STATUS           (0x0030)
#define USB_HOST_STAGE_FIELD            (0x00f0)

#if 0
#define USB_HOST_CHG_STAGEFIELD( r, v ) do { r &= ( ~USB_HOST_STAGE_FIELD );    \
                                         r |= v;                } while(0)
#endif

#define USB_HOST_DEVADD_MASK            (0x7fc0)


/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
extern uint16_t g_usb_host_elt_clockmode;

#endif /* USB_HOST_H */

/* End of File */
