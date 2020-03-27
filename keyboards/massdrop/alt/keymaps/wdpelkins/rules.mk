ifeq ($(OS),Windows_NT)
	MDLOADER = bin/mdloader_windows
else
	MDLOADER = sudo bin/mdloader_linux
endif

doflash: .build/massdrop_alt_wdpelkins.hex
	$(MDLOADER) --first --download $< --restart

