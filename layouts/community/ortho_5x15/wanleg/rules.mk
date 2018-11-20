ifeq (,$(findstring yes,$(BLUEFRUIT)))
  BLUETOOTH = AdafruitBLE
  BLUETOOTH_ENABLE = yes
  F_CPU = 8000000
  CONSOLE_ENABLE = no 		# Console for debug(+400)
  COMMAND_ENABLE = no 		# Commands for debug and configuration
  RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
endif

ifneq (,$(findstring xd75,$(KEYBOARD)))
#something
endif

ifeq (,$(findstring 40percentclub/5x5,$(KEYBOARD)))
#something
endif