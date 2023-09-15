// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later
// Special thanks to Whorf for his help with this

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#ifndef TAIPO_TAP_TIMEOUT
#define TAIPO_TAP_TIMEOUT 150
#endif

typedef struct {
    uint16_t keycode;
    bool     hold;
    bool     hold_handled;
} keypress;

typedef struct {
    uint16_t combo;
    uint16_t timer;
    keypress key;
} state;

static state left_state;
static state right_state;

static void clear_state(state* state) {
    state->combo            = 0;
    state->timer            = 0;
    state->key.keycode      = KC_NO;
    state->key.hold         = false;
    state->key.hold_handled = false;
}

static void clear_all_state(void) {
    clear_state(&left_state);
    clear_state(&right_state);
}

#if defined(TAIPO_FLAVOR_FLAT)
#define it 1 << 8
#define ot 1 << 9
#define both ot | it
#define d 1 << 0
#define a 1 << 1
#define n 1 << 2
#define i 1 << 3
#define r 1 << 4
#define o 1 << 5
#define t 1 << 6
#define e 1 << 7
#define s n | i
#define h t | e
#define l o | t
#define c a | n
#define u o | e
#define m a | i
#define w t | i
#define f n | e
#define g o | i
#define y a | e
#define p a | n | i
#define b o | t | e
#define v r | o
#define k d | a
#define j d | i
#define x r | e
#define q d | a | n
#define z r | o | t
#define eql d | e
#define minus r | i
#define slsh o | n
#define gui n | t
#define ctrl i | e
#define alt s | o
#define ralt r | a
#define play d | a | n | i
#define prnt r | o | t | e
#define ins r | o | e
#define layer d | a | i

