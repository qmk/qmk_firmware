ifeq ($(findstring massdrop,$(KEYBOARD)), massdrop)
	# Disable LTO for Massdrop boards, breaks with it enabled.
	DISABLE_LTO = yes
endif
