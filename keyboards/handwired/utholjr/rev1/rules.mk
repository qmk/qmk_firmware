# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu

BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
NKRO_ENABLE = yes	    # USB Nkey Rollover
KEYBOARD_SHARED_EP = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
TAP_DANCE_ENABLE = yes
