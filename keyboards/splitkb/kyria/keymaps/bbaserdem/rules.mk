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

# Kyria hardware
ifneq (,$(findstring splitkb/kyria/rev1,$(KEYBOARD)))
    OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
    ENCODER_ENABLE = yes       # Enables the use of one or more encoders
    RGBLIGHT_ENABLE = no       # Disable keyboard RGB underglow; can't see much
    RGB_MATRIX_ENABLE = no
endif
