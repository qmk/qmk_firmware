/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_GDISP && GDISP_NEED_IMAGE && GDISP_NEED_IMAGE_GIF

#include "gdisp_image_support.h"

// We need a special error to indicate the end of file (which may not actually be an error)
#define GDISP_IMAGE_GIF_EOF		((gdispImageError)-1)
#define GDISP_IMAGE_GIF_LOOP	((gdispImageError)-2)

#define GIF_MAX_CODE_BITS		12
#define GIF_CODE_MAX			((1<<GIF_MAX_CODE_BITS)-1)	// Maximum legal code value
#define GIF_CODE_FLUSH			(GIF_CODE_MAX+1)			// Illegal code to signal flush
#define GIF_CODE_FIRST			(GIF_CODE_MAX+2)			// Illegal code to signal first
#define GIF_CODE_NONE			(GIF_CODE_MAX+3)			// Illegal code to signal empty

// Convert bits to masks for that number of bits
static const gU16 GifBitMask[] = {
		0x0000, 0x0001, 0x0003, 0x0007,
		0x000f, 0x001f, 0x003f, 0x007f,
		0x00ff, 0x01ff, 0x03ff, 0x07ff,
		0x0fff
		};

// Structure for decoding a single frame
typedef struct gifimgdecode {
	gU8		blocksz;								// The size of the block currently being processed
	gU8		maxpixel;								// The maximum allowed pixel value
	gU8		bitsperpixel;
	gU8		bitspercode;
	gU8		shiftbits;
	gU16	maxcodesz;
	gU16	stackcnt;								// The number of items on the stack
	gU16	code_clear;
	gU16	code_eof;
	gU16	code_max;
	gU16	code_last;
	gU32	shiftdata;
	gColor *	palette;
	gU8		buf[GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE];					// Buffer for decoded pixels
	gU16	prefix[1<<GIF_MAX_CODE_BITS];				// The LZW table
    gU8		suffix[1<<GIF_MAX_CODE_BITS]; 				// So we can trace the codes
    gU8 	stack[1<<GIF_MAX_CODE_BITS];				// Decoded pixels might be stacked here
} gifimgdecode;

// The data on a single frame
typedef struct gifimgframe {
	gCoord				x, y;							// position relative to full image
	gCoord				width, height;					// size of frame
	gU16			delay;							// delay after processing
	gU8				flags;							// Local flags
		#define GIFL_TRANSPARENT	0x01					// There exists a transparent color
		#define GIFL_DISPOSECLEAR	0x02					// Dispose this frame by clearing
		#define GIFL_DISPOSEREST	0x04					// Dispose this frame by restoring
		#define GIFL_INTERLACE		0x08					// Current frame is interlaced
	gU8				paltrans;						// Transparency
	gU16			palsize;						// Local palette size
	gFileSize			posstart;						// The file position of the start of the image
	gFileSize			pospal;							// The file position of the palette
	gFileSize			posimg;							// The file position of the image bits
	gFileSize			posend;							// The file position of the end of the frame
} gifimgframe;

// The data for a cache
typedef struct gifimgcache {
	gifimgframe			frame;
	gColor *			palette;						// Local palette
	gU8 *			imagebits;						// Image bits - only saved when caching
	struct gifimgcache *next;							// Next cached frame
} gifimgcache;

// The data for a dispose area
typedef struct gifimgdispose {
	gU8				flags;							// Frame flags
	gU8				paltrans;						// Transparency
	gCoord				x, y;							// position relative to full image
	gCoord				width, height;					// size of dispose area
} gifimgdispose;

typedef struct gdispImagePrivate_GIF {
	gU8			flags;						// Flags (global)
		#define GIF_LOOP			0x01			// Loop back to first frame
		#define GIF_LOOPFOREVER		0x02			// Looping is forever
	gU8			bgcolor;					// Background Color (global)
	gU16		loops;						// Remaining frame loops (if animated)
	gU16		palsize;					// Global palette size (global)
	gPixel			*palette;					// Global palette (global)
	gFileSize		frame0pos;					// The position of the first frame
	gifimgcache *	cache;						// The list of cached frames
	gifimgcache *	curcache;					// The cache of the current frame (if created)
	gifimgdecode *	decode;						// The decode data for the decode in progress
	gifimgframe		frame;
	gifimgdispose	dispose;
	gPixel			buf[GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE];	// Buffer for reading and blitting
	} gdispImagePrivate_GIF;

/**
 * Get ready for decoding a frame.
 *
 * Pre:		Frame info has been read.
 */
