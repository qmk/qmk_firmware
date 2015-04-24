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

#ifndef _MXC_IOMAN_REGS_H_
#define _MXC_IOMAN_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  ioman_regs.h
 * @addtogroup ioman IO MUX Manager
 * @{
 */

typedef enum {
    /** Pin Mapping 'A' */
    MXC_E_IOMAN_MAPPING_A = 0,
    /** Pin Mapping 'B' */
    MXC_E_IOMAN_MAPPING_B,
    /** Pin Mapping 'C' */
    MXC_E_IOMAN_MAPPING_C,
    /** Pin Mapping 'D' */
    MXC_E_IOMAN_MAPPING_D,
    /** Pin Mapping 'E' */
    MXC_E_IOMAN_MAPPING_E,
    /** Pin Mapping 'F' */
    MXC_E_IOMAN_MAPPING_F,
    /** Pin Mapping 'G' */
    MXC_E_IOMAN_MAPPING_G,
    /** Pin Mapping 'H' */
    MXC_E_IOMAN_MAPPING_H,
} ioman_mapping_t;

/*                                      Offset   Register Description
                                        ======   ========================================== */
typedef struct {
    __IO uint32_t wud_req0;         /*  0x0000   Wakeup Detect Mode Request Register 0      */
    __IO uint32_t wud_req1;         /*  0x0004   Wakeup Detect Mode Request Register 1      */
    __IO uint32_t wud_ack0;         /*  0x0008   Wakeup Detect Mode Acknowledge Register 0  */
    __IO uint32_t wud_ack1;         /*  0x000C   Wakeup Detect Mode Acknowledge Register 1  */
    __IO uint32_t ali_req0;         /*  0x0010   Analog Input Request Register 0            */
    __IO uint32_t ali_req1;         /*  0x0014   Analog Input Request Register 1            */
    __IO uint32_t ali_ack0;         /*  0x0018   Analog Input Acknowledge Register 0        */
    __IO uint32_t ali_ack1;         /*  0x001C   Analog Input Acknowledge Register 1        */
    __IO uint32_t spi0_req;         /*  0x0020   SPI0 I/O Mode Request                      */
    __IO uint32_t spi0_ack;         /*  0x0024   SPI0 I/O Mode Acknowledge                  */
    __IO uint32_t spi1_req;         /*  0x0028   SPI1 I/O Mode Request                      */
    __IO uint32_t spi1_ack;         /*  0x002C   SPI1 I/O Mode Acknowledge                  */
    __IO uint32_t spi2_req;         /*  0x0030   SPI2 I/O Mode Request                      */
    __IO uint32_t spi2_ack;         /*  0x0034   SPI2 I/O Mode Acknowledge                  */
    __IO uint32_t uart0_req;        /*  0x0038   UART0 I/O Mode Request                     */
    __IO uint32_t uart0_ack;        /*  0x003C   UART0 I/O Mode Acknowledge                 */
    __IO uint32_t uart1_req;        /*  0x0040   UART1 I/O Mode Request                     */
    __IO uint32_t uart1_ack;        /*  0x0044   UART1 I/O Mode Acknowledge                 */
    __IO uint32_t i2cm0_req;        /*  0x0048   I2C Master 0 I/O Request                   */
    __IO uint32_t i2cm0_ack;        /*  0x004C   I2C Master 0 I/O Acknowledge               */
    __IO uint32_t i2cs0_req;        /*  0x0050   I2C Slave 0 I/O Request                    */
    __IO uint32_t i2s0_ack;         /*  0x0054   I2C Slave 0 I/O Acknowledge                */
    __IO uint32_t lcd_com_req;      /*  0x0058   LCD COM Driver I/O Request                 */
    __IO uint32_t lcd_com_ack;      /*  0x005C   LCD COM Driver I/O Acknowledge             */
    __IO uint32_t lcd_seg_req0;     /*  0x0060   LCD SEG Driver I/O Request Register 0      */
    __IO uint32_t lcd_seg_req1;     /*  0x0064   LCD SEG Driver I/O Request Register 1      */
    __IO uint32_t lcd_seg_ack0;     /*  0x0068   LCD SEG Driver I/O Acknowledge Register 0  */
    __IO uint32_t lcd_seg_ack1;     /*  0x006C   LCD SEG Driver I/O Acknowledge Register 1  */
    __IO uint32_t crnt_req;         /*  0x0070   Current Drive I/O Request Register         */
    __IO uint32_t io_crnt_ack;      /*  0x0074   Current Drive I/O Acknowledge Register     */
    __IO uint32_t crnt_mode;        /*  0x0078   Current Drive I/O Mode Control             */
    __IO uint32_t ali_connect0;     /*  0x007C   Analog I/O Connection Control Register 0   */
    __IO uint32_t ali_connect1;     /*  0x0080   Analog I/O Connection Control Register 1   */
    __IO uint32_t i2cm1_req;        /*  0x0084   I2C Master 1 I/O Request                   */
    __IO uint32_t i2cm1_ack;        /*  0x0088   I2C Master 1 I/O Acknowledge               */
    __IO uint32_t padx_control;     /*  0x008C   PADX Control                               */
} mxc_ioman_regs_t;


/*
   Register offsets for module IOMAN.
*/
#define MXC_R_IOMAN_OFFS_WUD_REQ0                 ((uint32_t)0x00000000UL)
#define MXC_R_IOMAN_OFFS_WUD_REQ1                 ((uint32_t)0x00000004UL)
#define MXC_R_IOMAN_OFFS_WUD_ACK0                 ((uint32_t)0x00000008UL)
#define MXC_R_IOMAN_OFFS_WUD_ACK1                 ((uint32_t)0x0000000CUL)
#define MXC_R_IOMAN_OFFS_ALI_REQ0                 ((uint32_t)0x00000010UL)
#define MXC_R_IOMAN_OFFS_ALI_REQ1                 ((uint32_t)0x00000014UL)
#define MXC_R_IOMAN_OFFS_ALI_ACK0                 ((uint32_t)0x00000018UL)
#define MXC_R_IOMAN_OFFS_ALI_ACK1                 ((uint32_t)0x0000001CUL)
#define MXC_R_IOMAN_OFFS_SPI0_REQ                 ((uint32_t)0x00000020UL)
#define MXC_R_IOMAN_OFFS_SPI0_ACK                 ((uint32_t)0x00000024UL)
#define MXC_R_IOMAN_OFFS_SPI1_REQ                 ((uint32_t)0x00000028UL)
#define MXC_R_IOMAN_OFFS_SPI1_ACK                 ((uint32_t)0x0000002CUL)
#define MXC_R_IOMAN_OFFS_SPI2_REQ                 ((uint32_t)0x00000030UL)
#define MXC_R_IOMAN_OFFS_SPI2_ACK                 ((uint32_t)0x00000034UL)
#define MXC_R_IOMAN_OFFS_UART0_REQ                ((uint32_t)0x00000038UL)
#define MXC_R_IOMAN_OFFS_UART0_ACK                ((uint32_t)0x0000003CUL)
#define MXC_R_IOMAN_OFFS_UART1_REQ                ((uint32_t)0x00000040UL)
#define MXC_R_IOMAN_OFFS_UART1_ACK                ((uint32_t)0x00000044UL)
#define MXC_R_IOMAN_OFFS_I2CM0_REQ                ((uint32_t)0x00000048UL)
#define MXC_R_IOMAN_OFFS_I2CM0_ACK                ((uint32_t)0x0000004CUL)
#define MXC_R_IOMAN_OFFS_I2CS0_REQ                ((uint32_t)0x00000050UL)
#define MXC_R_IOMAN_OFFS_I2SC0_ACK                ((uint32_t)0x00000054UL)
#define MXC_R_IOMAN_OFFS_LCD_COM_REQ              ((uint32_t)0x00000058UL)
#define MXC_R_IOMAN_OFFS_LCD_COM_ACK              ((uint32_t)0x0000005CUL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_REQ0             ((uint32_t)0x00000060UL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_REQ1             ((uint32_t)0x00000064UL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_ACK0             ((uint32_t)0x00000068UL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_ACK1             ((uint32_t)0x0000006CUL)
#define MXC_R_IOMAN_OFFS_IO_CRNT_REQ              ((uint32_t)0x00000070UL)
#define MXC_R_IOMAN_OFFS_IO_CRNT_ACK              ((uint32_t)0x00000074UL)
#define MXC_R_IOMAN_OFFS_IO_CRNT_MODE             ((uint32_t)0x00000078UL)
#define MXC_R_IOMAN_OFFS_ALI_CONNECT0             ((uint32_t)0x0000007CUL)
#define MXC_R_IOMAN_OFFS_ALI_CONNECT1             ((uint32_t)0x00000080UL)
#define MXC_R_IOMAN_OFFS_I2CM1_REQ                ((uint32_t)0x00000084UL)
#define MXC_R_IOMAN_OFFS_I2CM1_ACK                ((uint32_t)0x00000088UL)
#define MXC_R_IOMAN_OFFS_PADX_CONTROL             ((uint32_t)0x0000008CUL)


/*
   Field positions and masks for module IOMAN.
*/
#define MXC_F_IOMAN_WUD_REQ0_PORT0_POS                      0
#define MXC_F_IOMAN_WUD_REQ0_PORT0                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ0_PORT0_POS))
#define MXC_F_IOMAN_WUD_REQ0_PORT1_POS                      8
#define MXC_F_IOMAN_WUD_REQ0_PORT1                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ0_PORT1_POS))
#define MXC_F_IOMAN_WUD_REQ0_PORT2_POS                      16
#define MXC_F_IOMAN_WUD_REQ0_PORT2                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ0_PORT2_POS))
#define MXC_F_IOMAN_WUD_REQ0_PORT3_POS                      24
#define MXC_F_IOMAN_WUD_REQ0_PORT3                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ0_PORT3_POS))

#define MXC_F_IOMAN_WUD_REQ1_PORT4_POS                      0
#define MXC_F_IOMAN_WUD_REQ1_PORT4                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ1_PORT4_POS))
#define MXC_F_IOMAN_WUD_REQ1_PORT5_POS                      8
#define MXC_F_IOMAN_WUD_REQ1_PORT5                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ1_PORT5_POS))
#define MXC_F_IOMAN_WUD_REQ1_PORT6_POS                      16
#define MXC_F_IOMAN_WUD_REQ1_PORT6                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ1_PORT6_POS))
#define MXC_F_IOMAN_WUD_REQ1_PORT7_POS                      24
#define MXC_F_IOMAN_WUD_REQ1_PORT7                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_REQ1_PORT7_POS))

#define MXC_F_IOMAN_WUD_ACK0_PORT0_POS                      0
#define MXC_F_IOMAN_WUD_ACK0_PORT0                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK0_PORT0_POS))
#define MXC_F_IOMAN_WUD_ACK0_PORT1_POS                      8
#define MXC_F_IOMAN_WUD_ACK0_PORT1                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK0_PORT1_POS))
#define MXC_F_IOMAN_WUD_ACK0_PORT2_POS                      16
#define MXC_F_IOMAN_WUD_ACK0_PORT2                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK0_PORT2_POS))
#define MXC_F_IOMAN_WUD_ACK0_PORT3_POS                      24
#define MXC_F_IOMAN_WUD_ACK0_PORT3                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK0_PORT3_POS))

#define MXC_F_IOMAN_WUD_ACK1_PORT4_POS                      0
#define MXC_F_IOMAN_WUD_ACK1_PORT4                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK1_PORT4_POS))
#define MXC_F_IOMAN_WUD_ACK1_PORT5_POS                      8
#define MXC_F_IOMAN_WUD_ACK1_PORT5                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK1_PORT5_POS))
#define MXC_F_IOMAN_WUD_ACK1_PORT6_POS                      16
#define MXC_F_IOMAN_WUD_ACK1_PORT6                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK1_PORT6_POS))
#define MXC_F_IOMAN_WUD_ACK1_PORT7_POS                      24
#define MXC_F_IOMAN_WUD_ACK1_PORT7                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_WUD_ACK1_PORT7_POS))

#define MXC_F_IOMAN_ALI_REQ0_PORT0_POS                      0
#define MXC_F_IOMAN_ALI_REQ0_PORT0                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ0_PORT0_POS))
#define MXC_F_IOMAN_ALI_REQ0_PORT1_POS                      8
#define MXC_F_IOMAN_ALI_REQ0_PORT1                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ0_PORT1_POS))
#define MXC_F_IOMAN_ALI_REQ0_PORT2_POS                      16
#define MXC_F_IOMAN_ALI_REQ0_PORT2                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ0_PORT2_POS))
#define MXC_F_IOMAN_ALI_REQ0_PORT3_POS                      24
#define MXC_F_IOMAN_ALI_REQ0_PORT3                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ0_PORT3_POS))

#define MXC_F_IOMAN_ALI_REQ1_PORT4_POS                      0
#define MXC_F_IOMAN_ALI_REQ1_PORT4                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ1_PORT4_POS))
#define MXC_F_IOMAN_ALI_REQ1_PORT5_POS                      8
#define MXC_F_IOMAN_ALI_REQ1_PORT5                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ1_PORT5_POS))
#define MXC_F_IOMAN_ALI_REQ1_PORT6_POS                      16
#define MXC_F_IOMAN_ALI_REQ1_PORT6                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ1_PORT6_POS))
#define MXC_F_IOMAN_ALI_REQ1_PORT7_POS                      24
#define MXC_F_IOMAN_ALI_REQ1_PORT7                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_REQ1_PORT7_POS))

#define MXC_F_IOMAN_ALI_ACK0_PORT0_POS                      0
#define MXC_F_IOMAN_ALI_ACK0_PORT0                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK0_PORT0_POS))
#define MXC_F_IOMAN_ALI_ACK0_PORT1_POS                      8
#define MXC_F_IOMAN_ALI_ACK0_PORT1                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK0_PORT1_POS))
#define MXC_F_IOMAN_ALI_ACK0_PORT2_POS                      16
#define MXC_F_IOMAN_ALI_ACK0_PORT2                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK0_PORT2_POS))
#define MXC_F_IOMAN_ALI_ACK0_PORT3_POS                      24
#define MXC_F_IOMAN_ALI_ACK0_PORT3                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK0_PORT3_POS))

#define MXC_F_IOMAN_ALI_ACK1_PORT4_POS                      0
#define MXC_F_IOMAN_ALI_ACK1_PORT4                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK1_PORT4_POS))
#define MXC_F_IOMAN_ALI_ACK1_PORT5_POS                      8
#define MXC_F_IOMAN_ALI_ACK1_PORT5                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK1_PORT5_POS))
#define MXC_F_IOMAN_ALI_ACK1_PORT6_POS                      16
#define MXC_F_IOMAN_ALI_ACK1_PORT6                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK1_PORT6_POS))
#define MXC_F_IOMAN_ALI_ACK1_PORT7_POS                      24
#define MXC_F_IOMAN_ALI_ACK1_PORT7                          ((uint32_t)(0x000000FFUL << MXC_F_IOMAN_ALI_ACK1_PORT7_POS))

#define MXC_F_IOMAN_SPI_MAPPING_POS                         0
#define MXC_F_IOMAN_SPI_MAPPING                             ((uint32_t)(0x00000003UL << MXC_F_IOMAN_SPI_MAPPING_POS))
#define MXC_F_IOMAN_SPI_CORE_IO_POS                         4
#define MXC_F_IOMAN_SPI_CORE_IO                             ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_CORE_IO_POS))
#define MXC_F_IOMAN_SPI_SS0_IO_POS                          8
#define MXC_F_IOMAN_SPI_SS0_IO                              ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_SS0_IO_POS))
#define MXC_F_IOMAN_SPI_SS1_IO_POS                          9
#define MXC_F_IOMAN_SPI_SS1_IO                              ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_SS1_IO_POS))
#define MXC_F_IOMAN_SPI_SS2_IO_POS                          10
#define MXC_F_IOMAN_SPI_SS2_IO                              ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_SS2_IO_POS))
#define MXC_F_IOMAN_SPI_SS3_IO_POS                          11
#define MXC_F_IOMAN_SPI_SS3_IO                              ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_SS3_IO_POS))
#define MXC_F_IOMAN_SPI_SS4_IO_POS                          12
#define MXC_F_IOMAN_SPI_SS4_IO                              ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_SS4_IO_POS))
#define MXC_F_IOMAN_SPI_SR0_IO_POS                          16
#define MXC_F_IOMAN_SPI_SR0_IO                              ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_SR0_IO_POS))
#define MXC_F_IOMAN_SPI_SR1_IO_POS                          17
#define MXC_F_IOMAN_SPI_SR1_IO                              ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_SR1_IO_POS))
#define MXC_F_IOMAN_SPI_QUAD_IO_POS                         20
#define MXC_F_IOMAN_SPI_QUAD_IO                             ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_QUAD_IO_POS))
#define MXC_F_IOMAN_SPI_FAST_MODE_POS                       24
#define MXC_F_IOMAN_SPI_FAST_MODE                           ((uint32_t)(0x00000001UL << MXC_F_IOMAN_SPI_FAST_MODE_POS))

#define MXC_F_IOMAN_UART_MAPPING_POS                        0
#define MXC_F_IOMAN_UART_MAPPING                            ((uint32_t)(0x00000003UL << MXC_F_IOMAN_UART_MAPPING_POS))
#define MXC_F_IOMAN_UART_CORE_IO_POS                        4
#define MXC_F_IOMAN_UART_CORE_IO                            ((uint32_t)(0x00000001UL << MXC_F_IOMAN_UART_CORE_IO_POS))
#define MXC_F_IOMAN_UART_CTS_IO_POS                         5
#define MXC_F_IOMAN_UART_CTS_IO                             ((uint32_t)(0x00000001UL << MXC_F_IOMAN_UART_CTS_IO_POS))
#define MXC_F_IOMAN_UART_RTS_IO_POS                         6
#define MXC_F_IOMAN_UART_RTS_IO                             ((uint32_t)(0x00000001UL << MXC_F_IOMAN_UART_RTS_IO_POS))

#define MXC_F_IOMAN_I2CM_MAPPING_POS                        0
#define MXC_F_IOMAN_I2CM_MAPPING                            ((uint32_t)(0x00000003UL << MXC_F_IOMAN_I2CM_MAPPING_POS))
#define MXC_F_IOMAN_I2CM_CORE_IO_POS                        4
#define MXC_F_IOMAN_I2CM_CORE_IO                            ((uint32_t)(0x00000001UL << MXC_F_IOMAN_I2CM_CORE_IO_POS))

#define MXC_F_IOMAN_I2CS_MAPPING_POS                        0
#define MXC_F_IOMAN_I2CS_MAPPING                            ((uint32_t)(0x00000003UL << MXC_F_IOMAN_I2CS_MAPPING_POS))
#define MXC_F_IOMAN_I2CS_CORE_IO_POS                        4
#define MXC_F_IOMAN_I2CS_CORE_IO                            ((uint32_t)(0x00000001UL << MXC_F_IOMAN_I2CS_CORE_IO_POS))

#define MXC_F_IOMAN_LCD_COM_REQ_COM_IO_POS                  0
#define MXC_F_IOMAN_LCD_COM_REQ_COM_IO                      ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_COM_REQ_COM_IO_POS))

#define MXC_F_IOMAN_LCD_COM_ACK_COM_IO_POS                  0
#define MXC_F_IOMAN_LCD_COM_ACK_COM_IO                      ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_COM_ACK_COM_IO_POS))

#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_24_POS              0
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_24                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_24_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_25_POS              1
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_25                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_25_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_26_POS              2
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_26                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_26_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_27_POS              3
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_27                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_27_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_28_POS              4
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_28                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_28_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_29_POS              5
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_29                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_29_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_30_POS              6
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_30                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_30_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_31_POS              7
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_31                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_31_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_32_POS              8
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_32                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_32_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_33_POS              9
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_33                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_33_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_34_POS              10
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_34                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_34_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_35_POS              11
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_35                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_35_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_36_POS              12
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_36                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_36_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_37_POS              13
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_37                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_37_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_38_POS              14
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_38                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_38_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_39_POS              15
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_39                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_39_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_40_POS              16
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_40                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_40_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_41_POS              17
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_41                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_41_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_42_POS              18
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_42                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_42_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_43_POS              19
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_43                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_43_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_44_POS              20
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_44                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_44_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_45_POS              21
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_45                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_45_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_46_POS              22
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_46                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_46_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_47_POS              23
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_47                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_47_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_48_POS              24
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_48                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_48_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_49_POS              25
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_49                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_49_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_50_POS              26
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_50                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_50_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_51_POS              27
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_51                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_51_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_52_POS              28
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_52                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_52_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_53_POS              29
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_53                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_53_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_54_POS              30
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_54                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_54_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_55_POS              31
#define MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_55                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ0_IO_REQ_55_POS))

#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_56_POS              0
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_56                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_56_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_57_POS              1
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_57                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_57_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_58_POS              2
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_58                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_58_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_59_POS              3
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_59                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_59_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_60_POS              4
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_60                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_60_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_61_POS              5
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_61                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_61_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_62_POS              6
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_62                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_62_POS))
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_63_POS              7
#define MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_63                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_REQ1_IO_REQ_63_POS))

