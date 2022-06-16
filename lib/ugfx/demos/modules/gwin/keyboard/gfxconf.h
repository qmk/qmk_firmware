/**
 * This file has a different license to the rest of the uGFX system.
 * You can copy, modify and distribute this file as you see fit.
 * You do not need to publish your source modifications to this file.
 * The only thing you are not permitted to do is to relicense it
 * under a different license.
 */

/**
 * Copy this file into your project directory and rename it as gfxconf.h
 * Edit your copy to turn on the uGFX features you want to use.
 * The values below are the defaults. You should delete anything
 * you are leaving as default.
 *
 * Please use spaces instead of tabs in this file.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

/* The operating system to use. One of these must be defined - preferably in your Makefile */
//#define GFX_USE_OS_CHIBIOS                         GFXON
//#define GFX_USE_OS_WIN32                           GFXON
//#define GFX_USE_OS_LINUX                           GFXON
//#define GFX_USE_OS_OSX                             GFXON

#define GFX_USE_GDISP                                GFXON

#define GDISP_NEED_VALIDATION                        GFXON
#define GDISP_NEED_CLIP                              GFXON
//#define GDISP_NEED_SCROLL                            GFXON
#define GDISP_NEED_TEXT                              GFXON
    #define GDISP_INCLUDE_FONT_UI2                   GFXON

//#define GDISP_NEED_CONTROL                           GFXON
//#define GDISP_DEFAULT_ORIENTATION                    gOrientationLandscape
#define GDISP_NEED_MULTITHREAD                       GFXON

#define GFX_USE_GWIN                                 GFXON
#define GWIN_NEED_WINDOWMANAGER                      GFXON
#define GWIN_NEED_CONSOLE                            GFXON
#define GWIN_NEED_WIDGET                             GFXON
    #define GWIN_NEED_KEYBOARD                       GFXON

#define GFX_USE_GEVENT                               GFXON
#define GFX_USE_GTIMER                               GFXON

#define GFX_USE_GQUEUE                               GFXON
#define GQUEUE_NEED_ASYNC                            GFXON

#define GFX_USE_GINPUT                               GFXON
#define GINPUT_NEED_MOUSE                            GFXON
//#define GINPUT_NEED_KEYBOARD                         GFXON

#endif /* _GFXCONF_H */
