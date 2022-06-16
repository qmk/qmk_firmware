/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

// Safety first!
#if (!defined(__STDC__) || !__STDC__) && !defined(__cplusplus) && !defined(_MSC_VER)
	#error "K&R C Compilers are not supported. Try turning on ANSI C compliance or at least defining macro __STDC__=1"
#endif

// This guarantees definition (even in C89) of:
//	offsetof(s, m)		- required and compiler dependant
//	size_t				- we try not to use this in uGFX as it may be 64 bit
//	NULL				- globally useful
//	ptrdiff_t			- globally useful

#include <stddef.h>

#if (defined(__STDC__) && __STDC__ && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__SUNPRO_C) && __SUNPRO_C >= 0x570) || (defined(_MSC_VER) && _MSC_VER >= 1600) || (defined (__WATCOMC__) && (defined (_STDINT_H_INCLUDED) || __WATCOMC__ >= 1250)) || (defined(__GNUC__) && (__GNUC__ > 3 || defined(_STDINT_H) || defined(_STDINT_H_) || defined (__UINT_FAST64_TYPE__)) )
	#include <stdint.h>
	typedef int_least8_t			gI8;
	typedef uint_least8_t			gU8;
	typedef int_least16_t			gI16;
	typedef uint_least16_t			gU16;
	typedef int_least32_t			gI32;
	typedef uint_least32_t			gU32;

	#define GI8_C(v) 	 			INT8_C(v)
	#define GU8_C(v)  				UINT8_C(v)
	#define GI16_C(v) 				INT16_C(v)
	#define GU16_C(v)  				UINT16_C(v)
	#define GI32_C(v) 				INT32_C(v)
	#define GU32_C(v)  				UINT32_C(v)

	#ifdef INT64_C
		typedef int_least64_t		gI64;
		typedef uint_least64_t		gU64;
		#define GI64_C(v) 			INT64_C(v)
		#define GU64_C(v)  			UINT64_C(v)
		#define GFX_TYPE_64			GFXON
	#else
		#define GFX_TYPE_64			GFXOFF
	#endif

#elif defined(_MSC_VER)
	#if (_MSC_VER < 1300)
		typedef signed   char		gI8;
		typedef unsigned char		gU8;
		typedef signed   short		gI16;
		typedef unsigned short		gU16;
		typedef signed   int		gI32;
		typedef unsigned int		gU32;
	#else
		typedef signed   __int8		gI8;
		typedef unsigned __int8		gU8;
		typedef signed   __int16	gI16;
		typedef unsigned __int16	gU16;
		typedef signed   __int32	gI32;
		typedef unsigned __int32	gU32;
	#endif
	typedef signed   __int64		gI64;
	typedef unsigned __int64		gU64;

	#define GI8_C(v)  				v ## i8
	#define GU8_C(v)  				v ## ui8
	#define GI16_C(v) 				v ## i16
	#define GU16_C(v) 				v ## ui16
	#define GI32_C(v) 				v ## i32
	#define GU32_C(v) 				v ## ui32
	#define GI64_C(v) 				v ## i64
	#define GU64_C(v) 				v ## ui64

	#define GFX_TYPE_64				GFXON

/*#elif defined(__GNUC__) || defined(__GNUG__)
	typedef __INT8_TYPE__			gI8;
	typedef __UINT8_TYPE__			gU8;
	typedef __INT16_TYPE__			gI16;
	typedef __UINT16_TYPE__			gU16;
	typedef __INT32_TYPE__			gI32;
	typedef __UINT32_TYPE__			gU32;
	#define GI8_C(v)	  			v
	#define GU8_C(v)  				v ## U
	#define GI16_C(v)	  			v
	#define GU16_C(v)  				v ## U
	#define GI32_C(v)	  			v
	#define GU32_C(v)  				v ## U
	#define GFX_TYPE_64				GFXOFF
*/
#else
	#include <limits.h>

	/* char's are the smallest common type definition */
	typedef signed   char			gI8;
	typedef unsigned char			gU8;
	#define GI8_C(v)	  			v
	#define GU8_C(v)  				v ## U

	/*
	 *  Deduce the type assignments from limits.h under the assumption that
	 *  integer sizes in bits are powers of 2, and follow the ANSI
	 *  definitions.
	 */
	#if defined(SHRT_MAX) && SHRT_MAX >= 0x7FFF
		typedef signed   short		gI16
		typedef unsigned short		gU16
	#else
		typedef signed   int		gI16
		typedef unsigned int		gU16
	#endif
	#define GI16_C(v)	  			v
	#define GU16_C(v)  				v ## U

	#if defined(INT_MAX) && INT_MAX >= 0x7FFFFFFL
		typedef signed   int		gI32
		typedef unsigned int		gU32
		#define GI32_C(v)	  		v
		#define GU32_C(v)  			v ## U
	#else
		typedef signed   long		gI32
		typedef unsigned long		gU32
		#define GI32_C(v)	  		v ## L
		#define GU32_C(v)  			v ## UL
	#endif

	#if defined(__GNUC__) && !defined(vxWorks)
		#define GFX_TYPE_64				GFXON
		__extension__ typedef long long	gI64;
		__extension__ typedef unsigned long long gU64;
		#define GI64_C(v)				v ## LL
		#define GU64_C(v)				v ## ULL
	#elif defined(__MWERKS__) || defined (__SUNPRO_C) || defined (__SUNPRO_CC) || defined (__APPLE_CC__) || defined (_LONG_LONG) || defined (_CRAYC) || defined (S_SPLINT_S)
		#define GFX_TYPE_64				GFXON
		typedef long long				gI64;
		typedef unsigned long long		gU64;
		#define GI64_C(v)				v ## LL
		#define GU64_C(v)				v ## ULL
	#elif (defined(__WATCOMC__) && defined(__WATCOM_INT64__)) || (defined(_MSC_VER) && _INTEGRAL_MAX_BITS >= 64) || (defined (__BORLANDC__) && __BORLANDC__ > 0x460) || defined (__alpha) || defined (__DECC)
		#define GFX_TYPE_64				GFXON
		typedef signed   __int64		gI64;
		typedef unsigned __int64		gU64;
	#else
		#define GFX_TYPE_64				GFXOFF
	#endif
#endif

typedef void *				gAny;
typedef void *				gPtr;
typedef ptrdiff_t			gPtrDiff;
#if GFX_MEM_LT64K
	typedef gU16			gMemSize;
#else
	typedef gU32			gMemSize;
#endif
typedef gI32				gFileSize;
typedef gI8					gBool;
#define gTrue				(-1)
#define gFalse				(0)

#if GFX_COMPAT_V2
	/* Is stdint.h already included? */
	#ifndef INT16_C
		typedef gI8			int8_t;
		typedef gU8			uint8_t;
		typedef gI16		int16_t;
		typedef gU16		uint16_t;
		typedef gI32		int32_t;
		typedef gU32		uint32_t;
	#endif
	typedef gI8				bool_t;
	#ifndef TRUE
		#define TRUE		gTrue
	#endif
	#ifndef FALSE
		#define FALSE		gFalse
	#endif
#endif
