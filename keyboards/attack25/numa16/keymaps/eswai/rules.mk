
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
SWAP_HANDS_ENABLE = no        # Enable one-hand typing

define ATTACK25_CUSTOMISE_MSG
  	$(info Attack25 / numAttack16 customize)
  	$(info -  SMD_32u2=$(SMD_32u2))
  	$(info -  BACKLIGHT_ENABLE=$(BACKLIGHT_ENABLE))
  	$(info -  LED_UNDERGLOW_ENABLE=$(LED_UNDERGLOW_ENABLE))
  	$(info -  LED_ANIMATION=$(LED_ANIMATIONS))
  	$(info -  IOS_DEVICE_ENABLE=$(IOS_DEVICE_ENABLE))
endef

# numATTACK16 keyboard customize
SMD_32u2 = no               # on-board atmega32u2
BACKLIGHT_ENABLE = no        # LED backlight (Enable standard backlight, not WS2812)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 type RGB underlight)
LED_BOTH_ENABLE = no        # LED backlight and underglow
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
Link_Time_Optimization = no # if firmware size over limit, try this option
####  LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE.
####    Do not enable these with audio at the same time.

### Attack25 keyboard 'default' keymap: convenient command line option
##    make ATTACK25=<options> attack25:defualt
##    option= smd | back | under | na | ios
##    ex.
##      make ATTACK25=smd      attack25/numattack16:universal
##      make ATTACK25=smd,under    attack25/numattack16:universal
##      make ATTACK25=smd,back,under attack25/numattack16:universal
##      make ATTACK25=back     attack25/numattack16:universal
##      make ATTACK25=back,under  attack25/numattack16:universal

ifneq ($(strip $(ATTACK25)),)
  	ifeq ($(findstring smd,$(ATTACK25)), smd)
    	SMD_32u2 = yes
  	endif
  	ifeq ($(findstring back,$(ATTACK25)), back)
    	BACKLIGHT_ENABLE =  yes
  	endif
  	ifeq ($(findstring under,$(ATTACK25)), under)
    	LED_UNDERGLOW_ENABLE = yes
  	endif
  	ifeq ($(findstring na,$(ATTACK25)), na)
    	LED_ANIMATIONS = no
  	endif
  	ifeq ($(findstring ios,$(ATTACK25)), ios)
    	IOS_DEVICE_ENABLE = yes
  	endif
  	$(eval $(call ATTACK25_CUSTOMISE_MSG))
  	$(info )
endif

ifeq ($(strip $(SMD_32u2)),yes)
	MCU = atmega32u2
endif

ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
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

ifeq ($(strip $(Link_Time_Optimization)),yes)
    EXTRAFLAGS += -flto -DUSE_Link_Time_Optimization
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

# Uncomment these for debugging
# $(info -- RGBLIGHT_ENABLE=$(RGBLIGHT_ENABLE))
# $(info -- OPT_DEFS=$(OPT_DEFS))
# $(info )
