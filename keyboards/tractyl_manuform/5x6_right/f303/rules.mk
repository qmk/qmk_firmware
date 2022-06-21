# MCU name
MCU = STM32F303

# Bootloader selection
BOOTLOADER = stm32-dfu

# KEYBOARD_SHARED_EP = yes
CONSOLE_ENABLE     = yes

EEPROM_DRIVER = spi
WS2812_DRIVER = pwm
SERIAL_DRIVER = usart
AUDIO_DRIVER  = dac_additive
