BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE    = no       # Mouse keys
EXTRAKEY_ENABLE    = yes       # Audio control and System control
TAP_DANCE_ENABLE   = no
SPACE_CADET_ENABLE = no
NKRO_ENABLE        = yes
CAPS_WORD_ENABLE   = no

ifneq ($(strip $(KEYBOARD)), planck/rev6)
    CONSOLE_ENABLE              = no
    COMMAND_ENABLE              = no
    ifeq ($(strip $(LAYOUT_HAS_RGB)), yes)
        RGBLIGHT_ENABLE         = yes
        INDICATOR_LIGHTS        = yes
        RGBLIGHT_STARTUP_ANIMATION  = yes
    endif
else
    CONSOLE_ENABLE              = yes
    RGBLIGHT_ENABLE             = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
    RGB_MATRIX_ENABLE           = no
    AUDIO_ENABLE                = yes
    EEPROM_DRIVER               = i2c
    ENCODER_MAP_ENABLE          = yes
    AUTOCORRECTION_ENABLE       = yes
    CAPS_WORD_ENABLE            = yes
endif
ifeq ($(strip $(KEYBOARD)), planck/light)
    RGB_MATRIX_ENABLE           = yes
    RGBLIGHT_ENABLE             = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
    AUDIO_ENABLE                = yes
endif
ifeq ($(strip $(KEYBOARD)), planck/ez)
    RGBLIGHT_ENABLE             = no
    ENCODER_ENABLE              = yes
    ENCODER_MAP_ENABLE          = yes
    RGB_MATRIX_ENABLE           = yes
    INDICATOR_LIGHTS            = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
    CONSOLE_ENABLE              = yes
    COMMAND_ENABLE              = yes
    AUDIO_ENABLE                = yes
    AUTOCORRECTION_ENABLE       = yes
    CAPS_WORD_ENABLE            = yes
endif
