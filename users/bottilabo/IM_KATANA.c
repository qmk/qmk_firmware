#pragma once

// カタナ式   
#include "IM_ROMAJI_BASE.c"


// ESC .   pf  td  sz  .  |^   BS  i   e
//
// CTL .   .   r   kg  <-  ->  a   u   y
//               m
// SFT .   .   hb  n,  v|  E.  o   N   -
//               w

static const uint8_t katana_layout[] PROGMEM  = TRANSKEYCODE_DEF( \
    _,P,T,S,   _, UP   ,BSPC,I,E,_, \
    _,_,R,K,LEFT, RIGHT,   A,U,Y,_, \
    _,_,H,N,DOWN, ENT,     O,COMM,DOT,SLSH );

#define KATANA_SPC KATANA_RSHIFT

// 同時押しキー
enum katana {
    KATANA_A = 1U << 0,
    KATANA_I = 1U << 1,
    KATANA_U = 1U << 2,
    KATANA_E = 1U << 3,
    KATANA_O = 1U << 4,
    KATANA_Y = 1U << 5,

    KATANA_R = 1U << 6,
    KATANA_K = 1U << 7,
    KATANA_H = 1U << 8,
    KATANA_N = 1U << 9,

    KATANA_NN = 1U << 10,
    KATANA_tu = 1U << 11,
    KATANA_MACRON = 1U << 12,
};

// 同時押しキーから文字列への変換
static const ROMAJI_BASE_CC_t const katana_cctbl[] MEMCLASS = {
    {KATANA_Y,"y\0"},
    {KATANA_A,"a\0"},
    {KATANA_O,"o\0"},
    {KATANA_U,"u\0"},
    {KATANA_E,"e\0"},
    {KATANA_I,"i\0"},
    {KATANA_NN,"nn"},
    {KATANA_MACRON,"-\0"},
    {KATANA_tu,"lt"},
    {KATANA_tu,"u\0"},
};

// 単打キーから文字列への変換
static const ROMAJI_BASE_CC_t const katana_cctbl2[] MEMCLASS = {
    {'N',"nn"},
};

// キーコードから同時押しキーへの変換
static const ROMAJI_BASE_KEYCODE_BIT_t const katana_keycode_bit_tbl[] MEMCLASS = {
{KC_A,     KATANA_A},
{KC_I,     KATANA_I},
{KC_U,     KATANA_U},
{KC_E,     KATANA_E},
{KC_O,     KATANA_O},
{KC_Y,     KATANA_Y},

{KC_R,     KATANA_R},
{KC_K,     KATANA_K},
{KC_H,     KATANA_H},
{KC_N,     KATANA_N},
{KC_COMM,  KATANA_NN},
{KC_DOT,   KATANA_MACRON},
{KC_SLSH,  KATANA_tu},

{K_TR0,   ROMAJI_BASE_RSHIFT},
{K_TL0,   ROMAJI_BASE_LSHIFT},
};

// 同時押しキーから文字列への変換
static const ROMAJI_BASE_CODE_CHAR_t const katana_bit_char_tbl[] MEMCLASS = {
    {KATANA_R|KATANA_K,'m'},
    {KATANA_H|KATANA_N,'w'},
    {KATANA_R         ,'r'},
    {KATANA_K         ,'k'},
    {KATANA_H         ,'h'},
    {KATANA_N         ,'n'},

};

//

// 同時押しキーへの変換
static uint16_t katana_key_to_bits(uint16_t keycode) {
    return romaji_base_key_to_bits(katana_keycode_bit_tbl,sizeof(katana_keycode_bit_tbl)/sizeof(ROMAJI_BASE_KEYCODE_BIT_t),keycode);
}

// 単打キー、同時押しキーの特別な組み合わせからcharへの変換
char katana_compose_char(uint16_t keycode,uint16_t kbits) {
    bool shift = (kbits & ROMAJI_BASE_LSHIFT) | (kbits & ROMAJI_BASE_RSHIFT);
    char ch = romaji_base_code_to_char(katana_bit_char_tbl,sizeof(katana_bit_char_tbl)/sizeof(ROMAJI_BASE_CODE_CHAR_t),
        kbits&(~(ROMAJI_BASE_LSHIFT|ROMAJI_BASE_RSHIFT|KATANA_A|KATANA_I|KATANA_U|KATANA_E|KATANA_O) ) );
    return romaji_base_compose_char(ROMAJI_BASE_DAKUON_CHRS,shift,keycode,ch);
}

// 単打キーから文字列への変換
char* katana_char_to_str(char* p,char ch) {
    return romaji_base_char_to_str(katana_cctbl2,sizeof(katana_cctbl2)/sizeof(ROMAJI_BASE_CC_t),p,ch);
}

// 同時押しキーから文字列への変換
char* katana_bits_to_str(char* p,uint16_t bits) {
    return romaji_base_bits_to_str(katana_cctbl,sizeof(katana_cctbl)/sizeof(ROMAJI_BASE_CC_t),p,bits);
}

//
//

static uint8_t katana_enabled = false;

void IM_KATANA_enable(uint8_t modef) {
    katana_enabled = modef;
    if( ! modef ) return;

    romaji_base_connect(
    katana_key_to_bits,
    katana_compose_char,
    katana_char_to_str,
    katana_bits_to_str
    );
    IM_ROMAJI_BASE_enable(modef);
    transkeycode_set(katana_layout,"Katanasiki");
}

bool process_KATANA(uint16_t keycode, keyrecord_t *record) {
    if( ! katana_enabled )
        return true;
    return process_romaji_base(keycode,record);
}

