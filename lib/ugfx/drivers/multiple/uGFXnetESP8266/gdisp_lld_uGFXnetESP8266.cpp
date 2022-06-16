/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

// We need to include stdio.h below. Turn off GFILE_NEED_STDIO just for this file to prevent conflicts
#define GFILE_NEED_STDIO_MUST_BE_OFF

#include "gfx.h"

#if GFX_USE_GDISP

#include <ESP8266WiFi.h>

#define GDISP_DRIVER_VMT			GDISPVMT_uGFXnetESP8266
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"
#include "uGFXnetProtocol.h"

#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH	640
#endif
#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT	480
#endif
#ifndef GDISP_GFXNET_PORT
	#define GDISP_GFXNET_PORT	GNETCODE_DEFAULT_PORT
#endif
#ifndef GDISP_DONT_WAIT_FOR_NET_DISPLAY
	#define GDISP_DONT_WAIT_FOR_NET_DISPLAY	GFXOFF
#endif

static WiFiServer	server(GDISP_GFXNET_PORT);
static GTimer		poller;
static gBool		uGFXInitDone;

#ifndef GDISP_GFXNET_WIFI_INIT_FUNCTION
	#define GDISP_GFXNET_WIFI_INIT_FUNCTION	uGFXnetArduinoWifiInit
	#ifndef GDISP_GFXNET_WIFI_SSID
		#error "uGFXnetArduino: GDISP_GFXNET_WIFI_SSID is not set. You must define the Wifi SSID"
	#endif
	#ifndef GDISP_GFXNET_WIFI_PASSWORD
		#error "uGFXnetArduino: GDISP_GFXNET_WIFI_PASSWORD is not set. You must define the Wifi password"
	#endif
	
	static void uGFXnetArduinoWifiInit(WifiServer *ws) {
		WiFi.begin(GDISP_GFXNET_WIFI_SSID, GDISP_GFXNET_WIFI_PASSWORD);
		while (WiFi.status() != WL_CONNECTED)
			gfxYield();
			
		ws->begin();
	}
#else
	extern "C" void GDISP_GFXNET_WIFI_INIT_FUNCTION(WifiServer *ws);
#endif

#if GINPUT_NEED_MOUSE
	// Include mouse support code
	#define GMOUSE_DRIVER_VMT		GMOUSEVMT_uGFXnet
	#include "../../../src/ginput/ginput_driver_mouse.h"

	// Forward definitions
	static gBool NMouseInit(GMouse *m, unsigned driverinstance);
	static gBool NMouseRead(GMouse *m, GMouseReading *prd);

	const GMouseVMT const GMOUSE_DRIVER_VMT[1] = {{
		{
			GDRIVER_TYPE_MOUSE,
			GMOUSE_VFLG_NOPOLL|GMOUSE_VFLG_DYNAMICONLY,
				// Extra flags for testing only
				//GMOUSE_VFLG_TOUCH|GMOUSE_VFLG_SELFROTATION|GMOUSE_VFLG_DEFAULTFINGER
				//GMOUSE_VFLG_CALIBRATE|GMOUSE_VFLG_CAL_EXTREMES|GMOUSE_VFLG_CAL_TEST|GMOUSE_VFLG_CAL_LOADFREE
				//GMOUSE_VFLG_ONLY_DOWN|GMOUSE_VFLG_POORUPDOWN
			sizeof(GMouse),
			_gmouseInitDriver, _gmousePostInitDriver, _gmouseDeInitDriver
		},
		1,				// z_max
		0,				// z_min
		1,				// z_touchon
		0,				// z_touchoff
		{				// pen_jitter
			0,				// calibrate
			0,				// click
			0				// move
		},
		{				// finger_jitter
			0,				// calibrate
			2,				// click
			2				// move
		},
		NMouseInit,		// init
		0,				// deinit
		NMouseRead,		// get
		0,				// calsave
		0				// calload
	}};
#endif

#if GNETCODE_VERSION != GNETCODE_VERSION_1_0
	#error "GDISP: uGFXnetESP8266 - This driver only support protocol V1.0"
#endif
#if GDISP_LLD_PIXELFORMAT != GNETCODE_PIXELFORMAT
	#error "GDISP: uGFXnetESP8266 - The driver pixel format must match the protocol"
