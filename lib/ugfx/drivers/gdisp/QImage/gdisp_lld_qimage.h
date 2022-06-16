#pragma once

#include "../../../gfx.h"

/* This test is needed as this file is also included in the .cpp file providing the below functions */
#ifdef __cplusplus
extern "C" {
#endif

gBool qimage_init(GDisplay* g, gCoord width, gCoord height);
void qimage_setPixel(GDisplay* g);
gColor qimage_getPixel(GDisplay* g);

#ifdef __cplusplus
}
#endif
