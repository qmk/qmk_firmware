RGB_MATRIX_KEYPRESSES ?= no          # Enable reactive per-key effects.
RGB_MATRIX_FRAMEBUFFER_EFFECTS ?= no # Enable frame buffer effects like the typing heatmap.

# RGB layout selection
STAGGERED_LAYOUT ?= no # If you soldered R1-A12 and R4-A12, enable this.
RGB_ENCODERS ?= yes    # For RGB encoders, solder on both WS2811 chips

ifeq ($(strip $(RGB_MATRIX_KEYPRESSES)), yes)
    OPT_DEFS += -DRGB_MATRIX_KEYPRESSES
endif

ifeq ($(strip $(RGB_MATRIX_FRAMEBUFFER)), yes)
    OPT_DEFS += -DRGB_MATRIX_FRAMEBUFFER_EFFECTS
endif

ifeq ($(strip $(STAGGERED_LAYOUT)), yes)
    OPT_DEFS += -DSTAGGERED_LAYOUT
endif

ifeq ($(strip $(RGB_ENCODERS)), yes)
    OPT_DEFS += -DRGB_ENCODERS
endif

ifeq ($(strip $(RGB_ENCODERS)), yes)
    ifeq ($(strip $(STAGGERED_LAYOUT)), yes)
        OPT_DEFS += -DSTAGGERED_RGB_ENCODERS=$(strip $(STAGGERED_RGB_ENCODERS))
    endif
endif
