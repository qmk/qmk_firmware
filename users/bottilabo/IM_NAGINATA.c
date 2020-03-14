/* Copyright 2019 bottilabo [twitter @bottinabo]
 *                          [https://github.com/bottilabo/qmk_harmonize]
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
 
/*
    # ぼっちラボ製「薙刀式」
    - 高速入力時のロールオーバー打鍵に対応しています。
    
    # reference
    - 大岡俊彦「薙刀式」
        http://oookaworks.seesaa.net/article/456099128.html
    - eswai「crkbd用 薙刀式日本語入力キーマップ」
        https://github.com/eswai/qmk_firmware/tree/master/keyboards/crkbd/keymaps/naginata
*/


#include QMK_KEYBOARD_H
#include "IM_NAGINATA.h"


#include "kana-type.c"

#define KANA_BUF_SZ 5

typedef struct {
    bool enabled;
    bool mod_shift;
    uint16_t press_cnt;
    uint16_t mod_cnt;
    uint16_t time_max;
    uint16_t time_pressed;
    uint16_t time_released;
    
    uint8_t chrcount;
    uint32_t keycomb;
    uint32_t keyreleased;
    int8_t candidate_idx;
    uint32_t candidate[KANA_BUF_SZ];
} naginata_t;
static naginata_t _naginata = {false,false,0,0,NAGINATA_TERM,0,0,   0,0UL,0UL,  0};



static const uint8_t PROGMEM naginata_layout[] = TRANSKEYCODE_DEF( \
    Q,   W,   E,   R,LEFT, RIGHT,   U,   I,   O,   P, \
    A,   S,   D,   F,   G,     H,   J,   K,   L,SCLN, \
    Z,   X,   C,   V,   B,     N,   M,COMM, DOT,SLSH );

#define NAGINATA_KBIT_A    (1UL<<0)
#define NAGINATA_KBIT_B    (1UL<<1)
#define NAGINATA_KBIT_C    (1UL<<2)
#define NAGINATA_KBIT_D    (1UL<<3)
#define NAGINATA_KBIT_E    (1UL<<4)

#define NAGINATA_KBIT_F    (1UL<<5)
#define NAGINATA_KBIT_G    (1UL<<6)
#define NAGINATA_KBIT_H    (1UL<<7)
#define NAGINATA_KBIT_I    (1UL<<8)
#define NAGINATA_KBIT_J    (1UL<<9)

#define NAGINATA_KBIT_K    (1UL<<10)
#define NAGINATA_KBIT_L    (1UL<<11)
#define NAGINATA_KBIT_M    (1UL<<12)
#define NAGINATA_KBIT_N    (1UL<<13)
#define NAGINATA_KBIT_O    (1UL<<14)

#define NAGINATA_KBIT_P    (1UL<<15)
#define NAGINATA_KBIT_Q    (1UL<<16)
#define NAGINATA_KBIT_R    (1UL<<17)
#define NAGINATA_KBIT_S    (1UL<<18)
#define NAGINATA_KBIT_T    (1UL<<19)

#define NAGINATA_KBIT_U    (1UL<<20)
#define NAGINATA_KBIT_V    (1UL<<21)
#define NAGINATA_KBIT_W    (1UL<<22)
#define NAGINATA_KBIT_X    (1UL<<23)
#define NAGINATA_KBIT_Y    (1UL<<24)

#define NAGINATA_KBIT_Z    (1UL<<25)
#define NAGINATA_KBIT_COMM (1UL<<26)
#define NAGINATA_KBIT_DOT  (1UL<<27)
#define NAGINATA_KBIT_SLSH (1UL<<28)
#define NAGINATA_KBIT_SCLN (1UL<<29)

#define NAGINATA_KBIT_SHFT (1UL<<30)
//#define NAGINATA_KBIT_RSFT (1UL<<31)


