# Build Options
#   change to "no" to disable the options
#

BOOTMAGIC_ENABLE           = yes # Enable Bootmagic Lite
MOUSEKEY_ENABLE            = no  # Mouse keys
EXTRAKEY_ENABLE            = yes # Audio control and System control
CONSOLE_ENABLE             = no  # Console for debug
COMMAND_ENABLE             = no  # Commands for debug and configuration
NKRO_ENABLE                = yes # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE           = no  # Enable keyboard backlight functionality
AUDIO_ENABLE               = no  # Audio output
UNICODE_ENABLE             = no  # Unicode
RGBLIGHT_ENABLE            = no  # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE          = no  # Enable one-hand typing
OS_DETECTION_ENABLE        = no
CUSTOM_UNICODE_ENABLE      = no
CUSTOM_POINTING_DEVICE     = no
CUSTOM_SPLIT_TRANSPORT_SYNC = no

USE_ARM_CONFIG ?= no
ifeq ($(strip $(CONVERT_TO)), proton_c)
    USE_ARM_CONFIG = yes
endif
ifeq ($(strip $(CTPC)), yes)
    USE_ARM_CONFIG = yes
endif
ifeq ($(strip $(MCU)), STM32F303)
    USE_ARM_CONFIG = yes
endif
ifeq ($(strip $(MCU)), STM32F401)
    USE_ARM_CONFIG = yes
endif
ifeq ($(strip $(MCU)), STM32F411)
    USE_ARM_CONFIG = yes
endif

ifeq ($(strip $(MCU)), atmega32u4)
    BOOTLOADER             = qmk-hid
    BOOTLOADER_SIZE        = 512
endif

ifeq ($(strip $(USE_ARM_CONFIG)), yes)
    HAPTIC_ENABLE          = no
    WS2812_DRIVER          = pwm # won't work without a patch to the ctpc mk file
    SERIAL_DRIVER          = usart
    WPM_ENABLE             = yes
    AUTOCORRECT_ENABLE     = yes
    CAPS_WORD_ENABLE       = yes
    OS_DETECTION_ENABLE    = yes
    CUSTOM_UNICODE_ENABLE      = no
    CUSTOM_POINTING_DEVICE     = no
    CUSTOM_SPLIT_TRANSPORT_SYNC = no
endif

ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
    OLED_ENABLE            = yes
    RGB_MATRIX_ENABLE      = yes
    HAPTIC_ENABLE          = no
endif
