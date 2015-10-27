/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_MPU_HAL_H__
#define __FSL_MPU_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_mpu_features.h"
#include "fsl_device_registers.h"

#ifndef MBED_NO_MPU

#define MPU_REGION_NUMBER 12

/*!
 * @addtogroup mpu_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief MPU region number region0~region11. */
typedef enum _mpu_region_num{
    kMPURegionNum00 = 0U,  /*!< MPU region number 0*/
    kMPURegionNum01 = 1U,  /*!< MPU region number 1*/
    kMPURegionNum02 = 2U,  /*!< MPU region number 2*/
    kMPURegionNum03 = 3U,  /*!< MPU region number 3*/
    kMPURegionNum04 = 4U,  /*!< MPU region number 4*/
    kMPURegionNum05 = 5U,  /*!< MPU region number 5*/
    kMPURegionNum06 = 6U,  /*!< MPU region number 6*/
    kMPURegionNum07 = 7U,  /*!< MPU region number 7*/
    kMPURegionNum08 = 8U,  /*!< MPU region number 8*/
    kMPURegionNum09 = 9U,  /*!< MPU region number 9*/
    kMPURegionNum10 = 10U, /*!< MPU region number 10*/
    kMPURegionNum11 = 11U, /*!< MPU region number 11*/
#if defined(CPU_MK70FN1M0VMF12) || defined(CPU_MK70FX512VMF12) || defined(CPU_MK70FN1M0VMF15) || defined(CPU_MK70FX512VMF15) || \
    defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12) || defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15)
    kMPURegionNum11 = 12U, /*!< MPU region number 12*/
    kMPURegionNum11 = 13U, /*!< MPU region number 13*/
    kMPURegionNum11 = 14U, /*!< MPU region number 14*/
    kMPURegionNum11 = 15U, /*!< MPU region number 15*/
#endif
}mpu_region_num;

/*! @brief MPU error address register0~4. */
typedef enum _mpu_error_addr_reg{
    kMPUErrorAddrReg00 = 0U, /*!< MPU error address register 0*/
    kMPUErrorAddrReg01 = 1U, /*!< MPU error address register 1*/
    kMPUErrorAddrReg02 = 2U, /*!< MPU error address register 2*/
    kMPUErrorAddrReg03 = 3U, /*!< MPU error address register 3*/
    kMPUErrorAddrReg04 = 4U  /*!< MPU error address register 4*/
}mpu_error_addr_reg;

/*! @brief MPU error detail register0~4. */
typedef enum _mpu_error_detail_reg{
    kMPUErrorDetailReg00 = 0U, /*!< MPU error detail register 0*/
    kMPUErrorDetailReg01 = 1U, /*!< MPU error detail register 1*/
    kMPUErrorDetailReg02 = 2U, /*!< MPU error detail register 2*/
    kMPUErrorDetailReg03 = 3U, /*!< MPU error detail register 3*/
    kMPUErrorDetailReg04 = 4U  /*!< MPU error detail register 4*/
}mpu_error_detail_reg;

/*! @brief MPU access error. */
typedef enum _mpu_error_access_type{
    kMPUReadErrorType  = 0U, /*!< MPU error type---read*/
    kMPUWriteErrorType = 1U  /*!< MPU error type---write*/
}mpu_error_access_type;

/*! @brief MPU access error attributes.*/
typedef enum _mpu_error_attributes{
    kMPUUserModeInstructionAccess       = 0U, /*!< access instruction error in user mode*/
    kMPUUserModeDataAccess              = 1U, /*!< access data error in user mode*/
    kMPUSupervisorModeInstructionAccess = 2U, /*!< access instruction error in supervisor mode*/
    kMPUSupervisorModeDataAccess        = 3U  /*!< access data error in supervisor mode*/
}mpu_error_attributes;

/*! @brief access MPU in which mode. */
typedef enum _mpu_access_mode{
    kMPUAccessInUserMode       = 0U, /*!< access data or instruction in user mode*/
    kMPUAccessInSupervisorMode = 1U  /*!< access data or instruction in supervisor mode*/
}mpu_access_mode;

/*! @brief MPU master number. */
typedef enum _mpu_master_num{
    kMPUMaster00 = 0U, /*!< Core.*/
    kMPUMaster01 = 1U, /*!< Debugger.*/
    kMPUMaster02 = 2U, /*!< DMA.*/
    kMPUMaster03 = 3U, /*!< ENET.*/
    kMPUMaster04 = 4U, /*!< USB.*/
    kMPUMaster05 = 5U, /*!< SDHC.*/
    kMPUMaster06 = 6U, /*!< undefined.*/
    kMPUMaster07 = 7U  /*!< undefined.*/
}mpu_master_num;

