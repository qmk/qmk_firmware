
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no        # Enable one-hand typing

define HELIX_CUSTOMISE_MSG
  $
  $
  $
  $
  $
  $
endef

# Helix keyboard customize
# you can edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集します。
HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = no            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight 
LED_UNDERGLOW_ENABLE = no   # LED underglow 
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device 
Link_Time_Optimization = no # if firmware size over limit, try this option

####  LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE.
####    Do not enable these with audio at the same time.

### Helix keyboard 'default' keymap: convenient command line option
##    make HELIX=<options> helix:defualt
##    option= oled | back | under | na | ios
##    ex.
##      make HELIX=oled          helix:defualt
##      make HELIX=oled,back     helix:defualt
##      make HELIX=oled,under    helix:defualt
##      make HELIX=oled,back,na  helix:defualt
##      make HELIX=oled,back,ios helix:defualt
##
ifneq 
  ifeq 
    OLED_ENABLE = yes
  endif
  ifeq 
    LED_BACK_ENABLE = yes
  else ifeq 
    LED_UNDERGLOW_ENABLE = yes
  endif
  ifeq 
    LED_ANIMATIONS = no
  endif
  ifeq 
    IOS_DEVICE_ENABLE = yes
  endif
  $
  $
endif

# Uncomment these for checking
#   jp: コンパイル時にカスタマイズの状態を表示したい時はコメントをはずします。
# $
# $

ifneq 
  ifneq 
    $
  endif
endif
OPT_DEFS += -DHELIX_ROWS=$

ifeq 
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DRGBLED_BACK
  ifeq 
    $
    $
  endif
else ifeq 
  RGBLIGHT_ENABLE = yes
else
  RGBLIGHT_ENABLE = no
endif

ifeq 
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq 
    OPT_DEFS += -DLED_ANIMATIONS
endif

ifeq 
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq 
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

ifeq 
    EXTRAFLAGS += -flto -DUSE_Link_Time_Optimization
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

# Uncomment these for debugging
# $
# $
# $
