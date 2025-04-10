IOS_DEVICE_ENABLE ?= no              # Limit max brightness to connect to IOS device (iPad,iPhone)
RGBLIGHT_FULL_POWER ?= no            # Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX. Otherwise, limited to a safe level for a normal USB-A port
RGB_MATRIX_KEYPRESSES ?= no          # Enable reactive per-key effects.
RGB_MATRIX_FRAMEBUFFER_EFFECTS ?= no # Enable frame buffer effects like the typing heatmap.
LED_MIRRORED ?= no                   # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
FULLHAND_ENABLE ?= no                # Enables the additional 24 Full Hand LEDs
SF_ENABLE ?= no                      # Enables the additional 38 Starfighter LEDs

EXTRA_ENCODERS_ENABLE ?= no          # Enables 3 encoders per side (up from 1, not compatible with OLED_ENABLE)

# Special RGB Matrix, OLED, & Encoder Control Menu!
RGB_OLED_MENU ?= no                  # Enabled by setting this to the encoder index (0-5) you wish to use to control the menu.
                                     # Use the RGB_MENU keycode in the keymap for the encoder to advance the menu to the next option.


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

ifeq ($(strip $(FULLHAND_ENABLE)), yes)
    OPT_DEFS += -DFULLHAND_ENABLE
else ifeq ($(strip $(SF_ENABLE)), yes)
    OPT_DEFS += -DSF_ENABLE
endif

ifeq ($(strip $(EXTRA_ENCODERS_ENABLE)), yes)
    OPT_DEFS += -DEXTRA_ENCODERS_ENABLE
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    ifeq ($(strip $(ENCODER_ENABLE)), yes)
        ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
            ifneq ($(strip $(RGB_OLED_MENU)), no)
                OPT_DEFS += -DRGB_OLED_MENU=$(strip $(RGB_OLED_MENU))
            endif
        endif
    endif
endif
