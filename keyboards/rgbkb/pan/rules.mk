# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = bitbang
ENCODER_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# RGB layout selection
RGB_ENCODERS = yes # For RGB encoders, solder on both WS2811 chips
STAGGERED_LAYOUT = no # If you soldered R1-A12 and R4-A12, enable this.

# Default to revision 1
DEFAULT_FOLDER = rgbkb/pan/rev1
