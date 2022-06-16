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

#include "gfx.h"

int main(void) {
	gCoord		width, y;
	gFont		font1, font2;
	gCoord		fheight1, fheight2;
	const char	*line1, *line2;
	char		buf[8];

    // Initialize and clear the display
    gfxInit();

    // Get the screen size
    width = gdispGetWidth();

    // Get the fonts we want to use
	font1 = gdispOpenFont("DejaVu*");
	font2 = gdispOpenFont("UI2*");
	//font2 = gdispOpenFont("Geosans*");
	//font2 = gdispOpenFont("Free*");
	//font2 = gdispOpenFont("Hellovetica*");
	//font2 = gdispOpenFont("babyblue*");
	//font2 = gdispOpenFont("PF Ronda*");
	//font2 = gdispOpenFont("Apple*");

	y = 0;
	fheight1 = gdispGetFontMetric(font1, gFontHeight)+2;
	fheight2 = gdispGetFontMetric(font2, gFontHeight)+2;

	line1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	line2 = "0123456789~!@#$%^&*_-+=(){}[]<>|/\\:;,.?'\"`";

	// Font 1
	gdispFillStringBox(0, y, width,  fheight1, line1, font1, GFX_BLACK, GFX_WHITE, gJustifyCenter);
	y += fheight1+1;
	gdispFillStringBox(0, y, width,  fheight1, line2, font1, GFX_BLACK, GFX_WHITE, gJustifyCenter);
	y += fheight1+1;

	// Font 2
	gdispFillStringBox(0, y, width,  fheight2, line1, font2, GFX_BLACK, GFX_WHITE, gJustifyCenter);
	y += fheight2+1;
	gdispFillStringBox(0, y, width,  fheight2, line2, font2, GFX_BLACK, GFX_WHITE, gJustifyCenter);
	y += fheight2+1;

	// Font 1 drawing White on the (black) background
	gdispDrawStringBox(0, y, width,  fheight1, line1, font1, GFX_WHITE, gJustifyCenter);
	y += fheight1+1;
	gdispDrawStringBox(0, y, width,  fheight1, line2, font1, GFX_WHITE, gJustifyCenter);
	y += fheight1+1;

		// Show Sizes
	buf[0] = (fheight1-2)/10 + '0';
	buf[1] = (fheight1-2)%10 + '0';
	buf[2] = ',';
	buf[3] = ' ';
	buf[4] = (fheight2-2)/10 + '0';
	buf[5] = (fheight2-2)%10 + '0';
	buf[6] = 0;
	gdispFillStringBox(0, y, width,  fheight1, buf, font1, GFX_RED, GFX_WHITE, gJustifyCenter);
	
	// Wait forever
    while(1) {
    	gfxSleepMilliseconds(500);
    }   
}

