#pragma once

// hikky配列   
#include "IM_ALPHA.c"

#define KC__  KC_TRNS
#define KC___ KC_TRNS

static alpha_base_param_t _hikky_param = {15,350,1,false};

static const ALPHA_BASE_CC_t const _hikky_cctbl0[] MEMCLASS = ALPHA_BASE_DEF(
  O,  R,  I,  N,  D, __, __, __, __, __,   \
  A,  T,  E,  H,  S, __, __, __, __, __,   \
  W,  M,  U,  C,  L, __, __, __, __, __,   \
 __,__,__,__,__,__
);

static const ALPHA_BASE_CC_t const _hikky_cctbl1[] MEMCLASS = ALPHA_BASE_DEF(
 __,  7,  8,  9, __, __, __, __, __, __,   \
 __,  4,  5,  6, __, __, __, __, __, __,   \
  0,  1,  2,  3, __, __, __, __, __, __,   \
 __,__,__,__,__,__
);


// W 9 4 4 4
// 6 U 3 4 6
// 3 2 C 1 6
// 4 3 2 L 9
// 7 7 7 9 M
static const uint16_t const _hikky_taptbl[] MEMCLASS = {
// W
    KC_W,KC_V,KC__,KC_Q,KC_COMM,
// M
    KC_K,KC_M,KC_G,KC_J,KC_DOT,
// U
    KC_X,KC_P,KC_U,KC_F,KC_SLSH,
// C
    KC_Z,KC_B,KC_Y,KC_C,KC_BSLS,
// L
    KC_MINS,KC_EQL,KC_QUOT,KC__,KC_L
};

static int8_t hikky_tapidx(uint16_t keycode) {
    switch(keycode) {
        case KC_W:return 0;
        case KC_M:return 1;
        case KC_U:return 2;
        case KC_C:return 3;
        case KC_L:return 4;
        default:return -1;
    }
}


static uint16_t hikky_key_bit(uint16_t keycode) {
    switch(keycode) {
        case KC_LSHIFT: return ALPHA_BASE_LSHIFT;
        case KC_RSHIFT:
        case KC_SPC:    return ALPHA_BASE_RSHIFT;
        default:        return 0;
    }
}

static ALPHA_t hikky_key_alpha(uint16_t bits,uint16_t keycode) {
    bool lsh = (bits & ALPHA_BASE_LSHIFT);
    bool rsh = (bits & ALPHA_BASE_RSHIFT);
    uint8_t tbl = lsh*1+rsh*2;

    ALPHA_BASE_CC_t const * p;
    uint8_t sz;
    switch(tbl){
        case 1:
            p = _hikky_cctbl1;
            sz = sizeof(_hikky_cctbl1)/sizeof(ALPHA_BASE_CC_t);
            break;
        default:
            p = _hikky_cctbl0;
            sz = sizeof(_hikky_cctbl0)/sizeof(ALPHA_BASE_CC_t);
            break;
    }
    for( uint8_t i=0; i<sz;i++) {
        if( keycode == mem_read_word(&p[i].code,0) )
            return mem_read_word(&p[i].alpha,0);
    }
    return 0;

}

bool hikky_process_post_type(ALPHA_t prev,ALPHA_t ch,ALPHA_t* pnch) {
    int8_t pi = hikky_tapidx(prev);
    int8_t ci = hikky_tapidx(ch);
    if( pi != -1 && ci != -1 ) {
        *pnch = mem_read_word(_hikky_taptbl,pi*5+ci);
        return true;
    }
    return false;
}

bool hikky_determinable_alpha(int8_t evid,ALPHA_t ch) {
    if( (KC_0 <= ch && KC_9 ) ) return true;
    if( hikky_tapidx(ch) == -1 ) return true;
    return false;
}

//
//

void IM_HIKKY_enable(uint8_t modef) {
    _hikky_param.enabled = modef;
    if( ! modef ) return;

    alpha_base_connect(
        &_hikky_param,
        hikky_key_bit,
        hikky_key_alpha,
        hikky_process_post_type,
        hikky_determinable_alpha
    );
    IM_ALPHA_BASE_enable(modef);
    transkeycode_set(NULL,"hikky");
}

bool process_HIKKY(uint16_t keycode, keyrecord_t *record) {
    if( ! _hikky_param.enabled )
        return true;
    return process_alpha_base(keycode,record);
}


