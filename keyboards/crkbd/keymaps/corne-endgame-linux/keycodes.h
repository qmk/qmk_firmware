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
#define M_UNDO C(UK_Z)
#define M_CUT C(UK_X)
#define M_COPY C(UK_C)
#define M_PSTE C(UK_V)
#define M_SAVE C(UK_S)
#define LAU A(KC_SPC)    // Launcher for krunner 


//One Shot Modifiers
#define CTRL OSM(MOD_LCTL)
#define ALT OSM(MOD_LALT)
#define CMD OSM(MOD_LGUI)
#define SHFT OSM(MOD_LSFT)


// awkward symbols to type
#define TILDA UK_TILD
#define PIPE UK_PIPE
#define ATAT UK_AT
#define MYHASH UK_HASH
#define KASHISH S(UK_3)
#define GRAVE UK_GRV

//shortcuts
#define SCRNSHOT G(S(UK_4))
