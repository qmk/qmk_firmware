#ifndef HOST_H
#define HOST_H

#include <stdint.h>


#define REPORT_KEYS 6
#define MOUSE_BTN1 (1<<0)
#define MOUSE_BTN2 (1<<1)
#define MOUSE_BTN3 (1<<2)
#define MOUSE_BTN4 (1<<3)
#define MOUSE_BTN5 (1<<4)


typedef struct {
    uint8_t mods;
    uint8_t rserved;    // not used
    uint8_t keys[REPORT_KEYS];
} report_keyboard_t;

typedef struct {
    uint8_t buttons;
    int8_t x;
    int8_t y;
/*
    int8_t v;
    int8_t h;
 */
} report_mouse_t;


extern uint8_t host_keyboard_led;
void host_keyboard_send(report_keyboard_t *report);
void host_mouse_send(report_mouse_t *report);

#endif
