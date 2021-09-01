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

# Corne keyboard; with ARM
ifneq (,$(findstring crkbd/rev1,$(KEYBOARD)))
    # My usual features
    AUDIO_ENABLE = yes #breaks reset keycode
    BACKLIGHT_ENABLE = no
    ENCODER_ENABLE = yes
    RGB_MATRIX_ENABLE = yes
    RGBLIGHT_ENABLE = no
    OLED_DRIVER_ENABLE = yes
    # Proton C related stuff
    MCU = STM32F303
    COVERT_TO_PROTON_C = yes
    DEBUG_MATRIX_SCAN_RATE_ENABLE = no # output matrix scan rate in qmk console/qmk toolbox
    AUDIO_DRIVER = dac_basic
    SERIAL_DRIVER = usart
    WS2812_DRIVER = pwm
    VIA_ENABLE = yes
    SPLIT_KEYBOARD = yes
    OLED_DRIVER = SSD1306   # Enables the use of OLED displays
    # POINTING_DEVICE_ENABLE = no
    # SRC += pimoroni_trackball.c
    QUANTUM_LIB_SRC += i2c_master.c #drivers/chibios/i2cmaster.h needs patch - see lines 27/28
endif
