# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
ENCODER_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# RGB layout selection
RGB_ENCODERS = yes # For RGB encoders, solder on both WS2811 chips
STAGGERED_LAYOUT = no # If you soldered R1-A12 and R4-A12, enable this.

# Default to revision 1
DEFAULT_FOLDER = rgbkb/pan/rev1