#endif

#define GDISP_FLG_CONNECTED			(GDISP_FLG_DRIVER<<0)
#define GDISP_FLG_HAVEDATA			(GDISP_FLG_DRIVER<<1)

#define CLIENTFD	WifiClient *

/*===========================================================================*/
/* Driver local routines    .                                                */
/*===========================================================================*/

typedef struct netPriv {
	CLIENTFD		netfd;					// The current client
	unsigned		databytes;				// How many bytes have been read
	gU16		data[2];				// Buffer for storing data read.
	#if GINPUT_NEED_MOUSE
		gCoord		mousex, mousey;
		gU16	mousebuttons;
		GMouse *	mouse;
	#endif
} netPriv;

#if GDISP_GFXNET_UNSAFE_SOCKETS
	static gMutex	uGFXnetMutex;
	#define MUTEX_INIT		gfxMutexInit(&uGFXnetMutex)
	#define MUTEX_ENTER		gfxMutexEnter(&uGFXnetMutex)
	#define MUTEX_EXIT		gfxMutexExit(&uGFXnetMutex)
#else
	#define MUTEX_INIT
	#define MUTEX_ENTER
	#define MUTEX_EXIT
#endif

static void endcon(GDisplay *g) {
    netPriv *	priv;

	g->flags &= ~GDISP_FLG_CONNECTED;
	priv = g->priv;
	priv->netfd->stop();
	delete priv->netfd;
	priv->netfd = 0;
}

/**
 * Send a whole packet of data.
 * Len is specified in the number of gU16's we want to send as our protocol only talks gU16's.
 * Note that contents of the packet are modified to ensure it will cross the wire in the correct format.
 * If the connection closes before we send all the data - the call returns gFalse.
 */
static gBool sendpkt(CLIENTFD fd, gU16 *pkt, int len) {
	// Convert each gU16 to network order
	#if GFX_CPU_ENDIAN == GFX_CPU_ENDIAN_LITTLE
		{
			int		i;

			for(i = 0; i < len; i++)
				pkt[i] = ((pkt[i]>>8)|(pkt[i]<<8));
		}
	#endif

	// Send it
	len *= sizeof(gU16);
	return fd->write((gU8 *)pkt, len) == len;
}

static void rxdata(GDisplay *g) {
    netPriv *	priv;
	CLIENTFD	fd;
    int			len;

	if ((g->flags & GDISP_FLG_HAVEDATA)) {
		// The higher level is still processing the previous data.
		//	Give it a chance to run by coming back to this data.
		return;
	}
	
	priv = g->priv;
	fd = priv->netfd;

	MUTEX_ENTER;
	// Are we still connected?
	if (!fd->connected()) {
		MUTEX_EXIT;
		endcon(g);
		return;
	}

	// Is there data available
	if (!fd->available()) {
		MUTEX_EXIT;
		return;
	}
	
	// Get the data
	if ((len = fd->read(((gU8 *)priv->data)+priv->databytes, sizeof(priv->data)-priv->databytes, 0)) <= 0) {
		// Socket closed or in error state
		MUTEX_EXIT;
		endcon(g);
		return;
	}
	MUTEX_EXIT;

	// Do we have a full reply yet
	priv->databytes += len;
	if (priv->databytes < sizeof(priv->data))
		return;
	priv->databytes = 0;

	// Convert network byte or to host byte order
	#if GFX_CPU_ENDIAN == GFX_CPU_ENDIAN_LITTLE
		priv->data[0] = ((priv->data[0]>>8)|(priv->data[0]<<8))
		priv->data[1] = ((priv->data[1]>>8)|(priv->data[1]<<8))
	#endif

	// Process the data received
	switch(priv->data[0]) {
	#if GINPUT_NEED_MOUSE
		case GNETCODE_MOUSE_X:		priv->mousex = priv->data[1];		break;
		case GNETCODE_MOUSE_Y:		priv->mousey = priv->data[1];		break;
		case GNETCODE_MOUSE_B:
			priv->mousebuttons = priv->data[1];
			// Treat the button event as the sync signal
			_gmouseWakeup(priv->mouse);
			break;
	#endif
	case GNETCODE_CONTROL:
	case GNETCODE_READ:
		g->flags |= GDISP_FLG_HAVEDATA;
		break;
	case GNETCODE_KILL:
		gfxHalt("GDISP: uGFXnet - Display sent KILL command");
		break;

	default:
		// Just ignore unrecognised data
		break;
	}
}

