BOOTMAGIC_ENABLE  = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes       # Audio control and System control(+450)
CONSOLE_ENABLE    = no         # Console for debug(+400)
COMMAND_ENABLE    = no        # Commands for debug and configuration
TAP_DANCE_ENABLE  = no
AUDIO_ENABLE      = yes
ifeq (,$(findstring planck/rev6,$(KEYBOARD)))
  RGBLIGHT_ENABLE   = yes
  INDICATOR_LIGHTS  = yes
  RGBLIGHT_TWINKLE  = yes
endif
ifneq (,$(findstring planck/light,$(KEYBOARD)))
  RGB_MATRIX_ENABLE   = yes
  RGBLIGHT_ENABLE     = no
endif

ifeq ($(strip $(PROTOCOL)), VUSB)
NKRO_ENABLE       = no
else
NKRO_ENABLE       = yes
endif


MACROS_ENABLED    = no

