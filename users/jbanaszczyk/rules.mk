CONSOLE_ENABLE = yes

EXTRAKEY_ENABLE	= no
MOUSEKEY_ENABLE = no
BOOTMAGIC_ENABLE = no
NKRO_ENABLE = yes

DYNAMIC_MACRO_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

DO_NOT_SLEEP_ENABLE = yes

SRC += jbanaszczyk.c \
       do_not_sleep.c

#----------------------------------------

ifeq ($(strip $(DO_NOT_SLEEP_ENABLE)), yes)
    OPT_DEFS += -DDO_NOT_SLEEP
endif
