IOS_DEVICE_ENABLE ?= no              # Limit max brightness to connect to IOS device (iPad,iPhone)
RGBLIGHT_FULL_POWER ?= no            # Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX. Otherwise, limited to a safe level for a normal USB-A port
RGB_MATRIX_KEYPRESSES ?= no          # Enable reactive per-key effects.
RGB_MATRIX_FRAMEBUFFER_EFFECTS ?= no # Enable frame buffer effects like the typing heatmap.
LED_MIRRORED ?= yes                  # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
else ifeq ($(strip $(RGBLIGHT_FULL_POWER)), yes)
    OPT_DEFS += -DRGBLIGHT_FULL_POWER
endif

ifeq ($(strip $(RGB_MATRIX_KEYPRESSES)), yes)
    OPT_DEFS += -DRGB_MATRIX_KEYPRESSES
endif

ifeq ($(strip $(RGB_MATRIX_FRAMEBUFFER)), yes)
    OPT_DEFS += -DRGB_MATRIX_FRAMEBUFFER_EFFECTS
endif

ifeq ($(strip $(LED_MIRRORED)), yes)
    OPT_DEFS += -DLED_MIRRORED
endif
