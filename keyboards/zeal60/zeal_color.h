#ifndef ZEAL_COLOR_H
#define ZEAL_COLOR_H

#include <stdint.h>
#include <stdbool.h>

#if defined(__GNUC__)
#define PACKED __attribute__ ((__packed__))
#else
#define PACKED
#endif

#if defined(_MSC_VER)
#pragma pack( push, 1 )
#endif

typedef struct PACKED
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB;

typedef struct PACKED
{
	uint8_t h;
	uint8_t s;
	uint8_t v;
} HSV;

#if defined(_MSC_VER)
#pragma pack( pop )
#endif

RGB hsv_to_rgb( HSV hsv );

#endif // ZEAL_COLOR_H
