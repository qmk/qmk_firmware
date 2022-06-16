/*
 * Created by Oleg Gerasimov <ogerasimov@gmail.com>
 * 06.08.2016
 */

// We need to include stdio.h below. Turn off GFILE_NEED_STDIO just for this file to prevent conflicts
#define GFILE_NEED_STDIO_MUST_BE_OFF

#include "gfx.h"

#if GFX_USE_GDISP

#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <SDL.h>

#define GDISP_DRIVER_VMT				GDISPVMT_SDL
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#ifndef GDISP_FORCE_24BIT
	#define GDISP_FORCE_24BIT			GFXOFF
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH			640
#endif
#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT			480
#endif

#if GINPUT_NEED_MOUSE
	// Include mouse support code
	#define GMOUSE_DRIVER_VMT		GMOUSEVMT_SDL
	#include "../../../src/ginput/ginput_driver_mouse.h"

	// Forward definitions
	static gBool SDL_MouseInit(GMouse *m, unsigned driverinstance);
	static gBool SDL_MouseRead(GMouse *m, GMouseReading *prd);
	const GMouseVMT GMOUSE_DRIVER_VMT[1] = {{
		{
			GDRIVER_TYPE_MOUSE,
			GMOUSE_VFLG_NOPOLL|GMOUSE_VFLG_DYNAMICONLY,
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
		SDL_MouseInit,		// init
		0,				// deinit
		SDL_MouseRead,		// get
		0,				// calsave
		0				// calload
	}};
	static GMouse   *mouse = 0;
#endif

#if GINPUT_NEED_KEYBOARD
	// Include mouse support code
	#define GKEYBOARD_DRIVER_VMT		GKEYBOARDVMT_SDL
	#include "../../../src/ginput/ginput_driver_keyboard.h"

	// Forward definitions
	static gBool SDL_KeyboardInit(GKeyboard *k, unsigned driverinstance);
	static int SDL_KeyboardGetData(GKeyboard *k, gU8 *pch, int sz);

	const GKeyboardVMT GKEYBOARD_DRIVER_VMT[1] = {{
		{
			GDRIVER_TYPE_KEYBOARD,
			GKEYBOARD_VFLG_NOPOLL,			//  GKEYBOARD_VFLG_DYNAMICONLY
			sizeof(GKeyboard),
			_gkeyboardInitDriver, _gkeyboardPostInitDriver, _gkeyboardDeInitDriver
		},
		0,
		SDL_KeyboardInit,			// init
		0,						// deinit
		SDL_KeyboardGetData,		// getdata
		0						// putdata		void	(*putdata)(GKeyboard *k, char ch);		Optional
	}};

	static struct KeyMap {
		SDL_Keycode k_sdl;
		gU16 k_ugfx;
	} SDL_keymap[] =
	{
		{SDLK_UP,				GKEY_UP},
		{SDLK_DOWN,				GKEY_DOWN},
		{SDLK_RIGHT,			GKEY_RIGHT},
		{SDLK_LEFT,				GKEY_LEFT},
		{SDLK_END,				GKEY_END},
		{SDLK_HOME,				GKEY_HOME},
		{SDLK_PAGEDOWN,			GKEY_PAGEDOWN},
		{SDLK_PAGEUP,			GKEY_PAGEUP},
		{SDLK_F1,				GKEY_FN1},
		{SDLK_F2,				GKEY_FN2},
		{SDLK_F3,				GKEY_FN3},
		{SDLK_F4,				GKEY_FN4},
		{SDLK_F5,				GKEY_FN5},
		{SDLK_F6,				GKEY_FN6},
		{SDLK_F7,				GKEY_FN7},
		{SDLK_F8,				GKEY_FN8},
		{SDLK_F9,				GKEY_FN9},
		{SDLK_F10,				GKEY_FN10},
		{SDLK_F11,				GKEY_FN11},
		{SDLK_F12,				GKEY_FN12},
		{SDLK_F13,				GKEY_FN13},
		{SDLK_F14,				GKEY_FN14},
		{SDLK_F15,				GKEY_FN15},
		{SDLK_BRIGHTNESSDOWN,	GKEY_LIGHTDOWN},
		{SDLK_BRIGHTNESSUP,	GKEY_LIGHTUP},
		{SDLK_AUDIONEXT,		GKEY_MEDIANEXT},
		{SDLK_AUDIOPREV,		GKEY_MEDIAPREV},
		{SDLK_AUDIOPLAY,		GKEY_MEDIAPLAY},
		{SDLK_AUDIOSTOP,		GKEY_MEDIASTOP},
		{SDLK_VOLUMEUP,			GKEY_VOLUP},
		{SDLK_VOLUMEDOWN,		GKEY_VOLDOWN},
		{SDLK_MUTE,				GKEY_VOLMUTE},
		{0,0}
	};
	static struct ModMap {
		SDL_Keycode s_sdl;
		gU32 s_ugfx;
	} SDL_modmap[] = {
		{KMOD_LSHIFT,	GKEYSTATE_SHIFT_L},
		{KMOD_RSHIFT,	GKEYSTATE_SHIFT_R},
		{KMOD_RCTRL,	GKEYSTATE_CTRL_R},
		{KMOD_LCTRL,		GKEYSTATE_CTRL_L},
		{KMOD_RALT,		GKEYSTATE_ALT_R},
		{KMOD_LALT,		GKEYSTATE_ALT_L},
		{KMOD_CAPS,		GKEYSTATE_CAPSLOCK},
		{KMOD_NUM,		GKEYSTATE_NUMLOCK},
		{0,0}
	};
	struct SDL_keymsg {
		gU32 key;
		gU32 keystate;
	};
	static GKeyboard *keyboard = 0;
#endif

// shared IPC context
struct SDL_UGFXContext {
	gU32 	framebuf[GDISP_SCREEN_WIDTH*GDISP_SCREEN_HEIGHT];
	gI16		need_redraw;
	int		minx,miny,maxx,maxy;
#if GINPUT_NEED_MOUSE
	gCoord 	mousex, mousey;
	gU16 	buttons;
#endif
#if GINPUT_NEED_KEYBOARD
	gU16 	keypos;
	struct 		SDL_keymsg keybuffer[8];
#endif
};
 
static struct SDL_UGFXContext *context;
static sem_t *ctx_mutex;
static sem_t *input_event;

#define CTX_MUTEX_NAME 		"ugfx_ctx_mutex"
#define INPUT_EVENT_NAME 	"ugfx_input_event"


static int SDL_loop (void) {
	SDL_Window   *window = SDL_CreateWindow("uGFX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT, 0);
	SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture  *texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, GDISP_SCREEN_WIDTH, GDISP_SCREEN_HEIGHT);
	int done = 0;

	while  (!done) {
		
		if (context->need_redraw) {
			context->need_redraw = 0;
			SDL_Rect r;
			r.x = context->minx;
			r.y = context->miny;
			r.w = context->maxx - context->minx + 1;
			r.h = context->maxy - context->miny + 1;
			context->minx = GDISP_SCREEN_WIDTH;
			context->miny = GDISP_SCREEN_HEIGHT;
			context->maxx = 0;
			context->maxy = 0;
			
			SDL_UpdateTexture(texture, &r, context->framebuf+r.y*GDISP_SCREEN_WIDTH+r.x, GDISP_SCREEN_WIDTH*sizeof(gU32));
			SDL_RenderCopy(render, texture, 0, 0);
			SDL_RenderPresent(render);
		}
		SDL_Event event;
		for (; SDL_PollEvent(&event); ){
			switch(event.type){
#if GINPUT_NEED_MOUSE
#if 0
			// On osx event contains coordinates of touchpad. We can't use them, we screen coordinates. 
			case SDL_FINGERMOTION: 
			case SDL_FINGERDOWN:
			case SDL_FINGERUP:
				context->mousex = (event.tfinger.x<1.0)?event.tfinger.x*GDISP_SCREEN_WIDTH:event.tfinger.x;
				context->mousey = (event.tfinger.y<1.0)?event.tfinger.y*GDISP_SCREEN_HEIGHT:event.tfinger.y;
				context->buttons = (event.type != SDL_FINGERUP)?GINPUT_MOUSE_BTN_LEFT:0;
				sem_post (input_event);
				break;
#endif
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				context->mousex = event.button.x;
				context->mousey = event.button.y;
				context->buttons = (event.type ==SDL_MOUSEBUTTONDOWN)?GINPUT_MOUSE_BTN_LEFT:0;
				sem_post (input_event);
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.state & SDL_BUTTON_LMASK) {
					context->mousex = event.motion.x;
					context->mousey = event.motion.y;
					context->buttons = GINPUT_MOUSE_BTN_LEFT;
					sem_post (input_event);
				}
				break;
#endif
#if GINPUT_NEED_KEYBOARD
			case SDL_TEXTINPUT: {
				int i;
				sem_wait (ctx_mutex);
				for (i=0; context->keypos < sizeof  (context->keybuffer) && event.text.text[i]; ++i) {
					context->keybuffer[context->keypos].key = event.text.text[i];
					context->keybuffer[context->keypos++].keystate = 0;
				}
				sem_post (ctx_mutex);
				sem_post (input_event);
				break;
			
			}
			case SDL_KEYDOWN: 
			case SDL_KEYUP: {
				SDL_Keycode k_sdl = event.key.keysym.sym;
				gU8 k_ugfx = 0;
				gU32 s_ugfx = (event.type==SDL_KEYDOWN)?0:GKEYSTATE_KEYUP;
				int i;
				if (!(k_sdl & ~0x7f) && (k_sdl <32 || k_sdl == 127)) {
					k_ugfx = k_sdl;
				}
				else
					for (i = 0; SDL_keymap[i].k_sdl; ++i)
						if (SDL_keymap[i].k_sdl == k_sdl) {
							k_ugfx = SDL_keymap[i].k_ugfx;
							s_ugfx |= GKEYSTATE_SPECIAL;
							break;
						}
				for (i = 0; SDL_modmap[i].s_sdl; ++i)
					if (SDL_modmap[i].s_sdl & event.key.keysym.mod)
						s_ugfx |= SDL_modmap[i].s_ugfx;
				sem_wait (ctx_mutex);
				if (k_ugfx && context->keypos+1 < (int)sizeof  (context->keybuffer)) {
					context->keybuffer[context->keypos].key = k_ugfx;
					context->keybuffer[context->keypos++].keystate = s_ugfx;
				}
				sem_post (ctx_mutex);
				sem_post (input_event);
				break;
			}
#endif
			case SDL_QUIT:
				done = 1;
				break;
			default:
				break;
			}
		}
		SDL_Delay(40);
	}
	
	SDL_DestroyTexture (texture);
	SDL_DestroyRenderer (render);
	SDL_DestroyWindow (window);
    return 0;
}

