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

// This function draws a thick arc and a non-thick arc together
static void _drawCombinedArc(int x, int y, int angle1, int angle2)
{
	gdispDrawThickArc(x, y, 40, 60, angle1, angle2, GFX_RED);
	gdispDrawArc(x, y, 50, angle1, angle2, GFX_WHITE);
}

int main(void)
{
	int i = 35;

    // Initialize the uGFX library
    gfxInit();

	while(1) {
		// Clear the entire screen
		gdispClear(GFX_BLACK);

		// Draw some thick arcs with an outline
		_drawCombinedArc(150, 150, (i / 360) * 15 + 55, 55+i);
		_drawCombinedArc(300, 150, 100+i, (i / 360) * 15 + 100);
		_drawCombinedArc(300, 300, (i / 360) * 15 + 145, 145+i);
		_drawCombinedArc(150, 300, (i / 360) * 15 + 195, 195-i);
		
		// Draw different arcs the next time
		i++;

		// Wait a bit
		gfxSleepMilliseconds(20);
	}
}
