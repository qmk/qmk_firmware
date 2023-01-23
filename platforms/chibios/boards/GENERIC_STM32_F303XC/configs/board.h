/* Copyright 2020 Nick Brassel (tzarc)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include_next <board.h>

#undef STM32_HSE_BYPASS

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp)                                   \
    do {                                                            \
        palSetPadMode(GPIOA, GPIOA_USB_DP, PAL_MODE_ALTERNATE(14)); \
    } while (0)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp)                                  \
    do {                                                              \
        palSetPadMode(GPIOA, GPIOA_USB_DP, PAL_MODE_OUTPUT_PUSHPULL); \
        palClearPad(GPIOA, GPIOA_USB_DP);                             \
    } while (0)
