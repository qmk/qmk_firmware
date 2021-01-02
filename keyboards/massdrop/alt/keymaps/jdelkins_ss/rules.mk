ifeq ($(OS),Windows_NT)
	MDLOADER = bin/mdloader_windows
else
	MDLOADER = sudo bin/mdloader_linux
endif

doflash: .build/massdrop_alt_jdelkins_ss.hex
	$(MDLOADER) --first --download $< --restart

USER_NAME := jdelkins
