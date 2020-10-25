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

ifeq ($(strip $(KEYBOARD)), projectkb/alice/rev2)
  SRC += rgblight_layers.c
  SRC += startup_fanfare.c
  OPT_DEFS += -DHAS_INDICATORS
  VIA_ENABLE = yes
  LTO_ENABLE = no
  VELOCIKEY_ENABLE=yes
endif
ifeq ($(strip $(KEYBOARD)), tkc/osav2)
  SRC += rgblight_layers_osa.c
  VIA_ENABLE = yes
  LTO_ENABLE = no
  VELOCIKEY_ENABLE=yes
endif