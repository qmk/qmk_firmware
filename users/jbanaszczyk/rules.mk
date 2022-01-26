CONSOLE_ENABLE = yes
NKRO_ENABLE = yes

BOOTMAGIC_ENABLE = no
MAGIC_ENABLE = no

COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no

AUTO_SHIFT_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
EXTRAKEY_ENABLE	= yes
KEY_OVERRIDE_ENABLE = yes

DO_NOT_SLEEP_ENABLE = yes
AUTO_CAPS_OFF_ENABLE = yes

SRC += jbanaszczyk.c

#----------------------------------------

ifeq ($(strip $(DO_NOT_SLEEP_ENABLE)), yes)
	OPT_DEFS += -DDO_NOT_SLEEP
	SRC += do_not_sleep.c
endif

ifeq ($(strip $(AUTO_CAPS_OFF_ENABLE)), yes)
	OPT_DEFS += -DAUTO_CAPS_OFF
	SRC += auto_caps_off.c
endif
