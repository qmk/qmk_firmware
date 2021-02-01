# MCU name
MCU  = STM32F303

# Bootloader selection
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
DFU_SUFFIX_ARGS = -p DF11 -v 0483

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite            # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes              # Mouse keys
EXTRAKEY_ENABLE = yes              # Audio control and System control
CONSOLE_ENABLE = no                # Console for debug
COMMAND_ENABLE = no                # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes            # Breathing sleep LED during USB suspend
NKRO_ENABLE = no                   # USB Nkey Rollover
AUDIO_ENABLE = no
RGB_MATRIX_ENABLE = yes            # Use RGB matrix
RGB_MATRIX_DRIVER = IS31FL3733
NO_USB_STARTUP_CHECK = no          # Disable initialization only when usb is plugged in
