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

ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
    OLED_ENABLE            = yes
    RGB_MATRIX_ENABLE      = yes
    HAPTIC_ENABLE          = no
endif

ifeq ($(strip $(CTPC)), yes)
    HAPTIC_ENABLE          = no
    WS2812_DRIVER          = pwm # won't work without a patch to the ctpc mk file
    SERIAL_DRIVER          = usart
    SWAP_HANDS_ENABLE      = yes
    WPM_ENABLE             = yes
    AUTOCORRECTION_ENABLE  = yes
    CAPS_WORD_ENABLE       = yes
else
    CUSTOM_UNICODE_ENABLE  = no
    BOOTLOADER             = qmk-hid
    BOOTLOADER_SIZE        = 512
endif
