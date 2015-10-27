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

#ifndef _MXC_TPU_REGS_H_
#define _MXC_TPU_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  tpu_regs.h
 * @addtogroup tpu TPU
 * @{
 */

/*                                               Offset   Register Description
                                                 ======   ================================================== */
typedef struct {
    __I uint32_t rsv0000;                    /*  0x0000   Reserved                                          */
    __I uint32_t rsv0004;                    /*  0x0004   Reserved - PUF Control (Deprecated)               */
    __I uint32_t rsv0008;                    /*  0x0008   Reserved - PUF Output (Deprecated)                */
    __I uint32_t rsv000C[125];               /*  0x000C                                                     */
    __IO uint32_t prng_user_entropy;         /*  0x0200   PRNG User Entropy Value                           */
    __IO uint32_t prng_rnd_num;              /*  0x0204   PRNG Random Number Output                         */
} mxc_tpu_regs_t;

/*                                               Offset   Register Description
                                                 ======   ================================================= */
typedef struct {
    __IO uint32_t status;                    /*  0x0000   Dynamic Tamper Sensor Status                      */
    __IO uint32_t ctrl0;                     /*  0x0004   Dynamic Tamper Sensor Control 0                   */
    __IO uint32_t ctrl1;                     /*  0x0008   Dynamic Tamper Sensor Control 1                   */
    __IO uint32_t sks0;                      /*  0x0010   TPU Secure Key Storage Register 0                 */
    __IO uint32_t sks1;                      /*  0x0014   TPU Secure Key Storage Register 0                 */
    __IO uint32_t sks2;                      /*  0x0018   TPU Secure Key Storage Register 0                 */
    __IO uint32_t sks3;                      /*  0x001C   TPU Secure Key Storage Register 0                 */
} mxc_tpu_tsr_regs_t;

/*
   Register offsets for module TPU.
*/
#define MXC_R_TPU_OFFS_PRNG_USER_ENTROPY    ((uint32_t)0x00000200UL)
#define MXC_R_TPU_OFFS_PRNG_RND_NUM         ((uint32_t)0x00000204UL)
#define MXC_R_TPU_TSR_OFFS_STATUS           ((uint32_t)0x00000000UL)
#define MXC_R_TPU_TSR_OFFS_CTRL0            ((uint32_t)0x00000004UL)
#define MXC_R_TPU_TSR_OFFS_CTRL1            ((uint32_t)0x00000008UL)
#define MXC_R_TPU_TSR_OFFS_SKS0             ((uint32_t)0x00000010UL)
#define MXC_R_TPU_TSR_OFFS_SKS1             ((uint32_t)0x00000014UL)
#define MXC_R_TPU_TSR_OFFS_SKS2             ((uint32_t)0x00000018UL)
#define MXC_R_TPU_TSR_OFFS_SKS3             ((uint32_t)0x0000001CUL)


/*
   Field positions and masks for module TPU.
*/
#define MXC_F_TPU_CTRL0_ERR_THR_POS         0
#define MXC_F_TPU_CTRL0_ERR_THR             ((uint32_t)(0x0000001FUL << MXC_F_TPU_CTRL0_ERR_THR_POS))
#define MXC_F_TPU_CTRL0_OUT_FREQ_POS        5
#define MXC_F_TPU_CTRL0_OUT_FREQ            ((uint32_t)(0x00000007UL << MXC_F_TPU_CTRL0_OUT_FREQ_POS))
#define MXC_F_TPU_CTRL0_CLOCK_DIV_POS       8
#define MXC_F_TPU_CTRL0_CLOCK_DIV           ((uint32_t)(0x00000007UL << MXC_F_TPU_CTRL0_CLOCK_DIV_POS))
#define MXC_F_TPU_CTRL0_RTC_TX_BUSY_POS     14
#define MXC_F_TPU_CTRL0_RTC_TX_BUSY         ((uint32_t)(0x00000001UL << MXC_F_TPU_CTRL0_RTC_TX_BUSY_POS))
#define MXC_F_TPU_CTRL0_LOCK_POS            15
#define MXC_F_TPU_CTRL0_LOCK                ((uint32_t)(0x00000001UL << MXC_F_TPU_CTRL0_LOCK_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_TPU_REGS_H_ */
