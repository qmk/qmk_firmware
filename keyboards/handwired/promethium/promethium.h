#ifndef PROMETHIUM_H
#define PROMETHIUM_H

#include "quantum.h"

#define PS2_INIT_DELAY 2000

#define KEYMAP( \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
    k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c \
) \
{ \
    {k11, k12, k13, k14, k15, k16}, \
    {k21, k22, k23, k24, k25, k26}, \
    {k31, k32, k33, k34, k35, k36}, \
    {k41, k42, k43, k44, k45, k46}, \
    {k17, k18, k19, k1a, k1b, k1c}, \
    {k27, k28, k29, k2a, k2b, k2c}, \
    {k37, k38, k39, k3a, k3b, k3c}, \
    {k47, k48, k49, k4a, k4b, k4c} \
}

enum led_sequence {
  LED_IND_EMOJI,
  LED_IND_NUM,
  LED_IND_FUNC,

  LED_IND_BATTERY,
  LED_IND_USB,
  LED_IND_BLUETOOTH,

  LED_TAB,
  LED_ESC,
  LED_LSFT,
  LED_LCTL,

  LED_LGUI,
  LED_Z,
  LED_A,
  LED_Q,

  LED_W,
  LED_S,
  LED_X,
  LED_LALT,

  LED_PUNC,
  LED_C,
  LED_D,
  LED_E,

  LED_R,
  LED_F,
  LED_V,
  LED_NUM,

  LED_LSPC,
  LED_B,
  LED_G,
  LED_T,

  LED_TRACKPOINT1,
  LED_TRACKPOINT2,
  LED_TRACKPOINT3,

  LED_RSPC,
  LED_N,
  LED_HH,
  LED_Y,

  LED_U,
  LED_J,
  LED_M,
  LED_FUNC,

  LED_EMOJI,
  LED_COMM,
  LED_K,
  LED_I,

  LED_O,
  LED_L,
  LED_DOT,
  LED_RALT,

  LED_RGUI,
  LED_SLSH,
  LED_SCLN,
  LED_P,

  LED_BKSP,
  LED_ENT,
  LED_RSFT,
  LED_RCTL
};

#endif