static void *SDL_input_event_loop (void *arg) {
	(void)arg;
	for (;;) {
		sem_wait (input_event);
#if GINPUT_NEED_KEYBOARD
		if (keyboard)
			_gkeyboardWakeup (keyboard);
#endif
#if GINPUT_NEED_MOUSE
		if (mouse)
			_gmouseWakeup (mouse);
#endif
	}
	return 0;
}

// Init driver
// Must be executed on early stage of initialization:  before threads and timer

void sdl_driver_init (void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		exit (1) ;
	}

	if ((context = (struct SDL_UGFXContext*) mmap (0,sizeof (struct SDL_UGFXContext ),PROT_WRITE|PROT_READ,(MAP_ANONYMOUS | MAP_SHARED),0,0)) ==MAP_FAILED) {
		perror("Failed to allocate shared memory");
		exit(1);
	}

	// Create mutex for locking shared context
	sem_unlink (CTX_MUTEX_NAME);
	if((ctx_mutex = sem_open(CTX_MUTEX_NAME,O_CREAT,0666,1)) == SEM_FAILED) {
		perror("Failed init semaphore");
		exit(1);
	}

	// Create event for input notifications to ugfx process
	sem_unlink (INPUT_EVENT_NAME);
	if((input_event = sem_open(INPUT_EVENT_NAME,O_CREAT,0666,0)) == SEM_FAILED) {
		perror("Failed init semaphore");
		exit(1);
	}
	pid_t gui_pid = fork ();

	if (gui_pid) {
		// Main proccess. It's for host UI and SDL
		int status;
		memset (context,0,sizeof (*context));
		context->need_redraw = 1;
		context->maxx = GDISP_SCREEN_WIDTH-1;
		context->maxy = GDISP_SCREEN_HEIGHT-1;
		context->minx = 0;
		context->miny = 0;
		SDL_loop ();
		// cleanup
		kill(gui_pid,SIGKILL);
		waitpid(gui_pid, &status, 0);
		SDL_Quit ();
		munmap (context,sizeof (*context));
		sem_close (ctx_mutex);
		sem_unlink (CTX_MUTEX_NAME);
		sem_close (input_event);
		sem_unlink (INPUT_EVENT_NAME);
		exit (0);
	}
	
	// Create thread for input events processing
	pthread_t thread;
	pthread_create(&thread, NULL, SDL_input_event_loop, NULL);
	pthread_detach (thread);
	// Continue execution of ugfx UI in forked process
}


