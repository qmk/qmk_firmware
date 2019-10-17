BOOTMAGIC_ENABLE  = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes       # Audio control and System control(+450)
CONSOLE_ENABLE    = no         # Console for debug(+400)
COMMAND_ENABLE    = no        # Commands for debug and configuration
TAP_DANCE_ENABLE  = no
AUDIO_ENABLE      = yes
SPACE_CADET_ENABLE = no

ifneq ($(strip $(KEYBOARD)), planck/rev6)
	RGBLIGHT_ENABLE             = yes
	INDICATOR_LIGHTS            = yes
	RGBLIGHT_TWINKLE            = yes
	RGBLIGHT_STARTUP_ANIMATION  = yes
endif
ifeq ($(strip $(KEYBOARD)), planck/light)
	RGB_MATRIX_ENABLE           = yes
	RGBLIGHT_ENABLE             = no
	RGBLIGHT_STARTUP_ANIMATION  = no
	HAPTIC_ENABLE               += SOLENOID
endif
ifeq ($(strip $(KEYBOARD)), planck/ez)
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
