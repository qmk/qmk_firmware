/* 	2019, g Heavy Industries
        Blessed mother of Christ, please keep this readable
        and protect us from segfaults. For thine is the clock,
        the slave and the master. Until we return from main.

        Amen.

        This is a stripped down version of the Georgi engine meant for use with
        . As such serial-Steno features are disabled, chords are 16bits and
        crap is removed where possible
*/

#include QMK_KEYBOARD_H
#pragma once
#include "keymap.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "config_engine.h"
#include <avr/pgmspace.h>
#include "wait.h"
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif

// Set defaults
#ifndef IN_CHORD_MASK
#    define IN_CHORD_MASK 0xFFFFFFFFFFFFFFFF
#endif

#ifndef COMBO_END
#    define COMBO_END 0x00
#endif

// In memory chord datatypes
enum specialActions {
    SPEC_STICKY,
    SPEC_REPEAT,
    SPEC_CLICK,
    SPEC_SWITCH,
};
struct funcEntry {
    C_SIZE chord;
    void (*act)(void);
} funcEntry_t;
struct stringEntry {
    C_SIZE chord;
    PGM_P  str;
} stringEntry_t;
struct comboEntry {
    C_SIZE chord;
    PGM_P  keys;
} comboEntry_t;
struct keyEntry {
    C_SIZE  chord;
    uint8_t key;
} keyEntry_t;
struct specialEntry {
    C_SIZE              chord;
    enum specialActions action;
    uint16_t            arg;
} specialEntry_t;

// Chord Temps
extern C_SIZE cChord;
extern C_SIZE test;
extern size_t keymapsCount;  // Total keymaps (exported from keymap.c)

// Function defs
void    processKeysUp(void);
void    processChord(void);
C_SIZE  processQwerty(bool lookup);
C_SIZE  processFakeSteno(bool lookup);
void    saveState(C_SIZE cChord);
void    restoreState(void);
uint8_t bitpop_v(C_SIZE val);

// Macros for use in keymap.c
void   SEND(uint8_t kc);
void   REPEAT(void);
void   SET_STICKY(C_SIZE);
void   SWITCH_LAYER(int);
void   CLICK_MOUSE(uint8_t);
C_SIZE process_chord_getnext(C_SIZE cur_chord);
// Run before hitting the engine. Return false to skip engine processing
C_SIZE process_engine_pre(C_SIZE cur_chord, uint16_t keycode, keyrecord_t *record);
// Run after reading a chord.
C_SIZE process_engine_post(C_SIZE cur_chord, uint16_t keycode, keyrecord_t *record);

// Keymap helpers
// New Approach, multiple structures
#define P_KEYMAP(chord, keycode) {chord, keycode},

#define K_KEYMAP(chord, name, ...) {chord, (PGM_P)&name},
#define K_ACTION(chord, name, ...) const uint8_t name[] PROGMEM = __VA_ARGS__;

#define S_KEYMAP(chord, name, string) {chord, (PGM_P)&name},
#define S_ACTION(chord, name, string) const char name[] PROGMEM = string;

#define X_KEYMAP(chord, name, func) {chord, name},
#define X_ACTION(chord, name, func) \
    void name(void) { func }

#define Z_KEYMAP(chord, act, arg) {chord, act, arg},

#define TEST_COLLISION(chord, ...) \
    case chord:                    \
        break;
#define BLANK(...)

// Shift to internal representation
// i.e) S(teno)R(ight)F
#define STN(n) ((C_SIZE)1 << n)
#define ENGINE_HOOK(keycode, chord)                        \
    case keycode:                                          \
        pr ? (pressed |= (chord)) : (pressed &= ~(chord)); \
        break;
