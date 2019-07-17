enum unicode_names {
    A_ACUTE,
    A_ACUTEC,
    E_ACUTE,
    E_ACUTEC,
    I_ACUTE,
    I_ACUTEC,
    O_ACUTE,
    O_ACUTEC,
    U_ACUTE,
    U_ACUTEC,
    U_DIERESIS,
    U_DIERESISC,
    N_TILDE,
    N_TILDEC,
    OPEN_EXCML,
    OPEN_QUEST,
    EURO,
    POUND,
    LEFT_ARROW,
    DOWN_ARROW,
    UP_ARROW,
    RIGHT_ARROW,
    LEFT_DARROW,
    DOWN_DARROW,
    UP_DARROW,
    RIGHT_DAROW,
    LEFT_DQUOT,
    RGHT_DQUOT,
    DEGREE,
    DEGREE_CELCIUS,
    SUPER_1,
    SUPER_2,
    SUPER_3,
    ONE_HALF,
    PER_MILLE,
    PER_THOUS,
    PILCROW,
    COPYRIGHT,
    REGISTERED,
    MICRO,
    MIDDLE_DOT,
    BOX_CORNER_1,
    BOX_CORNER_2,
    BOX_CORNER_3,
    BOX_CORNER_4,
    BOX_HORIZONTAL,
    BOX_VERTICAL,
    BOX_CROSS,
    BOX_UNION_1,
    BOX_UNION_2,
    BOX_UNION_3,
    BOX_UNION_4,
    DBOX_CORNER_1,
    DBOX_CORNER_2,
    DBOX_CORNER_3,
    DBOX_CORNER_4,
    DBOX_HORIZONT,
    DBOX_VERTICAL,
    DBOX_CROSS,
    DBOX_UNION_1,
    DBOX_UNION_2,
    DBOX_UNION_3,
    DBOX_UNION_4,
    LESS_EQUAL,
    MORE_EQUAL,
    DIVISION,
    SQUARE_ROOT,
    CUBE_ROOT,
    SPADE_SUIT,
    TREBOL_SUIT,
    HEART_SUIT,
    DIAMOND_SUIT,
};

const uint32_t PROGMEM unicode_map[] = {
    [A_ACUTE]       = 0x00E1,
    [A_ACUTEC]      = 0x00C1,
    [E_ACUTE]       = 0x00E9,
    [E_ACUTEC]      = 0x00C9,
    [I_ACUTE]       = 0x00ED,
    [I_ACUTEC]      = 0x00CD,
    [O_ACUTE]       = 0x00F3,
    [O_ACUTEC]      = 0x00D3,
    [U_ACUTE]       = 0x00FA,
    [U_ACUTEC]      = 0x00DA,
    [U_DIERESIS]    = 0x00FC,
    [U_DIERESISC]   = 0x00DC,
    [N_TILDE]       = 0x00F1,
    [N_TILDEC]      = 0x00D1,
    [OPEN_EXCML]    = 0x00A1,
    [OPEN_QUEST]    = 0x00BF,
    [EURO]          = 0x20AC,
    [POUND]         = 0x00A3,
    [LEFT_ARROW]    = 0x2190,
    [DOWN_ARROW]    = 0x2193,
    [UP_ARROW]      = 0x2191,
    [RIGHT_ARROW]   = 0x2192,
    [LEFT_DARROW]   = 0x21E6,
    [DOWN_DARROW]   = 0x21D3,
    [UP_DARROW]     = 0x21D1,
    [RIGHT_DAROW]   = 0x21D2,
    [LEFT_DQUOT]    = 0x00AB,
    [RGHT_DQUOT]    = 0x00BB,
    [DEGREE]        = 0x00B0,
    [DEGREE_CELCIUS]= 0x2103,
    [SUPER_1]       = 0x00B9,
    [SUPER_2]       = 0x00B2,
    [SUPER_3]       = 0x00B3,
    [ONE_HALF]      = 0x00BD,
    [PER_MILLE]     = 0x0609,
    [PER_THOUS]     = 0x060A,
    [PILCROW]       = 0x00B6,
    [COPYRIGHT]     = 0x00A9,
    [REGISTERED]    = 0x00AE,
    [MICRO]         = 0x00B5,
    [MIDDLE_DOT]    = 0x00B7,
    [BOX_CORNER_1]  = 0x250C,
    [BOX_CORNER_2]  = 0x2510,
    [BOX_CORNER_3]  = 0x2514,
    [BOX_CORNER_4]  = 0x2518,
    [BOX_HORIZONTAL]= 0x2500,
    [BOX_VERTICAL]  = 0x2502,
    [BOX_CROSS]     = 0x253C,
    [BOX_UNION_1]   = 0x2524,
    [BOX_UNION_2]   = 0x252C,
    [BOX_UNION_3]   = 0x2534,
    [BOX_UNION_4]   = 0x251C,
    [DBOX_CORNER_1] = 0x2554,
    [DBOX_CORNER_2] = 0x2557,
    [DBOX_CORNER_3] = 0x255A,
    [DBOX_CORNER_4] = 0x255D,
    [DBOX_HORIZONT] = 0x2550,
    [DBOX_VERTICAL] = 0x2551,
    [DBOX_CROSS]    = 0x256C,
    [DBOX_UNION_1]  = 0x2563,
    [DBOX_UNION_2]  = 0x2566,
    [DBOX_UNION_3]  = 0x2569,
    [DBOX_UNION_4]  = 0x2560,
    [LESS_EQUAL]    = 0x2264,
    [MORE_EQUAL]    = 0x2265,
    [DIVISION]      = 0x00F7,
    [SQUARE_ROOT]   = 0x221A,
    [CUBE_ROOT]     = 0x221B,
    [SPADE_SUIT]    = 0x2660, 
    [TREBOL_SUIT]   = 0x2663,
    [HEART_SUIT]    = 0x2664,
    [DIAMOND_SUIT]  = 0x2665
};

