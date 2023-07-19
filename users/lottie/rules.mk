# Copyright 2023 Gyozo Gaspar
#
# This file is part of Lottie layout. The Lottie layout is free
# software: you can redistribute it and/or modify it under the terms
# of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option)
# any later version.  The Lottie layout is distributed in the hope
# that it will be useful, but WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE. See the GNU General Public License for more details.  You
# should have received a copy of the GNU General Public License along
# with Lottie layout. If not, see <https://www.gnu.org/licenses/>.

$(info Executing user rules.mk)

# SRC += source.c

# Build Options from miryoku
MOUSEKEY_ENABLE = yes # Maybe not necessary, but does not hurt
EXTRAKEY_ENABLE = yes # Copy / Paste works because of it?
AUTO_SHIFT_ENABLE = no # Key override does not take effect when auto shifting. I can press shift when needed NP.
TAP_DANCE_ENABLE = no # Used by the double tap guard feature, I don't use it at the moment
CAPS_WORD_ENABLE = yes # This is a good feature, test with the desired layout
KEY_OVERRIDE_ENABLE = yes # Needed for adjustment to a hungarian host

# Build Options from crkbd
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover ### i dont need it probably
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality, yes -> #error "Backlight pin/pins not defined. Please configure."
AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = yes            # if firmware size over limit, try this option
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight / Cannot use RGBLIGHT and RGB Matrix using WS2812 at the same time.
RGB_MATRIX_ENABLE = no      # WS2812B
OLED_ENABLE     = yes

# EXTRAFLAGS += -Os # -flto does not have an effect, probably the same a LTO_ENABLE
                    # -Os does not have an effect

INTROSPECTION_KEYMAP_C = lottie.c # keymaps

$(info Finished executing user rules.mk)
