# force hard required features on - cannot be done in qmk_module.json
DYNAMIC_KEYMAP_ENABLE := yes
RAW_ENABLE := yes
BOOTMAGIC_ENABLE := yes

OPT_DEFS += -DVIA_ENABLE

ifeq ($(strip $(VIA_INSECURE)), yes)
	OPT_DEFS += -DVIA_INSECURE
endif