static uint16_t determine_key(uint16_t val) {
    switch (val) {
        case it:
            return KC_BSPC;
        case ot:
            return KC_SPC;
        case both:
            return KC_LSFT;
        case e:
            return KC_E;
        case e | ot:
            return S(KC_E);
        case e | it:
            return KC_RIGHT;
        case e | both:
            return KC_END;
        case t:
            return KC_T;
        case t | ot:
            return S(KC_T);
        case t | it:
            return KC_DOWN;
        case t | both:
            return KC_PGDN;
        case a:
            return KC_A;
        case a | ot:
            return S(KC_A);
        case a | it:
            return KC_ESC;
        case a | both:
            return KC_DEL;
        case o:
            return KC_O;
        case o | ot:
            return S(KC_O);
        case o | it:
            return KC_LEFT;
        case o | both:
            return KC_HOME;
        case i:
            return KC_I;
        case i | ot:
            return S(KC_I);
        case i | it:
            return KC_ENTER;
        case i | both:
            return KC_TAB;
        case n:
            return KC_N;
        case n | ot:
            return S(KC_N);
        case n | it:
            return KC_UP;
        case n | both:
            return KC_PGUP;
        case s:
            return KC_S;
        case s | ot:
            return S(KC_S);
        case s | it:
            return KC_DOT;
        case s | both:
            return KC_AT;
        case h:
            return KC_H;
        case h | ot:
            return S(KC_H);
        case h | it:
            return KC_COMM;
        case h | both:
            return KC_HASH;
        case r:
            return KC_R;
        case r | ot:
            return S(KC_R);
        case r | it:
            return KC_QUOT;
        case r | both:
            return KC_PERC;
        case d:
            return KC_D;
        case d | ot:
            return S(KC_D);
        case d | it:
            return KC_DQT;
        case d | both:
            return KC_DLR;
        case l:
            return KC_L;
        case l | ot:
            return S(KC_L);
        case l | it:
            return KC_0;
        case l | both:
            return KC_F10;
        case c:
            return KC_C;
        case c | ot:
            return S(KC_C);
        case c | it:
            return KC_1;
        case c | both:
            return KC_F1;
        case u:
            return KC_U;
        case u | ot:
            return S(KC_U);
        case u | it:
            return KC_2;
        case u | both:
            return KC_F2;
        case m:
            return KC_M;
        case m | ot:
            return S(KC_M);
        case m | it:
            return KC_3;
        case m | both:
            return KC_F3;
        case w:
            return KC_W;
        case w | ot:
            return S(KC_W);
        case w | it:
            return KC_4;
        case w | both:
            return KC_F4;
        case f:
            return KC_F;
        case f | ot:
            return S(KC_F);
        case f | it:
            return KC_5;
        case f | both:
            return KC_F5;
        case g:
            return KC_G;
        case g | ot:
            return S(KC_G);
        case g | it:
            return KC_6;
        case g | both:
            return KC_F6;
        case y:
            return KC_Y;
        case y | ot:
            return S(KC_Y);
        case y | it:
            return KC_7;
        case y | both:
            return KC_F7;
        case p:
            return KC_P;
        case p | ot:
            return S(KC_P);
        case p | it:
            return KC_8;
        case p | both:
            return KC_F8;
        case b:
            return KC_B;
        case b | ot:
            return S(KC_B);
        case b | it:
            return KC_9;
        case b | both:
            return KC_F9;
        case v:
            return KC_V;
        case v | ot:
            return S(KC_V);
        case v | it:
            return KC_QUES;
        case v | both:
            return KC_F11;
        case k:
            return KC_K;
        case k | ot:
            return S(KC_K);
        case k | it:
            return KC_EXLM;
        case k | both:
            return KC_F12;
        case j:
            return KC_J;
        case j | ot:
            return S(KC_J);
        case j | it:
            return KC_SCLN;
        case j | both:
            return KC_NO;
        case x:
            return KC_X;
        case x | ot:
            return S(KC_X);
        case x | it:
            return KC_COLN;
        case x | both:
            return KC_NO;
        case q:
            return KC_Q;
        case q | ot:
            return S(KC_Q);
        case q | it:
            return KC_GRV;
        case q | both:
            return KC_NO;
        case z:
            return KC_Z;
        case z | ot:
            return S(KC_Z);
        case z | it:
            return KC_TILD;
        case z | both:
            return KC_NO;
        case eql:
            return KC_EQL;
        case eql | ot:
            return KC_PLUS;
        case eql | it:
            return KC_ASTR;
        case eql | both:
            return KC_CIRC;
        case minus:
            return KC_MINUS;
        case minus | ot:
            return KC_UNDS;
        case minus | it:
            return KC_AMPR;
        case minus | both:
            return KC_NO;
        case slsh:
            return KC_SLSH;
        case slsh | ot:
            return KC_BSLS;
        case slsh | it:
            return KC_PIPE;
        case slsh | both:
            return KC_NO;
        case gui:
            return KC_LGUI;
        case gui | ot:
            return KC_RPRN;
        case gui | it:
            return KC_LPRN;
        case gui | both:
            return KC_MOD_GS;
        case ctrl:
            return KC_LCTL;
        case ctrl | ot:
            return KC_RBRC;
        case ctrl | it:
            return KC_LBRC;
        case ctrl | both:
            return KC_MOD_CS;
        case alt:
            return KC_LALT;
        case alt | ot:
            return KC_RCBR;
        case alt | it:
            return KC_LCBR;
        case alt | both:
            return KC_MOD_AS;
        case ralt:
            return KC_RALT;
        case ralt | ot:
            return KC_GT;
        case ralt | it:
            return KC_LT;
        case ralt | both:
            return KC_MOD_RS;
        case play:
            return KC_MEDIA_PLAY_PAUSE;
        case play | ot:
            return KC_MEDIA_NEXT_TRACK;
        case play | it:
            return KC_MEDIA_PREV_TRACK;
        case play | both:
            return KC_MEDIA_STOP;
        case prnt:
            return KC_PRINT_SCREEN;
        case prnt | ot:
            return KC_KB_VOLUME_UP;
        case prnt | it:
            return KC_KB_VOLUME_DOWN;
        case prnt | both:
            return KC_KB_MUTE;
        case ins:
            return KC_INS;
        case ins | ot:
            return KC_BRIGHTNESS_UP;
        case ins | it:
            return KC_BRIGHTNESS_DOWN;
        case ins | both:
            return KC_NO;
        case layer:
            return KC_LAYER0;
        case layer | ot:
            return KC_LAYER1;
        case layer | it:
            return KC_LAYER2;
        case layer | both:
            return KC_LAYER3;
    }
    return KC_NO;
}
#elif defined(TAIPO_FLAVOR_POSH)
#define it 1 << 8
#define ot 1 << 9
#define both ot | it
#define e 1 << 7
#define t 1 << 6
#define a 1 << 1
#define o 1 << 5
#define i 1 << 3
#define n 1 << 2
#define s n | i
#define h t | e
#define r n | e
#define d a | n
#define l t | i
#define c o | e
#define u o | t
#define m a | e
#define w o | i
#define f a | i
#define g o | n
#define y o | n | i
#define p a | n | i
#define b o | t | e
#define v o | n | e
#define k a | n | e
#define j o | t | i
#define x a | t | e
#define q t | e | i
#define z n | t | e
#define ques a | t
#define grv o | e | i
#define gui t | n
#define ctrl e | i
#define alt o | a
#define ralt a | o | t
#define play a | o | e
#define prnt o | t | n
#define ins a | i | e
#define layer a | t | i


