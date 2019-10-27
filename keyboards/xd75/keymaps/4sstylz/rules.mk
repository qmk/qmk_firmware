# Copyright 2013 Jun Wako <wakojun@gmail.com>
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

COMBO_ENABLE     = yes # Enable combo for special function when using multiple keys at once.
BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
RGBLIGHT_ENABLE  = yes # Enable WS2812 RGB underlight.

BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes # Audio control and System control(+450)
CONSOLE_ENABLE   = no  # Console for debug(+400)
COMMAND_ENABLE   = no  # Commands for debug and configuration
NKRO_ENABLE      = yes # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE      = no  # MIDI support (+2400 to 4200, depending on config)
AUDIO_ENABLE     = no  # Audio output on port C6
UNICODE_ENABLE   = no  # Unicode
BLUETOOTH_ENABLE = no  # Enable Bluetooth with the Adafruit EZ-Key HID
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
