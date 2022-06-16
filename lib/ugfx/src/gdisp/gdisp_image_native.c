/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_GDISP && GDISP_NEED_IMAGE && GDISP_NEED_IMAGE_NATIVE

#include "gdisp_image_support.h"

/**
 * How big a pixel array to allocate for blitting
 * Bigger is faster but uses more RAM.
 */
#define BLIT_BUFFER_SIZE_NATIVE	32

#define HEADER_SIZE_NATIVE			8
#define FRAME0POS_NATIVE			(HEADER_SIZE_NATIVE)

/**
 * Helper Routines Needed
 */
void *gdispImageAlloc(gImage *img, gMemSize sz);
void gdispImageFree(gImage *img, void *ptr, gMemSize sz);

typedef struct gdispImagePrivate_NATIVE {
	gPixel		*frame0cache;
	gPixel		buf[BLIT_BUFFER_SIZE_NATIVE];
	} gdispImagePrivate_NATIVE;

void gdispImageClose_NATIVE(gImage *img) {
	gdispImagePrivate_NATIVE *	priv;

	priv = (gdispImagePrivate_NATIVE *)img->priv;
	if (priv) {
		if (priv->frame0cache)
			gdispImageFree(img, (void *)priv->frame0cache, img->width * img->height * sizeof(gPixel));
		gdispImageFree(img, (void *)priv, sizeof(gdispImagePrivate_NATIVE));
		img->priv = 0;
	}
}

gdispImageError gdispImageOpen_NATIVE(gImage *img) {
	gU8		hdr[HEADER_SIZE_NATIVE];

	/* Read the 8 byte header */
	if (gfileRead(img->f, hdr, 8) != 8)
		return GDISP_IMAGE_ERR_BADFORMAT;		// It can't be us

	if (hdr[0] != 'N' || hdr[1] != 'I')
		return GDISP_IMAGE_ERR_BADFORMAT;		// It can't be us

	if (hdr[6] != GDISP_PIXELFORMAT/256 || hdr[7] != (GDISP_PIXELFORMAT & 0xFF))
		return GDISP_IMAGE_ERR_UNSUPPORTED;		// Unsupported pixel format

	/* We know we are a native format image */
	img->flags = 0;
	img->width = (((gU16)hdr[2])<<8) | (hdr[3]);
	img->height = (((gU16)hdr[4])<<8) | (hdr[5]);
	if (img->width < 1 || img->height < 1)
		return GDISP_IMAGE_ERR_BADDATA;
	if (!(img->priv = gdispImageAlloc(img, sizeof(gdispImagePrivate_NATIVE))))
		return GDISP_IMAGE_ERR_NOMEMORY;
	((gdispImagePrivate_NATIVE *)(img->priv))->frame0cache = 0;

	img->type = GDISP_IMAGE_TYPE_NATIVE;
	return GDISP_IMAGE_ERR_OK;
}

gdispImageError gdispImageCache_NATIVE(gImage *img) {
	gMemSize		len;
	gdispImagePrivate_NATIVE *	priv;

	/* If we are already cached - just return OK */
	priv = (gdispImagePrivate_NATIVE *)img->priv;
	if (priv->frame0cache)
		return GDISP_IMAGE_ERR_OK;

	/* We need to allocate the cache */
	len = img->width * img->height * sizeof(gPixel);
	priv->frame0cache = (gPixel *)gdispImageAlloc(img, len);
	if (!priv->frame0cache)
		return GDISP_IMAGE_ERR_NOMEMORY;

	/* Read the entire bitmap into cache */
	gfileSetPos(img->f, FRAME0POS_NATIVE);
	if (gfileRead(img->f, priv->frame0cache, len) != len)
		return GDISP_IMAGE_ERR_BADDATA;

	return GDISP_IMAGE_ERR_OK;
}

gdispImageError gdispGImageDraw_NATIVE(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy) {
	gCoord		mx, mcx;
	gFileSize	pos;
	gMemSize	len;
	gdispImagePrivate_NATIVE *	priv;

	priv = (gdispImagePrivate_NATIVE *)img->priv;

	/* Check some reasonableness */
	if (sx >= img->width || sy >= img->height) return GDISP_IMAGE_ERR_OK;
	if (sx + cx > img->width) cx = img->width - sx;
	if (sy + cy > img->height) cy = img->height - sy;

	/* Draw from the image cache - if it exists */
	if (priv->frame0cache) {
		gdispGBlitArea(g, x, y, cx, cy, sx, sy, img->width, priv->frame0cache);
		return GDISP_IMAGE_ERR_OK;
	}

	/* For this image decoder we cheat and just seek straight to the region we want to display */
	pos = FRAME0POS_NATIVE + (img->width * sy + sx) * sizeof(gPixel);

	/* Cycle through the lines */
	for(;cy;cy--, y++) {
		/* Move to the start of the line */
		gfileSetPos(img->f, pos);

		/* Draw the line in chunks using BitBlt */
		for(mx = x, mcx = cx; mcx > 0; mcx -= len, mx += len) {
			// Read the data
			len = gfileRead(img->f,
						priv->buf,
						mcx > BLIT_BUFFER_SIZE_NATIVE ? (BLIT_BUFFER_SIZE_NATIVE*sizeof(gPixel)) : (mcx * sizeof(gPixel)))
					/ sizeof(gPixel);
			if (!len)
				return GDISP_IMAGE_ERR_BADDATA;

			/* Blit the chunk of data */
			gdispGBlitArea(g, mx, y, len, 1, 0, 0, len, priv->buf);
		}

		/* Get the position for the start of the next line */
		pos += img->width*sizeof(gPixel);
	}

	return GDISP_IMAGE_ERR_OK;
}

gDelay gdispImageNext_NATIVE(gImage *img) {
	(void) img;

	/* No more frames/pages */
	return gDelayForever;
}

#endif /* GFX_USE_GDISP && GDISP_NEED_IMAGE && GDISP_NEED_IMAGE_NATIVE */
