#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stdbool.h"


#define REPORT_KEYS 6
typedef struct{
    uint8_t mods;
    uint8_t rserved;    // not used
    uint8_t keys[REPORT_KEYS];
}report_t;


//extern report_t *report;
//extern report_t *report_prev;

report_t *report_get(void);
bool report_has_key(void);
void report_send(void);
void report_add_mod(uint8_t mod);
void report_add_key(uint8_t key);
void report_add_code(uint8_t code);
void report_swap(void);
void report_clear(void);

#endif
