# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = full	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = no # once arm_rgb is implemented
RGB_MATRIX_DRIVER = WS2812
HAPTIC_ENABLE += DRV2605L
QWIIC_ENABLE = yes
QWIIC_DRIVERS += MICRO_OLED
ENCODER_ENABLER = yes
# SERIAL_LINK_ENABLE = yes