#define NAGINATA_CH_A     NAGINATA_KBIT_J
#define NAGINATA_CH_I     NAGINATA_KBIT_K
#define NAGINATA_CH_U     NAGINATA_KBIT_L
#define NAGINATA_CH_E     NAGINATA_KBIT_O
#define NAGINATA_CH_O     NAGINATA_KBIT_N
#define NAGINATA_CH_YA    NAGINATA_KBIT_H
#define NAGINATA_CH_YU    NAGINATA_KBIT_P
#define NAGINATA_CH_YO    NAGINATA_KBIT_I

#define NAGINATA_CH_SHFT  NAGINATA_KBIT_SHFT
#define NAGINATA_CH_LDSH  NAGINATA_KBIT_F
#define NAGINATA_CH_LHSH  NAGINATA_KBIT_V
#define NAGINATA_CH_RDSH  NAGINATA_KBIT_J
#define NAGINATA_CH_RHSH  NAGINATA_KBIT_M

#define MASK_SHIFT (0xc0000000)


typedef struct {
    uint32_t bits;
    uint16_t code;
} NAGINATA_BitsToCode_t;



uint32_t naginata_key_bit(uint16_t keycode) {
    if( keycode < KC_A ) return 0;
    if( keycode <= KC_Z ) return (1UL << (keycode - KC_A) );
    switch(keycode) {
        case KC_COMM:return NAGINATA_KBIT_COMM;
        case KC_DOT:return NAGINATA_KBIT_DOT;
        case KC_SLSH:return NAGINATA_KBIT_SLSH;
        case KC_SCLN:return NAGINATA_KBIT_SCLN;
        case K_TL0:
        case K_TR0:
		return NAGINATA_KBIT_SHFT;
    }
    return 0;
}


