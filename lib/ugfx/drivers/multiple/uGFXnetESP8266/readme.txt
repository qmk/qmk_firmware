To use this driver:

This driver is special in that it implements both the gdisp low level driver
and a touchscreen driver.

1. Add in your gfxconf.h:
	a) #define GFX_USE_GDISP		GFXON
	b) Optionally #define GFX_USE_GINPUT			GFXON
					#define GINPUT_USE_MOUSE		GFXON
	c) Any optional high level driver defines (see gdisp.h) eg: GDISP_NEED_MULTITHREAD
	d) Optionally the following (with appropriate values):
		#define GDISP_SCREEN_WIDTH					640			// Virtual display width
		#define GDISP_SCREEN_HEIGHT					480			// Virtual display height
		#define GDISP_GFXNET_WIFI_INIT_FUNCTION		MyWifiStart	// Optionally specify if you want to
																//  use your own wifi startup routine.
																// Prototype...
																//    extern "C" void MyWifiStart(WifiServer *ws);
		#define GDISP_GFXNET_WIFI_SSID				"ssid"		// Your wifi SSID.
																//  Not required if GDISP_GFXNET_WIFI_INIT_FUNCTION
																//  is specified.
		#define GDISP_GFXNET_WIFI_PASSWORD			"password"	// Your wifi password.
																//  Not required if GDISP_GFXNET_WIFI_INIT_FUNCTION
																//  is specified.
		#define GDISP_DONT_WAIT_FOR_NET_DISPLAY		GFXOFF		// Don't halt waiting for the first connection
		$define GDISP_GFXNET_PORT					13001		// The TCP port the display sits on


2. To your makefile (or Library) add the following lines:
	include $(GFXLIB)/gfx.mk
	include $(GFXLIB)/drivers/multiple/uGFXnetESP8266/driver.mk
