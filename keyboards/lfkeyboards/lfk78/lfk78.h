#pragma once

#include "quantum.h"

#if defined(KEYBOARD_lfkeyboards_lfk78_revb)
#    include "revb.h"
#elif defined(KEYBOARD_lfkeyboards_lfk78_revc)
#    include "revc.h"
#elif defined(KEYBOARD_lfkeyboards_lfk78_revj)
#    include "revj.h"
#endif

typedef struct RGB_Color {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
} RGB_Color;

typedef struct Layer_Info {
    uint32_t layer;
    uint32_t mask;
    RGB_Color color;
} Layer_Info;

extern const uint32_t layer_count;
extern const Layer_Info layer_info[];

#define CLICK_HZ 500
#define CLICK_MS 2
#define CLICK_ENABLED 0

void reset_keyboard_kb(void);
void click(uint16_t freq, uint16_t duration);
