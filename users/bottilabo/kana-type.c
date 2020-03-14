#pragma once
#include "keymap_jp.h"
#include "kana-type.h"

static inline bool send_key(uint16_t code) {
    if( code == 0 )
        return false;
    register_code16( code );
    unregister_code16( code );
    return true;
}
static inline void send_key2(uint16_t code,uint16_t mod) {
    register_code16( mod );
    register_code16( code );
    unregister_code16( code );
    unregister_code16( mod );
}

/*
typedef struct {
    uint16_t code0;
    uint16_t code1;
} KanaToSendKey1;

KanaToSendKey1 const kana_tbl_1[] = {
    {KANA_ENT,KC_ENT},
    {KANA_BSPC,KC_BSPC},
    {KANA_ZENHAN,JP_ZHTG},
    {KANA_EISU,KC_KC_LANG2},
    {KANA_MHEN,JP_MHEN},
    {KANA_HENK,JP_MHENK},
    {KANA_KANA,JP_KANA},
};


typedef struct {
    uint16_t code0;
    uint16_t code1;
    uint16_t code2;
} KanaToSendKey2;

KanaToSendKey2 const kana_tbl_2[] = {
    {KANA_QSTN,KC_SLSH,KC_LSFT},
    {KANA_EXCL,KC_KC1,KC_LSFT},
};

typedef struct {
    uint16_t code0;
    const char* str; 
} KanaToSendKey2;

KanaToSendKey3 const kana_tbl_3[] = {
    {KANA_DOU,KC_SLSH,"DOU"},
};
*/

static bool send_romaji_kigou(uint16_t code) {
    switch(code) {
        case KANA_ENT:  send_key(KC_ENT);return true;
        case KANA_BSPC: send_key(KC_BSPC);return true;
        case KANA_ZENHAN: send_key(JP_ZHTG); return true;
        case KANA_EISU: send_key(KC_LANG2); return true;
        case KANA_MHEN: send_key(JP_MHEN); return true;
        case KANA_HENK: send_key(JP_HENK); return true;
        case KANA_KANA: send_key(JP_KANA); return true;
        case KANA_QSTN: send_key2(KC_SLSH,KC_LSFT);return true;
        case KANA_EXCL: send_key2(KC_1,KC_LSFT);return true;
        case KANA_DOU: send_string("DOU"); return true;

    }
    /*
    for(uint8_t i=0; i<sizeof(kana_tbl_1)/sizeof(KanaToSendKey1); i++) {
        if( 
    }
    */
    return false;
}

#ifndef NO_KANA 

static bool send_kana_kigou(uint16_t code) {
    switch(code) {
        case KANA_BSPC:
            send_key(KC_BSPC);
            return true;
        case KANA_QSTN:
            send_key2(KC_SLSH,KC_LSFT);
            send_key(KC_F9);
            return true;
        case KANA_EXCL:
            send_key2(KC_1,KC_LSFT);
            send_key(KC_F9);
            return true;
    }
    return send_romaji_kigou(code);
}


//
// KANA
//

// あ　から　ん     50   8
// , .             2    2
// ぁぃぅぇぉゃゅょ　8    4

const uint16_t MEMCLASS KANA_TBL[] = {
    JP_AT,JP_LBRC,
    KC_3,KC_E,KC_4,KC_5,KC_6,
    KC_T,KC_G,KC_H,JP_COLN,KC_B,
    KC_X,KC_D,KC_R,KC_P,KC_C,
    KC_Q,KC_A,KC_Z,KC_W,KC_S,
    KC_U,KC_I,KC_1,KC_COMM,KC_K,        // KC_U,KC_I,KC_1,JP_LT,KC_K,
    KC_F,KC_V,KC_2,JP_CIRC,JP_MINS,
    KC_J,KC_N,KC_NUHS,JP_SLSH,KC_M,
    KC_7,0,KC_8,0,KC_9,
    KC_O,KC_L,KC_DOT,JP_SCLN,LSFT(KC_GRV),    // KC_O,KC_L,JP_GT,JP_SCLN,JP_BSLS,
    KC_0,0,0,0,LSFT(KC_0),
    KC_Y,
    LSFT(KC_Z),
    KC_SPC,
    LSFT(KC_COMM),LSFT(KC_DOT),LSFT(KC_SLSH),LSFT(KC_MINS) // JP_COMM,JP_DOT,JP_SLSH,JP_YEN ,
};
const uint16_t MEMCLASS KANA_TBL_JP[] = {
    JP_AT,JP_LBRC,
    KC_3,KC_E,KC_4,KC_5,KC_6,
    KC_T,KC_G,KC_H,JP_COLN,KC_B,
    KC_X,KC_D,KC_R,KC_P,KC_C,
    KC_Q,KC_A,KC_Z,KC_W,KC_S,
    KC_U,KC_I,KC_1,KC_COMM,KC_K,        // KC_U,KC_I,KC_1,JP_LT,KC_K,
    KC_F,KC_V,KC_2,JP_CIRC,JP_MINS,
    KC_J,KC_N,KC_NUHS,JP_SLSH,KC_M,
    KC_7,0,KC_8,0,KC_9,
    KC_O,KC_L,KC_DOT,JP_SCLN,JP_BSLS,    // KC_O,KC_L,JP_GT,JP_SCLN,JP_BSLS,
    KC_0,0,0,0,LSFT(KC_0),
    KC_Y,
    LSFT(KC_Z),
    KC_SPC,
    LSFT(KC_COMM),LSFT(KC_DOT),LSFT(KC_SLSH),JP_YEN // JP_COMM,JP_DOT,JP_SLSH,JP_YEN ,
};


