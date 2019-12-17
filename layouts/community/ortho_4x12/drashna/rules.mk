BOOTMAGIC_ENABLE   = lite       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE    = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE    = yes       # Audio control and System control(+450)
TAP_DANCE_ENABLE   = no
AUDIO_ENABLE       = yes
SPACE_CADET_ENABLE = no
NKRO_ENABLE        = yes

ifneq ($(strip $(KEYBOARD)), planck/rev6)
    CONSOLE_ENABLE    			= no
    COMMAND_ENABLE    			= no
    ifeq ($(strip $(LAYOUT_HAS_RGB)), yes)
        RGBLIGHT_ENABLE         = yes
	endif
    INDICATOR_LIGHTS            = yes
    RGBLIGHT_TWINKLE            = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
else
    CONSOLE_ENABLE    			= yes
    COMMAND_ENABLE    			= yes
    RGBLIGHT_ENABLE             = no
    RGB_MATRIX_ENABLE           = WS2812
endif
ifeq ($(strip $(KEYBOARD)), planck/light)
    RGB_MATRIX_ENABLE           = yes
    RGBLIGHT_ENABLE             = no
    RGBLIGHT_STARTUP_ANIMATION  = no
    # HAPTIC_ENABLE               += SOLENOID
endif
ifeq ($(strip $(KEYBOARD)), planck/ez)
    RGBLIGHT_ENABLE = no
    # SERIAL_LINK_ENABLE = yes
    ENCODER_ENABLE = yes
    RGB_MATRIX_ENABLE = IS31FL3737
    INDICATOR_LIGHTS            = yes
    RGBLIGHT_TWINKLE            = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
    CONSOLE_ENABLE    			= yes
    COMMAND_ENABLE    			= yes
endif
