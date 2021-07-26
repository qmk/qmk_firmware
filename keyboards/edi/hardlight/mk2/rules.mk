# ©2021 Everywhere Defense Industries / Fate Everywhere <fate@7storm.org>
 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


# MCU name
MCU = STM32F072

# Build Options
#   comment out to disable the options.

BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = no
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = no      # Custom matrix file
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = yes
AUDIO_ENABLE = no       # Audio output
WS2812_DRIVER = pwm
KEY_LOCK_ENABLE = yes
VELOCIKEY_ENABLE = yes

# Layout definitions
# LAYOUTS = ortho_4x16

# Wildcard to allow APM32 MCU 
DFU_SUFFIX_ARGS = -p FFFF -v FFFF

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
