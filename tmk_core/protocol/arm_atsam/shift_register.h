/*
Copyright 2018 Massdrop Inc.

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

#pragma once

#include <stdint.h>

/* Data structure to define Shift Register output expander hardware */
/* This structure gets shifted into registers LSB first */
typedef union {
    struct {
        uint16_t RSVD4 : 1;       /*!< bit:      0                                               */
        uint16_t RSVD3 : 1;       /*!< bit:      1                                               */
        uint16_t RSVD2 : 1;       /*!< bit:      2                                               */
        uint16_t RSVD1 : 1;       /*!< bit:      3                                               */
        uint16_t SDB_N : 1;       /*!< bit:      4  SHUTDOWN THE CHIP WHEN 0, RUN WHEN 1         */
        uint16_t IRST : 1;        /*!< bit:      5  RESET THE IS3733 I2C WHEN 1, RUN WHEN 0      */
        uint16_t SRC_2 : 1;       /*!< bit:      6  ADVERTISE A SOURCE TO USBC-2 CC              */
        uint16_t SRC_1 : 1;       /*!< bit:      7  ADVERTISE A SOURCE TO USBC-1 CC              */
        uint16_t E_VBUS_2 : 1;    /*!< bit:      8  ENABLE 5V OUT TO USBC-2 WHEN 1               */
        uint16_t E_VBUS_1 : 1;    /*!< bit:      9  ENABLE 5V OUT TO USBC-1 WHEN 1               */
        uint16_t E_DN1_N : 1;     /*!< bit:     10  ENABLE DN1 1:2 MUX WHEN 0                    */
        uint16_t S_DN1 : 1;       /*!< bit:     11  SELECT DN1 PATH 0:USBC-1, 1:USBC-2           */
        uint16_t E_UP_N : 1;      /*!< bit:     12  ENABLE SUP 1:2 MUX WHEN 0                    */
        uint16_t S_UP : 1;        /*!< bit:     13  SELECT UP PATH 0:USBC-1, 1:USBC-2            */
        uint16_t HUB_RESET_N : 1; /*!< bit:     14  RESET USB HUB WHEN 0, RUN WHEN 1             */
        uint16_t HUB_CONNECT : 1; /*!< bit:     15  SIGNAL VBUS CONNECT TO USB HUB WHEN 1        */
    } bit;                        /*!< Structure used for bit access                             */
    uint16_t reg;                 /*!< Type      used for register access                        */
} sr_exp_t;

extern sr_exp_t sr_exp_data;

void SR_EXP_WriteData(void);
void SR_EXP_Init(void);