#define DEF_NAGINATA(MODL,MODR,Q,W,E,R,T,Y,U,I,O,P, A,S,D,F,G,H,J,K,L,SCLN, Z,X,C,V,B,N,M,COMM,DOT,SLSH) \
    {MODL|NAGINATA_KBIT_A,KANA_##A},{MODL|NAGINATA_KBIT_B,KANA_##B}      ,{MODL|NAGINATA_KBIT_C,KANA_##C}      ,{MODL|NAGINATA_KBIT_D,KANA_##D}    ,{MODL|NAGINATA_KBIT_E,KANA_##E}, \
    {MODL|NAGINATA_KBIT_F,KANA_##F},{MODL|NAGINATA_KBIT_G,KANA_##G}      ,{MODR|NAGINATA_KBIT_H,KANA_##H}      ,{MODR|NAGINATA_KBIT_I,KANA_##I}    ,{MODR|NAGINATA_KBIT_J,KANA_##J}, \
    {MODR|NAGINATA_KBIT_K,KANA_##K},{MODR|NAGINATA_KBIT_L,KANA_##L}      ,{MODR|NAGINATA_KBIT_M,KANA_##M}      ,{MODR|NAGINATA_KBIT_N,KANA_##N}    ,{MODR|NAGINATA_KBIT_O,KANA_##O}, \
    {MODR|NAGINATA_KBIT_P,KANA_##P},{MODL|NAGINATA_KBIT_Q,KANA_##Q}      ,{MODL|NAGINATA_KBIT_R,KANA_##R}      ,{MODL|NAGINATA_KBIT_S,KANA_##S}    ,{MODL|NAGINATA_KBIT_T,KANA_##T}, \
    {MODR|NAGINATA_KBIT_U,KANA_##U},{MODL|NAGINATA_KBIT_V,KANA_##V}      ,{MODL|NAGINATA_KBIT_W,KANA_##W}      ,{MODL|NAGINATA_KBIT_X,KANA_##X}    ,{MODR|NAGINATA_KBIT_Y,KANA_##Y}, \
    {MODL|NAGINATA_KBIT_Z,KANA_##Z},{MODR|NAGINATA_KBIT_SCLN,KANA_##SCLN},{MODR|NAGINATA_KBIT_COMM,KANA_##COMM},{MODR|NAGINATA_KBIT_DOT,KANA_##DOT},{MODR|NAGINATA_KBIT_SLSH,KANA_##SLSH}


static const NAGINATA_BitsToCode_t const naginata_codes_1[] PROGMEM = {
        //
        {NAGINATA_KBIT_F | NAGINATA_KBIT_J,KANA_GA},
        {NAGINATA_KBIT_V | NAGINATA_KBIT_J,KANA_GO},

        DEF_NAGINATA(0,0, \
            __, KI, TE, SI, __,   __, __, RU, SU, HE, \
            RO, HI, TO, KA, tu,   KU, _A, _I, _U, MINS, \
            HO, KE, HA, KO, SO,   TA, NA, NN, RA, RE \
        ),

        // 外来音
        {NAGINATA_KBIT_DOT | NAGINATA_CH_A,KANA_FA},
        {NAGINATA_KBIT_DOT | NAGINATA_CH_I,KANA_FI},
        {NAGINATA_KBIT_DOT | NAGINATA_CH_E,KANA_FE},
        {NAGINATA_KBIT_DOT | NAGINATA_CH_O,KANA_FO},

        {NAGINATA_KBIT_R | NAGINATA_CH_E,KANA_SYE},
        {NAGINATA_KBIT_E | NAGINATA_CH_I,KANA_TELI},

        {NAGINATA_CH_U | NAGINATA_CH_I,KANA_ULI},
        {NAGINATA_CH_U | NAGINATA_CH_E,KANA_ULE},
        {NAGINATA_CH_U | NAGINATA_CH_O,KANA_ULO},
        {NAGINATA_KBIT_D | NAGINATA_CH_U,KANA_TOLU},
        {NAGINATA_KBIT_G | NAGINATA_CH_E,KANA_TILE},

        // 拗音同時
        {NAGINATA_KBIT_W | NAGINATA_CH_YA,KANA_KYA},
        {NAGINATA_KBIT_W | NAGINATA_CH_YU,KANA_KYU},
        {NAGINATA_KBIT_W | NAGINATA_CH_YO,KANA_KYO},
        {NAGINATA_KBIT_R | NAGINATA_CH_YA,KANA_SYA},
        {NAGINATA_KBIT_R | NAGINATA_CH_YU,KANA_SYU},
        {NAGINATA_KBIT_R | NAGINATA_CH_YO,KANA_SYO},
        {NAGINATA_KBIT_G | NAGINATA_CH_YA,KANA_TYA},
        {NAGINATA_KBIT_G | NAGINATA_CH_YU,KANA_TYU},
        {NAGINATA_KBIT_G | NAGINATA_CH_YO,KANA_TYO},
        {NAGINATA_KBIT_S | NAGINATA_CH_YA,KANA_HYA},
        {NAGINATA_KBIT_S | NAGINATA_CH_YU,KANA_HYU},
        {NAGINATA_KBIT_S | NAGINATA_CH_YO,KANA_HYO},
        {NAGINATA_KBIT_D | NAGINATA_CH_YA,KANA_NYA},
        {NAGINATA_KBIT_D | NAGINATA_CH_YU,KANA_NYU},
        {NAGINATA_KBIT_D | NAGINATA_CH_YO,KANA_NYO},
        {NAGINATA_KBIT_B | NAGINATA_CH_YA,KANA_MYA},
        {NAGINATA_KBIT_B | NAGINATA_CH_YU,KANA_MYU},
        {NAGINATA_KBIT_B | NAGINATA_CH_YO,KANA_MYO},
        {NAGINATA_KBIT_E | NAGINATA_CH_YA,KANA_RYA},
        {NAGINATA_KBIT_E | NAGINATA_CH_YU,KANA_RYU},
        {NAGINATA_KBIT_E | NAGINATA_CH_YO,KANA_RYO},

        //{NAGINATA_KBIT_F|NAGINATA_CH_SHLR,KANA_daku},
        //{NAGINATA_KBIT_V|NAGINATA_CH_SHLR,KANA_hndk},

};

static const NAGINATA_BitsToCode_t const naginata_codes_2[] PROGMEM = {
        // 小書き
        {NAGINATA_KBIT_Q | NAGINATA_CH_A,KANA__a},
        {NAGINATA_KBIT_Q | NAGINATA_CH_I,KANA__i},
        {NAGINATA_KBIT_Q | NAGINATA_CH_U,KANA__u},
        {NAGINATA_KBIT_Q | NAGINATA_CH_E,KANA__e},
        {NAGINATA_KBIT_Q | NAGINATA_CH_O,KANA__o},
        {NAGINATA_KBIT_Q | NAGINATA_CH_U|NAGINATA_KBIT_SHFT,KANA_wa},

};

static const NAGINATA_BitsToCode_t const naginata_codes_3[] PROGMEM = {
        // シフト
        DEF_NAGINATA(NAGINATA_CH_SHFT,NAGINATA_CH_SHFT, \
            __, NE, RI, ME , __,     __, SA , YO, _E, YU, \
            SE, NU, NI, MA , TI,     YA, NO , MO, WA, TU, \
            __, __, WO,COMM, MI,     _O, DOT, MU, HU, __ \
        ),

        // 外来音
        {NAGINATA_KBIT_R | NAGINATA_CH_E | NAGINATA_CH_RDSH,KANA_JE},
        {NAGINATA_KBIT_E | NAGINATA_CH_I | NAGINATA_CH_LDSH,KANA_DELI},
        //{NAGINATA_KBIT_F | NAGINATA_CH_U | NAGINATA_CH_SHR,KANA_DELU},

        // 拗音
        {NAGINATA_CH_LHSH | NAGINATA_CH_YA,KANA_ya},
        {NAGINATA_CH_LHSH | NAGINATA_CH_YU,KANA_yu},
        {NAGINATA_CH_LHSH | NAGINATA_CH_YO,KANA_yo},

        // 濁音
        DEF_NAGINATA(NAGINATA_CH_RDSH,NAGINATA_CH_LDSH, \
            __, GI, DE, JI , __,     __, ZA , __, ZU, BE, \
            ZE, BI, DO, GA , DI,     GU, __ , __, VU, DU, \
            BO, GE, BA, GO , ZO,     DA, __ , __, BU, __ \
        ),


        // 半濁音
        {NAGINATA_CH_RHSH | NAGINATA_KBIT_C   ,KANA_PA},
        {NAGINATA_CH_RHSH | NAGINATA_KBIT_S   ,KANA_PI},
        {NAGINATA_CH_LHSH | NAGINATA_KBIT_SLSH,KANA_PU},
        {NAGINATA_CH_LHSH | NAGINATA_KBIT_P   ,KANA_PE},
        {NAGINATA_CH_RHSH | NAGINATA_KBIT_Z   ,KANA_PO},

        // 半濁音拗音同時
        {NAGINATA_CH_RHSH | NAGINATA_KBIT_S | NAGINATA_CH_YA,KANA_PYA},
        {NAGINATA_CH_RHSH | NAGINATA_KBIT_S | NAGINATA_CH_YU,KANA_PYU},
        {NAGINATA_CH_RHSH | NAGINATA_KBIT_S | NAGINATA_CH_YO,KANA_PYO},

        // 濁音拗音同時
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_W | NAGINATA_CH_YU,KANA_GYU},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_W | NAGINATA_CH_YO,KANA_GYO},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_R | NAGINATA_CH_YA,KANA_JYA},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_R | NAGINATA_CH_YU,KANA_JYU},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_R | NAGINATA_CH_YO,KANA_JYO},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_G | NAGINATA_CH_YA,KANA_DYA},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_G | NAGINATA_CH_YU,KANA_DYU},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_G | NAGINATA_CH_YO,KANA_DYO},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_S | NAGINATA_CH_YA,KANA_BYA},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_S | NAGINATA_CH_YU,KANA_BYU},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_S | NAGINATA_CH_YO,KANA_BYO},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_W | NAGINATA_CH_YA,KANA_GYA},


        // 外来音
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_L | NAGINATA_CH_A,KANA_VA},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_L | NAGINATA_CH_I,KANA_VI},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_L | NAGINATA_CH_E,KANA_VE},
        {NAGINATA_CH_RDSH | NAGINATA_KBIT_L | NAGINATA_CH_O,KANA_VO},

        {NAGINATA_CH_SHFT | NAGINATA_KBIT_SCLN | NAGINATA_CH_A,KANA_TULA},
        {NAGINATA_CH_SHFT | NAGINATA_KBIT_SCLN | NAGINATA_CH_I,KANA_TULI},
        {NAGINATA_CH_SHFT | NAGINATA_KBIT_SCLN | NAGINATA_CH_E,KANA_TULE},
        {NAGINATA_CH_SHFT | NAGINATA_KBIT_SCLN | NAGINATA_CH_O,KANA_TULO},

        // 濁音外来音
        {NAGINATA_CH_RDSH | NAGINATA_CH_I | NAGINATA_KBIT_E,KANA_DELI},
        {NAGINATA_CH_RDSH | NAGINATA_CH_U | NAGINATA_KBIT_D,KANA_DOLU},
        {NAGINATA_CH_RDSH | NAGINATA_CH_E | NAGINATA_KBIT_R,KANA_JE},
};