#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_24_POS              0
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_24                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_24_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_25_POS              1
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_25                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_25_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_26_POS              2
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_26                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_26_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_27_POS              3
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_27                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_27_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_28_POS              4
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_28                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_28_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_29_POS              5
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_29                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_29_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_30_POS              6
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_30                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_30_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_31_POS              7
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_31                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_31_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_32_POS              8
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_32                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_32_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_33_POS              9
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_33                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_33_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_34_POS              10
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_34                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_34_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_35_POS              11
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_35                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_35_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_36_POS              12
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_36                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_36_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_37_POS              13
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_37                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_37_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_38_POS              14
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_38                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_38_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_39_POS              15
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_39                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_39_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_40_POS              16
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_40                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_40_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_41_POS              17
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_41                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_41_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_42_POS              18
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_42                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_42_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_43_POS              19
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_43                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_43_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_44_POS              20
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_44                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_44_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_45_POS              21
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_45                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_45_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_46_POS              22
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_46                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_46_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_47_POS              23
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_47                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_47_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_48_POS              24
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_48                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_48_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_49_POS              25
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_49                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_49_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_50_POS              26
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_50                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_50_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_51_POS              27
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_51                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_51_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_52_POS              28
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_52                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_52_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_53_POS              29
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_53                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_53_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_54_POS              30
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_54                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_54_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_55_POS              31
#define MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_55                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK0_IO_ACK_55_POS))

