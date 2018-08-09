RGBLIGHT_ENABLE   = no
AUDIO_ENABLE      = no
BOOTLOADER        = qmk-dfu # caterina is bad and it should feel bad. I don't use anything but DFU
BACKLIGHT_ENABLE  = no      # Enable keyboard backlight functionality
NKRO_ENABLE       = no      # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
TAP_DANCE_ENABLE  = yes     # Enable tap dance.
AUTO_SHIFT_ENABLE = no      # Auto hold shift on longer keypress

EXTRAFLAGS        += -flto

