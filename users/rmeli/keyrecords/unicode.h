#pragma once
#include QMK_KEYBOARD_H

// Needs to be active on the OS side as well
// https://docs.qmk.fm/#/feature_unicode?id=input-modes

enum unicode_names {
    aGRV,
    AGRV,
    eGRV,
    EGRV,
    eACT,
    EACT,
    iGRV,
    IGRV,
    oGRV,
    OGRV,
    uGRV,
    UGRV,
};

const uint32_t PROGMEM unicode_map[] = {
    // KC_A
    [aGRV]  = 0x00E0, // à
    [AGRV]  = 0x00C0, // À
    // KC_E
    [eGRV]  = 0x00E8, // è
    [EGRV]  = 0x00C8, // È
    [eACT]  = 0x00E9, // é
    [EACT]  = 0x00C9, // É
    // KC_I
    [iGRV]  = 0x00EC, // ì
    [IGRV]  = 0x00CC, // Ì
    // KC_O
    [oGRV]  = 0x00F2, // ò
    [OGRV]  = 0x00D2, // Ò
    // KC_U
    [uGRV]  = 0x00F9, // ù
    [UGRV]  = 0x00D9, // Ù
};

// Accents
#define A_GRV XP(aGRV, AGRV)
#define E_GRV XP(eGRV, EGRV)
#define I_GRV XP(iGRV, IGRV)
#define O_GRV XP(oGRV, OGRV)
#define U_GRV XP(uGRV, UGRV)
#define E_ACT XP(eACT, EACT)
