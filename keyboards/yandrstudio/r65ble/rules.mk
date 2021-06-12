# MCU name
MCU = STM32F303
# BOARD = QMK_PROTON_C
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
COMMAND_ENABLE = yes         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# NKRO_ENABLE = yes            # USB Nkey Rollover
#RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = spi
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no        # Breathing sleep LED during USB suspend
WPM_ENABLE = yes		 # Show APM.
ENCODER_ENABLE = yes
AUTO_SHIFT_ENABLE = no
VELOCIKEY_ENABLE = yes
# TAP_DANCE_ENABLE = yes
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
