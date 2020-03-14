#pragma once

#define MASTER_LEFT

/* Limit max RGB LED current to avoid tripping controller fuse. */
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
