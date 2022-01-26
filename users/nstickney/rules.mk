# Copyright 2021 @nstickney
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
SRC += nstickney.c

KEY_LOCK_ENABLE = yes
RGBLIGHT_ENABLE = yes
TAP_DANCE_ENABLE = yes
UNICODE_ENABLE = no
UNICODEMAP_ENABLE = yes
UCIS_ENABLE = no

# https://github.com/qmk/qmk_firmware/issues/3224#issuecomment-399769416
LTO_ENABLE = yes

# https://beta.docs.qmk.fm/developing-qmk/qmk-reference/getting_started_make_guide#rules-mk-options
AUDIO_ENABLE = no
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
MOUSEKEY_ENABLE  = no
MIDI_ENABLE = no
NKRO_ENABLE = no
SLEEP_LED_ENABLE = no
VARIABLE_TRACE = no
