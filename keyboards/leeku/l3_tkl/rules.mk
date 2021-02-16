
# Copyright 2021 MajorKoos <https://github.com/MajorKoos>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# MCU name
MCU = atmega32a
F_CPU = 12000000
F_USB = $(F_CPU)

# Bootloader
BOOTLOADER = bootloadHID

# Build Options
BOOTMAGIC_ENABLE = no     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
AUDIO_ENABLE = no

# Bling
SLEEP_LED_ENABLE = no        # Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = custom    # It's on i2c driver
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
WS2812_DRIVER = i2c

SRC += 	l3_common.c
QUANTUM_LIB_SRC += i2c_master.c

WATCHDOG_ENABLE = yes		# Resets keyboard if matrix_scan isn't run every 2 seconds
ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
     TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif
