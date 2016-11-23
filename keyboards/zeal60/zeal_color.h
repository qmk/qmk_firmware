#ifndef ZEAL_COLOR_H
#define ZEAL_COLOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct RGB
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB;

typedef struct HSV
{
	uint8_t h;
	uint8_t s;
	uint8_t v;
} HSV;

RGB hsv_to_rgb( HSV hsv );

#endif // ZEAL_COLOR_H
