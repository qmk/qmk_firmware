QUANTUM_DIR = quantum

# # project specific files
SRC += $(QUANTUM_DIR)/keymap_common.c \
	$(QUANTUM_DIR)/led.c 

ifdef KEYMAP
ifneq (,$(shell grep USING_MIDI 'keymaps/keymap_$(KEYMAP).c'))
MIDI_ENABLE=yes
$(info  * Overriding MIDI_ENABLE setting - keymap_$(KEYMAP).c requires it)
endif
ifneq (,$(shell grep USING_UNICODE 'keymaps/keymap_$(KEYMAP).c'))
UNICODE_ENABLE=yes
$(info  * Overriding UNICODE_ENABLE setting - keymap_$(KEYMAP).c requires it)
endif
ifneq (,$(shell grep USING_BACKLIGHT 'keymaps/keymap_$(KEYMAP).c'))
BACKLIGHT_ENABLE=yes
$(info  * Overriding BACKLIGHT_ENABLE setting - keymap_$(KEYMAP).c requires it)
endif
endif

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

