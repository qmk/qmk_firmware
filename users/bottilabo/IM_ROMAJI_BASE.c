/* Copyright 2019,2020 bottilabo [twitter @bottinabo]
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
 

#pragma once
#include <string.h>

#include "IM_ROMAJI_BASE.h"

typedef struct _romaji_base_t {
    volatile bool mode;
    uint8_t press_cnt;
    uint8_t press_cnt_max;
    uint16_t time_max;
    uint16_t time_start;
    bool mod_shift;
    uint16_t keycode;
    uint16_t press;
    uint16_t pressing;

    //
    uint16_t (*key_to_bits)(uint16_t keycode);
    char (*compose_char)(uint16_t keycode,uint16_t kbits);
    char* (*char_to_str)(char* p,char ch);
    char* (*bits_to_str)(char* p,uint16_t bits);
} romaji_base_t;

static romaji_base_t _romaji_base = {false,0,0,ROMAJI_BASE_TERM,0,false,0,0,0};


void romaji_base_connect(
    uint16_t (*key_to_bits)(uint16_t keycode),
    char (*compose_char)(uint16_t keycode,uint16_t kbits),
    char* (*char_to_str)(char* p,char ch),
    char* (*bits_to_str)(char* p,uint16_t bits)
) {
    _romaji_base.key_to_bits = key_to_bits;
    _romaji_base.compose_char = compose_char;
    _romaji_base.char_to_str = char_to_str;
    _romaji_base.bits_to_str = bits_to_str;
}

// 同時押しキーへの変換
uint16_t romaji_base_key_to_bits(const ROMAJI_BASE_KEYCODE_BIT_t* tbl,uint8_t sz,uint16_t keycode) {
    for( uint8_t i=0; i<sz;i++) {
        if( mem_read_word(&tbl[i].keycode,0) == keycode ) return mem_read_word(&tbl[i].bit,0);
    }
    return 0;
}

// bits,keycodeから文字に変換
char romaji_base_code_to_char(const ROMAJI_BASE_CODE_CHAR_t* tbl,uint8_t sz,uint16_t code) {
    for( uint8_t i=0; i<sz;i++) {
        if( code == mem_read_word(&tbl[i].code,0) ) {
            return mem_read_byte( &tbl[i].c,0);
        }
    }
    return 0;
}

char* romaji_base_char_to_str(const ROMAJI_BASE_CC_t* tbl,uint8_t sz,char* p,char ch) {
    for( uint8_t i=0; i<sz;i++) {
        if( ch == mem_read_word(&tbl[i].code,0) ) {
            for(uint8_t j=0;j<2;j++) {
                char c = mem_read_byte( &tbl[i].ch2[j],0);
                if(c)
                    *p++ = c;
            }
            //break;
        }
    }
    return p;
}

char* romaji_base_bits_to_str(const ROMAJI_BASE_CC_t* tbl,uint8_t sz,char* p,uint16_t bits) {
    for( uint8_t i=0; i<sz;i++) {
        if( ( bits & mem_read_word(&tbl[i].code,0) ) ) {
            for(uint8_t j=0;j<2;j++) {
                char c = mem_read_byte(&tbl[i].ch2[j],0);
                if(c)
                    *p++ = c;
            }
        }
    }
    return p;
}

//                                                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ-,./[]\'";
const char* const ROMAJI_BASE_SHIFTED_CHRS MEMCLASS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_<>?    ";
const char* const ROMAJI_BASE_DAKUON_CHRS MEMCLASS  = "A g Ev bI g   Of  zdU v   _<>?    ";

// 単打キーキーから文字への変換
static const ROMAJI_BASE_CODE_CHAR_t const _romaji_base_keycode_chr[] MEMCLASS = {
    {KC_MINS,'-'},
    {KC_COMM,','},
    {KC_DOT ,'.'},
    {KC_SLSH,'/'},
    {KC_QUOT,','},
    {KC_BSLS,'\\'},
    {KC_LBRC,'['},
    {KC_RBRC,']'},
};

static uint8_t romaji_base_keycode_chr(uint16_t keycode) {
    if( KC_A <= keycode && keycode <= KC_Z )
        return 'a' + keycode - KC_A;
    for( uint8_t i=0; i<sizeof(_romaji_base_keycode_chr)/sizeof(ROMAJI_BASE_CODE_CHAR_t);i++) {
        if( mem_read_word(&_romaji_base_keycode_chr[i].code,0) == keycode ) return mem_read_byte(&_romaji_base_keycode_chr[i].c,0);
    }
    return 0;    
}

static char* ROMAJI_BASE_extra_keys = "-,./[]\\'";

char romaji_base_compose_char(const char* tbl,bool fshift,uint16_t keycode,char ch) {
    if( ch == 0 )
        ch = romaji_base_keycode_chr(keycode);

    // 濁音
    if( fshift  ) {
        if( 'a' <= ch && ch <= 'z' )
            ch = tbl[ ch - 'a' ];
        else
            for(uint8_t i=0;i<sizeof(ROMAJI_BASE_extra_keys);i++) {
                if(ROMAJI_BASE_extra_keys[i] == ch) {
                    ch = tbl[26 + i];
                    break;
                }
            }
    }
    return ch;
}

//

bool is_romaji_base_mode(void) {
    return _romaji_base.mode;
}

static bool romaji_base_set_flg(uint16_t keycode) {
    uint16_t bit = _romaji_base.key_to_bits(keycode);
    if(bit) {
        _romaji_base.press |= bit;
        _romaji_base.pressing |= bit;
        return true;
    }

    if( _romaji_base.keycode == 0 ) {
        _romaji_base.keycode = keycode;
        return true;
    }

    return false;
}

static void romaji_base_clear(void) {
    _romaji_base.keycode = 0;
    _romaji_base.press = 0;
}

void romaji_base_reset(void) {
    _romaji_base.press_cnt = 0;
    _romaji_base.press_cnt_max = 0;
    romaji_base_clear();
    _romaji_base.pressing = 0;
}

void IM_ROMAJI_BASE_enable(bool tf) {
    romaji_base_reset();
    _romaji_base.mode = tf;
}

static bool romaji_base_flush(void) {
    char tbuf[8];
    char*buf = &tbuf[0];
    char*p = buf;
    char ch = _romaji_base.compose_char(_romaji_base.keycode,_romaji_base.press|_romaji_base.pressing);

    if( ch != 0 ) {

        // 文字から文字列を生成
        char *pp = p;
        p = _romaji_base.char_to_str(p,ch);
        if( pp == p ) {
            switch(ch) {
                case ' ':
                    break;
                default:
                    *p++ = ch;
            }
        }
    }

    // 同時押しキーから文字列を生成
    p = _romaji_base.bits_to_str(p,_romaji_base.press);

    // 文字列を出力
    bool fout = (buf != p);
    if( fout ) {
        *p++ = 0;
        send_string(buf);
    } else {
        //else if( _romaji_base.press_cnt == 0 ) {
        // 文字列がない時、スペースの処理
        if( (_romaji_base.press & ROMAJI_BASE_SPC) ) {
            send_string(" ");
        }
    }
    romaji_base_clear();
    return fout;
}


static void romaji_base_key(uint16_t keycode,bool pressed) {
    uint16_t now = timer_read();
    uint16_t bit = _romaji_base.key_to_bits(keycode);
    if (pressed) {
        bool update_time = true;
        //if( bit == ROMAJI_BASE_LSHIFT || bit == ROMAJI_BASE_RSHIFT )
        //    update_time = false;

        if( update_time ) {
            if( _romaji_base.press_cnt == 0 ) {
                _romaji_base.time_start = now;
            } else {
                if( elapsed_time(now,_romaji_base.time_start) > _romaji_base.time_max ) {
                    _romaji_base.time_start = now;
                    romaji_base_flush();
                }
            }
        }

        _romaji_base.press_cnt++;
        if( _romaji_base.press_cnt_max < _romaji_base.press_cnt )
            _romaji_base.press_cnt_max = _romaji_base.press_cnt;

        if( ! romaji_base_set_flg(keycode) ) {
            romaji_base_flush();
            romaji_base_set_flg(keycode);
        }
    } else {
        _romaji_base.press_cnt--;
        _romaji_base.pressing &= ~bit;
        if( _romaji_base.press_cnt == 0 )
            romaji_base_flush();
    }
}


bool process_romaji_base(uint16_t keycode, keyrecord_t *record) {
    if( keycode == 0 )
        return true;

    /*
    switch(keycode) {
        case KC_LSHIFT:
        case KC_RSHIFT:
            if( ! record->event.pressed ) {
                if( _romaji_base.mod_shift )
                {
                    _romaji_base.mod_shift = false;
                    unregister_code(KC_LSHIFT);
                }
            }
        break;
    }
*/


    if( is_romaji_base_mode() ) {
        bool f = romaji_base_keycode_chr(keycode);
        bool fmod = _romaji_base.key_to_bits(keycode);

/*        
        // ローマ字と関係ない文字ならフラッシュ
        if( !f && !fmod && !_romaji_base.mod_shift) {
            if(record->event.pressed) {
                bool fshift = romaji_base_check_pressed( ROMAJI_BASE_SHIFT );
                if( _romaji_base.press_cnt != 0 ) {
                    bool fout = romaji_base_flush();
                    if( fshift && (!fout) ) {
                        _romaji_base.mod_shift = true;
                    }
                }
                else {
                    _romaji_base.mod_shift = fshift;
                }
                if( _romaji_base.mod_shift )
                    register_code(KC_LSHIFT);

                romaji_base_clear();
            }
            return true;
        }
*/

        if( !f && !fmod ) {
            //romaji_base_flush();
            return true;
        }

        romaji_base_key(keycode,record->event.pressed);
        return false;
    }

    return true;
}

