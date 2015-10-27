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

#ifndef _MXC_LCD_REGS_H
#define _MXC_LCD_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @file  lcd_regs.h
 * @addtogroup lcd LCD
 * @{
 */

#define MXC_LCD_ADDRESS_SEGS 21

/*                                 Offset   Register Description
                                   ======   ======================================================= */
typedef struct {    
    __IO uint32_t lcfg;         /* 0x0000                                                           */
    __IO uint32_t lcra;         /* 0x0004                                                           */
    __IO uint32_t lpcf;         /* 0x0008  LCD Port Configuration Register                          */
    __IO uint32_t lcaddr;       /* 0x000C                                                           */
    __IO uint32_t lcdata;       /* 0x0010  LCD Memory Data Read / Write                             */
    __IO uint32_t lpwrctrl;     /* 0x0014  LCD Power Control                                        */
} mxc_lcd_regs_t;

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _MXC_LCD_REGS_H */
