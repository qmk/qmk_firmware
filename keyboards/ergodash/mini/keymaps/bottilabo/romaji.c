#include <string.h>

#define G(X) _romaji_##X

enum Romaji {
    G(_A) = 0,
    G(_I),
    G(_U),
    G(_E),
    G(_O),
    G(_Y),
    G(_H),

    G(_SLASH),
    G(_NN),
    G(_MACRON),
    G(_SHIFT),
    G(_ARRAY_SIZE)
};

bool G(mode) = false;
static bool G(key_pressed)[G(_ARRAY_SIZE)];
static uint16_t G(shift_press_cnt) = 0;
static uint16_t G(press_cnt) = 0;
static uint16_t G(consonants) = 0;
static uint16_t G(time_max) = ROMAJI_TERM;
static uint16_t G(time_start) = 0;
static uint16_t G(mod_cnt) = 0;

static int romaji_key_idx(uint16_t keycode) {
    switch(keycode) {
        case KC_A:     return G(_A);
        case KC_I:     return G(_I);
        case KC_U:     return G(_U);
        case KC_E:     return G(_E);
        case KC_O:     return G(_O);
        case KC_Y:     return G(_Y);
        case KC_H:     return G(_H);
        case KC_SPACE: return G(_NN);
        case KC_LSHIFT:  return G(_SHIFT);
        case KC_RSHIFT:  return G(_SHIFT);
        case KC_MINS:    return G(_MACRON);
        case KC_SLASH:   return G(_SLASH);
        default:       return -1;
    }
}

static bool set_flg(uint16_t keycode) {
    static const bool pressed = true;

    int rmkidx = romaji_key_idx(keycode);
    if(rmkidx != -1) {
        G(key_pressed)[rmkidx] |= pressed;
        return true;
    }

    if(pressed) {
        if(G(consonants))
            return false;

        G(consonants) = keycode;
    }
    return true;
}

static void romaji_clear(void) {
    G(consonants) = 0;
    //memset( G(key_pressed)     ,0,sizeof(bool)*G(_Y) );
    memset( G(key_pressed)     ,0,sizeof(bool)*G(_ARRAY_SIZE) );
}

void romaji_reset(void) {
    G(press_cnt) = 0;
    G(shift_press_cnt) = 0;
    romaji_clear();
    //memset( G(key_pressed)     ,0,sizeof(bool)*G(_ARRAY_SIZE) );
}


static inline bool check_pressed(uint16_t kidx) {
    return G(key_pressed)[kidx];
}
static inline bool is_lower(char ch) {
    return 'a' <= ch && ch <= 'z';
}
static inline char to_lower(char ch) {
    if( is_lower(ch) )
        return ch;
    else
        return ch - 'A' + 'a';
}
//                                   "abcdefghijklmnopqrstuvwxyz";
static const char* G(shifted_chrs) = "     p b  g  N    zd      ";

static void romaji_flush(void) {
    char buf[16];
    char*p = buf;
    char ch = 0;
    bool fshift = check_pressed( G(_SHIFT) );
    if( G(consonants) == 0 ) {
        if( check_pressed( G(_H) ) ) {
            G(consonants) = KC_H;
            G(key_pressed)[ G(_H)  ] = false;
        }
    }
    if( G(consonants) != 0 ) {
        if( fshift  ) {
            char tch = G(shifted_chrs)[ G(consonants) - KC_A ];
            if( tch != ' ' )
                ch = tch;
        }
        else {
            ch = (char)( G(consonants) - KC_A + 'a');
        }
        *p++ = to_lower(ch);
        if( ! is_lower(ch) ) 
            *p++ = to_lower(ch);
    }
    if( check_pressed( G(_H) ) )    *p++ = 'h';
    if( check_pressed( G(_Y) ) )    *p++ = 'y';
    if( check_pressed( G(_A) ) )    *p++ = 'a';
    if( check_pressed( G(_O) ) )    *p++ = 'o';
    if( check_pressed( G(_U) ) )    *p++ = 'u';
    if( check_pressed( G(_E) ) )    *p++ = 'e';
    if( check_pressed( G(_I) ) )    *p++ = 'i';
    if( check_pressed( G(_MACRON) ) )    *p++ = '-';
    if( check_pressed( G(_SLASH) ) ) {
        if( fshift )
            *p++ = '?';
        else
            *p++ = '/';
    }
    if( check_pressed( G(_NN) ) ) {
        if( buf == p )
            *p++ = ' ';
        else {
            *p++ = 'n';
            *p++ = 'n';
        }
    }
    if( fshift && (buf == p - 1) && (buf[0] == 'n') )
        *p++ = ch;

    if(buf != p) {
        *p++ = 0;
        send_string(buf);
    }

    romaji_clear();

    // shiftの状態は継承する
    if( 0 < G(shift_press_cnt) )
        G(key_pressed)[ G(_SHIFT) ] |= true;
} 

static uint16_t elapsed_time(uint16_t a,uint16_t b) {
    if( a > b )
        return a - b;
    else
        return (uint16_t)( ((uint32_t)a) + 65535 - b);
}

static void romaji_modkey(uint16_t keycode,bool pressed) {
    if (pressed) {
        set_flg(keycode);
    }
    else {
        if( G(press_cnt) == 0 ) {
            romaji_flush();
        }
    }
}

static void romaji_key(uint16_t keycode,bool pressed) {
    if (pressed) {
        uint16_t now = timer_read();
        if( G(press_cnt) == 0 ) {
            G(time_start) = now;
        }
        else {
            if( elapsed_time(now,G(time_start)) > G(time_max) ) {
                G(time_start) = now;
                romaji_flush();
            }
        }

        G(press_cnt)++;
        if( ! set_flg(keycode) )
        {
            romaji_flush();
            set_flg(keycode);
        }
    }
    else {
        G(press_cnt)--;
        if( G(press_cnt) == 0 )
            romaji_flush();
    }
}

static void romaji_change_param(uint16_t id,int16_t val) {
    int32_t v = G(time_max);
    v += val*5;
    if(v<0)    v = 0;
    if(v>200)   v = 200;
    G(time_max) = (uint16_t)v;
}

static void romaji_report_param(void) {
    char buf[20];
    snprintf(buf,sizeof(buf),"time:%d\n",G(time_max));
    send_string(buf);
}


bool process_romaji(uint16_t keycode, keyrecord_t *record) {
    int d = -1;
    if (record->event.pressed) {
        switch(keycode) {
            case REPORT_PARAM:
                romaji_report_param();
                return false;
            case INC_PARAM:
              romaji_change_param(0,1);
              return false;
            case DEC_PARAM:
              romaji_change_param(0,-1);
              return false;
        }

        //
        d = 1;
    }

    // ctl,alt,modなどのキーが押されていたら、ローマ字の処理はしない
    switch(keycode) {
        case KC_LCTL:
        case KC_LALT:
        case KC_LGUI:
        case KC_RCTL:
        case KC_RALT:
        case KC_RGUI:
            if( record->event.pressed )
                G(mod_cnt)++;
            else
                G(mod_cnt)--;
            break; 

        case KC_LSFT:
        case KC_RSFT:
            G(shift_press_cnt) += d;
            break;
    }

    if( G(mod_cnt) != 0 )
        return true;
   

    //
    if( _romaji_mode ) {
        bool f = (KC_A <= keycode && keycode <= KC_Z);

        // ローマ字の修飾キー
        bool fmod = false;
        if( !f ) {
            switch(keycode) {
                case KC_SPACE:
                case KC_MINS:
                case KC_SLASH:
                case KC_LSHIFT:
                case KC_RSHIFT:
                    f = fmod = true;
                    break;
            }
        }
        // ローマ字と関係ない文字ならフラッシュ
        if( !f ) {
            if(record->event.pressed) {
                if( G(press_cnt) != 0 )
                    romaji_flush();
                romaji_clear();
            }
            return true;
        }

        if( f ) {
            if( fmod )
                romaji_modkey(keycode,record->event.pressed);
            else
                romaji_key(keycode,record->event.pressed);
        
            // shiftキーには通常の
            switch(keycode) {
                case KC_LSHIFT:
                case KC_RSHIFT:
                    return true;
            }

            return false;
        }
    }

    return true;
}


#undef G

