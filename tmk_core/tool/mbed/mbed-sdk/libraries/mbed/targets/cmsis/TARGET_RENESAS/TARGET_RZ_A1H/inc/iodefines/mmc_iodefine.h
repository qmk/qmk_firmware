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
* http://www.renesas.com/disclaimer*
* Copyright (C) 2013-2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name : mmc_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef MMC_IODEFINE_H
#define MMC_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_mmc
{                                                          /* MMC              */
    volatile uint16_t CE_CMD_SETH;                      /*  CE_CMD_SETH */
    volatile uint16_t CE_CMD_SETL;                      /*  CE_CMD_SETL */
    volatile uint8_t   dummy182[4];                            /*                  */
    volatile uint32_t  CE_ARG;                                 /*  CE_ARG          */
    volatile uint32_t  CE_ARG_CMD12;                           /*  CE_ARG_CMD12    */
    volatile uint32_t  CE_CMD_CTRL;                            /*  CE_CMD_CTRL     */
    volatile uint32_t  CE_BLOCK_SET;                           /*  CE_BLOCK_SET    */
    volatile uint32_t  CE_CLK_CTRL;                            /*  CE_CLK_CTRL     */
    volatile uint32_t  CE_BUF_ACC;                             /*  CE_BUF_ACC      */
#define MMC_CE_RESPn_COUNT 4
    volatile uint32_t  CE_RESP3;                               /*  CE_RESP3        */
    volatile uint32_t  CE_RESP2;                               /*  CE_RESP2        */
    volatile uint32_t  CE_RESP1;                               /*  CE_RESP1        */
    volatile uint32_t  CE_RESP0;                               /*  CE_RESP0        */
    volatile uint32_t  CE_RESP_CMD12;                          /*  CE_RESP_CMD12   */
    volatile uint32_t  CE_DATA;                                /*  CE_DATA         */
    volatile uint8_t   dummy183[8];                            /*                  */
    volatile uint32_t  CE_INT;                                 /*  CE_INT          */
    volatile uint32_t  CE_INT_EN;                              /*  CE_INT_EN       */
    volatile uint32_t  CE_HOST_STS1;                           /*  CE_HOST_STS1    */
    volatile uint32_t  CE_HOST_STS2;                           /*  CE_HOST_STS2    */
    volatile uint8_t   dummy184[12];                           /*                  */
    volatile uint32_t  CE_DMA_MODE;                            /*  CE_DMA_MODE     */
    volatile uint8_t   dummy185[16];                           /*                  */
    volatile uint32_t  CE_DETECT;                              /*  CE_DETECT       */
    volatile uint32_t  CE_ADD_MODE;                            /*  CE_ADD_MODE     */
    volatile uint8_t   dummy186[4];                            /*                  */
    volatile uint32_t  CE_VERSION;                             /*  CE_VERSION      */
};


#define MMC     (*(struct st_mmc     *)0xE804C800uL) /* MMC */


#define MMCCE_CMD_SETH MMC.CE_CMD_SETH
#define MMCCE_CMD_SETL MMC.CE_CMD_SETL
#define MMCCE_ARG MMC.CE_ARG
#define MMCCE_ARG_CMD12 MMC.CE_ARG_CMD12
#define MMCCE_CMD_CTRL MMC.CE_CMD_CTRL
#define MMCCE_BLOCK_SET MMC.CE_BLOCK_SET
#define MMCCE_CLK_CTRL MMC.CE_CLK_CTRL
#define MMCCE_BUF_ACC MMC.CE_BUF_ACC
#define MMCCE_RESP3 MMC.CE_RESP3
#define MMCCE_RESP2 MMC.CE_RESP2
#define MMCCE_RESP1 MMC.CE_RESP1
#define MMCCE_RESP0 MMC.CE_RESP0
#define MMCCE_RESP_CMD12 MMC.CE_RESP_CMD12
#define MMCCE_DATA MMC.CE_DATA
#define MMCCE_INT MMC.CE_INT
#define MMCCE_INT_EN MMC.CE_INT_EN
#define MMCCE_HOST_STS1 MMC.CE_HOST_STS1
#define MMCCE_HOST_STS2 MMC.CE_HOST_STS2
#define MMCCE_DMA_MODE MMC.CE_DMA_MODE
#define MMCCE_DETECT MMC.CE_DETECT
#define MMCCE_ADD_MODE MMC.CE_ADD_MODE
#define MMCCE_VERSION MMC.CE_VERSION
/* <-SEC M1.10.1 */
#endif
