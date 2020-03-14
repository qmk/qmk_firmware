/*
na 1 2 3 4 5  6 7 8 9 0 nb nc nd ne
t0 q w e r t  y u i o p t1 t2
h0 a s d f g  h j k l ; h1 h2
b0 z x c v b  n m , . / b1
        u0 u1 u2 u3

*/


#define ALPHA_max 255
typedef uint16_t ALPHA_t;


// 1 2 3 4 5  6 7 8 9 0 ; = BS
// q w e r t  y u i o p [ ] BSLS
// a s d f g  h j k l - '
// z x c v b  n m , . / CTL
#define ALPHA_BASE_DEF( \
    Q, W, E, R, T, Y, U,   I,   O,   P, \
    A, S, D, F, G, H, J,   K,   L,SCLN, \
    Z, X, C, V, B, N, M,COMM, DOT,SLSH, \
            U0,U1,U2,U3,U4,U5 \
) { \
    {KC_A,KC_##A},{KC_B,KC_##B}      ,{KC_C,KC_##C}      ,{KC_D,KC_##D}    ,{KC_E,KC_##E}, \
    {KC_F,KC_##F},{KC_G,KC_##G}      ,{KC_H,KC_##H}      ,{KC_I,KC_##I}    ,{KC_J,KC_##J}, \
    {KC_K,KC_##K},{KC_L,KC_##L}      ,{KC_M,KC_##M}      ,{KC_N,KC_##N}    ,{KC_O,KC_##O}, \
    {KC_P,KC_##P},{KC_Q,KC_##Q}      ,{KC_R,KC_##R}      ,{KC_S,KC_##S}    ,{KC_T,KC_##T}, \
    {KC_U,KC_##U},{KC_V,KC_##V}      ,{KC_W,KC_##W}      ,{KC_X,KC_##X}    ,{KC_Y,KC_##Y}, \
    {KC_Z,KC_##Z} \
}


typedef struct {
    uint16_t code;
    uint16_t alpha;
} ALPHA_BASE_CC_t;

typedef struct {
    ALPHA_t a;
    ALPHA_t b;
} ALPHA_BASE_KK_t;

typedef struct _alpha_base_param_t {
    int16_t  stkin_term;
    int16_t  moratorium_term;

    volatile bool enabled;
    uint8_t kintype;
} alpha_base_param_t;

//　同時押しでモディファイアとして使うキー 
enum {
    ALPHA_BASE_DAKU = 1U << 12,
    ALPHA_BASE_HNDK  = 1U << 13,
    ALPHA_BASE_LSHIFT = 1U << 14,
    ALPHA_BASE_RSHIFT  = 1U << 15,
};


#ifndef K_ALPHA_LSFT
#define K_ALPHA_LSFT KC_SPC
#endif

#ifndef K_ALPHA_RSFT
#define K_ALPHA_RSFT KC_SPC
#endif


#ifndef ALPHA_BASE_TERM
#define ALPHA_BASE_TERM STKIN_TERM
#endif

