TAP_DANCE_ENABLE  = yes
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
COMMAND_ENABLE    = yes  # Commands for debug and configuration
ifeq ($(strip $(KEYBOARD)), ergodox_ez)
  RGBLIGHT_ENABLE   = yes
endif
CONSOLE_ENABLE    = no
BOOTMAGIC_ENABLE  = yes

UNICODE_ENABLE    = no
UNICDOEMAP_ENABLE = yes
