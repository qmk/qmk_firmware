#pragma once

// 新JISかな配列
#include "IM_KANA_BASE.c"

static kana_base_param_t _sinjis_param = {15,350,1,false};

static const KANA_BASE_CC_t const _sinjis_cctbl0[] MEMCLASS = KANA_BASE_DEF1(
 SO, KE, SE, TE, yo, TU, NN, NO, WO, RI, TI,  \
 HA, KA, SI, TO, TA, KU, _U, _I,daku,KI, NA,  \
 SU, KO, NI, SA, _A, tu, RU,COMM,DOT,RE, __,  \
 ZENHAN,EISU,MHEN,SPC,HEN,KANA
);

static const KANA_BASE_CC_t const _sinjis_cctbl1[] MEMCLASS = KANA_BASE_DEF1(
 _a,hndk,HO, HU, ME, HI, _E, MI, YA, NU, LBRC,  \
 _i, HE, RA, yu, YO, MA, _O, MO, WA, YU, RBRC,  \
 _u, _e, _o, NE, ya, MU, RO,CDOT,MINS,__, __, \
 ZENHAN,EISU,MHEN,SPC,HEN,KANA
);

/*
static const KANA_BASE_CC_t const _sinjis_daku0[] MEMCLASS = KANA_BASE_DEF1(
 ZO, GE, ZE, DE, __, DU, __, __, __, __, DI,  \
 BA, GA, JI, DO, DA, GU, VU, __, __, GI, __,  \
 ZU, GO, __, ZA, __, __, __, __, __, __, __,  \
 ZENHAN,EISU,MHEN,SPC,HEN,KANA
);

static const KANA_BASE_CC_t const _sinjis_daku1[] MEMCLASS = KANA_BASE_DEF1(
 __, __, BO, BU, __, BI, __, __, __, __, LBRC,  \
 __, BE, __, __, __, __, __, __, __, __, RBRC,  \
 __, __, __, __, __, __, __, __, __, __, __, \
 ZENHAN,EISU,MHEN,SPC,HEN,KANA
);
*/

static uint16_t sinjis_key_bit(uint16_t keycode) {
    switch(keycode) {
        case K_TL0:    return KANA_BASE_LSHIFT;
        case K_TR0:    return KANA_BASE_RSHIFT;
        default:       return 0;
    }
}

static KANA_t sinjis_key_kana(uint16_t bits,uint16_t keycode) {
    bool lsh = (bits & KANA_BASE_LSHIFT);
    bool rsh = (bits & KANA_BASE_RSHIFT);
    uint8_t tbl = (lsh || rsh) * 1;

    KANA_BASE_CC_t const * p;
    uint8_t sz;
    switch(tbl){
        case 1:
            p = _sinjis_cctbl1;
            sz = sizeof(_sinjis_cctbl1)/sizeof(KANA_BASE_CC_t);
            break;

        case 0:
        default:
            p = _sinjis_cctbl0;
            sz = sizeof(_sinjis_cctbl0)/sizeof(KANA_BASE_CC_t);
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

void IM_SINJIS_enable(uint8_t modef) {
    _sinjis_param.enabled = modef;
    if( ! modef ) return;

    kana_base_connect(
        &_sinjis_param,
        sinjis_key_bit,
        sinjis_key_kana,
        NULL,
        NULL
    );
    IM_KANA_BASE_enable(modef);
    transkeycode_set(NULL,"ShinJIS");
}

bool process_SINJIS(uint16_t keycode, keyrecord_t *record) {
    if( ! _sinjis_param.enabled )
        return true;
    return process_kana_base(keycode,record);
}