static gdispImageError startDecodeGif(gImage *img) {
	gdispImagePrivate_GIF *	priv;
	gifimgdecode *			decode;
	gU16				cnt;

	priv = (gdispImagePrivate_GIF *)img->priv;

	// We need the decode ram, and possibly a palette
	if (!(decode = (gifimgdecode *)gdispImageAlloc(img, sizeof(gifimgdecode)+priv->frame.palsize*sizeof(gColor))))
		return GDISP_IMAGE_ERR_NOMEMORY;

	// We currently have not read any image data block
	decode->blocksz = 0;

	// Set the palette
	if (priv->frame.palsize) {
		// Local palette
		decode->maxpixel = priv->frame.palsize-1;
		decode->palette = (gColor *)(decode+1);
		gfileSetPos(img->f, priv->frame.pospal);
		for(cnt = 0; cnt < priv->frame.palsize; cnt++) {
			if (gfileRead(img->f, &decode->buf, 3) != 3)
				goto baddatacleanup;
			decode->palette[cnt] = RGB2COLOR(decode->buf[0], decode->buf[1], decode->buf[2]);
		}
	} else if (priv->palette) {
		// Global palette
		decode->maxpixel = priv->palsize-1;
		decode->palette = priv->palette;
	} else {
		// Oops - we must have a palette
		goto baddatacleanup;
	}

	// Get the initial lzw code size and values
	gfileSetPos(img->f, priv->frame.posimg);
	if (gfileRead(img->f, &decode->bitsperpixel, 1) != 1 || decode->bitsperpixel >= GIF_MAX_CODE_BITS)
		goto baddatacleanup;
	decode->code_clear = 1 << decode->bitsperpixel;
	decode->code_eof = decode->code_clear + 1;
	decode->code_max = decode->code_clear + 2;
	decode->code_last = GIF_CODE_NONE;
	decode->bitspercode = decode->bitsperpixel+1;
	decode->maxcodesz = 1 << decode->bitspercode;
	decode->shiftbits = 0;
	decode->shiftdata = 0;
	decode->stackcnt = 0;
	for(cnt = 0; cnt <= GIF_CODE_MAX; cnt++)
		decode->prefix[cnt] = GIF_CODE_NONE;

	// All ready to go
	priv->decode = decode;
	return GDISP_IMAGE_ERR_OK;

baddatacleanup:
	gdispImageFree(img, decode, sizeof(gifimgdecode)+priv->frame.palsize*sizeof(gColor));
	return GDISP_IMAGE_ERR_BADDATA;
}

/**
 * Stop decoding a frame.
 *
 * Pre:		Frame info has been read.
 */
static void stopDecodeGif(gImage *img) {
	gdispImagePrivate_GIF *	priv;

	priv = (gdispImagePrivate_GIF *)img->priv;

	// Free the decode data
	if (priv->decode) {
		gdispImageFree(img, (void *)priv->decode, sizeof(gifimgdecode)+priv->frame.palsize*sizeof(gColor));
		priv->decode = 0;
	}
}

static gU16 getPrefixGif(gifimgdecode *decode, gU16 code) {
	gU16 i;

	for(i=0; code > decode->code_clear && i <= GIF_CODE_MAX; i++, code = decode->prefix[code]) {
		if (code > GIF_CODE_MAX)
			return GIF_CODE_NONE;
	}
    return code;
}

/**
 * Decode some pixels from a frame.
 *
 * Pre:		We are ready for decoding.
 *
 * Return:	The number of pixels decoded 0 .. GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE-1. 0 means EOF
 *
 * Note:	The resulting pixels are stored in decode->buf
 */
static gU16 getBytesGif(gImage *img) {
	gdispImagePrivate_GIF *	priv;
	gifimgdecode *			decode;
	gU16				cnt;
	gU16				code, prefix;
	gU8					bdata;

	priv = (gdispImagePrivate_GIF *)img->priv;
	decode = priv->decode;
	cnt = 0;

	// At EOF
	if (decode->code_last == decode->code_eof)
		return 0;

	while(cnt < sizeof(decode->buf)) {
		// Use the stack up first
		if (decode->stackcnt > 0) {
			decode->buf[cnt++] = decode->stack[--decode->stackcnt];
			continue;
		}

	    // Get another code - a code is made up of decode->bitspercode bits.
	    while (decode->shiftbits < decode->bitspercode) {
	    	// Get a byte - we may have to start a new data block
	    	if ((!decode->blocksz && (gfileRead(img->f, &decode->blocksz, 1) != 1 || !decode->blocksz))
	    			|| gfileRead(img->f, &bdata, 1) != 1) {
	    		// Pretend we got the EOF code - some encoders seem to just end the file
	    		decode->code_last = decode->code_eof;
	    		return cnt;
	    	}
   	    	decode->blocksz--;

	        decode->shiftdata |= ((unsigned long)bdata) << decode->shiftbits;
	        decode->shiftbits += 8;
	    }
	    code = decode->shiftdata & GifBitMask[decode->bitspercode];
	    decode->shiftdata >>= decode->bitspercode;
	    decode->shiftbits -= decode->bitspercode;
	    /**
	     * If code cannot fit into bitspercode bits we must raise its size.
	     * Note that codes above GIF_CODE_MAX are used for special signaling.
	     * If we're using GIF_MAX_CODE_BITS bits already and we're at the max code, just
	     * keep using the table as it is, don't increment decode->bitspercode.
	     */
	    if (decode->code_max < GIF_CODE_MAX + 2 && ++decode->code_max > decode->maxcodesz && decode->bitspercode < GIF_MAX_CODE_BITS) {
	        decode->maxcodesz <<= 1;
	        decode->bitspercode++;
	    }

		// EOF - the appropriate way to stop decoding
		if (code == decode->code_eof) {
			// Skip to the end of the data blocks
			do {
				gfileSetPos(img->f, gfileGetPos(img->f)+decode->blocksz);
			} while (gfileRead(img->f, &decode->blocksz, 1) == 1 && decode->blocksz);

			// Mark the end
			decode->code_last = decode->code_eof;
			break;
		}

		if (code == decode->code_clear) {
			// Start again
			for(prefix = 0; prefix <= GIF_CODE_MAX; prefix++)
				decode->prefix[prefix] = GIF_CODE_NONE;
			decode->code_max = decode->code_eof + 1;
			decode->bitspercode = decode->bitsperpixel + 1;
			decode->maxcodesz = 1 << decode->bitspercode;
			decode->code_last = GIF_CODE_NONE;
			continue;
		}

		if (code < decode->code_clear) {
			// Simple unencoded pixel - add it
			decode->buf[cnt++] = code;

		} else {
			/**
			 * Its a LZW code - trace the linked list until the prefix is a
			 * valid pixel while pushing the suffix pixels on the stack.
			 * If done, pop the stack in reverse order adding the pixels
			 */
			if (decode->prefix[code] != GIF_CODE_NONE)
				prefix = code;

			/**
			 * Only allowed if the code equals the partial code.
			 * In that case code = XXXCode, CrntCode or the
			 * prefix code is last code and the suffix char is
			 * exactly the prefix of last code!
			 */
			else if (code == decode->code_max - 2 && decode->stackcnt < sizeof(decode->stack)) {
				prefix = decode->code_last;
				decode->suffix[decode->code_max - 2] = decode->stack[decode->stackcnt++] = getPrefixGif(decode, decode->code_last);
			} else
				return 0;

			/**
			 * If the image is OK we should not get a GIF_CODE_NONE while tracing.
			 * To prevent looping with a bad image we use StackPtr as loop counter
			 * and stop before overflowing Stack[].
			 */
			while (decode->stackcnt < sizeof(decode->stack) && prefix > decode->code_clear && prefix <= GIF_CODE_MAX) {
				decode->stack[decode->stackcnt++] = decode->suffix[prefix];
				prefix = decode->prefix[prefix];
			}
			if (decode->stackcnt >= sizeof(decode->stack) || prefix > GIF_CODE_MAX)
				return 0;

			/* Push the last character on stack: */
			decode->stack[decode->stackcnt++] = prefix;
		}

		if (decode->code_last != GIF_CODE_NONE && decode->prefix[decode->code_max - 2] == GIF_CODE_NONE) {
			decode->prefix[decode->code_max - 2] = decode->code_last;

			/* Only allowed if code is exactly the running code:
			* In that case code = XXXCode, CrntCode or the
			* prefix code is last code and the suffix char is
			* exactly the prefix of last code! */
			decode->suffix[decode->code_max - 2] = getPrefixGif(decode, code == decode->code_max - 2 ? decode->code_last : code);
		}
		decode->code_last = code;
	}
	return cnt;
}

