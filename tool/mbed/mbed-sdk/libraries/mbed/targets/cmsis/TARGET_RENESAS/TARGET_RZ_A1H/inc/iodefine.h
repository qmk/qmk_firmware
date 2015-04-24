/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer*
* Copyright (C) 2013-2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name : iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register (V1.00a)
******************************************************************************/
#ifndef R7S72100_IODEFINE_H
#define R7S72100_IODEFINE_H
#define IODEFINE_H_VERSION  100

enum iodefine_byte_select_t
{
    L = 0, H = 1,
    LL= 0, LH = 1, HL = 2, HH = 3
};

/***********************************************************************
  <<< [iodefine_reg32_t] >>> 
- Padding : sizeof(iodefine_reg32_t) == 4
- Alignment(Offset) : &UINT32==0, &UINT16[0]==0, &UINT16[1]==2
-                     &UINT8[0]==0, &UINT8[1]==1, &UINT8[2]==2, &UINT8[3]==3
- Endian : Independent (Same as CPU endian as register endian)
- Bit-Order : Independent
************************************************************************/
/* ->MISRA 18.4 : Pack unpack union */ /* ->SEC M1.6.2 */
/* ->SEC M1.10.1 : Not magic number */
union iodefine_reg32_t
{
    volatile uint32_t  UINT32;                                  /*  32-bit Access   */
    volatile uint16_t  UINT16[2];                               /*  16-bit Access   */
    volatile uint8_t   UINT8[4];                                /*  8-bit Access    */
};
/* <-SEC M1.10.1 */
/* <-MISRA 18.4 */ /* <-SEC M1.6.2 */

/***********************************************************************
  <<< [iodefine_reg32_16_t] >>> 
- Padding : sizeof(iodefine_reg32_16_t) == 4
- Alignment(Offset) : &UINT32==0, &UINT16[0]==0, &UINT16[1]==2
- Endian : Independent (Same as CPU endian as register endian)
- Bit-Order : Independent
************************************************************************/
/* ->MISRA 18.4 : Pack unpack union */ /* ->SEC M1.6.2 */
/* ->SEC M1.10.1 : Not magic number */
union iodefine_reg32_16_t
{
    volatile uint32_t  UINT32;                                  /*  32-bit Access   */
    volatile uint16_t  UINT16[2];                               /*  16-bit Access   */
};
/* <-SEC M1.10.1 */
/* <-MISRA 18.4 */ /* <-SEC M1.6.2 */

/***********************************************************************
  <<< [iodefine_reg16_8_t] >>> 
- Padding : sizeof(iodefine_reg16_8_t) == 2
- Alignment(Offset) : &UINT16==0, &UINT8[0]==0, &UINT8[1]==1
- Endian : Independent (Same as CPU endian as register endian)
- Bit-Order : Independent
************************************************************************/
/* ->MISRA 18.4 : Pack unpack union */ /* ->SEC M1.6.2 */
/* ->SEC M1.10.1 : Not magic number */
union iodefine_reg16_8_t
{
    volatile uint16_t  UINT16;                                  /*  16-bit Access   */
    volatile uint8_t   UINT8[2];                                /*  8-bit Access    */
};
/* <-SEC M1.10.1 */
/* <-MISRA 18.4 */ /* <-SEC M1.6.2 */






#include "adc_iodefine.h"                             /* (V1.00a) */
#include "bsc_iodefine.h"                             /* (V1.00a) */
#include "ceu_iodefine.h"                             /* (V1.00a) */
#include "cpg_iodefine.h"                             /* (V1.00a) */
#include "disc_iodefine.h"                            /* (V1.00a) */
#include "dmac_iodefine.h"                            /* (V1.00a) */
#include "dvdec_iodefine.h"                           /* (V1.00a) */
#include "ether_iodefine.h"                           /* (V1.00a) */
#include "flctl_iodefine.h"                           /* (V1.00a) */
#include "gpio_iodefine.h"                            /* (V1.00a) */
#include "ieb_iodefine.h"                             /* (V1.00a) */
#include "inb_iodefine.h"                             /* (V1.00a) */
#include "intc_iodefine.h"                            /* (V1.00a) */
#include "irda_iodefine.h"                            /* (V1.00a) */
#include "jcu_iodefine.h"                             /* (V1.00a) */
#include "l2c_iodefine.h"                             /* (V1.00a) */
#include "lin_iodefine.h"                             /* (V1.00a) */
#include "lvds_iodefine.h"                            /* (V1.00a) */
#include "mlb_iodefine.h"                             /* (V1.00a) */
#include "mmc_iodefine.h"                             /* (V1.00a) */
#include "mtu2_iodefine.h"                            /* (V1.00a) */
#include "ostm_iodefine.h"                            /* (V1.00a) */
#include "pfv_iodefine.h"                             /* (V1.00a) */
#include "pwm_iodefine.h"                             /* (V1.00a) */
#include "riic_iodefine.h"                            /* (V1.00a) */
#include "romdec_iodefine.h"                          /* (V1.00a) */
#include "rscan0_iodefine.h"                          /* (V1.00a) */
#include "rspi_iodefine.h"                            /* (V1.00a) */
#include "rtc_iodefine.h"                             /* (V1.00a) */
#include "scif_iodefine.h"                            /* (V1.00a) */
#include "scim_iodefine.h"                            /* (V1.00a) */
#include "scux_iodefine.h"                            /* (V1.00a) */
#include "sdg_iodefine.h"                             /* (V1.00a) */
#include "spdif_iodefine.h"                           /* (V1.00a) */
#include "spibsc_iodefine.h"                          /* (V1.00a) */
#include "ssif_iodefine.h"                            /* (V1.00a) */
#include "usb20_iodefine.h"                           /* (V1.00a) */
#include "vdc5_iodefine.h"                            /* (V1.00a) */
#include "wdt_iodefine.h"                             /* (V1.00a) */
#endif
