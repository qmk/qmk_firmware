#include "2x5keypad.h"

void keyboard_pre_init_user(void)
{
  setPinOutput(RED_LED);
  setPinOutput(BLUE_LED);
  setPinOutput(GREEN_LED);
}
