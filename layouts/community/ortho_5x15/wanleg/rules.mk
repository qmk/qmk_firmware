ifeq ($(strip $(KEYBOARD)), xd75)
#or
#ifeq (,$(findstring xd75,$(KEYBOARD)))
SWAP_HANDS_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), 40percentclub/5x5)
#or
#ifeq (,$(findstring 40percentclub/5x5,$(KEYBOARD)))
SWAP_HANDS_ENABLE = yes
endif