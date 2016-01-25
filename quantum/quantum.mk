QUANTUM_DIR = quantum

# # project specific files
SRC += $(QUANTUM_DIR)/keymap_common.c \
	$(QUANTUM_DIR)/led.c

# ifdef KEYMAP_FILE
# ifneq (,$(shell grep USING_MIDI '$(KEYMAP_FILE)'))
# MIDI_ENABLE=yes
# $(info  * Overriding MIDI_ENABLE setting - $(KEYMAP_FILE) requires it)
# endif
# ifneq (,$(shell grep USING_UNICODE '$(KEYMAP_FILE)'))
# UNICODE_ENABLE=yes
# $(info  * Overriding UNICODE_ENABLE setting - $(KEYMAP_FILE) requires it)
# endif
# ifneq (,$(shell grep USING_BACKLIGHT '$(KEYMAP_FILE)'))
# BACKLIGHT_ENABLE=yes
# $(info  * Overriding BACKLIGHT_ENABLE setting - $(KEYMAP_FILE) requires it)
# endif
# endif

ifndef CUSTOM_MATRIX
	SRC += $(QUANTUM_DIR)/matrix.c
endif

ifdef MIDI_ENABLE
	SRC += $(QUANTUM_DIR)/keymap_midi.c
endif

ifdef AUDIO_ENABLE
	SRC += $(QUANTUM_DIR)/audio.c
endif

ifdef UNICODE_ENABLE
	SRC += $(QUANTUM_DIR)/keymap_unicode.c
endif

ifdef RGBLIGHT_ENABLE
	SRC += $(QUANTUM_DIR)/light_ws2812.c
	SRC += $(QUANTUM_DIR)/rgblight.c
	OPT_DEFS += -DRGBLIGHT_ENABLE
endif

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(TOP_DIR)/$(QUANTUM_DIR)

include $(TMK_DIR)/protocol/lufa.mk

include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk
