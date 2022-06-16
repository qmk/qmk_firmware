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


///////////////////////////////////////////////////////////////////////////
// GDISP                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GDISP                                GFXON

#define GDISP_NEED_VALIDATION                        GFXON
#define GDISP_NEED_CLIP                              GFXON
#define GDISP_NEED_CIRCLE                            GFXON
#define GDISP_NEED_CONVEX_POLYGON                    GFXON
//#define GDISP_NEED_SCROLL                            GFXON
#define GDISP_NEED_CONTROL                           GFXON
#define GDISP_NEED_TEXT                              GFXON
    #define GDISP_INCLUDE_FONT_UI2                   GFXON
#define GDISP_NEED_STREAMING	                     GFXON

#define GDISP_NEED_IMAGE                             GFXON
    #define GDISP_NEED_IMAGE_BMP                     GFXON
    #define GDISP_NEED_IMAGE_GIF                     GFXON

#define GDISP_DEFAULT_ORIENTATION                    gOrientationLandscape
#define GDISP_NEED_MULTITHREAD                       GFXON

///////////////////////////////////////////////////////////////////////////
// GWIN                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GWIN                                 GFXON

#define GWIN_NEED_WINDOWMANAGER                      GFXON
	#define GWIN_NEED_FLASHING						 GFXON

#define GWIN_NEED_CONSOLE                            GFXON
    #define GWIN_CONSOLE_USE_HISTORY                 GFXON
        #define GWIN_CONSOLE_HISTORY_AVERAGING       GFXON
        #define GWIN_CONSOLE_HISTORY_ATCREATE        GFXON
#define GWIN_NEED_GRAPH                              GFXON

#define GWIN_NEED_WIDGET                             GFXON
    #define GWIN_NEED_LABEL                          GFXON
        #define GWIN_LABEL_ATTRIBUTE                 GFXON
    #define GWIN_NEED_BUTTON                         GFXON
//        #define GWIN_BUTTON_LAZY_RELEASE             GFXON
    #define GWIN_NEED_SLIDER                         GFXON
    #define GWIN_NEED_CHECKBOX                       GFXON
    #define GWIN_NEED_IMAGE                          GFXON
    #define GWIN_NEED_RADIO                          GFXON
    #define GWIN_NEED_LIST                           GFXON
        #define GWIN_NEED_LIST_IMAGES                GFXON
    #define GWIN_NEED_PROGRESSBAR                    GFXON
        #define GWIN_PROGRESSBAR_AUTO                GFXON

#define GWIN_NEED_CONTAINERS                         GFXON
    #define GWIN_NEED_CONTAINER                      GFXON

#define GWIN_NEED_TABSET                             GFXON

///////////////////////////////////////////////////////////////////////////
// GEVENT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GEVENT                               GFXON

///////////////////////////////////////////////////////////////////////////
// GTIMER                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GTIMER                               GFXON

///////////////////////////////////////////////////////////////////////////
// GQUEUE                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GQUEUE                               GFXON

#define GQUEUE_NEED_ASYNC                            GFXON

///////////////////////////////////////////////////////////////////////////
// GINPUT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GINPUT                               GFXON

#define GINPUT_NEED_MOUSE                            GFXON
//#define GINPUT_NEED_TOGGLE                           GFXON
//#define GINPUT_NEED_DIAL                             GFXON

///////////////////////////////////////////////////////////////////////////
// GFILE                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GFILE                                GFXON

#define GFILE_NEED_PRINTG                            GFXON
#define GFILE_NEED_STRINGS                           GFXON

#define GFILE_NEED_ROMFS                             GFXON
//#define GFILE_NEED_NATIVEFS                          GFXON

///////////////////////////////////////////////////////////////////////////
// GMISC                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GMISC				                 GFXON
#define GMISC_NEED_INVSQRT			                 GFXON


#endif /* _GFXCONF_H */
