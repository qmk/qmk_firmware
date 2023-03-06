#include "vimclutch.h"

void keyboard_pre_init_kb(void)
{
	setPinOutput(F4);
	setPinOutput(F5);

	keyboard_pre_init_user();
};
