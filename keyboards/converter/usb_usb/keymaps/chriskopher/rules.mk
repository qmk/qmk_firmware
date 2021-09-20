# Copyright 2020 Christopher Ko <chriskopher@gmail.com>
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

COMMAND_ENABLE = no # Not being used, and can cause conflicts with space cadet shifting
SPACE_CADET_ENABLE = no # Not using special built in space cadet keys, using custom tap dance instead
EXTRAKEY_ENABLE = yes # Used for audio control and system control keys
COMBO_ENABLE = yes # Used to allow chording of keys to trigger an action
TAP_DANCE_ENABLE = yes # Used to allow multiple taps of a key to perform different actions

LTO_ENABLE = yes # Reduces the compiled firmware size

SRC += combo.c tap_dance.c
