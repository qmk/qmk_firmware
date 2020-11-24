# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/keyboards/helix/rules.mk for a list of options that can be set.
#   See TOP/docs/config_options.md for more information.
#
 CONSOLE_ENABLE = no        # Console for debug
 COMMAND_ENABLE = no        # Commands for debug and configuration
 # CONSOLE_ENABLE and COMMAND_ENABLE
 #      yes, no  +1500
 #      yes, yes +3200
 #      no,  yes +400
LTO_ENABLE = no  # if firmware size over limit, try this option

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

ifneq ($(strip $(HELIX)),)
  define KEYMAP_OPTION_PARSE
    # $xinfo .$1.x #debug
    # parse  'dispoff', 'consle', 'stdole', 'oled', 'sc'
    ifeq ($(strip $1),dispoff)
        OLED_ENABLE = no
        OLED_DRIVER_ENABLE = no
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = no
    endif
    ifeq ($(strip $1),console)
        CONSOLE_ENABLE = yes
    endif
    ifeq ($(strip $1),stdole)
        ## make HELIX=stdole helix:five_rows -- use TOP/drivers/oled/oled_driver.c
        OLED_ENABLE = new
    endif
    ifeq ($(strip $1),oled)
         ## make HELIX=oled helix:five_rows -- use helix/local_drivers/ssd1306.c
        OLED_ENABLE = yes
    endif
    ifeq ($(strip $1),back)
        LED_BACK_ENABLE = yes
    endif
    ifeq ($(strip $1),sc)
        SPLIT_KEYBOARD = yes
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(HELIX)),  \
      $(call KEYMAP_OPTION_PARSE,$(A_OPTION_NAME))))
endif

ifeq ($(strip $(OLED_ENABLE)), new)
    OLED_DRIVER_ENABLE = yes
    OLED_ENABLE = no
    SRC += oled_display.c
    ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
       OPT_DEFS += -DOLED_FONT_H=\<helixfont.h\>
    else
       OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"
    endif
endif
ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled_display.c
endif

# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.
include $(strip $(KEYBOARD_LOCAL_FEATURES_MK))
