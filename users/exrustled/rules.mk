MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control

TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes

SRC += exrustled.c # keymap

# select alternative base layer alphas
ifneq ($(strip $(ALPHAS)),)
  OPT_DEFS += -DALPHAS_$(ALPHAS)
endif

# select alternative subset mappings
ifneq ($(strip $(MAPPING)),)
  OPT_DEFS += -DMAPPING_$(MAPPING)
endif