/*! @brief MPU error access control detail. */
typedef enum _mpu_error_access_control{
    kMPUNoRegionHitError        = 0U, /*!< no region hit error*/
    kMPUNoneOverlappRegionError = 1U, /*!< access single region error*/
    kMPUOverlappRegionError     = 2U  /*!< access overlapping region error*/
}mpu_error_access_control;

/*! @brief MPU access rights in supervisor mode for master0~master3. */
typedef enum _mpu_supervisor_access_rights{
    kMPUSupervisorReadWriteExecute = 0U, /*!< R W E allowed in supervisor mode*/
    kMPUSupervisorReadExecute      = 1U, /*!< R E allowed in supervisor mode*/
    kMPUSupervisorReadWrite        = 2U, /*!< R W allowed in supervisor mode*/
    kMPUSupervisorEqualToUsermode  = 3U  /*!< access permission equal to user mode*/
}mpu_supervisor_access_rights;

/*! @brief MPU access rights in user mode for master0~master3. */
typedef enum _mpu_user_access_rights{
    kMPUUserNoAccessRights   = 0U, /*!< no access allowed in user mode*/
    kMPUUserExecute          = 1U, /*!< E allowed in user mode*/
    kMPUUserWrite            = 2U, /*!< W allowed in user mode*/
    kMPUUserWriteExecute     = 3U, /*!< W E allowed in user mode*/
    kMPUUserRead             = 4U, /*!< R allowed in user mode*/
    kMPUUserReadExecute      = 5U, /*!< R E allowed in user mode*/
    kMPUUserReadWrite        = 6U, /*!< R W allowed in user mode*/
    kMPUUserReadWriteExecute = 7U  /*!< R W E allowed in user mode*/
}mpu_user_access_rights;

/*! @brief MPU process identifier. */
typedef enum _mpu_process_identifier_value{
    kMPUIdentifierDisable = 0U, /*!< processor identifier disable*/
    kMPUIdentifierEnable  = 1U  /*!< processor identifier enable*/
}mpu_process_identifier_value;

/*! @brief MPU access control for master4~master7. */
typedef enum _mpu_access_control{
    kMPUAccessDisable = 0U, /*!< Read or Write not allowed*/
    kMPUAccessEnable  = 1U  /*!< Read or Write allowed*/
}mpu_access_control;

/*! @brief MPU access type for master4~master7. */
typedef enum _mpu_access_type{
    kMPUAccessRead  = 0U, /*!< Access type is read*/
    kMPUAccessWrite = 1U  /*!< Access type is write*/
}mpu_access_type;

/*! @brief MPU access region valid. */
typedef enum _mpu_region_valid{
    kMPURegionInvalid = 0U, /*!< region invalid*/
    kMPURegionValid   = 1U  /*!< region valid*/
}mpu_region_valid;

/*! @brief MPU status return codes.*/
typedef enum _MPU_status {
    kStatus_MPU_Success                   = 0x0U, /*!< Succeed. */
    kStatus_MPU_NotInitlialized           = 0x1U, /*!< MPU is not initialized yet. */
    kStatus_MPU_NullArgument              = 0x2U, /*!< Argument is NULL.*/
 } mpu_status_t;
 
