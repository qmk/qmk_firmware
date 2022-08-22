OLED_DRIVER = SSD1306

VIA_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE  = yes
WPM_ENABLE = yes

#Config to choose screen animation.  Only choose one.
OCEAN_DREAM_ENABLE = yes
LUNA_ENABLE = no

#Ocean Dream and Luna Code to handle above toggles
ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled_setup.c

	ifdef OCEAN_DREAM_ENABLE
		ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
			SRC += ocean_dream.c
			OPT_DEFS += -DOCEAN_DREAM_ENABLE
    	endif
	endif
	ifndef OCEAN_DREAM_ENABLE
		SRC += ocean_dream.c
		OPT_DEFS += -DOCEAN_DREAM_ENABLE
	endif

	ifdef LUNA_ENABLE
		ifeq ($(strip $(LUNA_ENABLE)), yes)
			SRC += luna.c
			OPT_DEFS += -DLUNA_ENABLE
		endif
	endif
	ifndef LUNA_ENABLE
		SRC += luna.c
		OPT_DEFS += -DLUNA_ENABLE
	endif
endif
