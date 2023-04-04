# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = qmk-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no  
COMMAND_ENABLE = no  
NKRO_ENABLE = yes    
BACKLIGHT_ENABLE = no
AUDIO_ENABLE = no    
RGBLIGHT_ENABLE = yes
KEY_LOCK_ENABLE = yes
UNICODE_ENABLE = yes 

SPLIT_KEYBOARD = yes
ENCODER_ENABLE = no
TRI_LAYER_ENABLE = yes

LTO_ENABLE = yes
