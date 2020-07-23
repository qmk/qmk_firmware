#include QMK_KEYBOARD_H
#include "stdafx.h"

#include "IM_ONEHAND"

const char* led_def[5] = {
[0] =
"100500"
"155550"
"400000"
"666",
[1] =
"100100"
"101110"
"400000"
"676",
[2] =
"105550"
"105550"
"455550"
"766",
[3] =
"233333"
"133333"
"455545"
"776",
[4] =
"100400"
"144440"
"504000"
"666",
};

uint8_t pos_to_idx(uint8_t x,uint8_t y) {
    uint8_t i;

    if( y == 3 || y == 7) {
        i = y * 6 + 6 + (x % 3);
    }
    else {
        i = x + y * 6 + 6;
    }
    
    return i;
}

#define ANIFRM 128 
#define ANINUM 4
#define MODNUM 4

typedef struct
{
    uint8_t led_anim;
    uint8_t last_led_idx;
    LED_TYPE led1,led2;
} LEDAnim_t;

static LEDAnim_t ledanim[ANINUM] = { {0},{0},{0},{0} };
static uint8_t ledanim_idx = 0;

typedef struct
{
    uint8_t led_idx;
    LED_TYPE led1;
} LEDMod_t;

static LEDMod_t ledmod[MODNUM] = { {0},{0},{0},{0} };



void matrix_init_local(void) {
    rgblight_timer_disable();
}

uint8_t determine_layer(void) {
    for(uint8_t i=3;i!=0;i--) {
        if( IS_LAYER_ON(i) )
            return i;
    }
    if( _onehand.im_mode == 2)
        return 4;
    else
        return 0;
}

static uint8_t fct0 = 0;
static uint8_t fct1 = 0;
static uint8_t fct2 = 0;
static bool led_refresh = true;
static bool update_led_layer = true;
static bool update_led = false;
//static uint8_t prev_mod = 0;

inline bool zeroone(uint8_t val) {
    if( val ) return 1;
    else return 0;
}

void matrix_scan_local(void) { 
    if( update_led_layer ) {
        const uint8_t V = LED_MID;
        uint8_t layeridx = determine_layer();

        const char *a = led_def[layeridx];
        fct1++;
        if( a[fct1] == 0 ) {
            fct1=0;
            update_led_layer = false;
            update_led = true;

            //uint8_t mod = zeroone(_onehand.mod_shift) | (zeroone(_onehand.mod_ctl) << 1) | (zeroone(_onehand.mod_alt) << 2) | (zeroone(_onehand.mod_gui) << 3);
            //if( prev_mod != mod )
            {
                update_led_layer = true;
                //prev_mod = mod;
                for(uint8_t i=0;i<MODNUM;i++)  {
                    LEDMod_t* ledp = &ledmod[i];
                    switch(i) {
                        case 0:if( _onehand.mod_shift == 0 )  continue;
                            break;
                        case 1:if( _onehand.mod_ctl   == 0 ) continue;
                            break;
                        case 2:if( _onehand.mod_alt   == 0 ) continue;
                            break;
                        case 3:if( _onehand.mod_gui   == 0 ) continue;
                            break;
                    }
                    LED_TYPE l = ledp->led1;
                    setrgb(l.r,l.g,l.b,(LED_TYPE *)&led[ ledp->led_idx ]);
                }
            }
        }
        else {
            uint8_t i = fct1;
            uint8_t r,g,b;
            switch(a[i]) {
            case '1':r=0;g=0;b=V;break;
            case '2':r=V;g=0;b=0;break;
            case '3':r=V;g=0;b=V;break;
            case '4':r=0;g=V;b=0;break;
            case '5':r=0;g=V;b=V;break;
            case '6':r=V;g=V;b=0;break;
            case '7':r=V;g=V;b=V;break;
            default: r=0;g=0;b= LED_LOW;
           }
           setrgb(r, g, b, (LED_TYPE *)&led[i + 6]);
        }
    }

    if( true )
    {
        fct2++;
        if(fct2>=ANINUM)
            fct2=0;
        uint8_t i=fct2;
        LEDAnim_t* ledp = &ledanim[i];
        if( ledp->led_anim != 0 )
        {
            update_led = true;
            ledp->led_anim--;
            LED_TYPE l;
            l.r = ledp->led1.r + ( ((ledp->led2.r - ledp->led1.r) * ledp->led_anim) >>7);
            l.g = ledp->led1.g + ( ((ledp->led2.g - ledp->led1.g) * ledp->led_anim) >>7);
            l.b = ledp->led1.b + ( ((ledp->led2.b - ledp->led1.b) * ledp->led_anim) >>7);
            setrgb(l.r,l.g,l.b,(LED_TYPE *)&led[ ledp->last_led_idx ]);
        }
    }

    if( update_led )
        led_refresh = true;
    update_led = false;

    fct0++;
    if( fct0 >= 3 ) {
        fct0 = 0;

        if( led_refresh ) {
            rgblight_set();
        }
        led_refresh = false;
    }

}

void setrgb_(LED_TYPE* p,uint8_t r,uint8_t g,uint8_t b) {
    p->r = r;
    p->g = g;
    p->b = b;
}

bool process_record_local(uint16_t keycode, keyrecord_t *record) {
    update_led_layer = true;
    update_led = true;

    if( record->event.pressed )
    {
        uint8_t ledidx = pos_to_idx(record->event.key.col,record->event.key.row);
        switch( keycode ) {
            case KX__SFT:
                ledmod[0].led_idx = ledidx;
                setrgb_(&ledmod[0].led1,LED_HIGH,LED_HIGH,LED_HIGH);
                break;
            case KX__CTL:
                ledmod[1].led_idx = ledidx;
                setrgb_(&ledmod[1].led1,LED_HIGH,LED_HIGH,LED_HIGH);
                break;
            case KX__ALT:
                ledmod[2].led_idx = ledidx;
                setrgb_(&ledmod[2].led1,LED_HIGH,LED_HIGH,LED_HIGH);
                break;
            case KX__GUI:
                ledmod[3].led_idx = ledidx;
                setrgb_(&ledmod[3].led1,LED_HIGH,LED_HIGH,LED_HIGH);
                break;
            default:
                {
                ledanim_idx++;
                if( ledanim_idx >= ANINUM )
                    ledanim_idx = 0;


                LEDAnim_t* ani = &ledanim[ledanim_idx];
                ani->last_led_idx = ledidx;
                ani->led_anim = ANIFRM;
                ani->led1 = led[ ledidx ];
                setrgb_(&ani->led2,LED_HIGH,LED_HIGH,LED_HIGH);
                }
        }

   } 

    return true;
}


