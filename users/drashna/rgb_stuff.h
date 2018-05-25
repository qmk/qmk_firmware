#include "quantum.h"

typedef struct {
    bool enabled;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint16_t timer;
    uint8_t life;
} rgblight_fadeout;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void scan_rgblight_fadeout(void);