void uGFXnetClientPoller(void *param) {
	GDisplay	*g;
	(void)		param;

	// Is there a new server connection?
	if (server.hasClient()) {
	
		// Look for a display that isn't connected
		for(g = 0; (g = (GDisplay *)gdriverGetNext(GDRIVER_TYPE_DISPLAY, (GDriver *)g));) {
			// Ignore displays for other controllers
			#ifdef GDISP_DRIVER_LIST
				if (gvmt(g) != &GDISPVMT_uGFXnet)
					continue;
			#endif
			if (!(g->flags & GDISP_FLG_CONNECTED)) {
			    netPriv *	priv;
			
				// Reset the priv area
				priv = g->priv;
				priv->netfd = new WifiClient(server.available());
				priv->databytes = 0;
				priv->mousebuttons = 0;
			
				// Send the initialisation data (2 words at a time)
				priv->data[0] = GNETCODE_INIT;
				priv->data[1] = GNETCODE_VERSION;
				sendpkt(priv->netfd, priv->data, 2);
				priv->data[0] = GDISP_SCREEN_WIDTH;
				priv->data[1] = GDISP_SCREEN_HEIGHT;
				sendpkt(priv->netfd, priv->data, 2);
				priv->data[0] = GDISP_LLD_PIXELFORMAT;
				priv->data[1] = 1;							// We have a mouse
				MUTEX_ENTER;
				sendpkt(priv->netfd, priv->data, 2);
				MUTEX_EXIT;
			
				// The display is now working
				g->flags |= GDISP_FLG_CONNECTED;
			
				// Send a redraw all
				#if GFX_USE_GWIN && GWIN_NEED_WINDOWMANAGER
					gdispGClear(g, gwinGetDefaultBgColor());
					gwinRedrawDisplay(g, gFalse);
				#endif
				break;
			}
		}
	}
	
	// Look for a display that is connected so we can check if it has data
	for(g = 0; (g = (GDisplay *)gdriverGetNext(GDRIVER_TYPE_DISPLAY, (GDriver *)g));) {
		// Ignore displays for other controllers
		#ifdef GDISP_DRIVER_LIST
			if (gvmt(g) != &GDISPVMT_uGFXnet)
				continue;
		#endif
		if ((g->flags & GDISP_FLG_CONNECTED))
			rxdata(g);
	}
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	netPriv	*	priv;

	// Initialise the receiver thread (if it hasn't been done already)
	if (!uGFXInitDone) {
		MUTEX_INIT;
		// Init and Start the poller
		GDISP_GFXNET_WIFI_INIT_FUNCTION(&server);

		// Initialise the poller
		gtimerInit(&poller);
		gtimerStart(&poller, uGFXnetClientPoller, 0, gTrue, 50);
		uGFXInitDone = gTrue;
	}

	// Create a private area for this window
	if (!(priv = gfxAlloc(sizeof(netPriv))))
		gfxHalt("GDISP: uGFXnetESP8266 - Memory allocation failed");
	memset(priv, 0, sizeof(netPriv));
	g->priv = priv;
	g->board = 0;			// no board interface for this controller

	// Create the associated mouse
	#if GINPUT_NEED_MOUSE
		priv->mouse = (GMouse *)gdriverRegister((const GDriverVMT const *)GMOUSE_DRIVER_VMT, g);
	#endif

	// Initialise the GDISP structure
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = 100;
	g->g.Contrast = 50;
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;

	return gTrue;
}

