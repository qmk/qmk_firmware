/* Danish keymaps - and shorthand defines */

#ifndef KEYMAP_DANISH
#define KEYMAP_DANISH

// Normal characters
#define half KC_GRV  // ½
#define plus KC_MINS // +
#define acut KC_EQL  // ´
#define aa   KC_LBRC // å
#define uml  KC_RBRC // ¨
#define ae   KC_SCLN // æ
#define oe   KC_QUOT // ø
#define quot KC_BSLS // '
#define lt   KC_NUBS // <
#define mins KC_SLSH // -

#define a KC_A
#define b KC_B
#define c KC_C
#define d KC_D
#define e KC_E
#define f KC_F
#define g KC_G
#define h KC_H
#define i KC_I
#define j KC_J
#define k KC_K
#define l KC_L
#define m KC_M
#define n KC_N
#define o KC_O
#define p KC_P
#define q KC_Q
#define r KC_R
#define s KC_S
#define t KC_T
#define u KC_U
#define v KC_V
#define w KC_W
#define x KC_X
#define y KC_Y
#define z KC_Z

#define f1  KC_F1
#define f2  KC_F2
#define f3  KC_F3
#define f4  KC_F4
#define f5  KC_F5
#define f6  KC_F6
#define f7  KC_F7
#define f8  KC_F8
#define f9  KC_F9
#define f10 KC_F10
#define f11 KC_F11
#define f12 KC_F12

#define lalt KC_LALT
#define lctl KC_LCTL
#define lsft KC_LSFT
#define ralt KC_RALT
#define rctl KC_RCTL
#define rsft KC_RSFT
#define lgui KC_LGUI

#define n0 KC_0
#define n1 KC_1
#define n2 KC_2
#define n3 KC_3
#define n4 KC_4
#define n5 KC_5
#define n6 KC_6
#define n7 KC_7
#define n8 KC_8
#define n9 KC_9

#define bspc KC_BSPC
#define caps KC_CAPS
#define comm KC_COMM
#define spc  KC_SPC
#define tab  KC_TAB
#define del  KC_DEL
#define dot  KC_DOT
#define ent  KC_ENT
#define esc  KC_ESC

#define up   KC_UP
#define down KC_DOWN
#define left KC_LEFT
#define rght KC_RGHT
#define home KC_HOME
#define end  KC_END
#define pgdn KC_PGDN
#define pgup KC_PGUP
#define ins  KC_INS
#define prnt KC_PSCR

#define volu KC_VOLU
#define vold KC_VOLD
#define mute KC_MUTE
#define next KC_MNXT
#define play KC_MPLY
#define prev KC_MPRV


// Shifted characters
#define sect LSFT(half) // §
#define exlm LSFT(n1)   // !
#define dquo LSFT(n2)   // "
#define hash LSFT(n3)   // #
#define bult LSFT(n4)   // ¤
#define perc LSFT(n5)   // %
#define ampr LSFT(n6)   // &
#define slsh LSFT(n7)   // /
#define lprn LSFT(n8)   // (
#define rprn LSFT(n9)   // )
#define eql  LSFT(n0)   // =
#define ques LSFT(plus) // ?
#define grv  LSFT(acut) // `
#define circ LSFT(uml)  // ^
#define astr LSFT(quot) // *
#define gt   LSFT(lt)   // >
#define scln LSFT(comm) // ;
#define coln LSFT(dot)  // :
#define unds LSFT(mins) // _

// AltGr characters
#define at   ALGR(n2)   // @
#define pnd  ALGR(n3)   // £
#define dlr  ALGR(n4)   // $
#define lcbr ALGR(n7)   // {
#define lbrc ALGR(n8)   // [
#define rbrc ALGR(n9)   // ]
#define rcbr ALGR(n0)   // }
#define pipe ALGR(acut) // |
#define euro ALGR(e)    // €
#define tild ALGR(uml)  // ~
#define bsls ALGR(lt)   // Backslash
#define mu   ALGR(m)    // µ

#endif