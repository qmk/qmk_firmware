# MCU name
MCU = STM32F042

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control

CONSOLE_ENABLE = yes # Console for debug
COMMAND_ENABLE = yes # Commands for debug and configuration
NKRO_ENABLE = yes # USB Nkey Rollover
