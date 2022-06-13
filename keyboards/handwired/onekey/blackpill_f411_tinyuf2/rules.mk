# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = tinyuf2

KEYBOARD_SHARED_EP = yes

# Use the wear-leveling driver
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = stm32f4x1