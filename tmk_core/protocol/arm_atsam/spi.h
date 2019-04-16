/*
Copyright 2019 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SPI_H_
#define _SPI_H_

#include "config_spi.h"

/* Various macros for use in this header */
#define SPI_MACRO_CONCAT(str,var) str ## var
#define SPI_MACRO_EXPAND(str,var) SPI_MACRO_CONCAT(str,var)

/* Macros to define Shift Register macro (Ex: SERCOM2) */
#define SR_EXP_SERCOM SPI_MACRO_EXPAND(SERCOM,SR_EXP_SERCOM_NUM)

/* Macros to define Shift Register Peripheral ID (Ex: ID_SERCOM2) */
#define SR_EXP_SERCOM_PID SPI_MACRO_EXPAND(ID_SERCOM,SR_EXP_SERCOM_NUM)

/* Macros for Shift Register control */
#define SR_EXP_RCLK_LO PORT->Group[SR_EXP_RCLK_PORT].OUTCLR.reg = (1 << SR_EXP_RCLK_PIN)
#define SR_EXP_RCLK_HI PORT->Group[SR_EXP_RCLK_PORT].OUTSET.reg = (1 << SR_EXP_RCLK_PIN)
#define SR_EXP_OE_N_ENA PORT->Group[SR_EXP_OE_N_PORT].OUTCLR.reg = (1 << SR_EXP_OE_N_PIN)
#define SR_EXP_OE_N_DIS PORT->Group[SR_EXP_OE_N_PORT].OUTSET.reg = (1 << SR_EXP_OE_N_PIN)

/* Determine bits to set for mux selection */
#if SR_EXP_DATAOUT_PIN % 2 == 0
#define SR_EXP_DATAOUT_MUX_SEL PMUXE
#else
#define SR_EXP_DATAOUT_MUX_SEL PMUXO
#endif

/* Determine bits to set for mux selection */
#if SR_EXP_SCLK_PIN % 2 == 0
#define SR_EXP_SCLK_MUX_SEL PMUXE
#else
#define SR_EXP_SCLK_MUX_SEL PMUXO
#endif

//Note: sr_exp_t struct defined in keyboard's config_spi.h

extern sr_exp_t sr_exp_data;

void SR_EXP_WriteData(void);
void SR_EXP_Init(void);
void SR_EXP_Init_kb(void);

//For devices which use two shift registers for key matrix column drive
#ifdef SR_KC_SERCOM_NUM

/* Macros to define Shift Register macro (Ex: SERCOM4) */
#define SR_KC_SERCOM SPI_MACRO_EXPAND(SERCOM,SR_KC_SERCOM_NUM)

/* Macros to define Shift Register Peripheral ID (Ex: ID_SERCOM2) */
#define SR_KC_SERCOM_PID SPI_MACRO_EXPAND(ID_SERCOM,SR_KC_SERCOM_NUM)

/* Macros for Shift Register control */
#define SR_KC_RCLK_LO PORT->Group[SR_KC_RCLK_PORT].OUTCLR.reg = (1 << SR_KC_RCLK_PIN)
#define SR_KC_RCLK_HI PORT->Group[SR_KC_RCLK_PORT].OUTSET.reg = (1 << SR_KC_RCLK_PIN)
#define SR_KC_OE_N_ENA PORT->Group[SR_KC_OE_N_PORT].OUTCLR.reg = (1 << SR_KC_OE_N_PIN)
#define SR_KC_OE_N_DIS PORT->Group[SR_KC_OE_N_PORT].OUTSET.reg = (1 << SR_KC_OE_N_PIN)

/* Determine bits to set for mux selection */
#if SR_KC_DATAOUT_PIN % 2 == 0
#define SR_KC_DATAOUT_MUX_SEL PMUXE
#else
#define SR_KC_DATAOUT_MUX_SEL PMUXO
#endif

/* Determine bits to set for mux selection */
#if SR_KC_SCLK_PIN % 2 == 0
#define SR_KC_SCLK_MUX_SEL PMUXE
#else
#define SR_KC_SCLK_MUX_SEL PMUXO
#endif

/* Data structure to define Shift Register output for key matrix column drive */
/* This structure gets shifted into registers MSB first */
typedef union {
  struct {
    uint16_t KC1:1;            /*!< bit:      0  Key matrix column 1 drive                    */
    uint16_t KC2:1;            /*!< bit:      1  Key matrix column 2 drive                    */
    uint16_t KC3:1;            /*!< bit:      2  Key matrix column 3 drive                    */
    uint16_t KC4:1;            /*!< bit:      3  Key matrix column 4 drive                    */
    uint16_t KC5:1;            /*!< bit:      4  Key matrix column 5 drive                    */
    uint16_t KC6:1;            /*!< bit:      5  Key matrix column 6 drive                    */
    uint16_t KC7:1;            /*!< bit:      6  Key matrix column 7 drive                    */
    uint16_t KC8:1;            /*!< bit:      7  Key matrix column 8 drive                    */
    uint16_t KC9:1;            /*!< bit:      8  Key matrix column 9 drive                    */
    uint16_t KC10:1;           /*!< bit:      9  Key matrix column 10 drive                   */
    uint16_t KC11:1;           /*!< bit:     10  Key matrix column 11 drive                   */
    uint16_t KC12:1;           /*!< bit:     11  Key matrix column 12 drive                   */
    uint16_t KC13:1;           /*!< bit:     12  Key matrix column 13 drive                   */
    uint16_t KC14:1;           /*!< bit:     13  Key matrix column 14 drive                   */
    uint16_t KC15:1;           /*!< bit:     14  Key matrix column 15 drive                   */
    uint16_t KC16:1;           /*!< bit:     15  Key matrix column 16 drive                   */
  } bit;                       /*!< Structure used for bit access                             */
  uint16_t reg;                /*!< Type      used for register access                        */
} sr_kc_t;

extern sr_kc_t sr_kc_data;

void SR_KC_WriteData(void);
void SR_KC_Init(void);

#endif //SR_KC_SERCOM

#endif //_SPI_H_
