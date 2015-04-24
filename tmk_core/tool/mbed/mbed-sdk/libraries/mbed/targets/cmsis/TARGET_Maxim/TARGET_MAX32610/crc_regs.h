/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

#ifndef _MXC_CRC_REGS_H_
#define _MXC_CRC_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  crc_regs.h
 * @addtogroup crc CRC
 * @{
 */

/*                                             Offset   Register Description
                                               ======   ======================================================= */
typedef struct {
    __IO uint32_t reseed;                  /*  0x0000   CRC-16/CRC-32 Reseed Controls                           */
    __IO uint32_t seed16;                  /*  0x0004   Reseed Value for CRC-16 Calculations                    */
    __IO uint32_t seed32;                  /*  0x0008   Reseed Value for CRC-32 Calculations                    */
} mxc_crc_regs_t;

/*                                             Offset   Register Description
                                               ======   ======================================================= */
typedef struct {
    __IO uint32_t value16[512];            /*  0x0000   Write Next CRC-16 Data Value / Read CRC-16 Result Value */
    __IO uint32_t value32[512];            /*  0x0800   Write Next CRC-32 Data Value / Read CRC-32 Result Value */
} mxc_crc_data_regs_t;

/*
   Register offsets for module CRC.
*/
#define MXC_R_CRC_OFFS_RESEED           ((uint32_t)0x00000000UL)
#define MXC_R_CRC_OFFS_SEED16           ((uint32_t)0x00000004UL)
#define MXC_R_CRC_OFFS_SEED32           ((uint32_t)0x00000008UL)
#define MXC_R_CRC_DATA_OFFS_VALUE16     ((uint32_t)0x00000000UL)
#define MXC_R_CRC_DATA_OFFS_VALUE32     ((uint32_t)0x00000800UL)

/*
   Field positions and masks for module CRC.
*/
#define MXC_F_CRC_RESEED_CRC16_POS      0
#define MXC_F_CRC_RESEED_CRC16          ((uint32_t)(0x00000001UL << MXC_F_CRC_RESEED_CRC16_POS))
#define MXC_F_CRC_RESEED_CRC32_POS      1
#define MXC_F_CRC_RESEED_CRC32          ((uint32_t)(0x00000001UL << MXC_F_CRC_RESEED_CRC32_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_CRC_REGS_H_ */
