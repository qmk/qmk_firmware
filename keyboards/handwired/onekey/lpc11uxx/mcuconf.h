/* Copyright 2022 Niels Westphal (crashniels)
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

#ifndef _MCUCONF_H_
#define _MCUCONF_H_

#define LPC11U3x
#define LPC11Uxx_MCUCONF

#define LPC_USE_SYSOSC TRUE
#define LPC_SYSOSC_FREQUENCY 12000000UL // 12MHz
#define LPC_SYSPLLCLKSEL SYSCON_SYSPLLCLKSEL_SYSOSC
#define LPC_MAINCLKSEL SYSCON_MAINCLKSEL_PLLOUT
#define LPC_SYSPLL_MULT 4 // MVALUE 4 -> bits 0b00011
#define LPC_SYSPLL_PDIV 4 // PSEL 2 -> bits 0b01
#define LPC_SYS_DIV 1     // NO SYS DIV

#define LPC_USB_USE_USB1 TRUE
#define LPC_USB_USB1_IRQ_PRIORITY 1

#endif /* _MCUCONF_H_ */
