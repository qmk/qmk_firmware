#include "duckypad.h"

#include "stdio.h"

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"

led_config_t g_led_config = { {
    { 2, 1, 0, 3, 4, 5, 8, 7, 6, 9, 10, 11, 14, 13, 12, NO_LED, NO_LED }
}, {
    {224, 0},
    {112, 0},
    {0, 0},
    {0, 16},
    {112, 16},
    {224, 16},
    {224, 32},
    {112, 32},
    {0, 32},
    {0, 48},
    {112, 48},
    {224, 48},
    {224, 64},
    {112, 64},
    {0, 64},
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
} };

#endif

void keyboard_pre_init_kb(void) {
    setPinOutput(A0);
    writePinHigh(A0);
    writePinLow(A0);
    wait_ms(10);
    writePinHigh(A0);
    rgb_matrix_toggle_noeeprom();
}
