#include "keymap_jp.h"

#ifndef NO_REPORT
#include <stdio.h>
#endif

void DEFAULTIM_enable(uint8_t modef) {
}

bool DEFAULTIM_PROC(uint16_t keycode, keyrecord_t *record) {
    return true;
}
static im_plug_t DEFAULTIM_PLUG = {DEFAULTIM_enable,DEFAULTIM_PROC};
Harmonize_t _harmonize = {
    &DEFAULTIM_PLUG,250,OS_WIN,0,0,0,0,0
};


#include "transkeycode.c"


#define _ADD_PLUG(X) X ## _PLUG
#define ADD_PLUG(X) _ADD_PLUG(X)

#ifdef KBIM1
    #define KBIM1S INCLUDEFILE(KBIM1)
    #include KBIM1S
    #define KBIM1_PLUG ADD_PLUG(KBIM1)
#else
    #define KBIM1 DEFAULTIM
    #define KBIM1_PLUG DEFAULTIM_PLUG
#endif

#ifdef KBIM2
    #define KBIM2S INCLUDEFILE(KBIM2)
    #include KBIM2S
    #define KBIM2_PLUG ADD_PLUG(KBIM2)
#else
    #define KBIM2 DEFAULTIM
    #define KBIM2_PLUG DEFAULTIM_PLUG
#endif

#ifdef KBIM3
    #define KBIM3S INCLUDEFILE(KBIM3)
    #include KBIM3S
    #define KBIM3_PLUG ADD_PLUG(KBIM3)
#else
    #define KBIM3 DEFAULTIM
    #define KBIM3_PLUG DEFAULTIM_PLUG
#endif

typedef union {
    uint32_t u32;
    uint8_t u8[4];
} u32bytes_t;


const im_plug_p im_plugins[IM_MAX_PLUG] = {&DEFAULTIM_PLUG,&KBIM1_PLUG,&KBIM2_PLUG,&KBIM3_PLUG};

void im_enable(uint8_t modef) {
    transkeycode_reset();

    _harmonize.im_enabled = modef;
    _harmonize.im_p->enable(modef);
}

bool is_im_enabled(void) {
    return _harmonize.im_enabled;
}

void im_select(uint8_t imid) {
    _harmonize.im_p = im_plugins[imid%IM_MAX_PLUG];
}

void harmonize_reset(void) {
   im_enable(false);
}

void im_on_off(uint32_t modef) {
    harmonize_reset();
    im_enable(modef);
}

static void keyonoff(bool on,uint16_t kc) {
    if(on) register_code(kc);
    else   unregister_code(kc);
}

void im_mode_key(uint8_t modef,bool push) {
/*
    switch( _harmonize.os_type )
    {
        case OS_WIN:
            if(push) {
                SEND_STRING(SS_LALT("`"));
            }
        break;

        default:
        {
            uint16_t kc = KC_LANG2;
            if( modef ) {
                kc = KC_LANG1;
            }
            keyonoff(push,kc);
        }
        break;

    }
*/
    if(push) {
        SEND_STRING(SS_LALT("`"));
    }
}

static inline bool is_lc_mode(void) {
    return _harmonize.lc_mode;
}

static inline void im_toggle(void) {
    bool imonoff = ! is_im_enabled();
    im_mode_key(imonoff,true);
    im_mode_key(imonoff,false);
    im_on_off(imonoff);
}

void init_state(void) {
    for(uint8_t i=1;i<16;i++)
        layer_off(i);
    layer_on(0);
    im_on_off(false);
}

void harmonize_save(void) {
    u32bytes_t dat;
    dat.u8[0] = _harmonize.os_type;
    dat.u8[1] = _harmonize.kb_layout_id;
    dat.u8[2] = _harmonize.im_id;
    dat.u8[3] = _harmonize.type_mode;
    eeconfig_update_user( dat.u32);
}

void harmonize_load(void) {
    u32bytes_t dat;
    dat.u32 = eeconfig_read_user();
    _harmonize.os_type = dat.u8[0];
    _harmonize.kb_layout_id = dat.u8[1];
    _harmonize.im_id = dat.u8[2];
    _harmonize.type_mode = dat.u8[3];
    im_select(_harmonize.im_id);
    select_kb_layout(dat.u8[1]);
    im_on_off(false);
}

bool hamromize_process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;

    XKEY_PROC;
