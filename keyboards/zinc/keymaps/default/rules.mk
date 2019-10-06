
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
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

define ZINC_CUSTOMISE_MSG
  $
  $
  $
  $
  $
endef

# Zinc keyboard customize
LED_BACK_ENABLE = no        # LED backlight 
LED_UNDERGLOW_ENABLE = no   # LED underglow 
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device 
Link_Time_Optimization = no # if firmware size over limit, try this option

####  LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE.
####    Do not enable these with audio at the same time.

### Zinc keyboard 'default' keymap: convenient command line option
##    make ZINC=<options> zinc:defualt
##    option= back | under | na | ios
##    ex.
##      make ZINC=under    zinc:defualt
##      make ZINC=under,ios zinc:defualt
##      make ZINC=back     zinc:default
##      make ZINC=back,na  zinc:default
##      make ZINC=back,ios zinc:default

ifneq 
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
#    OPT_DEFS += -DRGBLIGHT_ANIMATIONS
     OPT_DEFS += -DLED_ANIMATIONS

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
