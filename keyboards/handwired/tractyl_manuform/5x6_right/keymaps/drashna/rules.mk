COMMAND_ENABLE                   = no
RGBLIGHT_ENABLE                  = yes
RGBLIGHT_STARTUP_ANIMATION       = yes
AUDIO_ENABLE                     = yes
HAPTIC_ENABLE                    = no
TAP_DANCE_ENABLE                 = yes
OLED_ENABLE                      = yes
WPM_ENABLE                       = yes
ENCODER_ENABLE                   = yes
ENCODER_MAP_ENABLE               = yes
AUTOCORRECTION_ENABLE            = yes
CAPS_WORD_ENABLE                 = yes

ifeq ($(strip $(KEYBOARD)), handwired/tractyl_manuform/5x6_right/elite_c)
    RGBLIGHT_ENABLE              = no
    AUDIO_ENABLE                 = no
    HAPTIC_ENABLE                = no
    TAP_DANCE_ENABLE             = no
    OLED_ENABLE                  = no
    WPM_ENABLE                   = no
    ENCODER_ENABLE               = no
    AUTOCORRECTION_ENABLE        = no
    LTO_SUPPORTED                = yes
    SWAP_HANDS_ENABLE            = no
    CUSTOM_UNICODE_ENABLE        = no
    CAPS_WORD_ENABLE             = no
    BOOTLOADER                   = qmk-hid
    BOOTLOADER_SIZE              = 512
endif
ifeq ($(strip $(KEYBOARD)), handwired/tractyl_manuform/5x6_right/teensy2pp)
    AUTOCORRECTION_ENABLE        = no
    CAPS_WORD_ENABLE             = yes
endif
# DEBOUNCE_TYPE = sym_eager_pk

OLED_DRIVER = custom
