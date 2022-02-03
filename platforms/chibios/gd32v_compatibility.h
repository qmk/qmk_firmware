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

/* GD32VF103 has the same API as STM32F103, but uses different names for literally the same thing.
 * As of 23.7.2021 QMK is tailored to use STM32 defines/names, for compatibility sake
 * we just redefine the GD32 names. */

/* Close your eyes kids. */
#define MCU_STM32

/* AFIO redefines */
#define MAPR PCF0
#define AFIO_MAPR_USART1_REMAP AFIO_PCF0_USART0_REMAP
#define AFIO_MAPR_USART2_REMAP AFIO_PCF0_USART1_REMAP
#define AFIO_MAPR_USART3_REMAP_PARTIALREMAP AFIO_PCF0_USART2_REMAP_PARTIALREMAP
#define AFIO_MAPR_USART3_REMAP_FULLREMAP AFIO_PCF0_USART2_REMAP_FULLREMAP

/* DMA redefines. */
#define STM32_DMA_STREAM(stream) GD32_DMA_STREAM(stream)
#define STM32_DMA_STREAM_ID(peripheral, channel) GD32_DMA_STREAM_ID(peripheral - 1, channel - 1)
#define STM32_DMA_CR_DIR_M2P GD32_DMA_CTL_DIR_M2P
#define STM32_DMA_CR_PSIZE_WORD GD32_DMA_CTL_PWIDTH_WORD
#define STM32_DMA_CR_MSIZE_WORD GD32_DMA_CTL_MWIDTH_WORD
#define STM32_DMA_CR_MINC GD32_DMA_CTL_MNAGA
#define STM32_DMA_CR_CIRC GD32_DMA_CTL_CMEN
#define STM32_DMA_CR_PL GD32_DMA_CTL_PRIO
#define STM32_DMA_CR_CHSEL GD32_DMA_CTL_CHSEL
#define cr1 ctl0
#define cr2 ctl1
#define cr3 ctl2
#define dier dmainten

/* ADC redefines */
#if HAL_USE_ADC
#    define STM32_ADC_USE_ADC1 GD32_ADC_USE_ADC0

#    define smpr1 sampt0
#    define smpr2 sampt1
#    define sqr1 rsq0
#    define sqr2 rsq1
#    define sqr3 rsq2

#    define ADC_SMPR2_SMP_AN0 ADC_SAMPT1_SMP_SPT0
#    define ADC_SMPR2_SMP_AN1 ADC_SAMPT1_SMP_SPT1
#    define ADC_SMPR2_SMP_AN2 ADC_SAMPT1_SMP_SPT2
#    define ADC_SMPR2_SMP_AN3 ADC_SAMPT1_SMP_SPT3
#    define ADC_SMPR2_SMP_AN4 ADC_SAMPT1_SMP_SPT4
#    define ADC_SMPR2_SMP_AN5 ADC_SAMPT1_SMP_SPT5
#    define ADC_SMPR2_SMP_AN6 ADC_SAMPT1_SMP_SPT6
#    define ADC_SMPR2_SMP_AN7 ADC_SAMPT1_SMP_SPT7
#    define ADC_SMPR2_SMP_AN8 ADC_SAMPT1_SMP_SPT8
#    define ADC_SMPR2_SMP_AN9 ADC_SAMPT1_SMP_SPT9

#    define ADC_SMPR1_SMP_AN10 ADC_SAMPT0_SMP_SPT10
#    define ADC_SMPR1_SMP_AN11 ADC_SAMPT0_SMP_SPT11
#    define ADC_SMPR1_SMP_AN12 ADC_SAMPT0_SMP_SPT12
#    define ADC_SMPR1_SMP_AN13 ADC_SAMPT0_SMP_SPT13
#    define ADC_SMPR1_SMP_AN14 ADC_SAMPT0_SMP_SPT14
#    define ADC_SMPR1_SMP_AN15 ADC_SAMPT0_SMP_SPT15

#    define ADC_SQR3_SQ1_N ADC_RSQ2_RSQ1_N
#endif

/* FLASH redefines */
#if defined(EEPROM_ENABLE)
#    define SR STAT
#    define FLASH_SR_BSY FLASH_STAT_BUSY
#    define FLASH_SR_PGERR FLASH_STAT_PGERR
#    define FLASH_SR_EOP FLASH_STAT_ENDF
#    define FLASH_SR_WRPRTERR FLASH_STAT_WPERR
#    define FLASH_SR_WRPERR FLASH_SR_WRPRTERR
#    define FLASH_OBR_OPTERR FLASH_OBSTAT_OBERR
#    define AR ADDR
#    define CR CTL
#    define FLASH_CR_PER FLASH_CTL_PER
#    define FLASH_CR_STRT FLASH_CTL_START
#    define FLASH_CR_LOCK FLASH_CTL_LK
#    define FLASH_CR_PG FLASH_CTL_PG
#    define KEYR KEY
#endif

/* Serial USART redefines. */
#if HAL_USE_SERIAL
#    if !defined(SERIAL_USART_CR1)
#        define SERIAL_USART_CR1 (USART_CTL0_PCEN | USART_CTL0_PM | USART_CTL0_WL)  // parity enable, odd parity, 9 bit length
#    endif
#    if !defined(SERIAL_USART_CR2)
#        define SERIAL_USART_CR2 (USART_CTL1_STB_1)  // 2 stop bits
#    endif
#    if !defined(SERIAL_USART_CR3)
#        define SERIAL_USART_CR3 0x0
#    endif
#    define USART_CR3_HDSEL USART_CTL2_HDEN
#    define CCR CHCV
#endif

/* SPI redefines. */
#if HAL_USE_SPI
#    define SPI_CR1_LSBFIRST SPI_CTL0_LF
#    define SPI_CR1_CPHA SPI_CTL0_CKPH
#    define SPI_CR1_CPOL SPI_CTL0_CKPL
#    define SPI_CR1_BR_0 SPI_CTL0_PSC_0
#    define SPI_CR1_BR_1 SPI_CTL0_PSC_1
#    define SPI_CR1_BR_2 SPI_CTL0_PSC_2
#endif
