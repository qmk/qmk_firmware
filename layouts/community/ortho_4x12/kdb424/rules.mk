BOOTLOADER        = qmk-dfu # caterina is bad and it should feel bad. I don't use anything but DFU
BACKLIGHT_ENABLE  = no      # Enable keyboard backlight functionality
TAP_DANCE_ENABLE  = yes     # Enable tap dance.
USE_IC2           = no
AUDIO_ENABLE      = no
RGBLIGHT_ENABLE   = no
UNICODE_ENABLE    = no
UNICODEMAP_ENABLE = yes
UCIS_ENABLE       = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

# Enable N-Key Rollover, except in cases of VUSB:
# Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
ifeq ($(strip $(PROTOCOL)), VUSB)
  NKRO_ENABLE = no
else
  NKRO_ENABLE = yes
endif

#EXTRAFLAGS        += -flto
