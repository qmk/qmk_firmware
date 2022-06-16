/*
 * Copyright (c) 2012, 2013, Joel Bodenmann aka Tectu <joel@unormal.org>
 * Copyright (c) 2012, 2013, Andrew Hannam aka inmarket
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

/* GFX sub-systems to turn on */
#define GFX_USE_GDISP			                GFXON
#define GFX_USE_GEVENT			                GFXON
#define GFX_USE_GTIMER			                GFXON
#define GFX_USE_GINPUT			                GFXON

#define GFX_USE_GFILE                           GFXON
#define GFILE_NEED_ROMFS                        GFXON
#define GFILE_MAX_GFILES                         24

/* Features for the GDISP sub-system. */
#define GDISP_NEED_CONTROL		                GFXON
#define GDISP_NEED_VALIDATION		            GFXON
#define GDISP_NEED_CLIP			                GFXON
#define GDISP_NEED_TEXT			                GFXON
#define GDISP_NEED_MULTITHREAD		            GFXON
#define GDISP_NEED_IMAGE		                GFXON
#define GDISP_NEED_IMAGE_BMP		            GFXON
#define GDISP_NEED_CIRCLE		                GFXON
#define GDISP_NEED_ELLIPSE		                GFXON
#define GDISP_NEED_ARC			                GFXON
#define GDISP_NEED_STARTUP_LOGO                 GFXOFF


//////////////////
#define GFX_USE_GWIN                            GFXON

#define GWIN_NEED_WINDOWMANAGER                 GFXON
#define GQUEUE_NEED_ASYNC                       GFXON
#define GFX_USE_GQUEUE                          GFXON
#define GWIN_REDRAW_IMMEDIATE                   GFXON
#define GWIN_REDRAW_SINGLEOP                    GFXON

#define GWIN_NEED_WIDGET                        GFXON
#define GWIN_NEED_BUTTON                        GFXON
#define GWIN_BUTTON_LAZY_RELEASE                GFXOFF
#define GWIN_NEED_SLIDER                        GFXON
#define GWIN_FLAT_STYLING                       GFXOFF

#define GWIN_NEED_CONTAINERS                    GFXON
#define GWIN_NEED_CONTAINER                     GFXON
#define GWIN_NEED_FRAME                         GFXOFF
#define GWIN_NEED_TABSET                        GFXOFF


#define GWIN_NEED_CONSOLE                            GFXON
    #define GWIN_CONSOLE_USE_HISTORY                 GFXON
        #define GWIN_CONSOLE_HISTORY_AVERAGING       GFXON
        #define GWIN_CONSOLE_HISTORY_ATCREATE        GFXON
    #define GWIN_CONSOLE_ESCSEQ                      GFXON
    #define GWIN_CONSOLE_USE_BASESTREAM              GFXON
#define GWIN_NEED_GRAPH                              GFXON



/* Builtin Fonts */
#define GDISP_INCLUDE_FONT_DEJAVUSANS16      GFXON


/* Features for the GINPUT sub-system. */
#define GINPUT_NEED_MOUSE                       GFXON

#endif /* _GFXCONF_H */
