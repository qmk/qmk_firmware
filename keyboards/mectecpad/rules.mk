# MCU and board definitions
MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040
VIA_ENABLE = yes
RP2040_PWM_ENABLE = yes
FLASH_SIZE = 2MB         # Replace with your flash memory size

# Features to optimize firmware size
LTO_ENABLE = yes         # Enable Link Time Optimization for smaller firmware
EXTRAFLAGS += -Os        # Optimize for size

VIA_ENABLE = yes          # Enable VIA support

#/*
#* rules.mk
#*
#* Copyright 2025 Iakovos Sachinidhs isachinidhs@gmail.com
#*
#* This program is free software: you can redistribute it and/or modify
#* it under the terms of the GNU General Public License as published by
#* the Free Software Foundation, either version 2 of the License, or
#* (at your option) any later version.
#*
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#* GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License
#* along with this program.  If not, see <http://www.gnu.org/licenses/>.
#*/
