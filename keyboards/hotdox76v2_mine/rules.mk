# MCU name
#MCU = atmega32u4
#BOOTLOADER = atmel-dfu
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)

#OLED_ENABLE = yes    # Enable Support for SSD1306 or SH1106 OLED Displays; Communicating over I2C
#OLED_DRIVER = SSD1306

# NO_USB_STARTUP_CHECK = yes

RGB_MATRIX_DRIVER = WS2812
