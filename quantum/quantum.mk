QUANTUM_DIR = quantum

# # project specific files
SRC += $(QUANTUM_DIR)/keymap_common.c \
	$(QUANTUM_DIR)/led.c 

ifndef CUSTOM_MATRIX
	SRC += $(QUANTUM_DIR)/matrix.c
endif

ifdef MIDI_ENABLE
	SRC += $(QUANTUM_DIR)/keymap_midi.c \
		   $(QUANTUM_DIR)/beeps.c
endif

ifdef UNICODE_ENABLE
	SRC += $(QUANTUM_DIR)/keymap_unicode.c
endif

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(TOP_DIR)/$(QUANTUM_DIR)

include $(TMK_DIR)/protocol/lufa.mk

include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk

