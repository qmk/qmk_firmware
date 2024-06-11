DEBUG_MATRIX_SCAN_RATE_ENABLE ?= api
ENCODER_MAP_ENABLE = yes
SWAP_HANDS_ENABLE = no

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
