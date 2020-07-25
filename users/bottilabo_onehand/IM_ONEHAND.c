/* Copyright 2020 bottilabo [twitter @bottinabo]
 *                          [https://github.com/bottilabo/bottilabo_onehand]
 *
 * GNU General Public License version 3 [http://www.gnu.org/licenses/]
 */

#include "stdafx.h"
#include "IM_ONEHAND.h"



typedef uint16_t KEYCODE_t;
#define KC___ 0

onehand_t _onehand = {false,0,0,0,0,0,
    0,
    ONEHAND_TERM,0,0,   
    0,0UL,0UL,  0};

#define ONEHAND_KBIT_A    (1UL<<0)
#define ONEHAND_KBIT_B    (1UL<<1)
#define ONEHAND_KBIT_C    (1UL<<2)
#define ONEHAND_KBIT_D    (1UL<<3)
#define ONEHAND_KBIT_E    (1UL<<4)

#define ONEHAND_KBIT_F    (1UL<<5)
#define ONEHAND_KBIT_G    (1UL<<6)
#define ONEHAND_KBIT_H    (1UL<<7)
#define ONEHAND_KBIT_I    (1UL<<8)
#define ONEHAND_KBIT_J    (1UL<<9)

#define ONEHAND_KBIT_K    (1UL<<10)
#define ONEHAND_KBIT_L    (1UL<<11)
#define ONEHAND_KBIT_M    (1UL<<12)
#define ONEHAND_KBIT_N    (1UL<<13)
#define ONEHAND_KBIT_O    (1UL<<14)

#define ONEHAND_KBIT_P    (1UL<<15)
#define ONEHAND_KBIT_Q    (1UL<<16)
#define ONEHAND_KBIT_R    (1UL<<17)
#define ONEHAND_KBIT_S    (1UL<<18)
#define ONEHAND_KBIT_T    (1UL<<19)

#define ONEHAND_KBIT_U    (1UL<<20)
#define ONEHAND_KBIT_V    (1UL<<21)
#define ONEHAND_KBIT_W    (1UL<<22)
#define ONEHAND_KBIT_X    (1UL<<23)
#define ONEHAND_KBIT_Y    (1UL<<24)

#define ONEHAND_KBIT_Z    (1UL<<25)
#define ONEHAND_KBIT_COMM (1UL<<26)
#define ONEHAND_KBIT_DOT  (1UL<<27)
#define ONEHAND_KBIT_SLSH (1UL<<28)
#define ONEHAND_KBIT_SCLN (1UL<<29)

#define ONEHAND_KBIT_SHFT (1UL<<30)
#define ONEHAND_KBIT_AUXT (1UL<<31)


#define MASK_SHIFT (0xc0000000)


typedef struct {
    uint32_t bits;
    uint16_t code;
} ONEHAND_BitsToCode_t;



uint32_t onehand_key_bit(uint16_t keycode) {
    if( keycode < KC_A ) return 0;
    if( keycode <= KC_Z ) return (1UL << (keycode - KC_A) );
    switch(keycode) {
        case KC_COMM:return ONEHAND_KBIT_COMM;
        case KC_DOT:return ONEHAND_KBIT_DOT;
        case KC_SLSH:return ONEHAND_KBIT_SLSH;
        case KC_SCLN:return ONEHAND_KBIT_SCLN;
        case K_TL0:return ONEHAND_KBIT_SHFT;
        //case K_TL1:return ONEHAND_KBIT_AUXT;
    }
    return 0;
}


