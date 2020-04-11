USER_NAME := ericgebhart
SRC += ericgebhart.c
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

RGBLIGHT_ENABLE = yes
RGBLIGHT_ANIMATION = yes
# BACKLIGHT_ENABLE = yes

MOUSEKEY_ENABLE  = yes # Mouse keys
EXTRAKEY_ENABLE  = yes # Audio control and System control
COMMAND_ENABLE   = no # Commands for debug and configuration
NKRO_ENABLE      = yes # USB Nkey Rollover - for issues, see github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
SWAP_HANDS_ENABLE= no # Allow swapping hands of keyboard
KEY_LOCK_ENABLE  = yes # Enable the KC_LOCK key
TAP_DANCE_ENABLE = yes # Enable the tap dance feature.
CONSOLE_ENABLE   = no  # Console for debug

BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration
UNICODE_ENABLE   = no
SLEEP_LED_ENABLE = no
API_SYSEX_ENABLE = no
