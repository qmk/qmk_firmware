# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no      # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output
OLED_DRIVER_ENABLE = no
ENCODER_ENABLE = yes
UNICODE_ENABLE = no
DYNAMIC_MACRO_ENABLE = yes
COMBO_ENABLE = no
AUTO_SHIFT_ENABLE = no

NO_USB_STARTUP_CHECK = yes
WAIT_FOR_USB = no

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360
KEYBOARD_SHARED_EP = yes
MOUSE_SHARED_EP = no

DEFAULT_FOLDER = tractyl