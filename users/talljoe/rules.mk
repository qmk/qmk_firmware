SRC += talljoe.c

ifneq ("$(wildcard users/$(KEYMAP)/config.h)","")
    CONFIG_H += users/$(KEYMAP)/config.h
endif