static uint16_t determine_key(uint16_t val) {
    switch (val) {
        case it:
            return KC_BSPC;
        case ot:
            return KC_SPC;
        case both:
            return KC_LSFT;
        case e:
            return KC_E;
        case e | ot:
            return S(KC_E);
        case e | it:
            return KC_RIGHT;
        case e | both:
            return KC_END;
        case t:
            return KC_T;
        case t | ot:
            return S(KC_T);
        case t | it:
            return KC_DOWN;
        case t | both:
            return KC_PGDN;
        case a:
            return KC_A;
        case a | ot:
            return S(KC_A);
        case a | it:
            return KC_ESC;
        case a | both:
            return KC_DEL;
        case o:
            return KC_O;
        case o | ot:
            return S(KC_O);
        case o | it:
            return KC_LEFT;
        case o | both:
            return KC_HOME;
        case i:
            return KC_I;
        case i | ot:
            return S(KC_I);
        case i | it:
            return KC_ENTER;
        case i | both:
            return KC_TAB;
        case n:
            return KC_N;
        case n | ot:
            return S(KC_N);
        case n | it:
            return KC_UP;
        case n | both:
            return KC_PGUP;
        case s:
            return KC_S;
        case s | ot:
            return S(KC_S);
        case s | it:
            return KC_DOT;
        case s | both:
            return KC_DQT;
        case h:
            return KC_H;
        case h | ot:
            return S(KC_H);
        case h | it:
            return KC_COMM;
        case h | both:
            return KC_QUOT;
        case r:
            return KC_R;
        case r | ot:
            return S(KC_R);
        case r | it:
            return KC_0;
        case r | both:
            return KC_F10;
        case d:
            return KC_D;
        case d | ot:
            return S(KC_D);
        case d | it:
            return KC_1;
        case d | both:
            return KC_F1;
        case l:
            return KC_L;
        case l | ot:
            return S(KC_L);
        case l | it:
            return KC_2;
        case l | both:
            return KC_F2;
        case c:
            return KC_C;
        case c | ot:
            return S(KC_C);
        case c | it:
            return KC_3;
        case c | both:
            return KC_F3;
        case u:
            return KC_U;
        case u | ot:
            return S(KC_U);
        case u | it:
            return KC_4;
        case u | both:
            return KC_F4;
        case m:
            return KC_M;
        case m | ot:
            return S(KC_M);
        case m | it:
            return KC_5;
        case m | both:
            return KC_F5;
        case w:
            return KC_W;
        case w | ot:
            return S(KC_W);
        case w | it:
            return KC_6;
        case w | both:
            return KC_F6;
        case f:
            return KC_F;
        case f | ot:
            return S(KC_F);
        case f | it:
            return KC_7;
        case f | both:
            return KC_F7;
        case g:
            return KC_G;
        case g | ot:
            return S(KC_G);
        case g | it:
            return KC_8;
        case g | both:
            return KC_F8;
        case y:
            return KC_Y;
        case y | ot:
            return S(KC_Y);
        case y | it:
            return KC_9;
        case y | both:
            return KC_F9;
        case p:
            return KC_P;
        case p | ot:
            return S(KC_P);
        case p | it:
            return KC_PLUS;
        case p | both:
            return KC_EQL;
        case b:
            return KC_B;
        case b | ot:
            return S(KC_B);
        case b | it:
            return KC_MINS;
        case b | both:
            return KC_UNDS;
        case v:
            return KC_V;
        case v | ot:
            return S(KC_V);
        case v | it:
            return KC_SLSH;
        case v | both:
            return KC_BSLS;
        case k:
            return KC_K;
        case k | ot:
            return S(KC_K);
        case k | it:
            return KC_SCLN;
        case k | both:
            return KC_PIPE;
        case j:
            return KC_J;
        case j | ot:
            return S(KC_J);
        case j | it:
            return KC_COLN;
        case j | both:
            return KC_ASTR;
        case x:
            return KC_X;
        case x | ot:
            return S(KC_X);
        case x | it:
            return KC_DLR;
        case x | both:
            return KC_NO;
        case q:
            return KC_Q;
        case q | ot:
            return S(KC_Q);
        case q | it:
            return KC_AT;
        case q | both:
            return KC_F11;
        case z:
            return KC_Z;
        case z | ot:
            return S(KC_Z);
        case z | it:
            return KC_AMPR;
        case z | both:
            return KC_F12;
        case ques:
            return KC_QUES;
        case ques | ot:
            return KC_EXLM;
        case ques | it:
            return KC_HASH;
        case ques | both:
            return KC_CIRC;
        case grv:
            return KC_GRV;
        case grv | ot:
            return KC_TILD;
        case grv | it:
            return KC_PERC;
        case grv | both:
            return KC_NO;
        case gui:
            return KC_LGUI;
        case gui | ot:
            return KC_RPRN;
        case gui | it:
            return KC_LPRN;
        case gui | both:
            return KC_MOD_GS;
        case ctrl:
            return KC_LCTL;
        case ctrl | ot:
            return KC_RBRC;
        case ctrl | it:
            return KC_LBRC;
        case ctrl | both:
            return KC_MOD_CS;
        case alt:
            return KC_LALT;
        case alt | ot:
            return KC_RCBR;
        case alt | it:
            return KC_LCBR;
        case alt | both:
            return KC_MOD_AS;
        case ralt:
            return KC_RALT;
        case ralt | ot:
            return KC_GT;
        case ralt | it:
            return KC_LT;
        case ralt | both:
            return KC_MOD_RS;
        case play:
            return KC_MEDIA_PLAY_PAUSE;
        case play | ot:
            return KC_MEDIA_NEXT_TRACK;
        case play | it:
            return KC_MEDIA_PREV_TRACK;
        case play | both:
            return KC_MEDIA_STOP;
        case prnt:
            return KC_PRINT_SCREEN;
        case prnt | ot:
            return KC_KB_VOLUME_UP;
        case prnt | it:
            return KC_KB_VOLUME_DOWN;
        case prnt | both:
            return KC_KB_MUTE;
        case ins:
            return KC_INS;
        case ins | ot:
            return KC_BRIGHTNESS_UP;
        case ins | it:
            return KC_BRIGHTNESS_DOWN;
        case ins | both:
            return KC_NO;
        case layer:
            return KC_LAYER0;
        case layer | ot:
            return KC_LAYER1;
        case layer | it:
            return KC_LAYER2;
        case layer | both:
            return KC_LAYER3;
        // case %:
        //     return KC_;
        // case % | ot:
        //     return S(KC_);
        // case % | it:
        //     return KC_;
        // case % | both:
        //     return KC_;
    }
    return KC_NO;
}
#else
#define r 1 << 0
#define s 1 << 1
#define n 1 << 2
#define i 1 << 3
#define a 1 << 4
#define o 1 << 5
#define t 1 << 6
#define e 1 << 7
#define it 1 << 8
#define ot 1 << 9
static uint16_t determine_key(uint16_t val) {
    switch (val) {
        case it:
            return KC_BSPC;
        case ot:
            return KC_SPC;
        case r:
            return KC_R;
        case r | ot:
            return S(KC_R);
        case r | it:
            return KC_GT;
        case r | ot | it:
            return KC_PRINT_SCREEN;
        case s:
            return KC_S;
        case s | ot:
            return S(KC_S);
        case s | it:
            return KC_RCBR;
        case s | ot | it:
            return KC_BRIGHTNESS_UP;
        case n:
            return KC_N;
        case n | ot:
            return S(KC_N);
        case n | it:
            return KC_RBRC;
        case n | ot | it:
            return KC_BRIGHTNESS_DOWN;
        case i:
            return KC_I;
        case i | ot:
            return S(KC_I);
        case i | it:
            return KC_RPRN;
        case i | ot | it:
            return KC_MEDIA_PLAY_PAUSE;
        case a:
            return KC_A;
        case a | ot:
            return S(KC_A);
        case a | it:
            return KC_LT;
        case a | ot | it:
            return KC_MEDIA_NEXT_TRACK;
        case o:
            return KC_O;
        case o | ot:
            return S(KC_O);
        case o | it:
            return KC_LCBR;
        case o | ot | it:
            return KC_KB_VOLUME_UP;
        case t:
            return KC_T;
        case t | ot:
            return S(KC_T);
        case t | it:
            return KC_LBRC;
        case t | ot | it:
            return KC_KB_VOLUME_DOWN;
        case e:
            return KC_E;
        case e | ot:
            return S(KC_E);
        case e | it:
            return KC_LPRN;
        case e | ot | it:
            return KC_MEDIA_PREV_TRACK;
        case e | o:
            return KC_C;
        case e | o | ot:
            return S(KC_C);
        case e | o | it:
            return KC_1;
        case e | o | ot | it:
            return KC_F1;
        case t | o:
            return KC_U;
        case t | o | ot:
            return S(KC_U);
        case t | o | it:
            return KC_2;
        case t | o | ot | it:
            return KC_F2;
        case t | a:
            return KC_Q;
        case t | a | ot:
            return S(KC_Q);
        case t | a | it:
            return KC_3;
        case t | a | ot | it:
            return KC_F3;
        case o | a:
            return KC_L;
        case o | a | ot:
            return S(KC_L);
        case o | a | it:
            return KC_4;
        case o | a | ot | it:
            return KC_F4;
        case i | n:
            return KC_Y;
        case i | n | ot:
            return S(KC_Y);
        case i | n | it:
            return KC_5;
        case i | n | ot | it:
            return KC_F5;
        case i | s:
            return KC_F;
        case i | s | ot:
            return S(KC_F);
        case i | s | it:
            return KC_6;
        case i | s | ot | it:
            return KC_F6;
        case n | s:
            return KC_P;
        case n | s | ot:
            return S(KC_P);
        case n | s | it:
            return KC_7;
        case n | s | ot | it:
            return KC_F7;
        case n | r:
            return KC_Z;
        case n | r | ot:
            return S(KC_Z);
        case n | r | it:
            return KC_8;
        case n | r | ot | it:
            return KC_F8;
        case s | r:
            return KC_B;
        case s | r | ot:
            return S(KC_B);
        case s | r | it:
            return KC_9;
        case s | r | ot | it:
            return KC_F9;
        case e | t:
            return KC_H;
        case e | t | ot:
            return S(KC_H);
        case e | t | it:
            return KC_0;
        case e | t | ot | it:
            return KC_F10;
        case e | a:
            return KC_D;
        case e | a | ot:
            return S(KC_D);
        case e | a | it:
            return KC_AT;
        case e | a | ot | it:
            return KC_F11;
        case i | r:
            return KC_G;
        case i | r | ot:
            return S(KC_G);
        case i | r | it:
            return KC_HASH;
        case i | r | ot | it:
            return KC_F12;
        case t | r:
            return KC_X;
        case t | r | ot:
            return S(KC_X);
        case t | r | it:
            return KC_CIRC;
        case t | r | ot | it:
            return C(KC_X);
        case i | o:
            return KC_K;
        case i | o | ot:
            return S(KC_K);
        case i | o | it:
            return KC_PLUS;
        case i | o | ot | it:
            return C(KC_C);
        case e | s:
            return KC_V;
        case e | s | ot:
            return S(KC_V);
        case e | s | it:
            return KC_ASTR;
        case e | s | ot | it:
            return C(KC_V);
        case n | a:
            return KC_J;
        case n | a | ot:
            return S(KC_J);
        case n | a | it:
            return KC_EQL;
        case n | a | ot | it:
            return C(KC_Z);
        case e | r:
            return KC_M;
        case e | r | ot:
            return S(KC_M);
        case e | r | it:
            return KC_DLR;
        // case e | r | ot | it:
        //     return KC_NO;
        case i | a:
            return KC_W;
        case i | a | ot:
            return S(KC_W);
        case i | a | it:
            return KC_AMPR;
        // case i | a | ot | it:
        //     return KC_NO;
        case t | s:
            return KC_SLSH;
        case t | s | ot:
            return KC_BSLS;
        case t | s | it:
            return KC_PIPE;
        // case t | s | ot | it:
        //     return KC_NO;
        case n | o:
            return KC_MINS;
        case n | o | ot:
            return KC_UNDS;
        case n | o | it:
            return KC_PERC;
        // case n | o | ot | it:
        //     return KC_NO;
        case i | t:
            return KC_QUES;
        case i | t | ot:
            return KC_EXLM;
        // case i | t | it:
        //     return KC_NO;
        // case i | t | ot | it:
        //     return KC_NO;
        case e | n:
            return KC_COMM;
        case e | n | ot:
            return KC_DOT;
        case e | n | it:
            return KC_TILD;
        // case e | n | ot | it:
        //     return KC_NO;
        case o | r:
        case t | o | a:
            return KC_SCLN;
        case o | r | ot:
        case t | o | a | ot:
            return KC_COLN;
        // case o | r | it:
        // case t | o | a | it:
        //     return KC_NO;
        // case o | r | ot | it:
        // case t | o | a | ot | it:
        //     return KC_NO;
        case s | a:
        case n | s | r:
            return KC_QUOT;
        case s | a | ot:
        case n | s | r | ot:
            return KC_DQT;
        case s | a | it:
        case n | s | r | it:
            return KC_GRV;
        // case s | a | ot | it:
        // case n | s | r | ot | it:
        //     return KC_NO;
        case i | n | s:
            return KC_TAB;
        case i | n | s | ot:
            return KC_DEL;
        case i | n | s | it:
            return KC_INS;
        // case i | n | s | ot | it:
        //     return KC_NO;
        case e | t | o:
            return KC_ENTER;
        case e | t | o | ot:
            return KC_ESC;
        case e | t | o | it:
            return KC_RALT;
        // case e | t | o | ot | it:
        //     return KC_NO;
        case a | r:
            return KC_LGUI;
        case a | r | ot:
            return KC_RIGHT;
        case a | r | it:
            return KC_PGUP;
        case a | r | ot | it:
            return KC_LAYER3;
        case o | s:
            return KC_LALT;
        case o | s | ot:
            return KC_UP;
        case o | s | it:
            return KC_HOME;
        case o | s | ot | it:
            return KC_LAYER2;
        case t | n:
            return KC_LCTL;
        case t | n | ot:
            return KC_DOWN;
        case t | n | it:
            return KC_END;
        case t | n | ot | it:
            return KC_LAYER1;
        case e | i:
            return KC_LSFT;
        case e | i | ot:
            return KC_LEFT;
        case e | i | it:
            return KC_PGDN;
        case e | i | ot | it:
            return KC_LAYER0;
        case r | a | s | o:
            return KC_MOD_GA;
        case r | a | n | t:
            return KC_MOD_GC;
        case r | a | i | e:
            return KC_MOD_GS;
        case s | o | n | t:
            return KC_MOD_AC;
        case s | o | i | e:
            return KC_MOD_AS;
        case n | t | i | e:
            return KC_MOD_CS;
        case r | a | s | o | n | t:
            return KC_MOD_GAC;
        case r | a | s | o | i | e:
            return KC_MOD_GAS;
        case r | a | n | t | i | e:
            return KC_MOD_GCS;
        case s | o | n | t | i | e:
            return KC_MOD_ACS;
        case r | a | s | o | n | t | i | e:
            return KC_MOD_GACS;
    }
    return KC_NO;
}
#endif

