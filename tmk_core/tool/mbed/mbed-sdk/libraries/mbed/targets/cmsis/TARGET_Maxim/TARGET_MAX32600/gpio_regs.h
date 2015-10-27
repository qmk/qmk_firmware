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

#ifndef _MXC_GPIO_REGS_H_
#define _MXC_GPIO_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  gpio_regs.h
 * @addtogroup gpio GPIO
 * @{
 */

/*                                             Offset          Register Description
                                            =============   ========================================== */
typedef struct {
    __I uint32_t rsv000[16];            /*  0x0000-0x003C                                              */

    __IO uint32_t free[8];              /*  0x0040-0x005C   Port P[0..7] Free for GPIO Operation Flags */
    __I uint32_t rsv060[8];             /*  0x0060-0x007C                                              */

    __IO uint32_t out_mode[8];          /*  0x0080-0x009C   Port P[0..7] GPIO Output Drive Mode        */
    __I uint32_t rsv0A0[8];             /*  0x00A0-0x00BC                                              */

    __IO uint32_t out_val[8];           /*  0x00C0-0x00DC   Port P[0..7] GPIO Output Value             */
    __I uint32_t rsv0E0[8];             /*  0x00E0-0x00FC                                              */

    __IO uint32_t func_sel[8];          /*  0x0100-0x011C   Port P[0..7] GPIO Function Select          */
    __I uint32_t rsv120[8];             /*  0x0120-0x013C                                              */

    __IO uint32_t in_mode[8];           /*  0x0140-0x015C   Port P[0..7] GPIO Input Monitoring Mode    */
    __I uint32_t rsv160[8];             /*  0x0160-0x017C                                              */

    __IO uint32_t in_val[8];            /*  0x0180-0x019C   Port P[0..7] GPIO Input Value              */
    __I uint32_t rsv1A0[8];             /*  0x01A0-0x01BC                                              */

    __IO uint32_t int_mode[8];          /*  0x01C0-0x01DC   Port P[0..7] Interrupt Detection Mode      */
    __I uint32_t rsv1E0[8];             /*  0x01E0-0x01FC                                              */

    __IO uint32_t intfl[8];             /*  0x0200-0x021C   Port P[0..7] Interrupt Flags               */
    __I uint32_t rsv220[8];             /*  0x0220-0x023C                                              */

    __IO uint32_t inten[8];             /*  0x0240-0x025C   Port P[0..7] Interrupt Enables             */
} mxc_gpio_regs_t;

/*
   Register offsets for module GPIO.
*/
#define MXC_R_GPIO_OFFS_FREE_P0                   ((uint32_t)0x00000040UL)
#define MXC_R_GPIO_OFFS_FREE_P1                   ((uint32_t)0x00000044UL)
#define MXC_R_GPIO_OFFS_FREE_P2                   ((uint32_t)0x00000048UL)
#define MXC_R_GPIO_OFFS_FREE_P3                   ((uint32_t)0x0000004CUL)
#define MXC_R_GPIO_OFFS_FREE_P4                   ((uint32_t)0x00000050UL)
#define MXC_R_GPIO_OFFS_FREE_P5                   ((uint32_t)0x00000054UL)
#define MXC_R_GPIO_OFFS_FREE_P6                   ((uint32_t)0x00000058UL)
#define MXC_R_GPIO_OFFS_FREE_P7                   ((uint32_t)0x0000005CUL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P0               ((uint32_t)0x00000080UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P1               ((uint32_t)0x00000084UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P2               ((uint32_t)0x00000088UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P3               ((uint32_t)0x0000008CUL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P4               ((uint32_t)0x00000090UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P5               ((uint32_t)0x00000094UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P6               ((uint32_t)0x00000098UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P7               ((uint32_t)0x0000009CUL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P0                ((uint32_t)0x000000C0UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P1                ((uint32_t)0x000000C4UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P2                ((uint32_t)0x000000C8UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P3                ((uint32_t)0x000000CCUL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P4                ((uint32_t)0x000000D0UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P5                ((uint32_t)0x000000D4UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P6                ((uint32_t)0x000000D8UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P7                ((uint32_t)0x000000DCUL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P0               ((uint32_t)0x00000100UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P1               ((uint32_t)0x00000104UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P2               ((uint32_t)0x00000108UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P6               ((uint32_t)0x00000118UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P7               ((uint32_t)0x0000011CUL)
#define MXC_R_GPIO_OFFS_IN_MODE_P0                ((uint32_t)0x00000140UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P1                ((uint32_t)0x00000144UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P2                ((uint32_t)0x00000148UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P3                ((uint32_t)0x0000014CUL)
#define MXC_R_GPIO_OFFS_IN_MODE_P4                ((uint32_t)0x00000150UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P5                ((uint32_t)0x00000154UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P6                ((uint32_t)0x00000158UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P7                ((uint32_t)0x0000015CUL)
#define MXC_R_GPIO_OFFS_IN_VAL_P0                 ((uint32_t)0x00000180UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P1                 ((uint32_t)0x00000184UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P2                 ((uint32_t)0x00000188UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P3                 ((uint32_t)0x0000018CUL)
#define MXC_R_GPIO_OFFS_IN_VAL_P4                 ((uint32_t)0x00000190UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P5                 ((uint32_t)0x00000194UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P6                 ((uint32_t)0x00000198UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P7                 ((uint32_t)0x0000019CUL)
#define MXC_R_GPIO_OFFS_INT_MODE_P0               ((uint32_t)0x000001C0UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P1               ((uint32_t)0x000001C4UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P2               ((uint32_t)0x000001C8UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P3               ((uint32_t)0x000001CCUL)
#define MXC_R_GPIO_OFFS_INT_MODE_P4               ((uint32_t)0x000001D0UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P5               ((uint32_t)0x000001D4UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P6               ((uint32_t)0x000001D8UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P7               ((uint32_t)0x000001DCUL)
#define MXC_R_GPIO_OFFS_INTFL_P0                  ((uint32_t)0x00000200UL)
#define MXC_R_GPIO_OFFS_INTFL_P1                  ((uint32_t)0x00000204UL)
#define MXC_R_GPIO_OFFS_INTFL_P2                  ((uint32_t)0x00000208UL)
#define MXC_R_GPIO_OFFS_INTFL_P3                  ((uint32_t)0x0000020CUL)
#define MXC_R_GPIO_OFFS_INTFL_P4                  ((uint32_t)0x00000210UL)
#define MXC_R_GPIO_OFFS_INTFL_P5                  ((uint32_t)0x00000214UL)
#define MXC_R_GPIO_OFFS_INTFL_P6                  ((uint32_t)0x00000218UL)
#define MXC_R_GPIO_OFFS_INTFL_P7                  ((uint32_t)0x0000021CUL)
#define MXC_R_GPIO_OFFS_INTEN_P0                  ((uint32_t)0x00000240UL)
#define MXC_R_GPIO_OFFS_INTEN_P1                  ((uint32_t)0x00000244UL)
#define MXC_R_GPIO_OFFS_INTEN_P2                  ((uint32_t)0x00000248UL)
#define MXC_R_GPIO_OFFS_INTEN_P3                  ((uint32_t)0x0000024CUL)
#define MXC_R_GPIO_OFFS_INTEN_P4                  ((uint32_t)0x00000250UL)
#define MXC_R_GPIO_OFFS_INTEN_P5                  ((uint32_t)0x00000254UL)
#define MXC_R_GPIO_OFFS_INTEN_P6                  ((uint32_t)0x00000258UL)
#define MXC_R_GPIO_OFFS_INTEN_P7                  ((uint32_t)0x0000025CUL)


/*
   Field positions and masks for module GPIO.
*/
#define MXC_F_GPIO_FREE_PIN0_POS                             0
#define MXC_F_GPIO_FREE_PIN0                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN0_POS))
#define MXC_F_GPIO_FREE_PIN1_POS                             1
#define MXC_F_GPIO_FREE_PIN1                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN1_POS))
#define MXC_F_GPIO_FREE_PIN2_POS                             2
#define MXC_F_GPIO_FREE_PIN2                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN2_POS))
#define MXC_F_GPIO_FREE_PIN3_POS                             3
#define MXC_F_GPIO_FREE_PIN3                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN3_POS))
#define MXC_F_GPIO_FREE_PIN4_POS                             4
#define MXC_F_GPIO_FREE_PIN4                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN4_POS))
#define MXC_F_GPIO_FREE_PIN5_POS                             5
#define MXC_F_GPIO_FREE_PIN5                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN5_POS))
#define MXC_F_GPIO_FREE_PIN6_POS                             6
#define MXC_F_GPIO_FREE_PIN6                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN6_POS))
#define MXC_F_GPIO_FREE_PIN7_POS                             7
#define MXC_F_GPIO_FREE_PIN7                                ((uint32_t)(0x00000001UL << MXC_F_GPIO_FREE_PIN7_POS))

#define MXC_F_GPIO_OUT_MODE_PIN0_POS                         0
#define MXC_F_GPIO_OUT_MODE_PIN0                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_F_GPIO_OUT_MODE_PIN1_POS                         4
#define MXC_F_GPIO_OUT_MODE_PIN1                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_F_GPIO_OUT_MODE_PIN2_POS                         8
#define MXC_F_GPIO_OUT_MODE_PIN2                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_F_GPIO_OUT_MODE_PIN3_POS                        12
#define MXC_F_GPIO_OUT_MODE_PIN3                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_F_GPIO_OUT_MODE_PIN4_POS                        16
#define MXC_F_GPIO_OUT_MODE_PIN4                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_F_GPIO_OUT_MODE_PIN5_POS                        20
#define MXC_F_GPIO_OUT_MODE_PIN5                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_F_GPIO_OUT_MODE_PIN6_POS                        24
#define MXC_F_GPIO_OUT_MODE_PIN6                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_F_GPIO_OUT_MODE_PIN7_POS                        28
#define MXC_F_GPIO_OUT_MODE_PIN7                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_OUT_MODE_PIN7_POS))

#define MXC_F_GPIO_OUT_VAL_PIN0_POS                          0
#define MXC_F_GPIO_OUT_VAL_PIN0                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN0_POS))
#define MXC_F_GPIO_OUT_VAL_PIN1_POS                          1
#define MXC_F_GPIO_OUT_VAL_PIN1                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN1_POS))
#define MXC_F_GPIO_OUT_VAL_PIN2_POS                          2
#define MXC_F_GPIO_OUT_VAL_PIN2                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN2_POS))
#define MXC_F_GPIO_OUT_VAL_PIN3_POS                          3
#define MXC_F_GPIO_OUT_VAL_PIN3                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN3_POS))
#define MXC_F_GPIO_OUT_VAL_PIN4_POS                          4
#define MXC_F_GPIO_OUT_VAL_PIN4                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN4_POS))
#define MXC_F_GPIO_OUT_VAL_PIN5_POS                          5
#define MXC_F_GPIO_OUT_VAL_PIN5                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN5_POS))
#define MXC_F_GPIO_OUT_VAL_PIN6_POS                          6
#define MXC_F_GPIO_OUT_VAL_PIN6                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN6_POS))
#define MXC_F_GPIO_OUT_VAL_PIN7_POS                          7
#define MXC_F_GPIO_OUT_VAL_PIN7                             ((uint32_t)(0x00000001UL << MXC_F_GPIO_OUT_VAL_PIN7_POS))

#define MXC_F_GPIO_FUNC_SEL_PIN0_POS                         0
#define MXC_F_GPIO_FUNC_SEL_PIN0                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN0_POS))
#define MXC_F_GPIO_FUNC_SEL_PIN1_POS                         4
#define MXC_F_GPIO_FUNC_SEL_PIN1                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN1_POS))
#define MXC_F_GPIO_FUNC_SEL_PIN2_POS                         8
#define MXC_F_GPIO_FUNC_SEL_PIN2                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN2_POS))
#define MXC_F_GPIO_FUNC_SEL_PIN3_POS                        12
#define MXC_F_GPIO_FUNC_SEL_PIN3                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN3_POS))
#define MXC_F_GPIO_FUNC_SEL_PIN4_POS                        16
#define MXC_F_GPIO_FUNC_SEL_PIN4                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN4_POS))
#define MXC_F_GPIO_FUNC_SEL_PIN5_POS                        20
#define MXC_F_GPIO_FUNC_SEL_PIN5                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN5_POS))
#define MXC_F_GPIO_FUNC_SEL_PIN6_POS                        24
#define MXC_F_GPIO_FUNC_SEL_PIN6                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN6_POS))
#define MXC_F_GPIO_FUNC_SEL_PIN7_POS                        28
#define MXC_F_GPIO_FUNC_SEL_PIN7                            ((uint32_t)(0x0000000FUL << MXC_F_GPIO_FUNC_SEL_PIN7_POS))

#define MXC_F_GPIO_IN_MODE_PIN0_POS                          0
#define MXC_F_GPIO_IN_MODE_PIN0                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN0_POS))
#define MXC_F_GPIO_IN_MODE_PIN1_POS                          4
#define MXC_F_GPIO_IN_MODE_PIN1                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN1_POS))
#define MXC_F_GPIO_IN_MODE_PIN2_POS                          8
#define MXC_F_GPIO_IN_MODE_PIN2                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN2_POS))
#define MXC_F_GPIO_IN_MODE_PIN3_POS                         12
#define MXC_F_GPIO_IN_MODE_PIN3                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN3_POS))
#define MXC_F_GPIO_IN_MODE_PIN4_POS                         16
#define MXC_F_GPIO_IN_MODE_PIN4                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN4_POS))
#define MXC_F_GPIO_IN_MODE_PIN5_POS                         20
#define MXC_F_GPIO_IN_MODE_PIN5                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN5_POS))
#define MXC_F_GPIO_IN_MODE_PIN6_POS                         24
#define MXC_F_GPIO_IN_MODE_PIN6                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN6_POS))
#define MXC_F_GPIO_IN_MODE_PIN7_POS                         28
#define MXC_F_GPIO_IN_MODE_PIN7                             ((uint32_t)(0x00000003UL << MXC_F_GPIO_IN_MODE_PIN7_POS))

#define MXC_F_GPIO_IN_VAL_PIN0_POS                           0
#define MXC_F_GPIO_IN_VAL_PIN0                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN0_POS))
#define MXC_F_GPIO_IN_VAL_PIN1_POS                           1
#define MXC_F_GPIO_IN_VAL_PIN1                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN1_POS))
#define MXC_F_GPIO_IN_VAL_PIN2_POS                           2
#define MXC_F_GPIO_IN_VAL_PIN2                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN2_POS))
#define MXC_F_GPIO_IN_VAL_PIN3_POS                           3
#define MXC_F_GPIO_IN_VAL_PIN3                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN3_POS))
#define MXC_F_GPIO_IN_VAL_PIN4_POS                           4
#define MXC_F_GPIO_IN_VAL_PIN4                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN4_POS))
#define MXC_F_GPIO_IN_VAL_PIN5_POS                           5
#define MXC_F_GPIO_IN_VAL_PIN5                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN5_POS))
#define MXC_F_GPIO_IN_VAL_PIN6_POS                           6
#define MXC_F_GPIO_IN_VAL_PIN6                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN6_POS))
#define MXC_F_GPIO_IN_VAL_PIN7_POS                           7
#define MXC_F_GPIO_IN_VAL_PIN7                              ((uint32_t)(0x00000001UL << MXC_F_GPIO_IN_VAL_PIN7_POS))

#define MXC_F_GPIO_INT_MODE_PIN0_POS                         0
#define MXC_F_GPIO_INT_MODE_PIN0                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN0_POS))
#define MXC_F_GPIO_INT_MODE_PIN1_POS                         4
#define MXC_F_GPIO_INT_MODE_PIN1                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN1_POS))
#define MXC_F_GPIO_INT_MODE_PIN2_POS                         8
#define MXC_F_GPIO_INT_MODE_PIN2                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN2_POS))
#define MXC_F_GPIO_INT_MODE_PIN3_POS                        12
#define MXC_F_GPIO_INT_MODE_PIN3                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN3_POS))
#define MXC_F_GPIO_INT_MODE_PIN4_POS                        16
#define MXC_F_GPIO_INT_MODE_PIN4                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN4_POS))
#define MXC_F_GPIO_INT_MODE_PIN5_POS                        20
#define MXC_F_GPIO_INT_MODE_PIN5                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN5_POS))
#define MXC_F_GPIO_INT_MODE_PIN6_POS                        24
#define MXC_F_GPIO_INT_MODE_PIN6                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN6_POS))
#define MXC_F_GPIO_INT_MODE_PIN7_POS                        28
#define MXC_F_GPIO_INT_MODE_PIN7                            ((uint32_t)(0x00000007UL << MXC_F_GPIO_INT_MODE_PIN7_POS))

#define MXC_F_GPIO_INTFL_PIN0_POS                            0
#define MXC_F_GPIO_INTFL_PIN0                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN0_POS))
#define MXC_F_GPIO_INTFL_PIN1_POS                            1
#define MXC_F_GPIO_INTFL_PIN1                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN1_POS))
#define MXC_F_GPIO_INTFL_PIN2_POS                            2
#define MXC_F_GPIO_INTFL_PIN2                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN2_POS))
#define MXC_F_GPIO_INTFL_PIN3_POS                            3
#define MXC_F_GPIO_INTFL_PIN3                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN3_POS))
#define MXC_F_GPIO_INTFL_PIN4_POS                            4
#define MXC_F_GPIO_INTFL_PIN4                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN4_POS))
#define MXC_F_GPIO_INTFL_PIN5_POS                            5
#define MXC_F_GPIO_INTFL_PIN5                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN5_POS))
#define MXC_F_GPIO_INTFL_PIN6_POS                            6
#define MXC_F_GPIO_INTFL_PIN6                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN6_POS))
#define MXC_F_GPIO_INTFL_PIN7_POS                            7
#define MXC_F_GPIO_INTFL_PIN7                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTFL_PIN7_POS))

#define MXC_F_GPIO_INTEN_PIN0_POS                            0
#define MXC_F_GPIO_INTEN_PIN0                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN0_POS))
#define MXC_F_GPIO_INTEN_PIN1_POS                            1
#define MXC_F_GPIO_INTEN_PIN1                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN1_POS))
#define MXC_F_GPIO_INTEN_PIN2_POS                            2
#define MXC_F_GPIO_INTEN_PIN2                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN2_POS))
#define MXC_F_GPIO_INTEN_PIN3_POS                            3
#define MXC_F_GPIO_INTEN_PIN3                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN3_POS))
#define MXC_F_GPIO_INTEN_PIN4_POS                            4
#define MXC_F_GPIO_INTEN_PIN4                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN4_POS))
#define MXC_F_GPIO_INTEN_PIN5_POS                            5
#define MXC_F_GPIO_INTEN_PIN5                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN5_POS))
#define MXC_F_GPIO_INTEN_PIN6_POS                            6
#define MXC_F_GPIO_INTEN_PIN6                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN6_POS))
#define MXC_F_GPIO_INTEN_PIN7_POS                            7
#define MXC_F_GPIO_INTEN_PIN7                               ((uint32_t)(0x00000001UL << MXC_F_GPIO_INTEN_PIN7_POS))


/*
   Field values and shifted values for module GPIO.
*/
#define MXC_V_GPIO_FREE_PIN0_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN0_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN0_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN0_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN0_POS))
#define MXC_S_GPIO_FREE_PIN0_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN0_AVAILABLE      << MXC_F_GPIO_FREE_PIN0_POS))

#define MXC_V_GPIO_FREE_PIN1_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN1_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN1_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN1_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN1_POS))
#define MXC_S_GPIO_FREE_PIN1_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN1_AVAILABLE      << MXC_F_GPIO_FREE_PIN1_POS))

#define MXC_V_GPIO_FREE_PIN2_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN2_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN2_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN2_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN2_POS))
#define MXC_S_GPIO_FREE_PIN2_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN2_AVAILABLE      << MXC_F_GPIO_FREE_PIN2_POS))

#define MXC_V_GPIO_FREE_PIN3_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN3_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN3_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN3_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN3_POS))
#define MXC_S_GPIO_FREE_PIN3_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN3_AVAILABLE      << MXC_F_GPIO_FREE_PIN3_POS))

#define MXC_V_GPIO_FREE_PIN4_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN4_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN4_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN4_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN4_POS))
#define MXC_S_GPIO_FREE_PIN4_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN4_AVAILABLE      << MXC_F_GPIO_FREE_PIN4_POS))

#define MXC_V_GPIO_FREE_PIN5_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN5_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN5_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN5_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN5_POS))
#define MXC_S_GPIO_FREE_PIN5_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN5_AVAILABLE      << MXC_F_GPIO_FREE_PIN5_POS))

#define MXC_V_GPIO_FREE_PIN6_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN6_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN6_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN6_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN6_POS))
#define MXC_S_GPIO_FREE_PIN6_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN6_AVAILABLE      << MXC_F_GPIO_FREE_PIN6_POS))

#define MXC_V_GPIO_FREE_PIN7_NOT_AVAILABLE                                      ((uint32_t)(0x0x00000000UL))
#define MXC_V_GPIO_FREE_PIN7_AVAILABLE                                          ((uint32_t)(0x0x00000001UL))

#define MXC_S_GPIO_FREE_PIN7_NOT_AVAILABLE                                      ((uint32_t)(MXC_V_GPIO_FREE_PIN7_NOT_AVAILABLE  << MXC_F_GPIO_FREE_PIN7_POS))
#define MXC_S_GPIO_FREE_PIN7_AVAILABLE                                          ((uint32_t)(MXC_V_GPIO_FREE_PIN7_AVAILABLE      << MXC_F_GPIO_FREE_PIN7_POS))

#define MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP                                  ((uint32_t)(0x00000000UL))
#define MXC_V_GPIO_OUT_MODE_OPEN_DRAIN                                          ((uint32_t)(0x00000001UL))
#define MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP                              ((uint32_t)(0x00000002UL))
#define MXC_V_GPIO_OUT_MODE_HIGH_Z                                              ((uint32_t)(0x00000003UL))
#define MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z                                       ((uint32_t)(0x00000004UL))
#define MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE                                        ((uint32_t)(0x00000005UL))
#define MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z                                         ((uint32_t)(0x00000006UL))
#define MXC_V_GPIO_OUT_MODE_SLOW_DRIVE                                          ((uint32_t)(0x00000007UL))
#define MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z                                         ((uint32_t)(0x00000008UL))
#define MXC_V_GPIO_OUT_MODE_FAST_DRIVE                                          ((uint32_t)(0x00000009UL))

#define MXC_S_GPIO_OUT_MODE_PIN0_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN0_POS))
#define MXC_S_GPIO_OUT_MODE_PIN0_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN0_POS))

#define MXC_S_GPIO_OUT_MODE_PIN1_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN1_POS))
#define MXC_S_GPIO_OUT_MODE_PIN1_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN1_POS))

#define MXC_S_GPIO_OUT_MODE_PIN2_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN2_POS))
#define MXC_S_GPIO_OUT_MODE_PIN2_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN2_POS))

#define MXC_S_GPIO_OUT_MODE_PIN3_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN3_POS))
#define MXC_S_GPIO_OUT_MODE_PIN3_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN3_POS))

#define MXC_S_GPIO_OUT_MODE_PIN4_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN4_POS))
#define MXC_S_GPIO_OUT_MODE_PIN4_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN4_POS))

#define MXC_S_GPIO_OUT_MODE_PIN5_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN5_POS))
#define MXC_S_GPIO_OUT_MODE_PIN5_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN5_POS))

#define MXC_S_GPIO_OUT_MODE_PIN6_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN6_POS))
#define MXC_S_GPIO_OUT_MODE_PIN6_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN6_POS))

#define MXC_S_GPIO_OUT_MODE_PIN7_HIGH_Z_WEAK_PULLUP                             ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z_WEAK_PULLUP      << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_OPEN_DRAIN                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN              << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_OPEN_DRAIN_WEAK_PULLUP                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_OPEN_DRAIN_WEAK_PULLUP  << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_HIGH_Z                                         ((uint32_t)(MXC_V_GPIO_OUT_MODE_HIGH_Z                  << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_NORMAL_HIGH_Z                                  ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_HIGH_Z           << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_NORMAL_DRIVE                                   ((uint32_t)(MXC_V_GPIO_OUT_MODE_NORMAL_DRIVE            << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_SLOW_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_SLOW_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_SLOW_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_FAST_HIGH_Z                                    ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_HIGH_Z             << MXC_F_GPIO_OUT_MODE_PIN7_POS))
#define MXC_S_GPIO_OUT_MODE_PIN7_FAST_DRIVE                                     ((uint32_t)(MXC_V_GPIO_OUT_MODE_FAST_DRIVE              << MXC_F_GPIO_OUT_MODE_PIN7_POS))

#define MXC_V_GPIO_INT_MODE_DISABLED                                            ((uint32_t)(0x00000000UL))
#define MXC_V_GPIO_INT_MODE_FALLING_EDGE                                        ((uint32_t)(0x00000001UL))
#define MXC_V_GPIO_INT_MODE_RISING_EDGE                                         ((uint32_t)(0x00000002UL))
#define MXC_V_GPIO_INT_MODE_BOTH_EDGES                                          ((uint32_t)(0x00000003UL))
#define MXC_V_GPIO_INT_MODE_LOW_LEVEL                                           ((uint32_t)(0x00000004UL))
#define MXC_V_GPIO_INT_MODE_HIGH_LEVEL                                          ((uint32_t)(0x00000005UL))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* _MXC_GPIO_REGS_H_ */
