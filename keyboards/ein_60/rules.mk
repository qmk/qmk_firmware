# MCU name
MCU = at90usb1286

# Bootloader selection
BOOTLOADER = qmk-dfu
##LAYOUTS = split_4x6_2

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = no       # Enable for pretty RGB matrix effects
#RGB_MATRIX_DRIVER = WS2812  # Define RGB Matrix
ENCODER_ENABLE = yes        # Enables the use of one or more encoders
OLED_DRIVER_ENABLE = yes    # Enables the use of OLED displays
WPM_ENABLE = yes            # Enables default WPM display
