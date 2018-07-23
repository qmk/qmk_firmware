TAP_DANCE_ENABLE  = yes
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
COMMAND_ENABLE    = yes  # Commands for debug and configuration
<<<<<<< HEAD
RGBLIGHT_ENABLE   = yes
CONSOLE_ENABLE    = no
BOOTMAGIC_ENABLE  = yes

=======
ifeq ("$(KEYBOARD)","ergodox_ez")
  RGBLIGHT_ENABLE = yes
  RGB_MATRIX_ENABLE = no
endif
CONSOLE_ENABLE    = no
BOOTMAGIC_ENABLE  = yes

UNICODE_ENABLE    = no
UNICDOEMAP_ENABLE = yes

MACROS_ENABLED    = no
INDICATOR_LIGHTS  = no
ifdef RGBLIGHT_ENABLE
  RGBLIGHT_TWINKLE  = yes
endif
>>>>>>> 1225120b92411f4fa1a9dc79af2fd85bd5aa6dcc