#if GDISP_HARDWARE_FLUSH
	LLDSPEC void gdisp_lld_flush(GDisplay *g) {
		netPriv	*	priv;
		gU16	buf[1];

		#if GDISP_DONT_WAIT_FOR_NET_DISPLAY
			if (!(g->flags & GDISP_FLG_CONNECTED))
				return;
		#else
			while(!(g->flags & GDISP_FLG_CONNECTED))
				gfxSleepMilliseconds(200);
		#endif

		priv = g->priv;
		buf[0] = GNETCODE_FLUSH;
		MUTEX_ENTER;
		sendpkt(priv->netfd, buf, 1);
		MUTEX_EXIT;
	}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
		netPriv	*	priv;
		gU16	buf[4];

		#if GDISP_DONT_WAIT_FOR_NET_DISPLAY
			if (!(g->flags & GDISP_FLG_CONNECTED))
				return;
		#else
			while(!(g->flags & GDISP_FLG_CONNECTED))
				gfxSleepMilliseconds(200);
		#endif

		priv = g->priv;
		buf[0] = GNETCODE_PIXEL;
		buf[1] = g->p.x;
		buf[2] = g->p.y;
		buf[3] = gdispColor2Native(g->p.color);
		MUTEX_ENTER;
		sendpkt(priv->netfd, buf, 4);
		MUTEX_EXIT;
	}
#endif

/* ---- Optional Routines ---- */

#if GDISP_HARDWARE_FILLS
	LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
		netPriv	*	priv;
		gU16	buf[6];

		#if GDISP_DONT_WAIT_FOR_NET_DISPLAY
			if (!(g->flags & GDISP_FLG_CONNECTED))
				return;
		#else
			while(!(g->flags & GDISP_FLG_CONNECTED))
				gfxSleepMilliseconds(200);
		#endif

		priv = g->priv;
		buf[0] = GNETCODE_FILL;
		buf[1] = g->p.x;
		buf[2] = g->p.y;
		buf[3] = g->p.cx;
		buf[4] = g->p.cy;
		buf[5] = gdispColor2Native(g->p.color);
		MUTEX_ENTER;
		sendpkt(priv->netfd, buf, 6);
		MUTEX_EXIT;
	}
#endif

#if GDISP_HARDWARE_BITFILLS
	LLDSPEC void gdisp_lld_blit_area(GDisplay *g) {
		netPriv	*	priv;
		gPixel	*	buffer;
		gU16	buf[5];
		gCoord		x, y;

		#if GDISP_DONT_WAIT_FOR_NET_DISPLAY
			if (!(g->flags & GDISP_FLG_CONNECTED))
				return;
		#else
			while(!(g->flags & GDISP_FLG_CONNECTED))
				gfxSleepMilliseconds(200);
		#endif

		// Make everything relative to the start of the line
		buffer = g->p.ptr;
		buffer += g->p.x2*g->p.y1;

		priv = g->priv;
		buf[0] = GNETCODE_BLIT;
		buf[1] = g->p.x;
		buf[2] = g->p.y;
		buf[3] = g->p.cx;
		buf[4] = g->p.cy;
		MUTEX_ENTER;
		sendpkt(priv->netfd, buf, 5);

		for(y = 0; y < g->p.cy; y++, buffer += g->p.x2 - g->p.cx) {
			for(x = 0; x < g->p.cx; x++, buffer++) {
				buf[0] = gdispColor2Native(buffer[0]);
				sendpkt(priv->netfd, buf, 1);
			}
		}
		MUTEX_EXIT;
	}
#endif

#if GDISP_HARDWARE_PIXELREAD
	LLDSPEC	gColor gdisp_lld_get_pixel_color(GDisplay *g) {
		netPriv	*	priv;
		gU16	buf[3];
		gColor		data;

		#if GDISP_DONT_WAIT_FOR_NET_DISPLAY
			if (!(g->flags & GDISP_FLG_CONNECTED))
				return 0;
		#else
			while(!(g->flags & GDISP_FLG_CONNECTED))
				gfxSleepMilliseconds(200);
		#endif

		priv = g->priv;
		buf[0] = GNETCODE_READ;
		buf[1] = g->p.x;
		buf[2] = g->p.y;
		MUTEX_ENTER;
		sendpkt(priv->netfd, buf, 3);
		MUTEX_EXIT;

		// Now wait for a reply
		while(!(g->flags & GDISP_FLG_HAVEDATA) || priv->data[0] != GNETCODE_READ)
			gfxSleepMilliseconds(1);

		data = gdispNative2Color(priv->data[1]);
		g->flags &= ~GDISP_FLG_HAVEDATA;

		return data;
	}
#endif

