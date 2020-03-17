CONSOLE_ENABLE = no
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration
NKRO_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
RGB_MATRIX_ENABLE = WS2812
EXTRAFLAGS += -flto
BOOTLOADER = qmk-dfu
OLED_DRIVER_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes
NKRO_ENABLE = yes
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), lazydesigners/dimple)
EXTRAKEY_ENABLE = yes
RGBLIGHT_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), thevankeyboards/minivan)
EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
RGBLIGHT_ENABLE = yes
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), thevankeyboards/roadkit)
EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = no
COMBO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), hhkb)
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), treadstone32)
RGBLIGHT_ENABLE = yes
LED_ANIMATIONS = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes

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
RGBLIGHT_ENABLE = yes
LED_ANIMATIONS = yes
ifeq ($(strip $(LED_ANIMATIONS)), yes)
    # OPT_DEFS += -DRGBLIGHT_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS
endif
SRC += tominabox1.c
endif

ifeq ($(strip $(KEYBOARD)), handwired/brutal33)
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
NKRO_ENABLE = yes
RGBLIGHT_ENABLE = yes
SRC += tominabox1.c
endif
