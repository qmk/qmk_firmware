/* Copyright 2019
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

/*
            PCA9555
         ,----------.
   SDA --| SDA  P00 |-- P00
   SCL --| SCL  P01 |-- P01
   INT --| INT  P02 |-- P02
         |      P03 |-- P03
   A0  --| A0   P04 |-- P04
   A1  --| A1   P05 |-- P05
   A2  --| A2   P06 |-- P06
         |      P07 |-- P07
         |          |
         |      P10 |-- P10
         |      P11 |-- P11
         |      P12 |-- P12
         |      P13 |-- P13
         |      P14 |-- P14
         |      P15 |-- P15
         |      P16 |-- P16
         |      P17 |-- P17
         `----------'
*/

#define PCA9555_PORT0 0
#define PCA9555_PORT1 1

#define ALL_OUTPUT 0
#define ALL_INPUT 0xFF
#define ALL_LOW 0
#define ALL_HIGH 0xFF

void pca9555_init(uint8_t slave_addr);

void pca9555_set_config(uint8_t slave_addr, uint8_t port, uint8_t conf);

void pca9555_set_output(uint8_t slave_addr, uint8_t port, uint8_t conf);

uint8_t pca9555_readPins(uint8_t slave_addr, uint8_t port);
