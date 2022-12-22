#pragma once


/* Top LED is blue only.
 * Middle LED is blue, red or magenta.
 * Bottom LED is red only LED driver 2 RGB 48 Blue channel.
 */

#ifdef RGB_MATRIX_ENABLE
void indicators_update(uint8_t caps, uint8_t fn1, uint8_t fn2);

#endif // RGB_MATRIX_ENABLE