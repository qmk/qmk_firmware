#ifndef HOST_H
#define HOST_H

#include <stdint.h>


/* keyboard Modifiers in boot protocol report */
#define BIT_LCTRL   (1<<0)
#define BIT_LSHIFT  (1<<1)
#define BIT_LALT    (1<<2)
#define BIT_LGUI    (1<<3)
#define BIT_RCTRL   (1<<4)
#define BIT_RSHIFT  (1<<5)
#define BIT_RALT    (1<<6)
#define BIT_RGUI    (1<<7)
#define BIT_LCTL BIT_LCTRL
#define BIT_RCTL BIT_RCTRL
#define BIT_LSFT BIT_LSHIFT
#define BIT_RSFT BIT_RSHIFT

/* mouse buttons */
#define MOUSE_BTN1 (1<<0)
#define MOUSE_BTN2 (1<<1)
#define MOUSE_BTN3 (1<<2)
#define MOUSE_BTN4 (1<<3)
#define MOUSE_BTN5 (1<<4)


#define REPORT_KEYS 6
typedef struct {
    uint8_t mods;
    uint8_t rserved;
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


extern report_keyboard_t *keyboard_report;
extern report_keyboard_t *keyboard_report_prev;


/* keyboard report operations */
void host_add_key(uint8_t key);
void host_add_mod_bit(uint8_t mod);
void host_set_mods(uint8_t mods);
void host_add_code(uint8_t code);
void host_swap_keyboard_report(void);
void host_clear_keyboard_report(void);
uint8_t host_has_anykey(void);
uint8_t *host_get_keys(void);
uint8_t host_get_mods(void);


void host_send_keyboard_report(void);
void host_send_mouse_report(void);
void host_mouse_send(report_mouse_t *report);

#endif
