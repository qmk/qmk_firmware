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

#pragma once

/* Data structure to define Shift Register output expander hardware */
/* This structure gets shifted into registers LSB first */
typedef union {
  struct {
    uint16_t RSVD4:1;          /*!< bit:      0                                                         */
    uint16_t SRC_2_B5:1;       /*!< bit:      1  USBC-2 CC B5 UFP Rd 5.1k WHEN 1, DFP Rp 56k WHEN 0     */
    uint16_t SRC_1_B5:1;       /*!< bit:      2  USBC-1 CC B5 UFP Rd 5.1k WHEN 1, DFP Rp 56k WHEN 0     */
    uint16_t S_B_EXT:1;        /*!< bit:      3  B TO EX-1 WHEN 0, B TO USBC-1 WHEN 1                   */
    uint16_t SDB_N:1;          /*!< bit:      4  SHUTDOWN IS31FL3733 CHIPS WHEN 0, RUN WHEN 1           */
    uint16_t IRST:1;           /*!< bit:      5  RESET IS31FL3733 I2C WHEN 1, RUN WHEN 0                */
    uint16_t SRC_2_A5:1;       /*!< bit:      6  USBC-2 CC A5 UFP Rd 5.1k WHEN 1, DFP Rp 56k WHEN 0     */
    uint16_t SRC_1_A5:1;       /*!< bit:      7  USBC-1 CC A5 UFP Rd 5.1k WHEN 1, DFP Rp 56k WHEN 0     */
    uint16_t E_VBUS_2:1;       /*!< bit:      8  ENABLE 5V TO USBC-2/EX-2 WHEN 1, DISABLE WHEN 0        */
    uint16_t E_VBUS_1:1;       /*!< bit:      9  ENABLE 5V TO USBC-1/EX-1 WHEN 1, DISABLE WHEN 0        */
    uint16_t ENB:1;            /*!< bit:     10  ENABLE CHANNEL B USBC-1/EX-1 WHEN 1, DISABLE WHEN 0    */
    uint16_t S_A_EXT:1;        /*!< bit:     11  A TO USBC-2 WHEN 0, A TO EX-2 WHEN 1                   */
    uint16_t ENA:1;            /*!< bit:     12  ENABLE CHANNEL A USBC-2/EX-2 WHEN 1, DISABLE WHEN 0    */
    uint16_t S_A_UP:1;         /*!< bit:     13  DN1 TO A & UP TO B WHEN 1, DN1 TO B & UP TO A WHEN 0   */
    uint16_t HUB_RESET_N:1;    /*!< bit:     14  RESET USB HUB WHEN 0, RUN WHEN 1                       */
    uint16_t HUB_CONNECT:1;    /*!< bit:     15  SIGNAL VBUS CONNECT TO USB HUB WHEN 1                  */
  } bit;                       /*!< Structure used for bit access                                       */
  uint16_t reg;                /*!< Type      used for register access                                  */
} sr_exp_t;
