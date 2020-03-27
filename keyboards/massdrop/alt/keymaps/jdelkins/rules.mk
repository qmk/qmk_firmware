ifeq ($(OS),Windows_NT)
	MDLOADER = bin/mdloader_windows
else
	MDLOADER = sudo bin/mdloader_linux
endif

doflash: .build/massdrop_alt_jdelkins.hex
	$(MDLOADER) --first --download $< --restart

LEADER_ENABLE = yes
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
NKRO_ENABLE = no
TAP_DANCE_ENABLE = yes