/*
    if( keycode != 0 && !record->event.pressed ) {
        if( _xkey.last_released_key == KC_ESC ) {
            if( 6000 < _longpress.duration ) {
                //send_string("6000");
                reset_keyboard();
                return true;
            }
            else if( 3000 < _longpress.duration ) {
                //send_string("3000");
                init_state();
                return true;
            }
        }

        if( _xkey.last_released_key == K_XIMMODE ) {
            bool imonoff = ! is_im_enabled();
            switch( _renda.consecutive_count ) {
                case 0:return true;

                // toggle
                case 1: break;

                // off
                case 2:  imonoff = false; break;

                // on
                case 3:  imonoff = true; break;

                default: return true;
            }
            im_mode_key(imonoff,true);
            im_mode_key(imonoff,false);
            im_on_off(imonoff);
        }

        switch( _renda.consecutive_count ) {
            case 1:
                if( (_xkey.last_released_key == KC_LALT || _xkey.last_released_key == KC_RALT ) ) {
                    im_toggle();
                    return true;
                }
                break;

            case 2:
                if( _xkey.last_released_key == KC_ESC ) {
                    im_mode_key(false,true);
                    im_mode_key(false,false);
                    im_on_off(false);
                    return true;
                }
                break;
        }
    }
*/

    if( _harmonize.im_enabled ) {
        if(!_harmonize.im_p->process_record(keycode,record))
            return false;
    }

    //

    switch(_harmonize.lc_mode) {
        case 1: {
            uint16_t newkc = 0;
            switch(keycode) {
                //case KC_LPRN:newkc = JP_LPRN;break;
                //case KC_RPRN:newkc = JP_RPRN;break;
                case KC_LBRC:newkc = JP_LBRC;break;
                case KC_RBRC:newkc = JP_RBRC;break;
                //case KC_QUOT:newkc = JP_COLN;break;
                case KC_GRV: newkc = JP_AT;break;
                case KC_BSLS:newkc = JP_YEN;break;
            }
            if(newkc) {
                keyonoff(pressed,newkc);
                return false;
            }

            if(pressed ) {
                const char* str = NULL;
                switch(keycode) {
                    case K_LPRN:str = "*";break;
                    case K_RPRN:str = "(";break;
                }
                if(str) {
                    send_string(str);
                    return false;
                }
            }
        }
        break;

        default: {
            if(pressed ) {
                const char* str = NULL;
                switch(keycode) {
                    case K_LPRN:str = "(";break;
                    case K_RPRN:str = ")";break;
                }
                if(str) {
                    send_string(str);
                    return false;
                }
            }
        }
    }

    if( pressed ) {
        switch(keycode) {
          case K_REPRT: {
#ifndef NO_REPORT
                char buf[32];
                char *str_os[]={"win","mac","linux"};
                //send_string( get_kb_layout() );
                //send_string("\nmode:");
                snprintf(buf,sizeof(buf),"layout:%s\n",get_kb_layout() );
                send_string(buf);
                snprintf(buf,sizeof(buf),"mode:%s\n",str_os[_harmonize.os_type]);
                send_string(buf);
#endif
              }
              return true;
          default:
              ;
        }
    }
    uint8_t modef = false;
    switch (keycode) {
      case K_IM_JP:
      case K_IM_EN:
          modef = (keycode  == K_IM_JP);
          im_enable( modef );
          im_mode_key( modef,record->event.pressed);
          break;

      case K_ENKB:
          _harmonize.lc_mode = 0;
          break;
      case K_JPKB:
          _harmonize.lc_mode = 1;
          break;

      case K_TKANA:
          _harmonize.type_mode = 1;
          break;
      case K_TROMJ:
          _harmonize.type_mode = 0;
          break;

      case K_IM_0:
      case K_IM_1:
      case K_IM_2:
      case K_IM_3:
          im_select(keycode - K_IM_0);
          im_enable(true);
          break;

      case K_KB_0:
      case K_KB_1:
      case K_KB_2:
      case K_KB_3:
          select_kb_layout(keycode - K_KB_0);
          break;

      case K_WIN:
      case K_MAC:
      case K_LNX:
          _harmonize.os_type = keycode - K_WIN;
          break;

      default:
          return true;
    }

    im_on_off(  _harmonize.im_enabled );
    harmonize_save();

    return true;
}

void harmonize_init(void) {
    harmonize_reset();
    harmonize_load();
    _harmonize.im_p =  &KBIM1_PLUG;
}





#undef _CONCAT
#undef ADD_PLUG