KANA_t naginata_combination_to_str(uint32_t bits) {
    if( true ) {
        NAGINATA_BitsToCode_t const* p = &naginata_codes_1[0];
        for(uint8_t i=0;i<sizeof(naginata_codes_1)/sizeof(NAGINATA_BitsToCode_t);i++,p++) {
            if( pgm_read_dword(&p->bits) == bits )
                return pgm_read_word(&p->code);
        }
    }

    if( true ) {
        NAGINATA_BitsToCode_t const* p = &naginata_codes_2[0];
        for(uint8_t i=0;i<sizeof(naginata_codes_2)/sizeof(NAGINATA_BitsToCode_t);i++,p++) {
            if( pgm_read_dword(&p->bits) == bits )
                return pgm_read_word(&p->code);
        }
    }

    if( true )
    {
        NAGINATA_BitsToCode_t const* p = &naginata_codes_3[0];
        for(uint8_t i=0;i<sizeof(naginata_codes_3)/sizeof(NAGINATA_BitsToCode_t);i++,p++) {
            if( pgm_read_dword(&p->bits) == bits )
                return pgm_read_word(&p->code);
        }
    }

    return KANA___;
}


KANA_t naginata_combination_to_str_3(uint32_t bits) {
    switch(bits) {
        case NAGINATA_CH_SHFT: return KANA_SPC;
    }
    return KANA___;
}