static void handle_key(keypress* key) {
    uint8_t mods = 0;
    switch (key->keycode) {
        case KC_MOD_GA:
            mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT);
            break;
        case KC_MOD_GC:
            mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL);
            break;
        case KC_MOD_GS:
            mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT);
            break;
        case KC_MOD_AC:
            mods = MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL);
            break;
        case KC_MOD_AS:
            mods = MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT);
            break;
        case KC_MOD_CS:
            mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT);
            break;
        case KC_MOD_GAC:
            mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL);
            break;
        case KC_MOD_GAS:
            mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT);
            break;
        case KC_MOD_GCS:
            mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT);
            break;
        case KC_MOD_ACS:
            mods = MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT);
            break;
        case KC_MOD_GACS:
            mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT);
            break;
        case KC_LGUI:
        case KC_LALT:
        case KC_RALT:
        case KC_LCTL:
        case KC_LSFT:
            mods = MOD_BIT(key->keycode);
            break;
        case KC_LAYER0:
            layer_move(0);
            clear_all_state();
            break;
        case KC_LAYER1:
            layer_move(1);
            clear_all_state();
            break;
        case KC_LAYER2:
            layer_move(2);
            clear_all_state();
            break;
        case KC_LAYER3:
            layer_move(3);
            clear_all_state();
            break;
        default:
            if (key->hold_handled) {
                unregister_code16(key->keycode);
            } else if (key->hold) {
                register_code16(key->keycode);
                key->hold_handled = true;
            } else {
                tap_code16(key->keycode);
            }
    }
    if (mods) {
        if (key->hold_handled) {
            del_mods(mods);
            send_keyboard_report();
        } else if (key->hold) {
            add_mods(mods);
            send_keyboard_report();
            key->hold_handled = true;
        } else {
            add_oneshot_mods(mods);
        }
    }
}

bool taipo_process_record_user(uint16_t keycode, keyrecord_t* record) {
    uint16_t key   = keycode - TP_TLP;
    state*   state = (key / 10) ? &right_state : &left_state;

    if (record->event.pressed) {
        if (state->key.keycode != KC_NO) {
            handle_key(&state->key);
            clear_state(state);
        }
        state->timer = (record->event.time + TAIPO_TAP_TIMEOUT) | 1;
        state->combo |= 1 << (key % 10);
    } else {
        if (!state->key.hold) {
            state->key.keycode = determine_key(state->combo);
        }
        handle_key(&state->key);
        clear_state(state);
    }
    return false;
}

void taipo_matrix_scan_user(void) {
    if (left_state.timer && timer_expired(timer_read(), left_state.timer)) {
        left_state.key.keycode = determine_key(left_state.combo);
        left_state.key.hold    = true;
        handle_key(&left_state.key);
        left_state.timer = 0;
    }
    if (right_state.timer && timer_expired(timer_read(), right_state.timer)) {
        right_state.key.keycode = determine_key(right_state.combo);
        right_state.key.hold    = true;
        handle_key(&right_state.key);
        right_state.timer = 0;
    }
}
