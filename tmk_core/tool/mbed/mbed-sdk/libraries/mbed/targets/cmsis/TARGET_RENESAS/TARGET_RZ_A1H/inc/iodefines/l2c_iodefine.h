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
* File Name : l2c_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef L2C_IODEFINE_H
#define L2C_IODEFINE_H
/* ->SEC M1.10.1 : Not magic number */

struct st_l2c
{                                                          /* L2C              */
    volatile uint32_t  REG0_CACHE_ID;                          /*  REG0_CACHE_ID   */
    volatile uint32_t  REG0_CACHE_TYPE;                        /*  REG0_CACHE_TYPE */
    volatile uint8_t   dummy8[248];                            /*                  */
    volatile uint32_t  REG1_CONTROL;                           /*  REG1_CONTROL    */
    volatile uint32_t  REG1_AUX_CONTROL;                       /*  REG1_AUX_CONTROL */
    volatile uint32_t  REG1_TAG_RAM_CONTROL;                   /*  REG1_TAG_RAM_CONTROL */
    volatile uint32_t  REG1_DATA_RAM_CONTROL;                  /*  REG1_DATA_RAM_CONTROL */
    volatile uint8_t   dummy9[240];                            /*                  */
    volatile uint32_t  REG2_EV_COUNTER_CTRL;                   /*  REG2_EV_COUNTER_CTRL */
    volatile uint32_t  REG2_EV_COUNTER1_CFG;                   /*  REG2_EV_COUNTER1_CFG */
    volatile uint32_t  REG2_EV_COUNTER0_CFG;                   /*  REG2_EV_COUNTER0_CFG */
    volatile uint32_t  REG2_EV_COUNTER1;                       /*  REG2_EV_COUNTER1 */
    volatile uint32_t  REG2_EV_COUNTER0;                       /*  REG2_EV_COUNTER0 */
    volatile uint32_t  REG2_INT_MASK;                          /*  REG2_INT_MASK   */
    volatile uint32_t  REG2_INT_MASK_STATUS;                   /*  REG2_INT_MASK_STATUS */
    volatile uint32_t  REG2_INT_RAW_STATUS;                    /*  REG2_INT_RAW_STATUS */
    volatile uint32_t  REG2_INT_CLEAR;                         /*  REG2_INT_CLEAR  */
    volatile uint8_t   dummy10[1292];                          /*                  */
    volatile uint32_t  REG7_CACHE_SYNC;                        /*  REG7_CACHE_SYNC */
    volatile uint8_t   dummy11[60];                            /*                  */
    volatile uint32_t  REG7_INV_PA;                            /*  REG7_INV_PA     */
    volatile uint8_t   dummy12[8];                             /*                  */
    volatile uint32_t  REG7_INV_WAY;                           /*  REG7_INV_WAY    */
    volatile uint8_t   dummy13[48];                            /*                  */
    volatile uint32_t  REG7_CLEAN_PA;                          /*  REG7_CLEAN_PA   */
    volatile uint8_t   dummy14[4];                             /*                  */
    volatile uint32_t  REG7_CLEAN_INDEX;                       /*  REG7_CLEAN_INDEX */
    volatile uint32_t  REG7_CLEAN_WAY;                         /*  REG7_CLEAN_WAY  */
    volatile uint8_t   dummy15[48];                            /*                  */
    volatile uint32_t  REG7_CLEAN_INV_PA;                      /*  REG7_CLEAN_INV_PA */
    volatile uint8_t   dummy16[4];                             /*                  */
    volatile uint32_t  REG7_CLEAN_INV_INDEX;                   /*  REG7_CLEAN_INV_INDEX */
    volatile uint32_t  REG7_CLEAN_INV_WAY;                     /*  REG7_CLEAN_INV_WAY */
    volatile uint8_t   dummy17[256];                           /*                  */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN0;                       /*  REG9_D_LOCKDOWN0 */
    volatile uint32_t  REG9_I_LOCKDOWN0;                       /*  REG9_I_LOCKDOWN0 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN1;                       /*  REG9_D_LOCKDOWN1 */
    volatile uint32_t  REG9_I_LOCKDOWN1;                       /*  REG9_I_LOCKDOWN1 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN2;                       /*  REG9_D_LOCKDOWN2 */
    volatile uint32_t  REG9_I_LOCKDOWN2;                       /*  REG9_I_LOCKDOWN2 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN3;                       /*  REG9_D_LOCKDOWN3 */
    volatile uint32_t  REG9_I_LOCKDOWN3;                       /*  REG9_I_LOCKDOWN3 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN4;                       /*  REG9_D_LOCKDOWN4 */
    volatile uint32_t  REG9_I_LOCKDOWN4;                       /*  REG9_I_LOCKDOWN4 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN5;                       /*  REG9_D_LOCKDOWN5 */
    volatile uint32_t  REG9_I_LOCKDOWN5;                       /*  REG9_I_LOCKDOWN5 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN6;                       /*  REG9_D_LOCKDOWN6 */
    volatile uint32_t  REG9_I_LOCKDOWN6;                       /*  REG9_I_LOCKDOWN6 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
/* start of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint32_t  REG9_D_LOCKDOWN7;                       /*  REG9_D_LOCKDOWN7 */
    volatile uint32_t  REG9_I_LOCKDOWN7;                       /*  REG9_I_LOCKDOWN7 */
/* end of struct st_l2c_from_reg9_d_lockdown0 */
    volatile uint8_t   dummy18[16];                            /*                  */
    volatile uint32_t  REG9_LOCK_LINE_EN;                      /*  REG9_LOCK_LINE_EN */
    volatile uint32_t  REG9_UNLOCK_WAY;                        /*  REG9_UNLOCK_WAY */
    volatile uint8_t   dummy19[680];                           /*                  */
    volatile uint32_t  REG12_ADDR_FILTERING_START;             /*  REG12_ADDR_FILTERING_START */
    volatile uint32_t  REG12_ADDR_FILTERING_END;               /*  REG12_ADDR_FILTERING_END */
    volatile uint8_t   dummy20[824];                           /*                  */
    volatile uint32_t  REG15_DEBUG_CTRL;                       /*  REG15_DEBUG_CTRL */
    volatile uint8_t   dummy21[28];                            /*                  */
    volatile uint32_t  REG15_PREFETCH_CTRL;                    /*  REG15_PREFETCH_CTRL */
    volatile uint8_t   dummy22[28];                            /*                  */
    volatile uint32_t  REG15_POWER_CTRL;                       /*  REG15_POWER_CTRL */
};


