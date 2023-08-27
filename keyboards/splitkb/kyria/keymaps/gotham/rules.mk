CONSOLE_ENABLE     = yes  # Console for debug
ENCODER_ENABLE     = yes  # ENables the use of one or more encoders
RGBLIGHT_ENABLE    = yes  # Enable keyboard RGB underglow
MOUSEKEY_ENABLE    = no   # Mouse keys
OLED_ENABLE = yes
THUMBSTICK_ENABLE  = yes  # Enables analog thumbstick code

ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += encoder_utils.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled_utils.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    POINTING_DEVICE_DRIVER = custom
    OPT_DEFS += -DTHUMBSTICK_ENABLE
	SRC += analog.c
	SRC += thumbstick.c
endif