/*******************************************************************************
 ** Variables
 *******************************************************************************/

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name MPU HAL.
 * @{
 */

/*!
 * @brief Enables the MPU module operation
 *
 * @param baseAddr The MPU peripheral base address
 */
static inline void MPU_HAL_Enable(uint32_t baseAddr)
{
    BW_MPU_CESR_VLD(baseAddr, (uint8_t)true);
}

/*!
 * @brief Disables the MPU module operation
 *
 * @param baseAddr The MPU peripheral base address
 */
static inline void MPU_HAL_Disable(uint32_t baseAddr)
{
    BW_MPU_CESR_VLD(baseAddr, (uint8_t)false);
}

/*!
 * @brief Checks whether the MPU module is enabled
 *
 * @param baseAddr The MPU peripheral base address
 * @retval true MPU module is enabled
 * @retval false MPU module is disabled
 */
static inline bool MPU_HAL_IsEnabled(uint32_t baseAddr)
{
   return BR_MPU_CESR_VLD(baseAddr);
}

/*!
 * @brief Returns the total region number
 *
 * @param baseAddr The MPU peripheral base address
 * @retval the number of regions
 */
static inline uint32_t MPU_HAL_GetNumberOfRegions(uint32_t baseAddr)
{
    return (BR_MPU_CESR_NRGD(baseAddr));
}

/*!
 * @brief Returns MPU slave sports
 *
 * @param baseAddr The MPU peripheral base address
 * @retval the number of slaves
 */
static inline uint32_t MPU_HAL_GetNumberOfSlaves(uint32_t baseAddr)
{
    return (BR_MPU_CESR_NSP(baseAddr));
}

/*!
 * @brief Returns hardware level info
 *
 * @param baseAddr The MPU peripheral base address
 * @retval hardware revision level
 */
static inline uint32_t MPU_HAL_GetHardwareRevisionLevel(uint32_t baseAddr)
{
    return (BR_MPU_CESR_HRL(baseAddr));
}

/*!
 * @brief Returns hardware level info
 *
 * @param baseAddr The MPU peripheral base address
 * @param regNum Error address register number
 * @retval error access address
 */
static inline uint32_t MPU_HAL_GetErrorAccessAddr(uint32_t baseAddr, mpu_error_addr_reg regNum)
{
    assert(regNum < HW_MPU_EARn_COUNT);
    return (BR_MPU_EARn_EADDR(baseAddr, regNum));
}

/*!
 * @brief Returns error access slaves sports
 *
 * @param baseAddr The MPU peripheral base address
 * @retval error slave sports
*/
static inline uint8_t MPU_HAL_GetErrorSlaveSports(uint32_t baseAddr)
{
    return (BR_MPU_CESR_SPERR(baseAddr));
}

/*!
 * @brief Returns error access address
 *
 * @param baseAddr The MPU peripheral base address
 * @param errorDetailRegNum Error detail register number
 * @retval error access type
*/
static inline mpu_error_access_type MPU_HAL_GetErrorAccessType(uint32_t baseAddr, mpu_error_detail_reg errorDetailRegNum)
{
    assert(errorDetailRegNum < HW_MPU_EDRn_COUNT);
    return (mpu_error_access_type)(BR_MPU_EDRn_ERW(baseAddr, errorDetailRegNum));
}

/*!
 * @brief Returns error access attributes
 *
 * @param baseAddr The MPU peripheral base address
 * @param errorDetailRegNum Detail error register number
 * @retval error access attributes
 */
static inline mpu_error_attributes MPU_HAL_GetErrorAttributes(uint32_t baseAddr, mpu_error_detail_reg errorDetailRegNum)
{
    assert(errorDetailRegNum < HW_MPU_EDRn_COUNT);
    return (mpu_error_attributes)(BR_MPU_EDRn_EATTR(baseAddr, errorDetailRegNum));
}

/*!
 * @brief Returns error access master number
 *
 * @param baseAddr The MPU peripheral base address
 * @param errorDetailRegNum Error register number
 * @retval error master number
 */
static inline mpu_master_num MPU_HAL_GetErrorMasterNum(uint32_t baseAddr, mpu_error_detail_reg errorDetailRegNum)
{
    assert(errorDetailRegNum < HW_MPU_EDRn_COUNT);
    return (mpu_master_num)(BR_MPU_EDRn_EMN(baseAddr, errorDetailRegNum));
}

/*!
 * @brief Returns error process identifier
 *
 * @param baseAddr The MPU peripheral base address
 * @param errorDetailRegNum Error register number
 * @retval error process identifier
 */
static inline uint32_t MPU_HAL_GetErrorProcessIdentifier(uint32_t baseAddr, mpu_error_detail_reg errorDetailRegNum)
{
    assert(errorDetailRegNum < HW_MPU_EDRn_COUNT);
    return(BR_MPU_EDRn_EPID(baseAddr, errorDetailRegNum));
}

/*!
 * @brief Returns error access control
 *
 * @param baseAddr The MPU peripheral base address
 * @param errorDetailRegNum Error register number
 * @retval error access control
 */
static inline mpu_error_access_control MPU_HAL_GetErrorAccessControl(uint32_t baseAddr, mpu_error_detail_reg errorDetailRegNum)
{
    assert(errorDetailRegNum < HW_MPU_EDRn_COUNT);
    
    uint32_t i = BR_MPU_EDRn_EACD(baseAddr, errorDetailRegNum);
    
    if(0 == i)
    {
        return (kMPUNoRegionHitError);
    }
    else if(!(i&(i-1)))
    {
        return (kMPUNoneOverlappRegionError);
    }
    else 
    {
        return (kMPUOverlappRegionError);
    }
}

/*!
 * @brief Returns the region start address
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval region start address
 */
static inline uint32_t MPU_HAL_GetRegionStartAddr(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD0_COUNT);
    return (BR_MPU_RGDn_WORD0_SRTADDR(baseAddr, regionNum)<<BP_MPU_RGDn_WORD0_SRTADDR);
}

