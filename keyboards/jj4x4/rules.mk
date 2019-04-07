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
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
RGBLIGHT_CUSTOM_DRIVER = yes
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no 		# Enable support for HD44780 based LCDs (+400)

SRC += i2c_master.c

# programming options
PROGRAM_CMD = ./util/atmega32a_program.py $(TARGET).hex

LAYOUTS = ortho_4x4
