/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gdisp/gdisp_options.h
 * @brief   GDISP sub-system options header file.
 *
 * @addtogroup GDISP
 * @{
 */

#ifndef _GDISP_OPTIONS_H
#define _GDISP_OPTIONS_H

/**
 * @name    GDISP Functionality to be included
 * @{
 */
	/**
	 * @brief   Should drawing operations be automatically flushed.
	 * @details	Defaults to GFXOFF
	 * @note	If set to GFXOFF and the controller requires flushing
	 * 			then the application must manually call @p gdispGFlush().
	 * 			Setting this to GFXON causes GDISP to automatically flush
	 * 			after each drawing operation. Note this may be slow but enables
	 * 			an application to avoid having to manually call the flush routine.
	 * @note	If GFXON and GDISP_NEED_TIMERFLUSH is also GFXON, this takes precedence.
	 * @note	Most controllers don't need flushing which is why this is set to
	 * 			GFXOFF by default.
	 */
	#ifndef GDISP_NEED_AUTOFLUSH
		#define GDISP_NEED_AUTOFLUSH			GFXOFF
	#endif
	/**
	 * @brief   Should drawing operations be automatically flushed on a timer.
	 * @details	Defaults to GFXOFF, Can be set to GFXOFF or a timer period in milliseconds.
	 * @note	The period should not be set too short or it will consume all your CPU. A
	 * 			value between 250 and 500 milliseconds would probably be suitable.
	 * @note	If GFXON and GDISP_NEED_AUTOFLUSH is also GFXON, this is ineffective.
	 * @note	Most controllers don't need flushing which is why this is set to
	 * 			GFXOFF by default.
	 */
	#ifndef GDISP_NEED_TIMERFLUSH
		#define GDISP_NEED_TIMERFLUSH			GFXOFF
	#endif
	/**
	 * @brief   Should all operations be clipped to the screen and colors validated.
	 * @details	Defaults to GFXON.
	 * @note    If this is GFXOFF, any operations that extend beyond the
	 *          edge of the screen will have undefined results. Any
	 *			out-of-range colors will produce undefined results.
	 * @note	This should always be left as the default (GFXON) unless you
	 * 			are a maniac for speed and you have thoroughly tested your code
	 * 			and it never overwrites the edges of the screen.
	 * @note	Setting GDISP_NEED_CLIP to GFXON internally uses the same mechanism
	 * 			as this validation. There is no advantage in setting this GFXOFF if
	 * 			GDISP_NEED_CLIP is GFXON.
	 */
	#ifndef GDISP_NEED_VALIDATION
		#define GDISP_NEED_VALIDATION			GFXON
	#endif
	/**
	 * @brief   Are clipping functions needed.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_CLIP
		#define GDISP_NEED_CLIP					GFXON
	#endif
	/**
	 * @brief   Streaming functions are needed
	 * @details	Defaults to GFXOFF.
	 */
	#ifndef GDISP_NEED_STREAMING
		#define GDISP_NEED_STREAMING			GFXOFF
	#endif
	/**
	 * @brief   Are text functions needed.
	 * @details	Defaults to GFXOFF
	 * @note	You must also define at least one font.
	 */
	#ifndef GDISP_NEED_TEXT
		#define GDISP_NEED_TEXT					GFXOFF
	#endif
	/**
	 * @brief   Are circle functions needed.
	 * @details	Defaults to GFXOFF
	 * @note	Uses integer algorithms only. It does not use any trig or floating point.
	 */
	#ifndef GDISP_NEED_CIRCLE
		#define GDISP_NEED_CIRCLE				GFXOFF
	#endif
	/**
	 * @brief   Are dual circle functions needed (one circle inside another).
	 * @details	Defaults to GFXOFF
	 * @note	Uses integer algorithms only. It does not use any trig or floating point.
	 */
	#ifndef GDISP_NEED_DUALCIRCLE
		#define GDISP_NEED_DUALCIRCLE			GFXOFF
	#endif
	/**
	 * @brief   Are ellipse functions needed.
	 * @details	Defaults to GFXOFF
	 * @note	Uses integer algorithms only. It does not use any trig or floating point.
	 */
	#ifndef GDISP_NEED_ELLIPSE
		#define GDISP_NEED_ELLIPSE				GFXOFF
	#endif
	/**
	 * @brief   Are arc sector functions needed.
	 * @details	Defaults to GFXOFF
	 * @note	Uses integer algorithms only. It does not use any trig or floating point.
	 */
	#ifndef GDISP_NEED_ARCSECTORS
		#define GDISP_NEED_ARCSECTORS			GFXOFF
	#endif
	/**
	 * @brief   Are arc functions needed.
	 * @details	Defaults to GFXOFF
	 * @note	This can be compiled using fully integer mathematics by
	 * 			defining GFX_USE_GMISC and GMISC_NEED_FIXEDTRIG as GFXON.
	 * @note	This can be compiled to use floating point but no trig functions
	 * 			by defining GFX_USE_GMISC and GMISC_NEED_FASTTRIG as GFXON.
	 * @note	If neither of the above are defined it requires the maths library
	 * 			to be included in the link to provide floating point and trig support.
	 * 			ie  include -lm in your compiler flags.
	 */
	#ifndef GDISP_NEED_ARC
		#define GDISP_NEED_ARC					GFXOFF
	#endif
	/**
	 * @brief   Are convex polygon functions needed.
	 * @details	Defaults to GFXOFF
	 * @note	Convex polygons are those that have no internal angles. That is;
	 * 			you can draw a line from any point on the polygon to any other point
	 * 			on the polygon without it going outside the polygon.
	 */
	#ifndef GDISP_NEED_CONVEX_POLYGON
		#define GDISP_NEED_CONVEX_POLYGON		GFXOFF
	#endif
	/**
	 * @brief   Are scrolling functions needed.
	 * @details	Defaults to GFXOFF
	 * @note	This function must be supported by the low level GDISP driver
	 * 			you have included in your project. If it isn't, defining this
	 * 			option will cause a compile error.
	 */
	#ifndef GDISP_NEED_SCROLL
		#define GDISP_NEED_SCROLL				GFXOFF
	#endif
	/**
	 * @brief   Is the capability to read pixels back needed.
	 * @details	Defaults to GFXOFF
	 * @note	This function must be supported by the low level GDISP driver
	 * 			you have included in your project. If it isn't, defining this
	 * 			option will cause a compile error.
	 */
	#ifndef GDISP_NEED_PIXELREAD
		#define GDISP_NEED_PIXELREAD			GFXOFF
	#endif
	/**
	 * @brief   Control some aspect of the hardware operation.
	 * @details	Defaults to GFXOFF
	 * @note	This allows control of hardware specific features such as
	 * 			screen rotation, backlight levels, contrast etc
	 */
	#ifndef GDISP_NEED_CONTROL
		#define GDISP_NEED_CONTROL				GFXOFF
	#endif
	/**
	 * @brief   Query some aspect of the hardware operation.
	 * @details	Defaults to GFXOFF
	 * @note	This allows query of hardware specific features
	 */
	#ifndef GDISP_NEED_QUERY
		#define GDISP_NEED_QUERY				GFXOFF
	#endif
	/**
	 * @brief   Is the image interface required.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_IMAGE
		#define GDISP_NEED_IMAGE				GFXOFF
	#endif
	/**
	 * @brief   Is the image interface required.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_PIXMAP
		#define GDISP_NEED_PIXMAP				GFXOFF
	#endif
/**
 * @}
 *
 * @name    GDISP Multi-Threading Options
 * @{
 */
	/**
	 * @brief   Do the drawing functions need to be thread-safe.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_MULTITHREAD
		#define GDISP_NEED_MULTITHREAD			GFXOFF
	#endif
/**
 * @}
 *
 * @name    GDISP Optional Parameters
 * @{
 */
	/**
	 * @brief	Should the startup logo be displayed
	 *
	 * @details Defaults to GFXON
	 */
	#ifndef GDISP_NEED_STARTUP_LOGO
		#define GDISP_NEED_STARTUP_LOGO 		GFXON
	#endif
	/**
	 * @brief	Define the initial background color for all displays in the system.
	 */
	#ifndef GDISP_STARTUP_COLOR
		#define GDISP_STARTUP_COLOR				GFX_BLACK
	#endif
	/**
	 * @brief	Define the default orientation for all displays in the system.
	 * @note	GDISP_NEED_CONTROL must also be set (and the hardware must support it)
	 * @note	If not specified then displays default to the native hardware orientation
	 */
	// #define GDISP_DEFAULT_ORIENTATION		gOrientationLandscape
	/**
	 * @brief   The size of pixel buffer (in pixels) used for optimization.
	 * @details	Set to zero to guarantee disabling of the buffer.
	 * @note	Depending on the driver and what operations the application
	 * 			needs, this buffer may never be allocated.
	 * @note	Setting the size to zero may cause some operations to not
	 * 			compile eg. Scrolling if there is no hardware scroll support.
	 * @note	Increasing the size will speedup certain operations
	 * 			at the expense of RAM.
	 * @note	Currently only used to support scrolling on hardware without
	 * 			scrolling support, and to increase the speed of streaming
	 * 			operations on non-streaming hardware where there is a
	 * 			hardware supported bit-blit.
	 */
	#ifndef GDISP_LINEBUF_SIZE
		#define GDISP_LINEBUF_SIZE				128
	#endif
/**
 * @}
 *
 * @name    GDISP Multiple Display Support
 * @{
 */
	/**
	 * @brief   The total number of displays using the default driver.
	 * @note	If you want to use multiple displays either set GDISP_TOTAL_DISPLAYS or GDISP_DRIVER_LIST
	 *          but not both.
	 */
	#ifndef GDISP_TOTAL_DISPLAYS
		#define GDISP_TOTAL_DISPLAYS		1
	#endif
	#if defined(__DOXYGEN__)
		/**
		 * @brief   The list of display drivers.
		 * @note	Replace this example with your own definition in your gfxconf.h file. See the gdisp_lld.c
		 *          in each driver (near the top) to get the name of the VMT for a driver.
		 * @note    The same driver can occur more than once in the list to create an extra instance of that driver.
		 * @note    If defining this you must also define GDISP_PIXELFORMAT for your application to use.
         *          Choose a value that is most common accross all your drivers for efficiency.
         * @note    If using this you may optionally define the GDISP_HARDWARE_xxx values as either GFXON or GFXOFF.
         *          Doing this causes GDISP to assume that all (GFXON) or none (GFXOFF) of the listed drivers have that
         *          capability. This can help improve drawing speed and efficiency.
		 */
		#define GDISP_DRIVER_LIST		  GDISPVMT_Win32, GDISPVMT_SSD1963
	#endif
/**
 * @}
 *
 * @name    GDISP Image Options
 * @pre		GDISP_NEED_IMAGE must be GFXON
 * @{
 */
	/**
	 * @brief   Is native image decoding required.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_IMAGE_NATIVE
		#define GDISP_NEED_IMAGE_NATIVE			GFXOFF
	#endif
	/**
	 * @brief   Is GIF image decoding required.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_IMAGE_GIF
		#define GDISP_NEED_IMAGE_GIF			GFXOFF
	#endif
	/**
	 * @brief   Is BMP image decoding required.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_IMAGE_BMP
		#define GDISP_NEED_IMAGE_BMP			GFXOFF
	#endif
	/**
	 * @brief   Is JPG image decoding required.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_IMAGE_JPG
		#define GDISP_NEED_IMAGE_JPG			GFXOFF
	#endif
	/**
	 * @brief   Is PNG image decoding required.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_IMAGE_PNG
		#define GDISP_NEED_IMAGE_PNG			GFXOFF
	#endif
	/**
	 * @brief   Is memory accounting required during image decoding.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_IMAGE_ACCOUNTING
		#define GDISP_NEED_IMAGE_ACCOUNTING		GFXOFF
	#endif
/**
 * @}
 *
 * @name    GDISP BMP Image Options
 * @pre		GDISP_NEED_IMAGE and GDISP_NEED_IMAGE_BMP must be GFXON
 * @{
 */
	/**
	 * @brief   Is BMP 1 bit per pixel (monochrome/2 color) image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_1
		#define GDISP_NEED_IMAGE_BMP_1		GFXON
	#endif
	/**
	 * @brief   Is BMP 4 bits per pixel (16 color) image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_4
		#define GDISP_NEED_IMAGE_BMP_4		GFXON
	#endif
	/**
	 * @brief   Is BMP 4 bits per pixel (16 color) with RLE compression image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_4_RLE
		#define GDISP_NEED_IMAGE_BMP_4_RLE	GFXON
	#endif
	/**
	 * @brief   Is BMP 8 bits per pixel (256 color) image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_8
		#define GDISP_NEED_IMAGE_BMP_8		GFXON
	#endif
	/**
	 * @brief   Is BMP 8 bits per pixel (256 color) with RLE compression image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_8_RLE
		#define GDISP_NEED_IMAGE_BMP_8_RLE	GFXON
	#endif
	/**
	 * @brief   Is BMP 16 bits per pixel (65536 color) image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_16
		#define GDISP_NEED_IMAGE_BMP_16		GFXON
	#endif
	/**
	 * @brief   Is BMP 24 bits per pixel (true-color) image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_24
		#define GDISP_NEED_IMAGE_BMP_24		GFXON
	#endif
	/**
	 * @brief   Is BMP 32 bits per pixel (true-color) image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_BMP_32
		#define GDISP_NEED_IMAGE_BMP_32		GFXON
	#endif
	/**
	 * @brief   The BMP blit buffer size in pixels.
	 * @details	Defaults to 32 pixels
	 * @note 	Bigger is faster but requires more RAM.
	 * @note 	This must be greater than 40 bytes and 32 pixels as we read our headers into this space as well.
	 */
	#ifndef GDISP_IMAGE_BMP_BLIT_BUFFER_SIZE
		#define GDISP_IMAGE_BMP_BLIT_BUFFER_SIZE	32
	#endif
/**
 * @}
 *
 * @name    GDISP GIF Image Options
 * @pre		GDISP_NEED_IMAGE and GDISP_NEED_IMAGE_GIF must be GFXON
 * @{
 */
	/**
	 * @brief   The GIF blit buffer size.
	 * @details	Defaults to 32
	 * @note 	Bigger is faster but requires more RAM.
	 */
	#ifndef GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE
		#define GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE	32
	#endif
/**
 * @}
 *
 * @name    GDISP PNG Image Options
 * @pre		GDISP_NEED_IMAGE and GDISP_NEED_IMAGE_PNG must be GFXON
 * @{
 */
	/**
	 * @brief   Is PNG Interlaced image decoding required.
	 * @details	Defaults to GFXOFF
	 * @note	Currently not supported due to the complex decoding and display requirements
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_INTERLACED
		#define GDISP_NEED_IMAGE_PNG_INTERLACED			GFXOFF
	#endif
	/**
	 * @brief   Is PNG image transparency processed.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_TRANSPARENCY
		#define GDISP_NEED_IMAGE_PNG_TRANSPARENCY		GFXON
	#endif
	/**
	 * @brief   Is PNG background data processed.
	 * @details	Defaults to GFXON
	 * @note	If the background is specified in the image file and this define is GFXON,
	 * 			that background color is used for transparency and alpha blending.
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_BACKGROUND
		#define GDISP_NEED_IMAGE_PNG_BACKGROUND			GFXON
	#endif
	/**
	 * @brief   What is the cliff between non-blended alpha pixels being displayed or not.
	 * @details	Range of 0 to 255
	 * @note	If GDISP_NEED_IMAGE_PNG_BACKGROUND is GFXON and the PNG file contains a
	 * 			background color then the pixel will be blended with the background color
	 * 			according to the alpha.
	 * 			If not then no blending occurs. The pixel will either be set or not.
	 * 			Any alpha value greater or equal to this number will be displayed.
	 * 			Anything less than this number is not displayed.
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_ALPHACLIFF
		#define GDISP_NEED_IMAGE_PNG_ALPHACLIFF			32
	#endif
	/**
	 * @brief   Is 1, 2 and 4 bit PNG palettized image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_PALETTE_124
		#define GDISP_NEED_IMAGE_PNG_PALETTE_124		GFXON
	#endif
	/**
	 * @brief   Is 8 bit PNG palettized image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_PALETTE_8
		#define GDISP_NEED_IMAGE_PNG_PALETTE_8			GFXON
	#endif
	/**
	 * @brief   Is 1,2 and 4 bit PNG grayscale image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_GRAYSCALE_124
		#define GDISP_NEED_IMAGE_PNG_GRAYSCALE_124		GFXON
	#endif
	/**
	 * @brief   Is 8 bit PNG grayscale image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_GRAYSCALE_8
		#define GDISP_NEED_IMAGE_PNG_GRAYSCALE_8		GFXON
	#endif
	/**
	 * @brief   Is 16 bit PNG grayscale image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_GRAYSCALE_16
		#define GDISP_NEED_IMAGE_PNG_GRAYSCALE_16		GFXON
	#endif
	/**
	 * @brief   Is 8 bit PNG grayscale with 8 bit alpha image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_GRAYALPHA_8
		#define GDISP_NEED_IMAGE_PNG_GRAYALPHA_8		GFXON
	#endif
	/**
	 * @brief   Is 16 bit PNG grayscale with 16 bit alpha image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_GRAYALPHA_16
		#define GDISP_NEED_IMAGE_PNG_GRAYALPHA_16		GFXON
	#endif
	/**
	 * @brief   Is 8/8/8 bit PNG RGB image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_RGB_8
		#define GDISP_NEED_IMAGE_PNG_RGB_8				GFXON
	#endif
	/**
	 * @brief   Is 16/16/16 bit PNG RGB image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_RGB_16
		#define GDISP_NEED_IMAGE_PNG_RGB_16				GFXON
	#endif
	/**
	 * @brief   Is 8/8/8 bit PNG RGB with 8 bit alpha image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_RGBALPHA_8
		#define GDISP_NEED_IMAGE_PNG_RGBALPHA_8			GFXON
	#endif
	/**
	 * @brief   Is 16/16/16 bit PNG RGB with 16 bit alpha image decoding required.
	 * @details	Defaults to GFXON
	 */
	#ifndef GDISP_NEED_IMAGE_PNG_RGBALPHA_16
		#define GDISP_NEED_IMAGE_PNG_RGBALPHA_16		GFXON
	#endif
	/**
	 * @brief   The PNG blit buffer size in pixels.
	 * @details	Defaults to 32
	 * @note 	Bigger is faster but requires more RAM.
	 */
	#ifndef GDISP_IMAGE_PNG_BLIT_BUFFER_SIZE
		#define GDISP_IMAGE_PNG_BLIT_BUFFER_SIZE	32
	#endif
	/**
	 * @brief   The PNG input file buffer size in bytes.
	 * @details	Defaults to 8
	 * @note 	Bigger is faster but requires more RAM.
	 * @note 	Must be >= 8
	 */
	#ifndef GDISP_IMAGE_PNG_FILE_BUFFER_SIZE
		#define GDISP_IMAGE_PNG_FILE_BUFFER_SIZE	8
	#endif
	/**
	 * @brief   The PNG inflate decompression buffer size in bytes.
	 * @details	Defaults to 32768
	 * @note 	Bigger is faster but requires more RAM.
	 * @note 	Must be >= 32768 due to the PNG 32K sliding window.
	 * @note 	More efficient code is generated if this value is a power of 2.
	 */
	#ifndef GDISP_IMAGE_PNG_Z_BUFFER_SIZE
		#define GDISP_IMAGE_PNG_Z_BUFFER_SIZE	32768
	#endif
/**
 * @}
 *
 * @name	GDISP Text Rendering Options
 * @{
 */
	/**
	 * @brief	Enable advanced word-wrapping.
	 * @details	Only has an effect with @p gdispGDrawStringBox() and @p gdispGFillStringBox()
	 * @details Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_TEXT_WORDWRAP
		#define GDISP_NEED_TEXT_WORDWRAP		GFXOFF
	#endif
	/**
	 * @brief	Adding pixels to the left and right side of the box to pad text.
	 * @details	Only has an effect with @p gdispGDrawStringBox() and @p gdispGFillStringBox()
	 * @note	Can be turned off by using gJustifyNoPad
	 * @details Defaults to 1
	 */
	#ifndef GDISP_NEED_TEXT_BOXPADLR
		#define GDISP_NEED_TEXT_BOXPADLR		1
	#endif
	/**
	 * @brief	Adding pixels to the top and bottom side of the box to pad text.
	 * @details	Only has an effect with @p gdispGDrawStringBox() and @p gdispGFillStringBox()
	 * @note	Can be turned off by using gJustifyNoPad
	 * @details Defaults to 1
	 */
	#ifndef GDISP_NEED_TEXT_BOXPADTB
		#define GDISP_NEED_TEXT_BOXPADTB		1
	#endif
	/**
	 * @brief	Enable UTF-8 support for text rendering.
	 * @details Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_UTF8
		#define GDISP_NEED_UTF8					GFXOFF
	#endif
	/**
	 * @brief	Enable kerning for font rendering (improves character placement).
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_TEXT_KERNING
		#define GDISP_NEED_TEXT_KERNING			GFXOFF
	#endif
	/**
	 * @brief	Enable antialiased font support
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GDISP_NEED_ANTIALIAS
		#define GDISP_NEED_ANTIALIAS			GFXOFF
	#endif
/**
 * @}
 *
 * @name	GDISP Pixmap Options
 * @{
 */
	#ifndef GDISP_NEED_PIXMAP_IMAGE
		#define GDISP_NEED_PIXMAP_IMAGE			GFXOFF
	#endif
/**
 * @}
 *
 * @name    GDISP Optional Low Level Driver Defines
 * @{
 */
	/**
	 * @brief   Set the screen height and width.
	 * @note	Ignored by some low level GDISP drivers, optional for others.
	 * @note	Where these values are allowed, a default is always provided be the low level driver.
	 * @note	The list of GDISP low level drivers that allow these to be set are...
	 *				WIN32, SSD1289, SSD1963, TestStub
	 */
	/* #define GDISP_SCREEN_WIDTH		nnnn */
	/* #define GDISP_SCREEN_HEIGHT		nnnn */
	/**
	 * @brief   Define which bus interface to use.
	 * @details	Only required by the SSD1963 driver.
	 * @note	This will be replaced eventually by board definition files
	 */
	// #define GDISP_USE_FSMC
	// #define GDISP_USE_GPIO
/** @} */

#endif /* _GDISP_OPTIONS_H */
/** @} */

