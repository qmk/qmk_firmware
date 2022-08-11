ifeq ($(OS),Windows_NT)
	PROGRAM_CMD = bin/mdloader_windows --first --download $(TARGET).hex --restart
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		PROGRAM_CMD = bin/mdloader_mac --first --download $(TARGET).hex --restart
	else
		PROGRAM_CMD = sudo bin/mdloader_linux --first --download $(TARGET).hex --restart
	endif
endif

LEADER_ENABLE = yes
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
NKRO_ENABLE = no
TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = no
