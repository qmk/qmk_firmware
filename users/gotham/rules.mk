SRC += gotham.c \
	   process_records.c

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE        = yes
endif
