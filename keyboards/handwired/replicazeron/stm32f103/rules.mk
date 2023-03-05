# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
TAP_DANCE_ENABLE = no      # Tap Dance

JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
OLED_BRIGHTNESS = 32
LTO_ENABLE = yes

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

##########

QMK_SETTINGS = yes

LEDS_ENABLE = yes
THUMBSTICK_ENABLE = yes

SRC += ../common/state.c
