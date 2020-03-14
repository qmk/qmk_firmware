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

#include "IM_ALPHA.h"
#include "print.h"


typedef struct _alpha_base_t {
    uint16_t keycode;
    uint16_t pressed;
    uint16_t released;
    uint16_t pressing;
    int16_t  press_cnt;
    int16_t  moratorium;
    int16_t  stkin;
    ALPHA_t   type_buf;

    alpha_base_param_t* param;
    uint16_t (*key_bit)(uint16_t keycode);
    ALPHA_t (*key_alpha)(uint16_t kits,uint16_t keycode);
    bool (*process_post_type)(ALPHA_t prev,ALPHA_t ch,ALPHA_t* pnch);
    bool (*determinable_alpha)(int8_t evid,ALPHA_t ch);
} alpha_base_t;

static alpha_base_t _alpha_base = {0,0,0,0,0,0,0,0};

static void type_alpha(uint16_t code) {
    register_code16( code );
    unregister_code16( code );
}

static bool alpha_base_process_post_type(ALPHA_t prev,ALPHA_t ch,ALPHA_t* pnch) {
    return false;
}

static bool alpha_base_determinable_alpha(int8_t evid,ALPHA_t ch) {
    return true;
}

void alpha_base_connect(
    alpha_base_param_t* param,
    uint16_t (*key_bit)(uint16_t keycode),
    ALPHA_t (*key_alpha)(uint16_t bits,uint16_t keycode),
    bool (*process_post_type)(ALPHA_t prev,ALPHA_t ch,ALPHA_t* pnch),
    bool (*determinable_alpha)(int8_t evid,ALPHA_t ch)
) {
    _alpha_base.param = param;
    _alpha_base.key_bit = key_bit;
    _alpha_base.key_alpha = key_alpha;

    if( process_post_type == NULL )
        process_post_type = alpha_base_process_post_type;
    _alpha_base.process_post_type = process_post_type;

    if( determinable_alpha == NULL )
        determinable_alpha = alpha_base_determinable_alpha;
    _alpha_base.determinable_alpha = determinable_alpha;
}


bool is_alpha_base_mode(void) {
    return _alpha_base.param->enabled;
}

static bool alpha_base_set_flg(uint16_t keycode,uint16_t bit,ALPHA_t alpha) {
    if(bit) {
        _alpha_base.pressed |= bit;
        _alpha_base.pressing |= bit;
        return true;
    }
    if( !alpha )
        return false;

    if( _alpha_base.keycode == 0 ) {
        _alpha_base.keycode = keycode;
        return true;
    }

    return false;
}

static void alpha_base_clear(void) {
    _alpha_base.keycode = 0;
    _alpha_base.pressed = 0;
    _alpha_base.released = 0;
}

void alpha_base_reset(void) {
    alpha_base_clear();
    _alpha_base.pressing = 0;
    _alpha_base.type_buf = 0;
    _alpha_base.press_cnt = 0;
}

void IM_ALPHA_BASE_enable(bool tf) {
    alpha_base_reset();
    _alpha_base.param->enabled = tf;
    if(tf) {
        transkeycode_set(NULL,"ALPHA_BASE IM");
    }
}

void alpha_base_type_buf(ALPHA_t tch) {
    uint16_t ch = tch;

    if( ch == 0 )
        return;

    if( ch == ALPHA_max ) {
        ch = _alpha_base.type_buf;
    } else if( _alpha_base.type_buf == 0) {
        _alpha_base.type_buf = ch;
        return;
    } else {
        ALPHA_t nch;
        if( _alpha_base.process_post_type(_alpha_base.type_buf,ch,&nch) ) {
            ch = 0;
        }
        else {
            nch = _alpha_base.type_buf;
        }

        type_alpha( nch );
        _alpha_base.type_buf = ch;
        return;
    }

    type_alpha( ch );

    _alpha_base.type_buf = 0;
}