/**
 * Read the info on a frame.
 *
 * Pre:		The file position is at the start of the frame.
 */
static gdispImageError initFrameGif(gImage *img) {
	gdispImagePrivate_GIF *	priv;
	gifimgcache *			cache;
	gU8					blocktype;
	gU8					blocksz;

	priv = (gdispImagePrivate_GIF *)img->priv;

	// Save the dispose info from the existing frame
	priv->dispose.flags = priv->frame.flags;
	priv->dispose.paltrans = priv->frame.paltrans;
	priv->dispose.x = priv->frame.x;
	priv->dispose.y = priv->frame.y;
	priv->dispose.width = priv->frame.width;
	priv->dispose.height = priv->frame.height;

	// Check for a cached version of this image
	for(cache=priv->cache; cache && cache->frame.posstart <= gfileGetPos(img->f); cache=cache->next) {
		if (cache->frame.posstart == gfileGetPos(img->f)) {
			priv->frame = cache->frame;
			priv->curcache = cache;
			return GDISP_IMAGE_ERR_OK;
		}
	}

	// Get ready for a new image
	priv->curcache = 0;
	priv->frame.posstart = gfileGetPos(img->f);
	priv->frame.flags = 0;
	priv->frame.delay = 0;
	priv->frame.palsize = 0;

	// Process blocks until we reach the image descriptor
	while(1) {
		if (gfileRead(img->f, &blocktype, 1) != 1)
			return GDISP_IMAGE_ERR_BADDATA;

		switch(blocktype) {
		case 0x2C:			//',' - IMAGE_DESC_RECORD_TYPE;
			// Read the Image Descriptor
			if (gfileRead(img->f, priv->buf, 9) != 9)
				return GDISP_IMAGE_ERR_BADDATA;
			priv->frame.x = gdispImageGetAlignedLE16(priv->buf, 0);
			priv->frame.y = gdispImageGetAlignedLE16(priv->buf, 2);
			priv->frame.width = gdispImageGetAlignedLE16(priv->buf, 4);
			priv->frame.height = gdispImageGetAlignedLE16(priv->buf, 6);
			if (((gU8 *)priv->buf)[8] & 0x80)				// Local color table?
				priv->frame.palsize = 2 << (((gU8 *)priv->buf)[8] & 0x07);
			if (((gU8 *)priv->buf)[8] & 0x40)				// Interlaced?
				priv->frame.flags |= GIFL_INTERLACE;

			// We are ready to go for the actual palette read and image decode
			priv->frame.pospal = gfileGetPos(img->f);
			priv->frame.posimg = priv->frame.pospal+priv->frame.palsize*3;
			priv->frame.posend = 0;

			// Mark this as an animated image if more than 1 frame.
			if (priv->frame.posstart != priv->frame0pos)
				img->flags |= GDISP_IMAGE_FLG_ANIMATED;
			return GDISP_IMAGE_ERR_OK;

		case 0x21:			//'!' - EXTENSION_RECORD_TYPE;
			// Read the extension type
			if (gfileRead(img->f, &blocktype, 1) != 1)
				return GDISP_IMAGE_ERR_BADDATA;

			switch(blocktype) {
			case 0xF9:			// EXTENSION - Graphics Control Block
				// Read the GCB
				if (gfileRead(img->f, priv->buf, 6) != 6)
					return GDISP_IMAGE_ERR_BADDATA;
				// Check we have read a 4 byte data block and a data block terminator (0)
				if (((gU8 *)priv->buf)[0] != 4 || ((gU8 *)priv->buf)[5] != 0)
					return GDISP_IMAGE_ERR_BADDATA;
				// Process the flags
				switch(((gU8 *)priv->buf)[1] & 0x1C) {
				case 0x00: case 0x04:												break;		// Dispose = do nothing
				case 0x08:				priv->frame.flags |= GIFL_DISPOSECLEAR;		break;		// Dispose = clear
				case 0x0C: case 0x10:	priv->frame.flags |= GIFL_DISPOSEREST;		break;		// Dispose = restore. Value 0x10 is a hack for bad encoders
				default:				return GDISP_IMAGE_ERR_UNSUPPORTED;
				}
				if (((gU8 *)priv->buf)[1] & 0x01) {
					priv->frame.flags |= GIFL_TRANSPARENT;
					img->flags |= GDISP_IMAGE_FLG_TRANSPARENT;		// We set this but never clear it
				}
				if (((gU8 *)priv->buf)[1] & 0x02)				// Wait for user input?
					img->flags |= GDISP_IMAGE_FLG_MULTIPAGE;
				else
					img->flags &= ~GDISP_IMAGE_FLG_MULTIPAGE;
				// Process frame delay and the transparent color (if any)
				priv->frame.delay = gdispImageGetAlignedLE16(priv->buf, 2);
				priv->frame.paltrans = ((gU8 *)priv->buf)[4];
				break;

			case 0xFF:			// EXTENSION - Application
				// We only handle this for the special Netscape loop counter for animation
				if (priv->flags & GIF_LOOP)
					goto skipdatablocks;
				// Read the Application header
				if (gfileRead(img->f, priv->buf, 16) != 16)
					return GDISP_IMAGE_ERR_BADDATA;
				// Check we have read a 11 byte data block
				if (((gU8 *)priv->buf)[0] != 11 && ((gU8 *)priv->buf)[12] != 3)
					return GDISP_IMAGE_ERR_BADDATA;
				// Check the vendor
				if (((gU8 *)priv->buf)[1] == 'N' && ((gU8 *)priv->buf)[2] == 'E' && ((gU8 *)priv->buf)[3] == 'T'
						&& ((gU8 *)priv->buf)[4] == 'S' && ((gU8 *)priv->buf)[5] == 'C' && ((gU8 *)priv->buf)[6] == 'A'
						&& ((gU8 *)priv->buf)[7] == 'P' && ((gU8 *)priv->buf)[8] == 'E' && ((gU8 *)priv->buf)[9] == '2'
						&& ((gU8 *)priv->buf)[10] == '.' && ((gU8 *)priv->buf)[11] == '0') {
					if (((gU8 *)priv->buf)[13] == 1) {
						priv->loops = gdispImageGetAlignedLE16(priv->buf, 14);
						priv->flags |= GIF_LOOP;
						if (!priv->loops)
							priv->flags |= GIF_LOOPFOREVER;
					}
				}
				goto skipdatablocks;

			case 0x01:			// EXTENSION - Plain Text (Graphics Rendering)
			case 0xFE:			// EXTENSION - Comment
			default:
				// 0x00-0x7F (0-127) are the Graphic Rendering blocks
				if (blocktype <= 0x7F)
					return GDISP_IMAGE_ERR_UNSUPPORTED;
				// 0x80-0xF9 (128-249) are the Control blocks
				// 0xFA-0xFF (250-255) are the Special Purpose blocks
				// We don't understand this extension - just skip it by skipping data blocks
			skipdatablocks:
				while(1) {
					if (gfileRead(img->f, &blocksz, 1) != 1)
						return GDISP_IMAGE_ERR_BADDATA;
					if (!blocksz)
						break;
					gfileSetPos(img->f, gfileGetPos(img->f) + blocksz);
				}
				break;
			}
			break;

		case 0x3B:			//';' - TERMINATE_RECORD_TYPE;
			// Are we an looping animation
			if (!(priv->flags & GIF_LOOP))
				return GDISP_IMAGE_GIF_EOF;
			if (!(priv->flags & GIF_LOOPFOREVER)) {
				if (!priv->loops)
					return GDISP_IMAGE_GIF_EOF;
				priv->loops--;
			}

			// Seek back to frame0
			gfileSetPos(img->f, priv->frame0pos);
			return GDISP_IMAGE_GIF_LOOP;

		default:			// UNDEFINED_RECORD_TYPE;
			return GDISP_IMAGE_ERR_UNSUPPORTED;
		}
	}
}

