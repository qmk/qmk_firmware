# MCU name
MCU = STM32F411
BOARD = BLACKPILL_STM32_F411

# Bootloader selection
BOOTLOADER := tinyuf2

BOOTMAGIC_ENABLE      = yes # Enable Bootmagic Lite
MOUSEKEY_ENABLE       = yes # Mouse keys
EXTRAKEY_ENABLE       = yes # Audio control and System control
CONSOLE_ENABLE        = yes # Console for debug
COMMAND_ENABLE        = no  # Commands for debug and configuration
NKRO_ENABLE           = yes # Enable N-Key Rollover
RGBLIGHT_ENABLE       = no  # Enable keyboard RGB underglow
AUDIO_ENABLE          = yes # Audio output
AUDIO_SUPPORTED       = yes # is set to no in kb, needs to be forcibly enabled

KEYBOARD_SHARED_EP    = yes
MOUSE_SHARED_EP       = yes

EEPROM_DRIVER         = spi
WS2812_DRIVER         = pwm
SERIAL_DRIVER         = usart
AUDIO_DRIVER          = pwm_hardware
BACKLIGHT_DRIVER      = pwm

AUTOCORRECTION_ENABLE = yes
CAPS_WORD_ENABLE      = yes
SWAP_HANDS_ENABLE     = yes
TAP_DANCE_ENABLE      = yes
DEBOUNCE_TYPE         = asym_eager_defer_pk
WPM_ENABLE            = yes
LTO_ENABLE            = no
# OPT                   = 3