// 今の条件で一文字出力する
static bool alpha_base_type(void) {
    ALPHA_t alpha;

    // 単打もしくは同時押し
    alpha = _alpha_base.key_alpha(_alpha_base.pressed|_alpha_base.pressing,_alpha_base.keycode);
    //alpha = _alpha_base.key_alpha(_alpha_base.pressed,_alpha_base.keycode);

    bool lsp = (_alpha_base.pressed & ALPHA_BASE_LSHIFT) && (_alpha_base.released & ALPHA_BASE_LSHIFT);
    bool rsp = (_alpha_base.pressed & ALPHA_BASE_RSHIFT) && (_alpha_base.released & ALPHA_BASE_RSHIFT);
    if( alpha == 0 ) {
        if(lsp && rsp) {

        } else if(lsp) {
            alpha = K_ALPHA_LSFT;
        } else if(rsp) {
            alpha = K_ALPHA_RSFT;
        }
    }

    alpha_base_type_buf(alpha);
    alpha_base_clear();
    return alpha;
} 

static bool alpha_base_key(uint16_t keycode,bool pressed) {
    uint16_t bit = _alpha_base.key_bit(keycode);
    ALPHA_t alpha = _alpha_base.key_alpha(_alpha_base.pressed|_alpha_base.pressing,keycode);
    bool f = bit || alpha;

    if(!f) {
        return false;
    }

	if (pressed) {
        // modifierでない場合
        if( bit == 0 )
            _alpha_base.press_cnt++;

        // 新しいパラメーターを設定すると矛盾する場合は、出力
        if( ! alpha_base_set_flg(keycode,bit,alpha) ) {
            alpha_base_type();

            // 次に続く文字が後置として影響しない場合は確定
            if( _alpha_base.determinable_alpha(1,alpha) ) {
                alpha_base_type_buf(ALPHA_max);
            }

            // 新しい文字のパラメーターを設定
            alpha_base_set_flg(keycode,bit,alpha);
            _alpha_base.stkin = 0;
        }
        // 一文字目の文字がそれ単体で確定する場合
        else {
            // 次に続く文字が後置として影響しない場合は確定
            if( _alpha_base.determinable_alpha(0,alpha) ) {
                alpha_base_type();
                alpha_base_type_buf(ALPHA_max);
            }
        }
    } else {
        _alpha_base.released |= bit;
		_alpha_base.pressing &= ~bit;

        // modifierでない場合
        if( bit == 0 )
            _alpha_base.press_cnt--;

        switch( _alpha_base.param->kintype ) {
        case 1: 
            if( _alpha_base.stkin == 0 ) {
                _alpha_base.stkin = _alpha_base.param->stkin_term;
            }
        break;
        
        case 2: 
            if( _alpha_base.press_cnt == 0 && _alpha_base.stkin == 0 ) {
                _alpha_base.stkin = _alpha_base.param->stkin_term;
            }
        break;


        default:
            if( _alpha_base.press_cnt == 0 ) {
                _alpha_base.stkin = _alpha_base.param->stkin_term;
            }
        }//switch
    }
    return true;
}

bool process_alpha_base(uint16_t keycode, keyrecord_t *record) {
    if( is_alpha_base_mode() ) {
        if(_alpha_base.stkin) {
            _alpha_base.stkin-=TICKMS;
            if(_alpha_base.stkin<=0) {
                alpha_base_type();
                _alpha_base.stkin = 0;
                _alpha_base.moratorium = _alpha_base.param->moratorium_term;
            }
        }
        else if(_alpha_base.moratorium) {
            _alpha_base.moratorium-=TICKMS;
            if(_alpha_base.moratorium<=0) {
                _alpha_base.moratorium=0;
                alpha_base_type_buf(ALPHA_max);
            }
        }

        if( keycode == 0 ) return true;

        return ! alpha_base_key(keycode,record->event.pressed);
    }

    return true;
}

