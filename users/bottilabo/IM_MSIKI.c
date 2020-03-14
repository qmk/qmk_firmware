#pragma once

// M式   
#include "IM_ROMAJI_BASE.c"


static const uint8_t msiki_layout[] PROGMEM  = TRANSKEYCODE_DEF( \
    Q,  L,  J,  F,  C,   M,  Y,  R,  W,  P, \
    E,  U,  I,  A,  O,   K,  S,  T,  N,  H, \
 SLSH,  X,  V,MINS,DOT,  G,  Z,  D,COMM, B );

// 同時押しキー
//

// 同時押しキーから文字への変換
static const ROMAJI_BASE_CC_t const msiki_cctbl[] MEMCLASS = {
};

// 単打キーから文字列への変換
static const ROMAJI_BASE_CC_t const msiki_cctbl2[] MEMCLASS = {
    {'Q',"fe"},
    {'L',"fy"},{'l',"u-"},
    {'J',"fi"},
    {'F',"fa"},
    {'C',"fo"},

    {'?',"el"},{'?',"tu"},
    {'X',"ul"},{'X',"tu"},
    {'V',"ul"},{'V',"tu"},
    {'_',"al"},{'_',"tu"},
    {'>',"ol"},{'>',"tu"},

    {'M',"my"},
    {'Y',"lt"},{'Y',"u\0"},
    {'R',"ry"},
    {'W',"nn"},
    {'P',"py"},

    {'K',"ky"},
    {'S',"sy"},
    {'T',"ty"},
    {'N',"ny"},
    {'H',"hy"},

    {'G',"gy"},
    {'Z',"zy"},
    {'D',"dy"},
    {'<',".\0"},
    {'B',"by"},
    
    {'q',"le"},
    {'l',"lu"},
    {'j',"li"},
    {'f',"la"},
    {'c',"lo"},

    {'E',"en"},{'E',"n\0"},
    {'U',"un"},{'U',"n\0"},
    {'I',"in"},{'I',"n\0"},
    {'A',"an"},{'A',"n\0"},
    {'O',"on"},{'O',"n\0"},

    {'/',"ei"},
    {'x',"uu"},
    {'v',"ui"},
    {'-',"ai"},
    {'.',"ou"},

};

// キーコードから同時押しキーへの変換
static const ROMAJI_BASE_KEYCODE_BIT_t const msiki_keycode_bit_tbl[] MEMCLASS = {
    {K_TL0,  ROMAJI_BASE_LSHIFT},
    {K_TR0,  ROMAJI_BASE_RSHIFT},
};

// 同時押しキーから文字列への変換
static const ROMAJI_BASE_CODE_CHAR_t const msiki_bit_char_tbl[] MEMCLASS = {
};

//

// 同時押しキーへの変換
static uint16_t msiki_key_to_bits(uint16_t keycode) {
    return romaji_base_key_to_bits(msiki_keycode_bit_tbl,sizeof(msiki_keycode_bit_tbl)/sizeof(ROMAJI_BASE_KEYCODE_BIT_t),keycode);
}


// 単打キー、同時押しキーの特別な組み合わせからcharへの変換
char msiki_compose_char(uint16_t keycode,uint16_t kbits) {
    bool shift = (kbits & ROMAJI_BASE_LSHIFT) | (kbits & ROMAJI_BASE_RSHIFT);
    char ch = romaji_base_code_to_char(msiki_bit_char_tbl,sizeof(msiki_bit_char_tbl)/sizeof(ROMAJI_BASE_CODE_CHAR_t),kbits );
    return romaji_base_compose_char(ROMAJI_BASE_SHIFTED_CHRS,shift,keycode,ch);
}

// 単打キーキーから文字への変換
char* msiki_char_to_str(char* p,char ch) {
    return romaji_base_char_to_str(msiki_cctbl2,sizeof(msiki_cctbl2)/sizeof(ROMAJI_BASE_CC_t),p,ch);
}

// 同時押しキーから文字への変換
char* msiki_bits_to_str(char* p,uint16_t bits) {
    return romaji_base_bits_to_str(msiki_cctbl,sizeof(msiki_cctbl)/sizeof(ROMAJI_BASE_CC_t),p,bits);
}

//
//

static uint8_t msiki_enabled = false;

void IM_MSIKI_enable(uint8_t modef) {
    msiki_enabled = modef;
    if( ! modef ) return;

    romaji_base_connect(
    msiki_key_to_bits,
    msiki_compose_char,
    msiki_char_to_str,
    msiki_bits_to_str
    );
    IM_ROMAJI_BASE_enable(modef);
    transkeycode_set(msiki_layout,"M-Siki");
}

bool process_MSIKI(uint16_t keycode, keyrecord_t *record) {
    if( ! msiki_enabled )
        return true;
    return process_romaji_base(keycode,record);
}

