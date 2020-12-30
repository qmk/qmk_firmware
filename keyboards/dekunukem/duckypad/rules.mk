<<<<<<< HEAD
MCU = STM32F072
BOARD = ST_STM32F072B_DISCOVERY

BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
SLEEP_LED_ENABLE = no
NKRO_ENABLE = no
RGBLIGHT_ENABLE = no

# TODO: Can we get this working with SPI?
WS2812_DRIVER = bitbang
RGB_MATRIX_ENABLE = WS2812

OLED_DRIVER_ENABLE = yes
=======
# MCU Name
MCU = STM32F072

# Build Options
#  change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here:  https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output

WS2812_DRIVER = bitbang
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

OLED_DRIVER_ENABLE = yes
>>>>>>> 0f5f6a6a75b26d06ae5ee2b726eb97a67d04d325
