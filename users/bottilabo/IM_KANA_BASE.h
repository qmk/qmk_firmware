/*
na 1 2 3 4 5  6 7 8 9 0 nb nc nd ne
t0 q w e r t  y u i o p t1 t2
h0 a s d f g  h j k l ; h1 h2
b0 z x c v b  n m , . / b1
        u0 u1 u2 u3

*/



// 1 2 3 4 5  6 7 8 9 0 ; = BS
// q w e r t  y u i o p [ ] BSLS
// a s d f g  h j k l - '
// z x c v b  n m , . / CTL
#define KANA_BASE_DEF( \
    Q, W, E, R, T, Y, U,   I,   O,   P, \
    A, S, D, F, G, H, J,   K,   L,SCLN, \
    Z, X, C, V, B, N, M,COMM, DOT,SLSH, \
            U0,U1,U2,U3,U4,U5 \
) { \
    {KC_A,KANA_##A},{KC_B,KANA_##B}      ,{KC_C,KANA_##C}      ,{KC_D,KANA_##D}    ,{KC_E,KANA_##E}, \
    {KC_F,KANA_##F},{KC_G,KANA_##G}      ,{KC_H,KANA_##H}      ,{KC_I,KANA_##I}    ,{KC_J,KANA_##J}, \
    {KC_K,KANA_##K},{KC_L,KANA_##L}      ,{KC_M,KANA_##M}      ,{KC_N,KANA_##N}    ,{KC_O,KANA_##O}, \
    {KC_P,KANA_##P},{KC_Q,KANA_##Q}      ,{KC_R,KANA_##R}      ,{KC_S,KANA_##S}    ,{KC_T,KANA_##T}, \
    {KC_U,KANA_##U},{KC_V,KANA_##V}      ,{KC_W,KANA_##W}      ,{KC_X,KANA_##X}    ,{KC_Y,KANA_##Y}, \
    {KC_Z,KANA_##Z},{KC_MINS,KANA_##SCLN},{KC_COMM,KANA_##COMM},{KC_DOT,KANA_##DOT},{KC_SLSH,KANA_##SLSH} \
}

#define KANA_BASE_DEF1( \
    Q, W, E, R, T, Y, U,   I,   O,   P, T1, \
    A, S, D, F, G, H, J,   K,   L,SCLN, H1, \
    Z, X, C, V, B, N, M,COMM, DOT,SLSH, B1, \
            U0,U1,U2,U3,U4,U5 \
) { \
    {KC_LBRC,KANA_##T1},   \
    {KC_QUOT,KANA_##H1},  \
    {KC_RCTL,KANA_##B1},  \
    {KC_A,KANA_##A},{KC_B,KANA_##B}      ,{KC_C,KANA_##C}      ,{KC_D,KANA_##D}    ,{KC_E,KANA_##E}, \
    {KC_F,KANA_##F},{KC_G,KANA_##G}      ,{KC_H,KANA_##H}      ,{KC_I,KANA_##I}    ,{KC_J,KANA_##J}, \
    {KC_K,KANA_##K},{KC_L,KANA_##L}      ,{KC_M,KANA_##M}      ,{KC_N,KANA_##N}    ,{KC_O,KANA_##O}, \
    {KC_P,KANA_##P},{KC_Q,KANA_##Q}      ,{KC_R,KANA_##R}      ,{KC_S,KANA_##S}    ,{KC_T,KANA_##T}, \
    {KC_U,KANA_##U},{KC_V,KANA_##V}      ,{KC_W,KANA_##W}      ,{KC_X,KANA_##X}    ,{KC_Y,KANA_##Y}, \
    {KC_Z,KANA_##Z},{KC_MINS,KANA_##SCLN},{KC_COMM,KANA_##COMM},{KC_DOT,KANA_##DOT},{KC_SLSH,KANA_##SLSH} \
}

#define KANA_BASE_DEF1B( \
    Q, W, E, R, T, Y, U,   I,   O,   P, T1,T2, \
    A, S, D, F, G, H, J,   K,   L,SCLN, H1,H2, \
    Z, X, C, V, B, N, M,COMM, DOT,SLSH, B1,    \
            U0,U1,U2,U3,U4,U5 \
) { \
    {KC_LBRC,KANA_##T1},{KC_RBRC,KANA_##T2},  \
    {KC_QUOT,KANA_##H1},{KC_GRV,KANA_##H2},  \
    {KC_RCTL,KANA_##B1},  \
    {KC_A,KANA_##A},{KC_B,KANA_##B}      ,{KC_C,KANA_##C}      ,{KC_D,KANA_##D}    ,{KC_E,KANA_##E}, \
    {KC_F,KANA_##F},{KC_G,KANA_##G}      ,{KC_H,KANA_##H}      ,{KC_I,KANA_##I}    ,{KC_J,KANA_##J}, \
    {KC_K,KANA_##K},{KC_L,KANA_##L}      ,{KC_M,KANA_##M}      ,{KC_N,KANA_##N}    ,{KC_O,KANA_##O}, \
    {KC_P,KANA_##P},{KC_Q,KANA_##Q}      ,{KC_R,KANA_##R}      ,{KC_S,KANA_##S}    ,{KC_T,KANA_##T}, \
    {KC_U,KANA_##U},{KC_V,KANA_##V}      ,{KC_W,KANA_##W}      ,{KC_X,KANA_##X}    ,{KC_Y,KANA_##Y}, \
    {KC_Z,KANA_##Z},{KC_MINS,KANA_##SCLN},{KC_COMM,KANA_##COMM},{KC_DOT,KANA_##DOT},{KC_SLSH,KANA_##SLSH} \
}



#define KANA_BASE_DEF2( \
    T0, Q, W, E, R, T, Y, U,   I,   O,   P, T1, \
    H0, A, S, D, F, G, H, J,   K,   L,SCLN, H1, \
    B0, Z, X, C, V, B, N, M,COMM, DOT,SLSH, B1, \
            U0,U1,U2,U3,U4,U5 \
) { \
    {KC_GRV ,KANA_##T0},{KC_LBRC,KANA_##T1},   \
    {KC_TAB ,KANA_##H0},{KC_QUOT,KANA_##H1},  \
    {KC_LSFT,KANA_##B0},{KC_RCTL,KANA_##B1},  \
    {KC_A,KANA_##A},{KC_B,KANA_##B}      ,{KC_C,KANA_##C}      ,{KC_D,KANA_##D}    ,{KC_E,KANA_##E}, \
    {KC_F,KANA_##F},{KC_G,KANA_##G}      ,{KC_H,KANA_##H}      ,{KC_I,KANA_##I}    ,{KC_J,KANA_##J}, \
    {KC_K,KANA_##K},{KC_L,KANA_##L}      ,{KC_M,KANA_##M}      ,{KC_N,KANA_##N}    ,{KC_O,KANA_##O}, \
    {KC_P,KANA_##P},{KC_Q,KANA_##Q}      ,{KC_R,KANA_##R}      ,{KC_S,KANA_##S}    ,{KC_T,KANA_##T}, \
    {KC_U,KANA_##U},{KC_V,KANA_##V}      ,{KC_W,KANA_##W}      ,{KC_X,KANA_##X}    ,{KC_Y,KANA_##Y}, \
    {KC_Z,KANA_##Z},{KC_MINS,KANA_##SCLN},{KC_COMM,KANA_##COMM},{KC_DOT,KANA_##DOT},{KC_SLSH,KANA_##SLSH} \
}

#define KANA_BASE_DEF3( \
   N1,N2,N3,N4,N5,N6,N7,  N8,  N9,  N0, NA,NB,NC, \
    Q, W, E, R, T, Y, U,   I,   O,   P, T1,T2, \
    A, S, D, F, G, H, J,   K,   L,SCLN, H1,H2, \
    Z, X, C, V, B, N, M,COMM, DOT,SLSH, B1, \
            U0,U1,U2,U3,U4,U5 \
) { \
    {KC_1,KANA_##N1},{KC_2,KANA_##N2}      ,{KC_3,KANA_##N3}      ,{KC_4,KANA_##N4}    ,{KC_5,KANA_##N5}, \
    {KC_6,KANA_##N6},{KC_7,KANA_##N7}      ,{KC_8,KANA_##N8}      ,{KC_9,KANA_##N9}    ,{KC_0,KANA_##N0}, \
    {KC_SCLN,KANA_##NA},{KC_EQL,KANA_##NB} ,{KC_BSPC,KANA_##NC},  \
    {KC_LBRC,KANA_##T1},{KC_RBRC,KANA_##T2},  \
    {KC_QUOT,KANA_##H1},{KC_GRV,KANA_##H2},  \
    {KC_RCTL,KANA_##B1},  \
    {KC_A,KANA_##A},{KC_B,KANA_##B}      ,{KC_C,KANA_##C}      ,{KC_D,KANA_##D}    ,{KC_E,KANA_##E}, \
    {KC_F,KANA_##F},{KC_G,KANA_##G}      ,{KC_H,KANA_##H}      ,{KC_I,KANA_##I}    ,{KC_J,KANA_##J}, \
    {KC_K,KANA_##K},{KC_L,KANA_##L}      ,{KC_M,KANA_##M}      ,{KC_N,KANA_##N}    ,{KC_O,KANA_##O}, \
    {KC_P,KANA_##P},{KC_Q,KANA_##Q}      ,{KC_R,KANA_##R}      ,{KC_S,KANA_##S}    ,{KC_T,KANA_##T}, \
    {KC_U,KANA_##U},{KC_V,KANA_##V}      ,{KC_W,KANA_##W}      ,{KC_X,KANA_##X}    ,{KC_Y,KANA_##Y}, \
    {KC_Z,KANA_##Z},{KC_MINS,KANA_##SCLN},{KC_COMM,KANA_##COMM},{KC_DOT,KANA_##DOT},{KC_SLSH,KANA_##SLSH} \
}

#define KANA_BASE_DEF4( \
   N0A, N1,N2,N3,N4,N5,N6,N7,  N8,  N9,  N0, NA,NB,NC,ND, \
   T0,  Q, W, E, R, T, Y, U,   I,   O,   P, T1,T2, \
   H0,  A, S, D, F, G, H, J,   K,   L,SCLN, H1,H2, \
   B0,  Z, X, C, V, B, N, M,COMM, DOT,SLSH, B1,B2, \
            U0,U1,U2,U3,U4,U5 \
) { \
    {KC_ESC,KANA_##N0A},{KC_TAB,KANA_##T0}  ,{KC_CAPS,KANA_##H0}   ,{KC_LSFT,KANA_##B0},  \
    {KC_1,KANA_##N1},{KC_2,KANA_##N2}      ,{KC_3,KANA_##N3}      ,{KC_4,KANA_##N4}    ,{KC_5,KANA_##N5}, \
    {KC_6,KANA_##N6},{KC_7,KANA_##N7}      ,{KC_8,KANA_##N8}      ,{KC_9,KANA_##N9}    ,{KC_0,KANA_##N0}, \
    {KC_SCLN,KANA_##NA},{KC_EQL,KANA_##NB} ,{KC_BSPC,KANA_##NC}   ,{KC_BSPC,KANA_##ND}, {KC_BSPC,KANA_##NC}, \
    {KC_LBRC,KANA_##T1},{KC_RBRC,KANA_##T2},  \
    {KC_QUOT,KANA_##H1},{KC_GRV,KANA_##H2},  \
    {KC_RCTL,KANA_##B1},{KC_RCTL,KANA_##B2},  \
    {KC_A,KANA_##A},{KC_B,KANA_##B}      ,{KC_C,KANA_##C}      ,{KC_D,KANA_##D}    ,{KC_E,KANA_##E}, \
    {KC_F,KANA_##F},{KC_G,KANA_##G}      ,{KC_H,KANA_##H}      ,{KC_I,KANA_##I}    ,{KC_J,KANA_##J}, \
    {KC_K,KANA_##K},{KC_L,KANA_##L}      ,{KC_M,KANA_##M}      ,{KC_N,KANA_##N}    ,{KC_O,KANA_##O}, \
    {KC_P,KANA_##P},{KC_Q,KANA_##Q}      ,{KC_R,KANA_##R}      ,{KC_S,KANA_##S}    ,{KC_T,KANA_##T}, \
    {KC_U,KANA_##U},{KC_V,KANA_##V}      ,{KC_W,KANA_##W}      ,{KC_X,KANA_##X}    ,{KC_Y,KANA_##Y}, \
    {KC_Z,KANA_##Z},{KC_MINS,KANA_##SCLN},{KC_COMM,KANA_##COMM},{KC_DOT,KANA_##DOT},{KC_SLSH,KANA_##SLSH}, \
    {KC_LSFT,KANA_##U1},{KC_SPC,KANA_##U2},  \
}

typedef struct {
    uint16_t code;
    uint16_t kana;
} KANA_BASE_CC_t;

typedef struct {
    KANA_t a;
    KANA_t b;
} KANA_BASE_KK_t;

typedef struct _kana_base_param_t {
    int16_t  stkin_term;
    int16_t  moratorium_term;

    volatile bool enabled;
    uint8_t kintype;
} kana_base_param_t;

//　同時押しでモディファイアとして使うキー 
enum {
    KANA_BASE_DAKU = 1U << 12,
    KANA_BASE_HNDK  = 1U << 13,
    KANA_BASE_LSHIFT = 1U << 14,
    KANA_BASE_RSHIFT  = 1U << 15,
};


#ifndef K_KANA_LSFT
#define K_KANA_LSFT KANA_SPC
#endif

#ifndef K_KANA_RSFT
#define K_KANA_RSFT KANA_SPC
#endif

#ifndef K_KANA_DSFT
#define K_KANA_DSFT KANA___
#endif


#ifndef KANA_BASE_TERM
#define KANA_BASE_TERM STKIN_TERM
#endif