/*!
 * @brief Sets region start address
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param startAddr Region start address
 */
static inline void MPU_HAL_SetRegionStartAddr(uint32_t baseAddr, mpu_region_num regionNum, uint32_t startAddr)
{
    assert(regionNum < HW_MPU_RGDn_WORD0_COUNT);
    startAddr >>= BP_MPU_RGDn_WORD0_SRTADDR; 
    BW_MPU_RGDn_WORD0_SRTADDR(baseAddr, regionNum, startAddr);
}

/*!
 * @brief Returns region end address
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval region end address
 */
static inline uint32_t MPU_HAL_GetRegionEndAddr(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD1_COUNT);
    return (BR_MPU_RGDn_WORD1_ENDADDR(baseAddr, regionNum)<<BP_MPU_RGDn_WORD0_SRTADDR);
}

/*!
 * @brief Sets region end address
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param endAddr Region end address
 */
static inline void MPU_HAL_SetRegionEndAddr(uint32_t baseAddr, mpu_region_num regionNum, uint32_t endAddr)
{
    assert(regionNum < HW_MPU_RGDn_WORD1_COUNT);
    endAddr >>= BP_MPU_RGDn_WORD0_SRTADDR;
    BW_MPU_RGDn_WORD1_ENDADDR(baseAddr, regionNum, endAddr);
}

/*!
 * @brief Returns all masters access permission for a specific region
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval all masters access permission
 */
static inline uint32_t MPU_HAL_GetAllMastersAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (HW_MPU_RGDn_WORD2_RD(baseAddr, regionNum));
}

/*!
 * @brief Sets all masters access permission for a specific region
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights All masters access rights
 */
static inline void MPU_HAL_SetAllMastersAccessRights(uint32_t baseAddr, mpu_region_num regionNum, uint32_t accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    HW_MPU_RGDn_WORD2_WR(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Gets M0 access permission in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master0 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM0SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDn_WORD2_M0SM(baseAddr, regionNum)); 
}

/*!
 * @brief Gets M0 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master0 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM0UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT); 
    return (mpu_user_access_rights)(BR_MPU_RGDn_WORD2_M0UM(baseAddr, regionNum));
}

/*!
 * @brief Sets M0 access permission in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master0 access permission
 */
static inline void MPU_HAL_SetM0SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);  
    BW_MPU_RGDn_WORD2_M0SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets M0 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master0 access permission
 */
static inline void MPU_HAL_SetM0UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT); 
    BW_MPU_RGDn_WORD2_M0UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether the M0 process identifier is enabled in region hit evaluation
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true m0 process identifier is enabled
 * @retval false m0 process identifier is disabled
 */

static inline bool MPU_HAL_IsM0ProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDn_WORD2_M0PE(baseAddr, regionNum));
}

/*!
 * @brief Sets the M0 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param identifierValue Process identifier value
 */
static inline void MPU_HAL_SetM0ProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M0PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets M1 access permission in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master1 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM1SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDn_WORD2_M1SM(baseAddr, regionNum)); 
}

/*!
 * @brief Gets M1 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master1 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM1UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (mpu_user_access_rights)(BR_MPU_RGDn_WORD2_M1UM(baseAddr, regionNum));
}

/*!
 * @brief Sets M1 access permission in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master1 access permission
 */
static inline void MPU_HAL_SetM1SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M1SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets M1 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master1 access permission
 */
static inline void MPU_HAL_SetM1UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M1UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether M1 process identifier enabled in region hit evaluation
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true m1 process identifier is enabled
 * @retval false m1 process identifier is disabled
 */
static inline bool MPU_HAL_IsM1ProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDn_WORD2_M1PE(baseAddr, regionNum));
}

