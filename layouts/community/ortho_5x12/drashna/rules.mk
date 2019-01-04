BOOTMAGIC_ENABLE  = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes       # Audio control and System control(+450)
CONSOLE_ENABLE    = no         # Console for debug(+400)
COMMAND_ENABLE    = no        # Commands for debug and configuration
TAP_DANCE_ENABLE  = no
AUDIO_ENABLE      = yes
ifneq (,$(findstring fractal,$(KEYBOARD))) # Make sure it IS the Planck Light
  RGB_MATRIX_ENABLE   = no
  AUDIO_ENABLE        = no
  RGBLIGHT_ENABLE     = yes
  RGBLIGHT_TWINKLE    = yes
  BOOTLOADER          = qmk-dfu
endif

ifeq ($(strip $(PROTOCOL)), VUSB)
NKRO_ENABLE       = no
else
NKRO_ENABLE       = yes
endif


MACROS_ENABLED    = no
