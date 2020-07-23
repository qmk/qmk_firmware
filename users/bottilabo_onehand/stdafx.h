/* Copyright 2020 bottilabo [twitter @bottinabo]
 *                          [https://github.com/bottilabo/bottilabo_onehand]
 *
 * GNU General Public License version 3 [http://www.gnu.org/licenses/]
 */

#pragma once
//
typedef struct {
    void (*enable)(uint8_t modef);
    bool (*process_record)(uint16_t keycode, keyrecord_t *record);
    uint8_t flags;
} im_plug_t;

typedef im_plug_t* im_plug_p;

#ifdef __AVR__
#define USE_PROGMEM
#endif

#ifdef NO_PROGMEM
#undef USE_PROGMEM
#endif

#ifdef USE_PROGMEM

#include <avr/pgmspace.h>
#define mem_read_byte(X,Y) pgm_read_byte(X+Y)
#define mem_read_word(X,Y) pgm_read_word(X+Y)
#define mem_read_dword(X,Y) pgm_read_dword(X+Y)

#else

#define PROGMEM
#define mem_read_byte(X,Y) *(((const char*)(X))+Y )
#define mem_read_word(X,Y) *(((const uint16_t*)(X))+Y )
#define mem_read_dword(X,Y) *(((const uint32_t*)(X))+Y )

#endif

#define BOOLEAN(X) ((bool)((X)!=0))
typedef uint16_t tick_t;

inline bool send_key(uint16_t code) {
    if( code == 0 )
        return false;
    register_code16( code );
    unregister_code16( code );
    return true;
}
inline void send_key2(uint16_t code,uint16_t mod) {
    register_code16( mod );
    register_code16( code );
    unregister_code16( code );
    unregister_code16( mod );
}
inline void send_keycode(uint16_t code,uint8_t flg) {
    if( code == 0 )
        return;

    if( flg != 0 ) {
        register_code16( code );
    }
    if( flg == 0 || flg == 2 ) {
        unregister_code16( code );
    }
}
inline bool is_lower(char ch) {
    return 'a' <= ch && ch <= 'z';
}
inline char to_lower(char ch) {
    if( is_lower(ch) )
        return ch;
    else
        return ch - 'A' + 'a';
}
inline uint16_t elapsed_time(uint16_t a,uint16_t b) {
    if( a > b )
        return a - b;
    else
        return (uint16_t)( ((uint32_t)a) + 65535 - b);
}

