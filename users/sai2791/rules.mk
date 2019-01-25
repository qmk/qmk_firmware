ifeq ($(strip $(KEYBOARD)), ymdk_np21)
		SRC +=
endif

ifeq ($(strip $(KEYBOARD)), ergodox_ez)
		SRC += sai2791.c
endif
