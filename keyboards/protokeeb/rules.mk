# Build Options
# Change yes to no to diable feature

# Custom scanning of matrix
#CUSTOM_MATRIX = lite

# SPI Flash driver
#FLASH_DRIVER = spi

# EEPROM driver
#EEPROM_DRIVER = spi
#EEPROM_DRIVER = wear_leveling
#WEAR_LEVELING_DRIVER = spi_flash

# Debounce Method
#DEBOUNCE_TYPE = sym_defer_g # Default Method

# OS detection
OS_DETECTION_ENABLE = yes

# Enable Bootmagic Lite
#BOOTMAGIC_ENABLE = yes

# Development Board used
#BOARD = GENERIC_RP_RP2040

# Bootlader Selection
#BOOTLOADER = rp2040

# Enable N-Key Rollover
#NKRO_ENABLE = yes

# ARGB LED Driver used
#WS2812_DRIVER = vendor # For RP2040 MCU

# Rotary Encoder support
ENCODER_ENABLE = yes
# Rotary Encoder Keymap support
ENCODER_MAP_ENABLE = yes

# DIP Switch support
# Note: Here using for Encoder Push Button Functionality
#DIP_SWITCH_ENABLE = yes
# DIP Switch Keymap support
DIP_SWITCH_MAP_ENABLE = no

# Refer: USB Endpoint Limitations
#KEYBOARD_SHARED_EP = yes
#MOUSE_SHARED_EP = no