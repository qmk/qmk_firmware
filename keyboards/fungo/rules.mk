# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu   # controller Elite-C
#BOOTLOADER = caterina   # controller pro micro

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no       # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
KEY_LOCK_ENABLE = yes       # kc_lock use

#PS2_MOUSE_ENABLE = yes
#PS2_USE_INT = yes
#PS2_USE_USART = yes


OLED_ENABLE = no
OLED_DRIVER = SSD1306      # OLED display
SPLIT_KEYBOARD = yes       # split type

DEFAULT_FOLDER = fungo/rev1

# point device future(mouse)

# POINTING_DEVICE_DRIVER = adns9800
# ADNS9800_CLOCK_SPEED 	(Optional) Sets the clock speed that the sensor runs at. 	2000000
# ADNS9800_SPI_LSBFIRST 	(Optional) Sets the Least/Most Significant Byte First setting for SPI. 	false
# ADNS9800_SPI_MODE 	(Optional) Sets the SPI Mode for the sensor. 	3
# ADNS9800_SPI_DIVISOR 	(Optional) Sets the SPI Divisor used for SPI communication. 	varies
# ADNS9800_CS_PIN 	(Required) Sets the Cable Select pin connected to the sensor. 	not defined
