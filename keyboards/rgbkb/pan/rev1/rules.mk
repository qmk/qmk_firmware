# RGBKB Pan Defaults

# Keycode Options
BOOTMAGIC_ENABLE 		= no      # Virtual DIP switch configuration. Lite is ~42B, Full is ~1000B
EXTRAKEY_ENABLE         = no       # Audio control and System control

# RGBLIGHT_ENABLE		= yes

# Lighting Options
RGB_MATRIX_ENABLE       = WS2812    # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
#RGB_MATRIX_KEYPRESSES   = yes        # Enable reactive per-key effects.
#RGB_MATRIX_FRAMEBUFFER_EFFECTS = no # Enable frame buffer effects like the typing heatmap.

RGBLIGHT_FULL_POWER     = yes        # Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX. Otherwise, limited to a safe level for a normal USB-A port
IOS_DEVICE_ENABLE       = no        # Limit max brightness to connect to IOS device (iPad,iPhone)

# Misc
OLED_DRIVER_ENABLE      = yes        # Enable the OLED Driver
PROTON_C                = yes

ifeq ($(strip $(PROTON_C)), yes)
    MCU = STM32F303
endif
