/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* AT32 has the same API as STM32Fx, but uses different names for literally the same thing.
 * As of 23.7.2021 QMK is tailored to use STM32 defines/names, for compatibility sake
 * we just redefine the AT32 names. */

/* timer redefines */
#define TIM_DIER_UDE AT32_TMR_IDEN_OVFDEN
#define TIM_DIER_TDE AT32_TMR_IDEN_TDEN
#define STM32_PWM_USE_ADVANCED AT32_PWM_USE_ADVANCED
#define CCR CDT
#define dier iden
#define tim tmr

/* DMA redefines */
#define STM32_DMA_STREAM(stream) AT32_DMA_STREAM(stream)
#define STM32_DMA_STREAM_ID(peripheral, channel) AT32_DMA_STREAM_ID(peripheral, channel)
#define STM32_DMA_CR_DIR_M2P AT32_DMA_CTRL_DTD_M2P
#define STM32_DMA_CR_MSIZE_BYTE AT32_DMA_CTRL_MWIDTH_BYTE
#define STM32_DMA_CR_PSIZE_WORD AT32_DMA_CTRL_PWIDTH_WORD
#define STM32_DMA_CR_PSIZE_HWORD AT32_DMA_CTRL_PWIDTH_HWORD
#define STM32_DMA_CR_MINC AT32_DMA_CTRL_MINCM
#define STM32_DMA_CR_CIRC AT32_DMA_CTRL_LM
#define STM32_DMA_CR_PL AT32_DMA_CTRL_CHPL
#define STM32_DMA_CR_CHSEL AT32_DMA_CTRL_CHSEL

#define cr1 ctrl1
#define cr2 ctrl2
#define cr3 ctrl3

/* ADC redefines */
#if HAL_USE_ADC
#    define smpr1 spt1
#    define smpr2 spt2

#    define sqr1 osq1
#    define sqr2 osq2
#    define sqr3 osq3

#    define ADC_SMPR2_SMP_AN0 ADC_SPT2_CSPT0
#    define ADC_SMPR2_SMP_AN1 ADC_SPT2_CSPT1
#    define ADC_SMPR2_SMP_AN2 ADC_SPT2_CSPT2
#    define ADC_SMPR2_SMP_AN3 ADC_SPT2_CSPT3
#    define ADC_SMPR2_SMP_AN4 ADC_SPT2_CSPT4
#    define ADC_SMPR2_SMP_AN5 ADC_SPT2_CSPT5
#    define ADC_SMPR2_SMP_AN6 ADC_SPT2_CSPT6
#    define ADC_SMPR2_SMP_AN7 ADC_SPT2_CSPT7
#    define ADC_SMPR2_SMP_AN8 ADC_SPT2_CSPT8
#    define ADC_SMPR2_SMP_AN9 ADC_SPT2_CSPT9
#    define ADC_SMPR1_SMP_AN10 ADC_SPT1_CSPT10
#    define ADC_SMPR1_SMP_AN11 ADC_SPT1_CSPT11
#    define ADC_SMPR1_SMP_AN12 ADC_SPT1_CSPT12
#    define ADC_SMPR1_SMP_AN13 ADC_SPT1_CSPT13
#    define ADC_SMPR1_SMP_AN14 ADC_SPT1_CSPT14
#    define ADC_SMPR1_SMP_AN15 ADC_SPT1_CSPT15
#    define ADC_SQR3_SQ1_N ADC_OSQ3_OSN1_N
#    define ADC_SMPR_SMP_1P5 ADC_SAMPLE_1P5
#    define ADC_SMPR_SMP_7P5 ADC_SAMPLE_7P5
#    define ADC_SMPR_SMP_13P5 ADC_SAMPLE_13P5
#    define ADC_SMPR_SMP_28P5 ADC_SAMPLE_28P5
#    define ADC_SMPR_SMP_41P5 ADC_SAMPLE_41P5
#    define ADC_SMPR_SMP_55P5 ADC_SAMPLE_55P5
#    define ADC_SMPR_SMP_71P5 ADC_SAMPLE_71P5
#    define ADC_SMPR_SMP_239P5 ADC_SAMPLE_239P5

#endif

/* USART redefines */
#if HAL_USE_SERIAL
#    if !defined(SERIAL_USART_CR1)
#        define SERIAL_USART_CR1 (USART_CTRL1_PEN | USART_CTRL1_PSEL | USART_CTRL1_DBN)
#    endif
#    if !defined(SERIAL_USART_CR2)
#        define SERIAL_USART_CR2 USART_CTRL2_STOPBN_2_BITS
#    endif
#    if !defined(SERIAL_USART_CR3)
#        define SERIAL_USART_CR3 0x0
#    endif
#    define USART_CR3_HDSEL USART_CTRL3_SLBEN

#endif

/* GPIO redefines */
#    define PAL_OUTPUT_TYPE_OPENDRAIN PAL_AT32_OMODE_OPENDRAIN
#    define PAL_OUTPUT_TYPE_PUSHPULL PAL_AT32_OMODE_PUSHPULL
#    define PAL_OUTPUT_SPEED_HIGHEST PAL_AT32_ODRV_STRONGER
#    define PAL_PUPDR_FLOATING PAL_AT32_PULL_FLOATING
#    if HAL_USE_ADC
#        define ADC_CR2_SWSTART ADC_CTRL2_OCSWTRG
#    endif

#    if HAL_USE_SERIAL
#        if !defined(USART_CR1_M0)
#            define USART_CR1_M0 USART_CTRL1_DBN0
#        endif
#        define USART_CR2_SWAP USART_CTRL2_TRPSWAP
#    endif

/* SPI redefines. */
#if HAL_USE_SPI
#    define SPI_CR1_LSBFIRST SPI_CTRL1_LTF
#    define SPI_CR1_CPHA SPI_CTRL1_CLKPHA
#    define SPI_CR1_CPOL SPI_CTRL1_CLKPOL
#    define SPI_CR1_BR_0 (1 << 3)
#    define SPI_CR1_BR_1 (2 << 3)
#    define SPI_CR1_BR_2 (4 << 3)
#endif



