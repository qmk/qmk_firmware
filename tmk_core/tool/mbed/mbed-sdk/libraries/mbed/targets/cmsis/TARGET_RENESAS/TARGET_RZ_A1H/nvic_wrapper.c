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
* Copyright (C) 2012 - 2015 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/**************************************************************************//**
* @file         nvic_wrapper.c
* $Rev:  $
* $Date:: $
* @brief        Wrapper between NVIC(for Cortex-M) and GIC(for Cortex-A9)
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "MBRZA1H.h"
#include "wdt_iodefine.h"
#include "nvic_wrapper.h"
#include "gic.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#define PRIO_BITS            (7)   /* Set binary point to 0 in gic.c */
#define WDT_WTCNT_WRITE      (0x5A00)
#define WDT_WTCSR_WRITE      (0xA500)
#define WDT_WRCSR_WOVF_WRITE (0xA500)
#define WDT_WRCSR_RSTE_WRITE (0x5A00)

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/



/* ##########################   NVIC functions  #################################### */
void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    GIC_SetBinaryPoint(PriorityGroup);
}


uint32_t NVIC_GetPriorityGrouping(void)
{
    return GIC_GetBinaryPoint(0);
}


void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    GIC_EnableIRQ(IRQn);
}


void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    GIC_DisableIRQ(IRQn);
}


uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    uint32_t pending;
    
    pending = GIC_GetIRQStatus(IRQn);
    pending = (pending & 0x00000001);
    
    return pending;
}


void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    GIC_SetPendingIRQ(IRQn);
}


void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    GIC_ClearPendingIRQ(IRQn);
}


uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
    uint32_t active;
    
    active = GIC_GetIRQStatus(IRQn);
    active = ((active >> 1) & 0x00000001);
    
    return active;
}


void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    GIC_SetPriority(IRQn, (priority << 3));
}


uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{
    uint32_t priority_field;
    
    priority_field = GIC_GetPriority(IRQn);
    priority_field = (priority_field >> 3);
    return priority_field;
}


uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
    uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);          /* only values 0..7 are used          */
    uint32_t PreemptPriorityBits;
    uint32_t SubPriorityBits;

    PreemptPriorityBits = ((7 - PriorityGroupTmp) > PRIO_BITS) ? PRIO_BITS : 7 - PriorityGroupTmp;
    SubPriorityBits     = ((PriorityGroupTmp + PRIO_BITS) < 7) ? 0 : PriorityGroupTmp - 7 + PRIO_BITS;

    return (
             ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
             ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
           );
}


void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
    uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);          /* only values 0..7 are used          */
    uint32_t PreemptPriorityBits;
    uint32_t SubPriorityBits;

    PreemptPriorityBits = ((7 - PriorityGroupTmp) > PRIO_BITS) ? PRIO_BITS : 7 - PriorityGroupTmp;
    SubPriorityBits     = ((PriorityGroupTmp + PRIO_BITS) < 7) ? 0 : PriorityGroupTmp - 7 + PRIO_BITS;

    *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
    *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}

void NVIC_SystemReset(void)
{
    uint16_t reg;
    uint8_t  dummy_read;
    /* Use Watch Dog Timer to system reset */
    
    /* Set WT/IT bit of WTCSR to 1 = Watch Dog */
    /* CLK = 000, 1xP0phi(=33.3333MHz) = 7.7us */
    reg = (WDT_WTCSR_WRITE | 0x0058);
    WDTWTCSR = reg;
    
    /* Clear Count reg */
    reg = (WDT_WTCNT_WRITE | 0x0000);
    WDTWTCNT = reg;
    
    /* Clear WOVF flag */
    dummy_read = WDTWRCSR;
    reg = (WDT_WRCSR_WOVF_WRITE | (dummy_read & 0x0000));
    WDTWRCSR = reg;
    /* Enable Internal Reset */
    reg = (WDT_WRCSR_RSTE_WRITE | 0x005F);
    WDTWRCSR = reg;
    
    /* Watch Dog start */
    reg = (WDT_WTCSR_WRITE | 0x0078);
    WDTWTCSR = reg;
    
    while(1);                      /* wait Internal Reset */
}

/* ##################################    SysTick function  ############################################ */
uint32_t SysTick_Config(uint32_t ticks)
{
    /* Not support this function */
    /* Use mbed Ticker */
    return (1);     /* impossible */
}


/* ##################################### Debug In/Output function ########################################### */
uint32_t ITM_SendChar (uint32_t ch)
{
    /* Not support this function */
    /* Use mbed Serial */
    return (ch);
}


int32_t ITM_ReceiveChar (void) {
    /* Not support this function */
    /* Use mbed Serial */
    return (-1);    /* no character available */
}


int32_t ITM_CheckChar (void) {
    /* Not support this function */
    /* Use mbed Serial */
    return (0);                                 /* no character available */
}

