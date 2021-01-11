BOOTMAGIC_ENABLE  = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes       # Audio control and System control(+450)
CONSOLE_ENABLE    = no         # Console for debug(+400)
COMMAND_ENABLE    = no        # Commands for debug and configuration
TAP_DANCE_ENABLE  = no
AUDIO_ENABLE      = yes
SPACE_CADET_ENABLE = no

ifeq (,$(findstring planck/rev6,$(KEYBOARD))) # Make sure it's NOT the Planck Rev6
    RGBLIGHT_ENABLE             = yes
    INDICATOR_LIGHTS            = yes
    RGBLIGHT_TWINKLE            = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
endif
ifneq (,$(findstring planck/light,$(KEYBOARD))) # Make sure it IS the Planck Light
    RGB_MATRIX_ENABLE           = yes
    RGBLIGHT_ENABLE             = no
    RGBLIGHT_STARTUP_ANIMATION  = no
endif
ifneq (,$(findstring planck/ez,$(KEYBOARD))) # Make sure it IS the Planck Light
    RGBLIGHT_ENABLE = no
    # SERIAL_LINK_ENABLE = yes
    ENCODER_ENABLE = yes
    RGB_MATRIX_ENABLE = IS31FL3737
    INDICATOR_LIGHTS            = yes
    RGBLIGHT_TWINKLE            = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
endif

ifeq ($(strip $(PROTOCOL)), VUSB)
NKRO_ENABLE       = no
else
NKRO_ENABLE       = yes
endif