/*!
 * @brief Sets the M1 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param identifierValue Process identifier value
 */
static inline void MPU_HAL_SetM1ProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M1PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets M2 access permission in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master2 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM2SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDn_WORD2_M2SM(baseAddr, regionNum)); 
}

/*!
 * @brief Gets M2 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master2 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM2UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (mpu_user_access_rights)(BR_MPU_RGDn_WORD2_M2UM(baseAddr, regionNum));
}

/*!
 * @brief Sets M2 access permission in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master2 access permission
 */
static inline void MPU_HAL_SetM2SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M2SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets M2 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master2 access permission
 */
static inline void MPU_HAL_SetM2UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M2UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether the M2 process identifier enabled in region hit evaluation
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true m2 process identifier is enabled
 * @retval false m2 process identifier is disabled
 */

static inline bool MPU_HAL_IsM2ProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDn_WORD2_M2PE(baseAddr, regionNum));
}

/*!
 * @brief Sets the M2 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param identifierValue Process identifier value.
 */
static inline void MPU_HAL_SetM2ProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M2PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets M3 access permission in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master3 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM3SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDn_WORD2_M3SM(baseAddr, regionNum)); 
}

/*!
 * @brief Gets M3 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master3 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM3UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (mpu_user_access_rights)(BR_MPU_RGDn_WORD2_M3UM(baseAddr, regionNum));
}

/*!
 * @brief Sets M3 access permission in supervisor mode.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessRights Master3 access permission.
 */
static inline void MPU_HAL_SetM3SupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M3SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets M3 access permission in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master3 access permission
 */
static inline void MPU_HAL_SetM3UserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M3UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether the M3 process identifier enabled in region hit evaluation
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true m3 process identifier is enabled
 * @retval false m3 process identifier is disabled
 */

static inline bool MPU_HAL_IsM3ProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDn_WORD2_M3PE(baseAddr, regionNum));
}

/*!
 * @brief Sets M3 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param identifierValue Process identifier value
 */
static inline void MPU_HAL_SetM3ProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDn_WORD2_M3PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets the M4 access permission.
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType Access type Read/Write
 * @retval read or write permission
 */
static inline mpu_access_control MPU_HAL_GetM4AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M4RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M4WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets the M4 access permission
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType Access type Read/Write
 * @param accessControl Access permission
 */
static inline void MPU_HAL_SetM4AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
       BW_MPU_RGDn_WORD2_M4RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDn_WORD2_M4WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Gets the M5 access permission
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType Access type Read/Write
 * @retval read or write permission
 */
static inline mpu_access_control MPU_HAL_GetM5AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M5RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M5WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets the M5 access permission
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType Access type Read/Write
 * @param accessControl Access permission
 */
static inline void MPU_HAL_SetM5AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
       BW_MPU_RGDn_WORD2_M5RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDn_WORD2_M5WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Gets the M6 access permission
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType access type Read/Write
 * @retval read or write permission
 */
static inline mpu_access_control MPU_HAL_GetM6AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M6RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M6WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets the M6 access permission
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType Access type Read/Write
 * @param accessControl Access permission
 */
static inline void MPU_HAL_SetM6AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
       BW_MPU_RGDn_WORD2_M6RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDn_WORD2_M6WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Gets the M7 access permission
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType Access type Read/Write
 * @retval read or write permission
 */
static inline mpu_access_control MPU_HAL_GetM7AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M7RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDn_WORD2_M7WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets the M7 access permission
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessType Access type Read/Write
 * @param accessControl Access permission
 */
static inline void MPU_HAL_SetM7AccessControl(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    if(kMPUAccessRead == accessType)
    {
       BW_MPU_RGDn_WORD2_M7RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDn_WORD2_M7WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Checks whether region is valid
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true region is valid
 * @retval false region is invalid
 */
static inline bool MPU_HAL_IsRegionValid(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD3_COUNT);
    return (1 == BR_MPU_RGDn_WORD3_VLD(baseAddr, regionNum));
}

/*!
 * @brief Sets  the region valid value
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param validValue Region valid value
 */
static inline void MPU_HAL_SetRegionValidValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_region_valid validValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD3_COUNT);
    BW_MPU_RGDn_WORD3_VLD(baseAddr, regionNum, validValue);
}

/*!
 * @brief Gets the process identifier mask
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval region process identifier mask
 */
