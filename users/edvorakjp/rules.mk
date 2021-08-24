SRC += edvorakjp.c \
       edvorakjp_process_record.c \
       edvorakjp_status.c

ifeq ($(TAP_DANCE_ENABLE), yes)
SRC += edvorakjp_tap_dance.c
endif
