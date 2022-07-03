TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes
BACKLIGHT_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
AUDIO_ENABLE = no
CONSOLE_ENABLE = no
NKRO_ENABLE = yes
LTO_ENABLE = yes
VIA_ENABLE = yes

SRC += stanrc85.c

ifeq ($(strip $(KEYBOARD)), projectkb/alice/rev2)
  SRC += rgblight_layers.c
  SRC += startup_fanfare.c
  OPT_DEFS += -DHAS_INDICATORS
  VELOCIKEY_ENABLE=yes
endif
ifeq ($(strip $(KEYBOARD)), sneakbox/aliceclone)
  SRC += indicator_layers_sneakbox.c
  SRC += startup_fanfare.c
  OPT_DEFS += -DHAS_INDICATORS
  OPT_DEFS += -DHAS_ROTARY
endif
ifeq ($(strip $(KEYBOARD)), tkc/osav2)
  SRC += rgblight_layers_osa.c
  VELOCIKEY_ENABLE=yes
  SRC += rgb_timeout.c
endif
ifeq ($(strip $(KEYBOARD)), jacky_studio/bear_65)
  BACKLIGHT_ENABLE = yes
  RGB_MATRIX_ENABLE = yes
  RGBLIGHT_ENABLE = no
  SRC += rgb_layers.c
endif
ifeq ($(strip $(KEYBOARD)), mechlovin/adelais/rgb_led/rev2)
  SRC += rgb_layers.c
  SRC += rgb_timeout.c
endif
ifeq ($(strip $(KEYBOARD)), mechlovin/adelais/standard_led/arm/rev4/stm32f303)
  OPT_DEFS += -DHAS_INDICATORS
  SRC += rgb_timeout.c
  SRC += indicator_layers_sneakbox.c
endif
ifeq ($(strip $(KEYBOARD)), nasu)
  SRC += indicator_layers_sneakbox.c
  SRC += startup_fanfare.c
  OPT_DEFS += -DHAS_INDICATORS
endif
