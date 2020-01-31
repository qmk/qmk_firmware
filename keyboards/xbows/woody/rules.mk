# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration
BACKLIGHT_ENABLE = no
MOUSEKEY_ENABLE = yes              # Mouse keys
EXTRAKEY_ENABLE = yes              # Audio control and System control
CONSOLE_ENABLE = no                # Console for debug
COMMAND_ENABLE = no                # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes            # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes                 # USB Nkey Rollover
AUDIO_ENABLE = no
RGB_MATRIX_ENABLE = yes     # Use RGB matrix
NO_USB_STARTUP_CHECK = no          # Disable initialization only when usb is plugged in
