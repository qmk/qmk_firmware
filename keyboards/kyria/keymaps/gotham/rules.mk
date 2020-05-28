CONSOLE_ENABLE = no        # Console for debug
ENCODER_ENABLE = yes       # ENables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
MOUSEKEY_ENABLE = no       # Mouse keys
OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays

THUMBSTICK_ENABLE = yes

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DTHUMBSTICK_ENABLE
endif
