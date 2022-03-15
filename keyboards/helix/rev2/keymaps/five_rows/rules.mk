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

CUSTOM_DELAY = yes

ifneq ($(strip $(HELIX)),)
  define KEYMAP_OPTION_PARSE
    # parse  'dispoff', 'consloe', 'na', 'ani', 'mini-ani', 'scan-api',
    $(if $(SHOW_PARCE),$(info parse -$1-))  #debug
    ifeq ($(strip $1),dispoff)
        OLED_ENABLE = no
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = no
    endif
    ifneq ($(filter nooled no-oled,$(strip $1)),)
        OLED_ENABLE = no
    endif
    ifeq ($(strip $1),oled)
        OLED_ENABLE = yes
    endif
    ifneq ($(filter core-oled core_oled newoled new-oled olednew oled-new,$(strip $1)),)
        OLED_ENABLE = yes
        OLED_SELECT = core
    endif
    ifneq ($(filter local-oled local_oled oldoled old-oled oledold oled-old,$(strip $1)),)
        OLED_ENABLE = yes
        OLED_SELECT = local
    endif
    ifeq ($(strip $1),console)
        CONSOLE_ENABLE = yes
    endif
    ifeq ($(strip $1),debug)
        DEBUG_CONFIG = yes
    endif
    ifneq ($(filter nodebug no-debug no_debug,$(strip $1)),)
        DEBUG_CONFIG = no
    endif
    ifneq ($(filter na no_ani no-ani,$(strip $1)),)
        LED_ANIMATIONS = no
    endif
    ifneq ($(filter mini-ani mini_ani,$(strip $1)),)
        LED_ANIMATIONS = mini
    endif
    ifneq ($(filter ani animation,$(strip $1)),)
        LED_ANIMATIONS = yes
    endif
    ifeq ($(strip $1),lto)
        LTO_ENABLE = yes
    endif
    ifneq ($(filter nolto no-lto no_lto,$(strip $1)),)
        LTO_ENABLE = no
    endif
    ifeq ($(strip $1),scan-api)
        # use DEBUG_MATRIX_SCAN_RATE
        # see docs/newbs_testing_debugging.md
        DEBUG_MATRIX_SCAN_RATE_ENABLE = api
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(HELIX)),  \
      $(call KEYMAP_OPTION_PARSE,$(A_OPTION_NAME))))
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DLED_ANIMATIONS_LEVEL=2
endif

ifeq ($(strip $(LED_ANIMATIONS)), mini)
    OPT_DEFS += -DLED_ANIMATIONS_LEVEL=1
    LED_ANIMATIONS = yes
endif

ifeq ($(strip $(DEBUG_CONFIG)), yes)
    OPT_DEFS += -DDEBUG_CONFIG
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled_display.c
endif

ifeq ($(strip $(CUSTOM_DELAY)),yes)
    SRC += matrix_output_unselect_delay.c
endif