void gdispImageClose_GIF(gImage *img) {
	gdispImagePrivate_GIF *	priv;
	gifimgcache *			cache;
	gifimgcache *			ncache;

	priv = (gdispImagePrivate_GIF *)img->priv;
	if (priv) {
		// Free any stored frames
		cache = priv->cache;
		while(cache) {
			ncache = cache->next;
			gdispImageFree(img, (void *)cache, sizeof(gifimgcache)+cache->frame.width*cache->frame.height+cache->frame.palsize*sizeof(gColor));
			cache = ncache;
		}
		if (priv->palette)
			gdispImageFree(img, (void *)priv->palette, priv->palsize*sizeof(gColor));
		gdispImageFree(img, (void *)priv, sizeof(gdispImagePrivate_GIF));
		img->priv = 0;
	}
}

gdispImageError gdispImageOpen_GIF(gImage *img) {
	gdispImagePrivate_GIF *priv;
	gU8		hdr[6];
	gU16	aword;

	/* Read the file identifier */
	if (gfileRead(img->f, hdr, 6) != 6)
		return GDISP_IMAGE_ERR_BADFORMAT;		// It can't be us

	/* Process the GIFFILEHEADER structure */

	if (hdr[0] != 'G' || hdr[1] != 'I' || hdr[2] != 'F'
			|| hdr[3] != '8' || (hdr[4] != '7' && hdr[4] != '9') || hdr[5] != 'a')
		return GDISP_IMAGE_ERR_BADFORMAT;		// It can't be us

	/* We know we are a GIF format image */
	img->flags = 0;

	/* Allocate our private area */
	if (!(img->priv = gdispImageAlloc(img, sizeof(gdispImagePrivate_GIF))))
		return GDISP_IMAGE_ERR_NOMEMORY;

	/* Initialise the essential bits in the private area */
	priv = (gdispImagePrivate_GIF *)img->priv;
	priv->flags = 0;
	priv->palsize = 0;
	priv->palette = 0;
	priv->frame.flags = 0;
	priv->cache = 0;
	priv->curcache = 0;
	priv->decode = 0;

	/* Process the Screen Descriptor structure */

	// Read the screen descriptor
	if (gfileRead(img->f, priv->buf, 7) != 7)
		goto baddatacleanup;
	// Get the width
	img->width = gdispImageGetAlignedLE16(priv->buf, 0);
	// Get the height
	img->height = gdispImageGetAlignedLE16(priv->buf, 2);
	if (((gU8 *)priv->buf)[4] & 0x80) {
		// Global color table
		priv->palsize = 2 << (((gU8 *)priv->buf)[4] & 0x07);
		// Allocate the global palette
		if (!(priv->palette = (gColor *)gdispImageAlloc(img, priv->palsize*sizeof(gColor))))
			goto nomemcleanup;
		// Read the global palette
		for(aword = 0; aword < priv->palsize; aword++) {
			if (gfileRead(img->f, &priv->buf, 3) != 3)
				goto baddatacleanup;
			priv->palette[aword] = RGB2COLOR(((gU8 *)priv->buf)[0], ((gU8 *)priv->buf)[1], ((gU8 *)priv->buf)[2]);
		}
	}
	priv->bgcolor = ((gU8 *)priv->buf)[5];

	// Save the fram0pos
	priv->frame0pos = gfileGetPos(img->f);

	// Read the first frame descriptor
	switch(initFrameGif(img)) {
	case GDISP_IMAGE_ERR_OK:					// Everything OK
		img->type = GDISP_IMAGE_TYPE_GIF;
		return GDISP_IMAGE_ERR_OK;
	case GDISP_IMAGE_ERR_UNSUPPORTED:			// Unsupported
		gdispImageClose_GIF(img);					// Clean up the private data area
		return GDISP_IMAGE_ERR_UNSUPPORTED;
	case GDISP_IMAGE_ERR_NOMEMORY:				// Out of Memory
	nomemcleanup:
		gdispImageClose_GIF(img);					// Clean up the private data area
		return GDISP_IMAGE_ERR_NOMEMORY;
	case GDISP_IMAGE_GIF_EOF:						// We should have a frame but we don't seem to
	case GDISP_IMAGE_GIF_LOOP:						// We should have a frame but we don't seem to
	case GDISP_IMAGE_ERR_BADDATA:				// Oops - something wrong with the data
	default:
	baddatacleanup:
		gdispImageClose_GIF(img);					// Clean up the private data area
		return GDISP_IMAGE_ERR_BADDATA;
	}
}

