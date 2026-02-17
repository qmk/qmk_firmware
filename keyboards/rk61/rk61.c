#include "quantum.h"

#define LOOP_10HZ_PERIOD    100

deferred_token loop10hz_token  = INVALID_DEFERRED_TOKEN;
uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg);
uint8_t blink_cnt=0;

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
	loop10hz_token = defer_exec(LOOP_10HZ_PERIOD, loop_10Hz, NULL);
}

uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg) {
 
    extern matrix_row_t matrix[MATRIX_ROWS];
	static uint32_t reset_to_factory_tick = 0;
  
	if(matrix[0] ==0 && matrix[1] == 0 && matrix[2] == 0 && 
       matrix[3] == 0x0 && matrix[4] == 0x1020) {
        if(reset_to_factory_tick++ > 30) {
            reset_to_factory_tick = 0;
            eeconfig_init();
			soft_reset_keyboard();
        }
    } else {
        reset_to_factory_tick = 0;
    }
	
	if(matrix[0] ==0 && matrix[1] == 0x200 && matrix[2] == 0x200 && 
       matrix[3] == 0x0 && matrix[4] == 0x1000)
	{
			clear_keyboard();
			rgb_matrix_set_color_all(RGB_WHITE);
			extern void rgb_matrix_update_pwm_buffers(void);
			rgb_matrix_update_pwm_buffers();
			wait_ms(100);
			matrix_scan();
			while(matrix[0] ==0 && matrix[1] == 0x0 && matrix[2] == 0x0 && 
					matrix[3] == 0x0 && matrix[4] == 0x0)
					matrix_scan();
	}
	
	if(blink_cnt != 0)
	{
		if(blink_cnt % 4 ==1)
			rgb_matrix_disable_noeeprom();
		else if(blink_cnt % 4 ==3)
			rgb_matrix_enable_noeeprom();
		blink_cnt++;
		if(blink_cnt>12)
			blink_cnt=0;
	}
	
	return LOOP_10HZ_PERIOD;
}

#ifdef RGB_MATRIX_ENABLE
#define __ NO_LED

/*

Key Index	Key Code
0	KC_BSPC
1	KC_EQL
2	KC_MINS
3	KC_0
4	KC_9
5	KC_8
6	KC_7
7	KC_6
8	KC_5
9	KC_4
10	KC_3
11	KC_2
12	KC_1
13	KC_ESC
14	KC_TAB
15	KC_Q
16	KC_W
17	KC_E
18	KC_R
19	KC_T
20	KC_Y
21	KC_U
22	KC_I
23	KC_O
24	KC_P
25	KC_LBRC
26	KC_RBRC
27	KC_BSLS
28	KC_ENT
29	KC_QUOT
30	KC_SCLN
31	KC_L
32	KC_K
33	KC_J
34	KC_H
35	KC_G
36	KC_F
37	KC_D
38	KC_S
39	KC_A
40	KC_CAPS
41	KC_LSFT
42	KC_Z
43	KC_X
44	KC_C
45	KC_V
46	KC_B
47	KC_N
48	KC_M
49	KC_COMM
50	KC_DOT
51	KC_SLASH
52	KC_RSFT
53  (FN Key)
54	KC_RCTL
55	KC_APP
56	KC_RALT
57	KC_SPC
58	KC_LALT
59	KC_LWIN
60	KC_LCTL
*/
led_config_t g_led_config = {
	{
         // Key Matrix to LED Index
        { 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0 },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 },
        { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, __ },
        { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, __, __ },
        { 60, 59, 58, __, __, 57, __, __, 56, 55, 54, __, 53, __ },
    },
/*	{
         // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 },
        { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, __, 40 },
        { 41, __, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, __, 52 },
        { 53, 54, 55, __, __, __, 56, __, __, __, 57, 58, 59, 60 },
    },*/
/*    {
        // LED Index to Physical Position
         {0,0},   {16,0},  {32,0},  {48,0},  {64,0},  {81,0},   {97,0},  {113,0},  {129,0},  {145,0},  {161,0},  {177,0},  {193,0},  {218,0},
        {4,16},  {24,16}, {40,16}, {56,16}, {73,16}, {89,16}, {105,16}, {121,16}, {137,16}, {153,16}, {169,16}, {185,16}, {202,16}, {222,16},
        {6,32},  {28,32}, {44,32}, {60,32}, {77,32}, {93,32}, {109,32}, {125,32}, {141,32}, {157,32}, {173,32}, {189,32},           {216,32},
       {10,48},           {36,48}, {52,48}, {69,48}, {85,48}, {101,48}, {117,48}, {133,48}, {149,48}, {165,48}, {181,48},           {212,48},
        {2,64},  {22,64}, {42,64},                            {103,64},                               {164,64}, {184,64}, {204,64}, {224,64},
    },*/
	{
	       // LED Index to Physical Position
       {218,0},  {193,0}, {177,0}, {161,0}, {145,0},  {129,0},  {113,0},   {97,0},   {81,0},   {64,0},   {48,0},   {32,0},   {16,0},    {0,0},   
        {4,16},  {24,16}, {40,16}, {56,16}, {73,16},  {89,16}, {105,16}, {121,16}, {137,16}, {153,16}, {169,16}, {185,16}, {202,16}, {222,16},
      {216,32},          {189,32},{173,32},{157,32},{141,32}, {125,32}, {109,32},  {93,32},  {77,32},  {60,32},  {44,32},  {28,32},    {6,32},           
       {10,48},           {36,48}, {52,48}, {69,48},  {85,48}, {101,48}, {117,48}, {133,48}, {149,48}, {165,48}, {181,48},           {212,48},
      {224,64}, {204,64},{184,64},{164,64},                              {103,64},                                {42,64},  {22,64},   {2,64},  
	},
	{
        // RGB LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1, 1, 1,          1,          1, 1, 1, 1,
    }
};


#endif // RGB_MATRIX_ENABLE

#ifdef VIA_ENABLE
bool via_command_kb(uint8_t *data, uint8_t length) {
	uint8_t *command_id   = &(data[0]);
	
	if( *command_id == 0x0A)	//VIA_EEPROM_RESET
	{
		eeconfig_init();
		soft_reset_keyboard();
	}
	
    return false;
}
#endif