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

# This small layout is a macro-pad; does not need userspace

# Gherkin has both RGB strip and LED lights
ifneq (,$(findstring 40percentclub/gherkin,$(KEYBOARD)))
    CONVERT_TO_PROTON_C = yes
    RGB_MATRIX_ENABLE = yes
    RGB_MATRIX_DRIVER = WS2812
    AUDIO_ENABLE = yes
    BACKLIGHT_ENABLE = yes
    VELOCIKEY_ENABLE = yes
endif