static inline uint8_t MPU_HAL_GetProcessIdentifierMask(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD3_COUNT);
    return (BR_MPU_RGDn_WORD3_PIDMASK(baseAddr, regionNum));
}

/*!
 * @brief Sets the process identifier mask
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param processIdentifierMask Process identifier mask value
 */
static inline void MPU_HAL_SetPIDMASK(uint32_t baseAddr, mpu_region_num regionNum, uint8_t processIdentifierMask)
{
    assert(regionNum < HW_MPU_RGDn_WORD3_COUNT);
    BW_MPU_RGDn_WORD3_PIDMASK(baseAddr, regionNum, processIdentifierMask);
}

/*!
 * @brief Gets the process identifier
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval process identifier
 */
static inline uint8_t MPU_HAL_GetProcessIdentifier(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD3_COUNT);
    return (BR_MPU_RGDn_WORD3_PID(baseAddr, regionNum));
}

/*!
 * @brief Sets the process identifier
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param processIdentifier Process identifier
 */
static inline void MPU_HAL_SetProcessIdentifier(uint32_t baseAddr, mpu_region_num regionNum, uint8_t processIdentifier)
{
    assert(regionNum < HW_MPU_RGDn_WORD3_COUNT);
    BW_MPU_RGDn_WORD3_PID(baseAddr, regionNum, processIdentifier);
}

/*!
 * @brief Gets all masters access permission from alternative register
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval all masters access permission
 */
static inline uint32_t MPU_HAL_GetAllMastersAlternateAcessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (HW_MPU_RGDAACn_RD(baseAddr, regionNum));
}

/*!
 * @brief Sets all masters access permission through alternative register
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights All masters access permission
 */
static inline void MPU_HAL_SetAllMastersAlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, uint32_t accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    HW_MPU_RGDAACn_WR(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Gets the M0 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master0 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM0AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDAACn_M0SM(baseAddr, regionNum));
}

/*!
 * @brief Gets the M0 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master0 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM0AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_user_access_rights)(BR_MPU_RGDAACn_M0UM(baseAddr, regionNum));
}

/*!
 * @brief Sets the M0 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master0 access permission
 */
static inline void MPU_HAL_SetM0AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M0SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets the M0 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master0 access permission
 */
static inline void MPU_HAL_SetM0AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M0UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether the M0 process identifier works in region hit evaluation
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true m0 process identifier is enabled
 * @retval false m0 process identifier is disabled
 */
static inline bool MPU_HAL_IsM0AlternateProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDAACn_M0PE(baseAddr, regionNum));
}

/*!
 * @brief @brief Sets the M0 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param identifierValue Process identifier value
 */
static inline void MPU_HAL_SetM0AlternateProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDAACn_M0PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets M1 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master1 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM1AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDAACn_M1SM(baseAddr, regionNum));
}

/*!
 * @brief Gets M1 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval Master1 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM1AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_user_access_rights)(BR_MPU_RGDAACn_M1UM(baseAddr, regionNum));
}

/*!
 * @brief Sets M1 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master1 access permission
 */
static inline void MPU_HAL_SetM1AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M1SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets M1 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master1 access permission
 */
static inline void MPU_HAL_SetM1AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M1UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether the M1 process identifier works in region hit evaluation
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true m1 process identifier is enabled
 * @retval false m1 process identifier is disabled
 */
static inline bool MPU_HAL_IsM1AlternateProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDAACn_M1PE(baseAddr, regionNum));
}

/*!
 * @brief @brief Sets M1 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param identifierValue process identifier value
 */
static inline void MPU_HAL_SetM1AlternateProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDAACn_M1PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets M2 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval M2 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM2AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDAACn_M2SM(baseAddr, regionNum));
}

/*!
 * @brief Gets the M2 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval M2 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM2AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_user_access_rights)(BR_MPU_RGDAACn_M2UM(baseAddr, regionNum));
}

/*!
 * @brief Sets  M2 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights M2 access permission
 */
static inline void MPU_HAL_SetM2AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M2SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets M2 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights M2 access permission
 */
static inline void MPU_HAL_SetM2AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M2UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether the M2 process identifier works in region hit evaluation
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval true m2 process identifier is enabled
 * @retval false m2 process identifier is disabled
 */
static inline bool MPU_HAL_IsM2AlternateProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDAACn_M2PE(baseAddr, regionNum));
}

