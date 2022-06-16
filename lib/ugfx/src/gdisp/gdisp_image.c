/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_GDISP && GDISP_NEED_IMAGE

#include "gdisp_image_support.h"

#if GDISP_NEED_IMAGE_NATIVE
	extern gdispImageError gdispImageOpen_NATIVE(gImage *img);
	extern void gdispImageClose_NATIVE(gImage *img);
	extern gdispImageError gdispImageCache_NATIVE(gImage *img);
	extern gdispImageError gdispGImageDraw_NATIVE(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy);
	extern gDelay gdispImageNext_NATIVE(gImage *img);
#endif

#if GDISP_NEED_IMAGE_GIF
	extern gdispImageError gdispImageOpen_GIF(gImage *img);
	extern void gdispImageClose_GIF(gImage *img);
	extern gdispImageError gdispImageCache_GIF(gImage *img);
	extern gdispImageError gdispGImageDraw_GIF(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy);
	extern gDelay gdispImageNext_GIF(gImage *img);
#endif

#if GDISP_NEED_IMAGE_BMP
	extern gdispImageError gdispImageOpen_BMP(gImage *img);
	extern void gdispImageClose_BMP(gImage *img);
	extern gdispImageError gdispImageCache_BMP(gImage *img);
	extern gdispImageError gdispGImageDraw_BMP(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy);
	extern gDelay gdispImageNext_BMP(gImage *img);
	extern gU16 gdispImageGetPaletteSize_BMP(gImage *img);
	extern gColor gdispImageGetPalette_BMP(gImage *img, gU16 index);
	extern gBool gdispImageAdjustPalette_BMP(gImage *img, gU16 index, gColor newColor);
#endif

#if GDISP_NEED_IMAGE_JPG
	extern gdispImageError gdispImageOpen_JPG(gImage *img);
	extern void gdispImageClose_JPG(gImage *img);
	extern gdispImageError gdispImageCache_JPG(gImage *img);
	extern gdispImageError gdispGImageDraw_JPG(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy);
	extern gDelay gdispImageNext_JPG(gImage *img);
#endif

#if GDISP_NEED_IMAGE_PNG
	extern gdispImageError gdispImageOpen_PNG(gImage *img);
	extern void gdispImageClose_PNG(gImage *img);
	extern gdispImageError gdispImageCache_PNG(gImage *img);
	extern gdispImageError gdispGImageDraw_PNG(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy);
	extern gDelay gdispImageNext_PNG(gImage *img);
#endif

/* The structure defining the routines for image drawing */
typedef struct gdispImageHandlers {
	gdispImageError	(*open)(gImage *img);					/* The open function */
	void			(*close)(gImage *img);					/* The close function */
	gdispImageError	(*cache)(gImage *img);					/* The cache function */
	gdispImageError	(*draw)(GDisplay *g,
							gImage *img,
							gCoord x, gCoord y,
							gCoord cx, gCoord cy,
							gCoord sx, gCoord sy);			/* The draw function */
	gDelay		(*next)(gImage *img);					/* The next frame function */
	gU16		(*getPaletteSize)(gImage *img);			/* Retrieve the size of the palette (number of entries) */
	gColor			(*getPalette)(gImage *img, gU16 index);							/* Retrieve a specific color value of the palette */
	gBool			(*adjustPalette)(gImage *img, gU16 index, gColor newColor);	/* Replace a color value in the palette */
} gdispImageHandlers;

static gdispImageHandlers ImageHandlers[] = {
	#if GDISP_NEED_IMAGE_NATIVE
		{	gdispImageOpen_NATIVE,	gdispImageClose_NATIVE,
			gdispImageCache_NATIVE,	gdispGImageDraw_NATIVE,	gdispImageNext_NATIVE,
			0,						0,						0
		},
	#endif
	#if GDISP_NEED_IMAGE_GIF
		{	gdispImageOpen_GIF,		gdispImageClose_GIF,
			gdispImageCache_GIF,	gdispGImageDraw_GIF,	gdispImageNext_GIF,
			0,						0,						0
		},
	#endif
	#if GDISP_NEED_IMAGE_BMP
		{	gdispImageOpen_BMP,				gdispImageClose_BMP,
			gdispImageCache_BMP,			gdispGImageDraw_BMP,		gdispImageNext_BMP,
			gdispImageGetPaletteSize_BMP,	gdispImageGetPalette_BMP,	gdispImageAdjustPalette_BMP
		},
	#endif
	#if GDISP_NEED_IMAGE_JPG
		{	gdispImageOpen_JPG,		gdispImageClose_JPG,
			gdispImageCache_JPG,	gdispGImageDraw_JPG,	gdispImageNext_JPG,
			0,						0,						0
		},
	#endif
	#if GDISP_NEED_IMAGE_PNG
		{	gdispImageOpen_PNG,		gdispImageClose_PNG,
			gdispImageCache_PNG,	gdispGImageDraw_PNG,	gdispImageNext_PNG,
			0,						0,						0
		},
	#endif
};

void gdispImageInit(gImage *img) {
	img->type = GDISP_IMAGE_TYPE_UNKNOWN;
}

