# Copyright 2021 Batuhan Başerdem
# <baserdem.batuhan@gmail.com> @bbaserdem
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

# Common compilation flags
LTO_ENABLE = yes

# These should be enabled in all boards
MOUSEKEY_ENABLE = yes   # Mouse emulation keys
EXTRAKEY_ENABLE = yes   # OS signals like volume control
UNICODEMAP_ENABLE = yes # Used for unicode character emulation

# These should be disabled in all boards
BOOTMAGIC_ENABLE = no   # Access to EEPROM settings, not needed
CONSOLE_ENABLE = no     # Allows console output with a command
COMMAND_ENABLE = no     # Some bootmagic thing i dont use
SLEEP_LED_ENABLE = no   # Breathes LED's when computer is asleep. Untested.
MIDI_ENABLE = no        # Midi driver (untested)
UNICODE_ENABLE = no 	# We use unicodemap, not unicode
UCIS_ENABLE = no 	# We use unicodemap, not ucis
VARIABLE_TRACE = no     # Allows debugging variables
KEY_LOCK_ENABLE = no    # Allows locking any key. Not used in general
RGBLIGHT_ENABLE = no    # LED strip, but there is RGB_MATRIX instead
TAP_DANCE_ENABLE = no   # Tap dance keys; i don't use tap dance

# These features can be disabled at whim
NKRO_ENABLE ?= yes      # Default is 6KRO
VELOCIKEY_ENABLE ?= yes # Speed effects change with typing speed
WPM_ENABLE ?= yes       # Get WPM reports as you type

# Manually configure these on each keyboard individually
# AUDIO_ENABLE            # Audio stuff
# BACKLIGHT_ENABLE        # Switch LEDs
# ENCODER_ENABLE          # Rotary encoder
# RGB_MATRIX_ENABLE       # RGB LEDs
# OLED_ENABLE  	          # For OLED

# Userspace code
SRC += bbaserdem.c

# Macros
SRC += bb-macro.c

# Audio code
ifeq ($(strip $(AUDIO_ENABLE)), yes)
SRC += bb-audio.c
endif

# Rotary encoder stuff
ifeq ($(strip $(ENCODER_ENABLE)), yes)
SRC += bb-encoder.c
endif

# RGB LED (Underglow) code
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
SRC += bb-underglow.c
endif

# RGB LED (Perkey) code
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
SRC += bb-rgb.c
endif

# Backlight code
ifeq ($(strip $(BACKLIGHT_ENABLE)), yes)
SRC += bb-backlight.c
endif

# OLED code
ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += bb-oled.c
    ifeq ($(strip $(CTPC)), yes)
        SRC += bb-oled-extra.c
    endif
endif
