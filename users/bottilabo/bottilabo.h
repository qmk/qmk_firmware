#pragma once

#ifdef __AVR__
#define USE_PROGMEM
#endif

#ifdef NO_PROGMEM
#undef USE_PROGMEM
#endif

#ifdef USE_PROGMEM

#include <avr/pgmspace.h>
#define MEMCLASS PROGMEM
#define mem_read_byte(X,Y) pgm_read_byte(X+Y)
#define mem_read_word(X,Y) pgm_read_word(X+Y)

#else

//#define pgm_read_byte(X) *(((const char*)(X)) )
//#define pgm_read_word(X) *(((const uint16_t*)(X)) )

#define MEMCLASS
#define mem_read_byte(X,Y) *(((const char*)(X))+Y )
#define mem_read_word(X,Y) *(((const uint16_t*)(X))+Y )
//#define mem_read_ptr(X,Y) *((void*) (((const char*)(X))+sizeof(void*)*Y ) )

#endif

#ifndef STKIN_TERM
#define STKIN_TERM 125
#endif

#ifndef MORATORIUM_TERM
#define MORATORIUM_TERM 350
#endif

#ifdef NO_MORATORIUM
#undef MORATORIUM_TERM
#define MORATORIUM_TERM 0
#endif

#ifndef TICKMS
#define TICKMS 1
#endif

#ifndef KOP_SFT
  #define KOP_SFT KC_LSFT
#endif


#define _______ KC_TRNS
#define IIIIIII KC_TRNS
//#define XXXXXXX KC_TRNS
#define HHHHHHH KC_TRNS
#define FFFFFFF KC_TRNS

//Friendly Layer Names
enum harmonix_layers {
  _MAIN = 0,
  _Lr1,
  _Ll1,
  _Lr2,
  _Ll2,
  _ADJ,
  _MUS,
};


#ifndef HARMONIZE_KEYCODES

#define HARMONIZE_KEYCODES

// custom keycodes
enum harmonix_keycodes {
  K_XIMMODE = SAFE_RANGE,
  K_SCLN,
  K_COMM,
  K_DOT,
  K_SLSH,
  K_BSSFT,
  K_LPRN,
  K_RPRN,
  K_REPRT,
  K_VOLUM,
  K_JPKB,
  K_ENKB,
  K_IM_EN,
  K_IM_JP,
  K_TKANA,
  K_TROMJ,
  K_KB_0,
  K_KB_1,
  K_KB_2,
  K_KB_3,
  K_IM_0,
  K_IM_1,
  K_IM_2,
  K_IM_3,
  K_WIN,
  K_MAC,
  K_LNX,
  RGBRST,
  RGBMOD,
  K_AJ_RST,
  K_AJ_P1,
  K_AJ_P2,
  K_AJ_P3,
  
  _USERKEY,
};

#endif

#define KC_MINM KC_KP_SLASH
#define KC_MAXM KC_KP_ASTERISK
#define KC_INCR KC_KP_PLUS
#define KC_DECR KC_KP_MINUS

#define IM_MAX_PLUG 4


enum {
    OS_WIN,
    OS_MAC,
    OS_LNX,
};

typedef struct {
    void (*enable)(uint8_t modef);
    bool (*process_record)(uint16_t keycode, keyrecord_t *record);
    uint8_t flags;
} im_plug_t;

typedef im_plug_t* im_plug_p;
typedef struct _Harmonize_t {
    im_plug_p im_p;

    uint16_t dbltap_term;

    uint8_t os_type;
    uint8_t lc_mode;
    uint8_t im_enabled;
    uint8_t type_mode; // 0:romaji 1:kana
    uint8_t kb_layout_id; 
    uint8_t im_id; 
} Harmonize_t;

extern Harmonize_t _harmonize;

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



bool is_im_enabled(void);
void im_select(uint8_t imid);
void im_mode_key(uint8_t modef,bool push);
void im_on_off(uint32_t modef);

void harmonize_init(void);
bool hamromize_process_record_user(uint16_t keycode, keyrecord_t *record);
void indicate_layer(const char* pstr);

#define HARMONIZE_MATRIX_SCAN_USER \
    { uint16_t keycode = 0;keyrecord_t record = {.event = TICK}; process_record_user(keycode,&record); }

#define HARMONIZE_PROC_RECORD_USER \
  if( !hamromize_process_record_user(keycode,record) ) return false;

#include "transkeycode.h"
void matrix_init_local(void);
void matrix_scan_local(void);
bool process_record_local(uint16_t keycode, keyrecord_t *record);
