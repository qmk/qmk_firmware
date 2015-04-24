/**************************************************************************//**
 * @file     pl310.h
 * @brief    Implementation of pl310 functions
 * @version
 * @date     11 June 2013
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2011 - 2013 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#ifndef __PL310
#define __PL310

typedef struct
{
  __I  uint32_t CACHE_ID;                   /*!< Offset: 0x0000   Cache ID Register               */
  __I  uint32_t CACHE_TYPE;                 /*!< Offset: 0x0004   Cache Type Register             */
       uint32_t RESERVED0[0x3e];
  __IO uint32_t CONTROL;                    /*!< Offset: 0x0100   Control Register                */
  __IO uint32_t AUX_CNT;                    /*!< Offset: 0x0104   Auxiliary Control               */
       uint32_t RESERVED1[0x3e];
  __IO uint32_t EVENT_CONTROL;              /*!< Offset: 0x0200   Event Counter Control           */
  __IO uint32_t EVENT_COUNTER1_CONF;        /*!< Offset: 0x0204   Event Counter 1 Configuration   */
  __IO uint32_t EVENT_COUNTER0_CONF;        /*!< Offset: 0x0208   Event Counter 1 Configuration   */
       uint32_t RESERVED2[0x2];
  __IO uint32_t INTERRUPT_MASK;             /*!< Offset: 0x0214   Interrupt Mask                  */
  __I  uint32_t MASKED_INT_STATUS;          /*!< Offset: 0x0218   Masked Interrupt Status         */
  __I  uint32_t RAW_INT_STATUS;             /*!< Offset: 0x021c   Raw Interrupt Status            */
  __O  uint32_t INTERRUPT_CLEAR;            /*!< Offset: 0x0220   Interrupt Clear                 */
       uint32_t RESERVED3[0x143];
  __IO uint32_t CACHE_SYNC;                 /*!< Offset: 0x0730   Cache Sync                      */
       uint32_t RESERVED4[0xf];
  __IO uint32_t INV_LINE_PA;                /*!< Offset: 0x0770   Invalidate Line By PA           */
       uint32_t RESERVED6[2];
  __IO uint32_t INV_WAY;                    /*!< Offset: 0x077c   Invalidate by Way               */
       uint32_t RESERVED5[0xc];
  __IO uint32_t CLEAN_LINE_PA;              /*!< Offset: 0x07b0   Clean Line by PA                */
       uint32_t RESERVED7[1];
  __IO uint32_t CLEAN_LINE_INDEX_WAY;       /*!< Offset: 0x07b8   Clean Line by Index/Way         */
  __IO uint32_t CLEAN_WAY;                  /*!< Offset: 0x07bc   Clean by Way                    */
       uint32_t RESERVED8[0xc];
  __IO uint32_t CLEAN_INV_LINE_PA;          /*!< Offset: 0x07f0   Clean and Invalidate Line by PA  */
       uint32_t RESERVED9[1];
  __IO uint32_t CLEAN_INV_LINE_INDEX_WAY;   /*!< Offset: 0x07f8   Clean and Invalidate Line by Index/Way  */
  __IO uint32_t CLEAN_INV_WAY;              /*!< Offset: 0x07fc   Clean and Invalidate by Way     */
       uint32_t RESERVED10[0x40];
  __IO uint32_t DATA_LOCK_0_WAY;            /*!< Offset: 0x0900   Data Lockdown 0 by Way          */
  __IO uint32_t INST_LOCK_0_WAY;            /*!< Offset: 0x0904   Instruction Lockdown 0 by Way   */
  __IO uint32_t DATA_LOCK_1_WAY;            /*!< Offset: 0x0908   Data Lockdown 1 by Way          */
  __IO uint32_t INST_LOCK_1_WAY;            /*!< Offset: 0x090c   Instruction Lockdown 1 by Way   */
  __IO uint32_t DATA_LOCK_2_WAY;            /*!< Offset: 0x0910   Data Lockdown 2 by Way          */
  __IO uint32_t INST_LOCK_2_WAY;            /*!< Offset: 0x0914   Instruction Lockdown 2 by Way   */
  __IO uint32_t DATA_LOCK_3_WAY;            /*!< Offset: 0x0918   Data Lockdown 3 by Way          */
  __IO uint32_t INST_LOCK_3_WAY;            /*!< Offset: 0x091c   Instruction Lockdown 3 by Way   */
  __IO uint32_t DATA_LOCK_4_WAY;            /*!< Offset: 0x0920   Data Lockdown 4 by Way          */
  __IO uint32_t INST_LOCK_4_WAY;            /*!< Offset: 0x0924   Instruction Lockdown 4 by Way   */
  __IO uint32_t DATA_LOCK_5_WAY;            /*!< Offset: 0x0928   Data Lockdown 5 by Way          */
  __IO uint32_t INST_LOCK_5_WAY;            /*!< Offset: 0x092c   Instruction Lockdown 5 by Way   */
  __IO uint32_t DATA_LOCK_6_WAY;            /*!< Offset: 0x0930   Data Lockdown 5 by Way          */
  __IO uint32_t INST_LOCK_6_WAY;            /*!< Offset: 0x0934   Instruction Lockdown 5 by Way   */
  __IO uint32_t DATA_LOCK_7_WAY;            /*!< Offset: 0x0938   Data Lockdown 6 by Way          */
  __IO uint32_t INST_LOCK_7_WAY;            /*!< Offset: 0x093c   Instruction Lockdown 6 by Way   */
       uint32_t RESERVED11[0x4];
  __IO uint32_t LOCK_LINE_EN;               /*!< Offset: 0x0950   Lockdown by Line Enable         */
  __IO uint32_t UNLOCK_ALL_BY_WAY;          /*!< Offset: 0x0954   Unlock All Lines by Way         */
       uint32_t RESERVED12[0xaa];
  __IO uint32_t ADDRESS_FILTER_START;       /*!< Offset: 0x0c00   Address Filtering Start         */
  __IO uint32_t ADDRESS_FILTER_END;         /*!< Offset: 0x0c04   Address Filtering End           */
       uint32_t RESERVED13[0xce];
  __IO uint32_t DEBUG_CONTROL;              /*!< Offset: 0x0f40   Debug Control Register          */

} PL310_TypeDef;

#define PL310           ((PL310_TypeDef *)Renesas_RZ_A1_PL310_BASE) /*!< PL310 Declaration */

extern int PL310_GetID (void);
extern int PL310_GetType (void);
extern void PL310_InvAllByWay (void);
extern void PL310_CleanInvAllByWay(void);
extern void PL310_Enable(void);
extern void PL310_Disable(void);
extern void PL310_InvPa (void *);
extern void PL310_CleanPa (void *);
extern void PL310_CleanInvPa (void *);

#endif


