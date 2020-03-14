#include "xkey.h"

static bool on_xlongperss_key(xglobal_t* pg,xkey_t* pk,uint16_t now,uint16_t keycode,keyrecord_t *record) {
    if( keycode == 0 )
        return true;

    bool pressed = record->event.pressed;
    if( ! pressed ) {
        if( keycode == pg->last_pressed_key ) {
            pk->duration = TIMER_DIFF_16(now,pg->last_released_time);
        } else {
            pk->consecutive_count = 0;
        }
        return true;
    }
    return true;
}

static bool on_xrenda_key(xglobal_t* pg,xkey_t* pk,uint16_t now,uint16_t keycode,keyrecord_t *record) {
    if( keycode == 0 )
        return true;
    bool pressed = record->event.pressed;
    if( pressed ) {
        if( pg->last_released_key != keycode ) {
            if( TIMER_DIFF_16(now,pg->last_released_time) < 150 ) {
                pk->consecutive_count = -1;
            } else {
                pk->consecutive_count = 0;
            }
            return true;
        }

        if( TIMER_DIFF_16(now,pg->last_released_time) < 300 ) {
            pk->consecutive_count++;
        } else {
            pk->consecutive_count = 0;
        }
    }
    return true;
}

static bool _xkey_process_keys(xglobal_t* pg,uint16_t now,uint16_t keycode,keyrecord_t *record) {
    if( ! on_xrenda_key(pg,&_renda,now,keycode,record) ) return false;
    if( ! on_xlongperss_key(pg,&_longpress,now,keycode,record) ) return false;
    return true;
}

bool xkey_process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;
    uint16_t now = timer_read();

    bool r = _xkey_process_keys(&_xkey,now,keycode,record);
    if( keycode == 0 )
        return true;

    //if( keycode < QK_LAYER_TAP || keycode > QK_LAYER_MOD_MAX )
    if( true )
    {
        if(pressed) {
            _xkey.last_pressed_key = keycode;
            _xkey.last_pressed_time = now;
        } else {
            _xkey.last_released_key = keycode;
            _xkey.last_released_time = now;
        }
        if(!r)
          return false;
    }
    return true;
}

#define XKEY_PROC \
    if(!xkey_process_record_user(keycode,record)) return false;



