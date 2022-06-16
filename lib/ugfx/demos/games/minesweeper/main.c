/*
 * Copyright (c) Joel Bodenmann aka Tectu <joel@embedded.pro>
 * Copyright (c) Andrew Hannam aka inmarket
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

/*
 * This program was originally contributed by community member "Fleck".
 *
 * Some minor changes have been made by the uGFX maintainers.
 */

#include "gfx.h"
#include "mines.h"

int main(void)
{
	GEventMouse ev;
#if !MINES_SHOW_SPLASH
	gFont font;
#endif

    gfxInit();
    ginputGetMouse(0);
    minesInit();

#if MINES_SHOW_SPLASH
    minesShowSplash();
#else
    font = gdispOpenFont("DejaVuSans16");
    gdispDrawString((gdispGetWidth()-gdispGetStringWidth("Touch to start!", font))/2, gdispGetHeight()-25, "Touch to start!", font, GFX_WHITE);
    gdispCloseFont(font);
#endif

    while (1) {
        ginputGetMouseStatus(0, &ev);
        if (ev.buttons & GINPUT_MOUSE_BTN_LEFT) {
            while (ev.buttons & GINPUT_MOUSE_BTN_LEFT) {            // Wait until release
                ginputGetMouseStatus(0, &ev);
            }

            minesStart();
        }
    }
}
