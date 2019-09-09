#include "2x5keypad.h"


void matrix_init_kb(void)
{
    matrix_init_user();

    setPinOutput(RED_LED);
    setPinOutput(BLUE_LED);
    setPinOutput(GREEN_LED);
}
