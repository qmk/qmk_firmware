# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options

#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = full      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes      # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
AUDIO_ENABLE = yes           # Audio output on port C6
RGBLIGHT_ENABLE = no
ENCODER_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend

ENCODER_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3737

MOUSE_SHARED_EP = no

LAYOUTS = ortho_4x12
LAYOUTS_HAS_RGB = no