#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_56_POS              0
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_56                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_56_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_57_POS              1
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_57                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_57_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_58_POS              2
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_58                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_58_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_59_POS              3
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_59                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_59_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_60_POS              4
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_60                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_60_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_61_POS              5
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_61                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_61_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_62_POS              6
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_62                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_62_POS))
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_63_POS              7
#define MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_63                  ((uint32_t)(0x00000001UL << MXC_F_IOMAN_LCD_SEG_ACK1_IO_ACK_63_POS))

#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT0_POS               0
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT0                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT0_POS))
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT1_POS               1
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT1                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT1_POS))
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT2_POS               2
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT2                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT2_POS))
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT3_POS               3
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT3                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT3_POS))
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT4_POS               4
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT4                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT4_POS))
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT5_POS               5
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT5                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT5_POS))
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT6_POS               6
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT6                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT6_POS))
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT7_POS               7
#define MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT7                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_REQ_IO_REQ_CRNT7_POS))

#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT0_POS               0
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT0                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT0_POS))
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT1_POS               1
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT1                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT1_POS))
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT2_POS               2
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT2                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT2_POS))
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT3_POS               3
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT3                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT3_POS))
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT4_POS               4
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT4                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT4_POS))
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT5_POS               5
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT5                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT5_POS))
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT6_POS               6
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT6                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT6_POS))
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT7_POS               7
#define MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT7                   ((uint32_t)(0x00000001UL << MXC_F_IOMAN_CRNT_ACK_IO_ACK_CRNT7_POS))