/*!
 * @brief Sets M2 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param identifierValue process identifier value
 */
static inline void MPU_HAL_SetM2AlternateProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDAACn_M2PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets  M3 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval M3 access permission
 */
static inline mpu_supervisor_access_rights MPU_HAL_GetM3AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_supervisor_access_rights)(BR_MPU_RGDAACn_M3SM(baseAddr, regionNum));
}

/*!
 * @brief Gets M3 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @retval M3 access permission
 */
static inline mpu_user_access_rights MPU_HAL_GetM3AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    return (mpu_user_access_rights)(BR_MPU_RGDAACn_M3UM(baseAddr, regionNum));
}

/*!
 * @brief Sets M3 access rights in supervisor mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master3 access permission
 */
static inline void MPU_HAL_SetM3AlternateSupervisorAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_supervisor_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M3SM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Sets M3 access rights in user mode
 *
 * @param baseAddr The MPU peripheral base address
 * @param regionNum MPU region number
 * @param accessRights Master3 access permission
 */
static inline void MPU_HAL_SetM3AlternateUserAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_user_access_rights accessRights)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    BW_MPU_RGDAACn_M3UM(baseAddr, regionNum, accessRights);
}

/*!
 * @brief Checks whether the  M3 process identifier works in region hit evaluation.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @retval true m3 process identifier is enabled.
 * @retval false m3 process identifier is disabled.
 */
static inline bool MPU_HAL_IsM3AlternateProcessIdentifierEnabled(uint32_t baseAddr, mpu_region_num regionNum)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    return (1 == BR_MPU_RGDAACn_M3PE(baseAddr, regionNum));
}

/*!
 * @brief Sets M3 process identifier value--- 1 enable process identifier in region hit evaluation and 0 disable.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param identifierValue process identifier value.
 */
static inline void MPU_HAL_SetM3AlternateProcessIdentifierValue(uint32_t baseAddr, mpu_region_num regionNum, mpu_process_identifier_value identifierValue)
{
    assert(regionNum < HW_MPU_RGDn_WORD2_COUNT);
    BW_MPU_RGDAACn_M3PE(baseAddr, regionNum, identifierValue);
}

/*!
 * @brief Gets M4 access permission from alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @retval read or write permission.
 */
static inline mpu_access_control MPU_HAL_GetM4AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M4RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M4WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets M4 access permission through alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @param accessControl Access permission.
 */
static inline void MPU_HAL_SetM4AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        BW_MPU_RGDAACn_M4RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDAACn_M4WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Gets M5 access permission from alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @retval read or write permission.
 */
static inline mpu_access_control MPU_HAL_GetM5AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M5RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M5WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets M5 access permission through alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @param accessControl Master5 Access permission.
 */
static inline void MPU_HAL_SetM5AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        BW_MPU_RGDAACn_M5RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDAACn_M5WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Gets M6 access permission from alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @retval read or write permission.
 */
static inline mpu_access_control MPU_HAL_GetM6AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M6RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M6WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets M6 access permission through alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @param accessControl Master6 access permission.
 */
static inline void MPU_HAL_SetM6AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        BW_MPU_RGDAACn_M6RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDAACn_M6WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Gets M7 access permission from alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @retval read or write permission.
 */
static inline mpu_access_control MPU_HAL_GetM7AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M7RE(baseAddr, regionNum));
    }
    else
    {
        return (mpu_access_control)(BR_MPU_RGDAACn_M7WE(baseAddr, regionNum));
    }
}

/*!
 * @brief Sets M7 access permission through alternate register.
 *
 * @param baseAddr The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param accessType Access type Read/Write.
 * @param accessControl Master7 access permission.
 */
static inline void MPU_HAL_SetM7AlternateAccessRights(uint32_t baseAddr, mpu_region_num regionNum, mpu_access_type accessType, mpu_access_control accessControl)
{
    assert(regionNum < HW_MPU_RGDAACn_COUNT);
    if(kMPUAccessRead == accessType)
    {
        BW_MPU_RGDAACn_M7RE(baseAddr, regionNum, accessControl);
    }
    else
    {
        BW_MPU_RGDAACn_M7WE(baseAddr, regionNum, accessControl);
    }
}

/*!
 * @brief Initializes the MPU module.
 *
 * @param baseAddr The MPU peripheral base address.
 */
void MPU_HAL_Init(uint32_t baseAddr);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* MBED_NO_MPU */

#endif /* __FSL_MPU_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

