# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = no # once arm_rgb is implemented
RGB_MATRIX_DRIVER = WS2812
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = DRV2605L
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
ENCODER_ENABLER = yes
