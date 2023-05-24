# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
SWAP_HANDS_ENABLE = no        # Enable one-hand typing
LTO_ENABLE = no             # if firmware size over limit, try this option

define ZINC_CUSTOMISE_MSG
  $(info Zinc customize)
  $(info -  LED_BACK_ENABLE=$(LED_BACK_ENABLE))
  $(info -  LED_UNDERGLOW_ENABLE=$(LED_UNDERGLOW_ENABLE))
  $(info -  LED_BOTH_ENABLE=$(LED_BOTH_ENABLE))
  $(info -  LED_RGB_CONT=$(LED_RGB_CONT))
  $(info -  LED_ANIMATION=$(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE=$(IOS_DEVICE_ENABLE))
endef

# Zinc keyboard customize
LED_BACK_ENABLE = no        # LED backlight (Enable SK6812mini backlight)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight)
LED_BOTH_ENABLE = no        # LED backlight and underglow
LED_RGB_CONT = no           # LED continuous backlight or/and underglow between left Zinc and right Zinc
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

####  LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE.
####    Do not enable these with audio at the same time.

### Zinc keyboard 'default' keymap: convenient command line option
##    make ZINC=<options> zinc:defualt
##    option= back | under | both | cont | na | ios
##    ex.
##      make ZINC=under    zinc:defualt
##      make ZINC=under,ios zinc:defualt
##      make ZINC=back     zinc:default
##      make ZINC=back,na  zinc:default
##      make ZINC=back,ios zinc:default

ifneq ($(strip $(ZINC)),)
  ifeq ($(findstring back,$(ZINC)), back)
    LED_BACK_ENABLE = yes
  endif
  ifeq ($(findstring under,$(ZINC)), under)
    LED_UNDERGLOW_ENABLE = yes
  endif
  ifeq ($(findstring both,$(ZINC)), both)
    LED_BOTH_ENABLE = yes
  endif
  ifeq ($(findstring cont,$(ZINC)), cont)
    LED_RGB_CONT = yes
  endif
  ifeq ($(findstring na,$(ZINC)), na)
    LED_ANIMATIONS = no
  endif
  ifeq ($(findstring ios,$(ZINC)), ios)
    IOS_DEVICE_ENABLE = yes
  endif
  $(eval $(call ZINC_CUSTOMISE_MSG))
  $(info )
endif

ifeq ($(strip $(LED_BACK_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
  ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
    OPT_DEFS += -DRGBLED_BOTH
    $(info LED_BOTH_ENABLE option is enabled instead of LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE)
  else
    OPT_DEFS += -DRGBLED_BACK
  endif
else ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
else
  RGBLIGHT_ENABLE = no
endif

ifeq ($(strip $(LED_BOTH_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DRGBLED_BOTH
endif

ifeq ($(strip $(LED_RGB_CONT)), yes)
  OPT_DEFS += -DRGBLED_CONT
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
  OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
# OPT_DEFS += -DRGBLIGHT_ANIMATIONS
  OPT_DEFS += -DLED_ANIMATIONS

endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

# Uncomment these for debugging
# $(info -- RGBLIGHT_ENABLE=$(RGBLIGHT_ENABLE))
# $(info -- OPT_DEFS=$(OPT_DEFS))
# $(info )
