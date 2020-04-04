#pragma once

//
#include "IM_ROMAJI_BASE.c"

static const uint8_t romaji_colemak_layout[] PROGMEM  = TRANSKEYCODE_DEF( \
    X,  W,  F,  P,  G,   J,  L,  U,  Y,  MINS, \
    A,  R,  S,  T,  D,   H,  N,  E,  I,  O, \
    X,  Z,  K,  V,  B,   K,  M,COMM,DOT,SLSH );

// 同時押しキー
//enum {
//};

// 同時押しキーから文字列への変換
static const ROMAJI_BASE_CC_t const romaji_colemak_cctbl[] MEMCLASS = {
};

// 単打キーから文字列への変換
static const ROMAJI_BASE_CC_t const romaji_colemak_cctbl2[] MEMCLASS = {
    {'/',"lt"},{'/',"u\0"},
    {'l',"nn"},
    {'A',"la"},
    {'I',"li"},
    {'U',"lu"},
    {'E',"le"},
    {'O',"lo"},
};

// キーコードから同時押しキーへの変換
static const ROMAJI_BASE_KEYCODE_BIT_t const romaji_colemak_keycode_bit_tbl[] MEMCLASS = {
    {K_TR0,   ROMAJI_BASE_RSHIFT},
    {K_TL0,   ROMAJI_BASE_LSHIFT},
};


//


// 同時押しキーへの変換
static uint16_t romaji_colemak_key_to_bits(uint16_t keycode) {
    return romaji_base_key_to_bits(romaji_colemak_keycode_bit_tbl,sizeof(romaji_colemak_keycode_bit_tbl)/sizeof(ROMAJI_BASE_KEYCODE_BIT_t),keycode);
}

// 単打キー、同時押しキーの特別な組み合わせからcharへの変換
char romaji_colemak_compose_char(uint16_t keycode,uint16_t kbits) {
    bool shift = (kbits & ROMAJI_BASE_LSHIFT) | (kbits & ROMAJI_BASE_RSHIFT);
    return romaji_base_compose_char(ROMAJI_BASE_DAKUON_CHRS,shift,keycode,0);
}

// 単打キーキーから文字列への変換
char* romaji_colemak_char_to_str(char* p,char ch) {
    return romaji_base_char_to_str(romaji_colemak_cctbl2,sizeof(romaji_colemak_cctbl2)/sizeof(ROMAJI_BASE_CC_t),p,ch);
}

// 同時押しキーから文字列への変換
char* romaji_colemak_bits_to_str(char* p,uint16_t bits) {
    return romaji_base_bits_to_str(romaji_colemak_cctbl,sizeof(romaji_colemak_cctbl)/sizeof(ROMAJI_BASE_CC_t),p,bits);
}

//
//

static uint8_t romaji_colemak_enabled = false;

void IM_ROMAJI_COLEMAK_enable(uint8_t modef) {
    romaji_colemak_enabled = modef;
    if( ! modef ) return;

    romaji_base_connect(
    romaji_colemak_key_to_bits,
    romaji_colemak_compose_char,
    romaji_colemak_char_to_str,
    romaji_colemak_bits_to_str
    );
    IM_ROMAJI_BASE_enable(modef);
    transkeycode_set(romaji_colemak_layout,"Colemak-R");
}

bool process_ROMAJI_COLEMAK(uint16_t keycode, keyrecord_t *record) {
    if( ! romaji_colemak_enabled )
        return true;
    return process_romaji_base(keycode,record);
}
