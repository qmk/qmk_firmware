/* Copyright 2019 Sebastian Williams
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
# MCU name
MCU = atmega32u4

# Processor frequency.
F_CPU = 16000000

#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

# Input clock frequency.
F_USB = $(F_CPU)

# Bootloader
BOOTLOADER = caterina

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE  = no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = no	# Mouse keys(+4700)
EXTRAKEY_ENABLE  = no	# Audio control and System control(+450)
CONSOLE_ENABLE  = yes	# Console for debug(+400)
COMMAND_ENABLE  = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE  = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE  = no  # Custom backlighting code is used, so this should not be enabled
AUDIO_ENABLE  = no # This can be enabled if a speaker is connected to the expansion port. Not compatible with RGBLIGHT below
RGBLIGHT_ENABLE  = yes # This can be enabled if a ws2812 strip is connected to the expansion port.
