/**************************************************************************//**
 * @file     gic.c
 * @brief    Implementation of GIC functions declared in CMSIS Cortex-A9 Core Peripheral Access Layer Header File
 * @version
 * @date     19 Sept 2013
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

#define GICDistributor      ((GICDistributor_Type      *)     Renesas_RZ_A1_GIC_DISTRIBUTOR_BASE ) /*!< GIC Distributor configuration struct */
#define GICInterface        ((GICInterface_Type        *)     Renesas_RZ_A1_GIC_INTERFACE_BASE )   /*!< GIC Interface configuration struct */

/* Globals for use of post-scatterloading code that must access GIC */
const uint32_t GICDistributor_BASE = Renesas_RZ_A1_GIC_DISTRIBUTOR_BASE;
const uint32_t GICInterface_BASE = Renesas_RZ_A1_GIC_INTERFACE_BASE;

void GIC_EnableDistributor(void)
{
    GICDistributor->ICDDCR |= 1; //enable distributor
}

void GIC_DisableDistributor(void)
{
    GICDistributor->ICDDCR &=~1; //disable distributor
}

uint32_t GIC_DistributorInfo(void)
{
    return (uint32_t)(GICDistributor->ICDICTR);
}

uint32_t GIC_DistributorImplementer(void)
{
    return (uint32_t)(GICDistributor->ICDIIDR);
}

void GIC_SetTarget(IRQn_Type IRQn, uint32_t cpu_target)
{
    volatile uint8_t* field = (volatile uint8_t*)&(GICDistributor->ICDIPTR[IRQn / 4]);
    field += IRQn % 4;
    *field = (uint8_t)cpu_target & 0xf;
}

void GIC_SetICDICFR (const uint32_t *ICDICFRn)
{
    uint32_t i, num_irq;

    //Get the maximum number of interrupts that the GIC supports
    num_irq = 32 * ((GIC_DistributorInfo() & 0x1f) + 1);

    for (i = 0; i < (num_irq/16); i++)
    {
        GICDistributor->ICDISPR[i] = *ICDICFRn++;
    }
}

uint32_t GIC_GetTarget(IRQn_Type IRQn)
{
    volatile uint8_t* field = (volatile uint8_t*)&(GICDistributor->ICDIPTR[IRQn / 4]);
    field += IRQn % 4;
    return ((uint32_t)*field & 0xf);
}

void GIC_EnableInterface(void)
{
    GICInterface->ICCICR |= 1; //enable interface
}

void GIC_DisableInterface(void)
{
    GICInterface->ICCICR &=~1; //disable distributor
}

IRQn_Type GIC_AcknowledgePending(void)
{
    return (IRQn_Type)(GICInterface->ICCIAR);
}

void GIC_EndInterrupt(IRQn_Type IRQn)
{
    GICInterface->ICCEOIR = IRQn;
}

void GIC_EnableIRQ(IRQn_Type IRQn)
{
    GICDistributor->ICDISER[IRQn / 32] = 1 << (IRQn % 32);
}

void GIC_DisableIRQ(IRQn_Type IRQn)
{
    GICDistributor->ICDICER[IRQn / 32] = 1 << (IRQn % 32);
}

void GIC_SetPendingIRQ(IRQn_Type IRQn)
{
    GICDistributor->ICDISPR[IRQn / 32] = 1 << (IRQn % 32);
}

void GIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    GICDistributor->ICDICPR[IRQn / 32] = 1 << (IRQn % 32);
}

void GIC_SetLevelModel(IRQn_Type IRQn, int8_t edge_level, int8_t model)
{
    volatile uint8_t* field = (volatile uint8_t*)&(GICDistributor->ICDICFR[IRQn / 16]);
    int  bit_shift = (IRQn % 16)<<1;
    uint8_t save_byte;

    field += (bit_shift / 8);
    bit_shift %= 8;

    save_byte = *field;
    save_byte &= ((uint8_t)~(3u << bit_shift));

    *field = save_byte | ((uint8_t)((edge_level<<1) | model)<< bit_shift);
}

void GIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    volatile uint8_t* field = (volatile uint8_t*)&(GICDistributor->ICDIPR[IRQn / 4]);
    field += (IRQn % 4);
    *field = (uint8_t)priority;
}

uint32_t GIC_GetPriority(IRQn_Type IRQn)
{
    volatile uint8_t* field = (volatile uint8_t*)&(GICDistributor->ICDIPR[IRQn / 4]);
    field += (IRQn % 4);
    return (uint32_t)*field;
}

void GIC_InterfacePriorityMask(uint32_t priority)
{
    GICInterface->ICCPMR = priority & 0xff; //set priority mask
}

void GIC_SetBinaryPoint(uint32_t binary_point)
{
    GICInterface->ICCBPR = binary_point & 0x07; //set binary point
}

uint32_t GIC_GetBinaryPoint(uint32_t binary_point)
{
    return (uint32_t)GICInterface->ICCBPR;
}

uint32_t GIC_GetIRQStatus(IRQn_Type IRQn)
{
    uint32_t pending, active;

    active = ((GICDistributor->ICDABR[IRQn / 32])  >> (IRQn % 32)) & 0x1;
    pending =((GICDistributor->ICDISPR[IRQn / 32]) >> (IRQn % 32)) & 0x1;

    return ((active<<1) | pending);
}

