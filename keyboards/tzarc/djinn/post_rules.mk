ifeq ($(DJINN_DEFAULT_THEME),yes)
	OPT_DEFS += -DDJINN_DEFAULT_THEME
	VPATH += keyboards/tzarc/djinn/graphics
	SRC += \
		theme_djinn_default.c \
		djinn.qgf.c \
		lock-caps-ON.qgf.c \
		lock-scrl-ON.qgf.c \
		lock-num-ON.qgf.c \
		lock-caps-OFF.qgf.c \
		lock-scrl-OFF.qgf.c \
		lock-num-OFF.qgf.c \
		thintel15.qff.c
endif