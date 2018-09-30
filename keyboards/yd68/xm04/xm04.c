#include <avr/io.h>
#include "host.h"
#include "host_driver.h"
#include "xm04.h"
#include "print.h"
#include "timer.h"
#include "wait.h"
#include "suart.h"

/* Host driver */
static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

host_driver_t xm04_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};

void xm04_init(void)
{
    DDRF |= (1<<4);
    DDRF |= (1<<7);
	PORTF &= ~(1<<7);
}

static uint8_t leds = 0;
static uint8_t keyboard_leds(void) { return leds; }
void xm04_set_leds(uint8_t l) { leds = l; }

static void send_keyboard(report_keyboard_t *report)
{
    xmit(0x0C);             //L2CAP length low byte
    xmit(0);                //L2CAP length high byte
    xmit(0xA1);             //BT HID DATA INPUT header type 
    xmit(1);                //BT HID Boot Protocol Report ID, Keyboard
    xmit(report->mods);     //HID report
    xmit(0x00);
    xmit(report->keys[0]);
    xmit(report->keys[1]);
    xmit(report->keys[2]);
    xmit(report->keys[3]);
    xmit(report->keys[4]);
    xmit(report->keys[5]);
}

static void send_mouse(report_mouse_t *report)
{
    xmit(0x08);             //L2CAP length low byte
    xmit(0);                //L2CAP length high byte
    xmit(0xA1);             //BT HID DATA INPUT header type 
    xmit(2);                //BT HID Boot Protocol Report ID, Mouse
    xmit(report->buttons);  //HID report
    xmit(report->x);
    xmit(report->y);
    xmit(report->v);
}

static void send_system(uint16_t data)
{
}

static uint32_t usage2bits(uint16_t usage)
{
    switch (usage) {
        case AC_BACK:                   return 1<<0;
        case AC_FORWARD:                return 1<<1;
        case AC_STOP:                   return 1<<2;
        case AC_REFRESH:                return 1<<3;
        case AC_SEARCH:                 return 1<<4;
        case AC_BOOKMARKS:              return 1<<5;
        case AC_HOME:                   return 1<<6;
        case AL_EMAIL:                  return 1<<7;
        case AUDIO_MUTE:                return 1<<8;
        case AUDIO_VOL_DOWN:            return 1<<9;
        case AUDIO_VOL_UP:              return 1<<10;
        case TRANSPORT_PLAY_PAUSE:      return 1<<11;
        case TRANSPORT_STOP:            return 1<<12;
        case TRANSPORT_PREV_TRACK:      return 1<<13;
        case TRANSPORT_NEXT_TRACK:      return 1<<14;
        case AL_LOCAL_BROWSER:          return 1UL<<16;   
        case AL_CALCULATOR:             return 1UL<<17;   
        case TRANSPORT_RECORD:          return 1UL<<19;   
        case TRANSPORT_FAST_FORWARD:    return 1UL<<20;   
        case TRANSPORT_REWIND:          return 1UL<<21;   
        case TRANSPORT_EJECT:           return 1UL<<29;   
    };
    return 0;
}

static void send_consumer(uint16_t data)
{
    uint32_t bits = usage2bits(data);
    xmit(0x08);             //L2CAP length low byte
    xmit(0);                //L2CAP length high byte
    xmit(0xA1);             //BT HID DATA INPUT header type 
    xmit(0x03);             //BT HID Boot Protocol Report ID, Consumer Control?
    xmit(bits&0xFF);        //HID report
    xmit((bits>>8)&0xFF);
    xmit((bits>>16)&0xFF);
    xmit((bits>>24)&0xFF);
}

bool bt_powered(void)
{
    return !(PORTB&(1<<PB2));
}

void turn_off_bt(void)
{
    PORTB |= (1<<PB2);
}

void turn_on_bt(void)
{
    PORTB &= ~(1<<PB2);
}

void toggle_bt(void)
{
    PORTB ^= (1<<PB2);
}

