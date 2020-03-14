#pragma once

// nicola配列
#include "IM_KANA_BASE.c"

static kana_base_param_t _nicola_param = {15,1,0,false};

static const KANA_BASE_CC_t const _nicola_cctbl0[] MEMCLASS = KANA_BASE_DEF1(
DOT, KA, TA, KO, SA, RA, TI, KU, TU,COMM,COMM,  \
 _U, SI, TE, KE, SE, HA, TO, KI, _I, NN, __,  \
CDOT,HI, SU, HU, HE, ME, SO, NE, HO,SLSH,__,  \
 ZENHAN,EISU,MHEN,SPC,HEN,KANA
);

static const KANA_BASE_CC_t const _nicola_cctbl1[] MEMCLASS = KANA_BASE_DEF1(
 _a, _E, RI, ya, RE, PA, DI, GU, DU,  PI, __,  \
 WO, _A, NA, yu, MO, BA, DO, GI, PO,  __, __,  \
 _u,MINS,RO, YA, _i, PU, ZO, PE, BO,QSTN, __, \
 ZENHAN,EISU,MHEN,SPC,HEN,KANA
);

static const KANA_BASE_CC_t const _nicola_cctbl2[] MEMCLASS = KANA_BASE_DEF1(
 __, GA, DA, GO, ZA, YO, NI, RU, MA, _e, __,  \
 __, JI, DE, GE, ZE, MI, _O, NO, yo, tu, __,  \
 __, BI, ZU, BU, BE, NU, YU, MU, WA, _o, __, \
 ZENHAN,EISU,MHEN,SPC,HEN,KANA
);

static const KANA_BASE_CC_t const _nicola_cctbl3[] MEMCLASS = {};


static uint16_t nicola_key_bit(uint16_t keycode) {
        switch(keycode) {
        case K_TL0:    return KANA_BASE_LSHIFT;
        case K_TR0:    return KANA_BASE_RSHIFT;
        default:       return 0;
    }
}


static KANA_t nicola_key_kana(uint16_t bits,uint16_t keycode) {
    uint8_t lsh = (bits & KANA_BASE_LSHIFT) ? 1 : 0;
    uint8_t rsh = (bits & KANA_BASE_RSHIFT) ? 1 : 0;
    uint8_t tbl = lsh*1+rsh*2;

    KANA_BASE_CC_t const * p;
    uint8_t sz;
    switch(tbl){
        case 1:
            p = _nicola_cctbl1;
            sz = sizeof(_nicola_cctbl1)/sizeof(KANA_BASE_CC_t);
            break;
        case 2:
            p = _nicola_cctbl2;
            sz = sizeof(_nicola_cctbl2)/sizeof(KANA_BASE_CC_t);
            break;
        case 3:
            return 0;
        case 0:
        default:
            p = _nicola_cctbl0;
            sz = sizeof(_nicola_cctbl0)/sizeof(KANA_BASE_CC_t);
            break;                          
    }
    for( uint8_t i=0; i<sz;i++) {
        if( keycode == mem_read_word(&p[i].code,0) )
            return mem_read_word(&p[i].kana,0);
    }
    return KANA___;

}


//
//

void IM_NICOLA_enable(uint8_t modef) {
    _nicola_param.enabled = modef;
    if( ! modef ) return;

    kana_base_connect(
        &_nicola_param,
        nicola_key_bit,
        nicola_key_kana,
        NULL,
        NULL
    );
    IM_KANA_BASE_enable(modef);
    transkeycode_set(NULL,"Nicola");
}

bool process_NICOLA(uint16_t keycode, keyrecord_t *record) {
    if( ! _nicola_param.enabled )
        return true;
    return process_kana_base(keycode,record);
}


