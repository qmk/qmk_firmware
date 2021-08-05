/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define LAYOUT( \
  K29,K1E,K1F,K20,K21,K22,K2D,    K2E,K23,K24,K25,K26,K27,K2A,\
  K2B,K14,K1A,K08,K15,K17,K4B,    K2F,K1C,K18,K0C,K12,K13,K31,\
  K39,K04,K16,K07,K09,K0A,            K0B,K0D,K0E,K0F,K33,K34,\
  KE1,K1D,K1B,K06,K19,K05,K4E,    K30,K11,K10,K36,K37,K52,KE5,\
  KE0,KE3,KE2,                                    K50,K51,K4F,\
                      K2C,K49,    K4A,K28,        \
                      KE6,K4C,    K4D,KE4         \
) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, K04,   K05,   K06,   K07,      /* 00-07 */ \
      K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F    }, /* 08-0F */ \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,      /* 10-17 */ \
      K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F    }, /* 18-1F */ \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,      /* 20-27 */ \
      K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F    }, /* 28-2F */ \
    { K30,   K31,   KC_NO, K33,   K34,   KC_NO, K36,   K37,      /* 30-37 */ \
      KC_NO, K39,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 38-3F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 40-47 */ \
      KC_NO, K49,   K4A,   K4B,   K4C,   K4D,   K4E,   K4F    }, /* 48-4F */ \
    { K50,   K51,   K52,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 50-57 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 58-5F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 60-67 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 68-6F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 70-77 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 78-7F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 80-87 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 88-8F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 90-97 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 98-9F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* A0-A7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* A8-AF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* B0-B7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* B8-BF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* C0-C7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* C8-CF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* D0-D7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* D8-DF */ \
    { KE0,   KE1,   KE2,   KE3,   KE4,   KE5,   KE6,   KC_NO,    /* E0-E7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* E8-EF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* F0-F7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* F8-FF */ \
}

#define LAYOUT_beta_pcb( \
  K1E, K1F, K30, K2F, K45, K3B, KE6,          KE2, K3A, K39, K14, K04, K09, K07, \
  K29, K15, K3C, K3D, K3E, K3F, K58,          K50, K2C, K11, K05, K55, K10, K06, \
  K31, K5F, K5E, K61, K2A, K38,                    K4C, K57, K53, K5B, K5A, K08, \
  K35, K5D, K17, K1B, K1A, K52, K56,          K51, K4D, K23, K1C, K13, K2E, K0C, \
  K5C, K0A, K0F,                                                  K36, K0E, K37, \
                           KE4, K49,          K4B, KE0,                          \
                                KE5,          KE1\
) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, K04,   K05,   K06,   K07,      /* 00-07 */ \
      K08,   K09,   K0A,   KC_NO, K0C,   KC_NO, K0E,   K0F    }, /* 08-0F */ \
    { K10,   K11,   KC_NO, K13,   K14,   K15,   KC_NO, K17,      /* 10-17 */ \
      KC_NO, KC_NO, K1A,   K1B,   K1C,   K1E,   K1F,   KC_NO  }, /* 18-1F */ \
    { KC_NO, KC_NO, KC_NO, K23,   KC_NO, KC_NO, KC_NO, KC_NO,    /* 20-27 */ \
      KC_NO, K29,   K2A,   KC_NO, K2C,   KC_NO, K2E,   K2F    }, /* 28-2F */ \
    { K30,   K31,   KC_NO, KC_NO, KC_NO, K35,   K36,   K37,      /* 30-37 */ \
      K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F    }, /* 38-3F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K45,   KC_NO, KC_NO,    /* 40-47 */ \
      KC_NO, K49,   KC_NO, K4B,   K4C,   K4D,   KC_NO, KC_NO  }, /* 48-4F */ \
    { K50,   K51,   K52,   K53,   KC_NO, K55,   K56,   K57,      /* 50-57 */ \
      K58,   KC_NO, K5A,   K5B,   K5C,   K5D,   K5E,   K5F    }, /* 58-5F */ \
    { KC_NO, K61,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 60-67 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 68-6F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 70-77 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 78-7F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 80-87 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 88-8F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* 90-97 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* 98-9F */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* A0-A7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* A8-AF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* B0-B7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* B8-BF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* C0-C7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* C8-CF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* D0-D7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* D8-DF */ \
    { KE0,   KE1,   KE2,   KC_NO, KE4,   KE5,   KE6,   KC_NO,    /* E0-E7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* E8-EF */ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    /* F0-F7 */ \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO  }, /* F8-FF */ \
}
