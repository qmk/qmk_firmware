# RGBKB Sol Rev1 Defaults

# Keycode Options
BOOTMAGIC_ENABLE        = no        # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE         = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE         = yes       # Audio control and System control(+450)
UNICODE_ENABLE          = no        # Unicode keycodes
NKRO_ENABLE             = no        # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

# Debug Options
CONSOLE_ENABLE          = no        # Console for debug(+400)
COMMAND_ENABLE          = no        # Commands for debug and configuration

# RGB Options
RGBLIGHT_ENABLE         = yes       # Enable global lighting effects. Do not enable with RGB Matrix
RGBLIGHT_ANIMATIONS     = yes       # LED animations
LED_MIRRORED            = yes       # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)

RGB_MATRIX_ENABLE       = no        # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
RGB_MATRIX_KEYPRESSES   = no        # Enable reactive per-key effects.
RGB_MATRIX_FRAMEBUFFER_EFFECTS = no # Enable frame buffer effects like the typing heatmap.

RGBLIGHT_FULL_POWER     = no        # Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX. Otherwise, limited to a safe level for a normal USB-A port
IOS_DEVICE_ENABLE       = no        # Limit max brightness to connect to IOS device (iPad,iPhone)

# Misc
OLED_DRIVER_ENABLE      = no        # Enable the OLED Driver
SWAP_HANDS_ENABLE       = no        # Enable one-hand typing
