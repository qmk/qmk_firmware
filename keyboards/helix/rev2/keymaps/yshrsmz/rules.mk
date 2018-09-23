
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
SWAP_HANDS_ENABLE = no        # Enable one-hand typing

define HELIX_CUSTOMISE_MSG
  $(info Helix customize)
  $(info -  OLED_ENABLE=$(OLED_ENABLE))
  $(info -  LED_BACK_ENABLE=$(LED_BACK_ENABLE))
  $(info -  LED_UNDERGLOW_ENABLE=$(LED_UNDERGLOW_ENABLE))
  $(info -  LED_ANIMATION=$(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE=$(IOS_DEVICE_ENABLE))
endef

# Helix keyboard customize
# you can edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集します。
HELIX_ROWS = 4              # Helix Rows is 4 or 5
OLED_ENABLE = yes            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = no        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

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
ifneq ($(strip $(HELIX)),)
  ifeq ($(findstring oled,$(HELIX)), oled)
    OLED_ENABLE = yes
  endif
  ifeq ($(findstring back,$(HELIX)), back)
    LED_BACK_ENABLE = yes
  else ifeq ($(findstring under,$(HELIX)), under)
    LED_UNDERGLOW_ENABLE = yes
  endif
  ifeq ($(findstring na,$(HELIX)), na)
    LED_ANIMATIONS = no
  endif
  ifeq ($(findstring ios,$(HELIX)), ios)
    IOS_DEVICE_ENABLE = yes
  endif
  $(eval $(call HELIX_CUSTOMISE_MSG))
  $(info )
endif

# Uncomment these for checking
#   jp: コンパイル時にカスタマイズの状態を表示したい時はコメントをはずします。
# $(eval $(call HELIX_CUSTOMISE_MSG))
# $(info )

ifneq ($(strip $(HELIX_ROWS)), 4)
  ifneq ($(strip $(HELIX_ROWS)), 5)
    $(error HELIX_ROWS = $(strip $(HELIX_ROWS)) is unexpected value)
  endif
endif
OPT_DEFS += -DHELIX_ROWS=$(strip $(HELIX_ROWS))

ifeq ($(strip $(LED_BACK_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DRGBLED_BACK
  ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
    $(eval $(call HELIX_CUSTOMISE_MSG))
    $(error LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE both 'yes')
  endif
else ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
else
  RGBLIGHT_ENABLE = no
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DRGBLIGHT_ANIMATIONS
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

AUTO_SHIFT_ENABLE = yes

# Uncomment these for debugging
# $(info -- RGBLIGHT_ENABLE=$(RGBLIGHT_ENABLE))
# $(info -- OPT_DEFS=$(OPT_DEFS))
# $(info )
