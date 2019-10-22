MCU = atmega32u4
BOOTLOADER = atmel-dfu
OPT_DEFS += -DBOOTLOADER_SIZE=4096
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration(+1000)
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
