#include "rev1.h"
#include "split_util.h"  // for isLeftHand

/*
Logical Layout
Left:
R\C 0  1  2  3  4  5
0   12 11 10 09 08 07
		   03    02    01
1		13 14 15 16 17 18
2		24 23 22 21 20 19
		   04    05    06  
3		25 26 27 28 29 30  31 

4		      35 34 33     32
*/ 


#define KEY_2_LED_LEFT \
	{ 11, 10,  9,  8,  7,  6 }, \
	{ 12, 13, 14, 15, 16, 17 }, \
	{ 23, 22, 21, 20, 19, 18 }, \
	{ 24, 25, 26, 27, 28, 29 }, \
	{ NO_LED, 34, 33, 32, 31, 30}

#define KEY_2_LED_RIGHT \
	{ 46, 45, 44, 43, 42, 41 }, \
	{ 47, 48, 49, 50, 51, 52 }, \
	{ 58, 57, 56, 55, 54, 53 }, \
	{ 59, 60, 61, 62, 63, 64 }, \
	{ NO_LED, 69, 68, 67, 66, 65}

#define POS_LED_LEFT \
  { 83, 11}, { 50,  7}, { 16, 14}, { 16, 46}, { 50, 51}, { 83, 62}, \
	{ 83,  3}, { 61,  1}, { 50,  0}, { 33,  1}, { 16,  6}, {  0,  7}, \
	{  0, 23}, { 16, 22}, { 33, 18}, { 50, 16}, { 61, 18}, { 83, 20}, \
	{ 83, 37}, { 61, 35}, { 50, 33}, { 33, 35}, { 16, 39}, {  0, 40}, \
	{  0, 57}, { 16, 56}, { 33, 52}, { 50, 50}, { 61, 52}, { 83, 53}, \
	           {100, 45}, { 97, 71}, { 75, 70}, { 59, 68}, { 42, 68}

#define POS_LED_RIGHT \
  {141, 11}, {174,  7}, {208, 14}, {208, 46}, {174, 51}, {141, 62}, \
	{141,  3}, {163,  1}, {174,  0}, {191,  1}, {208,  6}, {224,  7}, \
	{224, 23}, {208, 22}, {191, 18}, {174, 16}, {163, 18}, {141, 20}, \
	{141, 37}, {163, 35}, {174, 33}, {191, 35}, {208, 39}, {224, 40}, \
	{224, 57}, {208, 56}, {191, 52}, {174, 50}, {163, 52}, {141, 53}, \
             {124, 45}, {127, 71}, {149, 70}, {165, 68}, {182, 68}

#define LED_FLAG \
  2, 2, 2, 2, 2, 2, \
	4, 4, 4, 4, 4, 1, \
	1, 4, 4, 4, 4, 4, \
	4, 4, 4, 4, 4, 1, \
	1, 4, 4, 4, 4, 4, \
	1, 1, 1, 1, 1


#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
	KEY_2_LED_LEFT,
	KEY_2_LED_RIGHT
}, {
	POS_LED_LEFT,
	POS_LED_RIGHT
}, {
	LED_FLAG, LED_FLAG
}}; 

#endif

__attribute__((weak))
void matrix_init_user(void) {}

void matrix_init_kb(void) {
#ifdef RGB_MATRIX_ENABLE
	if (!isLeftHand) {
		g_led_config = (led_config_t){ {
			KEY_2_LED_RIGHT,
			KEY_2_LED_LEFT
		}, {
			POS_LED_RIGHT,
			POS_LED_LEFT
		}, {
			LED_FLAG, LED_FLAG
		}};
	}
#endif
	matrix_init_user();
}


#undef KEY_2_LED_LEFT
#undef KEY_2_LED_RIGHT
#undef POS_LED_LEFT
#undef POS_LED_RIGHT
#undef LED_FLAG