#define DEF_ONEHAND(MODL,MODR,Q,W,E,R,T,Y,U,I,O,P, A,S,D,F,G,H,J,K,L,SCLN, Z,X,C,V,B,N,M,COMM,DOT,SLSH) \
    {MODL|ONEHAND_KBIT_A,KC_##A},{MODL|ONEHAND_KBIT_B,KC_##B}        ,{MODL|ONEHAND_KBIT_C,KC_##C}      ,{MODL|ONEHAND_KBIT_D,KC_##D}    ,{MODL|ONEHAND_KBIT_E,KC_##E}, \
    {MODL|ONEHAND_KBIT_F,KC_##F},{MODL|ONEHAND_KBIT_G,KC_##G}        ,{MODR|ONEHAND_KBIT_H,KC_##H}      ,{MODR|ONEHAND_KBIT_I,KC_##I}    ,{MODR|ONEHAND_KBIT_J,KC_##J}, \
    {MODR|ONEHAND_KBIT_K,KC_##K},{MODR|ONEHAND_KBIT_L,KC_##L}        ,{MODR|ONEHAND_KBIT_M,KC_##M}      ,{MODR|ONEHAND_KBIT_N,KC_##N}    ,{MODR|ONEHAND_KBIT_O,KC_##O}, \
    {MODR|ONEHAND_KBIT_P,KC_##P},{MODL|ONEHAND_KBIT_Q,KC_##Q}        ,{MODL|ONEHAND_KBIT_R,KC_##R}      ,{MODL|ONEHAND_KBIT_S,KC_##S}    ,{MODL|ONEHAND_KBIT_T,KC_##T}, \
    {MODR|ONEHAND_KBIT_U,KC_##U},{MODL|ONEHAND_KBIT_V,KC_##V}        ,{MODL|ONEHAND_KBIT_W,KC_##W}      ,{MODL|ONEHAND_KBIT_X,KC_##X}    ,{MODR|ONEHAND_KBIT_Y,KC_##Y}, \
    {MODL|ONEHAND_KBIT_Z,KC_##Z},{MODR|ONEHAND_KBIT_SCLN,KC_##SCLN},{MODR|ONEHAND_KBIT_COMM,KC_##COMM},{MODR|ONEHAND_KBIT_DOT,KC_##DOT},{MODR|ONEHAND_KBIT_SLSH,KC_##SLSH}

static const ONEHAND_BitsToCode_t const onehand_codes_1[] PROGMEM = {
        DEF_ONEHAND(0,0, \
         COMM,   S,   U,  T,  P,   __, __, __, __, __, \
            A,   O,   E,  I,  C,   __, __, __, __, __,   \
          DOT,   X,MINS,  H,  J,   __, __, __, __, __ \
        ),

        {                    ONEHAND_KBIT_Q | ONEHAND_KBIT_W, KC_EXLM}, // 4 --...
        {                    ONEHAND_KBIT_A | ONEHAND_KBIT_S, KC_UNDS}, // 3 --...
        {                    ONEHAND_KBIT_Z | ONEHAND_KBIT_X, KC_QUES}, // 4 --...

        {                    ONEHAND_KBIT_W | ONEHAND_KBIT_E, KC_LBRC}, // 2 .--..
        {                    ONEHAND_KBIT_S | ONEHAND_KBIT_D, KC_LPRN}, // 2 .--..
        {                    ONEHAND_KBIT_X | ONEHAND_KBIT_C, KC_LCBR}, // 3 .--..

        {                    ONEHAND_KBIT_E | ONEHAND_KBIT_R, KC_W   }, // 2 ..--.
        {                    ONEHAND_KBIT_D | ONEHAND_KBIT_F, KC_Y   }, // 1 ..--.
        {                    ONEHAND_KBIT_C | ONEHAND_KBIT_V, KC_M   }, // 3 ..--.

        {                    ONEHAND_KBIT_R | ONEHAND_KBIT_T, KC_GRV},  // 3 ...--
        {                    ONEHAND_KBIT_F | ONEHAND_KBIT_G, KC_SLSH}, // 2 ...--
        {                    ONEHAND_KBIT_V | ONEHAND_KBIT_B, KC___  }, // 2 ...--

        {                    ONEHAND_KBIT_R | ONEHAND_KBIT_G, KC_AMPR}, // 2 ...\.
        {                    ONEHAND_KBIT_F | ONEHAND_KBIT_B, KC_CIRC}, // 3 ...\.

        {                    ONEHAND_KBIT_E | ONEHAND_KBIT_F, KC_QUOT}, // 1 ..\..
        {                    ONEHAND_KBIT_D | ONEHAND_KBIT_V, KC_SCLN}, // 2 ..\..

        {                    ONEHAND_KBIT_S | ONEHAND_KBIT_E, KC_AT  }, // 1 ./...
        {                    ONEHAND_KBIT_X | ONEHAND_KBIT_D, KC_HASH}, // 2 ./...
};

static const ONEHAND_BitsToCode_t const onehand_codes_2[] PROGMEM = {
};

static const ONEHAND_BitsToCode_t const onehand_codes_3[] PROGMEM = {
        // シフト
        DEF_ONEHAND(ONEHAND_KBIT_SHFT,ONEHAND_KBIT_SHFT, \
          LT  ,    Z,  V,  D,  F,   __, __, __, __, __, \
          L   ,    R,  N,ENT,  G,   __, __, __, __, __,   \
          GT  ,    Q,EQL,  B,  K,   __, __, __, __, __ \
        ),

        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_Q | ONEHAND_KBIT_W, KC___  }, // 4 --...
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_A | ONEHAND_KBIT_S, KC_PIPE}, // 3 --...
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_Z | ONEHAND_KBIT_X, KC___  }, // 4 --...

        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_W | ONEHAND_KBIT_E, KC_RBRC}, // 2 .--..
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_S | ONEHAND_KBIT_D, KC_RPRN}, // 2 .--..
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_X | ONEHAND_KBIT_C, KC_RCBR}, // 3 .--..

        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_E | ONEHAND_KBIT_R, KC_ASTR}, // 2 ..--.
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_D | ONEHAND_KBIT_F, KC_PLUS}, // 1 ..--.
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_C | ONEHAND_KBIT_V, KC___  }, // 3 ..--.

        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_R | ONEHAND_KBIT_T, KC_TILD}, // 3 ...--
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_F | ONEHAND_KBIT_G, KC_BSLS}, // 2 ...--
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_V | ONEHAND_KBIT_B, KC___  }, // 2 ...--

        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_R | ONEHAND_KBIT_G, KC___  }, // 2 ...\.
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_F | ONEHAND_KBIT_B, KC___  }, // 3 ...\.

        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_E | ONEHAND_KBIT_F, KC_DQT }, // 1 ..\..
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_D | ONEHAND_KBIT_V, KC_COLN}, // 2 ..\..

        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_S | ONEHAND_KBIT_E, KC_DLR },  // 1 ./...
        {ONEHAND_KBIT_SHFT | ONEHAND_KBIT_X | ONEHAND_KBIT_D, KC_PERC},  // 2 ./...
};