struct st_l2c_from_reg9_d_lockdown0
{
    volatile uint32_t  REG9_D_LOCKDOWN0;                       /*  REG9_D_LOCKDOWN0 */
    volatile uint32_t  REG9_I_LOCKDOWN0;                       /*  REG9_I_LOCKDOWN0 */
};


#define L2C     (*(struct st_l2c     *)0x3FFFF000uL) /* L2C */


/* Start of channnel array defines of L2C */

/* Channnel array defines of L2C_FROM_REG9_D_LOCKDOWN0_ARRAY */
/*(Sample) value = L2C_FROM_REG9_D_LOCKDOWN0_ARRAY[ channel ]->REG9_D_LOCKDOWN0; */
#define L2C_FROM_REG9_D_LOCKDOWN0_ARRAY_COUNT  8
#define L2C_FROM_REG9_D_LOCKDOWN0_ARRAY_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &L2C_FROM_REG9_D_LOCKDOWN0, &L2C_FROM_REG9_D_LOCKDOWN1, &L2C_FROM_REG9_D_LOCKDOWN2, &L2C_FROM_REG9_D_LOCKDOWN3, &L2C_FROM_REG9_D_LOCKDOWN4, &L2C_FROM_REG9_D_LOCKDOWN5, &L2C_FROM_REG9_D_LOCKDOWN6, &L2C_FROM_REG9_D_LOCKDOWN7 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */
#define L2C_FROM_REG9_D_LOCKDOWN0 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN0) /* L2C_FROM_REG9_D_LOCKDOWN0 */
#define L2C_FROM_REG9_D_LOCKDOWN1 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN1) /* L2C_FROM_REG9_D_LOCKDOWN1 */
#define L2C_FROM_REG9_D_LOCKDOWN2 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN2) /* L2C_FROM_REG9_D_LOCKDOWN2 */
#define L2C_FROM_REG9_D_LOCKDOWN3 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN3) /* L2C_FROM_REG9_D_LOCKDOWN3 */
#define L2C_FROM_REG9_D_LOCKDOWN4 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN4) /* L2C_FROM_REG9_D_LOCKDOWN4 */
#define L2C_FROM_REG9_D_LOCKDOWN5 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN5) /* L2C_FROM_REG9_D_LOCKDOWN5 */
#define L2C_FROM_REG9_D_LOCKDOWN6 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN6) /* L2C_FROM_REG9_D_LOCKDOWN6 */
#define L2C_FROM_REG9_D_LOCKDOWN7 (*(struct st_l2c_from_reg9_d_lockdown0 *)&L2C.REG9_D_LOCKDOWN7) /* L2C_FROM_REG9_D_LOCKDOWN7 */

/* End of channnel array defines of L2C */


