/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gdisp/gdisp_image.h
 *
 * @defgroup Image Image
 * @ingroup GDISP
 *
 * @brief   Sub-Module for image handling.
 *
 * @{
 */

#ifndef _GDISP_IMAGE_H
#define _GDISP_IMAGE_H
#if (GFX_USE_GDISP && GDISP_NEED_IMAGE) || defined(__DOXYGEN__)

/**
 * @brief	The type of image
 */
typedef gU16	gdispImageType;
	#define GDISP_IMAGE_TYPE_UNKNOWN	0
	#define GDISP_IMAGE_TYPE_NATIVE		1
	#define GDISP_IMAGE_TYPE_GIF		2
	#define GDISP_IMAGE_TYPE_BMP		3
	#define GDISP_IMAGE_TYPE_JPG		4
	#define GDISP_IMAGE_TYPE_PNG		5

/**
 * @brief	An image error code
 */
typedef gU16	gdispImageError;
	#define GDISP_IMAGE_ERR_OK					0
	#define GDISP_IMAGE_ERR_UNRECOVERABLE		0x8000
	#define GDISP_IMAGE_ERR_BADFORMAT			(GDISP_IMAGE_ERR_UNRECOVERABLE+1)
	#define GDISP_IMAGE_ERR_BADDATA				(GDISP_IMAGE_ERR_UNRECOVERABLE+2)
	#define GDISP_IMAGE_ERR_UNSUPPORTED			(GDISP_IMAGE_ERR_UNRECOVERABLE+3)
	#define GDISP_IMAGE_ERR_UNSUPPORTED_OK		3
	#define GDISP_IMAGE_ERR_NOMEMORY			(GDISP_IMAGE_ERR_UNRECOVERABLE+4)
	#define GDISP_IMAGE_ERR_NOSUCHFILE			(GDISP_IMAGE_ERR_UNRECOVERABLE+5)
	#define GDISP_IMAGE_ERR_NULLPOINTER         (GDISP_IMAGE_ERR_UNRECOVERABLE+6)

/**
 * @brief	Image flags
 */
typedef gU16	gdispImageFlags;
	#define GDISP_IMAGE_FLG_TRANSPARENT			0x0001	/* The image has transparency */
	#define GDISP_IMAGE_FLG_ANIMATED			0x0002	/* The image has animation */
	#define GDISP_IMAGE_FLG_MULTIPAGE			0x0004	/* The image has multiple pages */

/**
 * @brief	The structure for an image
 */
typedef struct gImage {
	gdispImageType						type;				/* @< The image type */
	gdispImageFlags						flags;				/* @< The image flags */
	gColor								bgcolor;			/* @< The default background color */
	gCoord								width, height;		/* @< The image dimensions */
	GFILE *								f;					/* @< The underlying GFILE */
	#if GDISP_NEED_IMAGE_ACCOUNTING
		gU32						memused;			/* @< How much RAM is currently allocated */
		gU32						maxmemused;			/* @< How much RAM has been allocated (maximum) */
	#endif
	const struct gdispImageHandlers *	fns;				/* @< Don't mess with this! */
	void *								priv;				/* @< Don't mess with this! */
} gImage;

/**
 * @brief	Initialise a gImage object
 *
 * @param[in] img  		The image structure to initialise
 *
 */
void gdispImageInit(gImage *img);

/**
 * @brief	Open an image using an open GFILE and get it ready for drawing
 * @details	Determine the image format and get ready to decode the first image frame
 * @return	GDISP_IMAGE_ERR_OK (0) on success or an error code.
 *
 * @param[in] img  		The image structure
 * @param[in] f			The open GFILE stream.
 *
 * @pre		The GFILE must be open for reading.
 *
 * @note	This determines which decoder to use and then initialises all other fields
 * 			in the gImage structure.
 * @note	The image background color is set to White.
 * @note	There are three types of return - everything OK, partial success and unrecoverable
 * 			failures. For everything OK it returns GDISP_IMAGE_ERR_OK. A partial success can
 * 			be distinguished from a unrecoverable failure by testing the GDISP_IMAGE_ERR_UNRECOVERABLE
 * 			bit in the error code.
 * 			A partial success return code means an image can still be drawn but perhaps with
 * 			reduced functionality eg only the first page of a multi-page image.
 * @note	@p gdispImageClose() should be called when finished with the image. This will close
 * 			the image and its underlying GFILE file. Note that images opened with partial success
 * 			(eg GDISP_IMAGE_ERR_UNSUPPORTED_OK)
 * 			still need to be closed when you are finished with them.
 */
gdispImageError gdispImageOpenGFile(gImage *img, GFILE *f);

/**
 * @brief	Open an image in a file and get it ready for drawing
 * @details	Determine the image format and get ready to decode the first image frame
 * @return	GDISP_IMAGE_ERR_OK (0) on success or an error code.
 *
 * @pre		You must have included the file-system support into GFILE that you want to use.
 *
 * @param[in] img  		The image structure
 * @param[in] filename	The filename to open
 *
 * @note	This function just opens the GFILE using the filename and passes it to @p gdispImageOpenGFile().
 */
#define gdispImageOpenFile(img, filename)			gdispImageOpenGFile((img), gfileOpen((filename), "rb"))

/**
 * @brief	Open an image in a ChibiOS basefilestream and get it ready for drawing
 * @details	Determine the image format and get ready to decode the first image frame
 * @return	GDISP_IMAGE_ERR_OK (0) on success or an error code.
 *
 * @pre		GFILE_NEED_CHIBIOSFS and GFX_USE_OS_CHIBIOS must be GFXON. This only makes sense on the ChibiOS
 * 			operating system.
 *
 * @param[in] img  				The image structure
 * @param[in] BaseFileStreamPtr	A pointer to an open BaseFileStream
 *
 * @note	This function just opens the GFILE using the basefilestream and passes it to @p gdispImageOpenGFile().
 */
#define gdispImageOpenBaseFileStream(img, BaseFileStreamPtr)			gdispImageOpenGFile((img), gfileOpenBaseFileStream((BaseFileStreamPtr), "rb"))

/**
 * @brief	Open an image in memory and get it ready for drawing
 * @details	Determine the image format and get ready to decode the first image frame
 * @return	GDISP_IMAGE_ERR_OK (0) on success or an error code.
 *
 * @pre		GFILE_NEED_MEMFS must be GFXON
 *
 * @param[in] img  		The image structure
 * @param[in] ptr		A pointer to the image bytes in memory
 *
 * @note	This function just opens the GFILE using the basefilestream and passes it to @p gdispImageOpenGFile().
 */
#define gdispImageOpenMemory(img, ptr)			gdispImageOpenGFile((img), gfileOpenMemory((void *)(ptr), "rb"))

/**
 * @brief	Close an image and release any dynamically allocated working storage.
 *
 * @param[in] img   The image structure
 *
 * @pre		gdispImageOpenFile() must have returned successfully.
 *
 * @note	Also calls the IO close function (if it hasn't already been called).
 */
void gdispImageClose(gImage *img);

/**
 * @brief	Is an image open.
 * @return	gTrue if the image is currently open.
 *
 * @param[in] img   The image structure
 *
 * @note	Be careful with calling this on an uninitialized image structure as the image
 * 			will contain random data which may be interpreted as meaning the image
 * 			is open. Clearing the Image structure to 0's will guarantee the image
 * 			is seen as being closed.
 */
gBool gdispImageIsOpen(gImage *img);

/**
 * @brief	Set the background color of the image.
 *
 * @param[in] img   	The image structure
 * @param[in] bgcolor	The background color to use
 *
 * @pre		gdispImageOpen() must have returned successfully.
 *
 * @note	This color is only used when an image has to restore part of the background before
 * 			continuing with drawing that includes transparency eg some GIF animations.
 */
void gdispImageSetBgColor(gImage *img, gColor bgcolor);

/**
 * @brief	Cache the image
 * @details	Decodes and caches the current frame into RAM.
 * @return	GDISP_IMAGE_ERR_OK (0) on success or an error code.
 *
 * @param[in] img   The image structure
 *
 * @pre		gdispImageOpen() must have returned successfully.
 *
 * @note	This can use a LOT of RAM!
 * @note	The decoder may choose to ignore the request for caching. If it does so it will
 * 			return GDISP_IMAGE_ERR_UNSUPPORTED_OK.
 * @note	A fatal error here does not necessarily mean that drawing the image will fail. For
 * 			example, a GDISP_IMAGE_ERR_NOMEMORY error simply means there isn't enough RAM to
 * 			cache the image.
 */
gdispImageError gdispImageCache(gImage *img);

/**
 * @brief	Draw the image
 * @return	GDISP_IMAGE_ERR_OK (0) on success or an error code.
 *
 * @param[in] g   	The display to draw on
 * @param[in] img   The image structure
 * @param[in] x,y	The screen location to draw the image
 * @param[in] cx,cy	The area on the screen to draw
 * @param[in] sx,sy	The image position to start drawing at
 *
 * @pre		gdispImageOpen() must have returned successfully.
 *
 * @note	If sx,sy + cx,cy is outside the image boundaries the area outside the image
 * 			is simply not drawn.
 * @note	If @p gdispImageCache() has been called first for this frame, this routine will draw using a
 * 			fast blit from the cached frame. If not, it reads the input and decodes it as it
 * 			is drawing. This may be significantly slower than if the image has been cached (but
 * 			uses a lot less RAM)
 */
gdispImageError gdispGImageDraw(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy);
#define gdispImageDraw(img,x,y,cx,cy,sx,sy)		gdispGImageDraw(GDISP,img,x,y,cx,cy,sx,sy)

/**
 * @brief	Prepare for the next frame/page in the image file.
 * @return	A time in milliseconds to keep displaying the current frame before trying to draw
 * 			the next frame. Watch out for the special values gDelayNone and gDelayForever.
 *
 * @param[in] img   The image structure
 *
 * @pre		gdispImageOpen() must have returned successfully.
 *
 * @note	It will return gDelayNone if the first frame/page hasn't been drawn or if the next frame
 * 			should be drawn immediately.
 * @note	It will return gDelayForever if another image frame doesn't exist or an error has occurred.
 * @note	Images that support multiple pages (eg TIFF files) will return gDelayNone between pages
 * 			and then gDelayForever when there are no more pages.
 * @note	An image that displays a looped animation will never return gDelayForever unless it
 * 			gets an error.
 * @note	Calling gdispImageDraw() after getting a gDelayForever will go back to drawing the first
 * 			frame/page.
 */
gDelay gdispImageNext(gImage *img);

/**
 * @brief	Get the number of entries in the color palette.
 * @return	The number of entries in the color palette or 0 if the image doesn't use a color palette.
 *
 * @param[in] img	The image structure
 *
 * @pre		gdispImageOpen() must have returned successfully.
 */
gU16 gdispImageGetPaletteSize(gImage *img);

/**
 * @brief	Get an entry in the color palette.
 * @return	The color value at a given position in the color palette.
 *
 * @param[in] img	The image structure
 * @param[in] index	The index of the color palette entry
 *
 * @pre		gdispImageOpen() must have returned successfully.
 *
 * @note	This function will return 0 if the index is out of bounds or if the image doesn't use a color palette.
 */
gColor gdispImageGetPalette(gImage *img, gU16 index);

/**
 * @brief	Modify an entry in the color palette.
 * @return	@p gTrue on success, @p gFalse otherwise.
 *
 * @param[in] img		The image structure
 * @param[in] index		The index of the color palette entry
 * @param[in] newColor	The new color value of the specified entry
 *
 * @pre		gdispImageOpen() must have returned successfully.
 * @note	This function will return @p gFalse if the index is out of bounds or if the image doesn't use a color palette.
 */
gBool gdispImageAdjustPalette(gImage *img, gU16 index, gColor newColor);

#endif /* GFX_USE_GDISP && GDISP_NEED_IMAGE */
#endif /* _GDISP_IMAGE_H */
/** @} */