KEYCODE_t onehand_combination_to_str(uint32_t bits) {
    if( true ) {
        ONEHAND_BitsToCode_t const* p = &onehand_codes_1[0];
        for(uint8_t i=0;i<sizeof(onehand_codes_1)/sizeof(ONEHAND_BitsToCode_t);i++,p++) {
            if( mem_read_dword(&p->bits,0) == bits )
                return mem_read_word(&p->code,0);
        }
    }

    if( true ) {
        ONEHAND_BitsToCode_t const* p = &onehand_codes_2[0];
        for(uint8_t i=0;i<sizeof(onehand_codes_2)/sizeof(ONEHAND_BitsToCode_t);i++,p++) {
            if( mem_read_dword(&p->bits,0) == bits )
                return mem_read_word(&p->code,0);
        }
    }

    if( true )
    {
        ONEHAND_BitsToCode_t const* p = &onehand_codes_3[0];
        for(uint8_t i=0;i<sizeof(onehand_codes_3)/sizeof(ONEHAND_BitsToCode_t);i++,p++) {
            if( mem_read_dword(&p->bits,0) == bits )
                return mem_read_word(&p->code,0);
        }
    }

    return KC___;
}


KEYCODE_t onehand_combination_to_str_3(uint32_t bits) {
    switch(bits) {
        case ONEHAND_KBIT_SHFT: return KC_SPC;
        case ONEHAND_KBIT_AUXT: return KC_BSPC;
    }
    return KC___;
}

void onehand_reset(void) {
    onehand_clear();
    _onehand.keycomb = 0UL;
    _onehand.keyreleased = 0UL;
}

KEYCODE_t onehand_kana(uint32_t pressed,uint32_t released) {
    KEYCODE_t ch = onehand_combination_to_str(pressed);
    if( ch ) {
        return ch;
    }

    ch = onehand_combination_to_str_3( pressed & released );
    return ch;

}

