#include "monorail2.h"

void matrix_init_kb(void) {
	matrix_init_user();
}

led_config_t g_led_config = { {

{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
	{ 224, 0 }, { 179, 0 }, { 134, 0 }, { 90, 0 }, { 45, 0 }, { 0, 0 },
	{ 0, 64 }, { 45, 64 }, { 90, 64 }, { 134, 64 }, { 179, 64 }, { 224, 64 }
}, {
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };