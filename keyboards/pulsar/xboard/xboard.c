/* Copyright 2021 kuenhlee, Don Kjer, Tyler Tidman
 * Copyright 2021 Simon Arlott
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//#include "quantum.h"

#include "xboard.h"
#include <ch.h>
#include <hal.h>

#include <string.h>
#include <math.h>
#include <lib/lib8tion/lib8tion.h>

//#include <math.h>
//#include "print.h"

/* Private Functions */
void off_all_leds(void) {
#ifdef LED_NUM_LOCK_PIN
    writePinHigh(LED_NUM_LOCK_PIN);
#endif
    writePinHigh(LED_CAPS_LOCK_PIN);
    writePinHigh(LED_SCROLL_LOCK_PIN);
    writePinHigh(LED_WIN_LOCK_PIN);
    writePinHigh(LED_MR_LOCK_PIN);
}

void on_all_leds(void) {
#ifdef LED_NUM_LOCK_PIN
    writePinLow(LED_NUM_LOCK_PIN);
#endif
    writePinLow(LED_CAPS_LOCK_PIN);
    writePinLow(LED_SCROLL_LOCK_PIN);
    writePinLow(LED_WIN_LOCK_PIN);
    writePinLow(LED_MR_LOCK_PIN);
}

void off_mr_leds(void) {
    writePinHigh(LED_MR_LOCK_PIN);
}
void on_mr_leds(void) {
    writePinLow(LED_MR_LOCK_PIN);
}

/* WinLock and MR LEDs are non-standard. Need to override led init */
void led_init_ports(void) {
#ifdef LED_NUM_LOCK_PIN
    setPinOutput(LED_NUM_LOCK_PIN);
#endif
    setPinOutput(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_SCROLL_LOCK_PIN);
    setPinOutput(LED_WIN_LOCK_PIN);
    setPinOutput(LED_MR_LOCK_PIN);
    off_all_leds();
}
//---------------------

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}
//---------------------

 void keyboard_pre_init_kb(void) {

    setPinOutput(GPIO_KM_OE);       // power on default = 0
    setPinOutput(GPIO_KM_SEL);      // power on default = 0
    setPinOutput(GPIO_KM_PWEN);     // power on default = 1

    keyboard_pre_init_user();
 }

void keyboard_post_init_kb(void) {

    keyboard_post_init_user();

    #ifdef AUTO_SHIFT_ENABLE 
        autoshift_disable();
    #endif

    oneshot_disable();      // oneshot_enable(), oneshot_toggle()
}
//----------------------------------

#define __ NO_LED
#define ___ NO_LED

//------------------------------------------
#ifdef RGB_MATRIX_ENABLE

__attribute__ ((weak)) bool rgb_matrix_indicators_kb(void)  {
    led_t host_leds = host_keyboard_led_state();

    if (host_leds.caps_lock) { 
        rgb_matrix_set_color(72, 0x20, 0x0, 0x20);            
    }
    if (host_leds.scroll_lock) {
        rgb_matrix_set_color(22, 0x00, 0x20, 0x20);
    }        
    // if (host_keyboard_led_state().num_lock) {
    //     rgb_matrix_set_color(59, 0x20, 0x20, 0x00);    
    // }

    return rgb_matrix_indicators_user();
    return TRUE;
} 

//----------------------------------

led_config_t g_led_config = {    // 3731 Driver에서 LED 스트링으로 변경함, 상단 및 하단에 21개의 더미 LED 추가 됨
/*
---------------      0 ~ 20 , 21 개의 데코 LED ---------------------------------------------------------------------------------
KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   QUICK(New)  KC_PSCR, KC_SLCK, KC_PAUS,
 K00,      K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,      K0A,    K0B,     K0C,       K60           K0D,     K0E,      K0F,
  37,       36,      35,      34,      33,      32,      31,      30,       29      28       27        26      25        24,            23,      22,       21   <===좌 우 반전
                                                                                                                                        이전키매트릭스 아트웍 오류 수정 ==>  K67,      K69,     K68,
KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,            N_LOCK,   KC_PSLS, KC_PAST, KC_PMNS,
 K10,     K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     K19,     K1A,      K1B,    K1C,     K1E,         K2E,     K2F,     K1F,               K6A,      K69,      K68,    K67,    
 38,      39,      40,       41,     042,     043,     044,     045,     046,     047,     048,      049,     050,     051,        052,     053,     054,               -------------------------------

KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,           KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
 K20,     K21,    K22,      K23,     K24,     K25,     K26,     K27,     K28,     K29,     K2A,       K2B,      K2C,    K2D,      K3D,       K3E,     K3F,              K7A,      K79,     K78,     K6B,
  71,     70,      69,       68,      67,      66,      65,      64,       63,     62,      61,        60.       59,     58,       57,        56,    55, <=좌우 반전   -------------------------------
o
                                                                                                             <K42>
KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, <KC_NUHS> KC_ENT,                                         KC_P4,   KC_P5,   KC_P6,         
  K30,   K31,     K32,     K33,     K34,     K35,     K36,     K37,     K38,     K39,      K3A,      K3B,     K3C,    K4E,                                              K7E,     K7D,     K7C,
  072,   73,      74,       75,      76,      77,      78,      79,      80,      81,       82,        83,    XXX,     84,                                             -------------------------------

           <K45>                                                                                             
KC_LSFT,<KC_NUBS> KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  <K56>   KC_RSFT,              KC_UP,                     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
 K40,       K41,   K42,     K43,     K44,     K45,     K46,     K47,     K48,     K49,      K4A,      K4B,              K4D,                K4F,                       K6E,     K6D,     K6C,      K7B,
 97,       xxx,    96,      95,       94,      93,      92,      91,      90,      89,       88,       87,    ----       86,                  85,   <===좌 우 반전        -------------------------------

                            <k131>                                           <k132> <k133>
KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,MO(WIN_FN),KC_APP, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,           KC_P0,            KC_PDOT
 K50,      K51,    K52,                                K56,                                 K5A,     K5B,      K5C,     K5D,      K5E,      K5F,     K6F,              K7F,               K77
 98,        99     100                           101,  102,  103,                           104,      105,     106,     107,      108,      109,     110               -------------------------------

< 참고용 키매트릭스 > 
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E,  K0F },  \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  XXX,  K1E,  K1F },  \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,  K2E,  K2F },  \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D,  K3E,  K3F },  \
    { K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  XXX,  K4D,  K4E,  K4F },  \
    { K50,  K51,  K52,  XXX,  XXX,  XXX,  K56,  XXX,  XXX,  XXX,  K5A,  K5B,  K5C,  K5D,  K5E,  K5F },  \
    { K60,  K61,  K62,  K63,  XXX,  XXX,  XXX,  K67,  K68,  K69,  K6A,  K6B,  K6C,  K6D,  K6E,  K6F },  \
    { XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  K77,  K78,  K79,  K7A,  K7B,  K7C,  K7D,  K7E,  K7F }   \

    실제파일에 0을 앞에 붙이면 안됨.. 8진수로 오인함  /  위 LED넘버는 하나씩 뺴야 함
*/
    {       // total 16x8 = 128 - 22 = 106  (config led total = 112) // WS2812용
        { 37, 36, 35,  34,  33,  32,  31,  30,   29,  28,  27,  26,  25,  23,  22,  21 },
        { 38, 39, 40,  41,  42,  43,  44,  45,   46,  47,  48,  49,  50, ___,  51,  54 },
        { 71, 70, 69,  68,  67,  66,  65,  64,   63,  62,  61,  60,  59,  58,  52,  53 },
        { 72, 73, 74,  75,  76,  77,  78,  79,   80,  81,  82,  83, ___,  57,  56,  55 },
        { 97,___, 96,  95,  94,  93,  92,  91,   90,  89,  88,  87, ___,  86,  84,  85 },
        { 98, 99,100, ___, ___, ___, 102, ___,  ___, ___, 104, 105, 106, 107, 108, 109 },
        { 24,16, 17, 19, ___, ___, ___, ___,  ___, ___, ___, ___, ___, ___, ___, 110 },
        {___,___,___, ___, ___, ___, ___, ___,  ___, ___, ___, ___, ___, ___, ___, ___ }
    },
    {   //   (config led total = 111)
        // LED Index to Physical Position  상단에 21개 데코LED 추가, 1줄 더 추가됨, ANSI만 지원 ISO 및 JP 삭제  (아래에서 반전처리 및 넘패드 부분 삭제 완료)
        {0,0}, {9,0}, {18,0}, {27,0}, {36,0}, {45,0}, {54,0}, {63,0}, {72,0}, {81,0}, {90,0}, {99,0}, {108,0}, {117,0}, {126,0}, {135,0}, {144,0}, {153,0}, {162,0}, {171,0}, {180,0},
        {180,11}, {169,11}, {159,11},       {144,11},  {133,11}, {123,11}, {112,11}, {102,11}, {89,11}, {78,11},  {68,11}, {57,11}, {45,11}, {34,11}, {24,11}, {13,11},    {0,11},    
        {0,21}, {10,21}, {21,21}, {31,21}, {42,21}, {52,21}, {63,21}, {73,21}, {83,21}, {94,21}, {104,21}, {115,21}, {125,21},    {139,21},          {159,21}, {169,21}, {180,21},    
        {180,32}, {169,32}, {159,32},       {143,32}, {130,32}, {120,32},  {109,32}, {99,32}, {89,32}, {78,32}, {68,32}, {57,32}, {47,32},  {36,32}, {26,32}, {16,32}, {3,32},                   
        {4,43}, {18,43}, {29,43}, {39,43}, {50,43}, {60,43}, {70,43}, {81,43}, {91,43}, {102,43}, {112,43}, {123,43},           {138,43},                                             
                {169,53},                   {135,53}, {117,53},  {107,53},  {96,53},    {86,53},  {76,53},  {65,53},   {55,53},  {44,53},  {34,53}, {23,53}, {10,53},
        {1,64}, {14,64}, {27,64},                    {50,64},{66,64},{80,64},                 {105,64}, {118,64}, {131,64}, {145,64},                {159,64}, {169,64}, {180,64},        
    },
    {   // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,   1,   4, 4, 4, 4,   1, 1, 1, 1,    4, 4, 4, 4,    1, 
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1, 1, 1,
        1, 1, 1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   1,             
        1,    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,   
        1, 1, 1,     4,4,4,     1, 1, 1, 1,    1, 1, 1
    }

/*  {   //   (config led total = 111)
        // LED Index to Physical Position  상단에 21개 데코LED 추가, 1줄 더 추가됨, ANSI만 지원 ISO 및 JP 삭제  (위에 좌우 반전처리 및 넘패드 부분 삭제 완료)
        {0,0}, {9,0}, {18,0}, {27,0}, {36,0}, {45,0}, {54,0}, {63,0}, {72,0}, {81,0}, {90,0}, {99,0}, {108,0}, {117,0}, {126,0}, {135,0}, {144,0}, {153,0}, {162,0}, {171,0}, {180,0},
        {0,11}, {13,11}, {24,11}, {34,11}, {45,11}, {57,11}, {68,11}, {78,11}, {89,11}, {102,11}, {112,11}, {123,11}, {133,11},  {144,11},           {159,11}, {169,11}, {180,11},
        {0,21}, {10,21}, {21,21}, {31,21}, {42,21}, {52,21}, {63,21}, {73,21}, {83,21}, {94,21}, {104,21}, {115,21}, {125,21},    {139,21},          {159,21}, {169,21}, {180,21},     {193,21}, {203,21}, {214,21}, {224,21},
        {3,32}, {16,32}, {26,32}, {36,32}, {47,32}, {57,32}, {68,32}, {78,32}, {89,32}, {99,32},  {109,32}, {120,32}, {130,32}, {143,32},            {159,32}, {169,32}, {180,32},     {193,32}, {203,32}, {214,32}, {224,32},
        {4,43}, {18,43}, {29,43}, {39,43}, {50,43}, {60,43}, {70,43}, {81,43}, {91,43}, {102,43}, {112,43}, {123,43},        {138,43},                                                 {193,43}, {203,43}, {214,43},
            {10,53}, {23,53}, {34,53}, {44,53}, {55,53}, {65,53}, {76,53}, {86,53}, {96,53},  {107,53}, {117,53},      {135,53},                               {169,53},               {193,53}, {203,53}, {214,53}, {224,53},
        {1,64}, {14,64}, {27,64},                    {50,64},{66,64},{80,64},                 {105,64}, {118,64}, {131,64}, {145,64},                {159,64}, {169,64}, {180,64},          {198,64},      {214,64}
    },
    {   // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1,  4, 4, 4, 4,  1, 1, 1, 1,  4, 4, 4, 4,  1,  1, 1, 1,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,   1, 1, 1,        8, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   1, 1, 1,        4, 4, 4, 1,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   1,                    4, 4, 4,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   1,       1,           4, 4, 4, 1,
        1, 1, 1,       4,4,4,        1, 1, 1, 1,    1, 1, 1,        4,    4
    }
*/
};
#endif