#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT0_POS                  0
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT0                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT0_POS))
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT1_POS                  4
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT1                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT1_POS))
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT2_POS                  8
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT2                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT2_POS))
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT3_POS                  12
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT3                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT3_POS))
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT4_POS                  16
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT4                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT4_POS))
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT5_POS                  20
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT5                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT5_POS))
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT6_POS                  24
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT6                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT6_POS))
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT7_POS                  28
#define MXC_F_IOMAN_CRNT_MODE_IO_CRNT7                      ((uint32_t)(0x0000000FUL << MXC_F_IOMAN_CRNT_MODE_IO_CRNT7_POS))

#define MXC_F_IOMAN_PADX_CONTROL_PADX_POWER_CONTROL_POS     0
#define MXC_F_IOMAN_PADX_CONTROL_PADX_POWER_CONTROL         ((uint32_t)(0x00000001UL << MXC_F_IOMAN_PADX_CONTROL_PADX_POWER_CONTROL_POS))
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO0_OUT_MODE_POS    4
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO0_OUT_MODE        ((uint32_t)(0x00000003UL << MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO0_OUT_MODE_POS))
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO0_INPUT_STATE_POS 6
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO0_INPUT_STATE     ((uint32_t)(0x00000001UL << MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO0_INPUT_STATE_POS))
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO1_OUT_MODE_POS    8
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO1_OUT_MODE        ((uint32_t)(0x00000003UL << MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO1_OUT_MODE_POS))
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO1_INPUT_STATE_POS 10
#define MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO1_INPUT_STATE     ((uint32_t)(0x00000001UL << MXC_F_IOMAN_PADX_CONTROL_PADX_GPIO1_INPUT_STATE_POS))

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif   /* _MXC_IOMAN_REGS_H_ */