void GIC_SendSGI(IRQn_Type IRQn, uint32_t target_list, uint32_t filter_list)
{
    GICDistributor->ICDSGIR = ((filter_list & 0x3) << 24) | ((target_list & 0xff) << 16) | (IRQn & 0xf);
}

void GIC_DistInit(void)
{
    //IRQn_Type i;
    uint32_t i;
    uint32_t num_irq = 0;
    uint32_t priority_field;

    //A reset sets all bits in the ICDISRs corresponding to the SPIs to 0,
    //configuring all of the interrupts as Secure.

    //Disable interrupt forwarding
    GIC_DisableDistributor();
    //Get the maximum number of interrupts that the GIC supports
    num_irq = 32 * ((GIC_DistributorInfo() & 0x1f) + 1);

    /* Priority level is implementation defined.
     To determine the number of priority bits implemented write 0xFF to an ICDIPR
     priority field and read back the value stored.*/
    GIC_SetPriority((IRQn_Type)0, 0xff);
    priority_field = GIC_GetPriority((IRQn_Type)0);

    for (i = 32; i < num_irq; i++)
    {
        //Disable all SPI the interrupts
        GIC_DisableIRQ((IRQn_Type)i);
        //Set level-sensitive and N-N model
        //GIC_SetLevelModel(i, 0, 0);
        //Set priority
        GIC_SetPriority((IRQn_Type)i, priority_field/2);
        //Set target list to "all cpus"
        GIC_SetTarget((IRQn_Type)i, 0xff);
    }
    /* Set level-edge and 1-N model */
    /* GICDistributor->ICDICFR[ 0] is read only */
    GICDistributor->ICDICFR[ 1] = 0x00000055;
    GICDistributor->ICDICFR[ 2] = 0xFFFD5555;
    GICDistributor->ICDICFR[ 3] = 0x555FFFFF;
    GICDistributor->ICDICFR[ 4] = 0x55555555;
    GICDistributor->ICDICFR[ 5] = 0x55555555;
    GICDistributor->ICDICFR[ 6] = 0x55555555;
    GICDistributor->ICDICFR[ 7] = 0x55555555;
    GICDistributor->ICDICFR[ 8] = 0x5555F555;
    GICDistributor->ICDICFR[ 9] = 0x55555555;
    GICDistributor->ICDICFR[10] = 0x55555555;
    GICDistributor->ICDICFR[11] = 0xF5555555;
    GICDistributor->ICDICFR[12] = 0xF555F555;
    GICDistributor->ICDICFR[13] = 0x5555F555;
    GICDistributor->ICDICFR[14] = 0x55555555;
    GICDistributor->ICDICFR[15] = 0x55555555;
    GICDistributor->ICDICFR[16] = 0x55555555;
    GICDistributor->ICDICFR[17] = 0xFD555555;
    GICDistributor->ICDICFR[18] = 0x55555557;
    GICDistributor->ICDICFR[19] = 0x55555555;
    GICDistributor->ICDICFR[20] = 0xFFD55555;
    GICDistributor->ICDICFR[21] = 0x5F55557F;
    GICDistributor->ICDICFR[22] = 0xFD55555F;
    GICDistributor->ICDICFR[23] = 0x55555557;
    GICDistributor->ICDICFR[24] = 0x55555555;
    GICDistributor->ICDICFR[25] = 0x55555555;
    GICDistributor->ICDICFR[26] = 0x55555555;
    GICDistributor->ICDICFR[27] = 0x55555555;
    GICDistributor->ICDICFR[28] = 0x55555555;
    GICDistributor->ICDICFR[29] = 0x55555555;
    GICDistributor->ICDICFR[30] = 0x55555555;
    GICDistributor->ICDICFR[31] = 0x55555555;
    GICDistributor->ICDICFR[32] = 0x55555555;
    GICDistributor->ICDICFR[33] = 0x55555555;

    //Enable distributor
    GIC_EnableDistributor();
}

void GIC_CPUInterfaceInit(void)
{
    IRQn_Type i;
    uint32_t priority_field;

    //A reset sets all bits in the ICDISRs corresponding to the SPIs to 0,
    //configuring all of the interrupts as Secure.

    //Disable interrupt forwarding
    GIC_DisableInterface();

    /* Priority level is implementation defined.
     To determine the number of priority bits implemented write 0xFF to an ICDIPR
     priority field and read back the value stored.*/
    GIC_SetPriority((IRQn_Type)0, 0xff);
    priority_field = GIC_GetPriority((IRQn_Type)0);

    //SGI and PPI
    for (i = (IRQn_Type)0; i < 32; i++)
    {
        //Set level-sensitive and N-N model for PPI
        //if(i > 15)
            //GIC_SetLevelModel(i, 0, 0);
        //Disable SGI and PPI interrupts
        GIC_DisableIRQ(i);
        //Set priority
        GIC_SetPriority(i, priority_field/2);
    }
    //Enable interface
    GIC_EnableInterface();
    //Set binary point to 0
    GIC_SetBinaryPoint(0);
    //Set priority mask
    GIC_InterfacePriorityMask(0xff);
}

void GIC_Enable(void)
{
    GIC_DistInit();
    GIC_CPUInterfaceInit(); //per CPU
}

