AUDIO_ENABLE = no
SWAP_HANDS_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), jj40)
	SWAP_HANDS_ENABLE = no
endif

ifeq ($(strip $(KEYBOARD)), 4x4)
	SWAP_HANDS_ENABLE = no
	
#use alternate settings for 4x4 board using ProMicro instead of Micro
#usage: make 4x4:wanleg PM=yes
ifeq ($(strip $(PM)), yes)
	LAYOUTS = ortho_4x4  ortho_4x8  ortho_4x12
	PRO_MICRO = yes
endif	
endif