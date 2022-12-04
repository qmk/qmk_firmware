# Copyright 2021 Batuhan Başerdem
# <baserdem.batuhan@gmail.com> @bbaserdem
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

# Corne keyboard; with ARM
ifneq (,$(findstring crkbd/rev1,$(KEYBOARD)))
    # Proton C conversion
    MCU = STM32F303
    CTPC = yes
    # BOARD  = QMK_PROTON_C
    # BOOTLOADER = stm32-dfu
    # My usual features
    AUDIO_ENABLE = yes
    BACKLIGHT_ENABLE = no
    ENCODER_ENABLE = yes
    RGB_MATRIX_ENABLE = yes
    OLED_ENABLE = yes
    # Features that take otherwise too much space
    WPM_ENABLE = yes
    NKRO_ENABLE = yes
    # Config
    SERIAL_DRIVER = usart
    WS2812_DRIVER = pwm
    AUDIO_DRIVER = dac_basic
    SPLIT_KEYBOARD = yes
    # These are from waffle
    DEBUG_MATRIX_SCAN_RATE_ENABLE = no # output matrix scan rate in qmk console/qmk toolbox
    QUANTUM_LIB_SRC += i2c_master.c #drivers/chibios/i2cmaster.h needs patch - see lines 27/28
    VIA_ENABLE = no
    # COMMAND_ENABLE = no
    # CONSOLE_ENABLE = no
    # BOOTMAGIC_ENABLE = lite
    # LTO_ENABLE = yes
    # PIMORONI_TRACKBALL = no
endif
