#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keymap_uk.h"



// Layer keys
#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define NUM MO(_NUM)
#define MOUSE MO(_MOUS)
#define MEDIA MO(_MEDIA)
// FUN is both together

// shortcuts
#define M_UNDO G(UK_Z)
#define M_CUT G(UK_X)
#define M_COPY G(UK_C)
#define M_PSTE G(UK_V)
#define M_SAVE G(UK_S)
#define TAB_L G(S(UK_LBRC))
#define TAB_R G(S(UK_RBRC))
#define WS_L A(G(KC_LEFT))  // select word left
#define WS_R A(G(KC_RIGHT)) // select word right
#define W_L A(KC_LEFT)      // move word left
#define W_R A(KC_RIGHT)     // move word right
#define LAU G(KC_SPC)    // Launcher for krunner 


//One Shot Modifiers
#define CTRL OSM(MOD_LCTL)
#define ALT OSM(MOD_LALT)
#define CMD OSM(MOD_LGUI)
#define SHFT OSM(MOD_LSFT)

// MacOS Bindings

// awkward symbols to type
#define TILDA S(UK_BSLS)
#define PIPE S(UK_HASH)
#define ATAT S(UK_2)
#define MYHASH A(UK_3)
#define KASHISH S(UK_3)


//MacOS shortcuts
#define SCRNSHOT G(S(UK_4))
