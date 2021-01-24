
# MCU name
MCU = STM32F303

# Build Options
#   change yes to no to disable
#
ENCODER_ENABLE = no
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug 调试开关
COMMAND_ENABLE = yes         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no        # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes            # USB Nkey Rollover
RGBLIGHT_ENABLE = yes
VIA_ENABLE = NO