gdispImageError gdispImageOpenGFile(gImage *img, GFILE *f) {
	gdispImageError err;

	if (!img)
		return GDISP_IMAGE_ERR_NULLPOINTER;
	if (!f)
		return GDISP_IMAGE_ERR_NOSUCHFILE;
	img->f = f;
	img->bgcolor = GFX_WHITE;
	for(img->fns = ImageHandlers; img->fns < ImageHandlers+sizeof(ImageHandlers)/sizeof(ImageHandlers[0]); img->fns++) {
		err = img->fns->open(img);
		if (err != GDISP_IMAGE_ERR_BADFORMAT) {
			if ((err & GDISP_IMAGE_ERR_UNRECOVERABLE))
				goto unrecoverable;

			// Everything is possible
			return err;
		}

		// Try the next decoder
		gfileSetPos(img->f, 0);
	}

	err = GDISP_IMAGE_ERR_BADFORMAT;
	img->type = GDISP_IMAGE_TYPE_UNKNOWN;

unrecoverable:
	gfileClose(img->f);
	img->f = 0;
	img->flags = 0;
	img->fns = 0;
	img->priv = 0;
	return err;
}

void gdispImageClose(gImage *img) {
	if (!img)
		return;
	if (img->fns)
		img->fns->close(img);
	gfileClose(img->f);
	img->type = GDISP_IMAGE_TYPE_UNKNOWN;
	img->flags = 0;
	img->fns = 0;
	img->priv = 0;
}

gBool gdispImageIsOpen(gImage *img) {
	return img && img->type != GDISP_IMAGE_TYPE_UNKNOWN && img->fns != 0;
}

void gdispImageSetBgColor(gImage *img, gColor bgcolor) {
	if (!img)
		return;
	img->bgcolor = bgcolor;
}

gdispImageError gdispImageCache(gImage *img) {
	if (!img) return GDISP_IMAGE_ERR_NULLPOINTER;
	if (!img->fns) return GDISP_IMAGE_ERR_BADFORMAT;
	return img->fns->cache(img);
}

gdispImageError gdispGImageDraw(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy) {
	if (!img) return GDISP_IMAGE_ERR_NULLPOINTER;
	if (!img->fns) return GDISP_IMAGE_ERR_BADFORMAT;

	// Check on window
	if (cx <= 0 || cy <= 0) return GDISP_IMAGE_ERR_OK;
	if (sx < 0) sx = 0;
	if (sy < 0) sy = 0;
	if (sx >= img->width || sy >= img->height) return GDISP_IMAGE_ERR_OK;
	if (sx + cx > img->width)  cx = img->width - sx;
	if (sy + cy > img->height) cy = img->height - sy;

	// Draw
	return img->fns->draw(g, img, x, y, cx, cy, sx, sy);
}

gDelay gdispImageNext(gImage *img) {
	if (!img) return GDISP_IMAGE_ERR_NULLPOINTER;
	if (!img->fns) return GDISP_IMAGE_ERR_BADFORMAT;
	return img->fns->next(img);
}

gU16 gdispImageGetPaletteSize(gImage *img) {
	if (!img || !img->fns) return 0;
	if (!img->fns->getPaletteSize) return 0;
	return img->fns->getPaletteSize(img);
}

gColor gdispImageGetPalette(gImage *img, gU16 index) {
	if (!img || !img->fns) return 0;
	if (!img->fns->getPalette) return 0;
	return img->fns->getPalette(img, index);
}

gBool gdispImageAdjustPalette(gImage *img, gU16 index, gColor newColor) {
	if (!img || !img->fns) return gFalse;
	if (!img->fns->adjustPalette) return gFalse;
	return img->fns->adjustPalette(img, index, newColor);
}


// Helper Routines
void *gdispImageAlloc(gImage *img, gMemSize sz) {
	#if GDISP_NEED_IMAGE_ACCOUNTING
		void *ptr;

		ptr = gfxAlloc(sz);
		if (ptr) {
			img->memused += sz;
			if (img->memused > img->maxmemused)
				img->maxmemused = img->memused;
		}
		return ptr;
	#else
		(void) img;
		return gfxAlloc(sz);
	#endif
}

void gdispImageFree(gImage *img, void *ptr, gMemSize sz) {
	#if GDISP_NEED_IMAGE_ACCOUNTING
		gfxFree(ptr);
		img->memused -= sz;
	#else
		(void) img;
		(void) sz;
		gfxFree(ptr);
	#endif
}

#if GFX_CPU_ENDIAN != GFX_CPU_ENDIAN_LITTLE && GFX_CPU_ENDIAN != GFX_CPU_ENDIAN_BIG \
		&& GFX_CPU_ENDIAN != GFX_CPU_ENDIAN_WBDWL && GFX_CPU_ENDIAN != GFX_CPU_ENDIAN_WLDWB

	union wbyteorder_u {
		gU8		b[2];
		gU32	w;
	};
	union dwbyteorder_u {
		gU8		b[4];
		gU32	l;
	};

	gU16 gdispImageH16toLE16(gU16 w) {
		union wbyteorder_u	we;

		we.w = w;
		return	 (((gU16)we.b[0]))|(((gU16)we.b[1]) << 8);
	}
	gU16 gdispImageH16toBE16(gU16 w) {
		union wbyteorder_u	we;

		we.w = w;
		return	 (((gU16)we.b[0]) << 8)|(((gU16)we.b[1]));
	}

	gU32 gdispImageH32toLE32(gU32 dw) {
		union dwbyteorder_u	we;

		we.l = dw;
		return	 (((gU32)we.b[0]))
				|(((gU32)we.b[1]) << 8)
				|(((gU32)we.b[2]) << 16)
				|(((gU32)we.b[3]) << 24);
	}
	gU32 gdispImageH32toBE32(gU32 dw) {
		union dwbyteorder_u	we;

		we.l = dw;
		return	 (((gU32)we.b[0]) << 24)
				|(((gU32)we.b[1]) << 16)
				|(((gU32)we.b[2]) << 8)
				|(((gU32)we.b[3]));
	}
#endif

#endif /* GFX_USE_GDISP && GDISP_NEED_IMAGE */