#if GDISP_NEED_SCROLL && GDISP_HARDWARE_SCROLL
	LLDSPEC void gdisp_lld_vertical_scroll(GDisplay *g) {
		netPriv	*	priv;
		gU16	buf[6];

		#if GDISP_DONT_WAIT_FOR_NET_DISPLAY
			if (!(g->flags & GDISP_FLG_CONNECTED))
				return;
		#else
			while(!(g->flags & GDISP_FLG_CONNECTED))
				gfxSleepMilliseconds(200);
		#endif

		priv = g->priv;
		buf[0] = GNETCODE_SCROLL;
		buf[1] = g->p.x;
		buf[2] = g->p.y;
		buf[3] = g->p.cx;
		buf[4] = g->p.cy;
		buf[5] = g->p.y1;
		MUTEX_ENTER;
		sendpkt(priv->netfd, buf, 6);
		MUTEX_EXIT;
	}
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
		netPriv	*	priv;
		gU16	buf[3];
		gBool		allgood;

		#if GDISP_DONT_WAIT_FOR_NET_DISPLAY
			if (!(g->flags & GDISP_FLG_CONNECTED))
				return;
		#else
			while(!(g->flags & GDISP_FLG_CONNECTED))
				gfxSleepMilliseconds(200);
		#endif

		// Check if we might support the code
		switch(g->p.x) {
		case GDISP_CONTROL_ORIENTATION:
			if (g->g.Orientation == (gOrientation)g->p.ptr)
				return;
			break;
		case GDISP_CONTROL_POWER:
			if (g->g.Powermode == (gPowermode)g->p.ptr)
				return;
			break;
		case GDISP_CONTROL_BACKLIGHT:
			if (g->g.Backlight == (gU16)(int)g->p.ptr)
				return;
			if ((gU16)(int)g->p.ptr > 100)
				g->p.ptr = (void *)100;
			break;
		default:
			return;
		}

		// Send the command
		priv = g->priv;
		buf[0] = GNETCODE_CONTROL;
		buf[1] = g->p.x;
		buf[2] = (gU16)(int)g->p.ptr;
		MUTEX_ENTER;
		sendpkt(priv->netfd, buf, 3);
		MUTEX_EXIT;

		// Now wait for a reply
		while(!(g->flags & GDISP_FLG_HAVEDATA) || priv->data[0] != GNETCODE_CONTROL)
			gfxSleepMilliseconds(1);

		// Extract the return status
		allgood = priv->data[1] ? gTrue : gFalse;
		g->flags &= ~GDISP_FLG_HAVEDATA;

		// Do nothing more if the operation failed
		if (!allgood) return;

		// Update the local stuff
		switch(g->p.x) {
		case GDISP_CONTROL_ORIENTATION:
			switch((gOrientation)g->p.ptr) {
				case gOrientation0:
				case gOrientation180:
					g->g.Width = GDISP_SCREEN_WIDTH;
					g->g.Height = GDISP_SCREEN_HEIGHT;
					break;
				case gOrientation90:
				case gOrientation270:
					g->g.Height = GDISP_SCREEN_WIDTH;
					g->g.Width = GDISP_SCREEN_HEIGHT;
					break;
				default:
					return;
			}
			g->g.Orientation = (gOrientation)g->p.ptr;
			break;
		case GDISP_CONTROL_POWER:
			g->g.Powermode = (gPowermode)g->p.ptr;
			break;
		case GDISP_CONTROL_BACKLIGHT:
			g->g.Backlight = (gU16)(int)g->p.ptr;
			break;
		}
	}
#endif

#if GINPUT_NEED_MOUSE
	static gBool NMouseInit(GMouse *m, unsigned driverinstance) {
		(void)	m;
		(void)	driverinstance;
		return gTrue;
	}
	static gBool NMouseRead(GMouse *m, GMouseReading *pt) {
		GDisplay *	g;
		netPriv	*	priv;

		g = m->display;
		priv = g->priv;

		pt->x = priv->mousex;
		pt->y = priv->mousey;
		pt->z = (priv->mousebuttons & GINPUT_MOUSE_BTN_LEFT) ? 1 : 0;
		pt->buttons = priv->mousebuttons;
		return gTrue;
	}
#endif /* GINPUT_NEED_MOUSE */

#endif /* GFX_USE_GDISP */
