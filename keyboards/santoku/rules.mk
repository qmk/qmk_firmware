MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu


BOOTMAGIC_ENABLE = yes  # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = yes       # USB Nkey Rollover

# Options that are specific to current build of Santoku
WPM_ENABLE = yes        # Enable Words Per Minute Count for OLED 
POINTING_DEVICE_ENABLE = yes # used for the scroll wheel
PS2_MOUSE_ENABLE = yes
PS2_USE_USART = yes
# PS2_USE_INT = yes
# PS2_USE_BUSYWAIT = yes
ENCODER_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE = yes
