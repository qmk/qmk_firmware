# Copyright 2023 splitkb.com <support@splitkb.com>
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

QUANTUM_LIB_SRC += spi_master.c
CUSTOM_MATRIX = lite
CUSTOM_ENCODER = yes

SERIAL_DRIVER = usart
OLED_DRIVER = ssd1306

# Myriad boilerplate
SRC += myriad.c analog.c
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom