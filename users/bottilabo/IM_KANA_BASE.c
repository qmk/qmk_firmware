#pragma once

/* Copyright 2018-2019 bottilabo <@bottinabo>
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
	# ぼっちラボ製　かな入力基本機能

*/

#include <string.h>

#include "kana-type.c"
#include "IM_KANA_BASE.h"

#ifndef NO_REPORT
#include <stdio.h>
#endif

typedef struct _kana_base_t {
    uint16_t keycode;
    uint16_t pressed;
    uint16_t released;
    uint16_t pressing;
    int16_t  press_cnt;
    int16_t  moratorium;
    int16_t  stkin;
    KANA_t   type_buf;

    kana_base_param_t* param;
    uint16_t (*key_bit)(uint16_t keycode);
    KANA_t (*key_kana)(uint16_t kits,uint16_t keycode);
    bool (*process_post_type)(KANA_t prev,KANA_t ch,KANA_t* pnch);
    bool (*determinable_kana)(int8_t evid,KANA_t ch);
} kana_base_t;

static kana_base_t _kana_base = {0,0,0,0,0,0,0,0};

static bool kana_base_process_post_type(KANA_t prev,KANA_t ch,KANA_t* pnch) {
    return false;
}

static bool kana_base_determinable_kana(int8_t evid,KANA_t ch) {
    switch( (uint16_t)ch ) {
        case KANA_daku:
        case KANA_hndk:
            return false;
        default:
            return true;
    }
}

void kana_base_connect(
    kana_base_param_t* param,
    uint16_t (*key_bit)(uint16_t keycode),
    KANA_t (*key_kana)(uint16_t bits,uint16_t keycode),
    bool (*process_post_type)(KANA_t prev,KANA_t ch,KANA_t* pnch),
    bool (*determinable_kana)(int8_t evid,KANA_t ch)
) {
    _kana_base.param = param;
    _kana_base.key_bit = key_bit;
    _kana_base.key_kana = key_kana;

    if( process_post_type == NULL )
        process_post_type = kana_base_process_post_type;
    _kana_base.process_post_type = process_post_type;

    if( determinable_kana == NULL )
        determinable_kana = kana_base_determinable_kana;
    _kana_base.determinable_kana = determinable_kana;
}


bool is_kana_base_mode(void) {
    return _kana_base.param->enabled;
}

static bool kana_base_set_flg(uint16_t keycode,uint16_t bit,KANA_t kana) {
    if(bit) {
        _kana_base.pressed |= bit;
        _kana_base.pressing |= bit;
        return true;
    }
    if( !kana )
        return false;

    if( _kana_base.keycode == 0 ) {
        _kana_base.keycode = keycode;
        return true;
    }

    return false;
}

static void kana_base_clear(void) {
    _kana_base.keycode = 0;
    _kana_base.pressed = 0;
    _kana_base.released = 0;
}

void kana_base_reset(void) {
    kana_base_clear();
    _kana_base.pressing = 0;
    _kana_base.type_buf = 0;
    _kana_base.press_cnt = 0;
}

void IM_KANA_BASE_enable(bool tf) {
    kana_base_reset();
    _kana_base.param->enabled = tf;
    if(tf) {
        transkeycode_set(NULL,"KANA_BASE IM");
    }
}

void kana_base_type_buf(KANA_t tch) {
    uint16_t ch = tch;

    if( ch == 0 )
        return;

    if( ch == KANA_max ) {
        ch = _kana_base.type_buf;
    }
    // 後置の濁音、半濁音処理
    //else if( ch == KANA_daku || ch == KANA_hndk ) {
    //    ch |= _kana_base.type_buf;
    //}
    else if( _kana_base.type_buf == 0) {
        _kana_base.type_buf = ch;
        return;
    }
    else {
        KANA_t nch;
        if( _kana_base.process_post_type(_kana_base.type_buf,ch,&nch) ) {
            ch = 0;
        } else {
            nch = _kana_base.type_buf;
        }

        if( _harmonize.type_mode )
            type_kana( nch );
        else
            type_romaji( nch );
        _kana_base.type_buf = ch;
        return;
    }

    if( _harmonize.type_mode )
        type_kana( ch );
    else
        type_romaji( ch );

    _kana_base.type_buf = 0;
}

// 今の条件で一文字出力する
static bool kana_base_type(void) {
    KANA_t kana;

    // 単打もしくは同時押し
    kana = _kana_base.key_kana(_kana_base.pressed|_kana_base.pressing,_kana_base.keycode);
    //kana = _kana_base.key_kana(_kana_base.pressed,_kana_base.keycode);

    // 同時押しの濁音、半濁音処理
    if( (_kana_base.pressed&KANA_BASE_DAKU) || (_kana_base.pressing&KANA_BASE_DAKU) )
        kana |= KANA_daku;
    else if( (_kana_base.pressed&KANA_BASE_HNDK) || (_kana_base.pressed&KANA_BASE_HNDK) ) 
        kana |= KANA_hndk;

    bool lsp = (_kana_base.pressed & KANA_BASE_LSHIFT) && (_kana_base.released & KANA_BASE_LSHIFT);
    bool rsp = (_kana_base.pressed & KANA_BASE_RSHIFT) && (_kana_base.released & KANA_BASE_RSHIFT);
    if( kana == 0 ) {
        if(lsp && rsp) {
            kana = K_KANA_DSFT;
        } else if(lsp) {
            kana = K_KANA_LSFT;
        } else if(rsp) {
            kana = K_KANA_RSFT;
        }
    }

    kana_base_type_buf(kana);
    kana_base_clear();
    return kana;
} 

static bool kana_base_key(uint16_t keycode,bool pressed) {
    uint16_t bit = _kana_base.key_bit(keycode);
    KANA_t kana = _kana_base.key_kana(_kana_base.pressed|_kana_base.pressing,keycode);
    bool f = bit || kana;

    if(!f) {
        return false;
    }

	if (pressed) {
        // modifierでない場合
        if( bit == 0 )
            _kana_base.press_cnt++;

        // 新しいパラメーターを設定すると矛盾する場合は、出力
        if( ! kana_base_set_flg(keycode,bit,kana) ) {
            kana_base_type();

            // 次に続く文字が後置として影響しない場合は確定
            if( _kana_base.determinable_kana(1,kana) ) {
                kana_base_type_buf(KANA_max);
            }

            // 新しい文字のパラメーターを設定
            kana_base_set_flg(keycode,bit,kana);
            _kana_base.stkin = 0;
        } else {
            // 一文字目の文字がそれ単体で確定する場合
            // 次に続く文字が後置として影響しない場合は確定
            if( _kana_base.determinable_kana(0,kana) ) {
                kana_base_type();
                kana_base_type_buf(KANA_max);
            }
        }
    } else {
        _kana_base.released |= bit;
		_kana_base.pressing &= ~bit;

        // modifierでない場合
        if( bit == 0 )
            _kana_base.press_cnt--;

        switch( _kana_base.param->kintype ) {
            case 1: 
                if( _kana_base.stkin == 0 ) {
                    _kana_base.stkin = _kana_base.param->stkin_term;
                }
            break;
            
            case 2: 
                if( _kana_base.press_cnt == 0 && _kana_base.stkin == 0 ) {
                    _kana_base.stkin = _kana_base.param->stkin_term;
                }
            break;


            default:
                if( _kana_base.press_cnt == 0 ) {
                    _kana_base.stkin = _kana_base.param->stkin_term;
                }
        }//switch
    }
    return true;
}

const int8_t modetbl[] MEMCLASS = {0,1,2};
const int8_t paramtbl[] MEMCLASS = {3,6,10,15,20,30,40,50,60};
int8_t next_param_val(const int8_t* tbl,uint8_t sz,int8_t val) {
    for(uint8_t i=0;i<sz;i++) {
        uint8_t p = mem_read_byte(tbl,i);
        //char buf[24];
        //snprintf(buf,sizeof(buf),"# %d < %d\n",val,p);
        //send_string(buf);
        if(val < p )
            return p;
    }
    return mem_read_byte(tbl,0);
}

bool process_kana_base(uint16_t keycode, keyrecord_t *record) {
    if( is_kana_base_mode() ) {
        if(_kana_base.stkin) {
            _kana_base.stkin-=TICKMS;
            if(_kana_base.stkin<=0) {
                kana_base_type();
                _kana_base.stkin = 0;
                _kana_base.moratorium = _kana_base.param->moratorium_term;
            }
        }
        else if(_kana_base.moratorium) {
            _kana_base.moratorium-=TICKMS;
            if(_kana_base.moratorium<=0) {
                _kana_base.moratorium=0;
                kana_base_type_buf(KANA_max);
            }
        }

        if( keycode == 0 ) return true;

        if( record->event.pressed ) {
            bool report = false;
            switch(keycode) {
                case K_AJ_P1:
                    _kana_base.param->stkin_term=next_param_val(paramtbl,sizeof(paramtbl)/sizeof(int8_t),_kana_base.param->stkin_term/5)*5;
                    report = true;
                    break;
                case K_AJ_P2:
                    _kana_base.param->moratorium_term=next_param_val(paramtbl,sizeof(paramtbl)/sizeof(int8_t),_kana_base.param->moratorium_term/5)*5;
                    report = true;
                    break;
                case K_AJ_P3:
                    _kana_base.param->kintype=next_param_val(modetbl,sizeof(modetbl)/sizeof(int8_t),_kana_base.param->kintype);
                    report = true;
                    break;
                case K_REPRT:
                    report = true;
                    break;
            }
            if( report ) {
#ifndef NO_REPORT
                char buf[24];
                snprintf(buf,sizeof(buf),"moratorium:%d\n",_kana_base.param->moratorium_term);
                send_string(buf);
                snprintf(buf,sizeof(buf),"stkin:%d\n",_kana_base.param->stkin_term);
                send_string(buf);
                snprintf(buf,sizeof(buf),"kintype:%d\n",_kana_base.param->kintype);
                send_string(buf);
#endif
                return true;
            }
        }

        return ! kana_base_key(keycode,record->event.pressed);
    }

    return true;
}