bool onehand_type_char(KEYCODE_t ch,bool long_press) {

    // ROMAJI mode
    if( _onehand.im_mode == 2 ) {
        switch(ch){
        case KC_C:
            send_keycode(KC_K,2);
            break;
        case KC_X:
            send_keycode(KC_N,2);
            send_keycode(KC_N,2);
            break;
        case KC_Q:
            send_keycode(KC_L,2);
            send_keycode(KC_T,2);
            send_keycode(KC_U,2);
            break;
        case KC_L:
            if( _onehand.mod_shift || long_press ) {
                send_keycode(ch,2);
            }
            else {
                send_keycode(KC_N,2);
                send_keycode(KC_O,2);
            }
            break;
        case KC_W:
            if( _onehand.mod_shift || long_press ) {
                send_keycode(KC_W,2);
                send_keycode(KC_O,2);
            }
            else {
                send_keycode(KC_W,2);
                //send_keycode(KC_A,2);
            }
            break;
        default:
            send_keycode(ch,2);
        }
        
        if( _onehand.mod_shift || long_press ) {
            switch(ch ) {
                case KC_A:
                case KC_I:
                case KC_U:
                case KC_E:
                case KC_O:
                    send_keycode(KC_N,2);
                    send_keycode(KC_N,2);
                    break;
                case KC_C:
                case KC_K:
                case KC_G:
                case KC_S:
                case KC_Z:
                case KC_T:
                case KC_D:
                case KC_N:
                case KC_H:
                case KC_B:
                case KC_M:
                case KC_R:
                    send_keycode(KC_Y,2);
                    break;
            }
        }
    }
    // normal mode
    else {
        if( _onehand.mod_ctl ) {
            send_keycode(KC_LCTL,1);
        }
        if( _onehand.mod_alt ) {
            send_keycode(KC_LALT,1);
        }
        if( _onehand.mod_gui ) {
            send_keycode(KC_LGUI,1);
        }

        bool alphabet = (KC_A <= ch) && (ch <= KC_Z);
        bool fshift = long_press || (alphabet && _onehand.mod_shift != 0) || (!alphabet && _onehand.mod_shift == 1);
        if( fshift ) {
            send_keycode(KC_LSHIFT,1);
        }

        send_keycode(ch,2);

        if( fshift ) {
            send_keycode(KC_LSHIFT,0);
        }

        switch( _onehand.mod_shift ) {
            case 0:break;
            case 1:
                _onehand.mod_shift = 0;
        }
        switch( _onehand.mod_ctl ) {
            case 0:break;
            case 1:
                _onehand.mod_ctl = 0;
            default:
                send_keycode(KC_LCTL,0);
        }
        switch( _onehand.mod_alt ) {
            case 0:break;
            case 1:
                _onehand.mod_alt = 0;
            default:
                send_keycode(KC_LALT,0);
        }
        switch( _onehand.mod_gui ) {
            case 0:break;
            case 1:
                _onehand.mod_gui = 0;
            default:
                send_keycode(KC_LGUI,0);
        }
    }
      
    return true;
}

// 一連のキー入力を文字に直して出力する
bool onehand_type(bool long_press) {
    KEYCODE_t buf[ONEHAND_KANA_BUF_SZ];
    int8_t ci = _onehand.candidate_idx;
    int8_t bi = 0;
    bool ffound = false;
    uint32_t mod = 0;
    while( 0 < ci ) {
        for(int8_t j=0; j<ci; j++) {
            uint32_t keycomb = 0; 
            for(int8_t i = ci -1; j <= i; i--) {
                keycomb |= _onehand.candidate[i];
            }
            KEYCODE_t k = onehand_kana(keycomb|mod,_onehand.keyreleased);
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
        typed |= onehand_type_char(buf[i],long_press);
    }

    onehand_clear();

    return typed;
}


// バッファをクリアする
void onehand_clear(void) {
    _onehand.chrcount = 0;
    _onehand.time_pressed = 0;
    _onehand.candidate_idx = 0;
    _onehand.keycomb &= MASK_SHIFT;
    _onehand.keyreleased = 0;
}


void IM_ONEHAND_enable(uint8_t modef) {
    if( modef ) {
		_onehand.enabled = true;
		onehand_reset();
        _onehand.im_mode = modef;
    } else {
		_onehand.enabled = false;
		onehand_reset();
        _onehand.im_mode = 0;
    }
}


/*
tick_t check_pressing_time(uint16_t keycode,bool press) {
    static uint8_t keyct = 0;
    static tick_t prev_tick = 0;

    if(keycode>255)
        return 0;

    if( press ) {
        if(keyct == 0)
            prev_tick = timer_read();

        keyct++;
    }
    else {
        keyct--;

        if( keyct == 255 )
            keyct = 0;

        if( keyct == 0 ) {
            return elapsed_time( timer_read(),prev_tick );
        }
    }

    return 0;
}
*/

bool process_ONEHAND(uint16_t keycode, keyrecord_t *record) {
    if (!_onehand.enabled )
        return true;

    if( keycode == 0 ) return true;

    bool pressed = record->event.pressed;

    // MODキーの処理
    switch(keycode) {
        case KC_RSFT:
        case KC_RCTL:
        case KC_RALT:
        case KC_RGUI:
            if( pressed ) {
                bool dbltap = check_dbltap(keycode);
                switch(keycode) {
                    case KX__SFT:
                        switch( _onehand.mod_shift ) {
                        case 0:
                            _onehand.mod_shift++;
                            break;
                        default:
                            _onehand.mod_shift = 2 * dbltap;
                        }
                    break;
                    case KX__CTL:
                        switch( _onehand.mod_ctl ) {
                        case 0:
                            _onehand.mod_ctl++;
                            break;
                        default:
                            _onehand.mod_ctl = 2 * dbltap;
                        }
                    break;
                    case KX__ALT:
                        switch( _onehand.mod_alt ) {
                        case 0:
                            _onehand.mod_alt++;
                            break;
                        default:
                            _onehand.mod_alt = 2 * dbltap;
                        }
                    break;
                    case KX__GUI:
                        switch( _onehand.mod_gui ) {
                        case 0:
                            _onehand.mod_gui++;
                            break;
                        default:
                            _onehand.mod_gui = 2 * dbltap;
                        }
                    break;
                }
            }
            return false;
    }

    // onehand入力に関係なければフラッシュしてデフォルトの処理をさせる
    uint32_t bitcode = onehand_key_bit(keycode);
    if( !bitcode ) {
        onehand_type(false);
        return true;
    }

    bool kmod = (bitcode == ONEHAND_KBIT_SHFT) || (bitcode == ONEHAND_KBIT_AUXT);

    tick_t now = timer_read();
    if (pressed) {

        bool update_time = true;
        if( kmod )
              update_time = false;

        if( _onehand.time_pressed == 0 ) {
            if( update_time ) {
                _onehand.time_pressed = now;
            }
        }
        else {
            tick_t elapsed = elapsed_time(now,_onehand.time_pressed);
            if( elapsed  > _onehand.time_max ) {
                if( update_time ) {
                    _onehand.time_pressed = now;
                }
                else {
                    _onehand.time_pressed = 0;
                }
                onehand_type(false);
            }
        }

        if( !kmod ) {
            _onehand.press_cnt++;
        }
        _onehand.chrcount++;

        _onehand.keyreleased &= ~bitcode;
        _onehand.keycomb  |= bitcode;
        if( _onehand.candidate_idx < ONEHAND_KANA_BUF_SZ ) {
            _onehand.candidate[ _onehand.candidate_idx++ ] = bitcode | (_onehand.keycomb & MASK_SHIFT);
        }
        return false;
    }
    // key release
    else {
        _onehand.keyreleased  |= bitcode;
        if( !kmod ) {
            _onehand.press_cnt--;
        }

        // when something wrong
        if( _onehand.press_cnt == 255 )
            _onehand.press_cnt = 0;

        if (_onehand.chrcount > 0 && _onehand.press_cnt == 0 ) {
            bool long_press = elapsed_time(now,_onehand.time_pressed) > LONGPRESS_TERM;
            if( _onehand.time_pressed == 0 )
                long_press = false;
            onehand_type( long_press );
        }
        _onehand.keycomb &= ~bitcode;
        _onehand.time_released = now;
        return false;
    }
    return true;
}


