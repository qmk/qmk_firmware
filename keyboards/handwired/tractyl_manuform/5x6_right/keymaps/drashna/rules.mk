AUTOCORRECT_ENABLE               = no
AUDIO_ENABLE                     = no
ENCODER_ENABLE                   = no
CUSTOM_BOOTMAGIC_ENABLE          = no
CUSTOM_UNICODE_ENABLE            = no
HAPTIC_ENABLE                    = no
OLED_ENABLE                      = no
OLED_DRIVER                      = custom
RGBLIGHT_ENABLE                  = no
SWAP_HANDS_ENABLE                = no
TAP_DANCE_ENABLE                 = no
WPM_ENABLE                       = no

ifeq ($(strip $(KEYBOARD)), handwired/tractyl_manuform/5x6_right/elite_c)
    BOOTLOADER                       = qmk-hid
    BOOTLOADER_SIZE                  = 512
    CUSTOM_SPLIT_TRANSPORT_SYNC      = no
    LTO_ENABLE                       = yes
endif
ifeq ($(strip $(KEYBOARD)), handwired/tractyl_manuform/5x6_right/arduinomicro)
    BOOTLOADER                       = qmk-hid
    BOOTLOADER_SIZE                  = 512
    CUSTOM_SPLIT_TRANSPORT_SYNC      = no
    LTO_ENABLE                       = yes
endif
ifeq ($(strip $(KEYBOARD)), handwired/tractyl_manuform/5x6_right/teensy2pp)
    AUTOCORRECT_ENABLE               = no
    OVERLOAD_FEATURES                = yes
    LTO_ENABLE                       = yes
endif
ifeq ($(strip $(KEYBOARD)), handwired/tractyl_manuform/5x6_right/f411)
    BOOTLOADER                       = tinyuf2
    AUTOCORRECT_ENABLE               = yes
    LTO_SUPPORTED                    = no
    OVERLOAD_FEATURES                = yes
endif
# DEBOUNCE_TYPE = sym_eager_pk

ifeq ($(strip $(OVERLOAD_FEATURES)), yes)
    AUDIO_ENABLE                     = yes
    CAPS_WORD_ENABLE                 = yes
    CUSTOM_BOOTMAGIC_ENABLE          = yes
    CUSTOM_UNICODE_ENABLE            = yes
    ENCODER_ENABLE                   = yes
    ENCODER_MAP_ENABLE               = yes
    OLED_ENABLE                      = yes
    RGBLIGHT_ENABLE                  = yes
    RGBLIGHT_STARTUP_ANIMATION       = yes
    TAP_DANCE_ENABLE                 = yes
    SWAP_HANDS_ENABLE                = yes
    WPM_ENABLE                       = yes
endif
