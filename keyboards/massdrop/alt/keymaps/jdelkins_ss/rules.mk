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

USER_NAME := jdelkins
