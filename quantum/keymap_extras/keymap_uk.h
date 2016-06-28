#ifndef KEYMAP_UK_H
#define KEYMAP_UK_H

#include "keymap.h"

// Alt gr
#define ALGR(kc) kc | 0x1400
#define NO_ALGR KC_RALT

// Normal characters
#define UK_HASH KC_NUHS

#define UK_BSLS	KC_NUBS

// Shifted characters
#define UK_NOT	LSFT(KC_GRV)
#define UK_QUOT	LSFT(KC_2)
#define UK_PND	LSFT(KC_3)

#define UK_AT	LSFT(KC_QUOT)
#define UK_TILD	LSFT(KC_NUHS)

#define UK_PIPE	LSFT(KC_NUBS)

// Alt Gr-ed characters
#define UK_BRKP	ALGR(KC_GRV)
#define UK_EURO	ALGR(KC_4)

#define UK_EACT	ALGR(KC_E)
#define UK_UACT	ALGR(KC_U)
#define UK_IACT ALGR(KC_I)
#define UK_OACT ALGR(KC_O)

#define UK_AACT ALGR(KC_A)

#endif