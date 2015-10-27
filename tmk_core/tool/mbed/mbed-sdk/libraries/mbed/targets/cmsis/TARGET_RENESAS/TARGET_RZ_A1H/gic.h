/**************************************************************************//**
 * @file     gic.h
 * @brief    Implementation of GIC functions declared in CMSIS Cortex-A9 Core Peripheral Access Layer Header File
 * @version
 * @date     29 August 2013
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

#ifndef GIC_H_
#define GIC_H_

/* IO definitions (access restrictions to peripheral registers) */
/**
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

/** \brief  Structure type to access the Generic Interrupt Controller Distributor (GICD)
 */
typedef struct
{
  __IO uint32_t ICDDCR;
  __I  uint32_t ICDICTR;
  __I  uint32_t ICDIIDR;
       uint32_t RESERVED0[29];
  __IO uint32_t ICDISR[32];
  __IO uint32_t ICDISER[32];
  __IO uint32_t ICDICER[32];
  __IO uint32_t ICDISPR[32];
  __IO uint32_t ICDICPR[32];
  __I  uint32_t ICDABR[32];
       uint32_t RESERVED1[32];
  __IO uint32_t ICDIPR[256];
  __IO uint32_t ICDIPTR[256];
  __IO uint32_t ICDICFR[64];
       uint32_t RESERVED2[128];
  __IO uint32_t ICDSGIR;
}  GICDistributor_Type;

/** \brief  Structure type to access the Controller Interface (GICC)
 */
typedef struct
{
  __IO uint32_t ICCICR;          // +0x000 - RW - CPU Interface Control Register
  __IO uint32_t ICCPMR;          // +0x004 - RW - Interrupt Priority Mask Register
  __IO uint32_t ICCBPR;          // +0x008 - RW - Binary Point Register
  __I  uint32_t ICCIAR;          // +0x00C - RO - Interrupt Acknowledge Register
  __IO uint32_t ICCEOIR;         // +0x010 - WO - End of Interrupt Register
  __I  uint32_t ICCRPR;          // +0x014 - RO - Running Priority Register
  __I  uint32_t ICCHPIR;         // +0x018 - RO - Highest Pending Interrupt Register
  __IO uint32_t ICCABPR;         // +0x01C - RW - Aliased Binary Point Register

       uint32_t RESERVED[55];

  __I  uint32_t ICCIIDR;         // +0x0FC - RO - CPU Interface Identification Register
}  GICInterface_Type;

/*@} end of GICD */

/* ##########################   GIC functions  #################################### */
/**  \brief      Functions that manage interrupts via the GIC.
  @{
 */

/** \brief  Enable DistributorGICInterface->ICCICR |= 1; //enable interface

   Enables the forwarding of pending interrupts to the CPU interfaces.

 */
void GIC_EnableDistributor(void);

/** \brief  Disable Distributor

   Disables the forwarding of pending interrupts to the CPU interfaces.

 */
void GIC_DisableDistributor(void);

/** \brief  Provides information about the configuration of the GIC.
   Provides information about the configuration of the GIC.
   - whether the GIC implements the Security Extensions
   - the maximum number of interrupt IDs that the GIC supports
   - the number of CPU interfaces implemented
   - if the GIC implements the Security Extensions, the maximum number of implemented Lockable Shared Peripheral Interrupts (LSPIs).

   \return Distributor Information.
 */
uint32_t GIC_DistributorInfo(void);

/** \brief  Distributor Implementer Identification Register.

   Distributor Implementer Identification Register

   \return Implementer Information.
 */
uint32_t GIC_DistributorImplementer(void);

/** \brief  Set list of processors that the interrupt is sent to if it is asserted.

    The ICDIPTRs provide an 8-bit CPU targets field for each interrupt supported by the GIC.
    This field stores the list of processors that the interrupt is sent to if it is asserted.

    \param [in]      IRQn  Interrupt number.
    \param [in]    target  CPU target
 */
void GIC_SetTarget(IRQn_Type IRQn, uint32_t cpu_target);

/** \brief  Get list of processors that the interrupt is sent to if it is asserted.

    The ICDIPTRs provide an 8-bit CPU targets field for each interrupt supported by the GIC.
    This field stores the list of processors that the interrupt is sent to if it is asserted.

    \param [in]      IRQn  Interrupt number.
    \param [in]    target  CPU target
*/
uint32_t GIC_GetTarget(IRQn_Type IRQn);

/** \brief  Enable Interface

   Enables the signalling of interrupts to the target processors.

 */
void GIC_EnableInterface(void);