gdispImageError gdispImageCache_GIF(gImage *img) {
	gdispImagePrivate_GIF *	priv;
	gifimgcache *			cache;
	gifimgdecode *			decode;
	gU8 *				p;
	gU8 *				q;
	gCoord					mx, my;
	gU16				cnt;

	/* If we are already cached - just return OK */
	priv = (gdispImagePrivate_GIF *)img->priv;
	if (priv->curcache)
		return GDISP_IMAGE_ERR_OK;

	/* We need to allocate the frame, the palette and bits for the image */
	if (!(cache = (gifimgcache *)gdispImageAlloc(img, sizeof(gifimgcache) + priv->frame.palsize*sizeof(gColor) + priv->frame.width*priv->frame.height)))
		return GDISP_IMAGE_ERR_NOMEMORY;

	/* Initialise the cache */
	decode = 0;
	cache->frame = priv->frame;
	cache->imagebits = (gU8 *)(cache+1) + cache->frame.palsize*sizeof(gColor);
	cache->next = 0;

	/* Start the decode */
	switch(startDecodeGif(img)) {
	case GDISP_IMAGE_ERR_OK:			break;
	case GDISP_IMAGE_ERR_NOMEMORY:		goto nomemcleanup;
	case GDISP_IMAGE_ERR_BADDATA:
	default:							goto baddatacleanup;
	}
	decode = priv->decode;

	// Save the palette
	if (cache->frame.palsize) {
		cache->palette = (gColor *)(cache+1);

		/* Copy the local palette into the cache */
		for(cnt = 0; cnt < cache->frame.palsize; cnt++)
			cache->palette[cnt] = decode->palette[cnt];
	} else
		cache->palette = priv->palette;

	// Check for interlacing
	cnt = 0;
	q = 0;
	if (cache->frame.flags & GIFL_INTERLACE) {
		// Every 8th row starting at row 0
		for(p=cache->imagebits, my=0; my < cache->frame.height; my+=8, p += cache->frame.width*7) {
			for(mx=0; mx < cache->frame.width; mx++) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						while(cnt < sizeof(decode->buf))
							decode->buf[cnt++] = (cache->frame.flags & GIFL_TRANSPARENT) ? cache->frame.paltrans : 0;
					}
					q = decode->buf;
				}
				*p++ = *q++;
				cnt--;
			}
		}
		// Every 8th row starting at row 4
		for(p=cache->imagebits+cache->frame.width*4, my=4; my < cache->frame.height; my+=8, p += cache->frame.width*7) {
			for(mx=0; mx < cache->frame.width; mx++) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						while(cnt < sizeof(decode->buf))
							decode->buf[cnt++] = (cache->frame.flags & GIFL_TRANSPARENT) ? cache->frame.paltrans : 0;
					}
					q = decode->buf;
				}
				*p++ = *q++;
				cnt--;
			}
		}
		// Every 4th row starting at row 2
		for(p=cache->imagebits+cache->frame.width*2, my=2; my < cache->frame.height; my+=4, p += cache->frame.width*3) {
			for(mx=0; mx < cache->frame.width; mx++) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						while(cnt < sizeof(decode->buf))
							decode->buf[cnt++] = (cache->frame.flags & GIFL_TRANSPARENT) ? cache->frame.paltrans : 0;
					}
					q = decode->buf;
				}
				*p++ = *q++;
				cnt--;
			}
		}
		// Every 2nd row starting at row 1
		for(p=cache->imagebits+cache->frame.width, my=1; my < cache->frame.height; my+=2, p += cache->frame.width) {
			for(mx=0; mx < cache->frame.width; mx++) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						while(cnt < sizeof(decode->buf))
							decode->buf[cnt++] = (cache->frame.flags & GIFL_TRANSPARENT) ? cache->frame.paltrans : 0;
					}
					q = decode->buf;
				}
				*p++ = *q++;
				cnt--;
			}
		}
	} else {
		// Every row in sequence
		p=cache->imagebits;
		for(my=0; my < cache->frame.height; my++) {
			for(mx=0; mx < cache->frame.width; mx++) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						while(cnt < sizeof(decode->buf))
							decode->buf[cnt++] = (cache->frame.flags & GIFL_TRANSPARENT) ? cache->frame.paltrans : 0;
					}
					q = decode->buf;
				}
				*p++ = *q++;
				cnt--;
			}
		}
	}
	// We could be pedantic here but extra bytes won't hurt us
	while(getBytesGif(img));
	priv->frame.posend = cache->frame.posend = gfileGetPos(img->f);

	// Save everything
	priv->curcache = cache;
	if (!priv->cache)
		priv->cache = cache;
	else if (priv->cache->frame.posstart > cache->frame.posstart) {
		cache->next = priv->cache;
		priv->cache = cache;
	} else {
		gifimgcache	*pc;

		for(pc = priv->cache; pc; pc = pc->next) {
			if (!pc->next || pc->next->frame.posstart > cache->frame.posstart) {
				cache->next = pc->next;
				pc->next = cache;
				break;
			}
		}
	}
	stopDecodeGif(img);
	return GDISP_IMAGE_ERR_OK;

