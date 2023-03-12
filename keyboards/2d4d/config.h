// Copyright 2023 mechMehmet (@mechMehmet)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define MATRIX_ROWS 8  // Rows are doubled-up
#define MATRIX_COLS 6

#define DEBOUNCE 5

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//sırayla yaz
#define MATRIX_ROW_PINS \
    { B3, B4, B5, B6, A2, A3, A4, A5 }
#define MATRIX_COL_PINS \
    { B12, B13, B14, B15, A8, A15 }

//A VE B kanalı çok önemli değil, eğer yanlış bağlarsan bunları yer değiştir.
#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A \
    { A1 }
#define ENCODERS_PAD_B \
    { A0 }
#define ENCODER_RESOLUTION 4
#endif

    //proje amacı 18 pin kullanmaktı. 14 pin satır-sütun kullanıyorum. 4 pin arttı.
    //1 encoder için 2 pin, böylece 2 pini led için kullanabilirim
    //2 encoder içinse matrix oluşturuyorum. 4 pin yerine 3 pin kullanarak encoderleri kullanabilirim. 1 pini de lede kullanarım.
// //2 encoder için, 3 pinle, kullanımda kısıtlama olmaz
// #define ENCODERS_PAD_A { A0, A0 }
// #define ENCODERS_PAD_B { A1, A2 }

// //3 encoder için, 3 pinle ancak 2 encoderi aynı anda kullanmak sorun oluşturabilir.
// #define ENCODERS_PAD_A { B1, B1, B2 }
// #define ENCODERS_PAD_B { B2, B3, B3 }

// //daha fazla kombinasyonla üretebilirsin. 5 pinle 6 encoder. 
// #define ENCODERS_PAD_A { B1, B1, B1, A1, A1, A1 }
// #define ENCODERS_PAD_B { B2, B3, B4, B2, B3, B4 }


#define ledGreen B0
#define ledBlue  B1
#define ledRed   B10
#define ledWhite B9
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