/** \brief  Disable Interface

   Disables the signalling of interrupts to the target processors.

 */
void GIC_DisableInterface(void);

/** \brief  Acknowledge Interrupt

    The function acknowledges the highest priority pending interrupt and returns its IRQ number.

    \return             Interrupt number
 */
IRQn_Type GIC_AcknowledgePending(void);

/** \brief  End Interrupt

    The function writes the end of interrupt register, indicating that handling of the interrupt is complete.

    \param [in]   IRQn  Interrupt number.
 */
void GIC_EndInterrupt(IRQn_Type IRQn);


/** \brief  Enable Interrupt

    Set-enable bit for each interrupt supported by the GIC.

    \param [in]      IRQn  External interrupt number.
 */
void GIC_EnableIRQ(IRQn_Type IRQn);

/** \brief  Disable Interrupt

    Clear-enable bit for each interrupt supported by the GIC.

    \param [in]      IRQn  Number of the external interrupt to disable
 */
void GIC_DisableIRQ(IRQn_Type IRQn);

/** \brief  Set Pending Interrupt

    Set-pending bit for each interrupt supported by the GIC.

    \param [in]      IRQn  Interrupt number.
 */
void GIC_SetPendingIRQ(IRQn_Type IRQn);

/** \brief  Clear Pending Interrupt

    Clear-pending bit for each interrupt supported by the GIC

    \param [in]      IRQn  Number of the interrupt for clear pending
 */
void GIC_ClearPendingIRQ(IRQn_Type IRQn);

/** \brief  Int_config field for each interrupt supported by the GIC.

    This field identifies whether the corresponding interrupt is:
    (1) edge-triggered or (0) level-sensitive
    (1) 1-N model or (0) N-N model

    \param [in]      IRQn  Interrupt number.
    \param [in] edge_level (1) edge-triggered or (0) level-sensitive
    \param [in] model      (1) 1-N model or (0) N-N model
 */
void GIC_SetLevelModel(IRQn_Type IRQn, int8_t edge_level, int8_t model);


/** \brief  Set Interrupt Priority

    The function sets the priority of an interrupt.

    \param [in]      IRQn  Interrupt number.
    \param [in]  priority  Priority to set.
 */
void GIC_SetPriority(IRQn_Type IRQn, uint32_t priority);

/** \brief  Get Interrupt Priority

    The function reads the priority of an interrupt.

    \param [in]   IRQn  Interrupt number.
    \return             Interrupt Priority.
 */
uint32_t GIC_GetPriority(IRQn_Type IRQn);

/** \brief  CPU Interface Priority Mask Register

    The priority mask level for the CPU interface. If the priority of an interrupt is higher than the
    value indicated by this field, the interface signals the interrupt to the processor.

    \param [in]   Mask.
 */
void GIC_InterfacePriorityMask(uint32_t priority);

/** \brief  Set the binary point.

     Set the point at which the priority value fields split into two parts, the group priority field and the subpriority field.

    \param [in]   Mask.
 */
void GIC_SetBinaryPoint(uint32_t binary_point);

/** \brief  Get the binary point.

     Get the point at which the priority value fields split into two parts, the group priority field and the subpriority field.

    \return  Binary point.
 */
uint32_t GIC_GetBinaryPoint(uint32_t binary_point);

/** \brief  Get Interrupt state.

     Get the interrupt state, whether pending and/or active

    \return  0 - inactive, 1 - pending, 2 - active, 3 - pending and active
 */
uint32_t GIC_GetIRQStatus(IRQn_Type IRQn);

/** \brief  Send Software Generated interrupt

    Provides an interrupt priority filter. Only interrupts with higher priority than the value in this register can be signalled to the processor.
GIC_InterfacePriorityMask
    \param [in]   IRQn         The Interrupt ID of the SGI.
    \param [in]   target_list  CPUTargetList
    \param [in]   filter_list  TargetListFilter
 */
void GIC_SendSGI(IRQn_Type IRQn, uint32_t target_list, uint32_t filter_list);

/** \brief  API call to initialise the interrupt distributor

   API call to initialise the interrupt distributor

 */
void GIC_DistInit(void);

/** \brief  API call to initialise the CPU interface

   API call to initialise the CPU interface

 */
void GIC_CPUInterfaceInit(void);

/** \brief  API call to set the Interrupt Configuration Registers

   API call to initialise the Interrupt Configuration Registers

 */
void GIC_SetICDICFR (const uint32_t *ICDICFRn);

/** \brief  API call to  Enable the GIC

   API call to  Enable the GIC

 */
void GIC_Enable(void);

#endif /* GIC_H_ */