nomemcleanup:
	stopDecodeGif(img);
	gdispImageFree(img, cache, sizeof(gifimgcache) + priv->frame.palsize*sizeof(gColor) + priv->frame.width*priv->frame.height);
	return GDISP_IMAGE_ERR_NOMEMORY;

baddatacleanup:
	stopDecodeGif(img);
	gdispImageFree(img, cache, sizeof(gifimgcache) + priv->frame.palsize*sizeof(gColor) + priv->frame.width*priv->frame.height);
	return GDISP_IMAGE_ERR_BADDATA;
}

gdispImageError gdispGImageDraw_GIF(GDisplay *g, gImage *img, gCoord x, gCoord y, gCoord cx, gCoord cy, gCoord sx, gCoord sy) {
	gdispImagePrivate_GIF *	priv;
	gifimgdecode *			decode;
	gU8 *				q = 0;
	gCoord					mx, my, fx, fy;
	gU16				cnt, gcnt;
	gU8					col;

	priv = (gdispImagePrivate_GIF *)img->priv;

	/* Handle previous frame disposing */
	if (priv->dispose.flags & (GIFL_DISPOSECLEAR|GIFL_DISPOSEREST)) {
		// Clip to the disposal area - clip area = mx,my -> fx, fy (sx,sy,cx,cy are unchanged)
		mx = priv->dispose.x;
		my = priv->dispose.y;
		fx = priv->dispose.x+priv->dispose.width;
		fy = priv->dispose.y+priv->dispose.height;
		if (sx > mx) mx = sx;
		if (sy > my) my = sy;
		if (sx+cx <= fx) fx = sx+cx;
		if (sy+cy <= fy) fy = sy+cy;
		if (fx > mx && fy > my) {
			// We only support clearing (not restoring). The specification says that we are allowed to do this.
			// Calculate the bgcolor
			// The spec says to restore the backgound color (priv->bgcolor) but in practice if there is transparency
			//	image decoders tend to assume that a restore to the transparent color is required instead
			if (((priv->dispose.flags & GIFL_TRANSPARENT) /*&& priv->dispose.paltrans == priv->bgcolor*/) || priv->bgcolor >= priv->palsize)
				gdispGFillArea(g, x+mx-sx, y+my-sy, fx-mx, fy-my, img->bgcolor);
			else
				gdispGFillArea(g, x+mx-sx, y+my-sy, fx-mx, fy-my, priv->palette[priv->bgcolor]);
		}
	}

	/* Clip to just this frame - clip area = sx,sy -> fx, fy */
	fx = priv->frame.x+priv->frame.width;
	fy = priv->frame.y+priv->frame.height;
	if (sx >= fx || sy >= fy || sx+cx < priv->frame.x || sy+cy < priv->frame.y) return GDISP_IMAGE_ERR_OK;
	if (sx < priv->frame.x) { mx = priv->frame.x - sx; x += mx; cx -= mx; sx = priv->frame.x; }
	if (sy < priv->frame.y) { my = priv->frame.y - sy; y += my; cy -= my; sy = priv->frame.y; }
	if (sx+cx > fx) cx = fx-sx;
	if (sy+cy > fy) cy = fy-sy;

	// Make sx, sy relative to this frame so we are not adding priv->frame.x & priv->frame.y each time
	sx -= priv->frame.x; sy -= priv->frame.y;
	fx = sx + cx;
	fy = sy + cy;

	/* Draw from the image cache - if it exists */
	if (priv->curcache) {
		gifimgcache *	cache;

		cache = priv->curcache;
		q = cache->imagebits+priv->frame.width*sy+sx;

		for(my=sy; my < fy; my++, q += priv->frame.width - cx) {
			for(gcnt=0, mx=sx, cnt=0; mx < fx; mx++) {
				col = *q++;
				if ((priv->frame.flags & GIFL_TRANSPARENT) && col == priv->frame.paltrans) {
					// We have a transparent pixel - dump the buffer to the display
					switch(gcnt) {
					case 0:																							break;
					case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
					default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
					}
					continue;
				}
				priv->buf[gcnt++] = cache->palette[col];
				if (gcnt >= GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE) {
					// We have run out of buffer - dump it to the display
					gdispGBlitArea(g, x+mx-sx-gcnt+1, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);
					gcnt = 0;
				}
			}
			// We have finished the line - dump the buffer to the display
			switch(gcnt) {
			case 0:																					break;
			case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]);					break;
			default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);	break;
			}
		}

		return GDISP_IMAGE_ERR_OK;
	}

	/* Start the decode */
	switch(startDecodeGif(img)) {
	case GDISP_IMAGE_ERR_OK:			break;
	case GDISP_IMAGE_ERR_NOMEMORY:		return GDISP_IMAGE_ERR_NOMEMORY;
	case GDISP_IMAGE_ERR_BADDATA:
	default:							return GDISP_IMAGE_ERR_BADDATA;
	}
	decode = priv->decode;

	// Check for interlacing
	cnt = 0;
	if (priv->frame.flags & GIFL_INTERLACE) {
		// Every 8th row starting at row 0
		for(my=0; my < priv->frame.height; my+=8) {
			for(gcnt=0, mx=0; mx < priv->frame.width; mx++, q++, cnt--) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						mx++;
						break;
					}
					q = decode->buf;
				}
				if (my >= sy && my < fy && mx >= sx && mx < fx) {
					col = *q;
					if ((priv->frame.flags & GIFL_TRANSPARENT) && col == priv->frame.paltrans) {
						// We have a transparent pixel - dump the buffer to the display
						switch(gcnt) {
						case 0:																							break;
						case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
						default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
						}
						continue;
					}
					priv->buf[gcnt++] = decode->palette[col];
					if (gcnt >= GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE) {
						// We have run out of buffer - dump it to the display
						gdispGBlitArea(g, x+mx-sx-gcnt+1, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);
						gcnt = 0;
					}
					continue;
				}
				// We have finished the visible area - dump the buffer to the display
				switch(gcnt) {
				case 0:																							break;
				case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
				default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
				}
			}
			// We have finished the line - dump the buffer to the display
			switch(gcnt) {
			case 0:																					break;
			case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]);					break;
			default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);	break;
			}
		}
		// Every 8th row starting at row 4
		for(my=4; my < priv->frame.height; my+=8) {
			for(gcnt=0, mx=0; mx < priv->frame.width; mx++, q++, cnt--) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						mx++;
						break;
					}
					q = decode->buf;
				}
				if (my >= sy && my < fy && mx >= sx && mx < fx) {
					col = *q;
					if ((priv->frame.flags & GIFL_TRANSPARENT) && col == priv->frame.paltrans) {
						// We have a transparent pixel - dump the buffer to the display
						switch(gcnt) {
						case 0:																							break;
						case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
						default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
						}
						continue;
					}
					priv->buf[gcnt++] = decode->palette[col];
					if (gcnt >= GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE) {
						// We have run out of buffer - dump it to the display
						gdispGBlitArea(g, x+mx-sx-gcnt+1, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);
						gcnt = 0;
					}
					continue;
				}
				// We have finished the visible area - dump the buffer to the display
				switch(gcnt) {
				case 0:																							break;
				case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
				default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
				}
			}
			// We have finished the line - dump the buffer to the display
			switch(gcnt) {
			case 0:																					break;
			case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]);					break;
			default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);	break;
			}
		}
		// Every 4th row starting at row 2
		for(my=2; my < priv->frame.height; my+=4) {
			for(gcnt=0, mx=0; mx < priv->frame.width; mx++, q++, cnt--) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						mx++;
						break;
					}
					q = decode->buf;
				}
				if (my >= sy && my < fy && mx >= sx && mx < fx) {
					col = *q;
					if ((priv->frame.flags & GIFL_TRANSPARENT) && col == priv->frame.paltrans) {
						// We have a transparent pixel - dump the buffer to the display
						switch(gcnt) {
						case 0:																							break;
						case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
						default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
						}
						continue;
					}
					priv->buf[gcnt++] = decode->palette[col];
					if (gcnt >= GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE) {
						// We have run out of buffer - dump it to the display
						gdispGBlitArea(g, x+mx-sx-gcnt+1, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);
						gcnt = 0;
					}
					continue;
				}
				// We have finished the visible area - dump the buffer to the display
				switch(gcnt) {
				case 0:																							break;
				case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
				default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
				}
			}
			// We have finished the line - dump the buffer to the display
			switch(gcnt) {
			case 0:																					break;
			case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]);					break;
			default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);	break;
			}
		}
		// Every 2nd row starting at row 1
		for(my=1; my < priv->frame.height; my+=2) {
			for(gcnt=0, mx=0; mx < priv->frame.width; mx++, q++, cnt--) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						mx++;
						break;
					}
					q = decode->buf;
				}
				if (my >= sy && my < fy && mx >= sx && mx < fx) {
					col = *q;
					if ((priv->frame.flags & GIFL_TRANSPARENT) && col == priv->frame.paltrans) {
						// We have a transparent pixel - dump the buffer to the display
						switch(gcnt) {
						case 0:																							break;
						case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
						default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
						}
						continue;
					}
					priv->buf[gcnt++] = decode->palette[col];
					if (gcnt >= GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE) {
						// We have run out of buffer - dump it to the display
						gdispGBlitArea(g, x+mx-sx-gcnt+1, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);
						gcnt = 0;
					}
					continue;
				}
				// We have finished the visible area - dump the buffer to the display
				switch(gcnt) {
				case 0:																							break;
				case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
				default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
				}
			}
			// We have finished the line - dump the buffer to the display
			switch(gcnt) {
			case 0:																					break;
			case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]);					break;
			default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);	break;
			}
		}
	} else {
		// Every row in sequence
		for(my=0; my < priv->frame.height; my++) {
			for(gcnt=0, mx=0; mx < priv->frame.width; mx++, q++, cnt--) {
				if (!cnt) {
					if (!(cnt = getBytesGif(img))) {
						// Sometimes the image EOF is a bit early - treat the rest as transparent
						if (decode->code_last != decode->code_eof)
							goto baddatacleanup;
						mx++;
						break;
					}
					q = decode->buf;
				}
				if (my >= sy && my < fy && mx >= sx && mx < fx) {
					col = *q;
					if ((priv->frame.flags & GIFL_TRANSPARENT) && col == priv->frame.paltrans) {
						// We have a transparent pixel - dump the buffer to the display
						switch(gcnt) {
						case 0:																							break;
						case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
						default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
						}
						continue;
					}
					priv->buf[gcnt++] = decode->palette[col];
					if (gcnt >= GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE) {
						// We have run out of buffer - dump it to the display
						gdispGBlitArea(g, x+mx-sx-gcnt+1, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);
						gcnt = 0;
					}
					continue;
				}
				// We have finished the visible area - dump the buffer to the display
				switch(gcnt) {
				case 0:																							break;
				case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]); gcnt = 0;					break;
				default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf); gcnt = 0;	break;
				}
			}
			// We have finished the line - dump the buffer to the display
			switch(gcnt) {
			case 0:																					break;
			case 1:		gdispGDrawPixel(g, x+mx-sx-gcnt, y+my-sy, priv->buf[0]);					break;
			default:	gdispGBlitArea(g, x+mx-sx-gcnt, y+my-sy, gcnt, 1, 0, 0, gcnt, priv->buf);	break;
			}
		}
	}
	// We could be pedantic here but extra bytes won't hurt us
	while (getBytesGif(img));
	priv->frame.posend = gfileGetPos(img->f);

	stopDecodeGif(img);
	return GDISP_IMAGE_ERR_OK;

