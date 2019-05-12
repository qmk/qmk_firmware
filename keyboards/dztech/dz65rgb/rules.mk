MCU  = STM32F303
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
DFU_SUFFIX_ARGS = -p DF11 -v 0483
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = lite           # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes              # Mouse keys
EXTRAKEY_ENABLE = yes              # Audio control and System control
CONSOLE_ENABLE = no                # Console for debug
COMMAND_ENABLE = no                # Commands for debug and configuration
NKRO_ENABLE = yes                 # USB Nkey Rollover
AUDIO_ENABLE = no
RGB_MATRIX_ENABLE = yes     # Use RGB matrix

LAYOUTS = 65_ansi
