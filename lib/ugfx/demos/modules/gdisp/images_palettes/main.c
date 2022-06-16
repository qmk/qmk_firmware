/*
 * Copyright (c) 2016, Joel Bodenmann aka Tectu <joel@embedded.pro>
 * Copyright (c) 2016, Andrew Hannam aka inmarket
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
 * This example demonstrates how the color palette of an image can be modified
 * during run-time of the program to exchange colors.
 * This example uses a BMP1 image (one-bit BMP) and which only has a palette
 * size of two.
 * Note that although the demo shows multiple images with different colors at
 * the same time there's still just one copy of the image in memory at all times.
 */

#define USE_PRINTF GFXON

#include "gfx.h"

static gImage _imgHome;

int main(void)
{
	int paletteSize = 0;

	// Initialize everything
	gfxInit();
	gdispClear(GFX_SILVER);

	// Open the image file
	gdispImageOpenFile(&_imgHome, "icon_home.bmp");
	
	// Retrieve the color palette size and dump it - just for fun.
	paletteSize = gdispImageGetPaletteSize(&_imgHome);
	if (paletteSize != 2) {		// With this image we expect the palette to have only two entries!
		gdispClear(GFX_RED);
		while (1);
	}
	
	// Draw the image w/o modifying the palette
	gdispImageDraw(&_imgHome, 10, 10, gdispGetWidth(), gdispGetHeight(), 0, 0);
	
	// Modify the palette & redraw at a different location
	gdispImageAdjustPalette(&_imgHome, 0, GFX_BLUE);
	gdispImageAdjustPalette(&_imgHome, 1, GFX_RED);
	gdispImageDraw(&_imgHome, 10, 60, gdispGetWidth(), gdispGetHeight(), 0, 0);
	
	// Modify the palette & redraw at a different location
	gdispImageAdjustPalette(&_imgHome, 0, GFX_WHITE);
	gdispImageAdjustPalette(&_imgHome, 1, GFX_BLACK);
	gdispImageDraw(&_imgHome, 10, 110, gdispGetWidth(), gdispGetHeight(), 0, 0);
	
	// Modify the palette & redraw at a different location
	gdispImageAdjustPalette(&_imgHome, 0, GFX_LIME);
	gdispImageAdjustPalette(&_imgHome, 1, GFX_NAVY);
	gdispImageDraw(&_imgHome, 10, 160, gdispGetWidth(), gdispGetHeight(), 0, 0);
	
	// Modify the palette & redraw at a different location
	gdispImageAdjustPalette(&_imgHome, 0, GFX_GRAY);
	gdispImageAdjustPalette(&_imgHome, 1, GFX_YELLOW);
	gdispImageDraw(&_imgHome, 60, 60, gdispGetWidth(), gdispGetHeight(), 0, 0);
	
	// Modify the palette & redraw at a different location
	gdispImageAdjustPalette(&_imgHome, 0, GFX_GREEN);
	gdispImageAdjustPalette(&_imgHome, 1, GFX_BLACK);
	gdispImageDraw(&_imgHome, 60, 110, gdispGetWidth(), gdispGetHeight(), 0, 0);
	
	// Modify the palette & redraw at a different location
	gdispImageAdjustPalette(&_imgHome, 0, GFX_LIME);
	gdispImageAdjustPalette(&_imgHome, 1, GFX_TEAL);
	gdispImageDraw(&_imgHome, 60, 160, gdispGetWidth(), gdispGetHeight(), 0, 0);
	
	// We're done. Clean up.
	gdispImageClose(&_imgHome);

	while(1) {
        gfxSleepMilliseconds(500);
	}

	return 0;
}
