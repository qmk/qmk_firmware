SRC += jjerrell.c \
       process_records.c

LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE        = yes
endif
SPACE_CADET_ENABLE    = no
GRAVE_ESC_ENABLE      = no

ifneq ($(strip $(NO_SECRETS)), yes)
    ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
        SRC += secrets.c
    endif
    ifeq ($(strip $(NO_SECRETS)), lite)
        OPT_DEFS += -DNO_SECRETS
    endif
endif

# TODO: RGB is next
# RGB_MATRIX_ENABLE ?= no
# ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
#     SRC += rgb_matrix_stuff.c
# endif
