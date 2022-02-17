BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no            # Mouse keys
EXTRAKEY_ENABLE = yes           # Audio control and System control
CONSOLE_ENABLE = no             # Console for debug
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = yes
BACKLIGHT_ENABLE = yes           # Enable keyboard backlight functionality
AUDIO_ENABLE = yes              # Audio output
RGBLIGHT_ENABLE = yes           # Enable RGB underlight
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not WS2812
SLEEP_LED_ENABLE = yes

ISSI_ENABLE = yes			# If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no		# Resets keyboard if matrix_scan isn't run every 250ms




# Override the LFK87 hardware version.
#
# A - Green PCB. at90usb1286 Only 3 exist
# B - We don't talk about RevB
# C-D - Black PCB. at90usb646 First public release
#
# LFK_REV = C

# ifeq ($(LFK_REV), A)
# 	MCU = at90usb1286
# 	OPT_DEFS += -DBOOTLOADER_SIZE=8192
# else
# 	MCU = at90usb646
# 	OPT_DEFS += -DBOOTLOADER_SIZE=4096
# endif
# OPT_DEFS += -DLFK_TKL_REV_$(LFK_REV)
