# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/keyboards/helix/rules.mk for a list of options that can be set.
#   See TOP/docs/config_options.md for more information.
#
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
AUDIO_ENABLE = yes          # Audio output on port B5
LTO_ENABLE = no  # if firmware size over limit, try this option

# Helix Spacific Build Options
# you can uncomment and edit follows 4 Variables
#  jp: 以下の4つの変数を必要に応じて編集し、コメントアウトをはずします。
# LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
# LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
# LED_ANIMATIONS = yes        # LED animations
# IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
