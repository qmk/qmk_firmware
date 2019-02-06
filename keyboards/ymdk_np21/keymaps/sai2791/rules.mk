# Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
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
PROTOCOL = VUSB

# unsupported features for now
NO_UART = yes
NO_SUSPEND_POWER_DOWN = yes

# processor frequency
F_CPU = 12000000

# Bootloader
#     This definition is optional, and if your keyboard supports multiple bootloaders of
#     different sizes, comment this out, and the correct address will be loaded
#     automatically (+60). See bootloader.mk for all options.
BOOTLOADER = bootloadHID

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no  # System and audio keys
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

NKRO_ENABLE = no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no 		# MIDI controls
UNICODE_ENABLE = no 		# Unicode
BLUETOOTH_ENABLE = no # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6

BACKLIGHT_ENABLE = yes
BACKLIGHT_CUSTOM_DRIVER = yes

RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes
# DISABLE_WS2812 = no

KEY_LOCK_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

OPT_DEFS = -DDEBUG_LEVEL=0
OPT_DEFS += -flto

# custom matrix setup
CUSTOM_MATRIX = yes
SRC = matrix.c i2c.c backlight.c

#Add tapdance
TAP_DANCE_ENABLE = yes

# programming options
#This isnt working at the moment and it seems to use the default rules in the keymap directory
PROGRAM_CMD = 'sudo bootloadHID -r $(TARGET).hex'