LLDSPEC gBool gdisp_lld_init(GDisplay *g) {
	g->board = 0;					// No board interface for this driver

#if GINPUT_NEED_MOUSE
	gdriverRegister((const GDriverVMT *)GMOUSE_DRIVER_VMT, g);
#endif
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = 100;

	g->g.Contrast = 50;
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;

	return gTrue;
}


static void SDL_extendUpdateRect (int x,int y) {
	if (context->minx > x)
		context->minx = x;
	if (context->miny > y)
		context->miny = y;
	if (context->maxx < x)
		context->maxx = x;
	if (context->maxy < y)
		context->maxy = y;
}

LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g)
{
	if (context) {
		context->framebuf[(g->p.y*GDISP_SCREEN_WIDTH)+g->p.x] = gdispColor2Native(g->p.color);
		SDL_extendUpdateRect (g->p.x,g->p.y);
		context->need_redraw = 1;
	}
}

#if GDISP_HARDWARE_FILLS
	LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
		LLDCOLOR_TYPE c = gdispColor2Native(g->p.color);
		if (context) {
			int x,y;
			gU32 *pbuf = context->framebuf + g->p.y*GDISP_SCREEN_WIDTH + g->p.x;
			int dy = GDISP_SCREEN_WIDTH - g->p.cx;
			for (y = 0; y < g->p.cy; ++y) {
				for (x = 0; x < g->p.cx; ++x)
					*pbuf++ = c;
				pbuf += dy;
			}
			SDL_extendUpdateRect (g->p.x,g->p.y);
			SDL_extendUpdateRect (g->p.x+g->p.cx-1,g->p.y+g->p.cy-1);
			context->need_redraw = 1;
		}
	}