static uint8_t cur_kana_tbl = 0;
const uint16_t * KANATBL(void) {
    if(cur_kana_tbl) {
        return KANA_TBL_JP;
    } else  {
        return KANA_TBL;
    }
}

void set_kana_mode(uint8_t modef) {
    cur_kana_tbl = modef;
}

static const uint16_t MEMCLASS KANA_YOUON_TBL[] = {
    0,
    LSFT(KC_3),LSFT(KC_E),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),
    LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),
};

static bool send_kana(const uint16_t* tbl,uint8_t idx) {
    return send_key( mem_read_word(tbl,idx) );
}

static bool send_youon_key(KANA_t kch) {
    uint16_t code = kch >> 8;
    if( code == 0 ) { return false; }
    return send_kana( KANA_YOUON_TBL, code);
}


bool type_kana(KANA_t kch) {
    bool typed = false;
    switch( kch ) {
        case KANA___:return false;
        case KANA__A ... KANA_GRP1_MAX:
            return send_kana(KANATBL(),kch-KANA__A +2);
            break;
        
        case KANA_KIGOU ... KANA_MAX:
            return send_kana_kigou(kch);

        default:
            typed = type_kana( kch & KANA_GRP1_MAX );
            if( kch & KANA_daku ) {
                typed  |= send_kana(KANATBL(),0);
            } else if( kch & KANA_hndk ) {
                typed  |= send_kana(KANATBL(),1);
            }
            typed  |=  send_youon_key(kch);
            return typed;
    }
}

#else
    #define type_kana type_romaji
#endif

//
// Romaji
//
static const char MEMCLASS ROMAJI_TBL0[] = "aiueo";
static const char MEMCLASS ROMAJI_TBL1[] = "kstnhmyrw";
static const char MEMCLASS ROMAJI_TBL2[] = "gzd b   v";
static const char MEMCLASS ROMAJI_TBL3[] = "auo";

static bool send_romaji(uint16_t kch) {
    char buf[5];
    char* p = buf;
    
    uint8_t consonant = (kch & KP_MASK_1) / 5;
    uint8_t vowel = (kch & KP_MASK_1) % 5;
    uint8_t youon = (kch & KP_MASK_YOUON) >> 9;
    if( 2 <= consonant ) {
        consonant-=2;
        switch( kch & KP_MASK_HNDK ) {
            case KANA_daku:
                *p++ = mem_read_byte(ROMAJI_TBL2,consonant);
                break;
            case KANA_hndk:
                *p++ = 'p';
                break;
            default:
                *p++ = mem_read_byte(ROMAJI_TBL1,consonant);
        }
    }
    if( youon == 0 ) {
        *p++ = mem_read_byte(ROMAJI_TBL0,vowel);
    }
    else {
        if( 6 <=youon ) {
            if(consonant==0)
                *p++ = 'l';
            *p++ = 'y';
            *p++ = mem_read_byte(ROMAJI_TBL3,youon-6);
        }
    }
    //
    if( p == buf ) { return false; }
    *p++ = 0;
    send_string(buf);
    return true;
}

typedef struct {
    uint16_t code;
    const char *str;
} KanaToStr_t;

KanaToStr_t const romaji_to_str[] = {
    //{KANA_daku,"DAKU"},
    //{KANA_hndk,"HNDK"},
    {KANA_SPC," "},
    {KANA_COMM,","},
    {KANA_DOT,"."},
    {KANA_SLSH,"/"},
    {KANA_MINS,"-"},
    {KANA__a  ,"la"},
    {KANA__i  ,"li"},
    {KANA__u  ,"lu"},
    {KANA__e  ,"le"},
    {KANA__o  ,"lo"},
    {KANA_FA  ,"fa"},
    {KANA_FI  ,"fi"},
    {KANA_FU  ,"fu"},
    {KANA_FE  ,"fe"},
    {KANA_FO  ,"fo"},       
    {KANA_VA  ,"va"},
    {KANA_VI  ,"vi"},
    {KANA_VU  ,"vu"},
    {KANA_VE  ,"ve"},
    {KANA_VO  ,"vo"},
    {KANA_NN  ,"nn"},
    {KANA_tu  ,"ltu"},
    {KANA_wa  ,"lwa"},
    {KANA_SYE ,"sye"},
    {KANA_ULI ,"uli"},
    {KANA_ULE ,"ule"},
    {KANA_ULO ,"ulo"},
    {KANA_DELI,"deli"},
    {KANA_DEYU,"deyu"},
    {KANA_DOLU,"dolu"}, 
    {KANA_TOLU,"tolu"},
    {KANA_TILI,"tili"},
    {KANA_TILE,"tile"},
    {KANA_TELI,"teli"},
    {KANA_TULA,"tula"},
    {KANA_TULI,"tuli"},
    {KANA_TULE,"tule"},
    {KANA_TULO,"tulo"},
};

bool type_romaji(KANA_t kch) {
    const char* pout = NULL;
    switch( kch ) {
        case KANA___:return false;
        case KANA_KIGOU ... KANA_MAX:
            return send_romaji_kigou(kch);
        default:
            for(uint8_t i=0;i<sizeof(romaji_to_str)/sizeof(KanaToStr_t);i++) {
                if( romaji_to_str[i].code == kch ) {
                    pout = romaji_to_str[i].str;
                    break;
                }
            }
            if( pout ) { break; }
        
            return send_romaji(kch);
    }
    if(pout) { send_string(pout); }
    
    return true;
}
