# Copyright 2020 B. Fletcher (toraifu) <typefast@kyaa.gg>
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


# MCU
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
BOOTLOADER = atmel-dfu

F_USB = $(F_CPU)

OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Boot Section Size in *bytes*
OPT_DEFS += -DBOOTLOADER_SIZE=4096


# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE	= lite			# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE		= no			# Mouse keys(+4700)
EXTRAKEY_ENABLE		= yes			# Audio control and System control(+450)
CONSOLE_ENABLE		= no			# Console for debug(+400)
COMMAND_ENABLE		= yes			# Commands for debug and configuration
SLEEP_LED_ENABLE	= no			# Breathing sleep LED during USB suspend
NKRO_ENABLE			= yes			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE			= no
AUDIO_ENABLE		= no
RGBLIGHT_ENABLE		= yes
BACKLIGHT_ENABLE	= no			# Disable backlight


# Addtional sources required by the IS31FL3731 driver implementation
SRC = drivers/issi/is31fl3731-simple.c \
	  drivers/avr/i2c_master.c \
	  keyboards/fallacy/indicators.c
