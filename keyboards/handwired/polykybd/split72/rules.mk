# Build Options
#   change yes to no to disable

#Split keyboard setup
SERIAL_DRIVER = vendor
SPLIT_KEYBOARD = yes

#OLED setup
OLED_ENABLE = yes
OLED_DRIVER = ssd1306

#RGB matrix lighting
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812

#source files
QUANTUM_LIB_SRC += spi_master.c
SRC += base/text_helper.c base/helpers.c base/disp_array.c base/shift_reg.c base/spi_helper.c polykybd.c

DEFAULT_FOLDER = handwired/polykybd/split72

# Build Options
WS2812_DRIVER = vendor

ENCODER_ENABLE = yes

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c #POINTING_DEVICE_DRIVER = pimoroni_trackball

RAW_ENABLE = yes
WPM_ENABLE = yes
