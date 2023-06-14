# RGBKB Sol Rev2 Defaults

# Keycode Options
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE         = no        # Mouse keys
EXTRAKEY_ENABLE         = yes       # Audio control and System control
NKRO_ENABLE = no            # Enable N-Key Rollover

# Debug Options
CONSOLE_ENABLE          = no        # Console for debug
COMMAND_ENABLE          = no        # Commands for debug and configuration

# RGB Options
RGBLIGHT_ENABLE         = no        # Enable global lighting effects. Do not enable with RGB Matrix
LED_MIRRORED            = no        # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)

RGB_MATRIX_ENABLE = yes             # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
RGB_MATRIX_KEYPRESSES   = no        # Enable reactive per-key effects.
RGB_MATRIX_FRAMEBUFFER_EFFECTS = no # Enable frame buffer effects like the typing heatmap.

RGBLIGHT_FULL_POWER     = no        # Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX. Otherwise, limited to a safe level for a normal USB-A port
FULLHAND_ENABLE         = no        # Enables the additional 24 Full Hand LEDs
SF_ENABLE               = no        # Enables the additional 38 Starfighter LEDs
IOS_DEVICE_ENABLE       = no        # Limit max brightness to connect to IOS device (iPad,iPhone)

# Misc
OLED_ENABLE     = no        # Enable the OLED Driver
EXTRA_ENCODERS_ENABLE   = no        # Enables 3 encoders per side (up from 1, not compatible with OLED_ENABLE)
SWAP_HANDS_ENABLE       = no        # Enable one-hand typing
LTO_ENABLE = yes # Enable Link Time Optimizations greatly reducing firmware size by disabling the old Macros and Functions features

# Special RGB Matrix, OLED, & Encoder Control Menu!
RGB_OLED_MENU           = no        # Enabled by setting this to the encoder index (0-5) you wish to use to control the menu.
                                    # Use the RGB_MENU keycode in the keymap for the encoder to advance the menu to the next option.
