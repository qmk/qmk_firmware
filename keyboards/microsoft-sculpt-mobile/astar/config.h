/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

*/

#ifndef SCULPT_ASTAR_CONFIG
#define SCULPT_ASTAR_CONFIG

#include "../config.h"

/* key matrix size */
#define MATRIX_ROWS 8 
#define MATRIX_COLS 18 

			/*0   1   2   3    4   5  6   7   8 */
#define MATRIX_ROW_PINS {D7, C6, D4, D0, D1, D3, D2, E2}


/*                        A  B   C   D   E   F   G   H   I   J  K   L   M   N   O   P   Q  R  
*/
#define MATRIX_COL_PINS {B4, B5, E6, B7, B6, D6,  C7, F7, F6, F4,F5, F1,F0, D5, B0, B1, B2, B3}

#endif

