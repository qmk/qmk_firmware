USER_NAME := mtei
SPLIT_KEYBOARD = yes

 CONSOLE_ENABLE = no        # Console for debug
 COMMAND_ENABLE = no        # Commands for debug and configuration
 # CONSOLE_ENABLE and COMMAND_ENABLE
 #      yes, no  +1500
 #      yes, yes +3200
 #      no,  yes +400
LTO_ENABLE = no  # if firmware size over limit, try this option
LED_ANIMATIONS = yes

# Helix Spacific Build Options
# you can uncomment and edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集し、コメントアウトをはずします。
HELIX_ROWS = 5              # Helix Rows is 4 or 5
# OLED_ENABLE = no            # OLED_ENABLE
# LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
# LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
# LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
# LED_ANIMATIONS = yes        # LED animations
# IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
OLED_SELECT = core

SRC += oled_display.c
