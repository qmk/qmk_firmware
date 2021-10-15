/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef USB2422_ADDRESS
#    define USB2422_ADDRESS 0x58
#endif

#ifndef USB2422_VENDOR_ID
#    define USB2422_VENDOR_ID 0x04D8
#endif
#ifndef USB2422_PRODUCT_ID
#    define USB2422_PRODUCT_ID 0xEEC5
#endif
#ifndef USB2422_DEVICE_VER
#    define USB2422_DEVICE_VER 0x0101
#endif

#ifndef USB2422_MANUFACTURER
#    define USB2422_MANUFACTURER { 'Q', 'M', 'K' }
#endif
#ifndef USB2422_PRODUCT
#    define USB2422_PRODUCT { 'Q', 'M', 'K', ' ', 'H', 'u', 'b' }
#endif

void USB2422_init(void);

void USB2422_configure(void);
