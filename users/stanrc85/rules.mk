TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes
BACKLIGHT_ENABLE = no
COMMAND_ENABLE = no
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
AUDIO_ENABLE = no
CONSOLE_ENABLE = no
NKRO_ENABLE = no

SRC += stanrc85.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # Include my fancy rgb functions source here
  SRC += layer_rgb.c
endif

ifeq ($(strip $(KEYBOARD)), 1upkeyboards/1up60hse)
  VIA_ENABLE = yes
  LTO_ENABLE = yes
endif
ifeq ($(strip $(KEYBOARD)), dz60)
  VIA_ENABLE = yes
  LTO_ENABLE = yes
endif
ifeq ($(strip $(KEYBOARD)), projectkb/alice)
  VIA_ENABLE = yes
  LTO_ENABLE = yes
endif