#define UN_ESC  XP(DEGREE, DEGREE_CELCIUS)
#define UN_Q    XP(OPEN_EXCML, SUPER_1)
#define UN_W    XP(SUPER_2, SUPER_3)
#define UN_E    XP(E_ACUTE, E_ACUTEC)
#define UN_R    XP(EURO, ONE_HALF)
#define UN_T    XP(PER_MILLE, PER_THOUS)
#define UN_Y    XP(U_DIERESIS, U_DIERESISC)
#define UN_U    XP(U_ACUTE, U_ACUTEC)
#define UN_I    XP(I_ACUTE, I_ACUTEC)
#define UN_O    XP(O_ACUTE, O_ACUTEC)
#define UN_P    XP(POUND, PILCROW)
#define UN_A    XP(A_ACUTE, A_ACUTEC)
#define UN_S    XP(BOX_CORNER_1, DBOX_CORNER_1)
#define UN_D    XP(BOX_CORNER_2, DBOX_CORNER_2)
#define UN_F    XP(BOX_CORNER_3, DBOX_CORNER_3)
#define UN_G    XP(BOX_CORNER_4, DBOX_CORNER_4)
#define UN_H    XP(BOX_UNION_1, DBOX_UNION_1)
#define UN_J    XP(BOX_UNION_2, DBOX_UNION_2)
#define UN_K    XP(BOX_UNION_3, DBOX_UNION_3)
#define UN_L    XP(BOX_UNION_4, DBOX_UNION_4)
#define UN_SCLN XP(BOX_HORIZONTAL, DBOX_HORIZONT)
#define UN_Z    XP(BOX_VERTICAL, DBOX_VERTICAL)
#define UN_X    XP(BOX_CROSS, DBOX_CROSS)
#define UN_C    XP(COPYRIGHT, REGISTERED)
#define UN_V    XP(SPADE_SUIT, TREBOL_SUIT)
#define UN_B    XP(HEART_SUIT, DIAMOND_SUIT)
#define UN_N    XP(N_TILDE, N_TILDEC)
#define UN_M    XP(MICRO, MIDDLE_DOT)
#define UN_COMM XP(LESS_EQUAL, LEFT_DQUOT)
#define UN_DOT  XP(MORE_EQUAL, RGHT_DQUOT)
#define UN_SLSH XP(OPEN_QUEST, DIVISION)
#define UN_LEFT XP(LEFT_ARROW, LEFT_DARROW)
#define UN_DOWN XP(DOWN_ARROW, DOWN_DARROW)
#define UN_UP   XP(UP_ARROW, UP_DARROW)
#define UN_RGHT XP(RIGHT_ARROW, RIGHT_DAROW) 