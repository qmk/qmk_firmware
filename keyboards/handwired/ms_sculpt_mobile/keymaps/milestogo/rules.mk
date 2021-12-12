# only things overriding defaults
#
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover 

ifeq ($(strip $(KEYBOARD)), handwired/ms_sculpt_mobile/8x18_arm)
	RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. 
endif

#enable RAW in keymap config, since it can hang machines
RAW_ENABLE = no
# virtual serial port
VIRTSER_ENABLE = no

USER_NAME := miles2go