#endif

#if GDISP_HARDWARE_PIXELREAD
	LLDSPEC gColor gdisp_lld_get_pixel_color(GDisplay *g) {
		if (context)
			return gdispNative2Color(context->framebuf[(g->p.y*GDISP_SCREEN_WIDTH)+g->p.x]);
		return 0;
	}
#endif

#if GINPUT_NEED_MOUSE
	static gBool SDL_MouseInit(GMouse *m, unsigned driverinstance) {
		mouse = m;
		(void)	driverinstance;
		return gTrue;
	}

	static gBool SDL_MouseRead(GMouse *m, GMouseReading *pt) {
		(void)	m;
		if (!context)
			return gFalse;
		pt->x = context->mousex;
		pt->y = context->mousey;
		pt->z = (context->buttons & GINPUT_MOUSE_BTN_LEFT) ? 1 : 0;
		pt->buttons = context->buttons;
		return gTrue;
	}
#endif /* GINPUT_NEED_MOUSE */

#if GINPUT_NEED_KEYBOARD
	static gBool SDL_KeyboardInit(GKeyboard *k, unsigned driverinstance) {
		keyboard = k;
		(void)	driverinstance;
		return gTrue;
	}

	static int SDL_KeyboardGetData(GKeyboard *k, gU8 *pch, int sz) {
		int i = 0;
		if (!context || !context->keypos || !sz)
			return 0;

		sem_wait (ctx_mutex);
		k->keystate = context->keybuffer[0].keystate;
		for (i = 0; i < sz && i < context->keypos && context->keybuffer[0].keystate == context->keybuffer[i].keystate; i++)
			pch[i] = context->keybuffer[i].key;
		context->keypos -= i;
		memmove (context->keybuffer,context->keybuffer+i,context->keypos * sizeof (context->keybuffer[0]));
		sem_post (ctx_mutex);
		return i;
	}
#endif /* GINPUT_NEED_KEYBOARD */

#endif /* GFX_USE_GDISP */
