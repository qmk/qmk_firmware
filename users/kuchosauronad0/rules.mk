SRC += kuchosauronad0.c \
	   process_records.c

LTO_ENABLE = yes
SPACE_CADET_ENABLE            = no

ifneq ($(strip $(RGBLIGHT_ENABLE)),yes )
     SRC += rgblight_user.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
     SRC += tap_dances.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
     SRC += encoder.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
     SRC += combo.c
endif

ifeq ($(strip $(LEADER_ENABLE)), yes)
     SRC += leader.c
endif

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
     SRC += secrets.c
endif
ifeq ($(strip $(NO_SECRETS)), yes)
     OPT_DEFS += -DNO_SECRETS
endif
ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
     SRC += unicode.c
endif

ifeq ($(strip $(MACROS_ENABLED)), yes)
     OPT_DEFS += -DMACROS_ENABLED
endif

ifdef CONSOLE_ENABLE
     ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
         OPT_DEFS += -DKEYLOGGER_ENABLE
     endif
endif

ifeq ($(strip $(MAKE_BOOTLOADER)), yes)
     OPT_DEFS += -DMAKE_BOOTLOADER
endif
