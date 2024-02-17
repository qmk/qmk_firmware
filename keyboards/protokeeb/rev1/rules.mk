# Build Options
# Change yes to no to diable features

# Default keyboard folder
DEFAULT_FOLDER = protokeeb/rev1

# Custom scanning of matrix
#CUSTOM_MATRIX = lite

# SPI Flash driver
#FLASH_DRIVER = spi

# EEPROM driver
#EEPROM_DRIVER = spi
#EEPROM_DRIVER = wear_leveling
#WEAR_LEVELING_DRIVER = spi_flash

# OS detection
OS_DETECTION_ENABLE = yes

# Enable Bootmagic Lite
BOOTMAGIC_ENABLE = yes

# Development Board used
#BOARD = GENERIC_RP_RP2040

# Bootlader Selection
BOOTLOADER = rp2040

# Debounce Method
#DEBOUNCE_TYPE = sym_defer_g # Default Method

# Mouse keys
MOUSEKEY_ENABLE = no

# Audio Control and System Control keys
EXTRAKEY_ENABLE = yes

# Console for keyboard debug
CONSOLE_ENABLE = no

# Commands for debug and configuration
COMMAND_ENABLE = no

# Enable N-Key Rollover
NKRO_ENABLE = yes

# Enable keyboard RGB underglow
RGBLIGHT_ENABLE = yes

# Enable RGB LED Matrix
#RGB_MATRIX_ENABLE = yes
#RGB_MATRIX_DRIVER = WS2812

# ARGB LED Driver used
WS2812_DRIVER = vendor # For RP2040 MCU

# Enable Audio output
AUDIO_ENABLE = no

# Refer: USB Endpoint Limitations
KEYBOARD_SHARED_EP = yes
MOUSE_SHARED_EP = no

# Rotary Encoder support
ENCODER_ENABLE = no

# MIDI Enable
MIDI_ENABLE = no

# OLED Enable
OLED_ENABLE = no

# OLED Display Driver
OLED_DRIVER = SSD1306
