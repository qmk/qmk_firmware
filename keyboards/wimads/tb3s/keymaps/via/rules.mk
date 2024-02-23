COMBO_ENABLE = yes
KEY_LOCK_ENABLE = yes
VIA_ENABLE = yes

# MACCEL
MACCEL_VIA_ENABLE = yes
MACCEL_ENABLE = yes
SRC += ./maccel/maccel.c
ifeq ($(strip $(VIA_ENABLE)), yes)
	ifeq ($(strip $(MACCEL_VIA_ENABLE)), yes)
		SRC += ./maccel/maccel_via.c
	endif
endif
OPT_DEFS += -DMACCEL_ENABLE
