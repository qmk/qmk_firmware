#ifndef SUBATOMIC_H
#define SUBATOMIC_H

#include "quantum.h"

/*
 * Modified from keyboards/planck/planck.h
 * 14 Columns (01-14 because I'm a newb)
 *  5 Rows    (A-E)
 *        - https://github.com/noroadsleft
 *                            May 16, 2018
 */
#define LAYOUT_subatomic_mit( \
    A01, A02, A03, A04, A05, A06, A07, A08, A09, A10, A11, A12, A13, A14, \
    B01, B02, B03, B04, B05, B06, B07, B08, B09, B10, B11, B12, B13, B14, \
    C01, C02, C03, C04, C05, C06, C07, C08, C09, C10, C11, C12, C13, C14, \
    D01, D02, D03, D04, D05, D06, D07, D08  D09, D10, D11, D12, D13, D14  \
    E01, E02, E03, E04, E05, E06,    E07,   E09, E10, E11, E12, E13, E14  \
	) \
{ \
  { A01, A02, A03, A04, A05, A06, A07, A08, A09, A10, A11, A12, A13, A14 }, \
  { B01, B02, B03, B04, B05, B06, B07, B08, B09, B10, B11, B12, B13, B14 }, \
  { C01, C02, C03, C04, C05, C06, C07, C08, C09, C10, C11, C12, C13, C14 }, \
  { D01, D02, D03, D04, D05, D06, D07, D08, D09, D10, D11, D12, D13, D14 }  \
  { E01, E02, E03, E04, E05, E06, E07, E07, E09, E10, E11, E12, E13, E14 }  \
}

#define LAYOUT_subatomic_grid( \
    A01, A02, A03, A04, A05, A06, A07, A08, A09, A10, A11, A12, A13, A14, \
    B01, B02, B03, B04, B05, B06, B07, B08, B09, B10, B11, B12, B13, B14, \
    C01, C02, C03, C04, C05, C06, C07, C08, C09, C10, C11, C12, C13, C14, \
    D01, D02, D03, D04, D05, D06, D07, D08, D09, D10, D11, D12, D13, D14  \
    E01, E02, E03, E04, E05, E06, E07, E08, E09, E10, E11, E12, E13, E14  \
	) \
{ \
  { A01, A02, A03, A04, A05, A06, A07, A08, A09, A10, A11, A12, A13, A14 }, \
  { B01, B02, B03, B04, B05, B06, B07, B08, B09, B10, B11, B12, B13, B14 }, \
  { C01, C02, C03, C04, C05, C06, C07, C08, C09, C10, C11, C12, C13, C14 }, \
  { D01, D02, D03, D04, D05, D06, D07, D08, D09, D10, D11, D12, D13, D14 }  \
  { E01, E02, E03, E04, E05, E06, E07, E08, E09, E10, E11, E12, E13, E14 }  \
}

#define LAYOUT_ortho_4x14 LAYOUT_subatomic_grid

#endif
