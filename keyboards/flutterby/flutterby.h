#ifndef FLUTTERBY_H
#define FLUTTERBY_H

#include "quantum.h"

#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39  \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
}

bool sx1509_init(void);
uint16_t sx1509_read(void);
bool sx1509_make_ready(void);

void flutterby_led_enable(bool on);
void flutterby_blink_led(int times);

enum ThumbStickMode {
  ThumbStickMovesPointer,
  ThumbStickPanning,
};
void flutterby_thumbstick_set_mode(enum ThumbStickMode mode);
enum ThumbStickMode flutterby_thumbstick_get_mode(void);

#endif
