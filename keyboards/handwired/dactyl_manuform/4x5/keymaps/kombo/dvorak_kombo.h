//  0  1  2  3  4 | 29 28 27 26 25
//  5  6  7  8  9 | 34 33 32 31 30
// 10 11 12 13 14 | 39 38 37 36 35
//    16 17       |       42 41
//          18 19 | 44 43
//          23 24 | 49 48
//          21 22 | 47 46
#define CC_SCLN (1ULL << 0)
#define CC_COMM (1ULL << 1)
#define CC_DOT (1ULL << 2)
#define CC_P (1ULL << 3)
#define CC_Y (1ULL << 4)
#define CC_F (1ULL << 29)
#define CC_G (1ULL << 28)
#define CC_C (1ULL << 27)
#define CC_R (1ULL << 26)
#define CC_L (1ULL << 25)

#define CC_A (1ULL << 5)
#define CC_O (1ULL << 6)
#define CC_E (1ULL << 7)
#define CC_U (1ULL << 8)
#define CC_I (1ULL << 9)
#define CC_D (1ULL << 34)
#define CC_H (1ULL << 33)
#define CC_T (1ULL << 32)
#define CC_N (1ULL << 31)
#define CC_S (1ULL << 30)

#define CC_QUOT (1ULL << 10)
#define CC_Q (1ULL << 11)
#define CC_J (1ULL << 12)
#define CC_K (1ULL << 13)
#define CC_X (1ULL << 14)
#define CC_B (1ULL << 39)
#define CC_M (1ULL << 38)
#define CC_W (1ULL << 37)
#define CC_V (1ULL << 36)
#define CC_Z (1ULL << 35)

#define CC_LBRC (1ULL << 16)
#define CC_LCBR (1ULL << 17)
#define CC_RCBR (1ULL << 42)
#define CC_RBRC (1ULL << 41)

#define CC_TAB (1ULL << 18)
#define CC_SPC (1ULL << 19)
#define CC_BSPC (1ULL << 44)
#define CC_ESC (1ULL << 43)

#define CC_LPRN (1ULL << 23)
#define CC_LCTL (1ULL << 24)
#define CC_LSFT (1ULL << 49)
#define CC_RPRN (1ULL << 48)

#define CC_LALT (1ULL << 21)
#define CC_LGUI (1ULL << 22)
#define CC_BLSL (1ULL << 47)
#define CC_RALT (1ULL << 46)


int8_t
kombo_get_pos(uint8_t row, uint8_t col) {
	return (row * 5 + col);
}
