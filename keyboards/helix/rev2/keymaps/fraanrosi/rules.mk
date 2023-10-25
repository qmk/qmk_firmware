# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/keyboards/helix/rules.mk for a list of options that can be set.
#   See TOP/docs/config_options.md for more information.
#
SPLIT_KEYBOARD = yes
LTO_ENABLE = yes         # if firmware size over limit, try this option
MOUSEKEY_ENABLE = yes    # Mouse keys
EXTRAKEY_ENABLE = yes    # Audio control and System control
# AUDIO_ENABLE = yes       # Audio output on port C6
# Helix Spacific Build Options
# you can uncomment and edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集し、コメントアウトをはずします。
# OLED_ENABLE = no            # OLED_ENABLE
# LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
# LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
# LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations
# IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

LED_BACK_ENABLE = no
LED_UNDERGLOW_ENABLE = yes
