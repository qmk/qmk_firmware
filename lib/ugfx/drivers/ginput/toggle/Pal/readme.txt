To use this driver:

1. Add in your gfxconf.h:
	a)  #define GFX_USE_GINPUT		GFXON
		#define GINPUT_NEED_TOGGLE	GFXON
	d) If you are not using a known board then create a ginput_lld_toggle_board.h file
		and ensure it is on your include path.
		Use the ginput_lld_toggle_board_example.h file as a basis.
		Currently known boards are:
			Olimex SAM7-EX256

2. To your makefile add the following lines:
	include $(GFXLIB)/drivers/ginput/toggle/Pal/driver.mk
