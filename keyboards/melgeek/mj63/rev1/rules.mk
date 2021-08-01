# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes          # Mouse keys
EXTRAKEY_ENABLE = yes          # Audio control and System control
CONSOLE_ENABLE = no            # Console for debug
COMMAND_ENABLE = no            # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no          # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes              # USB Nkey Rollover
BACKLIGHT_ENABLE = no          # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no           # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no          # Enable Bluetooth
RGB_MATRIX_ENABLE = yes        # Use RGB matrix
RGB_MATRIX_DRIVER = IS31FL3741
NO_USB_STARTUP_CHECK = no      # Disable initialization only when usb is plugged in

LAYOUTS = 60_ansi_arrow