#define L2CREG0_CACHE_ID L2C.REG0_CACHE_ID
#define L2CREG0_CACHE_TYPE L2C.REG0_CACHE_TYPE
#define L2CREG1_CONTROL L2C.REG1_CONTROL
#define L2CREG1_AUX_CONTROL L2C.REG1_AUX_CONTROL
#define L2CREG1_TAG_RAM_CONTROL L2C.REG1_TAG_RAM_CONTROL
#define L2CREG1_DATA_RAM_CONTROL L2C.REG1_DATA_RAM_CONTROL
#define L2CREG2_EV_COUNTER_CTRL L2C.REG2_EV_COUNTER_CTRL
#define L2CREG2_EV_COUNTER1_CFG L2C.REG2_EV_COUNTER1_CFG
#define L2CREG2_EV_COUNTER0_CFG L2C.REG2_EV_COUNTER0_CFG
#define L2CREG2_EV_COUNTER1 L2C.REG2_EV_COUNTER1
#define L2CREG2_EV_COUNTER0 L2C.REG2_EV_COUNTER0
#define L2CREG2_INT_MASK L2C.REG2_INT_MASK
#define L2CREG2_INT_MASK_STATUS L2C.REG2_INT_MASK_STATUS
#define L2CREG2_INT_RAW_STATUS L2C.REG2_INT_RAW_STATUS
#define L2CREG2_INT_CLEAR L2C.REG2_INT_CLEAR
#define L2CREG7_CACHE_SYNC L2C.REG7_CACHE_SYNC
#define L2CREG7_INV_PA L2C.REG7_INV_PA
#define L2CREG7_INV_WAY L2C.REG7_INV_WAY
#define L2CREG7_CLEAN_PA L2C.REG7_CLEAN_PA
#define L2CREG7_CLEAN_INDEX L2C.REG7_CLEAN_INDEX
#define L2CREG7_CLEAN_WAY L2C.REG7_CLEAN_WAY
#define L2CREG7_CLEAN_INV_PA L2C.REG7_CLEAN_INV_PA
#define L2CREG7_CLEAN_INV_INDEX L2C.REG7_CLEAN_INV_INDEX
#define L2CREG7_CLEAN_INV_WAY L2C.REG7_CLEAN_INV_WAY
#define L2CREG9_D_LOCKDOWN0 L2C.REG9_D_LOCKDOWN0
#define L2CREG9_I_LOCKDOWN0 L2C.REG9_I_LOCKDOWN0
#define L2CREG9_D_LOCKDOWN1 L2C.REG9_D_LOCKDOWN1
#define L2CREG9_I_LOCKDOWN1 L2C.REG9_I_LOCKDOWN1
#define L2CREG9_D_LOCKDOWN2 L2C.REG9_D_LOCKDOWN2
#define L2CREG9_I_LOCKDOWN2 L2C.REG9_I_LOCKDOWN2
#define L2CREG9_D_LOCKDOWN3 L2C.REG9_D_LOCKDOWN3
#define L2CREG9_I_LOCKDOWN3 L2C.REG9_I_LOCKDOWN3
#define L2CREG9_D_LOCKDOWN4 L2C.REG9_D_LOCKDOWN4
#define L2CREG9_I_LOCKDOWN4 L2C.REG9_I_LOCKDOWN4
#define L2CREG9_D_LOCKDOWN5 L2C.REG9_D_LOCKDOWN5
#define L2CREG9_I_LOCKDOWN5 L2C.REG9_I_LOCKDOWN5
#define L2CREG9_D_LOCKDOWN6 L2C.REG9_D_LOCKDOWN6
#define L2CREG9_I_LOCKDOWN6 L2C.REG9_I_LOCKDOWN6
#define L2CREG9_D_LOCKDOWN7 L2C.REG9_D_LOCKDOWN7
#define L2CREG9_I_LOCKDOWN7 L2C.REG9_I_LOCKDOWN7
#define L2CREG9_LOCK_LINE_EN L2C.REG9_LOCK_LINE_EN
#define L2CREG9_UNLOCK_WAY L2C.REG9_UNLOCK_WAY
#define L2CREG12_ADDR_FILTERING_START L2C.REG12_ADDR_FILTERING_START
#define L2CREG12_ADDR_FILTERING_END L2C.REG12_ADDR_FILTERING_END
#define L2CREG15_DEBUG_CTRL L2C.REG15_DEBUG_CTRL
#define L2CREG15_PREFETCH_CTRL L2C.REG15_PREFETCH_CTRL
#define L2CREG15_POWER_CTRL L2C.REG15_POWER_CTRL
/* <-SEC M1.10.1 */
#endif