void naginata_reset(void) {
    naginata_clear();
    _naginata.keycomb = 0UL;
    _naginata.keyreleased = 0UL;
}

KANA_t naginata_kana(uint32_t pressed,uint32_t released) {
    KANA_t ch = naginata_combination_to_str(pressed);
    if( ch ) {
        return ch;
    }

    ch = naginata_combination_to_str_3( pressed & released );
    return ch;

}

inline bool naginata_type_char(KANA_t ch) {
    if( _harmonize.type_mode )
        return type_kana( ch );
    else
        return type_romaji( ch );
}

// 一連のキー入力を文字に直して出力する
bool naginata_type(void) {
    KANA_t buf[KANA_BUF_SZ];
    int8_t ci = _naginata.candidate_idx;
    int8_t bi = 0;
    bool ffound = false;
    uint32_t mod = 0;
    while( 0 < ci ) {
        for(int8_t j=0; j<ci; j++) {
            uint32_t keycomb = 0; 
            for(int8_t i = ci -1; j <= i; i--) {
                keycomb |= _naginata.candidate[i];
            }
            KANA_t k = naginata_kana(keycomb|mod,_naginata.keyreleased);
            if( k ) {
                buf[bi++] = k;
                ci = j;
                ffound = true;
                break;
            }
        }
        if( ! ffound )
            ci--;
    }

    bool typed = false;
    for(int8_t i = bi -1; 0 <= i; i--) {
        typed |= naginata_type_char(buf[i]);
    }

    naginata_clear();

    return typed;
}


