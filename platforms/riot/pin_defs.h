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

#define LINE_PIN0 GPIO_PIN(0, 0)
#define LINE_PIN1 GPIO_PIN(0, 1)
#define LINE_PIN2 GPIO_PIN(0, 2)
#define LINE_PIN3 GPIO_PIN(0, 3)
#define LINE_PIN4 GPIO_PIN(0, 4)
#define LINE_PIN5 GPIO_PIN(0, 5)
#define LINE_PIN6 GPIO_PIN(0, 6)

#ifdef HAS_PORT_PA
#define A0 GPIO_PIN(PA, 0)
#define A1 GPIO_PIN(PA, 1)
#define A2 GPIO_PIN(PA, 2)
#define A3 GPIO_PIN(PA, 3)
#define A4 GPIO_PIN(PA, 4)
#define A5 GPIO_PIN(PA, 5)
#define A6 GPIO_PIN(PA, 6)
#define A7 GPIO_PIN(PA, 7)
#define A8 GPIO_PIN(PA, 8)
#define A9 GPIO_PIN(PA, 9)
#define A10 GPIO_PIN(PA, 10)
#define A11 GPIO_PIN(PA, 11)
#define A12 GPIO_PIN(PA, 12)
#define A13 GPIO_PIN(PA, 13)
#define A14 GPIO_PIN(PA, 14)
#define A15 GPIO_PIN(PA, 15)
#define A16 GPIO_PIN(PA, 16)
#define A17 GPIO_PIN(PA, 17)
#define A18 GPIO_PIN(PA, 18)
#define A19 GPIO_PIN(PA, 19)
#define A20 GPIO_PIN(PA, 20)
#define A21 GPIO_PIN(PA, 21)
#define A22 GPIO_PIN(PA, 22)
#define A23 GPIO_PIN(PA, 23)
#define A24 GPIO_PIN(PA, 24)
#define A25 GPIO_PIN(PA, 25)
#define A26 GPIO_PIN(PA, 26)
#define A27 GPIO_PIN(PA, 27)
#define A28 GPIO_PIN(PA, 28)
#define A29 GPIO_PIN(PA, 29)
#define A30 GPIO_PIN(PA, 30)
#define A31 GPIO_PIN(PA, 31)
#endif

#ifdef HAS_PORT_PB
#define B0 GPIO_PIN(PB, 0)
#define B1 GPIO_PIN(PB, 1)
#define B2 GPIO_PIN(PB, 2)
#define B3 GPIO_PIN(PB, 3)
#define B4 GPIO_PIN(PB, 4)
#define B5 GPIO_PIN(PB, 5)
#define B6 GPIO_PIN(PB, 6)
#define B7 GPIO_PIN(PB, 7)
#define B8 GPIO_PIN(PB, 8)
#define B9 GPIO_PIN(PB, 9)
#define B10 GPIO_PIN(PB, 10)
#define B11 GPIO_PIN(PB, 11)
#define B12 GPIO_PIN(PB, 12)
#define B13 GPIO_PIN(PB, 13)
#define B14 GPIO_PIN(PB, 14)
#define B15 GPIO_PIN(PB, 15)
#define B16 GPIO_PIN(PB, 16)
#define B17 GPIO_PIN(PB, 17)
#define B18 GPIO_PIN(PB, 18)
#define B19 GPIO_PIN(PB, 19)
#define B20 GPIO_PIN(PB, 20)
#define B21 GPIO_PIN(PB, 21)
#define B22 GPIO_PIN(PB, 22)
#define B23 GPIO_PIN(PB, 23)
#define B24 GPIO_PIN(PB, 24)
#define B25 GPIO_PIN(PB, 25)
#define B26 GPIO_PIN(PB, 26)
#define B27 GPIO_PIN(PB, 27)
#define B28 GPIO_PIN(PB, 28)
#define B29 GPIO_PIN(PB, 29)
#define B30 GPIO_PIN(PB, 30)
#define B31 GPIO_PIN(PB, 31)
#endif
