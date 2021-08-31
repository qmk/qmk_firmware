# Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Planck rev6 has both RGBLIGHT and RGB_MATRIX enabled
# RGBLIGHT should be enabled for a board with the underglow leds
# RGB_MATRIX_ENABLE should be set to WS2812 for the daughter board
ifneq (,$(findstring planck/rev6,$(KEYBOARD)))
    RGBLIGHT_ENABLE = yes
    RGB_MATRIX_ENABLE = no
endif
# JJ40 here
ifneq (,$(findstring jj40,$(KEYBOARD)))
    RGBLIGHT_ENABLE = yes
    RGB_MATRIX_ENABLE = no
endif