baddatacleanup:
	stopDecodeGif(img);
	return GDISP_IMAGE_ERR_BADDATA;
}

gDelay gdispImageNext_GIF(gImage *img) {
	gdispImagePrivate_GIF *	priv;
	gDelay				delay;
	gU8					blocksz;

	priv = (gdispImagePrivate_GIF *)img->priv;

	// Save the delay and convert to millisecs
	delay = (gDelay)priv->frame.delay * 10;

	// We need to get to the end of this frame
	if (!priv->frame.posend) {
		// We don't know where the end of the frame is yet - find it!
		gfileSetPos(img->f, priv->frame.posimg+1);				// Skip the code size byte too
		while(1) {
			if (gfileRead(img->f, &blocksz, 1) != 1)
				return gDelayForever;
			if (!blocksz)
				break;
			gfileSetPos(img->f, gfileGetPos(img->f) + blocksz);
		}
		priv->frame.posend = gfileGetPos(img->f);
	}

	// Seek to the end of this frame
	gfileSetPos(img->f, priv->frame.posend);

	// Read the next frame descriptor
	for(blocksz=0; blocksz < 2; blocksz++) {		// 2 loops max to prevent cycling forever with a bad file
		switch(initFrameGif(img)) {
		case GDISP_IMAGE_ERR_OK:					// Everything OK
			return delay;
		case GDISP_IMAGE_GIF_LOOP:						// Back to the beginning
			break;
		case GDISP_IMAGE_GIF_EOF:						// The real End-Of-File
		case GDISP_IMAGE_ERR_BADDATA:				// Oops - something wrong with the data
		case GDISP_IMAGE_ERR_NOMEMORY:				// Out of Memory
		case GDISP_IMAGE_ERR_UNSUPPORTED:			// Unsupported
		default:
			return gDelayForever;
		}
	}
	return gDelayForever;
}

#endif /* GFX_USE_GDISP && GDISP_NEED_IMAGE && GDISP_NEED_IMAGE_GIF */
