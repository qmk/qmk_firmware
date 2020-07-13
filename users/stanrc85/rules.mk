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

ifeq ($(strip $(KEYBOARD)), 1upkeyboards/1up60hse)
  SRC += layer_rgb.c
  VIA_ENABLE = yes
  LTO_ENABLE = yes
endif
ifeq ($(strip $(KEYBOARD)), dz60)
  SRC += layer_rgb.c
  VIA_ENABLE = yes
  LTO_ENABLE = yes
endif
ifeq ($(strip $(KEYBOARD)), projectkb/alice/rev1)
  SRC += rgblight_layers.c
  VIA_ENABLE = yes
  LTO_ENABLE = no
  VELOCIKEY_ENABLE=yes
endif
ifeq ($(strip $(KEYBOARD)), projectkb/alice/rev2)
  SRC += rgblight_layers.c
  VIA_ENABLE = yes
  LTO_ENABLE = no
  VELOCIKEY_ENABLE=yes
endif