TAP_DANCE_ENABLE  = yes
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
COMMAND_ENABLE    = yes  # Commands for debug and configuration
ifneq (,$(findstring ergodox_ez,$(KEYBOARD)))
  RGBLIGHT_ENABLE = yes
  RGB_MATRIX_ENABLE = no
endif
CONSOLE_ENABLE    = no
BOOTMAGIC_ENABLE  = yes

UNICODE_ENABLE    = yes
UNICDOEMAP_ENABLE = no

MACROS_ENABLED    = no
RGBLIGHT_TWINKLE  = no
INDICATOR_LIGHTS  = no
