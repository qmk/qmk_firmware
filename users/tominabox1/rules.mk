# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
CONSOLE_ENABLE = yes
BOOTMAGIC_ENABLE = full      # Virtual DIP switch configuration
NKRO_ENABLE = yes
UCIS_ENABLE = no

ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
RGB_MATRIX_ENABLE = WS2812
EXTRAFLAGS += -flto
BOOTLOADER = qmk-dfu
OLED_DRIVER_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
NKRO_ENABLE = no
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), lazydesigners/dimple)
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), thevankeyboards/minivan)
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), thevankeyboards/roadkit)
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
TAP_DANCE_ENABLE = no
COMBO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), hhkb)
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
SRC += tominabox1.c
BOOTLOADER = halfkay
endif

ifeq ($(strip $(KEYBOARD)), treadstone32)
RGBLIGHT_ENABLE = yes  # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
NKRO_ENABLE = yes

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    # OPT_DEFS += -DRGBLIGHT_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS
endif

SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), handwired/postageboard/mini)
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
NKRO_ENABLE = yes
SRC += tominabox1.c
endif