// バッファをクリアする
void naginata_clear(void) {
    _naginata.chrcount = 0;
    _naginata.time_pressed = 0;
    _naginata.candidate_idx = 0;
    _naginata.keycomb &= MASK_SHIFT;
    _naginata.keyreleased = 0;
}


// 入力モードか編集モードかを確認する
void naginata_mode(uint16_t keycode, keyrecord_t *record) {
  if (!_naginata.enabled) return;

  // modifierが押されたらレイヤーをオフ
  switch (keycode) {
    case KC_LCTRL:
    //case KC_LSHIFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTRL:
    //case KC_RSHIFT:
    case KC_RALT:
    case KC_RGUI:
      if (record->event.pressed) {
        _naginata.mod_cnt++;
      } else {
        _naginata.mod_cnt--;
        if (_naginata.mod_cnt == 0) {
        }
      }
      break;
  }
}

void IM_NAGINATA_enable(uint8_t modef) {
    if( modef ) {
		_naginata.enabled = true;
		naginata_reset();

        transkeycode_set(naginata_layout,"IM NAGINATA");
    } else {
		_naginata.enabled = false;
		naginata_reset();
    }
}


// 薙刀式の入力処理
bool process_NAGINATA(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_LSHIFT:
        case KC_RSHIFT:
            if( ! record->event.pressed ) {
                if( _naginata.mod_shift )
                {
                    _naginata.mod_shift = false;
                    unregister_code(KC_LSHIFT);
                }
            }
        break;
    }

    naginata_mode(keycode,record);
    
    if (!_naginata.enabled )
        return true;
    
    if( keycode == 0 ) return true;

    if( _naginata.mod_cnt > 0) {
        transkeycode_reset();
        naginata_type();
        return true;
    }

    // naginata入力に関係なければフラッシュしてデフォルトの処理をさせる
    uint32_t bitcode = naginata_key_bit(keycode);
    if( !bitcode ) {
        naginata_type();
        if( _naginata.keycomb & NAGINATA_KBIT_SHFT ) {
            _naginata.mod_shift = true;
            register_code(KC_LSHIFT);
        }
        return true;
    }

  uint16_t now = timer_read();
  if (record->event.pressed) {

        bool update_time = true;
        switch( bitcode ) {
            case NAGINATA_KBIT_SHFT:
              update_time = false;
              break;
        }

        if( _naginata.time_pressed == 0 ) {
            if( update_time ) {
                _naginata.time_pressed = now;
            }
        }
        else {
            if( elapsed_time(now,_naginata.time_pressed) > _naginata.time_max ) {
                _naginata.time_pressed = now;
                naginata_type();
            }
        }

        _naginata.press_cnt++;
        _naginata.chrcount++;

        _naginata.keyreleased &= ~bitcode;
        _naginata.keycomb  |= bitcode;
        if( _naginata.candidate_idx < KANA_BUF_SZ ) {
            _naginata.candidate[ _naginata.candidate_idx++ ] = bitcode | (_naginata.keycomb & MASK_SHIFT);
        }
        return false;
  }
  // key release
  else {
        _naginata.keyreleased  |= bitcode;
        _naginata.press_cnt--;

        if (_naginata.chrcount > 0) {
            naginata_type();
        }
        _naginata.keycomb &= ~bitcode;
        _naginata.time_released = now;
        return false;
  }
  return true;
}


