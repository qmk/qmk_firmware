# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
SLEEP_LED_ENABLE = yes      # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
UNICODE_ENABLE = yes        # Unicode
AUDIO_ENABLE = no           # Audio output on port C6
TAP_DANCE_ENABLE = yes      # Let's dance
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = pwm

DEBOUNCE_TYPE = sym_defer_pk

LTO_ENABLE      = yes

#Debug options
VERBOSE = no
