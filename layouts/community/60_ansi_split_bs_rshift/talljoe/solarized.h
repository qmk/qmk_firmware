#ifndef SOLARIZED_H
#define SOLARIZED_H

#include "quantum/color.h"

typedef struct {
  HSV base03;
  HSV base02;
  HSV base01;
  HSV base00;
  HSV base0;
  HSV base1;
  HSV base2;
  HSV base3;
  HSV yellow;
  HSV orange;
  HSV red;
  HSV magenta;
  HSV violet;
  HSV blue;
  HSV cyan;
  HSV green;
} solarized_t;

extern solarized_t solarized;

#endif
