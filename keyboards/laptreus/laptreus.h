#ifndef LAPTREUS_H
#define LAPTREUS_H

#include "quantum.h"
#include "outputselect.h"

/*
// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
*/
#define LAYOUT( \
  A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, \
  B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, \
  C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, \
  D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12 \
) \
{ \
  {A2, A3, A4, A5, A6, A7, A8, A9, A10, A11}, \
  {B2, B3, B4, B5, B6, B7, B8, B9, B10, B11}, \
  {C2, C3, C4, C5, C6, C7, C8, C9, C10, C11}, \
  {D2, D3, D4, D5, D6, D7, D8, D9, D10, D11}, \
  {A1, B1, C1, D1, KC_NO, KC_NO, D12, C12, B12, A12} \
}

#endif
