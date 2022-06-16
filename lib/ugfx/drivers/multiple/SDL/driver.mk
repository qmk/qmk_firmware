GFXINC += $(GFXLIB)/drivers/multiple/SDL
GFXSRC += $(GFXLIB)/drivers/multiple/SDL/gdisp_lld_SDL.c
GFXDEFS += GFX_OS_PRE_INIT_FUNCTION=sdl_driver_init
CFLAGS += `sdl2-config --cflags || /usr/local/bin/sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs --cflags || /usr/local/bin/sdl2-config --libs --cflags`
