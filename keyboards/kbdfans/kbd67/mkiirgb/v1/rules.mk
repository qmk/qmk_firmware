# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = lite           # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes              # Mouse keys
EXTRAKEY_ENABLE = yes              # Audio control and System control
CONSOLE_ENABLE = no                # Console for debug
COMMAND_ENABLE = no                # Commands for debug and configuration
NKRO_ENABLE = yes                 # USB Nkey Rollover
AUDIO_ENABLE = no
RGB_MATRIX_ENABLE = yes            # Use RGB matrix
RGB_MATRIX_DRIVER = IS31FL3731

LAYOUTS = 65_ansi_blocker
