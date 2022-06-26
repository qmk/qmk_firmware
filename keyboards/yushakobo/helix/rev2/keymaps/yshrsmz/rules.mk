# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/keyboards/helix/rules.mk for a list of options that can be set.
#   See TOP/docs/config_options.md for more information.
#
LTO_ENABLE = no  # if firmware size over limit, try this option
SPLIT_KEYBOARD = yes

# Helix Spacific Build Options
# you can uncomment and edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集し、コメントアウトをはずします。
# HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = yes            # OLED_ENABLE
# LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
# LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
# LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = no        # LED animations
# IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

# OLED_ENABLE が yes のとき
#   OLED_SELECT が core ならば QMK 標準の oled_dirver.c を使用します。
#   OLED_SELECT が core 以外ならば従来どおり helix/local_drivers/ssd1306.c を使用します。
# If OLED_ENABLE is 'yes'
#   If OLED_SELECT is 'core', use QMK standard oled_dirver.c.
#   If OLED_SELECT is other than 'core', use helix/local_drivers/ssd1306.c.
OLED_SELECT = core
