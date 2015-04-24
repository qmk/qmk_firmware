/**************************************************************************//**
 * @file     pl310.c
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
#include "MBRZA1H.h"

//Cache Sync operation
void PL310_Sync(void)
{
    PL310->CACHE_SYNC = 0x0;
}

//return Cache controller cache ID
int PL310_GetID (void)
{
    return PL310->CACHE_ID;
}

//return Cache controller cache Type
int PL310_GetType (void)
{
    return PL310->CACHE_TYPE;
}

//Invalidate all cache by way
void PL310_InvAllByWay (void)
{
    unsigned int assoc;

    if (PL310->AUX_CNT & (1<<16))
        assoc = 16;
    else
        assoc =  8;

    PL310->INV_WAY = (1 << assoc) - 1;
    while(PL310->INV_WAY & ((1 << assoc) - 1)); //poll invalidate

    PL310_Sync();
}

//Clean and Invalidate all cache by way
void PL310_CleanInvAllByWay (void)
{
    unsigned int assoc;

    if (PL310->AUX_CNT & (1<<16))
        assoc = 16;
    else
        assoc =  8;

    PL310->CLEAN_INV_WAY = (1 << assoc) - 1;
    while(PL310->CLEAN_INV_WAY && ((1 << assoc) - 1)); //poll invalidate

    PL310_Sync();
}

//Enable Cache
void PL310_Enable(void)
{
    PL310->CONTROL = 0;
    PL310->INTERRUPT_CLEAR = 0x000001FFuL;
    PL310->DEBUG_CONTROL = 0;
    PL310->DATA_LOCK_0_WAY = 0;
    PL310->CACHE_SYNC = 0;

    PL310->CONTROL = 0x01;
    PL310_Sync();
}
//Disable Cache
void PL310_Disable(void)
{
    PL310->CONTROL = 0x00;
    PL310_Sync();
}

//Invalidate cache by physical address
void PL310_InvPa (void *pa)
{
    PL310->INV_LINE_PA = (unsigned int)pa;
    PL310_Sync();
}

//Clean cache by physical address
void PL310_CleanPa (void *pa)
{
    PL310->CLEAN_LINE_PA = (unsigned int)pa;
    PL310_Sync();
}

//Clean and invalidate cache by physical address
void PL310_CleanInvPa (void *pa)
{
    PL310->CLEAN_INV_LINE_PA = (unsigned int)pa;
    PL310_Sync();
}


