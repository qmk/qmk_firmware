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
/**************************************************************************//**
* @file         RZ_A1_Init.c
* $Rev: 624 $
* $Date:: 2013-04-24 13:37:48 +0900#$
* @brief        RZ_A1 Initialize
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "MBRZA1H.h"
#include "RZ_A1_Init.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#define CS2_SDRAM_MODE_16BIT_CAS2_BR_BW (*(volatile uint16_t*)0x3FFFD040)
#define CS3_SDRAM_MODE_16BIT_CAS2_BR_BW (*(volatile uint16_t*)0x3FFFE040)

#define GPIO_PORT0_BOOTMODE_BITMASK (0x000fu)

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/**************************************************************************//**
* Function Name: RZ_A1_SetSramWriteEnable
* @brief         Initialize Board settings
*
*                Description:<br>
*                Set SRAM write enable
* @param         none
* @retval        none
******************************************************************************/
void RZ_A1_SetSramWriteEnable(void)
{
    /* Enable SRAM write access */
    CPG.SYSCR3 = 0x0F;

    return;
}

/**************************************************************************//**
* Function Name: RZ_A1_InitClock
* @brief         Initialize Board settings
*
*                Description:<br>
*                Initialize Clock
* @param         none
* @retval        none
******************************************************************************/
void RZ_A1_InitClock(void)
{
    /* Cancel L2C standby status before clock change */
    L2CREG15_POWER_CTRL = 0x00000001;

    /* Clock settings */
    /* ClockMode0 */
    CPG.FRQCR  = 0x1035;    /* CPU Clock =399.99MHz */
    CPG.FRQCR2 = 0x0001;    /* G Clock   =266.66MHz */

    return;
}

/**************************************************************************//**
* Function Name: RZ_A1_IsClockMode0
* @brief         Query Clock Mode
*
*                Description:<br>
*                Answer ClockMode0 or not
* @param         none
* @retval        true  : clock mode 0
* @retval        false : clock mode 1
******************************************************************************/
int RZ_A1_IsClockMode0(void)
{
    /* ClockMode0 */
    return true;
}

/**************************************************************************//**
* Function Name: RZ_A1_InitBus
* @brief         Initialize Bus
*
*                Description:<br>
*                Initialize Pin Setting
* @param         none
* @retval        none
******************************************************************************/
void RZ_A1_InitBus(void)
{
    /*************************************************************************/
    /* If need Pin Setting before run program, the setting will be wrote here*/
    /*************************************************************************/

    return;
}

/******************************************************************************
End of file
******************************************************************************/
